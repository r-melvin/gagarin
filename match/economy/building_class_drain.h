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
#include "../_layout/techno_class.h"   // TechnoClass spine: DrainingMe @0x1D0

// DrainingMe is a TechnoClass-base member (+0x1D0). The full BuildingClass
// layout (its own members past 0x520) is P2; IsBeingDrained touches only the
// inherited pointer, so BuildingClass is modelled here as a bare TechnoClass
// derivative carrying just the one matched accessor.
struct BuildingClass : TechnoClass
{
    bool IsBeingDrained() const;   // GAMEMD 0x70FEC0 __thiscall
};

// Re-confirm the single inherited offset this TU depends on (read from the
// disasm above). Pointer-width-sensitive => guarded to the 32-bit match ABI.
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(TechnoClass, DrainingMe) == 0x1D0);
#endif

#endif  // GG_MATCH_ECONOMY_BUILDING_CLASS_DRAIN_H
