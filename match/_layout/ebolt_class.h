// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail RTTI names the class (".?AVEBolt@@", seen as the element type of
//   DynamicVectorClass<EBolt*> at 0x7E868C); EBolt itself has no vtable.
//   Size 0x30: the one allocation site (0x6FD460: operator new(0x30), then the
//   constructor 0x4C1E10). Constructor stores: Point1 and Point2 zeroed, +0x18
//   0, +0x1C 0, +0x20 0, +0x24 0, +0x28 0x10000, byte +0x2C 0.
//   Fire (0x4C2A60) writes the colour at +0x18 and a Randomizer draw at +0x1C;
//   SetOwner (0x4C2BD0) latches +0x20/+0x24 for a live, on-map UnitClass; the
//   owner's UnitClass+0x6DC points back at the bolt and is cleared on detach
//   (0x4C2C10, 0x4C29E0).
#ifndef GG_MATCH_LAYOUT_EBOLT_CLASS_H
#define GG_MATCH_LAYOUT_EBOLT_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "coord_struct.h"
#include "../core/vector_class.h"

class UnitClass;

class EBolt
{
public:
    // FUNCTION: GAMEMD 0x4C1E10
    EBolt();
    // FUNCTION: GAMEMD 0x4C2A60
    void Fire(CoordStruct from, CoordStruct to, int color);
    // FUNCTION: GAMEMD 0x4C2B40
    CoordStruct* GetOwnerCoords(CoordStruct* out);
    // FUNCTION: GAMEMD 0x4C2BD0
    void SetOwner(UnitClass* pOwner, int idxWeapon);
    // FUNCTION: GAMEMD 0x4C2C10 (a second copy of the same body sits at 0x4C1E50)
    void DetachOwner();

    CoordStruct Point1;     // +0x00
    CoordStruct Point2;     // +0x0C
    int         Color;      // +0x18  Fire() argument
    int         Phase;      // +0x1C  Fire(): Randomizer 0..0x100
    UnitClass*  Owner;      // +0x20  cleared when the bolt is detached
    int         WeaponSlot; // +0x24  passed to the owner's slot-44 coordinate query
    int         At_28;      // +0x28  constructor stores 0x10000
    bool        At_2C;      // +0x2C  constructor stores 0
    char        _pad2D[3];  // +0x2D
};
GG_STATIC_ASSERT(offsetof(EBolt, Point1) == 0x00);
GG_STATIC_ASSERT(offsetof(EBolt, Point2) == 0x0C);
GG_STATIC_ASSERT(offsetof(EBolt, Color) == 0x18);
GG_STATIC_ASSERT(offsetof(EBolt, Phase) == 0x1C);
GG_STATIC_ASSERT(offsetof(EBolt, Owner) == 0x20);
GG_STATIC_ASSERT(offsetof(EBolt, WeaponSlot) == 0x24);
GG_STATIC_ASSERT(offsetof(EBolt, At_28) == 0x28);
GG_STATIC_ASSERT(offsetof(EBolt, At_2C) == 0x2C);
GG_STATIC_ASSERT(sizeof(EBolt) == 0x30);

// GLOBAL: GAMEMD 0x8A0E88 -- the live-bolt list (EBolt::Array).
extern DynamicVectorClass<EBolt*> DAT_008A0E88;
// GLOBAL: GAMEMD 0x8A0E50 -- the zero coordinate (header_init_004c1b80.cpp).
struct HeaderCoordInit;
extern HeaderCoordInit DAT_008A0E50;

#endif  // GG_MATCH_LAYOUT_EBOLT_CLASS_H
