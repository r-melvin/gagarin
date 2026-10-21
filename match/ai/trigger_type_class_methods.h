// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x726F50-0x727000), cross-checked
//   against YRpp TriggerTypeClass.h / TEventClass.h (consult-only; reconfirmed
//   numerically here).
//
// TriggerTypeClass event/action predicates — each walks the trigger's singly
// linked event list (FirstEvent @0xAC) or action list (FirstAction @0xB0),
// returning true if any node has the matching Kind (node Kind @0x2C, Next
// @0x28). The list nodes (TEventClass / TActionClass) both derive AbstractClass
// (0x24) and place Next@0x28, Kind@0x2c.
// Retail RTTI confirms the class key: TypeDescriptor 0x842D08 is named
// ".?AVTriggerTypeClass@@"; the hierarchy records AbstractTypeClass at offset 0.
#ifndef GG_MATCH_AI_TRIGGER_TYPE_CLASS_METHODS_H
#define GG_MATCH_AI_TRIGGER_TYPE_CLASS_METHODS_H

#include <stddef.h>
#include "../_layout/trigger_type_class.h"
#include "../_rt/gg_static_assert.h"

GG_STATIC_ASSERT(offsetof(TTriggerListNode, Next) == 0x28);
GG_STATIC_ASSERT(offsetof(TTriggerListNode, Kind) == 0x2c);
GG_STATIC_ASSERT(offsetof(TriggerTypeClass, FirstEvent)  == 0xac);
GG_STATIC_ASSERT(offsetof(TriggerTypeClass, FirstAction) == 0xb0);

#endif  // GG_MATCH_AI_TRIGGER_TYPE_CLASS_METHODS_H
