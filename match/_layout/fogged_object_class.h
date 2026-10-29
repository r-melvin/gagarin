// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI: primary vtable 0x7E8B38, COL -> ".?AVFoggedObjectClass@@", bases
//   AbstractClass (IPersistStream chain at +0, IRTTITypeInfo at +4, INoticeSink
//   at +8, INoticeSource at +0xC); the constructors store the four tables
//   0x7E8B38 / 0x7E8B1C / 0x7E8B14 / 0x7E8B0C. Size 0x78: slot 12 (0x4D27C0)
//   returns 0x78 and the one allocation site (0x6C5FBC) allocates 0x78.
//   Fields from the default constructor 0x4D08B0 and the full constructor
//   0x4D0980 (cell coordinate argument at +0x34, the cell's level byte at +0x50,
//   the DrawRecord vector at +0x5C: vtable 0x7E8BA0, capacity increment 10),
//   the checksum 0x4D2810 and the stream writer 0x4D24A0.
//   The nested DrawRecord is the element named by the retail vector RTTI (a
//   0x10-byte record whose equality compares the first two words, as the
//   vector FindItemIndex inlines).
#ifndef GG_MATCH_LAYOUT_FOGGED_OBJECT_CLASS_H
#define GG_MATCH_LAYOUT_FOGGED_OBJECT_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"
#include "coord_struct.h"
#include "geometry2d.h"
#include "../core/vector_class.h"

struct Obj_004A1D30;

// CoordStruct / RectangleStruct as FoggedObjectClass's constructors build them:
// zeroed through an inlined constructor, in member-initialiser position. The
// canonical aggregates have no constructors, so these views supply them.
struct FoggedCoordInit : CoordStruct
{
    FoggedCoordInit() { X = 0; Y = 0; Z = 0; }
    FoggedCoordInit& operator=(const CoordStruct& c) { X = c.X; Y = c.Y; Z = c.Z; return *this; }
};
struct FoggedRectInit : RectangleStruct
{
    FoggedRectInit() { X = 0; Y = 0; Width = 0; Height = 0; }
    FoggedRectInit& operator=(const RectangleStruct& r) { X = r.X; Y = r.Y; Width = r.Width; Height = r.Height; return *this; }
};

// VTABLE: GAMEMD 0x7E8B38 (IPersistStream side)
// VTABLE: GAMEMD 0x7E8B1C (IRTTITypeInfo side, +0x04)
// VTABLE: GAMEMD 0x7E8B14 (INoticeSink side, +0x08)
// VTABLE: GAMEMD 0x7E8B0C (INoticeSource side, +0x0C)
class FoggedObjectClass : public AbstractClass
{
public:
    struct DrawRecord
    {
        int unknown_00;
        int unknown_04;
        unsigned char unknown_08;
        int unknown_0C;
        DrawRecord() : unknown_00(0), unknown_04(0), unknown_08(0), unknown_0C(0) {}
        DrawRecord(const DrawRecord& o) : unknown_00(o.unknown_00), unknown_04(o.unknown_04), unknown_08(o.unknown_08), unknown_0C(o.unknown_0C) {}
        bool operator==(const DrawRecord& o) const { return unknown_00==o.unknown_00 && unknown_04==o.unknown_04; }
        bool operator!=(const DrawRecord& o) const { return !(*this==o); }
    };

    // FUNCTION: GAMEMD 0x4D08B0 (default constructor)
    FoggedObjectClass();
    // FUNCTION: GAMEMD 0x4D1650 (destructor body; slot 8 = 0x4D2910)
    virtual ~FoggedObjectClass();

    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 3   0x4D27D0
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 5   0x4D2510
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 6   0x4D24A0
    virtual int vf_11();                                                  // 11  0x4D27B0: returns 0x3D
    virtual int vf_12();                                                  // 12  0x4D27C0: returns 0x78
    virtual void vf_13(Obj_004A1D30* crc);                                // 13  0x4D2810

    int         unknown_24;     // +0x24  constructor stores -1 (the full constructor's 2nd argument)
    int         unknown_28;     // +0x28  constructors store 0
    int         unknown_2C;     // +0x2C  the full constructor's 3rd argument
    int         unknown_30;     // +0x30  0x14 in the full constructor, 0 in the default one
    FoggedCoordInit Coords;    // +0x34  the cell coordinate argument
    FoggedRectInit Bounds;    // +0x40  screen bounds built from the cell's two rectangles
    int         unknown_50;     // +0x50  the cell's signed byte at +0x11B
    int         unknown_54;     // +0x54  constructors store -1
    int         unknown_58;     // +0x58  constructors store 0
    DynamicVectorClass<DrawRecord> DrawRecords;   // +0x5C  vtable 0x7E8BA0, capacity increment 10
    bool        unknown_74;     // +0x74  constructors store 1
    unsigned char _pad_75[3];   // +0x75
};
GG_STATIC_ASSERT(offsetof(FoggedObjectClass, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(FoggedObjectClass, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(FoggedObjectClass, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(FoggedObjectClass, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(FoggedObjectClass, Coords) == 0x34);
GG_STATIC_ASSERT(offsetof(FoggedObjectClass, Bounds) == 0x40);
GG_STATIC_ASSERT(offsetof(FoggedObjectClass, unknown_50) == 0x50);
GG_STATIC_ASSERT(offsetof(FoggedObjectClass, unknown_54) == 0x54);
GG_STATIC_ASSERT(offsetof(FoggedObjectClass, unknown_58) == 0x58);
GG_STATIC_ASSERT(offsetof(FoggedObjectClass, DrawRecords) == 0x5C);
GG_STATIC_ASSERT(offsetof(FoggedObjectClass, unknown_74) == 0x74);
GG_STATIC_ASSERT(sizeof(FoggedObjectClass) == 0x78);

#endif  // GG_MATCH_LAYOUT_FOGGED_OBJECT_CLASS_H
