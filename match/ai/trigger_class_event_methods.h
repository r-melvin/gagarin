// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x726250-0x726346), cross-checked
//   against YRpp TriggerClass.h (consult-only; reconfirmed numerically here).
//
// TriggerClass event-presence queries. Each TriggerClass delegates to its
// TriggerTypeClass (Type @0x24); the four queries here walk the optional
// AttachedTrigger (@0x28) chain. Confirmed from the disasm:
//   mov eax,[esi+0x28]  -> AttachedTrigger
//   mov ecx,[esi+0x24]  -> Type
// The TriggerTypeClass-side checks are separate retail functions (0x726f80,
// 0x726f50, 0x726fb0, 0x726fe0), declared in the shared layout.
#ifndef GG_MATCH_AI_TRIGGER_CLASS_EVENT_METHODS_H
#define GG_MATCH_AI_TRIGGER_CLASS_EVENT_METHODS_H

#include <stddef.h>
#include "../_layout/trigger_type_class.h"
#include "../_layout/trigger_class.h"
#include "../_rt/gg_static_assert.h"

// TriggerTypeClass provides these separate retail __thiscall predicates,
// each returning bool in AL.

// These methods use Type (+0x24) and the linked trigger (+0x28) from the
// shared TriggerClass declaration.

GG_STATIC_ASSERT(offsetof(TriggerClass, Type) == 0x24);
GG_STATIC_ASSERT(offsetof(TriggerClass, AttachedTrigger) == 0x28);

#endif  // GG_MATCH_AI_TRIGGER_CLASS_EVENT_METHODS_H
