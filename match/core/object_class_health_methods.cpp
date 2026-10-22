// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// REA/Ghidra confirms the full 0x20-byte entry at 0x5F5C60: signed Health+6C
// is converted before the primary virtual call at +88; the returned type's
// signed Strength+A0 is the divisor. The result remains in ST(0); RET has
// no stack argument. This uses the shared explicit-vptr class layout.
// /O1 emits a shorter 0x1E-byte body; /O2 matches all 0x20 bytes. Both /GX
// settings match under /O2, so this leaf does not identify the exception flag.
#include "../_layout/object_class.h"
#include "../_layout/object_type_class.h"
#include "rules_class.h"

typedef ObjectTypeClass* (* ObjectHealthGetType)(const ObjectClass*);
struct ObjectHealthVtablePrefix
{
    char unknown_00[0x88];
    ObjectHealthGetType GetType;
};
GG_STATIC_ASSERT(offsetof(ObjectClass, Health) == 0x6C);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Strength) == 0xA0);
GG_STATIC_ASSERT(offsetof(ObjectHealthVtablePrefix, GetType) == 0x88);
GG_STATIC_ASSERT(sizeof(ObjectHealthGetType) == 4);

// FUNCTION: GAMEMD 0x5F5C60
double ObjectClass::GetHealthPercentage() const
{
    double health = Health;
    const ObjectHealthVtablePrefix* vtable =
        static_cast<const ObjectHealthVtablePrefix*>(PrimaryVTable());
    return health / vtable->GetType(this)->Strength;
}

#define OBJECT_HEALTH_TYPE(object) \
    (static_cast<const ObjectHealthVtablePrefix*>( \
        (object)->PrimaryVTable())->GetType(object))

// FUNCTION: GAMEMD 0x5F5D20
// Two separate virtual calls and ratio evaluations occur in retail. The
// predicate returns an int; its original name is not confirmed by the binary.
int ObjectClass::FUN_005F5D20() const
{
    if ((double)Health / (double)OBJECT_HEALTH_TYPE(this)->Strength
        > RulesInstance->ConditionRed) {
        if ((double)Health / (double)OBJECT_HEALTH_TYPE(this)->Strength
            <= RulesInstance->ConditionYellow) {
            return 1;
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x5F5DD0
//
// Health band: 0 (red) when the health fraction is at or below ConditionRed and
// the object is still alive; 1 (yellow) when it is above ConditionRed but at or
// below ConditionYellow; otherwise 2 (green). A dead object (Health <= 0) falls
// through the first test and lands on 2.
//
// The fraction is spelled out three times because GetType() is virtual: each
// band test re-issues the call, exactly as retail does (three `FILD [ESI+0x6C];
// FSTP; CALL [vtbl+0x88]; FILD [EAX+0xA0]; FDIVR` groups).
int ObjectClass::GetHealthStatus() const
{
    if ((double)this->Health / (double)OBJECT_HEALTH_TYPE(this)->Strength
            <= RulesInstance->ConditionRed
        && this->Health > 0)
    {
        return 0;
    }

    if ((double)this->Health / (double)OBJECT_HEALTH_TYPE(this)->Strength
            > RulesInstance->ConditionRed
        && (double)this->Health / (double)OBJECT_HEALTH_TYPE(this)->Strength
            <= RulesInstance->ConditionYellow)
    {
        return 1;
    }

    return 2;
}

#undef OBJECT_HEALTH_TYPE
