// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly of Suspend / GetBuildTimeFrames),
//   cross-checked against the YRpp
//   (every offset reconfirmed numerically
//   below). Shares the FactoryClass binding pinned in factory_class_methods.h;
//   re-derived here so this translation unit is self-contained.
//
// FactoryClass — produces units/buildings for a HouseClass. Derives from
// AbstractClass (0x24 bytes; Production.Value lands at this+0x24). Only the
// members reached by Suspend / GetBuildTimeFrames are pinned; the unknown gaps
// are padded and the whole layout is asserted to YRpp's 0x74 total size.
#ifndef GG_MATCH_ECONOMY_FACTORY_CLASS_MORE_METHODS_H
#define GG_MATCH_ECONOMY_FACTORY_CLASS_MORE_METHODS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

// Unsorted::CurrentFrame — global frame counter @0x00A8ED84. Read by the
// inlined FrameTimer when Suspend stamps Production.Timer.StartTime.
#include "../core/frame_counter.h"

// ---------------------------------------------------------------------------
// TechnoClass — only TimeToBuild() is reached (a real retail member at
// 0x6F47A0, called __thiscall on the produced Object). Declared without a body
// so cl emits a (reloc-normalised) CALL.
// ---------------------------------------------------------------------------
// Retail RTTI 0x817B58 establishes the class key; public access preserves this ABI view.
#include "../_layout/techno_class.h"


#include "../_layout/factory_class.h"

#endif  // GG_MATCH_ECONOMY_FACTORY_CLASS_MORE_METHODS_H
