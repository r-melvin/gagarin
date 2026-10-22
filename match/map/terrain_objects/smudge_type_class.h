// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check (names only, consult-only)
//   Layout, tables and vptr offsets read from the retail gamemd.exe v1.001: RTTI
//   .?AVSmudgeTypeClass@@ (TD 0x840008; COL 0x8099A0 base 0 / vtable 0x7F3528, COL 0x809930 base 4 /
//   0x7F350C, COL 0x809918 base 8 / 0x7F3504, COL 0x809900 base 12 / 0x7F34FC; chain SmudgeTypeClass
//   -> ObjectTypeClass -> AbstractTypeClass -> AbstractClass -> IPersistStream -> IPersist -> IUnknown,
//   IRTTITypeInfo -> IUnknown, INoticeSink, INoticeSource), the constructor 0x6B5260 (every member
//   store below), the INI reader 0x6B56D0 (every key string and member offset), and the allocation
//   sites 0x6B5966 and 0x6C32BC (`PUSH 0x2A4; CALL 0x7C8E17`, two sites, both agreeing).
//
// SmudgeTypeClass: the rules-INI template of a smudge ([SmudgeTypes] sections).
//
//   +0x00..+0x293  MapObjTypeClassView (AbstractClass / AbstractTypeClass / ObjectTypeClass members;
//                  the type name is at +0x24, passed as the INI section by the reader)
//   +0x294 ArrayIndex (int)  ctor -1, then the index of this type in SmudgeTypeClass::Array
//   +0x298 Width      (int)  ctor 1, INI key "Width"
//   +0x29C Height     (int)  ctor 1, INI key "Height"
//   +0x2A0 Crater     (bool) ctor 0, INI key "Crater"
//   +0x2A1 Burn       (bool) ctor 0, INI key "Burn"
//   sizeof 0x2A4 (from the allocation)
#ifndef GG_MATCH_MAP_TERRAIN_OBJECTS_SMUDGE_TYPE_CLASS_H
#define GG_MATCH_MAP_TERRAIN_OBJECTS_SMUDGE_TYPE_CLASS_H

#include "terrain_common_types.h"
#include "terrain_common_vectors.h"
#include "terrain_common_views.h"

// GLOBAL: GAMEMD 0xA8EC18 - SmudgeTypeClass::Array, every smudge type (vptr 0x7E9DC4 side).
extern MapObjDynVector<SmudgeTypeClass*> SmudgeTypeArray;

// VTABLE: GAMEMD 0x7F3528 (IPersistStream side) and GAMEMD 0x7F350C / 0x7F3504 / 0x7F34FC
class SmudgeTypeClass : public MapObjTypeClassView
{
public:
    // FUNCTION: GAMEMD 0x6B5260
    SmudgeTypeClass(const char* id);
    static void __fastcall LoadFromIniList(int idxTheater); // existing row 0x6B5490
    // No-init constructor: Load re-runs it through placement new to restore
    // the vptrs without touching members.
    SmudgeTypeClass(const MapObjNoInit& noInit) : MapObjTypeClassView(noInit) {}

    // FUNCTION: GAMEMD 0x6B5F80 (read-only here, outside the cluster) - tested by SmudgeClass slot 73
    // with the object's cell and `true`; purpose not recovered.
    bool Method_6B5F80(const MapObjCell* cell, bool flag);
    // FUNCTION: GAMEMD 0x6B6080 (read-only here, outside the cluster) - walks the type's
    // Width x Height cells from the given cell; purpose not recovered.
    void Method_6B6080(const MapObjCell* cell);

    // ---- primary table (IPersistStream side) overrides ---------------------------------------
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                  // 3   0x6B58D0
    virtual HRESULT __stdcall Load(IStream* pStm);                          // 5   0x6B5850
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);        // 6   0x6B58B0
    // Slot 8: the scalar deleting destructor 0x6B6160 is compiler output; the destructor body is
    // inline (it is expanded into that entry, and the base body 0x5F7400 is out of line).
    virtual ~SmudgeTypeClass()
    {
        if (Image) {
            delete Image;
            Image = 0;
        }
        MapObjAnnouncePointerExpired(this, true);
        SmudgeTypeArray.RemoveItem(this);
    }
    virtual int WhatAmI();                                                  // 11  0x6B6130
    virtual int Size();                                                     // 12  0x6B6140
    virtual void ComputeCRC(MapObjCrcView& crc);                            // 13  0x6B57F0
    virtual int vf_16();                                                    // 16  0x6B6150
    virtual bool ReadINI(MapObjIniView* ini);                               // 25  0x6B56D0
    virtual bool vf_32(const MapObjCell* cell, MapObjHouseView* house);     // 32  0x6B5550
    virtual void* vf_35(MapObjHouseView* house);                     // 35  0x6B55C0
    // Slot 40 is not part of the shared ObjectTypeClass table (40 slots): SmudgeTypeClass adds it.
    virtual void vf_40(const MapObjPoint* where, MapObjRect* clip, int index, int height,
                       const MapObjCell* cell);                             // 40  0x6B55F0

    // ---- members (complete-object offsets) ---------------------------------------------------
    int            ArrayIndex;   // +0x294
    int            Width;        // +0x298
    int            Height;       // +0x29C
    bool           Crater;       // +0x2A0
    bool           Burn;         // +0x2A1
    char           unknown_2A2[2];   // +0x2A2 (padding; sizeof from the allocation)
};

GG_STATIC_ASSERT(offsetof(SmudgeTypeClass, ArrayIndex) == 0x294);
GG_STATIC_ASSERT(offsetof(SmudgeTypeClass, Width) == 0x298);
GG_STATIC_ASSERT(offsetof(SmudgeTypeClass, Height) == 0x29C);
GG_STATIC_ASSERT(offsetof(SmudgeTypeClass, Crater) == 0x2A0);
GG_STATIC_ASSERT(offsetof(SmudgeTypeClass, Burn) == 0x2A1);
// sizeof is from the allocation: `PUSH 0x2A4; CALL 0x7C8E17` at 0x6B5966 and 0x6C32BC.
GG_STATIC_ASSERT(sizeof(SmudgeTypeClass) == 0x2A4);

#endif  // GG_MATCH_MAP_TERRAIN_OBJECTS_SMUDGE_TYPE_CLASS_H
