// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x6E61F0 / 0x6E6220 / 0x6E6250 / 0x6E6280 / 0x6E62B0:
//   every one of the five opens `MOV ESI,[ECX+0xA0]` (the tag's first trigger)
//   and advances with `MOV ESI,[ESI+0xA8]` (the trigger's next link). Method
//   names and the callee bindings cross-checked against YRpp TagTypeClass.h /
//   TriggerTypeClass.h (consult-only, no LICENSE; reconfirmed here).
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
struct TriggerTypeClass
{
    char              _pad0[0xA8];        // +0x0000
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
// fields; only the trigger-list head at +0xA0 is touched here.
// ---------------------------------------------------------------------------
struct TagTypeClass : AbstractTypeClass
{
    char              _pad98[0xA0 - 0x98];   // +0x0098  (Persistence et al., P2)
    TriggerTypeClass* FirstTrigger;          // +0x00A0  (MOV ESI,[ECX+0xA0])

    // Declared ascending by retail address.
    int  GetFlags() const;                        // GAMEMD 0x6E61F0
    bool HasAllowWinAction() const;               // GAMEMD 0x6E6220
    bool HasCrossesHorizontalLineEvent() const;   // GAMEMD 0x6E6250
    bool HasCrossesVerticalLineEvent() const;     // GAMEMD 0x6E6280
    bool HasZoneEntryByEvent() const;             // GAMEMD 0x6E62B0
};
GG_STATIC_ASSERT(offsetof(TagTypeClass, FirstTrigger) == 0xA0);

#endif  // GG_MATCH_AI_TAG_TYPE_CLASS_FLAG_METHODS_H
