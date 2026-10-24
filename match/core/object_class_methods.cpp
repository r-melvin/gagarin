// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Retail entry-origin byte evidence: AttachTrigger reads ObjectClass+0x34 and
// TagClass+0x2C, with RET 4 at 0x5F5B7E; SetHealthPercentage reads Health+0x6C,
// dispatches virtual slot +0x88, reads returned ObjectTypeClass+0xA0 and ends
// with RET 8 spanning 0x5F5CC5..0x5F5CC7; IsRedHP reads the same health/type fields and the
// RulesInstance pointer at 0x8871E0 / ConditionRed+0x1708, with RET at 0x5F5D19.
// At 0x5F5B4C are four NOPs; current Ghidra analysis records no function
// entry or xrefs there. Only the evidenced 0x5F5B50 entry is bound here.
// Method names remain hypotheses, confirmed only as far as the
// observed operations permit.

// LIBRARY: GAMEMD 0x7C5F00 -- __ftol, used by SetHealthPercentage.
#include "../_layout/object_class.h"
#include "rules_class.h"
#include "../_layout/object_type_class.h"

struct ObjectTagRefCountView
{
    char unknown_00[0x2C];
    int InstanceCount;
};
GG_STATIC_ASSERT(offsetof(ObjectTagRefCountView, InstanceCount) == 0x2C);
GG_STATIC_ASSERT(sizeof(ObjectTagRefCountView) == 0x30);

typedef ObjectTypeClass* (* ObjectHealthGetType)(const ObjectClass*);
struct ObjectHealthVtablePrefix
{
    char unknown_00[0x88];
    ObjectHealthGetType GetType;
};
GG_STATIC_ASSERT(offsetof(ObjectClass, AttachedTag) == 0x34);
GG_STATIC_ASSERT(offsetof(ObjectClass, Health) == 0x6C);
GG_STATIC_ASSERT(offsetof(ObjectHealthVtablePrefix, GetType) == 0x88);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Strength) == 0xA0);
GG_STATIC_ASSERT(offsetof(RulesClass, ConditionRed) == 0x1708);
GG_STATIC_ASSERT(sizeof(ObjectHealthGetType) == 4);

// FUNCTION: GAMEMD 0x5F3B50
ObjectClass::ObjectClass(const AbstractNoInit& noInit)
    : AbstractClass(noInit)
{
}

// FUNCTION: GAMEMD 0x5F5B50
bool ObjectClass::AttachTrigger(TagClass* tag)
{
    if (this->AttachedTag) {
        --((ObjectTagRefCountView*)this->AttachedTag)->InstanceCount;
        this->AttachedTag = 0;
    }
    if (tag) {
        this->AttachedTag = tag;
        ++((ObjectTagRefCountView*)tag)->InstanceCount;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x5F5C80
void ObjectClass::SetHealthPercentage(double percentage)
{
    if (percentage > 0.0) {
        this->Health = (int)(
            (static_cast<const ObjectHealthVtablePrefix*>(
                 this->PrimaryVTable())->GetType(this)->Strength)
            * percentage);
        if (this->Health == 0)
            this->Health = 1;
    } else {
        this->Health = 0;
    }
}

// FUNCTION: GAMEMD 0x5F5CD0
bool ObjectClass::IsRedHP() const
{
    return (double)this->Health
                 / (double)(static_cast<const ObjectHealthVtablePrefix*>(
                               this->PrimaryVTable())->GetType(this)->Strength)
               <= RulesInstance->ConditionRed
           && this->Health > 0;
}

// SYNTHETIC: GAMEMD 0x5F6DC0 -- compiler-generated scalar deleting destructor.
