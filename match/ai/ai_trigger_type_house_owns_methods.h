// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x41EAF0 / 0x41EE90: the trigger's `[EBX+0xD8]`
//   (ConditionObject), `[EBX+0xE4]` (Conditions[0].Number) and `[EBX+0xE8]`
//   (Conditions[0].ComparatorOperand, 0..5 through a jump table); the
//   type's vtable slots `[EAX+0x40]` (array index, called first) and
//   `[EDX+0x2C]` (WhatAmI, switched on minus 3 through a byte index table:
//   7 = BuildingType, 0x28 = UnitType, 0x10 = InfantryType, 3 =
//   AircraftType); the house's four CounterClass objects at +0x5550
//   (OwnedBuildingTypes), +0x5564 (OwnedUnitTypes), +0x5578
//   (OwnedInfantryTypes), +0x558C (OwnedAircraftTypes) each handed to
//   0x49FAE0 (CounterClass::GetItemCount, one pushed index). Names
//   cross-checked against YRpp AITriggerTypeClass.h / HouseClass.h
//   (consult-only; NO LICENSE).
#ifndef GG_MATCH_AI_AI_TRIGGER_TYPE_HOUSE_OWNS_METHODS_H
#define GG_MATCH_AI_AI_TRIGGER_TYPE_HOUSE_OWNS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// CounterClass — only GetItemCount is called.
struct Counter_0041EAF0
{
    char opaque[0x14];
    // FUNCTION: GAMEMD 0x49FAE0 (decl; reloc) — CounterClass::GetItemCount.
    int GetItemCount(int index);
};
GG_STATIC_ASSERT(sizeof(Counter_0041EAF0) == 0x14);

struct TechnoType_0041EAF0;

// HouseClass — the four owned-type counters.
struct House_0041EAF0
{
    char              _pad000[0x5550];        // +0x0000
    Counter_0041EAF0  OwnedBuildingTypes;     // +0x5550
    Counter_0041EAF0  OwnedUnitTypes;         // +0x5564
    Counter_0041EAF0  OwnedInfantryTypes;     // +0x5578
    Counter_0041EAF0  OwnedAircraftTypes;     // +0x558C
};

GG_STATIC_ASSERT(offsetof(House_0041EAF0, OwnedBuildingTypes) == 0x5550);
GG_STATIC_ASSERT(offsetof(House_0041EAF0, OwnedUnitTypes)     == 0x5564);
GG_STATIC_ASSERT(offsetof(House_0041EAF0, OwnedInfantryTypes) == 0x5578);
GG_STATIC_ASSERT(offsetof(House_0041EAF0, OwnedAircraftTypes) == 0x558C);

struct TypeVtbl_0041EAF0;

// TechnoTypeClass — only two virtuals are called.
struct TechnoType_0041EAF0
{
    TypeVtbl_0041EAF0* Vptr;   // +0x0000
};
typedef int (TechnoType_0041EAF0::*Fn2C_0041EAF0)();
typedef int (TechnoType_0041EAF0::*Fn40_0041EAF0)();
struct TypeVtbl_0041EAF0
{
    char           _pad000[0x2C];   // +0x0000
    Fn2C_0041EAF0  WhatAmI;         // +0x002C
    char           _pad030[0x10];   // +0x0030
    Fn40_0041EAF0  GetArrayIndex;   // +0x0040
};
GG_STATIC_ASSERT(offsetof(TypeVtbl_0041EAF0, WhatAmI)       == 0x2C);
GG_STATIC_ASSERT(offsetof(TypeVtbl_0041EAF0, GetArrayIndex) == 0x40);

// AITriggerTypeClass — the condition object and the first comparator.
struct AITriggerType_0041EAF0
{
    char                  _pad000[0xD8];     // +0x0000
    TechnoType_0041EAF0*  ConditionObject;   // +0x00D8
    char                  _pad0DC[8];        // +0x00DC
    int                   Number;            // +0x00E4 Conditions[0].Number
    int                   ComparatorOperand; // +0x00E8 Conditions[0].ComparatorOperand

    // FUNCTION: GAMEMD 0x41EAF0 — AITriggerTypeClass::EnemyHouseOwns.
    bool EnemyHouseOwns(House_0041EAF0* calling, House_0041EAF0* target);
    // FUNCTION: GAMEMD 0x41EE90 — AITriggerTypeClass::OwnerHouseOwns.
    bool OwnerHouseOwns(House_0041EAF0* calling, House_0041EAF0* target);
};
GG_STATIC_ASSERT(offsetof(AITriggerType_0041EAF0, ConditionObject)   == 0xD8);
GG_STATIC_ASSERT(offsetof(AITriggerType_0041EAF0, Number)            == 0xE4);
GG_STATIC_ASSERT(offsetof(AITriggerType_0041EAF0, ComparatorOperand) == 0xE8);

#endif  // GG_MATCH_AI_AI_TRIGGER_TYPE_HOUSE_OWNS_METHODS_H
