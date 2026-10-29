// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets/globals derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x74D760-0x74D7BB), cross-
//   checked against YRpp (
//   every offset reconfirmed numerically here).
//
// VeinholeMonsterClass::DeleteAll: walks the global VeinholeMonster registry
// top-down, deletes each live monster through its virtual destructor, then tears
// the backing DynamicVectorClass down to an empty/unallocated state.
#ifndef GG_MATCH_COMBAT_VEINHOLE_MONSTER_DELETEALL_H
#define GG_MATCH_COMBAT_VEINHOLE_MONSTER_DELETEALL_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The global vein-monster registry @0x00B1D290:
//   DynamicVectorClass<VeinholeMonsterClass*>.
// DeleteAll touches Items @+0x04 (0xB1D294), Capacity @+0x08 (0xB1D298),
// IsAllocated byte @+0x0D (0xB1D29D) and Count @+0x10 (0xB1D2A0). It deliberately
// leaves IsInitialized @+0x0C (0xB1D29C) untouched, so the two bytes in that cell
// are modelled separately (the committed vector_class.h folds them into one int).
struct VeinholeArrayClass
{
    void* _vtable;            // +0x00  (vptr slot)
    void* Items;              // +0x04  (VeinholeMonsterClass** base)
    int   Capacity;           // +0x08
    bool  IsInitialized;      // +0x0C
    bool  IsAllocated;        // +0x0D
    int   Count;              // +0x10
    int   CapacityIncrement;  // +0x14
};

GG_STATIC_ASSERT(offsetof(VeinholeArrayClass, Items)       == 0x04);
GG_STATIC_ASSERT(offsetof(VeinholeArrayClass, Capacity)    == 0x08);
GG_STATIC_ASSERT(offsetof(VeinholeArrayClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(VeinholeArrayClass, Count)       == 0x10);
GG_STATIC_ASSERT(sizeof(VeinholeArrayClass)                == 0x18);

extern VeinholeArrayClass VeinholeArray;  // @0x00B1D290

// YR game-heap deallocator @0x007C8B3D (__cdecl, single pointer arg; forwards to
// the pool free at 0x007C93E8). Declared without a body so cl emits a relocatable
// CALL the differ normalises.
void __cdecl GameDeallocate(void* ptr);

// VeinholeMonsterClass : ObjectClass (COM-rooted). DeleteAll only needs the
// destructor's vtable slot so `delete p` issues the deleting-destructor call.
// The primary vtable (0x007F66A8) places ~VeinholeMonsterClass at offset 0x20
// (index 8): GetClassID@0x0C, Save@0x18, dtor-thunk@0x20 (0x00410470). Eight
// preceding virtual slots reproduce that index; the class is never instantiated
// here, so no vtable/bodies are emitted.
#include "../_layout/veinhole_monster_class.h"

// GLOBAL: GAMEMD 0x00B1D2F0 — the lazily allocated per-cell vein growth table.
// DeleteVeinholeGrowthData frees it through the same game-heap deallocator and
// nulls the pointer so the next request reallocates.
extern void* VeinholeGrowthData;

#endif  // GG_MATCH_COMBAT_VEINHOLE_MONSTER_DELETEALL_H
