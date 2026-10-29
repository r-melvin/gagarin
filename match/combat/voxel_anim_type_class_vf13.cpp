// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Slot 13 of VoxelAnimTypeClass (vtable 0x7F6548), read off retail gamemd.exe v1.001: the base
//   feeds its fields to the checksum sink, then this type's own fields (layout:
//   _layout/voxel_anim_type_class.h).

#include "../_layout/voxel_anim_type_class.h"

// FUNCTION: GAMEMD 0x74B690
void VoxelAnimTypeClass::vf_13(Obj_004A1D30* crc)
{
    ObjectTypeClass::vf_13(crc);
    crc->FUN_004A1CA0(unknown_294);
    crc->FUN_004A1CA0(unknown_295);
    crc->FUN_004A1CA0(unknown_296);
    crc->FUN_004A1D50(unknown_298);
    crc->FUN_004A1D50(unknown_29C);
    crc->FUN_004A1D90(unknown_2A0);
    crc->FUN_004A1D90(unknown_2A8);
    crc->FUN_004A1D90(unknown_2B0);
    crc->FUN_004A1D90(unknown_2B8);
    crc->FUN_004A1D90(unknown_2C0);
    crc->FUN_004A1D90(unknown_2C8);
    crc->FUN_004A1CA0(unknown_2D0);
    crc->FUN_004A1D50(unknown_2D8);
    crc->FUN_004A1D50(unknown_2DC);
    crc->FUN_004A1D50(unknown_2E0);
    crc->FUN_004A1D50(unknown_2F0);
    crc->FUN_004A1D50(unknown_2F4);
    crc->FUN_004A1CA0(unknown_300);
}
