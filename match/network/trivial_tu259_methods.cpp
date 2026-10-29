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

// FUNCTION: GAMEMD 0x747F20
// Member getter (dword). Vtable slot 45 of UnitTypeClass (RTTI).
int UnitTypeClass::vf_45()
{
    return RulesInstance->RepairStep;
}

// FUNCTION: GAMEMD 0x748160
// Returns a constant. Vtable slot 12 of UnitTypeClass (RTTI).
int Obj_00748160::FUN_00748160() const
{
    return 0xE78;
}

// FUNCTION: GAMEMD 0x748170
// Returns a constant. Vtable slot 11 of UnitTypeClass (RTTI).
int Obj_00748170::FUN_00748170() const
{
    return 0x28;
}

// FUNCTION: GAMEMD 0x748180
// Member getter (dword). Vtable slot 16 of UnitTypeClass (RTTI).
int Obj_00748180::FUN_00748180() const
{
    return unknown_DF8;
}
