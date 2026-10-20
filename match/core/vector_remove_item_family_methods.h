// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x63DFD0 and its four duplicates: remove an element by
//   value. The element's index comes from the vector's own virtual lookup at
//   vtable slot +0x10, and the tail shift is the same one the by-index
//   removal family uses (see vector_remove_index_family_methods.h). Members:
//   the items pointer at +4 and the count at +0x10. All five are
//   byte-identical.
#ifndef GG_MATCH_CORE_VECTOR_REMOVE_ITEM_FAMILY_METHODS_H
#define GG_MATCH_CORE_VECTOR_REMOVE_ITEM_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_0063DFD0;

struct ItemVector_0063DFD0
{
    Vtbl_0063DFD0* Vtbl;    // +0x0000
    int*           Items;   // +0x0004
    char           _pad008[0x10 - 0x08];
    int            Count;   // +0x0010
};
GG_STATIC_ASSERT(offsetof(ItemVector_0063DFD0, Items) == 0x4);
GG_STATIC_ASSERT(offsetof(ItemVector_0063DFD0, Count) == 0x10);

typedef int (ItemVector_0063DFD0::*Fn10_0063DFD0)(int item);

struct Vtbl_0063DFD0
{
    char          _pad000[0x10];  // +0x0000
    Fn10_0063DFD0 IndexOf;        // +0x0010
};
GG_STATIC_ASSERT(offsetof(Vtbl_0063DFD0, IndexOf) == 0x10);

// FUNCTION: GAMEMD 0x0063DFD0
bool __fastcall FUN_000063DFD0(ItemVector_0063DFD0* self, int, int item);
// FUNCTION: GAMEMD 0x0063E5D0
bool __fastcall FUN_000063E5D0(ItemVector_0063DFD0* self, int, int item);
// FUNCTION: GAMEMD 0x0063E900
bool __fastcall FUN_000063E900(ItemVector_0063DFD0* self, int, int item);
// FUNCTION: GAMEMD 0x0063EBD0
bool __fastcall FUN_000063EBD0(ItemVector_0063DFD0* self, int, int item);
// FUNCTION: GAMEMD 0x006CE2D0
bool __fastcall FUN_00006CE2D0(ItemVector_0063DFD0* self, int, int item);

#endif  // GG_MATCH_CORE_VECTOR_REMOVE_ITEM_FAMILY_METHODS_H
