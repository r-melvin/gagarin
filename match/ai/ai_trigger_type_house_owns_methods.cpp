// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x41EAF0 and 0x41EE90.

#include "ai_trigger_type_house_owns_methods.h"

// FUNCTION: GAMEMD 0x41EAF0
//
// Does the target (enemy) house own the condition object in the amount the
// first comparator asks for? The count comes from the house's per-kind
// owned-type counter; no house or no object counts as zero.
//
// PARTIAL (5.1% by position on both twins; every instruction present).
// The prologue, the guard chain, the two virtual calls, the WhatAmI index
// table and jump table, all four counter arms
// (`MOV reg,[ESP+0x1C]; PUSH EBP; LEA ECX,[reg+0x55xx]`) and the six
// comparator tails are byte-identical in form to retail. The whole residual
// is that cl 8804 cross-jumps the four arms' identical call-and-epilogue
// tails into one shared block, where retail's build emits a copy per arm
// (three with their own `POP EDI; POP EBP; JMP join`, the fourth falling
// into the default tail). The tails are byte-identical, which is exactly
// the condition under which this compiler merges them, so no source
// phrasing separates them. Tried: the count switch inlined in each body
// (this form, kept), the same switch as an inline member of HouseClass, as
// a free inline taking the house by reference and by pointer, per-arm
// `return` instead of assignment, the comparator switch with per-case
// returns / all-break / a memory-homed result bool, and the type and count
// locals declared in both orders. Recorded as an 8447-vs-8804 difference
// (identical-tail cross-jumping), sibling to the loop-head duplication
// class already in the methodology.
bool AITriggerType_0041EAF0::EnemyHouseOwns(House_0041EAF0* calling, House_0041EAF0* target)
{
    bool result = false;
    if (target != 0) {
        TechnoType_0041EAF0* type = ConditionObject;
        int count;
        if (type == 0) {
            count = 0;
        } else {
            int index = (type->*type->Vptr->GetArrayIndex)();
            count = 0;
            switch ((type->*type->Vptr->WhatAmI)()) {
            case 7:    count = target->OwnedBuildingTypes.GetItemCount(index); break;
            case 0x28: count = target->OwnedUnitTypes.GetItemCount(index);     break;
            case 0x10: count = target->OwnedInfantryTypes.GetItemCount(index); break;
            case 3:    count = target->OwnedAircraftTypes.GetItemCount(index); break;
            }
        }
        switch (ComparatorOperand) {
        case 0: return count < Number;
        case 1: return count <= Number;
        case 2: return count == Number;
        case 3: return count >= Number;
        case 4: return count > Number;
        case 5: result = count != Number; break;
        }
    }
    return result;
}

// FUNCTION: GAMEMD 0x41EE90
//
// The same test against the calling (owner) house.
bool AITriggerType_0041EAF0::OwnerHouseOwns(House_0041EAF0* calling, House_0041EAF0* target)
{
    bool result = false;
    if (calling != 0) {
        TechnoType_0041EAF0* type = ConditionObject;
        int count;
        if (type == 0) {
            count = 0;
        } else {
            int index = (type->*type->Vptr->GetArrayIndex)();
            count = 0;
            switch ((type->*type->Vptr->WhatAmI)()) {
            case 7:    count = calling->OwnedBuildingTypes.GetItemCount(index); break;
            case 0x28: count = calling->OwnedUnitTypes.GetItemCount(index);     break;
            case 0x10: count = calling->OwnedInfantryTypes.GetItemCount(index); break;
            case 3:    count = calling->OwnedAircraftTypes.GetItemCount(index); break;
            }
        }
        switch (ComparatorOperand) {
        case 0: return count < Number;
        case 1: return count <= Number;
        case 2: return count == Number;
        case 3: return count >= Number;
        case 4: return count > Number;
        case 5: result = count != Number; break;
        }
    }
    return result;
}
