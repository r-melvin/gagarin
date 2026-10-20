// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: TagClass ctor FUN_0x006E4DE0 (chains AbstractClass ctor
//   FUN_0x00410170 at offset 0).
//   Size 0x38 is supported by allocation-size and constructor evidence;
//   the layout is pinned below with a sizeof assertion.
//   RTTI: primary vtable 0x7F44E0 -> COL 0x80BBA0 -> TypeDescriptor
//   0x8249E8, whose name at 0x8249F0 is ".?AVTagClass@@".
//   Cross-read against YRpp TagClass.h: 6 named members claimed, 6 confirmed.
//   No disagreement found.
//
// TagClass — a live map tag binding triggers to objects. Derives AbstractClass.
#ifndef GG_MATCH_LAYOUT_TAG_CLASS_H
#define GG_MATCH_LAYOUT_TAG_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_class.h"
#include "foot_class.h"   // CellStruct

// Retail TypeDescriptor 0x8249E8 names ".?AVTagClass@@".
class TagClass : public AbstractClass
{
public:
    // FUNCTION: GAMEMD 0x6E5300
    bool HasCrossesVerticalLineEvent() const;
    // FUNCTION: GAMEMD 0x6E5320
    bool HasCrossesHorizontalLineEvent() const;
    // FUNCTION: GAMEMD 0x6E5340
    bool HasZoneEntryByEvent() const;
    // FUNCTION: GAMEMD 0x6E57C0
    bool ShouldReplace() const;
    // FUNCTION: GAMEMD 0x6E57F0
    static void __fastcall NotifyGlobalChanged(int idxGlobal);
    // FUNCTION: GAMEMD 0x6E5820
    static void __fastcall NotifyLocalChanged(int idxLocal);
    // FUNCTION: GAMEMD 0x6E5850
    bool IsOnlyInstanceOfType() const;

    void*         Type;            // +0x24 TagTypeClass*; ctor = arg1 @0x006E4DF0
    void*         FirstTrigger;    // +0x28 TriggerClass*; ctor @0x006E4DF3
    int           InstanceCount;   // +0x2C ctor @0x006E4DF6
    CellStruct    DefaultCoords;   // +0x30 ctor MOV [ESI+0x30],EAX(=[0x00B0E700]) @0x006E4DFE
    unsigned char Destroyed;       // +0x34 ctor @0x006E4E01
    unsigned char IsExecuting;     // +0x35 ctor @0x006E4E04
    unsigned char unknown_36[2];   // +0x36 unclassified tail bytes; closes the object at 0x38
    // GLOBAL: GAMEMD 0xB0E720 -- loader-zero registry storage.
    static DynamicVectorClassLayout Array;
};

GG_STATIC_ASSERT(offsetof(TagClass, Type)          == 0x24);
GG_STATIC_ASSERT(offsetof(TagClass, FirstTrigger)  == 0x28);
GG_STATIC_ASSERT(offsetof(TagClass, InstanceCount) == 0x2C);
GG_STATIC_ASSERT(offsetof(TagClass, DefaultCoords) == 0x30);
GG_STATIC_ASSERT(offsetof(TagClass, Destroyed)     == 0x34);
GG_STATIC_ASSERT(offsetof(TagClass, IsExecuting)   == 0x35);
GG_STATIC_ASSERT(sizeof(TagClass)                  == 0x38);

// VTABLE: GAMEMD 0x007F44E0  TagClass
// VTABLE: GAMEMD 0x007F44C4  TagClass::(+0x04)
// VTABLE: GAMEMD 0x007F44BC  TagClass::(+0x08)
// VTABLE: GAMEMD 0x007F44B4  TagClass::(+0x0C)

#endif  // GG_MATCH_LAYOUT_TAG_CLASS_H
