// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check (names only)
//   Layout, tables and vptr offsets read from the retail gamemd.exe v1.001: RTTI .?AVOverlayClass@@
//   (terrain_common_views.h), the constructor 0x5FC380 (every member store below), the scalar deleting
//   destructor 0x5FDF70, and the allocation sites 0x43F5F9, 0x5FD4AA, 0x5FE533 and 0x5FE573
//   (`PUSH 0xB0; CALL 0x7C8E17`, four sites, all agreeing).
//
// OverlayClass: one placed overlay object (walls, tiberium, veins, rubble, crates). Derives the
// ObjectClass-shaped partial view of terrain_common_views.h.
//
//   +0x00..+0xAB  MapObjClassView (AbstractClass / ObjectClass members)
//   +0xAC Type           (OverlayTypeClass*)  ctor argument 1
//   sizeof 0xB0 (from the allocation)
#ifndef GG_MATCH_MAP_TERRAIN_OBJECTS_OVERLAY_CLASS_H
#define GG_MATCH_MAP_TERRAIN_OBJECTS_OVERLAY_CLASS_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "overlay_type_class.h"
#include "overlay_shared.h"

// VTABLE: GAMEMD 0x7EF3D4 (IPersistStream side) and GAMEMD 0x7EF3B0 / 0x7EF3CC / 0x7EF3A8
class OverlayClass : public MapObjClassView
{
public:
    // FUNCTION: GAMEMD 0x5FC380
    OverlayClass(OverlayTypeClass* type, const MapObjCell& cell, int arg);
    static int GetTiberiumType(int idxOverlay); // existing row 0x5FDD20
    // No-init constructor: Load re-runs it through placement new to restore
    // the vptrs without touching members.
    OverlayClass(const MapObjNoInit& noInit) : MapObjClassView(noInit) {}

    // ---- primary table (IPersistStream side) overrides ---------------------------------------
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                  // 3   0x5FDF10
    virtual HRESULT __stdcall Load(IStream* pStm);                          // 5   0x5FD8F0
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);        // 6   0x5FD950
    // Slot 8: the scalar deleting destructor 0x5FDF70 is compiler output; the destructor body is
    // inline (it is expanded into that entry, and the base body 0x5F3B80 is out of line).
    // FUNCTION: GAMEMD 0x5FDF70 (scalar deleting destructor; ??_G)
    virtual ~OverlayClass()
    {
        MapObjAnnouncePointerExpired(this, true);
        OverlayArray.RemoveItem(this);
        if (MapObjRemovalEnabled)
            vf_53();
        Type = 0;
    }
    virtual int WhatAmI();                                                  // 11  0x5FDF50
    virtual int Size();                                                     // 12  0x5FDF00
    virtual MapObjTypeClassView* GetType();                               // 34  0x5FDDE0
    virtual bool Unlimbo(const MapObjCoord* where, int facing);                  // 54  0x5FD270
    virtual void vf_69(MapObjPoint* where, MapObjRect* clip);                                   // 69  0x5FDF60
    virtual void vf_70(MapObjPoint* where, MapObjRect* clip);             // 70  0x5FD970
    virtual bool Mark(int markType);                                        // 73  0x5FC570

    // ---- members (complete-object offsets) ---------------------------------------------------
    OverlayTypeClass*    Type;          // +0xAC
};

GG_STATIC_ASSERT(offsetof(OverlayClass, Type) == 0xAC);
// sizeof is from the allocation: `PUSH 0xB0; CALL 0x7C8E17` at 0x43F5F9, 0x5FD4AA, 0x5FE533, 0x5FE573.
GG_STATIC_ASSERT(sizeof(OverlayClass) == 0xB0);

#endif  // GG_MATCH_MAP_TERRAIN_OBJECTS_OVERLAY_CLASS_H
