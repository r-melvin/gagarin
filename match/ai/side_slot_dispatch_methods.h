// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every offset below is read numerically off the user's retail gamemd.exe
//   v1.001 through the local Ghidra CLI at 0x451750. The three base constants
//   0xF4C / 0xF5C / 0xF6C differ by 0x10, and the index is scaled by
//   (i*16 + i)*4 == i*0x44, so the owner holds an array of 0x44-byte records
//   at +0xF4C with byte fields at +0x00, +0x10 and +0x20.
#ifndef GG_MATCH_AI_SIDE_SLOT_DISPATCH_METHODS_H
#define GG_MATCH_AI_SIDE_SLOT_DISPATCH_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// One 0x44-byte record of the owner's per-index table.
struct Ent_00451750
{
    char At_00;               // +0x00
    char _pad0001[0xF];       // +0x01
    char At_10;               // +0x10
    char _pad0011[0xF];       // +0x11
    char At_20;               // +0x20
    char _pad0021[0x23];      // +0x21
};
GG_STATIC_ASSERT(offsetof(Ent_00451750, At_10) == 0x10);
GG_STATIC_ASSERT(offsetof(Ent_00451750, At_20) == 0x20);
GG_STATIC_ASSERT(sizeof(Ent_00451750) == 0x44);

struct Owner_00451750
{
    char _pad0000[0xF4C];     // +0x0000
    // Element count is not recoverable from this function; only the stride and
    // the base are. One element is declared and indexed past — the generated
    // address arithmetic is what has to match.
    Ent_00451750 Slots[1];    // +0x0F4C
};
GG_STATIC_ASSERT(offsetof(Owner_00451750, Slots) == 0xF4C);

struct Obj_00451750
{
    char _pad0000[0x520];     // +0x0000
    Owner_00451750* Owner;    // +0x0520

    // FUNCTION: GAMEMD 0x451750
    void FUN_00451750(int index, bool a, bool b, int extra);
    // FUNCTION: GAMEMD 0x451890
    void FUN_00451890(char* slot, int index, bool a, bool b, int extra);
};
GG_STATIC_ASSERT(offsetof(Obj_00451750, Owner) == 0x520);

#endif  // GG_MATCH_AI_SIDE_SLOT_DISPATCH_METHODS_H
