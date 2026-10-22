// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
//
// OverlayTypeClass entries (layout and evidence: overlay_type_class.h).

#include <new.h>
#include "overlay_type_class.h"
#include "overlay_class.h"

// FUNCTION: GAMEMD 0x5FE250
OverlayTypeClass::OverlayTypeClass(const char* id)
    : MapObjTypeClassView(id), DamageLevels(1), Strength(1), NoUseTileLandType(true), DrawFlat(true),
      ArrayIndex(-1), Land(0), CellAnim(0), Wall(false), Tiberium(false), Crate(false),
      CrateTrigger(false), IsVeinholeMonster(false), IsVeins(false), unknown_2AF(false),
      Explodes(false), ChainReaction(false), Overrides(false), IsRubble(false), IsARock(false),
      RadarColor(0, 0, 0)
{
    MapObjRttiBase::Create_ID();
    unknown_22F = 1;
    unknown_230 = 0;
    unknown_232 = 1;
    unknown_235 = 0;
    OverlayTypeArray.AddItemEarlyOut(this);
    ArrayIndex = OverlayTypeArray.FindIndex(this);
}

// FUNCTION: GAMEMD 0x5FE4C0
// The function-local static (guard bit 0 of 0xAC15E8, cells at 0xAC1640 / 0xAC1644) is built through
// temporaries; its destructor stub is the bare RET at 0x5FE520 (compiler-generated atexit entry).
MapObjCell* OverlayTypeClass::vf_36(int arg)
{
    static OverlayStaticCell list[2] = { OverlayMakeStaticCell(0, 0), OverlayMakeStaticCell(0x7FFF, 0x7FFF) };
    return list;
}

// FUNCTION: GAMEMD 0x5FE530
// MIGRATED from match/map/overlay_type_class_methods.cpp (OverlayTypeClass::SpawnAtMapCoords); the
// integrator retires the old row. The owning house is accepted and ignored (overlays have no owner).
bool OverlayTypeClass::vf_32(const MapObjCell* where, MapObjHouseView* owner)
{
    if (new OverlayClass(this, *where, -1))
    {
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x5FE570
// MIGRATED from match/map/overlay_type_class_methods.cpp (OverlayTypeClass::CreateObject); the
// integrator retires the old row. Builds one unplaced overlay on the zero cell; the house is ignored.
void* OverlayTypeClass::vf_35(MapObjHouseView* owner)
{
    return new OverlayClass(this, OverlayZeroCell, -1);
}

// FUNCTION: GAMEMD 0x5FE5A0
// CAPPED at 9.5% (38 of 42 instructions; retail-only: 2 `xor`, `push edi`, `pop edi`). Retail pushes the
// eight zero arguments through EDX/EAX (`XOR EDX,EDX; XOR EAX,EAX`) and enregisters `where` in EDI, cl
// 8804 pushes immediate 0s (recorded 8447-vs-8804 constant-materialisation class). Variants tried: one
// expression per coordinate (7.1%), locals for the two screen offsets (7.1%), a struct copy of the
// offset (2.4%), the inline drawer wrapper with split adds (9.5%, kept).
void OverlayTypeClass::vf_40(MapObjPoint* where, MapObjRect* clip, int frame)
{
    MapObjPoint point;
    point.X = where->X + MapObjClipRect.X;
    point.Y = where->Y + MapObjClipRect.Y;
    point.X += 0x1E;
    point.Y += 0xF;
    OverlayDrawShapeInline(MapObjSurface, OverlayDrawContext, vf_39(), frame, &point, clip, 0x600, 0, 0,
                           0, 1000, 0, 0, 0, 0, 0);
}

// FUNCTION: GAMEMD 0x5FE770
bool OverlayTypeClass::ReadINI(MapObjIniView* ini)
{
    ini->ClearCache();
    if (MapObjTypeClassView::ReadINI(ini)) {

        Land = ini->ReadEnum(ID, "Land", Land);
        Strength = ini->ReadInt(ID, "Strength", Strength);
        Wall = ini->ReadBool(ID, "Wall", Wall);
        Tiberium = ini->ReadBool(ID, "Tiberium", Tiberium);
        Crate = ini->ReadBool(ID, "Crate", Crate);
        CrateTrigger = ini->ReadBool(ID, "CrateTrigger", CrateTrigger);
        Explodes = ini->ReadBool(ID, "Explodes", Explodes);
        Overrides = ini->ReadBool(ID, "Overrides", Overrides);

        char animName[0x80];
        MapObjTypeClassView* oldAnim = CellAnim;
        CellAnim = ini->ReadString(ID, "CellAnim", OverlayEmptyText, animName, 0x80)
                       ? OverlayFindAnimType(animName) : oldAnim;

        DamageLevels = MapObjArtIni.ReadInt(ImageFile, "DamageLevels", DamageLevels);

        if (Tiberium) {
            unknown_9C = 6;
            if (Land == 0)
                Land = 5;
        }

        if (!Theater && !unknown_2AF) {
            char path[0x200];
            _makepath(path, 0, 0, ImageFile, OverlayShpExtension);
            Image = MapObjLoadShape(path, 1);
        }

        RadarColor = ini->ReadColor(ID, "RadarColor", RadarColor);
        NoUseTileLandType = ini->ReadBool(ID, "NoUseTileLandType", NoUseTileLandType);
        IsVeinholeMonster = ini->ReadBool(ID, "IsVeinholeMonster", IsVeinholeMonster);
        IsVeins = ini->ReadBool(ID, "IsVeins", IsVeins);
        ChainReaction = ini->ReadBool(ID, "ChainReaction", ChainReaction);
        DrawFlat = ini->ReadBool(ID, "DrawFlat", DrawFlat);
        IsARock = ini->ReadBool(ID, "IsARock", IsARock);
        IsRubble = ini->ReadBool(ID, "IsRubble", IsRubble);
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x5FEA30
MapObjCoord* OverlayTypeClass::vf_27(MapObjCoord* out, const MapObjCoord* in)
{
    *out = *in;
    return out;
}

// FUNCTION: GAMEMD 0x5FEA50
void OverlayTypeClass::ComputeCRC(MapObjCrcView& crc)
{
    MapObjTypeClassView::ComputeCRC(crc);
    crc.AddInt(ArrayIndex);
    crc.AddInt(Land);
    crc.AddInt(DamageLevels);
    crc.AddInt(Strength);
    crc.AddBool(Wall);
    crc.AddBool(Tiberium);
    crc.AddBool(Crate);
    crc.AddBool(CrateTrigger);
    crc.AddBool(Explodes);
}

// FUNCTION: GAMEMD 0x5FEAF0
HRESULT __stdcall OverlayTypeClass::Load(IStream* pStm)
{
    HRESULT hr = MapObjTypeClassView::Load(pStm);
    if (hr >= 0) {
        new (this) OverlayTypeClass(MapObjNoInit());
        LoadFixup();
        PostLoad();
        MapObjSwizzle.Swizzle((void**)&CellAnim);
        if (!unknown_2AF) {
            char path[0x200];
            if (Theater) {
                _makepath(path, 0, 0, ImageFile, MapObjTheaters[MapObjScenario->TheaterIndex].Extension);
            } else {
                _makepath(path, 0, 0, ImageFile, OverlayShpExtension);
                OverlayStampTheater(path, MapObjScenario->TheaterIndex);
            }
            if (Image == 0)
                Image = MapObjLoadShape(path, 1);
        }
        hr = 0;
    }
    return hr;
}

// FUNCTION: GAMEMD 0x5FEC10
HRESULT __stdcall OverlayTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = MapObjTypeClassView::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// GLOBAL: GAMEMD 0x7E9600 - CLSID of OverlayTypeClass (16 bytes read from the image).
extern "C" const CLSID CLSID_OverlayType =
    { 0x5AF2CE79, 0x0634, 0x11D2, { 0xAC, 0xA4, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5 } };

// FUNCTION: GAMEMD 0x5FEC30
HRESULT __stdcall OverlayTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = CLSID_OverlayType;
    return S_OK;
}

// FUNCTION: GAMEMD 0x5FEDE0
void* OverlayTypeClass::vf_39()
{
    void* image = Image;
    if (image == 0 && unknown_2AF) {
        OverlayTrace(OverlayDemandLoadFormat, Name);
        char path[0x200];
        if (Theater) {
            _makepath(path, 0, 0, ImageFile, MapObjTheaters[MapObjScenario->TheaterIndex].Extension);
        } else if (NewTheater) {
            _makepath(path, 0, 0, ImageFile, OverlayShpExtension);
            OverlayStampTheater(path, MapObjScenario->TheaterIndex);
        }
        OverlayFileView file(path);
        image = file.ReadShape();
        Image = image;
        if (image)
            ImageAllocated = 1;
    }
    return image;
}

// FUNCTION: GAMEMD 0x5FEF00
int OverlayTypeClass::WhatAmI()
{
    return 0x15;
}

// FUNCTION: GAMEMD 0x5FEF10
int OverlayTypeClass::Size()
{
    return 0x2BC;
}

// FUNCTION: GAMEMD 0x5FEF20
int OverlayTypeClass::vf_16()
{
    return ArrayIndex;
}

// SYNTHETIC: GAMEMD 0x5FEF30 — compiler-generated scalar deleting destructor emitted for the virtual destructor.
