// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The pinned PE maps 0xAC13C8 into .data's loader-zero tail: section VA
// 0x812000, virtual size 0x367BE4, file-backed size 0x6C000; offset 0x2AF3C8.
// This establishes the loader value only, not later initialization or writes.
#include "flight_level.h"
#include "../_rt/gg_static_assert.h"
GG_STATIC_ASSERT(sizeof(int) == 4);
// GLOBAL: GAMEMD 0x00AC13C8
int FlightLevel;
