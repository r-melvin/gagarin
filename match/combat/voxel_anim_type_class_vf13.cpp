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
    crc->FUN_004A1CA0(Normalized);
    crc->FUN_004A1CA0(Translucent);
    crc->FUN_004A1CA0(unknown_296);
    crc->FUN_004A1D50(VoxelIndex);
    crc->FUN_004A1D50(Duration);
    crc->FUN_004A1D90(Elasticity);
    crc->FUN_004A1D90(MinAngularVelocity);
    crc->FUN_004A1D90(MaxAngularVelocity);
    crc->FUN_004A1D90(MinZVel);
    crc->FUN_004A1D90(MaxZVel);
    crc->FUN_004A1D90(MaxXYVel);
    crc->FUN_004A1CA0(IsMeteor);
    crc->FUN_004A1D50(SpawnCount);
    crc->FUN_004A1D50(StartSound);
    crc->FUN_004A1D50(StopSound);
    crc->FUN_004A1D50(Damage);
    crc->FUN_004A1D50(DamageRadius);
    crc->FUN_004A1CA0(IsTiberium);
}
