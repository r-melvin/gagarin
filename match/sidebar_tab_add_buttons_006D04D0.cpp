// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes read from retail gamemd.exe v1.001 at 0x6D04D0.
//   PLACEMENT LEAD (inference): its caller 0x6D0680 (match/sidebar_tab_class.cpp) reaches it by a real
//   CALL. At /Ob2 cl inlines any body it can see, so the retail call implies the body was compiled in a
//   different original object than that caller. This file is that separate object; the original file name
//   is not known and is not claimed.
#include "sidebar_class_layout.h"

// GLOBAL: GAMEMD 0xB0C1C0 -- the command-bar buttons.
extern SidebarButton CommandButtons_00B0C1C0[25];

// FUNCTION: GAMEMD 0x6D04D0
// Add every command-bar button to the screen.
void TabClass::FUN_006D04D0()
{
    for (int index = 0; index < 25; ++index) {
        vf_13(&CommandButtons_00B0C1C0[index]);
    }
}

