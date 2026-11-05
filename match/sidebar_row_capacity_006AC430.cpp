// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes read from retail gamemd.exe v1.001 at 0x6AC430.
//   PLACEMENT LEAD (inference): its caller 0x6A6300 in Sidebar.cpp reaches it by a real CALL with ECX
//   set to the map singleton. At /Ob2 cl inlines any body it can see, so the retail call implies the body
//   was compiled in a different original object than that caller. This file is that separate object; the
//   original file name is not known and is not claimed. The row itself is unchanged by the move (a partial,
//   47.6% before and after).
#include "FUNCTION.H"
#include "sidebar_class_layout.h"

// Number of cameo rows that fit in the sidebar (expanded inline).
static inline int SidebarRowCount()
{
    int margin = 0x1A;
    if (DAT_00A8B230->unknown_34B8) {
        margin = 0x12;
    }
    return (DAT_00886F9C - StripY_00B0B4F8 - margin + DAT_00886F94 - 7) / 50;
}

// TUSPLIT: GAMEMD 0x6A6300 same-file 63.2% separate 100.0%
// FUNCTION: GAMEMD 0x6AC430
// PARTIAL: 47.6% -- same instructions; retail loads the scenario pointer into EAX and the flag into ECX
// (the sidebar margin flag class), ours rotates the three registers.
int __cdecl FUN_006AC430()
{
    return SidebarRowCount() * 2;
}
