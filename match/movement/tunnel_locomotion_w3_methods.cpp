// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Small ILocomotion overrides of TunnelLocomotionClass read off retail gamemd.exe
//   v1.001 (ILocomotion vtable 0x7F5A24). Functions are in ascending retail address order.

#include "tunnel_locomotion_w3_methods.h"
#include "../_layout/foot_class.h"

// FUNCTION: GAMEMD 0x728A60
// Moving, and not in state 1.
bool __stdcall TunnelLocomotionClass::IsMovingNow()
{
    if (IsMoving() && State != 1) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x72A020
int __stdcall TunnelLocomotionClass::ZGradient()
{
    if (State == 3 || State == 2 || State == 7 || State == 6 || State == 5) {
        return 2;
    }
    return LocomotionClass::ZGradient();
}

// FUNCTION: GAMEMD 0x72A060
bool __stdcall TunnelLocomotionClass::IsToHaveShadow()
{
    if (State == 0 || State == 1 || State == 7 || State == 2 || State == 6) {
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x72A1A0
int __stdcall TunnelLocomotionClass::InWhichLayer()
{
    return State != 4 ? 2 : 0;
}

// FUNCTION: GAMEMD 0x72A1C0
int __stdcall TunnelLocomotionClass::CanFire()
{
    int result = LocomotionClass::CanFire();
    if (!result && State) {
        result = 7;
    }
    return result;
}

// FUNCTION: GAMEMD 0x72A0E0
// Turn the linked unit's body toward the given facing.
void __stdcall TunnelLocomotionClass::DoTurn(unsigned long dir)
{
    DirStruct d = *reinterpret_cast<DirStruct*>(&dir);
    LinkedTo->PrimaryFacing.SetDesired(d);
}
