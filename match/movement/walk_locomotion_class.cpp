// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
//
// WalkLocomotionClass (layout, tables and evidence in walk_locomotion_class.h).
// The COM bodies (Load, Save, QueryInterface, PiggybackCLSID) have the same
// shape as DropPodLocomotionClass's. MovementStep 0x75AEC0 and 0x75C240 are
// not drafted here.

#include <new.h>
#include "walk_locomotion_class.h"
#include "../core/header_tuning_globals.h"

// ---- run-time initialised copies of the shared tuning globals --------------

// GLOBAL: GAMEMD 0xB45BD0
extern double DAT_00B45BD0;
// GLOBAL: GAMEMD 0x7F69C0
const double DAT_007F69C0 = 60.0;

// SYNTHETIC: GAMEMD 0x75A8D0
// GLOBAL: GAMEMD 0xB45C20
double DAT_00B45C20 = DAT_00B45BD0 / DAT_007F69C0;
// SYNTHETIC: GAMEMD 0x75A8F0
// GLOBAL: GAMEMD 0xB45C08
double DAT_00B45C08 = 1.0 / DAT_00B45C20;
// SYNTHETIC: GAMEMD 0x75AA70
// GLOBAL: GAMEMD 0xB45C10
TuningCoordInit DAT_00B45C10(128, 128, 0);

// FUNCTION: GAMEMD 0x75AA90
WalkLocomotionClass::WalkLocomotionClass()
    : unknown_1C(DAT_00B45BE8), MoveHeadTo(DAT_00B45BE8),
      unknown_34(false), unknown_35(false), unknown_36(false), Piggybackee(0)
{
}

// FUNCTION: GAMEMD 0x75AB30
bool __stdcall WalkLocomotionClass::IsMoving()
{
    return unknown_34;
}

// FUNCTION: GAMEMD 0x75AB40
// Moving, the linked object has a positive value at +0x578, and there is a
// head-to coordinate.
bool __stdcall WalkLocomotionClass::IsMovingNow()
{
    if (IsMoving() && WalkFoot(LinkedTo)->unknown_578 > 0.0 && !WalkIsEmpty(MoveHeadTo))
        return true;
    return false;
}

// FUNCTION: GAMEMD 0x75ABA0
LocoCoord __stdcall WalkLocomotionClass::Destination()
{
    LocoCoord c;
    if (IsMoving()) {
        c.X = unknown_1C.X;
        c.Y = unknown_1C.Y;
        c.Z = unknown_1C.Z;
        return c;
    }
    c.X = DAT_00B45BE8.X;
    c.Y = DAT_00B45BE8.Y;
    c.Z = DAT_00B45BE8.Z;
    return c;
}

// FUNCTION: GAMEMD 0x75AC00
// PARTIAL (34.1%). Retail keeps two separate return copies (field loads in
// ECX/EDX/EAX for the head-to path, ECX/EDX/ESI through a pointer for the
// location path); cl folds them into one tail. Tried: return of the member,
// WalkCoord conversions, explicit compares, local copies (2.4-34.1%).
LocoCoord __stdcall WalkLocomotionClass::HeadToCoord()
{
    LocoCoord c;
    if (!WalkIsEmpty(MoveHeadTo)) {
        c.X = MoveHeadTo.X;
        c.Y = MoveHeadTo.Y;
        c.Z = MoveHeadTo.Z;
        return c;
    }
    LocoCoord* loc = &WalkFoot(LinkedTo)->Location;
    c.X = loc->X;
    c.Y = loc->Y;
    c.Z = loc->Z;
    return c;
}

// FUNCTION: GAMEMD 0x75AC80
bool __stdcall WalkLocomotionClass::Process()
{
    unknown_35 = true;
    MovementStep(1);
    unknown_35 = false;
    return IsMoving();
}

// FUNCTION: GAMEMD 0x75ACB0
// PARTIAL (32.4%). Same blocks as retail, but cl puts the empty-destination
// path first and loads the argument copy in a different order. Tried: struct
// copy vs fieldwise copy, WalkIsEmpty vs explicit compares, early return and
// if/else on the equality chain (22.1-32.4%).
void __stdcall WalkLocomotionClass::MoveTo(LocoCoord to)
{
    if (WalkFoot(LinkedTo)->vf_37C() || WalkFoot(LinkedTo)->vf_1D4() || WalkFoot(LinkedTo)->vf_1D8())
        return;
    unknown_1C = to;
    if (to.X != DAT_00B45BE8.X || to.Y != DAT_00B45BE8.Y || to.Z != DAT_00B45BE8.Z) {
        if (WalkCellAt(to)->Flags & 0x100)
            unknown_1C.Z += LocoHeightScale(0x3C);
        unknown_34 = true;
    } else if (WalkIsEmpty(MoveHeadTo)) {
        bool was = unknown_34;
        unknown_34 = false;
        if (was)
            WalkFoot(LinkedTo)->vf_54C();
    }
}

// FUNCTION: GAMEMD 0x75ADA0
void __stdcall WalkLocomotionClass::StopMoving()
{
    unknown_1C = DAT_00B45BE8;
    if (WalkIsEmpty(MoveHeadTo)) {
        unknown_34 = false;
        unknown_36 = false;
        WalkFoot(LinkedTo)->vf_54C();
    }
}

// FUNCTION: GAMEMD 0x75AE00
void __stdcall WalkLocomotionClass::DoTurn(unsigned long dir)
{
    WalkFoot(LinkedTo)->PrimaryFacing.Fun_004C9300(WalkDirView(dir));
}

// FUNCTION: GAMEMD 0x75AE30
void __stdcall WalkLocomotionClass::ForceImmediateDestination(LocoCoord coord)
{
    bool was = unknown_34;
    Fun_0075C240(coord);
    if (WalkIsEmpty(MoveHeadTo) && WalkIsEmpty(unknown_1C)) {
        unknown_34 = false;
        if (was)
            WalkFoot(LinkedTo)->vf_54C();
    }
}

// FUNCTION: GAMEMD 0x75C680
HRESULT __stdcall WalkLocomotionClass::Load(IStream* pStm)
{
    HRESULT hr = LocomotionClass::Load(pStm);
    if (hr >= 0) {
        new (this) WalkLocomotionClass(0);
        bool hasPiggyback;
        pStm->Read(&hasPiggyback, 1, 0);
        if (hasPiggyback)
            hr = OleLoadFromStream(pStm, IID_ILocomotion, (void**)&Piggybackee);
    }
    return hr;
}

// FUNCTION: GAMEMD 0x75C700
HRESULT __stdcall WalkLocomotionClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = LocomotionClass::Save(pStm, fClearDirty);
    if (hr >= 0) {
        bool hasPiggyback;
        if (Piggybackee != 0) {
            hasPiggyback = true;
            pStm->Write(&hasPiggyback, 1, 0);
            IPersistStreamPtr persist(Piggybackee);
            hr = OleSaveToStream(persist, pStm);
        } else {
            hasPiggyback = false;
            pStm->Write(&hasPiggyback, 1, 0);
        }
    }
    return hr;
}

// FUNCTION: GAMEMD 0x75C7F0
HRESULT __stdcall WalkLocomotionClass::QueryInterface(REFIID riid, void** ppv)
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

// FUNCTION: GAMEMD 0x75C8E0
bool __stdcall WalkLocomotionClass::IsOkToEnd()
{
    if (!IsMoving() && Piggybackee != 0 && !unknown_35 && !WalkFoot(LinkedTo)->unknown_6AD)
        return true;
    return false;
}

// FUNCTION: GAMEMD 0x75C920
HRESULT __stdcall WalkLocomotionClass::PiggybackCLSID(CLSID* out)
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

// FUNCTION: GAMEMD 0x75CA30
void __stdcall WalkLocomotionClass::MarkAllOccupationBits(int mark)
{
    if (!mark) {
        WalkCoord c = HeadToCoord();
        WalkFoot(LinkedTo)->vf_0F4(&c);
    }
}

// FUNCTION: GAMEMD 0x75CB20
bool __stdcall WalkLocomotionClass::IsReallyMovingNow()
{
    return unknown_36;
}

// FUNCTION: GAMEMD 0x75CB30
void __stdcall WalkLocomotionClass::ClearCoords()
{
    unknown_1C = DAT_00B45BE8;
    MoveHeadTo = DAT_00B45BE8;
}

// FUNCTION: GAMEMD 0x75CBC0
void __stdcall WalkLocomotionClass::StopMovementAnimation()
{
    unknown_36 = false;
}

// FUNCTION: GAMEMD 0x75CBD0
int WalkLocomotionClass::Size()
{
    return sizeof(WalkLocomotionClass);
}

// FUNCTION: GAMEMD 0x75CBE0
// Scalar deleting destructor, compiler output around the inline destructor.
