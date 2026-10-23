// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x44E880), cross-checked against
//   YRpp
//   (every offset reconfirmed numerically from the disasm below).
//
// BuildingClass::GetPowerDrain — the structure's per-frame power consumption.
// The retail body is:
//   * an early-out virtual call through vtable slot @+0x1D4 (returns drain 0
//     when the building is offline / suppressed),
//   * a HasPower @+0x660 gate (drain 0 while unpowered),
//   * base drain   = Type->PowerDrain        ([Type+0xEE4]),
//   * + Type->ExtraPowerDrain ([Type+0xEEC]) when HasExtraPowerDrain @+0x669,
//   * + each populated Upgrades[0..2]->PowerDrain ([up+0xEE4]) when
//     UpgradeLevel @+0x702 is non-zero (a fixed 3-iteration loop over the
//     Upgrades[3] pointer array @+0x5EC).
//
// The leading dispatch is a virtual call at vtable byte offset 0x1D4
// (ObjectClass slot 117), called as vf_117(). Retail's prologue is a bare `PUSH ESI` with no frame
// pointer, which is what /O2 emits for this shape and carries none of the
// inline-assembly signature (no `PUSH EBP; MOV EBP,ESP`, no stack-homed locals,
// no instruction outside cl's repertoire), so the retail source was ordinary
// C++ and so is this.
#ifndef GG_MATCH_ECONOMY_BUILDING_CLASS_POWER_METHODS_H
#define GG_MATCH_ECONOMY_BUILDING_CLASS_POWER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/building_class.h"

#endif  // GG_MATCH_ECONOMY_BUILDING_CLASS_POWER_METHODS_H
