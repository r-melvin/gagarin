// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   FUN_005F6220 is the complete 0x26-byte entry-origin body at the pinned
//   retail address. It calls each object's primary-vtable slot +0xB8 with that
//   object in ECX, saves the argument object's EAX result, then compares the
//   receiver result against it with signed SETG. The caller at 0x551ADB tests
//   AL directly, confirming a bool result. The declarations below model only
//   this dispatch slot; they do not assert the original virtual's name or its
//   declaring class.

// /O1 changes register staging (four bytes); /O2 matches. Both /GX modes
// match under /O2, so this function does not identify the exception flag.
#include "../_layout/object_class.h"

// Minimal primary-vtable call view: the observed target is entry 46 (+0xB8),
// with no stack arguments and an int in EAX. This abstract view is never
// instantiated; it only lets ordinary C++ express the retail indirect call.
// Typed member-pointer and ECX-only fastcall prefix calls each differed in
// four register-staging bytes. This call view retains the exact instruction
// order; no complete hierarchy or concrete vtable is claimed.
struct ObjectClassSortCallView
{
#define GG_OBJECT_SORT_SLOT(n) virtual void unknown_##n() = 0;
    GG_OBJECT_SORT_SLOT(00) GG_OBJECT_SORT_SLOT(01)
    GG_OBJECT_SORT_SLOT(02) GG_OBJECT_SORT_SLOT(03)
    GG_OBJECT_SORT_SLOT(04) GG_OBJECT_SORT_SLOT(05)
    GG_OBJECT_SORT_SLOT(06) GG_OBJECT_SORT_SLOT(07)
    GG_OBJECT_SORT_SLOT(08) GG_OBJECT_SORT_SLOT(09)
    GG_OBJECT_SORT_SLOT(10) GG_OBJECT_SORT_SLOT(11)
    GG_OBJECT_SORT_SLOT(12) GG_OBJECT_SORT_SLOT(13)
    GG_OBJECT_SORT_SLOT(14) GG_OBJECT_SORT_SLOT(15)
    GG_OBJECT_SORT_SLOT(16) GG_OBJECT_SORT_SLOT(17)
    GG_OBJECT_SORT_SLOT(18) GG_OBJECT_SORT_SLOT(19)
    GG_OBJECT_SORT_SLOT(20) GG_OBJECT_SORT_SLOT(21)
    GG_OBJECT_SORT_SLOT(22) GG_OBJECT_SORT_SLOT(23)
    GG_OBJECT_SORT_SLOT(24) GG_OBJECT_SORT_SLOT(25)
    GG_OBJECT_SORT_SLOT(26) GG_OBJECT_SORT_SLOT(27)
    GG_OBJECT_SORT_SLOT(28) GG_OBJECT_SORT_SLOT(29)
    GG_OBJECT_SORT_SLOT(30) GG_OBJECT_SORT_SLOT(31)
    GG_OBJECT_SORT_SLOT(32) GG_OBJECT_SORT_SLOT(33)
    GG_OBJECT_SORT_SLOT(34) GG_OBJECT_SORT_SLOT(35)
    GG_OBJECT_SORT_SLOT(36) GG_OBJECT_SORT_SLOT(37)
    GG_OBJECT_SORT_SLOT(38) GG_OBJECT_SORT_SLOT(39)
    GG_OBJECT_SORT_SLOT(40) GG_OBJECT_SORT_SLOT(41)
    GG_OBJECT_SORT_SLOT(42) GG_OBJECT_SORT_SLOT(43)
    GG_OBJECT_SORT_SLOT(44) GG_OBJECT_SORT_SLOT(45)
#undef GG_OBJECT_SORT_SLOT
    virtual int unknown_B8() = 0; // slot 46 => 46 * 4 == 0xB8
};

// Typed vtable-prefix evidence, independent of the call-view declaration.
// The original virtual name and declaring class remain unknown.
struct ObjectClassPrimaryVtablePrefix
{
    void* unknown_00[46];
    int (ObjectClass::*unknown_B8)();
};
typedef int (ObjectClass::*ObjectClassSortKeyMember)();
GG_STATIC_ASSERT(offsetof(ObjectClassPrimaryVtablePrefix, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(ObjectClassPrimaryVtablePrefix, unknown_B8) == 0xB8);
GG_STATIC_ASSERT(sizeof(ObjectClassPrimaryVtablePrefix) == 0xBC);
GG_STATIC_ASSERT(sizeof(ObjectClassSortKeyMember) == 4);
GG_STATIC_ASSERT(offsetof(ObjectClass, _vtable_IPersistStream) == 0x00);
GG_STATIC_ASSERT(sizeof(void*) == 4);

// FUNCTION: GAMEMD 0x5F6220
bool ObjectClass::FUN_005F6220(ObjectClass* other)
{
    ObjectClassSortCallView* otherView = (ObjectClassSortCallView*)other;
    int otherValue = otherView->unknown_B8();
    ObjectClassSortCallView* thisView = (ObjectClassSortCallView*)this;
    int thisValue = thisView->unknown_B8();
    if (thisValue > otherValue)
        return true;
    return false;
}
