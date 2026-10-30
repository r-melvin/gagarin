// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu259_methods.h"
#include "../_layout/infantry_type_class.h"
#include "../_layout/unit_type_class.h"
#include "../_layout/rules_class.h"

// The two Rules-backed type getters share this existing source provisionally;
// this placement does not attest an original TU boundary or source filename.
// FUNCTION: GAMEMD 0x524790
int InfantryTypeClass::vf_45()
{
    return RulesInstance->IRepairStep;
}

// FUNCTION: GAMEMD 0x7473C0
// Tail-forwards to another function. Vtable slot 40 of UnitTypeClass (RTTI).
void Obj_007473C0::FUN_007473C0()
{
    FUN_00711E80();
}

// FUNCTION: GAMEMD 0x7473D0
// Tail-forwards to another function. Vtable slot 41 of UnitTypeClass (RTTI).
void Obj_007473D0::FUN_007473D0()
{
    FUN_00711E90();
}

