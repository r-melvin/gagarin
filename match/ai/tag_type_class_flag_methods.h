// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x6E61F0 / 0x6E6220 / 0x6E6250 / 0x6E6280 / 0x6E62B0:
//   every one of the five opens `MOV ESI,[ECX+0xA0]` (the tag's first trigger)
//   and advances with `MOV ESI,[ESI+0xA8]` (the trigger's next link). Method
//   names and the callee bindings cross-checked against YRpp TagTypeClass.h /
//   TriggerTypeClass.h (consult-only, no LICENSE; reconfirmed here).
//
// Additional binary evidence for the INI methods:
//   0x6E5B78/0x6E5B82/0x6E5B88 initialise +0x98/+0x9C/+0xA0;
//   0x6E6366 pushes 0xA4 for operator new, followed by ctor 0x6E5B60.
//   TriggerType's RTTI hierarchy at 0x80CA10, base array 0x80C9E0,
//   names AbstractTypeClass at zero offset via descriptor 0x7FB1C0.
//
// TagTypeClass flag/predicate leaves — each one is a fold over the tag's
// singly-linked TriggerTypeClass list, delegating to the same-named predicate
// on each trigger.
#ifndef GG_MATCH_AI_TAG_TYPE_CLASS_FLAG_METHODS_H
#define GG_MATCH_AI_TAG_TYPE_CLASS_FLAG_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/abstract_type_class.h"

// ---------------------------------------------------------------------------
// TriggerTypeClass — only the next-link and the five delegated predicates are
// modelled here; the full layout is P2. All five are non-virtual __thiscall
// calls in retail (direct CALL to the fixed address), so they are declared
// without bodies and the compiler emits reloc-normalised direct calls.
// ---------------------------------------------------------------------------
class TriggerTypeClass : public AbstractTypeClass
{
public:
    char              unknown_98[0xA8 - 0x98]; // +0x0098
    TriggerTypeClass* NextTrigger;        // +0x00A8  (MOV ESI,[ESI+0xA8])

    int  GetFlags() const;                        // GAMEMD 0x7271E0
    bool HasAllowWinAction() const;               // GAMEMD 0x726FE0
    bool HasCrossesHorizontalLineEvent() const;   // GAMEMD 0x726F80
    bool HasCrossesVerticalLineEvent() const;     // GAMEMD 0x726F50
    bool HasZoneEntryByEvent() const;             // GAMEMD 0x726FB0
};
GG_STATIC_ASSERT(offsetof(TriggerTypeClass, NextTrigger) == 0xA8);

// ---------------------------------------------------------------------------
// TagTypeClass — AbstractTypeClass spine (sizeof 0x98) plus the tag's own
// fields; INI methods also touch Persistence and inherited identity strings.
// Retail RTTI: primary vtable 0x7F45C4 -> COL 0x80BCF0 -> TypeDescriptor
// 0x842CB0, whose raw name is ".?AVTagTypeClass@@" (class key).
// ---------------------------------------------------------------------------
struct TagINI_006E6080;

class TagTypeClass : public AbstractTypeClass
{
public:
    int               unknown_98;           // +0x0098
    int               Persistence;          // +0x009C (store at 0x6E60E1)
    TriggerTypeClass* FirstTrigger;          // +0x00A0  (MOV ESI,[ECX+0xA0])

    // Declared ascending by retail address.
    // FUNCTION: GAMEMD 0x6E5E70
    static TagTypeClass* __fastcall FindByNameOrID(const char* name);
    // FUNCTION: GAMEMD 0x6E6080
    bool ReadFromINI(TagINI_006E6080* ini);
    // FUNCTION: GAMEMD 0x6E6160
    bool WriteToINI(TagINI_006E6080* ini);
    int  GetFlags() const;                        // GAMEMD 0x6E61F0
    bool HasAllowWinAction() const;               // GAMEMD 0x6E6220
    bool HasCrossesHorizontalLineEvent() const;   // GAMEMD 0x6E6250
    bool HasCrossesVerticalLineEvent() const;     // GAMEMD 0x6E6280
    bool HasZoneEntryByEvent() const;             // GAMEMD 0x6E62B0
};
GG_STATIC_ASSERT(offsetof(TagTypeClass, unknown_98) == 0x98);
GG_STATIC_ASSERT(offsetof(TagTypeClass, Persistence) == 0x9C);
GG_STATIC_ASSERT(offsetof(TagTypeClass, FirstTrigger) == 0xA0);
GG_STATIC_ASSERT(sizeof(TagTypeClass) == 0xA4);

#endif  // GG_MATCH_AI_TAG_TYPE_CLASS_FLAG_METHODS_H
