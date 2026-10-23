// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU216 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x6b4840-0x6b506f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//
// SmudgeClass entries (layout and evidence: smudge_class.h).

#include <new.h>
#include "terrain_objects/smudge_class.h"
#include "terrain_objects/smudge_type_class.h"

// GLOBAL: GAMEMD 0x7E9690 - CLSID of SmudgeClass (16 bytes read from the image).
extern "C" const CLSID CLSID_Smudge =
    { 0x0E272DC5, 0x9C0F, 0x11D1, { 0xB7, 0x09, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1 } };

//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"


void __stdcall FUN_006B4C70(int a1);


// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F32B8
extern const double DAT_007F32B8;
// GLOBAL: GAMEMD 0xB0B710
extern double DAT_00B0B710;

// SYNTHETIC: GAMEMD 0x6B4870
// GLOBAL: GAMEMD 0xB0B760
double DAT_00B0B760 = DAT_00B0B710 / DAT_007F32B8;

// SYNTHETIC: GAMEMD 0x6B4890
// GLOBAL: GAMEMD 0xB0B748
double DAT_00B0B748 = DAT_007E1718 / DAT_00B0B760;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B4A50
SmudgeClass::SmudgeClass(SmudgeTypeClass* type, const MapObjCoord& coord, int arg3) : Type(type)
{
    MapObjRttiBase::Create_ID();
    SmudgeArray.AddItem(this);

    if (coord.X != SmudgeEmptyCoord.X || coord.Y != SmudgeEmptyCoord.Y || coord.Z != SmudgeEmptyCoord.Z) {
        SmudgeCreateArg = arg3;
        if (!Unlimbo(&coord, 0)) {
            UnInit();
            return;
        }
        SmudgeCreateArg = -1;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B4BE0
// CAPPED at 82.4%: retail stores the copied cell (`MOV EAX,[EAX]; MOV [ESP+0x10],EAX`) before it reads
// the MapObjMarkGate global and keeps it in EAX; every variant tried (copy-initialised, assigned,
// copy-constructed, address held in a pointer, goto / flag / inline-predicate shapes of the condition)
// compiles the store after the global load with the copy in EDX, and the two `&cell` temporaries then
// take ECX/EAX instead of EDX/EAX. Same instruction multiset otherwise.
bool SmudgeClass::Mark(int arg)
{
    if (MapObjClassView::Mark(arg)) {
        if (arg == 1 || arg == 3) {
            MapObjCell cell;
            cell = *vf_110(MapObjCell().Address());
            if (MapObjMarkGate > 0 || MapObjMarkGateFlag || Type->Method_6B5F80(&cell, true))
                Type->Method_6B6080(&cell);
            unknown_74 = 0;
            UnInit();
            return true;
        }
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B4C70
// Empty function that pops its stack arguments.
void __stdcall FUN_006B4C70(int a1)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B4EA0
HRESULT __stdcall SmudgeClass::Load(IStream* pStm)
{
    HRESULT hr = MapObjClassView::Load(pStm);
    if (hr >= 0) {
        new (this) SmudgeClass(MapObjNoInit());
        MapObjSwizzle.Swizzle((void**)&Type);
    }
    return hr;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B4F00
HRESULT __stdcall SmudgeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    return MapObjClassView::Save(pStm, fClearDirty);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B4F20
MapObjTypeClassView* SmudgeClass::GetType()
{
    return Type;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B4F30
int SmudgeClass::Size()
{
    return 0xB0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B4F40
int SmudgeClass::WhatAmI()
{
    return 0x1D;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B4F50
HRESULT __stdcall SmudgeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = CLSID_Smudge;
    return S_OK;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6B4F90
void SmudgeClass::vf_69(MapObjPoint* where, MapObjRect* clip)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x6B4FA0 — compiler-generated scalar deleting destructor emitted for the virtual destructor.
