// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x4CA620 / 0x4CA670), cross-checked
//   against YRpp
//   (every offset reconfirmed numerically below).
//
// Translation unit: FactoryClass production-queue mutators.
//   RemoveOneFromQueue  -> locates pItem in QueuedObjects (virtual FindItemIndex
//                          via [vtbl+0x10]) and shifts the tail down (inlined
//                          RemoveItem), returning whether anything was removed.
//   CountTotal          -> 1 if the in-production Object's type matches, plus
//                          every QueuedObjects entry that matches pType.
//
// Self-contained model (separate TU from factory_class_methods.h): the queue
// vector here carries the retail VectorClass vtable order so the genuine virtual
// FindItemIndex call lands at [vtbl+0x10]; the in-production Object's type
// getter is a genuine virtual at [vtbl+0x84].
#ifndef GG_MATCH_ECONOMY_FACTORY_CLASS_QUEUE_METHODS_H
#define GG_MATCH_ECONOMY_FACTORY_CLASS_QUEUE_METHODS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

class TechnoTypeClass;

// ---------------------------------------------------------------------------
// TechnoClass -- only the vtable shape CountTotal reaches.  GetTechnoType is a
// genuine virtual at byte offset 0x84 (slot 33); CountTotal does
// `Object->GetTechnoType() == pType` => MOV EAX,[ECX]; CALL [EAX+0x84].
// ---------------------------------------------------------------------------
#include "../_layout/techno_class.h"


#include "../_layout/factory_class.h"
#include "../core/vector_class_operations.h"

#endif  // GG_MATCH_ECONOMY_FACTORY_CLASS_QUEUE_METHODS_H
