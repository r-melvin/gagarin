// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly of the four production
//   accessors), cross-checked against YRpp
//   (each offset reconfirmed numerically below).
//
// FactoryClass — produces units/buildings for a HouseClass. Derives from
// AbstractClass (0x24 bytes; Production.Value lands at this+0x24, so the base is
// exactly 0x24). Only the members the four targeted methods touch are pinned;
// the full layout is asserted to YRpp's 0x74 total size.
#ifndef GG_MATCH_ECONOMY_FACTORY_CLASS_METHODS_H
#define GG_MATCH_ECONOMY_FACTORY_CLASS_METHODS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

#include "../_layout/factory_class.h"

#endif  // GG_MATCH_ECONOMY_FACTORY_CLASS_METHODS_H
