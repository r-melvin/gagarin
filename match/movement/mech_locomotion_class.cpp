// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
//
// MechLocomotionClass (locomotion module leaf). Layout and evidence are in
// mech_locomotion_class.h. Its two emitted tables are checked slot-for-slot
// against retail; bound partial/default targets are not body-match claims.
// Inherited slots (bound, never defined here): QI/AddRef/Release and their
// adjustor thunks, IsDirty, Save, GetSizeMax; ILocomotion LinkToObject,
// CanEnterCell, IsToHaveShadow, DrawMatrix ... ForceTrack and the rest of the
// base defaults. Not in this partition: the destructor body 0x5AFF50 and the
// movement step 0x5B01C0 (bound by address).

#include <stdlib.h>
#include <new.h>
#include "mech_locomotion_class.h"

// GLOBAL: GAMEMD 0x7E9AA0
extern "C" const CLSID CLSID_MechLocomotion =
    { 0x55D141B8, 0xDB94, 0x11D1, { 0xAC, 0x98, 0x00, 0x60, 0x08, 0x05, 0x5B, 0xB5 } };


// FUNCTION: GAMEMD 0x5AFEF0
MechLocomotionClass::MechLocomotionClass()
    : MoveDestination(DAT_00ABEE10), MoveHeadTo(DAT_00ABEE10), Moving(false)
{
}

// FUNCTION: GAMEMD 0x5AFF70
bool __stdcall MechLocomotionClass::IsMoving()
{
    return Moving;
}

// FUNCTION: GAMEMD 0x5AFF80
LocoCoord __stdcall MechLocomotionClass::Destination()
{
    LocoCoord c;
    if (IsMoving()) {
        c.X = MoveDestination.X;
        c.Y = MoveDestination.Y;
        c.Z = MoveDestination.Z;
        return c;
    }
    c.X = DAT_00ABEE10.X;
    c.Y = DAT_00ABEE10.Y;
    c.Z = DAT_00ABEE10.Z;
    return c;
}

// FUNCTION: GAMEMD 0x5AFFE0
// CAP (ID98, final): 7.3%. VC6 lays the fall-through block out the other way
// round (retail: jne HEAD, jne HEAD, je LOC with the head copy first). Variants
// tried: ==/&& with if-else, !=/|| with early returns, !=/|| if-else, struct
// assignment instead of member copies, goto. Multiset delta vs retail:
// retail-only {mov 1, je 1}, compiled-only {jne 1} (41 vs 40 instructions).
LocoCoord __stdcall MechLocomotionClass::HeadToCoord()
{
    LocoCoord c;
    if (MoveHeadTo.X != DAT_00ABEE10.X || MoveHeadTo.Y != DAT_00ABEE10.Y || MoveHeadTo.Z != DAT_00ABEE10.Z) {
        c.X = MoveHeadTo.X;
        c.Y = MoveHeadTo.Y;
        c.Z = MoveHeadTo.Z;
        return c;
    }
    LocoCoord* loc = &MechFoot(LinkedTo)->Location;
    c.X = loc->X;
    c.Y = loc->Y;
    c.Z = loc->Z;
    return c;
}

// FUNCTION: GAMEMD 0x5B0060
bool __stdcall MechLocomotionClass::Process()
{
    MovementStep(1);
    return IsMoving();
}

// FUNCTION: GAMEMD 0x5B0080
// CAP (ID98, final): 39.6%. Retail keeps a pointer to Destination in EDI (`LEA EDI,[ESI+0x14]`)
// and writes the converted argument temp (re-stored in its own stack slot) before the member
// copy; VC6 here stores straight through ESI. Multiset delta: retail-only {push 1, lea 1, pop 1,
// mov 2-3}. Variants: struct assign, per-field copy, local copy (adds SUB ESP), converting
// temp via const MechCoord& (used), reference-bound temp, MechCoord operator= by value/ref.
void __stdcall MechLocomotionClass::MoveTo(LocoCoord to)
{
    if (MechFoot(LinkedTo)->vf_37C() || MechFoot(LinkedTo)->vf_380()
        || MechFoot(LinkedTo)->vf_1D4() || MechFoot(LinkedTo)->vf_1D8())
        return;
    MoveDestination = to;
    if (MechCellAt(to)->Flags & 0x100)
        MoveDestination.Z += LocoHeightScale(0x3C);
    Moving = true;
}

// FUNCTION: GAMEMD 0x5B0120
void __stdcall MechLocomotionClass::StopMoving()
{
    MoveDestination = DAT_00ABEE10;
    if (MoveHeadTo.X == DAT_00ABEE10.X && MoveHeadTo.Y == DAT_00ABEE10.Y && MoveHeadTo.Z == DAT_00ABEE10.Z)
        Moving = false;
}

// FUNCTION: GAMEMD 0x5B0170
void __stdcall MechLocomotionClass::DoTurn(unsigned long dir)
{
    MechFoot(LinkedTo)->PrimaryFacing.SetDesired(MechDirView(dir));
}

// FUNCTION: GAMEMD 0x5B01A0
// CAP (ID98, final): 0%. Retail: `MOV EAX,[ESP+8]; MOV ECX,[ESP+0xC]; PUSH ESI; MOV ESI,this;
// MOV EDX,[ESP+0x14]; ADD ESI,0x20; 3 stores`; compiled uses EAX as the base with offsets (or
// `ADD EAX,0x20` for memcpy). Multiset delta {push 1, add 1, pop 1}. Variants: struct assign,
// per-field, pointer local, MechCoord operator=/Set(), memcpy, /Ob0.
void __stdcall MechLocomotionClass::ForceImmediateDestination(LocoCoord coord)
{
    MoveHeadTo = coord;
}

// FUNCTION: GAMEMD 0x5B1960
HRESULT __stdcall MechLocomotionClass::GetClassID(CLSID* pClassID)
{
    if (pClassID == 0)
        return E_POINTER;
    *pClassID = CLSID_MechLocomotion;
    return S_OK;
}

// FUNCTION: GAMEMD 0x5B19A0
HRESULT __stdcall MechLocomotionClass::Load(IStream* pStm)
{
    HRESULT hr = LocomotionClass::Load(pStm);
    if (hr >= 0)
        new (this) MechLocomotionClass(0);
    return hr;
}

// FUNCTION: GAMEMD 0x5B19D0
int __stdcall MechLocomotionClass::InWhichLayer()
{
    return 2;
}

// FUNCTION: GAMEMD 0x5B19E0
bool __stdcall MechLocomotionClass::IsMovingNow()
{
    if (MECH_FACING(LinkedTo)->IsRotating())
        return true;
    if (IsMoving()) {
        if (MoveHeadTo.X != DAT_00ABEE10.X || MoveHeadTo.Y != DAT_00ABEE10.Y || MoveHeadTo.Z != DAT_00ABEE10.Z) {
            if (MechFoot(LinkedTo)->vf_538() > 0)
                return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x5B1A50
void __stdcall MechLocomotionClass::MarkAllOccupationBits(int mark)
{
    if (!mark)
        MechUnmarkAt(MechFoot(LinkedTo), HeadToCoord());
}

// FUNCTION: GAMEMD 0x5B1AA0
bool __stdcall MechLocomotionClass::IsMovingHere(LocoCoord to)
{
    LocoCoord c = HeadToCoord();
    MechCellCoord target(to);
    MechCellCoord current(c);
    if (current.X == target.X && current.Y == target.Y && abs(c.Z - to.Z) <= DAT_00ABEE50)
        return true;
    return false;
}
// FUNCTION: GAMEMD 0x5B1B40
int MechLocomotionClass::Size()
{
    return sizeof(MechLocomotionClass);
}

// SYNTHETIC: GAMEMD 0x5B1B50 -- compiler-generated Mech deleting destructor;
// the table's weak vector-deleting reference defaults to this scalar entry.
