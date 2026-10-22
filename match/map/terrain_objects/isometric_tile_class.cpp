// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// IsometricTileClass entries (layout and evidence: isometric_tile_class.h).

#include <new.h>
#include "isometric_tile_class.h"

// Slot 54, inline because the constructor expands it.
// FUNCTION: GAMEMD 0x543A10
inline bool IsometricTileClass::Unlimbo(const MapObjCoord* where, int facing)
{
    unknown_81 = 0;
    vf_109(where);
    return Mark(1);
}

// Slot 53: take the tile off the map. Inline, because the destructor expands it.
// FUNCTION: GAMEMD 0x543A40
inline bool IsometricTileClass::vf_53()
{
    if (MapObjRemovalEnabled && !unknown_81) {
        vf_84();
        vf_55(1);
        Mark(0);
        unknown_81 = 1;
        unknown_80 = 0;
        return true;
    }
    return false;
}

// Slot 8. The body is expanded both into the scalar deleting destructor 0x543B10 and into the
// stand-alone destructor 0x543880 (not emitted here: nothing in this unit calls it directly);
// the base body 0x5F3B80 is out of line.
// FUNCTION: GAMEMD 0x543B10 (scalar deleting destructor; ??_G)
inline IsometricTileClass::~IsometricTileClass()
{
    MapObjAnnouncePointerExpired(this, true);
    vf_53();
    Type = 0;
    DAT_0087F750.RemoveItem(this);
    reinterpret_cast<MapObjDynVector<void*>*>(&DAT_00B0F670)->RemoveItem(this);
}

// FUNCTION: GAMEMD 0x543780
IsometricTileClass::IsometricTileClass(int typeIndex, const MapObjCell* cell) : Type(DAT_00A8ED28[typeIndex])
{
    if (cell->X != DAT_00AA06D0.X || cell->Y != DAT_00AA06D0.Y) {
        MapObjCoord coord((cell->X << 8) + 0x80, (cell->Y << 8) + 0x80, 0);
        Unlimbo(&coord, 0);
    }
    DAT_0087F750.AddItem(this);
}

// FUNCTION: GAMEMD 0x543990
HRESULT __stdcall IsometricTileClass::Load(IStream* pStm)
{
    HRESULT hr = MapObjClassView::Load(pStm);
    if (hr >= 0) {
        new (this) IsometricTileClass(MapObjNoInit());
        MapObjSwizzle.Swizzle((void**)&Type);
    }
    return hr;
}

// FUNCTION: GAMEMD 0x543A90
int IsometricTileClass::Size()
{
    return 0xB0;
}

// FUNCTION: GAMEMD 0x543AA0
int IsometricTileClass::WhatAmI()
{
    return 0x11;
}

// FUNCTION: GAMEMD 0x543AF0
MapObjTypeClassView* IsometricTileClass::GetType()
{
    return Type;
}

// FUNCTION: GAMEMD 0x543B00
void IsometricTileClass::vf_69(MapObjPoint* where, MapObjRect* clip)
{
}
