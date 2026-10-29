// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Canonical OverlayTypeClass on the real ObjectTypeClass spine. Layout, vptr offsets and
//   member order read from the retail gamemd.exe v1.001: the named constructor 0x5FE250 (every
//   member store below), the no-init constructor 0x5FE3C0, the INI reader 0x5FE770 (the key
//   strings Land, Strength, Wall, Tiberium, Crate, CrateTrigger, Explodes, Overrides, CellAnim
//   and DamageLevels), the CRC slot 0x5FEA50, and the allocation sites 0x5FECC6 and 0x6C313C
//   (`PUSH 0x2BC; CALL 0x7C8E17`, both agreeing). The four vptrs stored at 0x5FE2F1.. are
//   0x7EF600 / 0x7EF5E4 / 0x7EF5DC / 0x7EF5D4 (RTTI .?AVOverlayTypeClass@@).
//
//   map/terrain_objects/overlay_type_class.h is the older partial view of the same object (it
//   derives a view of the ObjectTypeClass members). Do not include both in one translation unit;
//   the views are to be folded onto this header.
#ifndef GG_MATCH_LAYOUT_OVERLAY_TYPE_CLASS_H
#define GG_MATCH_LAYOUT_OVERLAY_TYPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "object_type_class.h"
#include "color_struct.h"
#include "cell.h"
#include "geometry2d.h"

class AnimTypeClass;
class HouseClass;
class ObjectClass;
class CCINIClass;
struct Obj_004A1D30;

// VTABLE: GAMEMD 0x7EF600 (IPersistStream side) and GAMEMD 0x7EF5E4 / 0x7EF5DC / 0x7EF5D4
class OverlayTypeClass : public ObjectTypeClass
{
public:
    // FUNCTION: GAMEMD 0x5FE250 -- the named constructor (the INI loader calls it to allocate a type it has not seen).
    OverlayTypeClass(const char* id);
    // FUNCTION: GAMEMD 0x5FE3C0 -- no-init constructor (Load re-runs it to restore the vptrs).
    OverlayTypeClass(const AbstractNoInit& noInit);
    // FUNCTION: GAMEMD 0x5FE470
    static int FindIndex(const char* pID);
    // FUNCTION: GAMEMD 0x5FE620
    static void LoadArt(int idxTheater);

    // Primary table (0x7EF600) overrides.
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                  // 3   0x5FEC30
    virtual HRESULT __stdcall Load(IStream* pStm);                          // 5   0x5FEAF0
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);        // 6   0x5FEC10
    virtual ~OverlayTypeClass();                                            // 8   0x5FEF30 (scalar deleting); body 0x5FE3F0
    virtual int vf_11();                                                    // 11  0x5FEF00
    virtual int vf_12();                                                    // 12  0x5FEF10
    virtual void vf_13(Obj_004A1D30* crc);                                  // 13  0x5FEA50
    virtual int vf_16();                                                    // 16  0x5FEF20
    virtual bool vf_25(CCINIClass* ini);                                    // 25  0x5FE770
    virtual CoordStruct vf_27(const CoordStruct& coord);                    // 27  0x5FEA30
    virtual bool vf_32(const CellStruct* cell, HouseClass* house);          // 32  0x5FE530
    virtual ObjectClass* vf_35(HouseClass* house);                          // 35  0x5FE570
    virtual void* vf_36(int a1);                                            // 36  0x5FE4C0
    virtual void* vf_39();                                                  // 39  0x5FEDE0
    virtual void vf_40(Point2D* where, RectangleStruct* clip, int frame);   // 40  0x5FE5A0 (introduced here)

    int            ArrayIndex;           // +0x294 ctor @0x5FE280; set to the registry index @0x5FE3A7
    int            Land;                 // +0x298 INI key Land
    AnimTypeClass* CellAnim;             // +0x29C INI key CellAnim (looked up by name)
    int            DamageLevels;         // +0x2A0 INI key DamageLevels (ctor = 1)
    int            Strength;             // +0x2A4 INI key Strength (ctor = 1)
    bool           Wall;                 // +0x2A8 INI key Wall
    bool           Tiberium;             // +0x2A9 INI key Tiberium
    bool           Crate;                // +0x2AA INI key Crate
    bool           CrateTrigger;         // +0x2AB INI key CrateTrigger
    bool           NoUseTileLandType;    // +0x2AC ctor = 1
    bool           IsVeinholeMonster;    // +0x2AD ctor = 0
    bool           IsVeins;              // +0x2AE ctor = 0
    bool           unknown_2AF;          // +0x2AF tested by the INI reader before loading the shape
    bool           Explodes;             // +0x2B0 INI key Explodes
    bool           ChainReaction;        // +0x2B1 ctor = 0
    bool           Overrides;            // +0x2B2 INI key Overrides
    bool           DrawFlat;             // +0x2B3 ctor = 1
    bool           IsRubble;             // +0x2B4 ctor = 0
    bool           IsARock;              // +0x2B5 ctor = 0
    ColorStruct    RadarColor;           // +0x2B6 ctor zero-constructs it inline
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

#endif  // GG_MATCH_LAYOUT_OVERLAY_TYPE_CLASS_H
