// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: TagClass ctor FUN_0x006E4DE0 (chains AbstractClass ctor
//   FUN_0x00410170 at offset 0).
//   sizeof: `PUSH 0x38` before the ctor call at all 3 allocation sites.
//   RTTI: 0x007F44E0 / 0x007F44C4 (+ the +8/+0xC tables) resolve to
//   ".?AVTagClass@@" (stored @0x006E4E07..0x006E4E1B).
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

struct TagClass : AbstractClass
{
    void*         Type;            // +0x24 TagTypeClass*; ctor = arg1 @0x006E4DF0
    void*         FirstTrigger;    // +0x28 TriggerClass*; ctor @0x006E4DF3
    int           InstanceCount;   // +0x2C ctor @0x006E4DF6
    CellStruct    DefaultCoords;   // +0x30 ctor MOV [ESI+0x30],EAX(=[0x00B0E700]) @0x006E4DFE
    unsigned char Destroyed;       // +0x34 ctor @0x006E4E01
    unsigned char IsExecuting;     // +0x35 ctor @0x006E4E04
    unsigned char padding_36[2];   // +0x36 (PROTECTED_PROPERTY); closes the object at 0x38
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
