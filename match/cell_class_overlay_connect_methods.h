// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x480510: the cell's `[EBP+0x44]` (OverlayTypeIndex)
//   and occupier list head `[EBP+0xE4]` (FirstObject) threaded through
//   `[ESI+0x30]` (NextObject); each occupier's WhatAmI slot `[EAX+0x2C]`
//   (6 = building), `[ESI+0x6C]` (Health) and `[ESI+0x520]`
//   (BuildingClass::Type); RulesClass 0x8871E0 building-type pointers at
//   +0x86C / +0x870 / +0x874 / +0x878 / +0x87C (GDIGateOne, GDIGateTwo,
//   NodGateOne, NodGateTwo, WallTower). The overlay indices 2 / 0x1A / 0xF3
//   are the wall overlays a gate joins. Names cross-checked against YRpp.
#ifndef GG_MATCH_MAP_CELL_CLASS_OVERLAY_CONNECT_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_OVERLAY_CONNECT_METHODS_H

// GLOBAL: GAMEMD 0x8871E0 — RulesClass::Instance, declared by rules_class.h as `Rules`.
#include "_layout/rules_class.h"

#endif  // GG_MATCH_MAP_CELL_CLASS_OVERLAY_CONNECT_METHODS_H
