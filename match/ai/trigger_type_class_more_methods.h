// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x727010 / 0x727050), cross-checked
//   against YRpp TriggerTypeClass.h / TEventClass.h (consult-only; reconfirmed
//   numerically here).
//
// TriggerTypeClass global/local-variable event predicates. Each walks the
// trigger's singly linked event list (FirstEvent @0xAC; node Next @0x28,
// EventKind @0x2c, Value @0x34) and returns true iff some event both has the
// matching set/cleared Kind AND carries the requested variable index in Value:
//   HasGlobalSetOrClearedEvent  — kinds 0x1b (global set) / 0x1c (global clear)
//   HasLocalSetOrClearedEvent   — kinds 0x24 (local  set) / 0x25 (local  clear)
//
// This is the "-more" split of trigger_type_class_methods.h. The shared
// TriggerTypeClass layout names the event-list pointer; the node view also
// pins Value @0x34 used by these predicates.
#ifndef GG_MATCH_AI_TRIGGER_TYPE_CLASS_MORE_METHODS_H
#define GG_MATCH_AI_TRIGGER_TYPE_CLASS_MORE_METHODS_H

#include <stddef.h>
#include "../_layout/trigger_type_class.h"
#include "../_rt/gg_static_assert.h"

GG_STATIC_ASSERT(offsetof(TriggerTypeClass, FirstEvent) == 0xac);

#endif  // GG_MATCH_AI_TRIGGER_TYPE_CLASS_MORE_METHODS_H
