// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and vtable slots read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x5F6CD0: `TEST byte ptr [ESI+0x14],1`
//   (AbstractFlags, the techno bit, behind a `TEST ESI,ESI` null test),
//   `MOV AL,[ESI+0x2A4]` (the object's own uncrushable byte), `MOV ECX,
//   [EDI+0x21C]` (the crusher's owning house, receiver of `CALL 0x4F9A90`
//   with `this` pushed), the slots `CALL [EAX+0x84]` (techno type, read on
//   both objects; bytes `[EAX+0xD29]` / `[EAX+0xD2A]` off it), `CALL
//   [EAX+0x88]` (object type; byte `[EAX+0x22D]` off it), `CALL [EAX+0x2C]`
//   (WhatAmI, compared with 6) and `CALL [EDX+0x160]` (a bool predicate).
//   Names cross-checked against YRpp ObjectClass.h / TechnoClass.h /
//   TechnoTypeClass.h / ObjectTypeClass.h (consult-only, no LICENSE); the
//   +0x21C / +0x2A4 / +0x22D members agree with match/_layout.
#ifndef GG_MATCH_CORE_OBJECT_CLASS_CRUSHABLE_METHODS_H
#define GG_MATCH_CORE_OBJECT_CLASS_CRUSHABLE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct ObjectClass;

// The two type objects, modelled only for the bytes read here.
struct TechnoTypeClass
{
    char _pad000[0xD29];   // +0x0000
    bool OmniCrusher;      // +0x0D29
    bool OmniCrushResistant; // +0x0D2A
};
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, OmniCrusher)        == 0xD29);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, OmniCrushResistant) == 0xD2A);

struct ObjectTypeClass
{
    char _pad000[0x22D];   // +0x0000
    bool Crushable;        // +0x022D
};
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Crushable) == 0x22D);

struct HouseClass
{
    // FUNCTION: GAMEMD 0x4F9A90 (decl; reloc) — HouseClass::IsAlliedWith.
    bool IsAlliedWith(ObjectClass* object);
};

// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_005F6CD0;

struct ObjectClass
{
    Vtbl_005F6CD0* Vtbl;    // +0x0000
    char _pad004[0x10];     // +0x0004
    int  AbstractFlags;     // +0x0014
    char _pad018[0x204];    // +0x0018
    HouseClass* Owner;      // +0x021C (TechnoClass)
    char _pad220[0x84];     // +0x0220
    bool Uncrushable;       // +0x02A4 (TechnoClass)

    // FUNCTION: GAMEMD 0x5F6CD0
    bool IsCrushable(ObjectClass* crusher);
};
GG_STATIC_ASSERT(offsetof(ObjectClass, AbstractFlags) == 0x14);
GG_STATIC_ASSERT(offsetof(ObjectClass, Owner)         == 0x21C);
GG_STATIC_ASSERT(offsetof(ObjectClass, Uncrushable)   == 0x2A4);

typedef int              (ObjectClass::*Fn02C_005F6CD0)();
typedef TechnoTypeClass* (ObjectClass::*Fn084_005F6CD0)();
typedef ObjectTypeClass* (ObjectClass::*Fn088_005F6CD0)();
typedef bool             (ObjectClass::*Fn160_005F6CD0)();

struct Vtbl_005F6CD0
{
    char _pad000[0x2C];               // +0x0000
    Fn02C_005F6CD0 WhatAmI;           // +0x002C
    char _pad030[0x84 - 0x30];        // +0x0030
    Fn084_005F6CD0 GetTechnoType;     // +0x0084
    Fn088_005F6CD0 GetType;           // +0x0088
    char _pad08C[0x160 - 0x8C];       // +0x008C
    Fn160_005F6CD0 At_160;            // +0x0160
};
GG_STATIC_ASSERT(offsetof(Vtbl_005F6CD0, WhatAmI)       == 0x2C);
GG_STATIC_ASSERT(offsetof(Vtbl_005F6CD0, GetTechnoType) == 0x84);
GG_STATIC_ASSERT(offsetof(Vtbl_005F6CD0, GetType)       == 0x88);
GG_STATIC_ASSERT(offsetof(Vtbl_005F6CD0, At_160)        == 0x160);

// Inlined helper: is the object a techno (AbstractFlags bit 0), null-safe.
inline bool IsTechno_005F6CD0(ObjectClass* object)
{
    return object != 0 && (object->AbstractFlags & 1) != 0;
}

#endif  // GG_MATCH_CORE_OBJECT_CLASS_CRUSHABLE_METHODS_H
