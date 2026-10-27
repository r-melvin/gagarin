// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: ObjectTypeClass ctor FUN_0x0058B8F0 member-access sites
//   cross-checked vs YRpp ColorStruct/IndexClass/AbilitiesStruct. P2 leaf
//   components reused by ObjectTypeClass (RadialColor, MainVoxel, voxel caches,
//   Veteran/EliteAbilities).
//
// Component struct sizes proven by the ctor member-access sites:
//   ColorStruct = 3, VoxelStruct = 8, IndexClass = 0x14, AbilitiesStruct = 0x12.
#ifndef GG_MATCH_LAYOUT_COMPONENTS_H
#define GG_MATCH_LAYOUT_COMPONENTS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "color_struct.h"

// VoxelStruct — a voxel model + its HVA animation (two 32-bit pointers).
// Pointer members modelled as real pointers (decomp shows undefined4 truncation).
struct AbstractNoInit;
struct VoxelStruct
{
    // ObjectType no-init5F7340/56: default array entries are two zero pointers;
    // its three individual voxel members use the explicit no-init path.
    VoxelStruct() : unknown_00(0), HVAData(0) {}
    VoxelStruct(const AbstractNoInit&) {}
    void* unknown_00;   // +0x00  (MotLib / VoxLib model ptr)
    void* HVAData;     // +0x04  (HVA animation ptr)
};

GG_STATIC_ASSERT(offsetof(VoxelStruct, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(VoxelStruct, HVAData)   == 0x04);
GG_STATIC_ASSERT(sizeof(VoxelStruct)              == 8);

// AbilitiesStruct — packed ability flags block (size = 0x12). The internal
// field breakdown is not member-resolved in the oracle; modelled as an
// exact-size byte block so downstream offsets stay byte-exact.
struct AbilitiesStruct
{
    unsigned char _raw[0x12];   // +0x00..0x11

    // Declaration: GAMEMD 0x7179D0; returns this 0x12-byte block by value.
    AbilitiesStruct FUN_007179D0(const AbilitiesStruct& source);
};

GG_STATIC_ASSERT(offsetof(AbilitiesStruct, _raw) == 0x00);
GG_STATIC_ASSERT(sizeof(AbilitiesStruct) == 0x12);

// IndexClass — key->index hash/lookup object (size = 0x14, independent
// of the Key/Value template; the NodeElement sizing affects only the heap
// table, not the object). Used by ObjectTypeClass voxel caches. Pointer members
// modelled as real pointers (decomp shows truncation at IndexTable/Archive).
struct IndexClass
{
    // ObjectType no-init5F7361..5F73D3: four empty cache records.
    IndexClass() : IndexTable(0), IndexCount(0), IndexSize(0), IsSorted(0), Archive(0) {}
    void*         IndexTable;   // +0x00  (NodeElement array on the heap)
    int           IndexCount;   // +0x04
    int           IndexSize;    // +0x08
    unsigned char IsSorted;     // +0x0C  (bool)
    unsigned char _pad_0D[3];   // +0x0D
    void*         Archive;      // +0x10  (last-found cache slot)
};

GG_STATIC_ASSERT(offsetof(IndexClass, IndexTable) == 0x00);
GG_STATIC_ASSERT(offsetof(IndexClass, IndexCount) == 0x04);
GG_STATIC_ASSERT(offsetof(IndexClass, IndexSize)  == 0x08);
GG_STATIC_ASSERT(offsetof(IndexClass, IsSorted)   == 0x0C);
GG_STATIC_ASSERT(offsetof(IndexClass, Archive)    == 0x10);
GG_STATIC_ASSERT(sizeof(IndexClass)               == 0x14);

#endif  // GG_MATCH_LAYOUT_COMPONENTS_H
