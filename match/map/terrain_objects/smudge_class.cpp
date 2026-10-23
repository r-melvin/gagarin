// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
//
// SmudgeClass entries (layout and evidence: smudge_class.h).

#include <new.h>
#include "smudge_class.h"
#include "smudge_type_class.h"

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

// FUNCTION: GAMEMD 0x6B4F00
HRESULT __stdcall SmudgeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    return MapObjClassView::Save(pStm, fClearDirty);
}

// FUNCTION: GAMEMD 0x6B4F20
MapObjTypeClassView* SmudgeClass::GetType()
{
    return Type;
}

// FUNCTION: GAMEMD 0x6B4F30
int SmudgeClass::Size()
{
    return 0xB0;
}

// FUNCTION: GAMEMD 0x6B4F40
int SmudgeClass::WhatAmI()
{
    return 0x1D;
}

// GLOBAL: GAMEMD 0x7E9690 - CLSID of SmudgeClass (16 bytes read from the image).
extern "C" const CLSID CLSID_Smudge =
    { 0x0E272DC5, 0x9C0F, 0x11D1, { 0xB7, 0x09, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1 } };

// FUNCTION: GAMEMD 0x6B4F50
HRESULT __stdcall SmudgeClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = CLSID_Smudge;
    return S_OK;
}

// FUNCTION: GAMEMD 0x6B4F90
void SmudgeClass::vf_69(MapObjPoint* where, MapObjRect* clip)
{
}

// SYNTHETIC: GAMEMD 0x6B4FA0 — compiler-generated scalar deleting destructor emitted for the virtual destructor.
