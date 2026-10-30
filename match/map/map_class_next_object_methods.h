// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, globals and slots read off the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI at 0x4AA2B0: the three-entry layer order table walked
//   from 0x820030 to 0x82003C, the 0x18-byte layer records at 0x8A0360 (Items
//   at +0x04 = 0x8A0364, Count at +0x10 = 0x8A0370), the object's flag byte at
//   +0x14 (bit 0), and the two zero-argument bool virtuals at +0x64 and
//   +0x13C. YRpp names the function
//   MapClass::NextObject and the layer array ObjectsInLayers; every offset is
//   reconfirmed here.
#ifndef GG_MATCH_MAP_MAP_CLASS_NEXT_OBJECT_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_NEXT_OBJECT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Vtbl_004AA2B0;

// An object in a layer. Bit 0 of the flag byte at +0x14 says it is a
// TechnoClass, which is what unlocks the second virtual.
struct Obj_004AA2B0
{
    Vtbl_004AA2B0* Vptr;     // +0x0000
    char _pad0004[0x10];     // +0x0004
    char AbstractFlags;      // +0x0014
};
GG_STATIC_ASSERT(offsetof(Obj_004AA2B0, AbstractFlags) == 0x14);

typedef bool (Obj_004AA2B0::*Fn64_004AA2B0)();
typedef bool (Obj_004AA2B0::*Fn13C_004AA2B0)();

struct Vtbl_004AA2B0
{
    char _pad000[0x64];            // +0x0000
    Fn64_004AA2B0 At_64;           // +0x0064  object-level selectable test
    char _pad068[0x13C - 0x68];    // +0x0068
    Fn13C_004AA2B0 At_13C;         // +0x013C  techno-level selectable test
};
GG_STATIC_ASSERT(offsetof(Vtbl_004AA2B0, At_64) == 0x64);
GG_STATIC_ASSERT(offsetof(Vtbl_004AA2B0, At_13C) == 0x13C);

// One draw layer: a DynamicVectorClass<ObjectClass*> head.
struct Layer_004AA2B0
{
    void* Vptr;                // +0x0000
    Obj_004AA2B0** Items;      // +0x0004
    char _pad0008[0x08];       // +0x0008
    int Count;                 // +0x0010
    int _pad0014;              // +0x0014
};
GG_STATIC_ASSERT(offsetof(Layer_004AA2B0, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(Layer_004AA2B0, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(Layer_004AA2B0) == 0x18);

// GLOBAL: GAMEMD 0x8A0360 — the draw-layer array (YRpp ObjectsInLayers).
extern Layer_004AA2B0 DAT_008A0360[];

// GLOBAL: GAMEMD 0x820030 — the three layer indices NextObject walks, in order.
extern int DAT_00820030[3];

// GLOBAL: GAMEMD 0x82003C — the three layer indices PrevObject walks, in order.
extern int DAT_0082003C[3];

struct Map_004AA2B0
{
    // FUNCTION: GAMEMD 0x4AA380 — the object before the one given (`this` never read).
    Obj_004AA2B0* PrevObject(Obj_004AA2B0* current);
    // FUNCTION: GAMEMD 0x4AA2B0 — MapClass::NextObject (`this` never read).
    Obj_004AA2B0* NextObject(Obj_004AA2B0* current);
};

#endif  // GG_MATCH_MAP_MAP_CLASS_NEXT_OBJECT_METHODS_H
