// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check (names only)
//   Layout, tables and vptr offsets read from the retail gamemd.exe v1.001: RTTI
//   .?AVOverlayTypeClass@@ (terrain_common_views.h), the constructor 0x5FE250 (every member store below), the
//   INI reader 0x5FE770 (every key string and member offset), the CRC slot 0x5FEA50, and the
//   allocation sites 0x5FECC6 and 0x6C313C (`PUSH 0x2BC; CALL 0x7C8E17`, two sites, both agreeing).
//
// OverlayTypeClass: the rules-INI template of an overlay ([OverlayTypes] sections). Derives the
// ObjectTypeClass-shaped partial view of terrain_common_views.h.
//
//   +0x00..+0x293  MapObjTypeClassView (AbstractClass / AbstractTypeClass / ObjectTypeClass members)
//   +0x294 ArrayIndex  +0x298 Land  +0x29C CellAnim  +0x2A0 DamageLevels  +0x2A4 Strength
//   +0x2A8 Wall  +0x2A9 Tiberium  +0x2AA Crate  +0x2AB CrateTrigger  +0x2AC NoUseTileLandType
//   +0x2AD IsVeinholeMonster  +0x2AE IsVeins  +0x2B0 Explodes  +0x2B1 ChainReaction
//   +0x2B2 Overrides  +0x2B3 DrawFlat  +0x2B4 IsRubble  +0x2B5 IsARock  +0x2B6 RadarColor
//   sizeof 0x2BC (from the allocation)
#ifndef GG_MATCH_MAP_TERRAIN_OBJECTS_OVERLAY_TYPE_CLASS_H
#define GG_MATCH_MAP_TERRAIN_OBJECTS_OVERLAY_TYPE_CLASS_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "overlay_shared.h"

// VTABLE: GAMEMD 0x7EF600 (IPersistStream side) and GAMEMD 0x7EF5E4 / 0x7EF5DC / 0x7EF5D4
class OverlayTypeClass : public MapObjTypeClassView
{
public:
    // FUNCTION: GAMEMD 0x5FE250 - the named constructor, also what the INI loader calls to allocate a
    // type it has not seen yet.
    OverlayTypeClass(const char* id);
    static int FindIndex(const char* pID); // existing row 0x5FE470
    static void LoadArt(int idxTheater);  // existing row 0x5FE620
    // No-init constructor: Load re-runs it through placement new to restore
    // the vptrs without touching any other member.
    OverlayTypeClass(const MapObjNoInit& noInit) : MapObjTypeClassView(noInit) {}

    // ---- primary table (IPersistStream side) overrides ---------------------------------------
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                  // 3   0x5FEC30
    virtual HRESULT __stdcall Load(IStream* pStm);                          // 5   0x5FEAF0
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);        // 6   0x5FEC10
    // Slot 8: the scalar deleting destructor 0x5FEF30 is compiler output; the destructor body is
    // inline (it is expanded into that entry) and the base body 0x5F7400 is out of line.
    // FUNCTION: GAMEMD 0x5FEF30 (scalar deleting destructor; ??_G)
    virtual ~OverlayTypeClass()
    {
        MapObjAnnouncePointerExpired(this, true);
        OverlayTypeArray.RemoveItem(this);
    }
    virtual int WhatAmI();                                                  // 11  0x5FEF00
    virtual int Size();                                                     // 12  0x5FEF10
    virtual void ComputeCRC(MapObjCrcView& crc);                           // 13  0x5FEA50
    virtual int vf_16();                                                    // 16  0x5FEF20
    virtual bool ReadINI(MapObjIniView* ini);                              // 25  0x5FE770
    virtual MapObjCoord* vf_27(MapObjCoord* out, const MapObjCoord* in);                     // 27  0x5FEA30
    virtual bool vf_32(const MapObjCell* where, MapObjHouseView* owner);        // 32  0x5FE530
    virtual void* vf_35(MapObjHouseView* owner);                           // 35  0x5FE570
    virtual MapObjCell* vf_36(int arg);                                    // 36  0x5FE4C0
    virtual void* vf_39();                                                  // 39  0x5FEDE0
    virtual void vf_40(MapObjPoint* where, MapObjRect* clip, int frame);  // 40  0x5FE5A0

    // ---- members (complete-object offsets) ---------------------------------------------------
    int            ArrayIndex;           // +0x294
    int            Land;                 // +0x298
    MapObjTypeClassView* CellAnim;     // +0x29C
    int            DamageLevels;         // +0x2A0
    int            Strength;             // +0x2A4
    bool           Wall;                 // +0x2A8
    bool           Tiberium;             // +0x2A9
    bool           Crate;                // +0x2AA
    bool           CrateTrigger;         // +0x2AB
    bool           NoUseTileLandType;    // +0x2AC
    bool           IsVeinholeMonster;    // +0x2AD
    bool           IsVeins;              // +0x2AE
    bool           unknown_2AF;          // +0x2AF
    bool           Explodes;             // +0x2B0
    bool           ChainReaction;        // +0x2B1
    bool           Overrides;            // +0x2B2
    bool           DrawFlat;             // +0x2B3
    bool           IsRubble;             // +0x2B4
    bool           IsARock;              // +0x2B5
    MapObjColor   RadarColor;           // +0x2B6
};

GG_STATIC_ASSERT(offsetof(OverlayTypeClass, ArrayIndex) == 0x294);
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, Land) == 0x298);
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, CellAnim) == 0x29C);
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, DamageLevels) == 0x2A0);
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, Strength) == 0x2A4);
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, Wall) == 0x2A8);
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, Tiberium) == 0x2A9);
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, Crate) == 0x2AA);
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, CrateTrigger) == 0x2AB);
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, NoUseTileLandType) == 0x2AC);
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, IsVeinholeMonster) == 0x2AD);
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, IsVeins) == 0x2AE);
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, unknown_2AF) == 0x2AF);
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, Explodes) == 0x2B0);
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, ChainReaction) == 0x2B1);
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, Overrides) == 0x2B2);
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, DrawFlat) == 0x2B3);
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, IsRubble) == 0x2B4);
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, IsARock) == 0x2B5);
GG_STATIC_ASSERT(offsetof(OverlayTypeClass, RadarColor) == 0x2B6);
// sizeof is from the allocation: `PUSH 0x2BC; CALL 0x7C8E17` at 0x5FECC6, 0x6C313C.
GG_STATIC_ASSERT(sizeof(OverlayTypeClass) == 0x2BC);

#endif  // GG_MATCH_MAP_TERRAIN_OBJECTS_OVERLAY_TYPE_CLASS_H
