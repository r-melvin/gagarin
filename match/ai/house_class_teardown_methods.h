// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, globals and the vtable slot read numerically off the user's
//   retail gamemd.exe v1.001 via the local Ghidra CLI at 0x4FB920:
//   `[0xA8EC88]` / `[0xA8EC7C]` (TechnoClass::Array Count/Items, base
//   0xA8EC78), `CMP [ECX+0x21C],EDI` (TechnoClass::Owner), `[0xA8EAF8]` /
//   `[0xA8EAEC]` (TriggerClass::Array Count/Items, base 0xA8EAE8),
//   `[ECX+0x24]` (TriggerClass::Type), `[EDX+0xA4]` (TriggerTypeClass::House),
//   `[EDI+0x34]` (HouseClass::Type) and the three `PUSH 1 / CALL [vtbl+0x20]`
//   scalar-deleting-destructor dispatches.  Name from YRpp HouseClass.h
//   (consult-only; every offset/address reconfirmed here).
#ifndef GG_MATCH_AI_HOUSE_CLASS_TEARDOWN_METHODS_H
#define GG_MATCH_AI_HOUSE_CLASS_TEARDOWN_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector_class.h"

struct HouseClass;
struct HouseTypeClass;   // opaque — compared by pointer identity only

// Each of the three classes below is modelled with just enough virtuals to put
// the virtual destructor at vtable+0x20 (slot 8), so `delete p` reproduces the
// retail `MOV EDX,[ECX]; PUSH 1; CALL [EDX+0x20]` scalar-deleting dispatch.
// None is ever instantiated, so no vtable is emitted for them.

struct TechnoClass
{
    virtual void vf00() = 0;   // vtable+0x00
    virtual void vf04() = 0;   // vtable+0x04
    virtual void vf08() = 0;   // vtable+0x08
    virtual void vf0C() = 0;   // vtable+0x0C
    virtual void vf10() = 0;   // vtable+0x10
    virtual void vf14() = 0;   // vtable+0x14
    virtual void vf18() = 0;   // vtable+0x18
    virtual void vf1C() = 0;   // vtable+0x1C
    virtual ~TechnoClass();    // vtable+0x20 (scalar deleting dtor)

    char        _pad004[0x21C - 0x4];   // +0x0004
    HouseClass* Owner;                  // +0x021C
};
GG_STATIC_ASSERT(offsetof(TechnoClass, Owner) == 0x21C);

struct TriggerTypeClass
{
    char        _pad000[0xA4];   // +0x0000
    HouseTypeClass* House;       // +0x00A4
};
GG_STATIC_ASSERT(offsetof(TriggerTypeClass, House) == 0xA4);

struct TriggerClass
{
    virtual void vf00() = 0;   // vtable+0x00
    virtual void vf04() = 0;   // vtable+0x04
    virtual void vf08() = 0;   // vtable+0x08
    virtual void vf0C() = 0;   // vtable+0x0C
    virtual void vf10() = 0;   // vtable+0x10
    virtual void vf14() = 0;   // vtable+0x14
    virtual void vf18() = 0;   // vtable+0x18
    virtual void vf1C() = 0;   // vtable+0x1C
    virtual ~TriggerClass();   // vtable+0x20 (scalar deleting dtor)

    char              _pad004[0x24 - 0x4];   // +0x0004
    TriggerTypeClass* Type;                  // +0x0024
};
GG_STATIC_ASSERT(offsetof(TriggerClass, Type) == 0x24);

struct HouseClass
{
    virtual void vf00() = 0;   // vtable+0x00
    virtual void vf04() = 0;   // vtable+0x04
    virtual void vf08() = 0;   // vtable+0x08
    virtual void vf0C() = 0;   // vtable+0x0C
    virtual void vf10() = 0;   // vtable+0x10
    virtual void vf14() = 0;   // vtable+0x14
    virtual void vf18() = 0;   // vtable+0x18
    virtual void vf1C() = 0;   // vtable+0x1C
    virtual ~HouseClass();     // vtable+0x20 (scalar deleting dtor)

    char            _pad004[0x34 - 0x4];   // +0x0004
    HouseTypeClass* Type;                  // +0x0034

    // FUNCTION: GAMEMD 0x4FB920
    void SDDTORAllAndTriggers();
};
GG_STATIC_ASSERT(offsetof(HouseClass, Type) == 0x34);

// GLOBAL: GAMEMD 0xA8EC78 — TechnoClass::Array.
extern DynamicVectorClassLayout TechnoArray;
// GLOBAL: GAMEMD 0xA8EAE8 — TriggerClass::Array.
extern DynamicVectorClassLayout TriggerArray;

#endif  // GG_MATCH_AI_HOUSE_CLASS_TEARDOWN_METHODS_H
