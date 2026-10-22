// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x727120 / 0x7271E0), cross-checked
//   against YRpp (reconfirmed numerically here).
//
//   This TU uses the shared TriggerTypeClass layout. These methods touch:
//     - the static lookup array TriggerTypeClass::Array (global @0x8B4178)
//     - ID (+0x24) / Name (+0x64) from AbstractTypeClass, NextTrigger (+0xA8),
//       FirstEvent (+0xAC), FirstAction (+0xB0).
#ifndef GG_MATCH_AI_TRIGGER_TYPE_CLASS_FLAGS_METHODS_H
#define GG_MATCH_AI_TRIGGER_TYPE_CLASS_FLAGS_METHODS_H

#include <stddef.h>
#include "../_layout/trigger_type_class.h"
#include "../_rt/gg_static_assert.h"

GG_STATIC_ASSERT(offsetof(TTriggerListNode, Next) == 0x28);
GG_STATIC_ASSERT(offsetof(TTriggerListNode, Kind) == 0x2c);
GG_STATIC_ASSERT(offsetof(TriggerTypeClass, NextTrigger) == 0xa8);
GG_STATIC_ASSERT(offsetof(TriggerTypeClass, FirstEvent)  == 0xac);
GG_STATIC_ASSERT(offsetof(TriggerTypeClass, FirstAction) == 0xb0);

#endif  // GG_MATCH_AI_TRIGGER_TYPE_CLASS_FLAGS_METHODS_H
