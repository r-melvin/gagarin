// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets and globals read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x4010A0 / 0x401170 / 0x406620 /
//   0x407000. None is bound by YRpp.
//
// Flag tests, a flag clear and a clamped setter.
#ifndef GG_MATCH_CORE_FLAG_AND_CLAMP_METHODS_H
#define GG_MATCH_CORE_FLAG_AND_CLAMP_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x87E728
extern void* DAT_0087E728;

// Three sub-objects at +0x00, +0x28 and +0x50, each opening with an int flag
// word. Bit 1 (mask 2) is the one both methods here care about.
//
// The flags are ints, not bytes, even though 0x4010A0 tests them with
// `TEST byte ptr`: 0x401170 reads and writes the full dword at the same
// offsets. VC6 narrows a `& 2` test to the low byte on its own.
struct Obj_00401000
{
    int  unknown_00;             // +0x0000
    char _pad04[0x28 - 0x04];
    int  unknown_28;             // +0x0028
    char _pad2C[0x50 - 0x2C];
    int  unknown_50;             // +0x0050

    // FUNCTION: GAMEMD 0x4010A0
    int FUN_004010A0() const;
    // FUNCTION: GAMEMD 0x401170
    void FUN_00401170();
};
GG_STATIC_ASSERT(offsetof(Obj_00401000, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(Obj_00401000, unknown_50) == 0x50);

struct Obj_00406600
{
    char _pad00[0x68];
    int  unknown_68;   // +0x0068
};
GG_STATIC_ASSERT(offsetof(Obj_00406600, unknown_68) == 0x68);

// FUNCTION: GAMEMD 0x406620 — value arrives in EDX, so __fastcall, not __thiscall.
void FUN_00406620(Obj_00406600* obj, int value);

// FUNCTION: GAMEMD 0x407000
bool __cdecl FUN_00407000();

#endif  // GG_MATCH_CORE_FLAG_AND_CLAMP_METHODS_H
