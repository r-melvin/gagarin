// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit TU109 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x543120-0x543c5f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//
// IsometricTileClass entries (layout and evidence: isometric_tile_class.h).

#include <new.h>
#include "../_layout/swizzle_manager_class.h"
#include "terrain_objects/isometric_tile_class.h"
#include "../_layout/object_class.h"

// GLOBAL: GAMEMD 0x007E9640 -- CLSID of IsometricTileClass.
extern const CLSID DAT_007E9640;

// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EC218
extern const double DAT_007EC218;
// GLOBAL: GAMEMD 0xAA06D8
extern double DAT_00AA06D8;

// dynamic initializer for DAT_00AA0728

// GLOBAL: GAMEMD 0x00AA0728
extern double DAT_00AA0728;

// dynamic initializer for DAT_00AA0710

// GLOBAL: GAMEMD 0x00AA0710
extern double DAT_00AA0710;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x543780
IsometricTileClass::IsometricTileClass(int typeIndex, const MapObjCell* cell) : Type(DAT_00A8ED28[typeIndex])
{
    if (cell->X != DAT_00AA06D0.X || cell->Y != DAT_00AA06D0.Y) {
        MapObjCoord coord((cell->X << 8) + 0x80, (cell->Y << 8) + 0x80, 0);
        vf_54(coord, 0);
    }
    DAT_0087F750.AddItem(this);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x543990
HRESULT __stdcall IsometricTileClass::Load(IStream* pStm)
{
    HRESULT hr = ObjectClass::Load(pStm);
    if (hr >= 0) {
        new (this) IsometricTileClass(AbstractNoInit());
        DAT_00B0C110.SwizzleManagerClass::vf_4(&Type);
    }
    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5439F0
HRESULT __stdcall IsometricTileClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Slot 54, inline because the constructor expands it.
// FUNCTION: GAMEMD 0x543A10
inline bool IsometricTileClass::vf_54(const CoordStruct& where, int facing)
{
    InLimbo = 0;
    vf_109(where);
    return vf_73(1);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Slot 53: take the tile off the map. Inline, because the destructor expands it.
// FUNCTION: GAMEMD 0x543A40
inline bool IsometricTileClass::vf_53()
{
    if (MapObjRemovalEnabled && !InLimbo) {
        vf_84();
        vf_55(1);
        vf_73(0);
        InLimbo = 1;
        NeedsRedraw = 0;
        return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x543A90
int IsometricTileClass::vf_12()
{
    return 0xB0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x543AA0
int IsometricTileClass::vf_11()
{
    return 0x11;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x543AB0
HRESULT __stdcall IsometricTileClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = DAT_007E9640;
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x543AF0
ObjectTypeClass* IsometricTileClass::vf_34()
{
    return Type;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x543B00
void IsometricTileClass::vf_69(Point2D* where, RectangleStruct* clip)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x87F750
MapObjDynVector<IsometricTileClass*> DAT_0087F750;
// GLOBAL: GAMEMD 0xAA06D0
MapObjCell DAT_00AA06D0;
// END defined globals
