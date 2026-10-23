// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2
//
// JumpjetLocomotionClass (layout and tables in _layout/jumpjet_locomotion_class.h).
// The COM / IPiggyback bodies below are the shapes DriveLocomotionClass uses
// (movement/drive_locomotion.cpp). Load's placement new of the no-init
// constructor stores the three vptrs, so VC6 emits Jumpjet's tables here and,
// with them, the ILocomotion (+4) and IPiggyback (+0x18) adjustor thunks.

#include <new.h>
#include "../_layout/jumpjet_locomotion_class.h"

// LIBRARY: OLE32!OleLoadFromStream, IAT 0x7E15F8 (declared by <ole2.h>).

// FUNCTION: GAMEMD 0x54B750
HRESULT __stdcall JumpjetLocomotionClass::Load(IStream* pStm)
{
    HRESULT hr = LocomotionClass::Load(pStm);
    if (hr >= 0) {
        new (this) JumpjetLocomotionClass(0);
        bool hasPiggyback;
        pStm->Read(&hasPiggyback, 1, 0);
        if (hasPiggyback)
            hr = OleLoadFromStream(pStm, IID_ILocomotion, (void**)&Piggybackee);
    }
    return hr;
}

// FUNCTION: GAMEMD 0x54DA00
HRESULT __stdcall JumpjetLocomotionClass::BeginPiggyback(ILocomotion* loco)
{
    if (!loco)
        return E_POINTER;
    if (Piggybackee == 0) {
        Piggybackee = loco;
        return S_OK;
    }
    return E_FAIL;
}

// FUNCTION: GAMEMD 0x54DB50
HRESULT __stdcall JumpjetLocomotionClass::PiggybackCLSID(CLSID* out)
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

// FUNCTION: GAMEMD 0x54DC60
HRESULT __stdcall JumpjetLocomotionClass::QueryInterface(REFIID riid, void** ppv)
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

// SYNTHETIC: GAMEMD 0x54DFA0 -- compiler-generated scalar deleting destructor.
// SYNTHETIC: GAMEMD 0x54DFF0 -- compiler-generated ILocomotion QI adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x54E000 -- compiler-generated ILocomotion AddRef adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x54E010 -- compiler-generated ILocomotion Release adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x54E020 -- compiler-generated IPiggyback QI adjustor thunk (this -= 0x18).
// SYNTHETIC: GAMEMD 0x54E030 -- compiler-generated IPiggyback AddRef adjustor thunk (this -= 0x18).
// SYNTHETIC: GAMEMD 0x54E040 -- compiler-generated IPiggyback Release adjustor thunk (this -= 0x18).
