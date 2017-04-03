#include "decaf_config.h"
#include "debugger/debugger_branchcalc.h"
#include "kernel/kernel.h"
#include "kernel/kernel_loader.h"

#include <atomic>
#include <common/decaf_assert.h>
#include <common/log.h>
#include <libcpu/cpu.h>
#include <libcpu/cpu_breakpoints.h>
#include <libcpu/mem.h>
#include <condition_variable>

namespace debugger
{

static std::mutex
sMutex;

static std::condition_variable
sPauseReleaseCond;

static std::atomic<uint32_t>
sIsPausing;

static std::atomic<uint32_t>
sIsResuming;

static std::atomic_bool
sIsPaused;

static cpu::Core *
sCorePauseState[3];

static uint32_t
sPauseInitiatorCoreId;

bool
enabled()
{
   return decaf::config::debugger::enabled;
}

bool
paused()
{
   return sIsPaused.load();
}

cpu::Core *
getPausedCoreState(uint32_t coreId)
{
   decaf_check(paused());
   return sCorePauseState[coreId];
}

uint32_t
getPauseInitiatorCoreId()
{
   decaf_check(paused());
   decaf_check(sPauseInitiatorCoreId < 3);
   return sPauseInitiatorCoreId;
}

void
pauseAll()
{
   for (auto i = 0; i < 3; ++i) {
      cpu::interrupt(i, cpu::DBGBREAK_INTERRUPT);
   }
}

void
resumeAll()
{
   auto oldState = sIsPaused.exchange(false);
   decaf_check(oldState);
   for (auto i = 0; i < 3; ++i) {
      sCorePauseState[i] = nullptr;
   }
   sPauseReleaseCond.notify_all();
}

static void
stepCore(uint32_t coreId, bool stepOver)
{
   decaf_check(sIsPaused.load());

   const cpu::CoreRegs *state = sCorePauseState[coreId];
   uint32_t nextInstr = calculateNextInstr(state, stepOver);
   cpu::addBreakpoint(nextInstr, cpu::Breakpoint::SingleFire);

   resumeAll();
}

void
stepCoreInto(uint32_t coreId)
{
   stepCore(coreId, false);
}

void
stepCoreOver(uint32_t coreId)
{
   stepCore(coreId, true);
}

void
handlePreLaunch()
{
   // Do not add entry breakpoints if debugger is disabled
   if (!decaf::config::debugger::enabled) {
      return;
   }

   if (decaf::config::debugger::break_on_entry) {
      auto appModule = kernel::getUserModule();
      auto userPreinit = appModule->findExport("__preinit_user");

      if (userPreinit) {
         cpu::addBreakpoint(userPreinit, cpu::Breakpoint::SingleFire);
      }

      auto start = appModule->entryPoint;
      cpu::addBreakpoint(start, cpu::Breakpoint::SingleFire);
   }
}

void
handleDbgBreakInterrupt()
{
   // If we are not initialised, we should ignore DbgBreaks
   if (!decaf::config::debugger::enabled) {
      return;
   }

   std::unique_lock<std::mutex> lock(sMutex);
   auto coreId = cpu::this_core::id();

   // Store our core state before we flip isPaused
   sCorePauseState[coreId] = cpu::this_core::state();

   // Check to see if we were the last core to join on the fun
   auto coreBit = 1 << coreId;
   auto isPausing = sIsPausing.fetch_or(coreBit);

   if (isPausing == 0) {
      // This is the first core to hit a breakpoint
      sPauseInitiatorCoreId = coreId;

      // Signal the rest of the cores to stop
      for (auto i = 0; i < 3; ++i) {
         cpu::interrupt(i, cpu::DBGBREAK_INTERRUPT);
      }
   }

   if ((isPausing | coreBit) == (1 | 2 | 4)) {
      // This was the last core to join.
      sIsPaused.store(true);
      sIsPausing.store(0);
      sIsResuming.store(0);
   }

   // Spin around the release condition while we are paused
   while (sIsPausing.load() || sIsPaused.load()) {
      sPauseReleaseCond.wait(lock);
   }

   // Clear any additional DbgBreaks that occured
   cpu::this_core::clearInterrupt(cpu::DBGBREAK_INTERRUPT);

   // Everyone needs to leave at once in case new breakpoints occur.
   if ((sIsResuming.fetch_or(coreBit) | coreBit) == (1 | 2 | 4)) {
      sPauseReleaseCond.notify_all();
   } else {
      while ((sIsResuming.load() | coreBit) != (1 | 2 | 4)) {
         sPauseReleaseCond.wait(lock);
      }
   }
}

} // namespace debugger
