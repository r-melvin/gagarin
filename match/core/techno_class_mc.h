// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly). Names cross-checked against
//   YRpp (every offset reconfirmed
//   numerically below from the matched bodies).
//
// This TU matches two tiny TechnoClass query helpers:
//   * GetEffectTintIntensity — folds the invulnerability + airstrike tint
//     intensities (calls two sibling helpers; no member access).
//   * IsMindControlled       — true if MindControlledBy is set OR the
//     MindControlledByAUnit flag is set.
// Only the members the matched bodies touch are modelled; the full layout is
// the committed _layout spine (match/_layout/techno_class.h) / P2. Confirmed
// offsets (from IsMindControlled @0x7105E0):
//   * MindControlledBy       +0x2C0  `MOV EAX,[ECX+0x2C0]`  — matches spine
//   * MindControlledByAUnit  +0x2C4  `MOV AL,[ECX+0x2C4]`   — matches spine
#ifndef GG_MATCH_CORE_TECHNO_CLASS_MC_H
#define GG_MATCH_CORE_TECHNO_CLASS_MC_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#ifndef NULL
#define NULL 0
#endif

// ---------------------------------------------------------------------------
// TechnoClass — minimal offset-pinned model for the two matched query helpers.
// The pad gap stands in for the full RadioClass/MissionClass/ObjectClass/
// TechnoClass spine (see match/_layout/techno_class.h); only the two touched
// members are named.
// ---------------------------------------------------------------------------
#include "../_layout/techno_class.h"


GG_STATIC_ASSERT(offsetof(TechnoClass, MindControlledBy)      == 0x2C0);
GG_STATIC_ASSERT(offsetof(TechnoClass, MindControlledByAUnit) == 0x2C4);

#endif  // GG_MATCH_CORE_TECHNO_CLASS_MC_H
