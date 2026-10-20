// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x5F5DD0: Health `FILD dword ptr [ESI+0x6C]`, the
//   GetType() virtual `CALL [EAX+0x88]`, Strength `FILD dword ptr [EAX+0xA0]`,
//   and the two RulesClass doubles `FCOMP qword ptr [ECX+0x1708]` /
//   `[EAX+0x1700]` with ECX/EAX = [0x8871E0]. The method name and the
//   Red/Yellow/Green value order come from YRpp (consult-only, no LICENSE).
//
// ObjectClass::GetHealthStatus — which of the three health bands the object
// sits in, from Health / GetType()->Strength against the two rules thresholds.
#ifndef GG_MATCH_CORE_OBJECT_CLASS_HEALTH_STATUS_METHODS_H
#define GG_MATCH_CORE_OBJECT_CLASS_HEALTH_STATUS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/object_class.h"   // ObjectClass: Health @0x6C

GG_STATIC_ASSERT(offsetof(ObjectClass, Health) == 0x6C);

// ObjectTypeClass — only Strength @0xA0 is read (`FILD dword ptr [EAX+0xA0]`).
struct HealthObjType
{
    char _pad00[0xA0];
    int  Strength;   // +0xA0
};
GG_STATIC_ASSERT(offsetof(HealthObjType, Strength) == 0xA0);

// RulesClass — the two health-band thresholds. Retail compares the fraction
// against +0x1708 first (the same field ObjectClass::IsRedHP @0x5F5CD0 uses),
// then against +0x1700 for the middle band.
struct HealthRules
{
    char   _pad00[0x1700];
    double ConditionYellow;   // +0x1700
    double ConditionRed;      // +0x1708
};
GG_STATIC_ASSERT(offsetof(HealthRules, ConditionYellow) == 0x1700);
GG_STATIC_ASSERT(offsetof(HealthRules, ConditionRed)    == 0x1708);

// GLOBAL: GAMEMD 0x8871E0 — RulesClass::Instance (pointer).
extern HealthRules* HealthRulesInstance;

// GetType() — primary-vtable slot +0x88, zero stack arguments. Modelled as a
// __fastcall pointer so VC6 emits `MOV EAX,[ESI]; CALL [EAX+0x88]` with ECX =
// this and nothing pushed.
typedef HealthObjType* (__fastcall* HealthGetTypeFunc)(const ObjectClass*);
#define HEALTH_GET_TYPE(obj) \
    ((*(HealthGetTypeFunc*)(*(char**)(obj) + 0x88))(obj))

// No-data host over the committed ObjectClass spine; layout identical.
struct ObjectHealthStatus : ObjectClass
{
    // FUNCTION: GAMEMD 0x5F5DD0  ObjectClass::GetHealthStatus  (__thiscall)
    int GetHealthStatus() const;
};

#endif  // GG_MATCH_CORE_OBJECT_CLASS_HEALTH_STATUS_METHODS_H
