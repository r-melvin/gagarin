// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU217 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x6b5070-0x6b69ff,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// SmudgeTypeClass entries (layout and evidence: smudge_type_class.h).
//
// Lookup of an element index by name in a global DynamicVectorClass of
// pointers, repeated for three element types. Each record carries its name
// buffer at +0x24 (the string compare is the statically linked CRT routine
// at 0x7C8D20). The three owners are placeholders `Obj_<ADDR>`; the global
// vectors are named by retail address.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).

#include <new.h>
#include "../core/vector_add_item_free.h"
#include "terrain_objects/smudge_class.h"
#include "terrain_objects/smudge_type_class.h"

// GLOBAL: GAMEMD 0xB0B7A8 - the all-zero coordinate CreateObject creates its smudge at.
extern MapObjCoord SmudgeOriginCoord;

// GLOBAL: GAMEMD 0x7E9610 - CLSID of SmudgeTypeClass (16 bytes read from the image).
extern "C" const CLSID CLSID_SmudgeType =
    { 0x5AF2CE78, 0x0634, 0x11D2, { 0xAC, 0xA4, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5 } };

#include "../core/vector_class_operations.h"

// LIBRARY: GAMEMD 0x7C8D20 -- CRT string compare (cdecl, two pointers).
extern "C" int __cdecl FUN_007C8D20(const char* a, const char* b);

struct Obj_006B5440 {
    unsigned char unknown_00[0x24];
    char ID[1];                     // +0x24, name buffer
    static int FUN_006B5440(const char* name);
};
extern DynamicVectorClass<Obj_006B5440*> DAT_00A8EC18;

struct Obj_006CEE60 {
    unsigned char unknown_00[0x24];
    char ID[1];                     // +0x24, name buffer
    static int FUN_006CEE60(const char* name);
};
extern DynamicVectorClass<Obj_006CEE60*> DAT_00A8E330;

struct Obj_0074B640 {
    unsigned char unknown_00[0x24];
    char ID[1];                     // +0x24, name buffer
    static int FUN_0074B640(const char* name);
};
extern DynamicVectorClass<Obj_0074B640*> DAT_00A8EB28;

struct Obj_006E81D0 {
    unsigned char unknown_00[0x64];
    char ID[1];                     // +0x64, name buffer
    static Obj_006E81D0* FUN_006E81D0(const char* name);
};
extern DynamicVectorClass<Obj_006E81D0*> DAT_00A8E8D0;

struct Obj_00773030 {
    unsigned char unknown_00[0x24];
    char ID[1];                     // +0x24, name buffer
    static int FUN_00773030(const char* name);
};
extern DynamicVectorClass<Obj_00773030*> DAT_00887568;

#include "smudge_type_class_load_methods.h"
#include "../_layout/memory_buffer.h"

// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F34E8
extern const double DAT_007F34E8;
// GLOBAL: GAMEMD 0xB0B790
extern double DAT_00B0B790;

// SYNTHETIC: GAMEMD 0x6B50A0
// GLOBAL: GAMEMD 0xB0B7E0
double DAT_00B0B7E0 = DAT_00B0B790 / DAT_007F34E8;

// SYNTHETIC: GAMEMD 0x6B50C0
// GLOBAL: GAMEMD 0xB0B7C8
double DAT_00B0B7C8 = DAT_007E1718 / DAT_00B0B7E0;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B5260
// MATCHED 100%: the registry append is the free DynamicVectorAddItemFree form. Historical note: retail loads Count then Capacity (EAX, ECX) for the inlined AddItem, the member compiled
// Capacity first; the early-return and Count-first AddItem shapes tried fall to 94.5% / 57.0%.
// The canonical DynamicVectorClass<SmudgeTypeClass*> with an inline AddItem was also tried and is
// worse: nested early-out ifs 45.2%, one short-circuit condition 45.2%, and that condition storing
// through an inline operator[] 94.5% (both CapacityIncrement + Capacity operand orders). The
// terrain-module vector model stays.
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
    DynamicVectorAddItemFree(&SmudgeTypeArray, this);
    ArrayIndex = SmudgeTypeArray.FindIndex(this);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x006B5440
int Obj_006B5440::FUN_006B5440(const char* name)
{
    if (name != 0) {
        for (int i = 0; i < DAT_00A8EC18.Count; ++i) {
            if (FUN_007C8D20(DAT_00A8EC18.Items[i]->ID, name) == 0)
                return i;
        }
    }
    return -1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B5490
//
// Load the theater-specific smudge art. For every smudge type flagged as
// theater-dependent, the file name is the type's ID with the theater's
// extension, opened as a stack file object whose whole contents become the
// type's image. The file object is torn down inline: this class's vtable, the
// +0x64 reset, the +0x58 sub-object release, the base vtable, the base
// destructor.
void SmudgeTypeClass::LoadFromIniList(int idxTheater)
{
    for (int i = 0; i < DAT_00A8EC28; ++i) {
        SmudgeTypeClass* type = DAT_00A8EC1C[i];
        if (type->Theater) {
            char path[0x200];
            _makepath(path, 0, 0, type->ID, DAT_007E1B78[idxTheater].Extension);

            File_006B5490 file;
            file.FUN_004739F0(path);
            type->Image = file.ReadWholeFile();

            file.Vtbl    = &VT_007E16B0;
            file.Reset64 = 0;
            ((MemoryBuffer*)file.Sub58)->Clear();
            file.Vtbl    = &VT_007E1668;
            FUN_00431B80(&file);
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B5550
bool SmudgeTypeClass::vf_32(const MapObjCell* cell, MapObjHouseView* house)
{
    if (new SmudgeClass(this, MapObjCoord(cell->X * 256 + 128, cell->Y * 256 + 128, 0), -1))
        return true;
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B55C0
void* SmudgeTypeClass::vf_35(MapObjHouseView* house)
{
    return new SmudgeClass(this, SmudgeOriginCoord, -1);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B55F0
// PARTIAL 76.2%, multiset identical. The zero arguments come from two zeroed registers because the
// drawer's trailing offset is a point by value; retail zeroes EDX/ECX where cl picks ECX/EAX, and
// the light and height pushes are scheduled differently.
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
                        -1 - MapObjHeightScale(height), 0, mapCell->Light, 0, 0, 0, MapObjPoint(0, 0));
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B58B0
HRESULT __stdcall SmudgeTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = MapObjTypeClassView::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B58D0
HRESULT __stdcall SmudgeTypeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = CLSID_SmudgeType;
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B6130
int SmudgeTypeClass::WhatAmI()
{
    return 0x1E;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B6140
int SmudgeTypeClass::Size()
{
    return 0x2A4;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B6150
int SmudgeTypeClass::vf_16()
{
    return ArrayIndex;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x6B6160 — compiler-generated scalar deleting destructor emitted for the virtual destructor.
