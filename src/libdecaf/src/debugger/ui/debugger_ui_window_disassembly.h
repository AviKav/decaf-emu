#pragma once
#include "debugger_ui_addrscroller.h"
#include "debugger_ui_window.h"

#include <array>
#include <libcpu/state.h>

namespace debugger
{

namespace ui
{

class DisassemblyWindow : public Window
{
public:
   DisassemblyWindow(const std::string &name);
   virtual ~DisassemblyWindow() = default;

   virtual void
   draw();

   void
   gotoAddress(uint32_t address);

private:
   AddressScroller mAddressScroller;
   int64_t mSelectedAddr = -1;
   std::array<char, 9> mAddressInput = { 0 };
};

} // namespace ui

} // namespace debugger
