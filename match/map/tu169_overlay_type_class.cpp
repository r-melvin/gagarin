// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU169 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x5fe060-0x5fefbf,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//
// OverlayTypeClass entries (layout and evidence: overlay_type_class.h).
//
//             private-ref-cross-check
//   0x5FE570. See the header for the RTTI derivation of the class identity.
//
//   GLOBAL:   GAMEMD 0xA83D80  OverlayTypeClass::Array
//   LIBRARY: GAMEMD 0x7C9FF0  CRT _makepath         (referenced; reloc)
//   LIBRARY:  GAMEMD 0x7C8B3D  game-heap free        (referenced; reloc)
//   GLOBAL:   GAMEMD 0xAC1608  default CellStruct for CreateObject
//   GLOBAL:   GAMEMD 0x7E1B78  the theater table
//   GLOBAL:   GAMEMD 0xA83D84  OverlayTypeClass::Array.Items
//   GLOBAL:   GAMEMD 0xA83D90  OverlayTypeClass::Array.Count
//   STRING:   GAMEMD 0x81834C  ".SHP"
// VC6FLAGS: /nologo /c /O2 /Gr /GR /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).

#include <new.h>
#include "../_layout/swizzle_manager_class.h"
#include "terrain_objects/overlay_type_class.h"
#include "terrain_objects/overlay_class.h"

// GLOBAL: GAMEMD 0x7E9600 - CLSID of OverlayTypeClass (16 bytes read from the image).
extern "C" const CLSID CLSID_OverlayType =
    { 0x5AF2CE79, 0x0634, 0x11D2, { 0xAC, 0xA4, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5 } };

#include "overlay_type_class_methods.h"

//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"


void __cdecl FUN_005FE520();


// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EF5C0
extern const double DAT_007EF5C0;
// GLOBAL: GAMEMD 0xAC1610
extern double DAT_00AC1610;

// SYNTHETIC: GAMEMD 0x5FE090
// GLOBAL: GAMEMD 0xAC1668
double DAT_00AC1668 = DAT_00AC1610 / DAT_007EF5C0;

// SYNTHETIC: GAMEMD 0x5FE0B0
// GLOBAL: GAMEMD 0xAC1650
double DAT_00AC1650 = DAT_007E1718 / DAT_00AC1668;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FE470  OverlayTypeClass::FindIndex (__fastcall)
// Index of the overlay type whose INI ID matches `pID` case-insensitively, or
// -1 when `pID` is null or nothing matches.
//
// Two details come from the bytes rather than from what the code ought to do:
// the count is re-loaded from the global at the top of every iteration (so it
// is read through the array object, not hoisted into a local), and the
// candidate's ID is the *first* _stricmp argument while the array walk in the
// sibling VocClass::FindIndex passes the needle first.
int OverlayTypeClass::FindIndex(const char* pID)
{
    if (pID)
    {
        for (int i = 0; i < OverlayTypeClass_Array.Count; ++i)
        {
            // The element must be subscripted inside the call rather than bound
            // to a named pointer first: naming it costs the ECX/EAX colouring of
            // the element load and holds at 90%. This is the mirror of the
            // named-element-pointer lever banked for search loops — here the
            // element feeds a call argument, not a comparison.
            if (gg_overlay_stricmp(
                    ((OverlayTypeClass**)OverlayTypeClass_Array.Items)[i]->ID,
                    pID) == 0)
                return i;
        }
    }

    return -1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FE4C0
// The function-local static (guard bit 0 of 0xAC15E8, cells at 0xAC1640 / 0xAC1644) is built through
// temporaries; its destructor stub is the bare RET at 0x5FE520 (compiler-generated atexit entry).
CellStruct* OverlayTypeClass::vf_36(int arg)
{
    static OverlayStaticCell list[2] = { OverlayMakeStaticCell(0, 0), OverlayMakeStaticCell(0x7FFF, 0x7FFF) };
    return list;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FE520
// Empty function.
void __cdecl FUN_005FE520()
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FE570
// MIGRATED from match/map/overlay_type_class_methods.cpp (OverlayTypeClass::CreateObject); the
// integrator retires the old row. Builds one unplaced overlay on the zero cell; the house is ignored.
void* OverlayTypeClass::vf_35(MapObjHouseView* owner)
{
    return new OverlayClass(this, OverlayZeroCell, -1);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FE5A0
// PARTIAL 26.2%. The zero arguments now come from two zeroed registers as in retail (the drawer's
// trailing offset is a point by value). Remaining: retail keeps `where` in EDI and calls vf_39 inside
// the argument pushes; through the inline drawer wrapper cl hoists the call, and through the plain
// declaration (16.7%) it does not keep `where` in a register.
void OverlayTypeClass::vf_40(MapObjPoint* where, MapObjRect* clip, int frame)
{
    MapObjPoint point;
    point.X = where->X + MapObjClipRect.X;
    point.Y = where->Y + MapObjClipRect.Y;
    point.X += 0x1E;
    point.Y += 0xF;
    OverlayDrawShapeInline(MapObjSurface, OverlayDrawContext, vf_39(), frame, &point, clip, 0x600, 0, 0,
                           0, 1000, 0, 0, 0, MapObjPoint(0, 0));
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FE620  OverlayTypeClass::LoadArt (__fastcall)
//
// Bring every overlay type's artwork into line with the theater being entered.
// A theater-specific type takes the theater's own file extension; a new-theater
// type keeps the .SHP extension and has the theater letter stamped into the
// second character of its name, falling back to the generic 'G' art when the
// theater-specific file is missing. Types whose art is supplied elsewhere are
// skipped on the way in and have their owned image released on the way out.
void OverlayTypeClass::LoadArt(int idxTheater)
{
    char path[0x200];

    for (int i = 0; i < DAT_00A83D90; ++i)
    {
        OverlayTypeClass* type = DAT_00A83D84[i];

        if (type->unknown_2AF == 0)
        {
            if (type->Theater != 0)
            {
                _makepath(path, 0, 0, type->ImageFile,
                          DAT_007E1B78[idxTheater].Extension);

                // Each arm's first load is bound to its own named local. With
                // the null test re-reading `type->Image` instead, cl recognises
                // the two load-and-retry blocks as identical and cross-jumps
                // the second into the first, which retail's build did not do.
                Image_005FE620* image = FUN_005B40B0(path, 1);
                type->Image = image;
                if (image == 0)
                {
                    FUN_005F9710(path);
                    type->Image = FUN_005B40B0(path, 1);
                }
            }
            else if (type->NewTheater != 0)
            {
                _makepath(path, 0, 0, type->ImageFile, STR_0081834C);
                FUN_005F96B0(path, idxTheater);

                Image_005FE620* themedImage = FUN_005B40B0(path, 1);
                type->Image = themedImage;
                if (themedImage == 0)
                {
                    FUN_005F9710(path);
                    type->Image = FUN_005B40B0(path, 1);
                }
            }
        }
        else if ((type->Theater != 0 || type->NewTheater != 0)
                 && type->Image != 0 && type->ImageAllocated != 0)
        {
            operator delete(type->Image);
            type->Image = 0;
            type->ImageAllocated = 0;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FEA30
MapObjCoord* OverlayTypeClass::vf_27(MapObjCoord* out, const MapObjCoord* in)
{
    *out = *in;
    return out;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FEAF0
HRESULT __stdcall OverlayTypeClass::Load(IStream* pStm)
{
    HRESULT hr = MapObjTypeClassView::Load(pStm);
    if (hr >= 0) {
        new (this) OverlayTypeClass(MapObjNoInit());
        LoadFixup();
        PostLoad();
        DAT_00B0C110.SwizzleManagerClass::vf_4(&CellAnim);
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FEC10
HRESULT __stdcall OverlayTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = MapObjTypeClassView::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FEC30
HRESULT __stdcall OverlayTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = CLSID_OverlayType;
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FEF00
int OverlayTypeClass::WhatAmI()
{
    return 0x15;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FEF10
int OverlayTypeClass::Size()
{
    return 0x2BC;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5FEF20
int OverlayTypeClass::vf_16()
{
    return ArrayIndex;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x5FEF30 — compiler-generated scalar deleting destructor emitted for the virtual destructor.

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA83D90
int DAT_00A83D90;
// GLOBAL: GAMEMD 0xAC1608
MapObjCell OverlayZeroCell;
// GLOBAL: GAMEMD 0x7EF5C0
extern const double DAT_007EF5C0 = 60.0;
// GLOBAL: GAMEMD 0x818668
extern const char OverlayDemandLoadFormat[] = "Demand loading image for %s\n";
// GLOBAL: GAMEMD 0x887180
MapObjIniView MapObjArtIni;
// END defined globals
