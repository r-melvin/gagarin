// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Slot 13 of WarheadTypeClass (vtable 0x7F6B30), read off retail gamemd.exe v1.001: the base
//   feeds its fields to the checksum sink, then this type's own (layout:
//   _layout/warhead_type_class.h).

#include "../_layout/warhead_type_class.h"

// FUNCTION: GAMEMD 0x75DEC0
void WarheadTypeClass::vf_13(Obj_004A1D30* crc)
{
    AbstractTypeClass::vf_13(crc);
    crc->FUN_004A1CA0(Wall);
    crc->FUN_004A1CA0(Wood);
    crc->FUN_004A1CA0(Tiberium);
    crc->FUN_004A1CA0(unknown_bool_149);
    crc->FUN_004A1CA0(Sparky);
    crc->FUN_004A1CA0(Sonic);
    crc->FUN_004A1CA0(Fire);
    crc->FUN_004A1CA0(Conventional);
    crc->FUN_004A1CA0(Rocker);
    crc->FUN_004A1CA0(DirectRocker);
    crc->FUN_004A1CA0(Bright);
    crc->FUN_004A1CA0(CLDisableRed);
    crc->FUN_004A1CA0(CLDisableGreen);
    crc->FUN_004A1CA0(CLDisableBlue);
    crc->FUN_004A1D90(Deform);
    crc->FUN_004A1D50(DeformTreshold);
    crc->FUN_004A1D90(ProneDamage);
    crc->FUN_004A1CA0(Veinhole);
    crc->FUN_004A1D50(ShakeXlo);
    crc->FUN_004A1D50(ShakeXhi);
    crc->FUN_004A1D50(ShakeYlo);
    crc->FUN_004A1D50(ShakeYhi);
    crc->FUN_004A1DE0(&Locomotor, 0x10);
    for (int i = 0; i < 0xB; i++)
        crc->FUN_004A1D90(Verses[i]);
    crc->FUN_004A1D50(AnimList.Count);
    crc->FUN_004A1D50(InfDeath);
}
