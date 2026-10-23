// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
//
// TerrainTypeClass entries (layout and evidence: terrain_type_class.h).

#include <new.h>
#include <stdlib.h>
#include "terrain_type_class.h"
#include "terrain_class.h"

// GLOBAL: GAMEMD 0x7E95E0 - CLSID of TerrainTypeClass (16 bytes read from the image).
extern "C" const CLSID CLSID_TerrainType =
    { 0x5AF2CE7B, 0x0634, 0x11D2, { 0xAC, 0xA4, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5 } };

// FUNCTION: GAMEMD 0x71DA80
// MATCHED (second look): the array append is the same inlined expansion the OverlayTypeClass
// constructor uses (AddItemEarlyOut: Capacity held in a local across the growth tests, the
// element stored through an index local), not the `T* slot = &Items[Count++]` shape.
TerrainTypeClass::TerrainTypeClass(const char* id) throw()
    : MapObjTypeClassView(id), ArrayIndex(-1), Foundation(0), RadarColor(0, 0, 0), AnimationRate(0),
      AnimationProbability(0),
      TemperateOccupationBits(7), SnowOccupationBits(7), WaterBound(false), SpawnsTiberium(false),
      IsFlammable(false), IsAnimated(false), IsVeinhole(false), FoundationCells(0)
{
    MapObjRttiBase::Create_ID();
    unknown_230 = false;
    unknown_234 = true;
    unknown_22F = true;
    unknown_231 = false;
    unknown_232 = true;
    TerrainTypeArray.AddItemEarlyOut(this);
    ArrayIndex = TerrainTypeArray.FindIndex(this);
    unknown_A0 = -1;
    unknown_9C = 6;
}

// FUNCTION: GAMEMD 0x71DDD0
bool TerrainTypeClass::vf_32(const MapObjCell* cell, MapObjHouseView* house)
{
    if (new TerrainClass(this, cell))
        return true;
    return false;
}

// FUNCTION: GAMEMD 0x71DE10
void* TerrainTypeClass::vf_35(MapObjHouseView* house)
{
    return new TerrainClass(this, &TerrainDefaultCell);
}

// FUNCTION: GAMEMD 0x71DE40
// The empty cell list: a function-local static {0x7FFF, 0x7FFF} (guard bit in 0xB0ED60, object at
// 0xB0ED78); its atexit stub is the bare RET at 0x71DE90 (compiler output, outside this partition). The
// static is initialised from a converting temporary (TerrainStaticCell from a MapObjCell): that is what
// builds the two-word stack temporary after the guard test and copies it as one dword, as retail does.
MapObjCell* TerrainTypeClass::vf_36(int arg)
{
    if (FoundationCells == 0) {
        static TerrainStaticCell invalidCell = MapObjCell(0x7FFF, 0x7FFF);
        return &invalidCell;
    }
    return FoundationCells;
}

// FUNCTION: GAMEMD 0x71DEA0
bool TerrainTypeClass::ReadINI(MapObjIniView* ini)
{
    ini->ClearCache();
    if (MapObjTypeClassView::ReadINI(ini)) {
        if (unknown_A0 == -1)
            unknown_A0 = MapObjRules->unknown_1144;
        IsVeinhole = ini->ReadBool(ID, "IsVeinhole", IsVeinhole);
        if (IsVeinhole) {
            unknown_234 = false;
            unknown_231 = true;
        }
        WaterBound = ini->ReadBool(ID, "WaterBound", WaterBound);
        SpawnsTiberium = ini->ReadBool(ID, "SpawnsTiberium", SpawnsTiberium);
        IsFlammable = ini->ReadBool(ID, "IsFlammable", IsFlammable);
        Foundation = MapObjArtIni.ReadFoundation(ImageFile, "Foundation", Foundation);
        FoundationCells = TerrainFoundationTable[Foundation];
        if (!Theater) {
            char path[0x200];
            _makepath(path, 0, 0, ImageFile, ".SHP");
            Image = MapObjLoadShape(path, false);
        }
        MapObjShapeView* shape = (MapObjShapeView*)vf_39();
        if (shape != 0)
            RadarColor = shape->GetRadarColor(0);
        RadarColor = ini->ReadColor(ID, "RadarColor", RadarColor);
        IsAnimated = ini->ReadBool(ID, "IsAnimated", IsAnimated);
        AnimationRate = ini->ReadInt(ID, "AnimationRate", AnimationRate);
        AnimationProbability = (float)ini->ReadDouble(ID, "AnimationProbability", AnimationProbability);
        TemperateOccupationBits = ini->ReadInt(ID, "TemperateOccupationBits", TemperateOccupationBits);
        SnowOccupationBits = ini->ReadInt(ID, "SnowOccupationBits", SnowOccupationBits);
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x71E0D0
MapObjCoord* TerrainTypeClass::vf_27(MapObjCoord* out, const MapObjCoord* coord)
{
    MapObjCoord c = *coord;
    c.Z = c.Z >= MapObjMap.GetHeight(&c) ? c.Z : MapObjMap.GetHeight(&c);
    *out = c;
    return out;
}

// FUNCTION: GAMEMD 0x71E140
void TerrainTypeClass::ComputeCRC(MapObjCrcView& crc)
{
    MapObjTypeClassView::ComputeCRC(crc);
    crc.AddInt(ArrayIndex);
    crc.AddBool(WaterBound);
    crc.AddBool(SpawnsTiberium);
    crc.AddBool(IsFlammable);
    crc.AddInt(Foundation);
    crc.AddBool(IsAnimated);
    crc.AddInt(AnimationRate);
    crc.AddFloat(AnimationProbability);
}

// FUNCTION: GAMEMD 0x71E1D0
HRESULT __stdcall TerrainTypeClass::Load(IStream* pStm)
{
    HRESULT hr = MapObjTypeClassView::Load(pStm);
    if (hr >= 0) {
        new (this) TerrainTypeClass(MapObjNoInit());
        LoadFixup();
        PostLoad();
        FoundationCells = TerrainFoundationTable[Foundation];
        hr = 0;
    }
    return hr;
}

// FUNCTION: GAMEMD 0x71E240
HRESULT __stdcall TerrainTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = MapObjTypeClassView::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x71E260
HRESULT __stdcall TerrainTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = CLSID_TerrainType;
    return S_OK;
}

// FUNCTION: GAMEMD 0x71E330
int TerrainTypeClass::WhatAmI()
{
    return 0x25;
}

// FUNCTION: GAMEMD 0x71E340
int TerrainTypeClass::Size()
{
    return 0x2BC;
}

// FUNCTION: GAMEMD 0x71E350
int TerrainTypeClass::vf_16()
{
    return ArrayIndex;
}

// SYNTHETIC: GAMEMD 0x71E360 — compiler-generated scalar deleting destructor emitted for the virtual destructor.
