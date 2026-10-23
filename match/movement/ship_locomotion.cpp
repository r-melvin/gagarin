// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2
//
// ShipLocomotionClass (layout and tables in _layout/ship_locomotion_class.h).
// The constructor and the COM / IPiggyback bodies below are the same shapes as
// DriveLocomotionClass's (movement/drive_locomotion.cpp), compiled against
// Ship's own file-scope empty coordinate and tables. Defining the constructor
// makes VC6 emit Ship's three tables here, and with them the ILocomotion (+4)
// and IPiggyback (+0x18) adjustor thunks.
//
// The destructor body 0x69ECF0 stays scored by ComRel_0069ECF0
// (match/core/multi_vtable_dtor_family_methods.cpp).

#include <new.h>
#include "../_layout/ship_locomotion_class.h"

// GLOBAL: GAMEMD 0xB077F8 - the empty coordinate this TU compares against
// (three dwords, read by the constructor at 0x69EC72..0x69EC83).
extern "C" LocoCoord DAT_00B077F8;

// LIBRARY: OLE32!OleLoadFromStream, IAT 0x7E15F8 (declared by <ole2.h>).

// FUNCTION: GAMEMD 0x69EC50
ShipLocomotionClass::ShipLocomotionClass()
    : unknown_1C(0), unknown_20(0), SlopeTimer(0),
      DestCoord(DAT_00B077F8), HeadTo(DAT_00B077F8),
      SpeedAccum(0), unknown_50(0.0), TrackNumber(-1), TrackIndex(-1),
      unknown_60(false), unknown_61(false), unknown_62(false),
      unknown_63(false), unknown_64(false), UnLocked(true), Piggybackee(0)
{
}

// FUNCTION: GAMEMD 0x69ED20
HRESULT __stdcall ShipLocomotionClass::PiggybackCLSID(CLSID* out)
{
    if (!out)
        return E_POINTER;
    if (Piggybackee) {
        IPersistPtr persist(Piggybackee);
        if (persist == 0)
            return E_FAIL;
        return persist->GetClassID(out);
    }
    IPersistPtr persist(static_cast<LocomotionClass*>(this));
    if (persist == 0)
        return E_FAIL;
    return persist->GetClassID(out);
}

// FUNCTION: GAMEMD 0x69EE30
HRESULT __stdcall ShipLocomotionClass::QueryInterface(REFIID riid, void** ppv)
{
    HRESULT hr = LocomotionClass::QueryInterface(riid, ppv);
    if (hr == E_NOINTERFACE) {
        if (riid == IID_IPiggyback)
            *ppv = static_cast<IPiggyback*>(this);
        if (*ppv == 0)
            return E_NOINTERFACE;
        AddRef();
        hr = S_OK;
    }
    return hr;
}

// FUNCTION: GAMEMD 0x69EE90
HRESULT __stdcall ShipLocomotionClass::Load(IStream* pStm)
{
    HRESULT hr = LocomotionClass::Load(pStm);
    if (hr >= 0) {
        new (this) ShipLocomotionClass(0);
        bool hasPiggyback;
        pStm->Read(&hasPiggyback, 1, 0);
        if (hasPiggyback)
            hr = OleLoadFromStream(pStm, IID_ILocomotion, (void**)&Piggybackee);
    }
    return hr;
}

// FUNCTION: GAMEMD 0x69EFF0
HRESULT __stdcall ShipLocomotionClass::BeginPiggyback(ILocomotion* loco)
{
    if (!loco)
        return E_POINTER;
    if (Piggybackee == 0) {
        Piggybackee = loco;
        return S_OK;
    }
    return E_FAIL;
}

// FUNCTION: GAMEMD 0x69F040
HRESULT __stdcall ShipLocomotionClass::EndPiggyback(ILocomotion** out)
{
    if (!out)
        return E_POINTER;
    if (Piggybackee) {
        *out = Piggybackee;
        Piggybackee.Detach();
        return S_OK;
    }
    return S_FALSE;
}

// SYNTHETIC: GAMEMD 0x6A4300 -- compiler-generated ILocomotion QI adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x6A4310 -- compiler-generated ILocomotion AddRef adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x6A4320 -- compiler-generated ILocomotion Release adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x6A4330 -- compiler-generated IPiggyback QI adjustor thunk (this -= 0x18).
// SYNTHETIC: GAMEMD 0x6A4340 -- compiler-generated IPiggyback AddRef adjustor thunk (this -= 0x18).
// SYNTHETIC: GAMEMD 0x6A4350 -- compiler-generated IPiggyback Release adjustor thunk (this -= 0x18).
