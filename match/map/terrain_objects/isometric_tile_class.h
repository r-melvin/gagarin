// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read from the retail gamemd.exe v1.001: RTTI ".?AVIsometricTileClass@@" on the tables 0x7EC258
//   (primary, 122 slots) / 0x7EC23C / 0x7EC234 / 0x7EC22C, the constructor 0x543780 (stores the
//   type at +0xAC), the destructor 0x543880, the scalar deleting destructor 0x543B10, and slot 12
//   (0x543A90 returns 0xB0, the object size).
//
// IsometricTileClass: one placed isometric tile object. Derives the ObjectClass-shaped view of
// terrain_common_views.h, as OverlayClass, SmudgeClass and TerrainClass do.
//
//   +0x00..+0xAB  MapObjClassView (AbstractClass / ObjectClass members)
//   +0xAC  Type  the tile type, taken from the type vector 0xA8ED28 by index
//   sizeof 0xB0 (slot 12)
#ifndef GG_MATCH_MAP_TERRAIN_OBJECTS_ISOMETRIC_TILE_CLASS_H
#define GG_MATCH_MAP_TERRAIN_OBJECTS_ISOMETRIC_TILE_CLASS_H

#include <stddef.h>
#include "terrain_common_types.h"
#include "terrain_common_vectors.h"
#include "terrain_common_views.h"
#include "../../core/abstract_registry.h"

class IsometricTileClass;

// GLOBAL: GAMEMD 0x87F750 - every live IsometricTileClass (the constructor appends, the
// destructor removes).
extern MapObjDynVector<IsometricTileClass*> DAT_0087F750;

// GLOBAL: GAMEMD 0xA8ED28 - the tile type vector the constructor indexes. Its elements are
// IsometricTileTypeClass objects; they are held here through their ObjectTypeClass-shaped base,
// which is what slot 34 returns.
extern MapObjDynVector<MapObjTypeClassView*> DAT_00A8ED28;

// GLOBAL: GAMEMD 0xAA06D0 - the cell value meaning "no placement" for the constructor.
extern MapObjCell DAT_00AA06D0;

// VTABLE: GAMEMD 0x7EC258 (IPersistStream side) and GAMEMD 0x7EC23C / 0x7EC234 / 0x7EC22C
class IsometricTileClass : public MapObjClassView
{
public:
    // FUNCTION: GAMEMD 0x543780
    IsometricTileClass(int typeIndex, const MapObjCell* cell);
    IsometricTileClass(const MapObjNoInit& noInit) : MapObjClassView(noInit) {}

    virtual HRESULT __stdcall Load(IStream* pStm);                          // 5   0x543990
    // Slot 8. The body is expanded both into the scalar deleting destructor 0x543B10 and into the
    // stand-alone destructor 0x543880 (not emitted here: nothing in this unit calls it directly);
    // the base body 0x5F3B80 is out of line.
    virtual ~IsometricTileClass();                                          // 8   0x543B10 (inline, below in the .cpp)
    virtual int WhatAmI();                                                  // 11  0x543AA0
    virtual int Size();                                                     // 12  0x543A90
    virtual MapObjTypeClassView* GetType();                                // 34  0x543AF0
    virtual bool vf_53();                                                   // 53  0x543A40
    virtual bool Unlimbo(const MapObjCoord* where, int facing);             // 54  0x543A10
    virtual void vf_69(MapObjPoint* where, MapObjRect* clip);               // 69  0x543B00

    MapObjTypeClassView* Type;   // +0xAC
};

GG_STATIC_ASSERT(offsetof(IsometricTileClass, Type) == 0xAC);
GG_STATIC_ASSERT(sizeof(IsometricTileClass) == 0xB0);

#endif  // GG_MATCH_MAP_TERRAIN_OBJECTS_ISOMETRIC_TILE_CLASS_H
