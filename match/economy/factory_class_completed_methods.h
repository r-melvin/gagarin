// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4CA1A0: `[ECX+0x58]` (Object), `[ECX+0x24]` compared
//   against 0x36 (Production.Value), `[ECX+0x70]` / `[ECX+0x5D]` byte stores
//   (IsSuspended / IsDifferent), `[ECX+0x68]` (SpecialItem, written -1),
//   `[ECX+0x38]` (Production.Rate), the `LEA EDI,[ECX+0x2C]` timer base with
//   `[EDI]`/`[EDI+4]`/`[EDI+8]` stores (Production.Timer), and the global
//   `[0x00A8ED84]` (Unsorted::CurrentFrame). Names cross-checked against the
//   YRpp (no text copied); the
//   binding agrees with match/economy/factory_class_methods.h and
//   factory_class_more_methods.h, re-derived here so the TU is standalone.
#ifndef GG_MATCH_ECONOMY_FACTORY_CLASS_COMPLETED_METHODS_H
#define GG_MATCH_ECONOMY_FACTORY_CLASS_COMPLETED_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame, the engine frame counter.
#include "../core/frame_counter.h"

#include "../_layout/factory_class.h"

#endif  // GG_MATCH_ECONOMY_FACTORY_CLASS_COMPLETED_METHODS_H
