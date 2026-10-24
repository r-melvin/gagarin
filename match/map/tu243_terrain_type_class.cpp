// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU243 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x71d390-0x71e40f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//
// TerrainTypeClass entries (layout and evidence: terrain_type_class.h).
//
//   0x71E2A0 / 0x75E3B0.
//
// Four instantiations of one lookup-or-create template, the callees the
// RulesClass INI list-parsers invoke per key. Each rejects the two "no type"
// literals, scans the type array by ID, and otherwise allocates and constructs.
// Written out four times rather than macro-generated so each carries its own
// addresses and asserts.
//
// Two constructs are load-bearing and both cost the entire match if missed:
//
//  * The constructors are declared `throw()`. `new T(id)` with a
//    potentially-throwing constructor makes VC6 emit an SEH frame
//    (`PUSH -1; PUSH 0; MOV EAX,FS:[0]`) so operator delete can run on unwind;
//    retail has no such frame. Without `throw()`: 3.8%.
//
//  * The array element is *recomputed* at both uses rather than bound to a
//    local. Binding it costs a third callee-saved register (retail saves ESI
//    and EDI only) and shifts every push: 14.5%. Retail reloads the Items base
//    inside the loop and again on the found path, which is what the repeated
//    subscript produces.

#include <new.h>
#include <stdlib.h>
#include "terrain_objects/terrain_type_class.h"
#include "terrain_objects/terrain_class.h"
#include "../_layout/obj_004a1d30.h"
#include "../platform/ccini_class_methods.h"
#include "../ui/shape_header.h"
#include "../core/scenario_class_methods.h"
// GLOBAL: GAMEMD 0x887180
extern CCINIClass DAT_00887180;

// GLOBAL: GAMEMD 0x7E95E0 - CLSID of TerrainTypeClass (16 bytes read from the image).
extern "C" const CLSID CLSID_TerrainType =
    { 0x5AF2CE7B, 0x0634, 0x11D2, { 0xAC, 0xA4, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5 } };

#include "../core/type_class_findoralloc_methods.h"

//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"





// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F5418
extern const double DAT_007F5418;
// GLOBAL: GAMEMD 0xB0ED80
extern double DAT_00B0ED80;

// SYNTHETIC: GAMEMD 0x71D3C0
// GLOBAL: GAMEMD 0xB0F140
double DAT_00B0F140 = DAT_00B0ED80 / DAT_007F5418;

// SYNTHETIC: GAMEMD 0x71D3E0
// GLOBAL: GAMEMD 0xB0EDB8
double DAT_00B0EDB8 = DAT_007E1718 / DAT_00B0F140;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71DA80
// MATCHED (second look): the array append is the same inlined expansion the OverlayTypeClass
// constructor uses (AddItemEarlyOut: Capacity held in a local across the growth tests, the
// element stored through an index local), not the `T* slot = &Items[Count++]` shape.
TerrainTypeClass::TerrainTypeClass(const char* id) throw()
    : ObjectTypeClass(id), ArrayIndex(-1), Foundation(0), RadarColor(0, 0, 0), AnimationRate(0),
      AnimationProbability(0),
      TemperateOccupationBits(7), SnowOccupationBits(7), WaterBound(false), SpawnsTiberium(false),
      IsFlammable(false), IsAnimated(false), IsVeinhole(false), FoundationCells(0)
{
    AbstractClass::vf_rtti_5();
    Selectable = false;
    IsLogic = true;
    RadarInvisible = true;
    LegalTarget = false;
    Insignificant = true;
    TerrainTypeArray.AddItemEarlyOut(this);
    ArrayIndex = TerrainTypeArray.FindIndex(this);
    Strength = -1;
    Armor = 6;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71DDD0
bool TerrainTypeClass::vf_32(const CellStruct* cell, HouseClass* house)
{
    if (new TerrainClass(this, cell))
        return true;
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71DE10
void* TerrainTypeClass::vf_35(void* house)
{
    return new TerrainClass(this, &TerrainDefaultCell);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71DE40
// The empty cell list: a function-local static {0x7FFF, 0x7FFF} (guard bit in 0xB0ED60, object at
// 0xB0ED78); its atexit stub is the bare RET at 0x71DE90 (compiler output, outside this partition). The
// The shared Cell value initializes through its two-word temporary and copies the four-byte result.
void* TerrainTypeClass::vf_36(int arg)
{
    if (FoundationCells == 0) {
        static Cell invalidCell = Cell(0x7FFF, 0x7FFF);
        return &invalidCell;
    }
    return FoundationCells;
}

// SYNTHETIC: GAMEMD 0x71DE90
// Compiler cleanup for vf_36's canonical Cell sentinel.

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71DEA0
bool TerrainTypeClass::vf_25(CCINIClass* ini)
{
    ini->Reset();
    if (ObjectTypeClass::vf_25(ini)) {
        if (Strength == -1)
            Strength = MapObjRules->unknown_1144;
        IsVeinhole = ini->FUN_005295F0(ID, "IsVeinhole", IsVeinhole);
        if (IsVeinhole) {
            IsLogic = false;
            LegalTarget = true;
        }
        WaterBound = ini->FUN_005295F0(ID, "WaterBound", WaterBound);
        SpawnsTiberium = ini->FUN_005295F0(ID, "SpawnsTiberium", SpawnsTiberium);
        IsFlammable = ini->FUN_005295F0(ID, "IsFlammable", IsFlammable);
        Foundation = DAT_00887180.ReadFoundation(ImageFile, "Foundation", Foundation);
        FoundationCells = TerrainFoundationTable[Foundation];
        if (!Theater) {
            char path[0x200];
            _makepath(path, 0, 0, ImageFile, ".SHP");
            Image = MapObjLoadShape(path, false);
        }
        ShapeHeader* shape = static_cast<ShapeHeader*>(vf_39());
        if (shape != 0)
            RadarColor = shape->GetRadarColor(0);
        RadarColor = ini->Read3Bytes(ID, "RadarColor", RadarColor);
        IsAnimated = ini->FUN_005295F0(ID, "IsAnimated", IsAnimated);
        AnimationRate = ini->FUN_005276D0(ID, "AnimationRate", AnimationRate);
        AnimationProbability = (float)ini->FUN_005283D0(ID, "AnimationProbability", AnimationProbability);
        TemperateOccupationBits = ini->FUN_005276D0(ID, "TemperateOccupationBits", TemperateOccupationBits);
        SnowOccupationBits = ini->FUN_005276D0(ID, "SnowOccupationBits", SnowOccupationBits);
        return true;
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71E0D0
CoordStruct TerrainTypeClass::vf_27(const CoordStruct& coord)
{
    CoordStruct c = coord;
    c.Z = c.Z >= MapInstance.FUN_00578080(&c) ? c.Z : MapInstance.FUN_00578080(&c);
    return c;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71E140
void TerrainTypeClass::vf_13(Obj_004A1D30* crc)
{
    AbstractTypeClass::vf_13(crc);
    crc->FUN_004A1D50(ArrayIndex);
    crc->FUN_004A1CA0(WaterBound);
    crc->FUN_004A1CA0(SpawnsTiberium);
    crc->FUN_004A1CA0(IsFlammable);
    crc->FUN_004A1D50(Foundation);
    crc->FUN_004A1CA0(IsAnimated);
    crc->FUN_004A1D50(AnimationRate);
    crc->FUN_004A1D70(AnimationProbability);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71E1D0
HRESULT __stdcall TerrainTypeClass::Load(IStream* pStm)
{
    HRESULT hr = ObjectTypeClass::Load(pStm);
    if (hr >= 0) {
        new (this) TerrainTypeClass(AbstractNoInit());
        FUN_005F8110();
        FUN_005F9070();
        FoundationCells = TerrainFoundationTable[Foundation];
        hr = 0;
    }
    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71E240
HRESULT __stdcall TerrainTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = ObjectTypeClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71E260
HRESULT __stdcall TerrainTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = CLSID_TerrainType;
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71E2A0  TerrainTypeClass::FindOrAllocate (__fastcall)
TerrainTypeClass* TerrainTypeClass::FindOrAllocate(const char* id)
{
    if (_stricmp("<none>", id) == 0)
        return 0;

    if (_stricmp("none", id) == 0)
        return 0;

    for (int i = 0; i < TerrainTypeClassArray.Count; i++) {
        if (_stricmp(((TerrainTypeClass**)TerrainTypeClassArray.Items)[i]->ID, id) == 0)
            return ((TerrainTypeClass**)TerrainTypeClassArray.Items)[i];
    }

    return new TerrainTypeClass(id);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71E330
int TerrainTypeClass::vf_11()
{
    return 0x25;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71E340
int TerrainTypeClass::vf_12()
{
    return 0x2BC;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x71E350
int TerrainTypeClass::vf_16()
{
    return ArrayIndex;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x71E360 — compiler-generated scalar deleting destructor emitted for the virtual destructor.
