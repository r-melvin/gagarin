// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and offsets read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4CA5A0. The member layout is confirmed against YRpp
//   working *backwards* from its named tail:
//   Owner @0x6C and IsSuspended @0x70 are read directly by this function, and
//   Object @0x58 sits immediately after a DynamicVectorClass — which places
//   QueuedObjects at 0x40, hence Items @0x44 and Count @0x50, exactly the
//   offsets the body uses. QueuedObjects is the canonical
//   DynamicVectorClass<TechnoTypeClass*>; its own offsets are asserted in
//   match/core/vector_class_layout_asserts.cpp.
#ifndef GG_MATCH_ECONOMY_FACTORY_CLASS_START_METHODS_H
#define GG_MATCH_ECONOMY_FACTORY_CLASS_START_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/vector_class_operations.h"
#include "../_layout/house_class.h"
#include "../_layout/factory_class.h"



// The queued blueprint. Two vtable slots are dispatched; because Slot_2C takes
// stack arguments it must be a real virtual rather than the tree's
// __fastcall-fn-pointer shortcut (methodology §4.6).
class TechnoTypeClass
{
public:
#include "factory_class_start_slots.inc"

    char          _padAfterVtbl[0xCCE - 4];  // +0x0004
    unsigned char unknown_CCE;               // +0x0CCE  passed to Slot_2C
};
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, unknown_CCE) == 0xCCE);

#endif  // GG_MATCH_ECONOMY_FACTORY_CLASS_START_METHODS_H
