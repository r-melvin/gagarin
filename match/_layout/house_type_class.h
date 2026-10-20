// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: ctor FUN_0x005113F0 (docs/decomp_spec/type_hierarchy_layout.md),
//   parent AbstractTypeClass ctor 0x00410800; member writes cross-checked vs
//   YRpp HouseTypeClass.h. Pad anchors align_B1@0xB1, align_C4@0xC4,
//   padding_1A9@0x1A9 confirmed; ctor writes ArrayIndex@0xB4, FirepowerMult@0xC8,
//   VeteranInfantry@0x14C. P2 layout-spine.
//
// HouseTypeClass — the [Countries]/side "blueprint" type (ParentCountry,
// per-category combat/cost/speed multipliers, veteran-unit lists, multiplayer
// flags). Derives AbstractTypeClass (the AbstractClass COM spine + ID/Name
// strings) at offset 0 and adds the country fields from 0x98.
#ifndef GG_MATCH_LAYOUT_HOUSE_TYPE_CLASS_H
#define GG_MATCH_LAYOUT_HOUSE_TYPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_type_class.h"

// TypeListData — embedded TypeList<*>(0x1C) value object. The element pointer
// type (InfantryTypeClass*/UnitTypeClass*/AircraftTypeClass*) does not change
// the object size; the inner storage pointers are decomp truncations. Modelled
// as an exact-size byte block so downstream offsets stay byte-exact.
struct TypeListData
{
    unsigned char _raw[0x1C];   // +0x00..0x1B
};

GG_STATIC_ASSERT(sizeof(TypeListData) == 0x1C);

// HouseTypeClass  (0x98..0x1AF, sizeof = 0x1B0)
struct HouseTypeClass : AbstractTypeClass
{
    char          ParentCountry[0x19];     // +0x98  FixedString<25>
    unsigned char align_B1[3];             // +0xB1
    int           ArrayIndex;              // +0xB4
    int           ArrayIndex2;             // +0xB8
    int           SideIndex;               // +0xBC
    int           ColorSchemeIndex;        // +0xC0
    unsigned long align_C4;                // +0xC4  (DWORD)

    double        FirepowerMult;           // +0xC8
    double        GroundspeedMult;         // +0xD0
    double        AirspeedMult;            // +0xD8
    double        ArmorMult;               // +0xE0
    double        ROFMult;                 // +0xE8
    double        CostMult;                // +0xF0
    double        BuildtimeMult;           // +0xF8

    float         ArmorInfantryMult;       // +0x100
    float         ArmorUnitsMult;          // +0x104
    float         ArmorAircraftMult;       // +0x108
    float         ArmorBuildingsMult;      // +0x10C
    float         ArmorDefensesMult;       // +0x110
    float         CostInfantryMult;        // +0x114
    float         CostUnitsMult;           // +0x118
    float         CostAircraftMult;        // +0x11C
    float         CostBuildingsMult;       // +0x120
    float         CostDefensesMult;        // +0x124
    float         SpeedInfantryMult;       // +0x128
    float         SpeedUnitsMult;          // +0x12C
    float         SpeedAircraftMult;       // +0x130
    float         BuildtimeInfantryMult;   // +0x134
    float         BuildtimeUnitsMult;      // +0x138
    float         BuildtimeAircraftMult;   // +0x13C
    float         BuildtimeBuildingsMult;  // +0x140
    float         BuildtimeDefensesMult;   // +0x144
    float         IncomeMult;              // +0x148

    TypeListData  VeteranInfantry;         // +0x14C  TypeList<InfantryTypeClass*>
    TypeListData  VeteranUnits;            // +0x168  TypeList<UnitTypeClass*>
    TypeListData  VeteranAircraft;         // +0x184  TypeList<AircraftTypeClass*>

    char          Suffix[4];               // +0x1A0
    char          Prefix;                  // +0x1A4
    bool          Multiplay;               // +0x1A5
    bool          MultiplayPassive;        // +0x1A6
    bool          WallOwner;               // +0x1A7
    bool          SmartAI;                 // +0x1A8
    unsigned char padding_1A9[7];          // +0x1A9  (pad to sizeof 0x1B0)
};

GG_STATIC_ASSERT(offsetof(HouseTypeClass, ParentCountry)     == 0x98);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, ArrayIndex)        == 0xB4);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, ColorSchemeIndex)  == 0xC0);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, FirepowerMult)     == 0xC8);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, BuildtimeMult)     == 0xF8);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, ArmorInfantryMult) == 0x100);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, IncomeMult)        == 0x148);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, VeteranInfantry)   == 0x14C);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, VeteranAircraft)   == 0x184);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, Suffix)            == 0x1A0);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, Multiplay)         == 0x1A5);
GG_STATIC_ASSERT(offsetof(HouseTypeClass, padding_1A9)       == 0x1A9);
GG_STATIC_ASSERT(sizeof(HouseTypeClass)                      == 0x1B0);

#endif  // GG_MATCH_LAYOUT_HOUSE_TYPE_CLASS_H
