// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x7180A0: ask the object through vtable slot +0x10, with
//   `this` pushed rather than passed in the register, which is the COM
//   __stdcall form; on a yes take the three coordinate words the object
//   carries at +0x18, +0x1C and +0x20, otherwise take them from +0x9C of the
//   owner it holds at +0x08. The result goes through a plain out pointer, not
//   a hidden return buffer, which the untouched return register at exit
//   proves.
#ifndef GG_MATCH_MOVEMENT_WAYPOINT_QUEUE_POSITION_METHODS_H
#define GG_MATCH_MOVEMENT_WAYPOINT_QUEUE_POSITION_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Coord_007180A0
{
    int X;   // +0x0000
    int Y;   // +0x0004
    int Z;   // +0x0008
};
GG_STATIC_ASSERT(sizeof(Coord_007180A0) == 0xC);

struct Owner_007180A0
{
    char             _pad000[0x9C];  // +0x0000
    Coord_007180A0   Position;       // +0x009C
};
GG_STATIC_ASSERT(offsetof(Owner_007180A0, Position) == 0x9C);

struct Source_007180A0;

struct Vtbl_007180A0
{
    char _pad000[0x10];                                    // +0x0000
    bool (__stdcall* HasOwnPosition)(Source_007180A0* self); // +0x0010
};
GG_STATIC_ASSERT(offsetof(Vtbl_007180A0, HasOwnPosition) == 0x10);

struct Source_007180A0
{
    Vtbl_007180A0*   Vtbl;           // +0x0000
    char             _pad004[0x4];   // +0x0004
    Owner_007180A0*  Owner;          // +0x0008
    char             _pad00C[0xC];   // +0x000C
    Coord_007180A0   Position;       // +0x0018
};
GG_STATIC_ASSERT(offsetof(Source_007180A0, Owner)    == 0x8);
GG_STATIC_ASSERT(offsetof(Source_007180A0, Position) == 0x18);

// FUNCTION: GAMEMD 0x7180A0
void __stdcall FUN_007180A0(Source_007180A0* self, Coord_007180A0* out);

#endif  // GG_MATCH_MOVEMENT_WAYPOINT_QUEUE_POSITION_METHODS_H
