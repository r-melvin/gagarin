// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU022 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x41e160-0x4206ef,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// Retail RTTI TypeDescriptors 0x8181B8 and 0x8181F8 identify
// VectorClass<AlphaLightingRemapClass*> and DynamicVectorClass<AlphaLightingRemapClass*>; the latter's
// CHD names the former as its zero-offset base.
// Full entry spans bind these methods; original TUs and standalone constructors
// are not established. No GX matches the complete derived deleting wrapper.
//
// Constant-return and identity leaves, ordered ascending by retail address.
//
// FindOrAllocate, ordered ascending by retail address, written out longhand per
// the family rule.
//
// The whole body sits inside one positive guard so that the single `return 0`
// lands in the trailing block, where retail has it at the very end. Written as
// three early `return 0` statements it scores 15.8% - every rejection gets its
// own inline epilogue and everything after shifts.

#include "../core/vector_class_operations.h"
class AlphaLightingRemapClass;

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// VTABLE: GAMEMD 0x7E2AF0 -- VectorClass<AlphaLightingRemapClass*>.
template class VectorClass<AlphaLightingRemapClass*>;
// VTABLE: GAMEMD 0x7E2AD0 -- DynamicVectorClass<AlphaLightingRemapClass*>.
template class DynamicVectorClass<AlphaLightingRemapClass*>;

typedef VectorClass<AlphaLightingRemapClass*> GgAlphaLightingRemapVector;
typedef DynamicVectorClass<AlphaLightingRemapClass*> GgAlphaLightingRemapDynamicVector;
GG_STATIC_ASSERT(sizeof(AlphaLightingRemapClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgAlphaLightingRemapVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAlphaLightingRemapVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAlphaLightingRemapVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAlphaLightingRemapVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAlphaLightingRemapVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAlphaLightingRemapVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgAlphaLightingRemapDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgAlphaLightingRemapDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgAlphaLightingRemapDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgAlphaLightingRemapDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgAlphaLightingRemapDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgAlphaLightingRemapDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgAlphaLightingRemapDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgAlphaLightingRemapDynamicVector, CapacityIncrement) == 0x14);

#include "ai_trigger_charged_methods.h"

#include "ai_trigger_type_house_owns_methods.h"

#include "ai_trigger_save_list_methods.h"

#include "threshold_compare_methods.h"

#include "../core/const_return_stub_methods.h"

#include "../core/find_or_allocate_methods.h"

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x41F0D0
//
// AI trigger condition: is the calling house's Iron Curtain nearly charged?
// Walks the house's superweapon list for the first one whose type is
// IronCurtain (1); it must exist and be present, and the fraction of its
// recharge still outstanding must be no more than 1 - AIMinorSuperReadyPercent.
// The target house is ignored.
//
// Retail converts both integers after the GetRechargeTime call (`FILD total;
// FILD left; FDIV ST0,ST1`, the divisor left on the stack and dropped by the
// trailing `FSTP ST0`): that is the float-typed `total` local divided into a
// cast `left`. An all-int `(float)left / (float)total` folds to `FIDIV`, and
// nesting the call inside the expression converts `left` before the call.
// The timer read is the inlined CDTimerClass::GetTimeLeft in the header; its
// `else return 0` arm is what makes the paused path share the single spill
// store and the expired path store its zero out of line.
bool AITriggerTypeClass::IronCurtainCharged(HouseClass* callingHouse, HouseClass* targetHouse) const
{
    if (callingHouse == 0) {
        return false;
    }
    for (int i = 0; i < callingHouse->SupersCount; i++) {
        if (callingHouse->SupersItems[i]->Type->Type == 1) {
            SuperClass* sw = callingHouse->SupersItems[i];
            if (sw == 0) {
                return false;
            }
            if (!sw->IsPresent) {
                return false;
            }
            int left = sw->RechargeTimer.GetTimeLeft();
            float total = (float)sw->GetRechargeTime();
            if ((float)left / total > 1.0f - Rules->AIMinorSuperReadyPercent) {
                return false;
            }
            return true;
        }
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x41F180
//
// Same test for the Chronosphere (type 3).
bool AITriggerTypeClass::ChronoSphereCharged(HouseClass* callingHouse, HouseClass* targetHouse) const
{
    if (callingHouse == 0) {
        return false;
    }
    for (int i = 0; i < callingHouse->SupersCount; i++) {
        if (callingHouse->SupersItems[i]->Type->Type == 3) {
            SuperClass* sw = callingHouse->SupersItems[i];
            if (sw == 0) {
                return false;
            }
            if (!sw->IsPresent) {
                return false;
            }
            int left = sw->RechargeTimer.GetTimeLeft();
            float total = (float)sw->GetRechargeTime();
            if ((float)left / total > 1.0f - Rules->AIMinorSuperReadyPercent) {
                return false;
            }
            return true;
        }
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x41F230
//
// Compare the node's measured value against this object's threshold using
// whichever of six relational operators is selected. A missing node, or an
// operator outside the table, is false.
//
// Every case assigns the function-scope `result` and `break`s to the single
// `return result` at the end. That is what keeps the result in BL — the
// register it was zeroed into at entry (`XOR BL,BL`) — with each case's
// `SETcc BL; MOV AL,BL` and its own epilogue for cases 0..4, while case 5
// falls into the default exit at 0x41F2BD. Returning per case (`return value
// < Threshold;` or `result = ...; return result;`) makes VC6 write each
// `SETcc` straight to AL and drops the five `MOV AL,BL` (30.4%); an inline
// helper holding the switch adds an extra register round-trip (7.1%).
bool Obj_0041F230::FUN_0041F230(int, Node_0041F230* node)
{
    bool result = false;
    if (node != 0) {
        int value = node->Sub.Vptr->At_18(&node->Sub);
        switch (this->Op) {
        case 0:
            result = value < this->Threshold;
            break;
        case 1:
            result = value <= this->Threshold;
            break;
        case 2:
            result = value == this->Threshold;
            break;
        case 3:
            result = value >= this->Threshold;
            break;
        case 4:
            result = value > this->Threshold;
            break;
        case 5:
            result = value != this->Threshold;
            break;
        }
    }
    return result;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x41F490
//
// Rewrite the AI trigger list into an INI. First every key already in the
// list section is walked, its value read into a small buffer, and the section
// named by that value cleared; then the list section itself is cleared; then
// every trigger type whose global flag matches the request writes itself back
// through its +0x68 virtual. A non-global (map) save also rewrites the enable
// section, one bool per trigger type keyed by its name.
//
// The key count is hoisted into a register for the first loop, but the
// section-name pointers are globals and are re-read after every call; the
// item loops re-read both the item table and the count each time round.
void AITriggerType_0041F490::SaveToINIList(CCINI_0041F490* ini, int isGlobal)
{
    char buffer[32];
    int  i;

    int count = ini->GetKeyCount(DAT_007E2A18);
    for (i = 0; i < count; i++) {
        const char* key = ini->GetKeyName(DAT_007E2A18, i);
        ini->ReadString(DAT_007E2A18, key, STR_00889F64, buffer, 32);
        ini->Clear(buffer, 0);
    }
    ini->Clear(DAT_007E2A18, 0);

    for (i = 0; i < DAT_00A8B200.Count; i++) {
        AITriggerType_0041F490* item = DAT_00A8B200[i];
        if (item->IsGlobal == isGlobal) {
            (item->*item->Vtbl->At_68)(ini);
        }
    }

    if (isGlobal == 0) {
        ini->Clear(DAT_007E2A1C, 0);
        for (i = 0; i < DAT_00A8B200.Count; i++) {
            AITriggerType_0041F490* item = DAT_00A8B200[i];
            ini->WriteBool(DAT_007E2A1C, item->ID, item->IsEnabled);
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x41FCA0
char* FUN_0041FCA0(const char* name)
{
    if (FUN_007C8D20(STR_00817474, name) != 0
        && FUN_007C8D20(STR_00817694, name) != 0) {

        for (int i = 0; i < DAT_00A8B210; i++) {
            if (FUN_007C8D20(DAT_00A8B204[i] + 0x24, name) == 0) {
                return DAT_00A8B204[i];
            }
        }

        void* item = FUN_007C8E17(0x110);

        if (item != 0) {
            return ((Item*)item)->FUN_0041E350(name);
        }
    }

    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x420120
void* FUN_00420120(void* self)
{
    return self;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x420370
// DynamicVectorClass<AlphaLightingRemapClass*>::Clear
// FUNCTION: GAMEMD 0x4203A0
// DynamicVectorClass<AlphaLightingRemapClass*>::Slot5
// FUNCTION: GAMEMD 0x4203C0
// VectorClass<AlphaLightingRemapClass*>::Slot6
// FUNCTION: GAMEMD 0x4203D0
// VectorClass<AlphaLightingRemapClass*>::operator==
// FUNCTION: GAMEMD 0x420410
// VectorClass<AlphaLightingRemapClass*>::SetCapacity
// FUNCTION: GAMEMD 0x4204C0
// VectorClass<AlphaLightingRemapClass*>::Clear
// FUNCTION: GAMEMD 0x4204F0
// VectorClass<AlphaLightingRemapClass*>::FindItemIndex
// FUNCTION: GAMEMD 0x420530
// VectorClass<AlphaLightingRemapClass*>::Slot5
// FUNCTION: GAMEMD 0x420550
// DynamicVectorClass<AlphaLightingRemapClass*>::SetCapacity
// FUNCTION: GAMEMD 0x420600
// DynamicVectorClass<AlphaLightingRemapClass*>::FindItemIndex
// SYNTHETIC: GAMEMD 0x420630
// VectorClass<AlphaLightingRemapClass*>::scalar deleting destructor
// SYNTHETIC: GAMEMD 0x420680
// DynamicVectorClass<AlphaLightingRemapClass*>::scalar deleting destructor

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA8B204
char** DAT_00A8B204;
// GLOBAL: GAMEMD 0xA8B210
int DAT_00A8B210;
// END defined globals
