// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against the user's retail gamemd.exe v1.001 over the
//   0x4CFC40-0x4CFDBF leaf run of FlyLocomotionClass. See the header for how
//   the class name was read out of its own runtime type information and for
//   the numeric offset derivation. Bodies ordered ascending by retail address.
#include "fly_locomotion_com_methods.h"
#include "loco_base.h"
#include "../_layout/foot_class.h"
#include "../_layout/techno_type_class.h"
#include <new.h>

// GLOBAL: GAMEMD 0x822410
// Native QueryInterface key; GUID field order reproduces its sixteen bytes.
extern const IID IID_00822410 = {
    0x820F501C, 0x4F39, 0x11D2,
    {0x9B, 0x70, 0x00, 0x10, 0x4B, 0x97, 0x2F, 0xE8}
};

// SYNTHETIC: GAMEMD 0x4B4C50
// LocomotionClass::IsReallyMovingNow

// VTABLE: GAMEMD 0x7E89F4 — the locomotor interface vtable (base offset 4).
// VTABLE: GAMEMD 0x7E8AC0 — the persist vtable (base offset 0).
// GLOBAL: GAMEMD 0x7E9A80 — CLSID_FlyLocomotionClass.
// GLOBAL: GAMEMD 0xA8B230 — the scenario object.

// Still under way: a landing aircraft has stopped moving, and one taking off
// counts as moving only until it is within half its travel of the target.
// FUNCTION: GAMEMD 0x4CFC40
char FlyLocomotionClass::FUN_004CFC40() const
{
    if (IsLanding == 0 &&
        (IsTakingOff == 0 ||
         LinkedTo->vf_114() >= FlightLevel / 2)) {
        return 1;
    }
    return 0;
}

// IPersist::GetClassID — hand back the locomotor's own class id.
// FUNCTION: GAMEMD 0x4CFC80
HRESULT __stdcall FlyLocomotionClass::GetClassID(CLSID* classID)
{
    if (classID == 0) {
        return 0x80004003;
    }

    *classID = CLSID_FlyLocomotion;
    return 0;
}

// IPersistStream::Load — run the shared locomotor load, then re-seat both of
// this class's vtables over the base's.
// FUNCTION: GAMEMD 0x4CFCC0
HRESULT __stdcall FlyLocomotionClass::Load(IStream* stream)
{
    HRESULT hr = LocomotionClass::Load(stream);
    if (hr >= 0) {
        new (this) FlyLocomotionClass(0);
    }
    return hr;
}

// Secondary slot29 returns four when Foot slot114 is positive,two otherwise.
// Native 0x4CFCF4 reads LinkedTo from secondary-self+8.
// FUNCTION: GAMEMD 0x4CFCF0
int __stdcall FlyLocomotionClass::InWhichLayer()
{
    return (LinkedTo->vf_114() <= 0) ? 2 : 4;
}

// Secondary slot23 starts the touchdown spin before the shared power-off.
// The native virtual calls are slot4 (+10) and slot18 (+48).
// FUNCTION: GAMEMD 0x4CFD20
bool __stdcall FlyLocomotionClass::PowerOff()
{
    if (IsMoving()) {
        IsSpinning = 1;
        unknown_54 = Scenario_00A8B230->RandomNumber.RandomRanged(0x14, 0x1E);
        if (Scenario_00A8B230->RandomNumber.RandomRanged(0, 0x63) < 0x32) {
            unknown_54 = -unknown_54;
        }
        StopMoving();
        SpinCount = 0;
    }
    return LocomotionClass::PowerOff();
}

// Secondary slot24 delegates to the real base implementation.
// FUNCTION: GAMEMD 0x4CFD90
bool __stdcall FlyLocomotionClass::IsPowered()
{
    return LocomotionClass::IsPowered();
}

// Native 0x4CFDAF loads type+D27 through Foot slot33;0x4CFDB7 tests the byte.
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, bools_D20) + 7 * sizeof(bool) == 0xD27);
// FUNCTION: GAMEMD 0x4CFDA0
bool __stdcall FlyLocomotionClass::IsIonSensitive()
{
    TechnoTypeClass* type = LinkedTo->vf_33();
    return type->bools_D20[7] == 0;
}

// SYNTHETIC: GAMEMD 0x4D03A0
// FlyLocomotionClass::scalar deleting destructor
// The selected primary-table SEARCH_LIBRARY default is proved against retail.

// SYNTHETIC: GAMEMD 0x4D0510
// LocomotionClass::QueryInterface adjustor thunk (this-4)
// SYNTHETIC: GAMEMD 0x4D0520
// LocomotionClass::AddRef adjustor thunk (this-4)
// SYNTHETIC: GAMEMD 0x4D0530
// LocomotionClass::Release adjustor thunk (this-4)
