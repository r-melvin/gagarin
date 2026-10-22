// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// No /GX: no retail body of this class has an exception frame (the _com_ptr_t
// conversions at 0x4B62C0 / 0x4B64E0 are compiled with their throw paths as
// plain calls to _com_issue_error).
//
// DropPodLocomotionClass (leaf of the locomotion module). Layout, tables and
// evidence are in droppod_locomotion.h; the foundation is loco_base.*.
//
// Addresses in this TU, by retail table:
//   primary table 0x7E8344: QI 0x4B6470, AddRef 0x4B66A0, Release 0x4B66B0,
//     GetClassID 0x4B6200, Load 0x4B6240, Save 0x4B62C0, Size 0x4B66E0,
//     scalar deleting destructor 0x4B66F0 (synthetic). Inherited (bound):
//     IsDirty 0x4B4C30, GetSizeMax 0x55AB40.
//   ILocomotion table 0x7E8278: adjustor thunks 0x4B6740 / 0x4B6750 / 0x4B6760
//     (synthetic), IsMoving 0x4B5B30, Destination 0x4B5B40, Process 0x4B5B70,
//     MoveTo 0x4B6040, StopMoving 0x4B63A0, InWhichLayer 0x4B64D0,
//     DrawingCode 0x4B65F0; every other slot is inherited from LocomotionClass.
//   IPiggyback table 0x7E8254: adjustor thunks 0x4B6770 / 0x4B6780 / 0x4B6790
//     (synthetic), BeginPiggyback 0x4B63B0, EndPiggyback 0x4B6400, IsOkToEnd
//     0x4B6440, PiggybackCLSID 0x4B64E0, IsPiggybacking 0x4B66C0.
//   Constructor 0x4B5AB0. The ordinary destructor body 0x4B5B00 stays scored
//   by ComRel_004B5B00 in match/core/multi_vtable_dtor_family_methods.cpp: an
//   out-of-line empty destructor here matches 0x4B5B00 but shrinks the deleting
//   wrapper 0x4B66F0 from 0x41 to 0x20 bytes, so this source keeps the inline
//   form and claims only the wrapper.

#include <new.h>
#include "droppod_locomotion.h"

// GLOBAL: GAMEMD 0x7E9A70 - CLSID of this locomotor, copied by GetClassID.
extern "C" const CLSID CLSID_DropPodLocomotion =
    { 0x4A582745, 0x9839, 0x11D1, { 0xB7, 0x09, 0x00, 0xA0, 0x24, 0xDD, 0xAF, 0xD1 } };

// LIBRARY: OLE32!OleLoadFromStream / OleSaveToStream, IAT 0x7E15F8 / 0x7E15F4
// (declared by <ole2.h>).

// FUNCTION: GAMEMD 0x4B5AB0
DropPodLocomotionClass::DropPodLocomotionClass()
    : unknown_1C(false), DestCoord(DAT_008A0820), Piggybackee(0)
{
}

// FUNCTION: GAMEMD 0x4B5B30
bool __stdcall DropPodLocomotionClass::IsMoving()
{
    return true;
}

// FUNCTION: GAMEMD 0x4B5B40
// migrated from match/movement/drop_pod_interface_004b5b30.cpp; integrator retires the old row
LocoCoord __stdcall DropPodLocomotionClass::Destination()
{
    LocoCoord c;
    c.X = DestCoord.X;
    c.Y = DestCoord.Y;
    c.Z = DestCoord.Z;
    return c;
}

// FUNCTION: GAMEMD 0x4B5B70
// PARTIAL: diff_retail 2.3% over the requested 0x4C9-byte span; the emitted
// section is 0x4C0 bytes, so this is not a full-span match. Retail holds the
// constant 0 in EBX and packs its locals into a 0x30 frame (this source: 0x38),
// so most stack offsets shift.
bool __stdcall DropPodLocomotionClass::Process()
{
    DropPodFootView* foot = reinterpret_cast<DropPodFootView*>(LinkedTo);
    LocoCoord loc = foot->Location;
    LocoCoord oldLoc = loc;
    int fall = foot->vf_1C8() / 10 + 2;
    if (RulesInstance->MinFall > fall)
        fall = RulesInstance->MinFall;
    if (unknown_1C)
        loc.X = (int)(FUN_004CAD00(RulesInstance->Angle) * fall + loc.X);
    else
        loc.X = (int)((double)loc.X - FUN_004CAD00(RulesInstance->Angle) * fall);
    loc.Z = (int)((double)loc.Z - FUN_004CACB0(RulesInstance->Angle) * fall);
    if (foot->vf_1C8() <= 0) {
        foot->vf_1CC(0);
        loc = foot->Location;
        foot->vf_0D4();
        AddRef();
        EndPiggyback(&foot->Locomotor);
        if (!foot->vf_0D8(&loc, 0)) {
            DropPod_DamageArea(&loc, 100, foot, RulesInstance->unknown_FA8, 1, 0);
            new DropPodAnimAllocationView(DropPod_SelectDamageAnim(100, RulesInstance->unknown_FA8, 0, &loc), &loc, 0, 1, 0x2600, DropPod_ZAdjust(loc), false);
            Release();
            return true;
        }
        new DropPodAnimAllocationView(RulesInstance->LandAnim, &loc, 0, 1, 0x600, 0, false);
        if (unknown_1C)
            new DropPodAnimAllocationView(RulesInstance->TouchdownAnims[1], &loc, 0, 1, 0x600, 0, false);
        else
            new DropPodAnimAllocationView(RulesInstance->TouchdownAnims[0], &loc, 0, 1, 0x600, 0, false);
        foot->vf_124(1);
        foot->vf_1CC(0);
        foot->vf_484(0, 1);
        foot->vf_1EC();
        foot->vf_174(&DAT_008A0820, 0, 0);
        Release();
        return true;
    }
    foot->vf_1B4(&loc);
    WeaponTypeClass* weapon = RulesInstance->Weapon;
    if (weapon) {
        if (CurrentFrame % 6 == 0)
            new DropPodAnimAllocationView(((AnimTypeClass**)AnimTypeClassArray.Items)[FUN_00427CB0("SMOKEY")], &oldLoc, 0, 1, 0x600, 0, false);
        if (CurrentFrame % 3 == 0) {
            LocoPoint2D offset;
            offset.X = 0;
            offset.Y = 0;
            if (!foot->House->IsAlliedWith(MapInstance.GetCellAt(&DestCoord)->FindTechnoNearestTo(&offset, false, 0))) {
                LocoCoord pos;
                pos = DropPod_RandomCoordsNear(DestCoord, 0x55, false);
                DropPod_PlaySample(weapon->Reports.Items[DAT_00886B88.Random() % weapon->Reports.Count], &pos, 0);
                DropPod_DamageArea(&pos, weapon->Damage << 1, foot, (int)weapon->Warhead, 1, 0);
                new DropPodAnimAllocationView(DropPod_SelectDamageAnim(weapon->Damage << 1, (int)weapon->Warhead, 0, &pos), &pos, 0, 1, 0x2600, DropPod_ZAdjust(pos), false);
            }
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x4B6040
// PARTIAL: diff_retail 27.1%. Retail copies `to` through EBX, saved and restored
// around the IsWithinUsableArea call, which shifts every later stack offset by 4.
void __stdcall DropPodLocomotionClass::MoveTo(LocoCoord to)
{
    DropPodFootView* foot = reinterpret_cast<DropPodFootView*>(LinkedTo);
    if (DropPodIsEmptyCoord(DestCoord)) {
        DestCoord.X = to.X;
        DestCoord.Y = to.Y;
        DestCoord.Z = to.Z;
        DestCoord.Z = MapInstance.GetHeightAt(&DestCoord);
        LocoCoord c = DestCoord;
        c.Z += RulesInstance->unknown_5A8;
        c.X = (int)((double)RulesInstance->unknown_5A8 / FUN_004CAD50(RulesInstance->Angle) + c.X);
        if (!MapInstance.IsWithinUsableArea(&c)) {
            unknown_1C = true;
            c.X = (int)((double)DestCoord.X - (double)RulesInstance->unknown_5A8 / FUN_004CAD50(RulesInstance->Angle));
        }
        foot->vf_1B4(&c);
        if (foot->vf_0D8(&c, 0x80)) {
            foot->vf_1B4(&c);
            short dir = (short)0x8000;
            foot->PrimaryFacing.Set(&dir);
            new DropPodAnimAllocationView(RulesInstance->SpawnAnim, &c, 0, 1, 0x600, 0, false);
        } else {
            foot->vf_0D8(&c, 0x80);
        }
    }
}

// FUNCTION: GAMEMD 0x4B6200
// migrated from match/movement/drop_pod_interface_004b5b30.cpp; integrator retires the old row
HRESULT __stdcall DropPodLocomotionClass::GetClassID(CLSID* pClassID)
{
    if (!pClassID)
        return E_POINTER;
    *pClassID = CLSID_DropPodLocomotion;
    return S_OK;
}

// FUNCTION: GAMEMD 0x4B6240
// migrated from match/movement/drop_pod_interface_004b5b30.cpp; integrator retires the old row
HRESULT __stdcall DropPodLocomotionClass::Load(IStream* pStm)
{
    HRESULT hr = LocomotionClass::Load(pStm);
    if (hr >= 0) {
        new (this) DropPodLocomotionClass(0);
        bool hasPiggyback;
        pStm->Read(&hasPiggyback, 1, 0);
        if (hasPiggyback)
            hr = OleLoadFromStream(pStm, IID_ILocomotion, (void**)&Piggybackee);
    }
    return hr;
}

// FUNCTION: GAMEMD 0x4B62C0
HRESULT __stdcall DropPodLocomotionClass::Save(IStream* pStm, BOOL fClearDirty)
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
            hr = pStm->Write(&hasPiggyback, 1, 0);
        }
    }
    return hr;
}

// FUNCTION: GAMEMD 0x4B63A0
// migrated from match/movement/drop_pod_interface_004b5b30.cpp; integrator retires the old row
void __stdcall DropPodLocomotionClass::StopMoving()
{
}

// FUNCTION: GAMEMD 0x4B63B0
HRESULT __stdcall DropPodLocomotionClass::BeginPiggyback(ILocomotion* loco)
{
    if (!loco)
        return E_POINTER;
    if (Piggybackee == 0) {
        Piggybackee = loco;
        return S_OK;
    }
    return E_FAIL;
}

// FUNCTION: GAMEMD 0x4B6400
HRESULT __stdcall DropPodLocomotionClass::EndPiggyback(ILocomotion** out)
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

// FUNCTION: GAMEMD 0x4B6440
bool __stdcall DropPodLocomotionClass::IsOkToEnd()
{
    if (!IsMoving() && Piggybackee != 0)
        return true;
    return false;
}

// FUNCTION: GAMEMD 0x4B6470
HRESULT __stdcall DropPodLocomotionClass::QueryInterface(REFIID riid, void** ppv)
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

// FUNCTION: GAMEMD 0x4B64D0
int __stdcall DropPodLocomotionClass::InWhichLayer()
{
    return 3;
}

// FUNCTION: GAMEMD 0x4B64E0
HRESULT __stdcall DropPodLocomotionClass::PiggybackCLSID(CLSID* out)
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

// FUNCTION: GAMEMD 0x4B65F0
int __stdcall DropPodLocomotionClass::DrawingCode()
{
    return unknown_1C != 0;
}

// FUNCTION: GAMEMD 0x4B6620
// FUNCTION: GAMEMD 0x4B6630
// FUNCTION: GAMEMD 0x4B6640
// FUNCTION: GAMEMD 0x4B6650
// FUNCTION: GAMEMD 0x4B6660
// FUNCTION: GAMEMD 0x4B6670
// FUNCTION: GAMEMD 0x4B6680
// FUNCTION: GAMEMD 0x4B6690
// (LocomotionClass inline slots 39-41 and 45-49, emitted here through this
// class's ILocomotion table, which inherits them; see loco_base.h.)

// FUNCTION: GAMEMD 0x4B66A0
ULONG __stdcall DropPodLocomotionClass::AddRef()
{
    return LocomotionClass::AddRef();
}

// FUNCTION: GAMEMD 0x4B66B0
ULONG __stdcall DropPodLocomotionClass::Release()
{
    return LocomotionClass::Release();
}

// FUNCTION: GAMEMD 0x4B66C0
bool __stdcall DropPodLocomotionClass::IsPiggybacking()
{
    return Piggybackee != 0;
}

// FUNCTION: GAMEMD 0x4B66E0
int DropPodLocomotionClass::Size()
{
    return sizeof(DropPodLocomotionClass);
}

// SYNTHETIC: GAMEMD 0x4B66F0 -- compiler-generated scalar deleting wrapper.
// SYNTHETIC: GAMEMD 0x4B6740 -- compiler-generated ILocomotion QI adjustor thunk.
// SYNTHETIC: GAMEMD 0x4B6750 -- compiler-generated ILocomotion AddRef adjustor thunk.
// SYNTHETIC: GAMEMD 0x4B6760 -- compiler-generated ILocomotion Release adjustor thunk.
// SYNTHETIC: GAMEMD 0x4B6770 -- compiler-generated IPiggyback QI adjustor thunk.
// SYNTHETIC: GAMEMD 0x4B6780 -- compiler-generated IPiggyback AddRef adjustor thunk.
// SYNTHETIC: GAMEMD 0x4B6790 -- compiler-generated IPiggyback Release adjustor thunk.

// DropPodLocomotionClass::~DropPodLocomotionClass (body 0x4B5B00, scored
// elsewhere; see above) and the scalar deleting destructor 0x4B66F0 are compiler output
// from the inline empty virtual destructor in the header: vptr stores, Piggybackee release,
// LocomotionClass body 0x55A6F0, `operator delete` when bit 0 of the flag is set.
