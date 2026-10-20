// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x6E5300-0x6E5358), cross-checked
//   against YRpp TagClass.h / TagTypeClass.h (consult-only; reconfirmed
//   numerically here).
//
// TagClass event predicates — each one delegates to the same-named query on
// the tag's TagTypeClass (this->Type @ +0x24), returning whether the type's
// trigger event list contains at least one event of the asked kind.
#ifndef GG_MATCH_AI_TAG_CLASS_METHODS_H
#define GG_MATCH_AI_TAG_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The TagTypeClass query targets. Declared (no body) so cl emits a __thiscall
// call with a normalised relocation; their own matching is out of scope here.
//   GAMEMD 0x6E6250  HasCrossesHorizontalLineEvent
//   GAMEMD 0x6E6280  HasCrossesVerticalLineEvent
//   GAMEMD 0x6E62B0  HasZoneEntryByEvent
struct TagTypeClass
{
    bool HasCrossesHorizontalLineEvent();   // GAMEMD 0x6E6250 __thiscall
    bool HasCrossesVerticalLineEvent();     // GAMEMD 0x6E6280 __thiscall
    bool HasZoneEntryByEvent();             // GAMEMD 0x6E62B0 __thiscall
};

// TagClass — only the Type pointer (@0x24, confirmed from `mov ecx,[ecx+0x24]`
// in all three predicates) is modelled; the AbstractClass base below it is
// padded.
// TriggerTypeClass — only the "persists across an owner change" flag at +0xA0
// is read here (`MOV DL,[ECX+0xA0]` @0x6E57CA). The bytes fix its offset but
// not its meaning, so it keeps a placeholder name.
struct TriggerTypeClass_Flag
{
    char _pad00[0xA0];   // +0x0000
    bool unknown_A0;     // +0x00A0
};

// TriggerClass — a live trigger instance attached to a tag. Confirmed from
// ShouldReplace: Type at +0x24 (`MOV ECX,[EAX+0x24]`) and the next link at
// +0x28 (`MOV EAX,[EAX+0x28]`).
struct TriggerClass
{
    char                   _pad00[0x24];   // +0x0000
    TriggerTypeClass_Flag* Type;           // +0x0024
    TriggerClass*          NextTrigger;    // +0x0028
};

struct TagClass
{
    char          _pad0[0x24];   // +0x00  AbstractClass base
    TagTypeClass* Type;          // +0x24
    TriggerClass* FirstTrigger;  // +0x28  (MOV EAX,[ECX+0x28] @0x6E57C0)

    bool HasCrossesVerticalLineEvent() const;     // GAMEMD 0x6E5300
    bool HasCrossesHorizontalLineEvent() const;   // GAMEMD 0x6E5320
    bool HasZoneEntryByEvent() const;             // GAMEMD 0x6E5340
    bool ShouldReplace() const;                   // GAMEMD 0x6E57C0
};

GG_STATIC_ASSERT(offsetof(TriggerClass, Type)        == 0x24);
GG_STATIC_ASSERT(offsetof(TriggerClass, NextTrigger) == 0x28);
GG_STATIC_ASSERT(offsetof(TagClass, FirstTrigger)    == 0x28);

GG_STATIC_ASSERT(offsetof(TagClass, Type) == 0x24);

#endif  // GG_MATCH_AI_TAG_CLASS_METHODS_H
