// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Seven 256-entry colour tables (768 bytes each) in the unit at 0x40D8A0. Each is an array of
// RGBClass, whose constructor zeroes the three channels; retail folds the array construction into
// a single compiler-generated loop per table.
#include "../_layout/rgb_class.h"

// SYNTHETIC: GAMEMD 0x40D8A0
// GLOBAL: GAMEMD 0x886080
RGBClass DAT_00886080[256];

// SYNTHETIC: GAMEMD 0x40D8C0
// GLOBAL: GAMEMD 0x885780
RGBClass DAT_00885780[256];

// SYNTHETIC: GAMEMD 0x40D8E0
// GLOBAL: GAMEMD 0x886380
RGBClass DAT_00886380[256];

// SYNTHETIC: GAMEMD 0x40D940
// GLOBAL: GAMEMD 0x885A80
RGBClass DAT_00885A80[256];

// SYNTHETIC: GAMEMD 0x40D960
// GLOBAL: GAMEMD 0x885480
RGBClass DAT_00885480[256];

// SYNTHETIC: GAMEMD 0x40D980
// GLOBAL: GAMEMD 0x886680
RGBClass DAT_00886680[256];

// SYNTHETIC: GAMEMD 0x40D9A0
// GLOBAL: GAMEMD 0x885180
RGBClass DAT_00885180[256];
