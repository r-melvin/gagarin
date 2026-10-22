// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu042_methods.h"

// FUNCTION: GAMEMD 0x46D070
// Returns a constant. Vtable slot 12 of CampaignClass (RTTI).
int Obj_0046D070::FUN_0046D070() const
{
    return 0x3A0;
}

// FUNCTION: GAMEMD 0x46D080
// Returns a constant. Vtable slot 11 of CampaignClass (RTTI).
int Obj_0046D080::FUN_0046D080() const
{
    return 0xA;
}
