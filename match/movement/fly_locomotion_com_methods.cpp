// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against the user's retail gamemd.exe v1.001 over the
//   0x4CFC40-0x4CFDBF leaf run of FlyLocomotionClass. See the header for how
//   the class name was read out of its own runtime type information and for
//   the numeric offset derivation. Bodies ordered ascending by retail address.
#include "fly_locomotion_com_methods.h"
#include "loco_base.h"

// VTABLE: GAMEMD 0x7E89F4 — the locomotor interface vtable (base offset 4).
// VTABLE: GAMEMD 0x7E8AC0 — the persist vtable (base offset 0).
// GLOBAL: GAMEMD 0x7E9A80 — CLSID_FlyLocomotionClass.
// GLOBAL: GAMEMD 0xA8B230 — the scenario object.

// Still under way: a landing aircraft has stopped moving, and one taking off
// counts as moving only until it is within half its travel of the target.
// FUNCTION: GAMEMD 0x4CFC40
char FlyLocomotionClass::IsMovingNow() const
{
    if (IsLanding == 0 &&
        (IsTakingOff == 0 ||
         (LinkedTo->*LinkedTo->Vtbl->At_1C8)() >= FlightLevel / 2)) {
        return 1;
    }
    return 0;
}

// IPersist::GetClassID — hand back the locomotor's own class id.
// FUNCTION: GAMEMD 0x4CFC80
HRESULT __stdcall FlyLocomotionGetClassID_004CFC80(ILocomotion_004CFD20*,
                                                   Guid_004CFC80* classID)
{
    if (classID == 0) {
        return 0x80004003;
    }

    *classID = CLSID_FlyLocomotion_007E9A80;
    return 0;
}

// IPersistStream::Load — run the shared locomotor load, then re-seat both of
// this class's vtables over the base's.
// FUNCTION: GAMEMD 0x4CFCC0
HRESULT __stdcall FlyLocomotionLoad_004CFCC0(FlyLocomotionClass* self,
                                             void* stream)
{
    // Fly's persist vptr is the complete-object primary base at +0; preserve the
    // old direct base-call target while using the canonical native declaration.
    HRESULT hr = reinterpret_cast<LocomotionClass*>(self)->LocomotionClass::Load((IStream*)stream);
    if (hr >= 0 && self != 0) {
        self->PersistVptr = (void*)0x7E8AC0;
        self->LocomotorVptr = (void*)0x7E89F4;
    }
    return hr;
}

// The drawing Z adjustment: four while the client still has travel left,
// two once it does not.
// FUNCTION: GAMEMD 0x4CFCF0
int __stdcall FlyLocomotionZAdjustment_004CFCF0(ILocomotion_004CFD20* self)
{
    Foot_004CFC40* linkedTo = self->LinkedTo;
    return ((linkedTo->*linkedTo->Vtbl->At_1C8)() <= 0) ? 2 : 4;
}

// The per-frame process: once the shadow is due, start the touchdown spin at
// a random rate, half the time in the opposite direction, re-mark the
// occupation bits and restart the spin counter. Then run the shared tail.
// FUNCTION: GAMEMD 0x4CFD20
void __stdcall FlyLocomotionProcess_004CFD20(ILocomotion_004CFD20* self)
{
    if (self->IsToHaveShadow()) {
        self->IsSpinning = 1;
        self->unknown_50 = Scenario_00A8B230->RandomNumber.RandomRanged(0x14, 0x1E);
        if (Scenario_00A8B230->RandomNumber.RandomRanged(0, 0x63) < 0x32) {
            self->unknown_50 = -self->unknown_50;
        }
        self->MarkAllOccupationBits();
        self->SpinCount = 0;
    }

    LocomotionClassProcess_0055A910(self);
}

// FlyLocomotionClass::IsPowered: the locomotor interface's slot 24 (vtable
// 0x7E8A54), answered by the shared locomotor implementation, which fills the
// same slot of LocomotionClass's table.
// FUNCTION: GAMEMD 0x4CFD90
bool __stdcall FlyLocomotionIsPowered_004CFD90(ILocomotion_004CFD20* self)
{
    return LocomotionClassIsPowered_0055A930(self);
}

// True while the client's owner has the gate byte clear.
// FUNCTION: GAMEMD 0x4CFDA0
char __stdcall FlyLocomotionIsSurfacing_004CFDA0(ILocomotion_004CFD20* self)
{
    Foot_004CFC40* linkedTo = self->LinkedTo;
    Owner_004CFDA0* owner = (linkedTo->*linkedTo->Vtbl->At_84)();
    return (char)(owner->At_D27 == 0);
}
