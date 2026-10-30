// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Three locomotors (Jumpjet, Ship, Teleport) override the IUnknown
// AddRef/Release slots of their primary table (slots 1 and 2) with a body that
// only forwards to LocomotionClass::AddRef (0x55A950) / Release (0x55A970), as
// DropPodLocomotionClass does at 0x4B66A0. The owning class of each address is
// read from the RTTI-named primary vtable that holds it; the classes come from
// their canonical headers.
#include "loco_base.h"
#include "../_layout/jumpjet_locomotion_class.h"
#include "../_layout/ship_locomotion_class.h"
#include "../_layout/teleport_locomotion_class.h"
#include "walk_locomotion_class.h"

// FUNCTION: GAMEMD 0x0054DF50
ULONG __stdcall JumpjetLocomotionClass::AddRef()
{
    return LocomotionClass::AddRef();
}

// FUNCTION: GAMEMD 0x0054DF60
ULONG __stdcall JumpjetLocomotionClass::Release()
{
    return LocomotionClass::Release();
}

// FUNCTION: GAMEMD 0x006A4260
ULONG __stdcall ShipLocomotionClass::AddRef()
{
    return LocomotionClass::AddRef();
}

// FUNCTION: GAMEMD 0x006A4270
ULONG __stdcall ShipLocomotionClass::Release()
{
    return LocomotionClass::Release();
}

// FUNCTION: GAMEMD 0x0071A0E0
ULONG __stdcall TeleportLocomotionClass::AddRef()
{
    return LocomotionClass::AddRef();
}

// FUNCTION: GAMEMD 0x0071A0F0
ULONG __stdcall TeleportLocomotionClass::Release()
{
    return LocomotionClass::Release();
}
