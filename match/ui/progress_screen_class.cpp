// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x642B10/0x642B20 (Ghidra
//   disasm). Names cross-checked against YRpp (consult-
//   only, no LICENSE; the +0x80 offset reconfirmed against the user's binary).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x642A60   ProgressScreenClass::Setup     (__thiscall)
//   FUNCTION: GAMEMD 0x642B10   ProgressScreenClass::SetSide   (__thiscall)
//   FUNCTION: GAMEMD 0x642B20   ProgressScreenClass::GetSide   (__thiscall)

#include "progress_screen_class.h"
#include "../renderer/surface_class.h"

// GLOBAL: GAMEMD 0x88730C -- the primary surface.
extern Surface* DAT_0088730C;

// FUNCTION: GAMEMD 0x642A60  (__thiscall, RET 0x10)
// Start a screen: store the two leading words, clear the slot pairs, raise the flag, and
// either keep the given value or blank the primary surface; reset the progress word.
void ProgressScreenClass::Setup(int first, int second, char slotCount, int unknown)
{
    unknown_48 = first;
    unknown_4C = second;
    unknown_61 = slotCount;
    for (int i = 0; i < unknown_61; i++) {
        int* slot = &Table08[i * 2];
        slot[0] = 0;
        slot[1] = 0;
    }
    unknown_60 = true;
    if (unknown != 0) {
        unknown_64 = unknown;
    } else {
        DAT_0088730C->Fill(0);
    }
    unknown_50 = 0;
    unknown_7C = -1;
}

// FUNCTION: GAMEMD 0x642B10  (__thiscall)
// MOV EAX,[ESP+4]; MOV [ECX+0x80],EAX; RET 4
void ProgressScreenClass::SetSide(int idx)
{
    this->PlayerSide = idx;
}

// FUNCTION: GAMEMD 0x642B20  (__thiscall)
// MOV EAX,[ECX+0x80]; RET
int ProgressScreenClass::GetSide()
{
    return this->PlayerSide;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x88730C
Surface* DAT_0088730C;
// END defined globals
