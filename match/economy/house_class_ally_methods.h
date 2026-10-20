// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x4F9A10-0x4F9ADE), cross-checked
//   against YRpp HouseClass.h / AbstractClass.h (consult-only; reconfirmed here).
//
// HouseClass::IsAlliedWith overload trio. Only the two members these methods
// touch are modelled (ArrayIndex@0x30, Allies bitfield dword@0x5788); the full
// HouseClass layout is P2. ObjectClass is modelled solely as a vtable carrier so
// the (ObjectClass const*) overload can issue its virtual GetOwningHouse call at
// vtable offset 0x3C (confirmed: `MOV EAX,[ECX]; CALL [EAX+0x3C]`).
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_ALLY_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_ALLY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class HouseClass;

// ---------------------------------------------------------------------------
// ObjectClass — modelled only as the polymorphic base whose vtable slot 15
// (offset 0x3C) is GetOwningHouse(). 15 placeholder virtuals precede it so the
// call `pObject->GetOwningHouse()` lands on [vtable+0x3C], matching retail.
// The placeholders / GetOwningHouse are declared, never defined: a virtual call
// through a pointer only needs the vtable-offset, computed from the declaration.
// ---------------------------------------------------------------------------
class ObjectClass
{
public:
    virtual void _vt00();  // 0x00
    virtual void _vt01();  // 0x04
    virtual void _vt02();  // 0x08
    virtual void _vt03();  // 0x0C
    virtual void _vt04();  // 0x10
    virtual void _vt05();  // 0x14
    virtual void _vt06();  // 0x18
    virtual void _vt07();  // 0x1C
    virtual void _vt08();  // 0x20
    virtual void _vt09();  // 0x24
    virtual void _vt10();  // 0x28
    virtual void _vt11();  // 0x2C
    virtual void _vt12();  // 0x30
    virtual void _vt13();  // 0x34
    virtual void _vt14();  // 0x38
    virtual HouseClass* GetOwningHouse() const;  // 0x3C
};

// ---------------------------------------------------------------------------
// HouseClass — only ArrayIndex (+0x30) and the Allies bitfield dword (+0x5788)
// are touched by the three IsAlliedWith overloads. The rest of the (huge)
// HouseClass body is opaque padding here; full layout is P2.
// ---------------------------------------------------------------------------
class HouseClass
{
public:
    bool IsAlliedWith(int idxHouse) const;             // GAMEMD 0x4F9A10 __thiscall
    bool IsAlliedWith(HouseClass const* pHouse) const; // GAMEMD 0x4F9A50 __thiscall
    bool IsAlliedWith(ObjectClass const* pObject) const; // GAMEMD 0x4F9A90 __thiscall

    char _pad0[0x30];     // [0x00..0x2F] opaque base — P2
    int  ArrayIndex;      // +0x30
    char _pad1[0x5788 - (0x30 + 4)]; // [0x34..0x5787] opaque — P2
    int  Allies;          // +0x5788  (IndexBitfield dword 0; one bit per house)
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(HouseClass, ArrayIndex) == 0x30);
GG_STATIC_ASSERT(offsetof(HouseClass, Allies)     == 0x5788);
#endif

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_ALLY_METHODS_H
