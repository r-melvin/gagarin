// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Support declarations for the BuildingClass bodies of the building-a2 cluster (0x43C2D0, 0x442230, 0x443C60,
//   0x449C30, 0x44E440): the bodies are written against the canonical BuildingClass in _layout; this header only
//   adds the retail entry points they call that have no canonical home yet. The shared helpers come from
//   building_a4_views.h.
#ifndef GG_MATCH_ECONOMY_HOUSE_BUILDING_BUILDING_A2_FOLD_H
#define GG_MATCH_ECONOMY_HOUSE_BUILDING_BUILDING_A2_FOLD_H

#include "building_a4_views.h"

// FUNCTION: GAMEMD 0x7509E0 (read-only here) - plays a sound at a position (the sound id in ECX).
void FUN_007509E0(int sound, CoordStruct* where, void* unused);

#endif
