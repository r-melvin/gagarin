// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check (names only, consult-only)
//   Layout, tables and vptr offsets read from the retail gamemd.exe v1.001: RTTI
//   .?AVTerrainTypeClass@@ (TD 0x8445E8; terrain_common_views.h), the constructor 0x71DA80 (every member store
//   below), the INI reader 0x71DEA0 (every key string and member offset), the loader 0x71E1D0, and the
//   allocation sites 0x6BF23C and 0x71E2F6 (`PUSH 0x2BC; CALL 0x7C8E17`, two sites, both agreeing).
//
// TerrainTypeClass: the rules-INI template of a tree / rock / terrain feature ([TerrainTypes]
// sections). Derives the ObjectTypeClass-shaped partial view of terrain_common_views.h.
//
//   +0x00..+0x293  MapObjTypeClassView (AbstractClass / AbstractTypeClass / ObjectTypeClass members;
//                  the type name is at +0x24, passed as the INI section by the reader)
//   +0x294 ArrayIndex        (int)    ctor: -1, then the index of this type in TerrainTypeClass::Array
//   +0x298 Foundation        (int)    ctor 0; the art INI's foundation index
//   +0x29C RadarColor        (three bytes)
//   +0x2A0 AnimationRate     (int)
//   +0x2A4 AnimationProbability (float)
//   +0x2A8 TemperateOccupationBits (int, ctor 7)  +0x2AC SnowOccupationBits (int, ctor 7)
//   +0x2B0 WaterBound  +0x2B1 SpawnsTiberium  +0x2B2 IsFlammable  +0x2B3 IsAnimated  +0x2B4 IsVeinhole
//   +0x2B8 FoundationCells   (pointer into the 0x28-byte-per-entry table at 0xB0EDC0)
//   sizeof 0x2BC (allocation).
#ifndef GG_MATCH_MAP_TERRAIN_OBJECTS_TERRAIN_TYPE_CLASS_H
#define GG_MATCH_MAP_TERRAIN_OBJECTS_TERRAIN_TYPE_CLASS_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "terrain_shared.h"

// VTABLE: GAMEMD 0x7F5458 (IPersistStream side) and GAMEMD 0x7F543C / 0x7F5434 / 0x7F542C
class TerrainTypeClass : public MapObjTypeClassView
{
public:
    // FUNCTION: GAMEMD 0x71DA80 - the named constructor.
    TerrainTypeClass(const char* id) throw();
    // No-init constructor: Load re-runs it through placement new to restore
    // the vptrs without touching members.
    TerrainTypeClass(const MapObjNoInit& noInit) : MapObjTypeClassView(noInit) {}

    // ---- primary table (IPersistStream side) overrides ---------------------------------------
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                  // 3   0x71E260
    virtual HRESULT __stdcall Load(IStream* pStm);                          // 5   0x71E1D0
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);        // 6   0x71E240
    // Slot 8: the scalar deleting destructor 0x71E360 is compiler output; the destructor body is
    // inline (expanded into that entry) and the base body 0x5F7400 is out of line.
    virtual ~TerrainTypeClass()
    {
        if (Image != 0) {
            operator delete(Image);
            Image = 0;
        }
        MapObjAnnouncePointerExpired(this, true);
        TerrainTypeArray.RemoveItem(this);
    }
    static TerrainTypeClass* __fastcall FindOrAllocate(const char* id); // existing row 0x71E2A0
    virtual int WhatAmI();                                                  // 11  0x71E330
    virtual int Size();                                                     // 12  0x71E340
    virtual void ComputeCRC(MapObjCrcView& crc);                           // 13  0x71E140
    virtual int vf_16();                                                    // 16  0x71E350
    virtual bool ReadINI(MapObjIniView* ini);                              // 25  0x71DEA0
    virtual MapObjCoord* vf_27(MapObjCoord* out, const MapObjCoord* coord);   // 27  0x71E0D0
    virtual bool vf_32(const MapObjCell* cell, MapObjHouseView* house);                     // 32  0x71DDD0
    virtual void* vf_35(MapObjHouseView* house);                                       // 35  0x71DE10
    virtual MapObjCell* vf_36(int arg);                                    // 36  0x71DE40

    // ---- members (complete-object offsets) ---------------------------------------------------
    int            ArrayIndex;                 // +0x294
    int            Foundation;                 // +0x298
    MapObjColor   RadarColor;                 // +0x29C
    char           unknown_29F;                // +0x29F
    int            AnimationRate;              // +0x2A0
    float          AnimationProbability;       // +0x2A4
    int            TemperateOccupationBits;    // +0x2A8
    int            SnowOccupationBits;         // +0x2AC
    bool           WaterBound;                 // +0x2B0
    bool           SpawnsTiberium;             // +0x2B1
    bool           IsFlammable;                // +0x2B2
    bool           IsAnimated;                 // +0x2B3
    bool           IsVeinhole;                 // +0x2B4
    char           unknown_2B5[3];             // +0x2B5
    MapObjCell*   FoundationCells;            // +0x2B8
};

GG_STATIC_ASSERT(offsetof(TerrainTypeClass, ArrayIndex) == 0x294);
GG_STATIC_ASSERT(offsetof(TerrainTypeClass, Foundation) == 0x298);
GG_STATIC_ASSERT(offsetof(TerrainTypeClass, RadarColor) == 0x29C);
GG_STATIC_ASSERT(offsetof(TerrainTypeClass, AnimationRate) == 0x2A0);
GG_STATIC_ASSERT(offsetof(TerrainTypeClass, AnimationProbability) == 0x2A4);
GG_STATIC_ASSERT(offsetof(TerrainTypeClass, TemperateOccupationBits) == 0x2A8);
GG_STATIC_ASSERT(offsetof(TerrainTypeClass, SnowOccupationBits) == 0x2AC);
GG_STATIC_ASSERT(offsetof(TerrainTypeClass, WaterBound) == 0x2B0);
GG_STATIC_ASSERT(offsetof(TerrainTypeClass, SpawnsTiberium) == 0x2B1);
GG_STATIC_ASSERT(offsetof(TerrainTypeClass, IsFlammable) == 0x2B2);
GG_STATIC_ASSERT(offsetof(TerrainTypeClass, IsAnimated) == 0x2B3);
GG_STATIC_ASSERT(offsetof(TerrainTypeClass, IsVeinhole) == 0x2B4);
GG_STATIC_ASSERT(offsetof(TerrainTypeClass, FoundationCells) == 0x2B8);
// sizeof is from the allocation: `PUSH 0x2BC; CALL 0x7C8E17` at 0x6BF23C and 0x71E2F6.
GG_STATIC_ASSERT(sizeof(TerrainTypeClass) == 0x2BC);

#endif  // GG_MATCH_MAP_TERRAIN_OBJECTS_TERRAIN_TYPE_CLASS_H
