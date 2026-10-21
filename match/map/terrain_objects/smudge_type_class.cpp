// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
//
// SmudgeTypeClass entries (layout and evidence: smudge_type_class.h).

#include <new.h>
#include "smudge_class.h"
#include "smudge_type_class.h"

// FUNCTION: GAMEMD 0x6B5260
// CAPPED at 97.3%: retail loads Count then Capacity (EAX, ECX) for the inlined AddItem, this compiles
// Capacity first; the early-return and Count-first AddItem shapes tried fall to 94.5% / 57.0%.
SmudgeTypeClass::SmudgeTypeClass(const char* id)
    : MapObjTypeClassView(id), ArrayIndex(-1), Width(1), Height(1), Crater(false), Burn(false)
{
    MapObjRttiBase::Create_ID();
    unknown_22F = true;
    unknown_230 = false;
    unknown_231 = false;
    unknown_232 = true;
    unknown_233 = true;
    unknown_235 = false;
    SmudgeTypeArray.AddItem(this);
    ArrayIndex = SmudgeTypeArray.FindIndex(this);
}

// FUNCTION: GAMEMD 0x6B5550
bool SmudgeTypeClass::vf_32(const MapObjCell* cell, MapObjHouseView* house)
{
    if (new SmudgeClass(this, MapObjCoord(cell->X * 256 + 128, cell->Y * 256 + 128, 0), -1))
        return true;
    return false;
}

// GLOBAL: GAMEMD 0xB0B7A8 - the all-zero coordinate CreateObject creates its smudge at.
extern MapObjCoord SmudgeOriginCoord;

// FUNCTION: GAMEMD 0x6B55C0
void* SmudgeTypeClass::vf_35(MapObjHouseView* house)
{
    return new SmudgeClass(this, SmudgeOriginCoord, -1);
}

// FUNCTION: GAMEMD 0x6B55F0
// CAPPED at 60.0%: the cell-index to screen-offset arithmetic and the argument order match retail;
// retail pushes the six zero arguments that precede the MapObjHeightScale call from two zeroed
// registers (XOR EDX,EDX / XOR ECX,ECX), this emits PUSH 0 for each. Zero locals, a void* argument
// and an inlined wrapper with the zeros as parameters did not change it.
void SmudgeTypeClass::vf_40(const MapObjPoint* where, MapObjRect* clip, int index, int height,
                            const MapObjCell* cell)
{
    void* shape = vf_39();
    if (shape) {
        MapObjPoint point = *where;
        if (index) {
            int column = index % Width;
            int row = index / Width;
            point.Y += (row + column) * -15;
            point.X += (row - column) * 60 / 2;
        }
        MapObjCellView* mapCell = MapObjMap.GetCellAt(*cell);
        MapObjDrawShape(MapObjSurface, mapCell->Convert, shape, 0, &point, clip, 0xE00, 0,
                        -1 - MapObjHeightScale(height), 0, mapCell->Light, 0, 0, 0, 0, 0);
    }
}

// FUNCTION: GAMEMD 0x6B56D0
bool SmudgeTypeClass::ReadINI(MapObjIniView* ini)
{
    ini->ClearCache();
    if (MapObjTypeClassView::ReadINI(ini)) {
        // STRING: GAMEMD 0x8185F4 "Crater", 0x840028 "Burn", 0x82BBE4 "Width", 0x81A7A8 "Height"
        Crater = ini->ReadBool(ID, "Crater", Crater);
        Burn = ini->ReadBool(ID, "Burn", Burn);
        Width = ini->ReadInt(ID, "Width", Width);
        Height = ini->ReadInt(ID, "Height", Height);
        char path[0x200];
        // STRING: GAMEMD 0x81834C ".SHP"; the theater branch reads MapObjTheaters[...].Extension
        if (!Theater)
            _makepath(path, 0, 0, ImageFile, ".SHP");
        else
            _makepath(path, 0, 0, ImageFile, MapObjTheaters[MapObjScenario->TheaterIndex].Extension);
        Image = MapObjLoadShape(path, false);
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x6B57F0
void SmudgeTypeClass::ComputeCRC(MapObjCrcView& crc)
{
    MapObjTypeClassView::ComputeCRC(crc);
    crc.AddInt(ArrayIndex);
    crc.AddBool(Crater);
    crc.AddBool(Burn);
    crc.AddInt(Width);
    crc.AddInt(Height);
}

// FUNCTION: GAMEMD 0x6B5850
HRESULT __stdcall SmudgeTypeClass::Load(IStream* pStm)
{
    HRESULT hr = MapObjTypeClassView::Load(pStm);
    if (hr >= 0) {
        new (this) SmudgeTypeClass(MapObjNoInit());
        LoadFixup();
        PostLoad();
        hr = 0;
    }
    return hr;
}

// FUNCTION: GAMEMD 0x6B58B0
HRESULT __stdcall SmudgeTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = MapObjTypeClassView::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// GLOBAL: GAMEMD 0x7E9610 - CLSID of SmudgeTypeClass (16 bytes read from the image).
extern "C" const CLSID CLSID_SmudgeType =
    { 0x5AF2CE78, 0x0634, 0x11D2, { 0xAC, 0xA4, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5 } };

// FUNCTION: GAMEMD 0x6B58D0
HRESULT __stdcall SmudgeTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = CLSID_SmudgeType;
    return S_OK;
}

// FUNCTION: GAMEMD 0x6B6130
int SmudgeTypeClass::WhatAmI()
{
    return 0x1E;
}

// FUNCTION: GAMEMD 0x6B6140
int SmudgeTypeClass::Size()
{
    return 0x2A4;
}

// FUNCTION: GAMEMD 0x6B6150
int SmudgeTypeClass::vf_16()
{
    return ArrayIndex;
}

// SYNTHETIC: GAMEMD 0x6B6160 — compiler-generated scalar deleting destructor emitted for the virtual destructor.
