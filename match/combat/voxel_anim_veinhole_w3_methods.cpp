// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Small VoxelAnimClass (vtable 0x7F6318) and VeinholeMonsterClass (vtable 0x7F66A8)
//   virtual overrides read off retail gamemd.exe v1.001. Functions are in ascending
//   retail address order.

#include "../_layout/voxel_anim_class.h"
#include "../_layout/veinhole_monster_class.h"

// A map cell, as far as the flag word VoxelAnimClass::vf_65 tests.
struct VoxelAnimCellView
{
    char unknown_00[0x12C];
    unsigned int Flags;   // +0x12C
};
GG_STATIC_ASSERT(offsetof(VoxelAnimCellView, Flags) == 0x12C);

// The map object, as far as its cell lookup.
struct VoxelAnimMapView
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x565730 (decl; reloc) -- MapClass::GetCellAt
    VoxelAnimCellView* FUN_00565730(const CoordStruct& coord);
};
// GLOBAL: GAMEMD 0x87F7E8 -- the map object.
extern VoxelAnimMapView VoxelAnimMap_0087F7E8;

// FUNCTION: GAMEMD 0x749B20
// Redraw when the cell it stands in carries flag 0x10, then draw as any object.
bool VoxelAnimClass::vf_65(RectangleStruct* rect, bool force, int a3)
{
    if (VoxelAnimMap_0087F7E8.FUN_00565730(vf_18())->Flags & 0x10) {
        NeedsRedraw = true;
    }
    return ObjectClass::vf_65(rect, force, 0);
}

// FUNCTION: GAMEMD 0x74F330
// Veinhole monsters sit in no layer.
int VeinholeMonsterClass::vf_30()
{
    return -1;
}
