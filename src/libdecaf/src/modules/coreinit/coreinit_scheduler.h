#pragma once
#include "coreinit_thread.h"
#include <cstdint>

namespace coreinit
{

struct OSThread;
struct OSThreadQueue;

namespace internal
{

void
startDefaultCoreThreads();

OSThread *
getCoreRunningThread(uint32_t coreId);

uint64_t
getCoreThreadRunningTime(uint32_t coreId);

void
pauseCoreTime(bool isPaused);

OSThread *
getFirstActiveThread();

OSThread *
getCurrentThread();

void
lockScheduler();

bool
isSchedulerLocked();

void
unlockScheduler();

bool
isSchedulerEnabled();

void
enableScheduler();

void
disableScheduler();

void
markThreadActiveNoLock(OSThread *thread);

void
markThreadInactiveNoLock(OSThread *thread);

bool
isThreadActiveNoLock(OSThread *thread);

void
setThreadAffinityNoLock(OSThread *thread,
                        uint32_t affinity);

int32_t
checkActiveThreadsNoLock();

void
checkRunningThreadNoLock(bool yielding);

void
rescheduleNoLock(uint32_t core);

void
rescheduleSelfNoLock();

void
rescheduleOtherCoreNoLock();

void
rescheduleAllCoreNoLock();

int32_t
resumeThreadNoLock(OSThread *thread,
                   int32_t counter);

bool
setThreadRunQuantumNoLock(OSThread *thread,
                          OSTime ticks);

void
sleepThreadNoLock(OSThreadQueue *queue);

void
sleepThreadNoLock(OSThreadSimpleQueue *queue);

void
suspendThreadNoLock(OSThread *thread);

void
testThreadCancelNoLock();

void
wakeupOneThreadNoLock(OSThread *thread);

void
wakeupThreadNoLock(OSThreadQueue *queue);

void
wakeupThreadNoLock(OSThreadSimpleQueue *queue);

void
wakeupThreadWaitForSuspensionNoLock(OSThreadQueue *queue,
                                    int32_t suspendResult);

int32_t
calculateThreadPriorityNoLock(OSThread *thread);

OSThread *
setThreadActualPriorityNoLock(OSThread *thread,
                              int32_t priority);

void
updateThreadPriorityNoLock(OSThread *thread);

void
promoteThreadPriorityNoLock(OSThread *thread,
                            int32_t priority);

} // namespace internal

} // namespace coreinit


