// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 @ 0x70FEC0 (Ghidra disasm).
//   Offset 0x1D0 (DrainingMe) read directly from `MOV EDX,[ECX+0x1d0]` in
//   IsBeingDrained; cross-checked vs YRpp DrainingMe @0x1D0.
//
// BuildingClass::IsBeingDrained — predicate: is some draining unit (e.g. a
// Floating Disc) currently siphoning power from this building? Reads the
// TechnoClass-base DrainingMe pointer; the member lives in the committed
// TechnoClass spine, so only the inherited offset is re-confirmed here.
#ifndef GG_MATCH_ECONOMY_BUILDING_CLASS_DRAIN_H
#define GG_MATCH_ECONOMY_BUILDING_CLASS_DRAIN_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/building_class.h"   // BuildingClass; TechnoClass::DrainingMe @0x1D0

#endif  // GG_MATCH_ECONOMY_BUILDING_CLASS_DRAIN_H
