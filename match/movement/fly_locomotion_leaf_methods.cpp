// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   The leaf half of FlyLocomotionClass. Bytes diffed against the user's
//   retail gamemd.exe v1.001; bodies ordered ascending by retail address.
//   Every entry point here came out of a raw-byte sweep of 0x4CC100-0x4D0600
//   for NOP runs ending on a four-byte boundary, not out of the Ghidra
//   function list, which under-segments this region badly.
#include "fly_locomotion_leaf_methods.h"
#include "loco_base.h"

// VTABLE: GAMEMD 0x7E89F4 — the locomotor interface vtable (base offset 4).
// VTABLE: GAMEMD 0x7E8AC0 — the persist vtable (base offset 0).
// GLOBAL: GAMEMD 0x8B3C78 — the engine's unset coordinate.
// GLOBAL: GAMEMD 0xA8B230 — the scenario object.

// ILocomotion slot +0x0C — bind the locomotor to a client. The base does the
// binding; this override then records whether the client is a ground-bound
// building-like object whose type carries the gate byte.
// FUNCTION: GAMEMD 0x4CCA20
GgHRESULT __stdcall FlyLocoLinkTo_004CCA20(FlyLocoIface* self,
                                           Foot_004CCA20* obj)
{
    LocomotionClass* base = reinterpret_cast<LocomotionClass*>(
        reinterpret_cast<char*>(self) - sizeof(void*));
    GgHRESULT hr = base->LocomotionClass::LinkToObject(
        reinterpret_cast<FootClass*>(obj));
    if (hr == 0) {
        if (obj != 0 && (obj->*obj->Vtbl->At_2C)() == 2 &&
            obj->Type->At_E0D != 0) {
            self->IsOnBridge = 1;
        } else {
            self->IsOnBridge = 0;
        }
    }
    return hr;
}

// The destructor: re-seat both of this class's vtables over the base's, then
// tail into the base destructor. cl turns the trailing call into the bare
// jump retail has.
// FUNCTION: GAMEMD 0x4CCA70
void FlyLocoObject::Destroy()
{
    PersistVptr = (void*)0x7E8AC0;
    LocomotorVptr = (void*)0x7E89F4;
    ((LocoBase_0055A6F0*)this)->Destroy();
}

// ILocomotion slot +0x10 — a flyer casts a shadow while it is elevating or
// while its client still has altitude.
// FUNCTION: GAMEMD 0x4CCA90
int __stdcall FlyLocoIsToHaveShadow_004CCA90(FlyLocoIface* self)
{
    if (self->HasMoveOrder == 0 && self->LinkedTo->Altitude <= 0.0f) {
        return 0;
    }
    return 1;
}

// ILocomotion slot +0x80 — true whenever the locomotor is holding a height.
// FUNCTION: GAMEMD 0x4CCAC0
char __stdcall FlyLocoIsPowered_004CCAC0(FlyLocoIface* self)
{
    if (self->Height == 0.0) {
        return 0;
    }
    return 1;
}

// ILocomotion slot +0x14 — where the flyer is headed: its own destination
// while it is still aloft, and the engine's unset coordinate once it is not.
// FUNCTION: GAMEMD 0x4CCAE0
Coord_004CCAE0 __stdcall FlyLocoIface::GetDestination()
{
    Coord_004CCAE0 result;
    if ((char)IsToHaveShadow()) {
        result.X = Destination.X;
        result.Y = Destination.Y;
        result.Z = Destination.Z;
        return result;
    }
    result.X = UnsetCoord_008B3C78.X;
    result.Y = UnsetCoord_008B3C78.Y;
    result.Z = UnsetCoord_008B3C78.Z;
    return result;
}

// ILocomotion slot +0x30 — a flyer contributes no voxel shadow offset.
// FUNCTION: GAMEMD 0x4CF940
Pair_004CF940 __stdcall FlyLocoIface::GetShadowOffset()
{
    Pair_004CF940 zero;
    zero.A = 0;
    zero.B = 0;
    return zero;
}

// ILocomotion slot +0x4C — hand the client's own target slot the object it
// should aim at. Retail copies the parameter over itself and passes that
// slot's address, which is what taking the address of a by-value handle does.
// FUNCTION: GAMEMD 0x4CFC10
void __stdcall FlyLocoAssignTarget_004CFC10(FlyLocoIface* self, void* target)
{
    void* handle = target;
    self->LinkedTo->TargetSlot.Assign(&handle);
}

// Start the touchdown spin at a random rate, half the time in the opposite
// direction. The out-of-line form of the block 0x4CFD20 has inlined.
// FUNCTION: GAMEMD 0x4CFDD0
void FlyLocoObject::StartSpin()
{
    IsSpinning = 1;
    SpinRate = Scenario_00A8B230->RandomNumber.RandomRanged(0x14, 0x1E);
    if (Scenario_00A8B230->RandomNumber.RandomRanged(0, 0x63) < 0x32) {
        SpinRate = -SpinRate;
    }
}

// ILocomotion slot +0x84 — the client's own rate scaled by the locomotor's
// held height, truncated to an integer.
// FUNCTION: GAMEMD 0x4CFE20
int __stdcall FlyLocoScaledRate_004CFE20(FlyLocoIface* self)
{
    Foot_004CCA20* linkedTo = self->LinkedTo;
    Owner_004CFE20* owner = (linkedTo->*linkedTo->Vtbl->At_84)();
    return (int)(owner->At_678 * self->Height);
}

// ILocomotion slot +0x90 — the draw layer: one while landing, zero while
// taking off, and otherwise two or three according to the shadow.
// FUNCTION: GAMEMD 0x4CFE50
int __stdcall FlyLocoDrawLayer_004CFE50(FlyLocoIface* self)
{
    if (self->IsLanding != 0) {
        return 1;
    }
    if (self->IsTakingOff != 0) {
        return 0;
    }
    return (char)self->IsToHaveShadow() ? 2 : 3;
}
