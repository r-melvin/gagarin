// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// /Ob1 and /Ob2 both reproduce these lifetime bodies.
#include "voxel_shade_palette.h"
#include <new.h>
// FUNCTION: GAMEMD 0x758950
VoxelShadePalette::VoxelShadePalette(unsigned char* palette, unsigned char* remap)
{
    if (!palette) { Palette = new unsigned char[768]; unknown_18 = 1; }
    else { Palette = palette; unknown_18 = 0; }
    if (!remap) { Remap = new unsigned char[32768]; unknown_1C = 1; }
    else { Remap = remap; unknown_1C = 0; }
}
// FUNCTION: GAMEMD 0x7589C0
VoxelShadePalette::~VoxelShadePalette()
{
    if (unknown_18) ::operator delete(Palette);
    if (unknown_1C) ::operator delete(Remap);
}
