// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Logic + calling convention derived from the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI (disasm at 0x6A60A0), cross-checked
//   against YRpp SidebarClass.h (consult-only; reconfirmed from disasm).
#include "sidebar_class_repaint_methods.h"

// FUNCTION: GAMEMD 0x6A60A0  SidebarClass::RepaintSidebar (__thiscall)
//   this -> ECX,  tab -> [ESP+4]
//   if (tab == ActiveTabIndex) { SidebarNeedsRedraw = 1;
//     Tabs[tab].NeedsRedraw = 1; Instance->FlagToRedraw(0); }
void SidebarClass::RepaintSidebar(int tab)
{
    if (tab == this->ActiveTabIndex) {
        this->SidebarNeedsRedraw = 1;
        this->Tabs[tab].NeedsRedraw = 1;
        SidebarClass_Instance.FlagToRedraw(0);
    }
}
