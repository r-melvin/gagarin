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
#include "../_layout/object_class.h"
#include "../_layout/object_type_class.h"
#include "../economy/house_class_ally_methods.h"

// Focused REA/Ghidra analysis reconfirms the full 0xC3-byte entry, including
// RET 4 at 0x5F6D90, and each field/slot operand documented above.
// Sparse view of the two techno-type bytes read by this function only.
struct CrushTechnoTypeView
{
    char unknown_00[0xD29];
    bool OmniCrusher;
    bool OmniCrushResistant;
};
GG_STATIC_ASSERT(offsetof(CrushTechnoTypeView, OmniCrusher) == 0xD29);
GG_STATIC_ASSERT(offsetof(CrushTechnoTypeView, OmniCrushResistant) == 0xD2A);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Crushable) == 0x22D);

// Confirmed ObjectClass prefix plus the two techno fields read here. This is
// a sparse view; it does not claim the intermediate direct-base hierarchy.
struct CrushTechnoObjectView : ObjectClass
{
    char unknown_AC[0x21C - 0xAC];
    HouseClass* Owner;
    char unknown_220[0x2A4 - 0x220];
    bool Uncrushable;
};
GG_STATIC_ASSERT(offsetof(ObjectClass, _vtable_IPersistStream) == 0);
GG_STATIC_ASSERT(offsetof(ObjectClass, AbstractFlags) == 0x14);
GG_STATIC_ASSERT(offsetof(CrushTechnoObjectView, Owner) == 0x21C);
GG_STATIC_ASSERT(offsetof(CrushTechnoObjectView, Uncrushable) == 0x2A4);

// Member pointers model the observed ECX-only slot-call ABI. Their owner
// type does not establish the original declaring class or complete vtables.
// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_005F6CD0;

typedef int              (ObjectClass::*Fn02C_005F6CD0)();
typedef CrushTechnoTypeView* (ObjectClass::*Fn084_005F6CD0)();
typedef ObjectTypeClass* (ObjectClass::*Fn088_005F6CD0)();
typedef bool             (ObjectClass::*Fn160_005F6CD0)();

struct Vtbl_005F6CD0
{
    char unknown_00[0x2C];               // +0x0000
    Fn02C_005F6CD0 WhatAmI;           // +0x002C
    char unknown_30[0x84 - 0x30];        // +0x0030
    Fn084_005F6CD0 GetTechnoType;     // +0x0084
    Fn088_005F6CD0 GetType;           // +0x0088
    char unknown_8C[0x160 - 0x8C];       // +0x008C
    Fn160_005F6CD0 At_160;            // +0x0160
};
GG_STATIC_ASSERT(sizeof(Fn02C_005F6CD0) == 4);
GG_STATIC_ASSERT(sizeof(Fn084_005F6CD0) == 4);
GG_STATIC_ASSERT(sizeof(Fn088_005F6CD0) == 4);
GG_STATIC_ASSERT(sizeof(Fn160_005F6CD0) == 4);
GG_STATIC_ASSERT(offsetof(Vtbl_005F6CD0, WhatAmI)       == 0x2C);
GG_STATIC_ASSERT(offsetof(Vtbl_005F6CD0, GetTechnoType) == 0x84);
GG_STATIC_ASSERT(offsetof(Vtbl_005F6CD0, GetType)       == 0x88);
GG_STATIC_ASSERT(offsetof(Vtbl_005F6CD0, At_160)        == 0x160);

inline const CrushTechnoObjectView* CrushTechno(const ObjectClass* object)
{
    return static_cast<const CrushTechnoObjectView*>(object);
}

// Inlined helper: is the object a techno (AbstractFlags bit 0), null-safe.
inline bool IsTechno_005F6CD0(ObjectClass* object)
{
    return object != 0 && (object->AbstractFlags & 1) != 0;
}

#endif  // GG_MATCH_CORE_OBJECT_CLASS_CRUSHABLE_METHODS_H
