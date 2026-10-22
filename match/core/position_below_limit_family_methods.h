// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x4F28B0 and its six duplicates: `MOV EAX,[ECX+4];
//   MOV ECX,[ECX+8]; CMP ECX,[EAX+0x10]; SBB EAX,EAX; NEG EAX; RET`. The
//   object holds a pointer to its owner at +4 and its own position at +8,
//   and the answer is whether that position is still below the owner's limit
//   at +0x10. The borrow-and-negate pair is how the period compiler spells an
//   unsigned comparison returned as a bool. All seven are byte-identical.
#ifndef GG_MATCH_CORE_POSITION_BELOW_LIMIT_FAMILY_METHODS_H
#define GG_MATCH_CORE_POSITION_BELOW_LIMIT_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Owner_004F28B0
{
    char         _pad000[0x10];  // +0x0000
    unsigned int Limit;          // +0x0010
};
GG_STATIC_ASSERT(offsetof(Owner_004F28B0, Limit) == 0x10);

struct Cursor_004F28B0
{
    char*           Vptr;      // +0x0000
    Owner_004F28B0* Owner;     // +0x0004
    unsigned int    Position;  // +0x0008
};
GG_STATIC_ASSERT(offsetof(Cursor_004F28B0, Owner)    == 0x4);
GG_STATIC_ASSERT(offsetof(Cursor_004F28B0, Position) == 0x8);

// FUNCTION: GAMEMD 0x004F28B0
bool FUN_004F28B0(Cursor_004F28B0* self);
// FUNCTION: GAMEMD 0x004F3FC0
bool FUN_004F3FC0(Cursor_004F28B0* self);
// FUNCTION: GAMEMD 0x00765700
bool FUN_00765700(Cursor_004F28B0* self);
// FUNCTION: GAMEMD 0x00766920
bool FUN_00766920(Cursor_004F28B0* self);
// FUNCTION: GAMEMD 0x0076F0B0
bool FUN_0076F0B0(Cursor_004F28B0* self);
// FUNCTION: GAMEMD 0x0076F0E0
bool FUN_0076F0E0(Cursor_004F28B0* self);
// FUNCTION: GAMEMD 0x0076F0F0
bool FUN_0076F0F0(Cursor_004F28B0* self);

#endif  // GG_MATCH_CORE_POSITION_BELOW_LIMIT_FAMILY_METHODS_H
