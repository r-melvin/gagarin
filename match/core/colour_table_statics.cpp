// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Seven 256-entry colour tables (768 bytes each) in the unit at 0x40D8A0. Each is an array of
// RGBClass, whose constructor zeroes the three channels; retail folds the array construction into
// a single compiler-generated loop per table.
#include "../_layout/rgb_class.h"

// A 256-entry table filled with one colour by the out-of-line constructor at
// 0x626020 (ownrdraw.cpp); the colour is passed as a temporary.
class ColorTableFill
{
public:
    RGBClass Colors[256];
    // FUNCTION: GAMEMD 0x626020 (decl; reloc)
    ColorTableFill(const RGBClass& fill);
};

class FillColour : public RGBClass
{
public:
    FillColour(unsigned char v) { Red = v; Green = v; Blue = v; }
};

// SYNTHETIC: GAMEMD 0x40D8A0
// GLOBAL: GAMEMD 0x886080
RGBClass DAT_00886080[256];

// SYNTHETIC: GAMEMD 0x40D8C0
// GLOBAL: GAMEMD 0x885780
RGBClass DAT_00885780[256];

// SYNTHETIC: GAMEMD 0x40D8E0
// GLOBAL: GAMEMD 0x886380
RGBClass DAT_00886380[256];

// SYNTHETIC: GAMEMD 0x40D900
// GLOBAL: GAMEMD 0x884E80
ColorTableFill DAT_00884E80(FillColour(0));

// SYNTHETIC: GAMEMD 0x40D920
// GLOBAL: GAMEMD 0x885D80
ColorTableFill DAT_00885D80(FillColour(0xFF));

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
