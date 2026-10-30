// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU267 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x75a8a0-0x75cc8f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// WalkLocomotionClass (layout, tables and evidence in walk_locomotion_class.h).
// The COM bodies (Load, Save, QueryInterface, PiggybackCLSID) have the same
// shape as DropPodLocomotionClass's. MovementStep 0x75AEC0 and 0x75C240 are
// not drafted here.
//
// One-instruction leaf members that repeat at several addresses (constant
// returns, field reads and writes, return -1), found in the engine's class
// vtables. Their owning classes are not modelled here, so each address is a
// member of a placeholder owner `Obj_<ADDR>` that declares only the field it
// touches (earlier bytes are `unknown_XX`), with an offset assert. The
// vtable owner and slot read from retail are noted per function. Each address
// was verified separately.

#include <new.h>
#include "walk_locomotion_class.h"
#include "../core/header_tuning_globals.h"

// ---- run-time initialised copies of the shared tuning globals --------------

// GLOBAL: GAMEMD 0xB45BD0
extern double DAT_00B45BD0;
// GLOBAL: GAMEMD 0x7F69C0
const double DAT_007F69C0 = 60.0;

// GLOBAL: GAMEMD 0xB45C20
extern double DAT_00B45C20;

// GLOBAL: GAMEMD 0xB45C08
extern double DAT_00B45C08;

// GLOBAL: GAMEMD 0xB45C10
extern TuningCoordInit DAT_00B45C10;

#include <stddef.h>
#include "../_rt/gg_static_assert.h"


// vtable owner / slot: -
#include "../_layout/obj_00681060.h"

// vtable owner / slot: ShipLocomotionClass+4/s29
#include "../_layout/obj_006a3e50.h"

// vtable owner / slot: -
struct Obj_006E5560 {
    unsigned char unknown_00[0x30];
    int unknown_30;
    void FUN_006E5560(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_006E5560, unknown_30) == 0x30);

// vtable owner / slot: TeleportLocomotionClass+4/s29
#include "../_layout/obj_00719e20.h"

// vtable owner / slot: WalkLocomotionClass+4/s29
#include "../_layout/obj_0075c7e0.h"




// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x75AA90
WalkLocomotionClass::WalkLocomotionClass()
    : unknown_1C(DAT_00B45BE8), MoveHeadTo(DAT_00B45BE8),
      unknown_34(false), unknown_35(false), unknown_36(false), Piggybackee(0)
{
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x75AB30
bool __stdcall WalkLocomotionClass::IsMoving()
{
    return unknown_34;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x75AB40
// Moving, the linked object has a positive value at +0x578, and there is a
// head-to coordinate.
bool __stdcall WalkLocomotionClass::IsMovingNow()
{
    if (IsMoving() && WalkFoot(LinkedTo)->unknown_578 > 0.0 && !WalkIsEmpty(MoveHeadTo))
        return true;
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x75AC80
bool __stdcall WalkLocomotionClass::Process()
{
    unknown_35 = true;
    MovementStep(1);
    unknown_35 = false;
    return IsMoving();
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x75AE00
void __stdcall WalkLocomotionClass::DoTurn(unsigned long dir)
{
    WalkFoot(LinkedTo)->PrimaryFacing.Fun_004C9300(WalkDirView(dir));
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x0075C7E0
int Obj_0075C7E0::FUN_0075C7E0(void*)
{
    return 2;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// FUNCTION: GAMEMD 0x75C850
HRESULT __stdcall WalkLocomotionClass::BeginPiggyback(ILocomotion* loco)
{
    if (!loco)
        return E_POINTER;
    if (Piggybackee == 0) {
        Piggybackee = loco;
        return S_OK;
    }
    return E_FAIL;
}

// FUNCTION: GAMEMD 0x75C8A0
HRESULT __stdcall WalkLocomotionClass::EndPiggyback(ILocomotion** out)
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x75C8E0
bool __stdcall WalkLocomotionClass::IsOkToEnd()
{
    if (!IsMoving() && Piggybackee != 0 && !unknown_35 && !WalkFoot(LinkedTo)->unknown_6AD)
        return true;
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x75CA30
void __stdcall WalkLocomotionClass::MarkAllOccupationBits(int mark)
{
    if (!mark) {
        WalkCoord c = HeadToCoord();
        WalkFoot(LinkedTo)->vf_0F4(&c);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x75CB20
bool __stdcall WalkLocomotionClass::IsReallyMovingNow()
{
    return unknown_36;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x75CB30
void __stdcall WalkLocomotionClass::ClearCoords()
{
    unknown_1C = DAT_00B45BE8;
    MoveHeadTo = DAT_00B45BE8;
}

// FUNCTION: GAMEMD 0x0075CB80
ULONG __stdcall WalkLocomotionClass::AddRef()
{
    return LocomotionClass::AddRef();
}

// FUNCTION: GAMEMD 0x0075CB90
ULONG __stdcall WalkLocomotionClass::Release()
{
    return LocomotionClass::Release();
}

// FUNCTION: GAMEMD 0x75CBA0
bool __stdcall WalkLocomotionClass::IsPiggybacking()
{
    return Piggybackee != 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x75CBC0
void __stdcall WalkLocomotionClass::StopMovementAnimation()
{
    unknown_36 = false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x75CBD0
int WalkLocomotionClass::Size()
{
    return sizeof(WalkLocomotionClass);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x75CBE0
// Scalar deleting destructor, compiler output around the inline destructor.

// SYNTHETIC: GAMEMD 0x75CC30 -- compiler-generated ILocomotion QI adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x75CC40 -- compiler-generated ILocomotion AddRef adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x75CC50 -- compiler-generated ILocomotion Release adjustor thunk (this -= 0x4).
// SYNTHETIC: GAMEMD 0x75CC60 -- compiler-generated IPiggyback QI adjustor thunk (this -= 0x18).
// SYNTHETIC: GAMEMD 0x75CC70 -- compiler-generated IPiggyback AddRef adjustor thunk (this -= 0x18).
// SYNTHETIC: GAMEMD 0x75CC80 -- compiler-generated IPiggyback Release adjustor thunk (this -= 0x18).

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB45BE8
LocoCoord DAT_00B45BE8;
// END defined globals
