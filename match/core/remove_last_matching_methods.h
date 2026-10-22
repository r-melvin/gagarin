// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets and the erase shape read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x471F90.
//
// Drop the array's *last* element if its first word is the key given, freeing
// it and closing the gap. Only the last slot is examined - retail computes
// `Count - 1` once and never advances - so this is a pop-if-match rather than a
// search.
//
// The shift is DynamicVectorClass::RemoveItem inlined: decrement the count,
// then copy each following element down one. Retail's `INC EAX` ahead of the
// pair of accesses is VC6's own strength reduction of `Items[j] = Items[j+1]`,
// so the source is written that way round rather than transcribing the
// optimised form.
#ifndef GG_MATCH_CORE_REMOVE_LAST_MATCHING_METHODS_H
#define GG_MATCH_CORE_REMOVE_LAST_MATCHING_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void __cdecl FUN_007C8B3D(void* block);

struct Obj_00471F90
{
    char   _pad000[0x28];
    void** Items;   // +0x0028
    char   _pad02C[0x34 - 0x2C];
    int    Count;   // +0x0034

    // FUNCTION: GAMEMD 0x471F90
    bool FUN_00471F90(void* key);
};
GG_STATIC_ASSERT(offsetof(Obj_00471F90, Items) == 0x28);
GG_STATIC_ASSERT(offsetof(Obj_00471F90, Count) == 0x34);

#endif  // GG_MATCH_CORE_REMOVE_LAST_MATCHING_METHODS_H
