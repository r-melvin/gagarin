// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x6B7B90 / 0x6B7D30 / 0x6B7D50),
//   cross-checked against YRpp (
//   every offset reconfirmed numerically here).
//
// SpawnManagerClass — manages a carrier's spawned aircraft (e.g. Aircraft
// Carrier Hornets, Boomer missiles). This TU matches three leaf accessors:
//   - SetTarget: stash a pending NewTarget unless it equals the live Target.
//   - CountAliveSpawns: count nodes whose Status != Dead(7).
//   - CountDockedSpawns: count nodes whose Status == Reloading(6) || Idle(0).
#ifndef GG_MATCH_COMBAT_SPAWN_MANAGER_CLASS_METHODS_H
#define GG_MATCH_COMBAT_SPAWN_MANAGER_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/spawn_manager_class.h"

#endif  // GG_MATCH_COMBAT_SPAWN_MANAGER_CLASS_METHODS_H
