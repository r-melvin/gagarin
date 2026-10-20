// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 via the local Ghidra CLI
//   (member-access + virtual-call disassembly at 0x5F5B4C / 0x5F5B50 /
//   0x5F5C80 / 0x5F5CD0). Signatures cross-checked against YRpp ObjectClass.h
//   (consult-only, no LICENSE; every offset reconfirmed numerically below).
//
// Four small ObjectClass accessors layered on the committed instance-side spine
// (../_layout/object_class.h). The spine models the COM vptrs as plain data
// fields, so deriving a no-data host struct adds no vtable and keeps `this` and
// every offset identical; the methods just need their own declarations to emit
// the `?Method@ObjectAccessors@@` __thiscall symbols the differ slices.
#ifndef GG_MATCH_CORE_OBJECT_CLASS_METHODS_H
#define GG_MATCH_CORE_OBJECT_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/object_class.h"   // ObjectClass: AttachedTag@0x34, Health@0x6C

// Re-assert the two spine members these accessors touch (self-guards the TU).
GG_STATIC_ASSERT(offsetof(ObjectClass, AttachedTag) == 0x34);
GG_STATIC_ASSERT(offsetof(ObjectClass, Health)      == 0x6C);

// TagClass — only the +0x2C reference count is touched here (dec on detach,
// inc on attach). `MOV EDX,[EAX+0x2C]; DEC EDX; MOV [EAX+0x2C],EDX` @0x5F5B57.
struct ObjTag
{
    char _pad00[0x2C];
    int  RefCount;   // +0x2C
};
GG_STATIC_ASSERT(offsetof(ObjTag, RefCount) == 0x2C);

// ObjectTypeClass — GetType() result; only Strength@0xA0 is read (FILD, int).
// `FILD dword ptr [EAX+0xA0]` @0x5F5C9C / 0x5F5CE5.
struct ObjType
{
    char _pad00[0xA0];
    int  Strength;   // +0xA0
};
GG_STATIC_ASSERT(offsetof(ObjType, Strength) == 0xA0);

// RulesClass — only ConditionRed@0x1708 (double) is read.
// `FCOMP qword ptr [ECX+0x1708]` @0x5F5CF5 with ECX = [0x008871E0].
struct ObjRules
{
    char   _pad00[0x1708];
    double ConditionRed;   // +0x1708
};
GG_STATIC_ASSERT(offsetof(ObjRules, ConditionRed) == 0x1708);

// GLOBAL: GAMEMD 0x008871E0  RulesClass::Instance (pointer; MOV ECX,[0x8871E0]).
extern ObjRules* RulesClassInstance;

// GetType() — virtual at primary-vtable slot +0x88 (CALL [vtbl+0x88]). Modelled
// as a __fastcall fn-pointer through the vtable so VC6 reproduces the indirect
// __thiscall (ECX = this, no stack args) exactly, matching `MOV EAX,[ESI];
// CALL [EAX+0x88]`.
typedef ObjType* (__fastcall* ObjGetTypeFunc)(const ObjectClass*);

// No-data host for the four methods; layout identical to ObjectClass.
struct ObjectAccessors : ObjectClass
{
    // FUNCTION: GAMEMD 0x5F5B4C  ObjectClass::ReplaceTag        (__thiscall)
    bool ReplaceTag(ObjTag* pTag);
    // FUNCTION: GAMEMD 0x5F5B50  ObjectClass::AttachTrigger     (__thiscall)
    bool AttachTrigger(ObjTag* pTag);
    // FUNCTION: GAMEMD 0x5F5C80  ObjectClass::SetHealthPercentage (__thiscall)
    void SetHealthPercentage(double percentage);
    // FUNCTION: GAMEMD 0x5F5CD0  ObjectClass::IsRedHP           (__thiscall)
    bool IsRedHP() const;
};

#endif  // GG_MATCH_CORE_OBJECT_CLASS_METHODS_H
