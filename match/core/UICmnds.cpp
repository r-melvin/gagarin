// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit UICmnds.cpp. The name is the source-file string at 0x845598
//   in retail gamemd.exe v1.001, passed by the assert at 0x731b01 inside this object's
//   code range (0x730780-0x73442f). Functions are in ascending retail address order.
//
//   cross-checked against YRpp. Each function is
//
// reccmp annotations:

#include "techno_class_owner_methods.h"

// Sidebar "tab object" globals @ 0x00B0FE5C / 0x00B0FE60. Declared-only so cl
// emits reloc-normalised absolute stores/compares.
extern TechnoClass* SidebarTabObjectA;   // 0x00B0FE5C
extern TechnoClass* SidebarTabObjectB;   // 0x00B0FE60

#include "trivial_tu256_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F5C08
extern const double DAT_007F5C08;
// GLOBAL: GAMEMD 0xB0FDF8
extern double DAT_00B0FDF8;
// GLOBAL: GAMEMD 0xB0FE30
extern double DAT_00B0FE30;
// GLOBAL: GAMEMD 0xB0FE38
extern int DAT_00B0FE38;
// GLOBAL: GAMEMD 0xB0FE3C
extern int DAT_00B0FE3C;
// GLOBAL: GAMEMD 0xB0FE40
extern int DAT_00B0FE40;
// GLOBAL: GAMEMD 0xB0FE48
extern double DAT_00B0FE48;

// FUNCTION: GAMEMD 0x7307B0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_007307B0()
{
    DAT_00B0FE48 = DAT_00B0FDF8 / DAT_007F5C08;
}

// FUNCTION: GAMEMD 0x7307D0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_007307D0()
{
    DAT_00B0FE30 = DAT_007E1718 / DAT_00B0FE48;
}

// FUNCTION: GAMEMD 0x730950
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_00730950()
{
    DAT_00B0FE40 = 0;
    DAT_00B0FE38 = 0x80;
    DAT_00B0FE3C = 0x80;
}

// FUNCTION: GAMEMD 0x730AD0
// Returns a constant.
int __cdecl FUN_00730AD0()
{
    return 0x4046;
}

// FUNCTION: GAMEMD 0x730AE0
// Returns a constant.
int __cdecl FUN_00730AE0()
{
    return 0xF0;
}

// FUNCTION: GAMEMD 0x731A30
// Branching.
void FUN_00731A30(int a1, int a2)
{
    if (DAT_00A8B538 == 0)
    {
        FUN_004AC960(DAT_0087F7E8, a2, -1);
    }
}

// FUNCTION: GAMEMD 0x731A90
// Tail-forwards to another function.
void __cdecl FUN_00731A90()
{
    FUN_00637AA0();
}

// FUNCTION: GAMEMD 0x731BE0
// Stores to a global.
void __cdecl FUN_00731BE0()
{
    DAT_00B0FE58 = 0;
}

// FUNCTION: GAMEMD 0x731CF0
// Stores to a global.
void __cdecl FUN_00731CF0()
{
    DAT_00B0FE58 = 0;
}

// FUNCTION: GAMEMD 0x732CA0
// Branching.
void __cdecl FUN_00732CA0()
{
    if (DAT_00B0FE65 == 0)
    {
        unsigned char t1 = DAT_00B0FE65;
        DAT_00B0FE65 = 1;
        int c0 = timeGetTime();
        DAT_00B0FE68 = c0;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x734270  (__thiscall)
// Removes this object from the two sidebar tab-object slots. A null this clears
// both slots; otherwise only the slot(s) that point at this object are cleared.
void TechnoClass::ClearSidebarTabObject()
{
    if (this == NULL) {
        SidebarTabObjectA = NULL;
        SidebarTabObjectB = NULL;
        return;
    }
    if (this == SidebarTabObjectA) {
        SidebarTabObjectA = NULL;
        return;
    }
    if (this == SidebarTabObjectB) {
        SidebarTabObjectB = NULL;
        return;
    }
}
