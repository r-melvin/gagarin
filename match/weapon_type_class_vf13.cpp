// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Slot 13 of WeaponTypeClass (vtable 0x7F73B8), read off retail gamemd.exe v1.001: the base
//   feeds its fields to the checksum sink, then this type's own (layout: weapon_type_class.h).

#include "weapon_type_class.h"

// A pointed-to type object's RTTI-info interface subobject sits at +4; its slot 4 (+0x10),
// __stdcall with the subobject as `this`, yields the id mixed into the checksum.
struct RttiInfoView_00772AE0
{
    virtual long __stdcall Slot0();
    virtual long __stdcall Slot1();
    virtual long __stdcall Slot2();
    virtual long __stdcall Slot3();
    virtual int __stdcall Slot4();
};

static inline int RttiInfoId_00772AE0(void* object)
{
    return reinterpret_cast<RttiInfoView_00772AE0*>(static_cast<char*>(object) + 4)->Slot4();
}

// FUNCTION: GAMEMD 0x772AE0
void WeaponTypeClass::vf_13(Obj_004A1D30* crc)
{
    AbstractTypeClass::vf_13(crc);
    crc->FUN_004A1D50(AmbientDamage);
    crc->FUN_004A1CA0(IsSonic);
    crc->FUN_004A1CA0(TurboBoost);
    crc->FUN_004A1CA0(Supress);
    crc->FUN_004A1CA0(Camera);
    crc->FUN_004A1CA0(IsLaser);
    crc->FUN_004A1CA0(IsHouseColor);
    crc->FUN_004A1D50(Burst);
    if (Projectile)
        crc->FUN_004A1D50(RttiInfoId_00772AE0(Projectile));
    crc->FUN_004A1D50(Damage);
    crc->FUN_004A1D50(Speed);
    if (Warhead)
        crc->FUN_004A1D50(RttiInfoId_00772AE0(Warhead));
    crc->FUN_004A1D50(ROF);
    crc->FUN_004A1D50(Range);
    crc->FUN_004A1D50(Reports.Count);
    crc->FUN_004A1D50(DownReport.Count);
    crc->FUN_004A1D50(Anim.Count);
    crc->FUN_004A1CA0(UseFireParticles);
    crc->FUN_004A1CA0(Lobber);
    crc->FUN_004A1C10(LaserDuration);
    crc->FUN_004A1CA0(IsBigLaser);
    crc->FUN_004A1CA0(IsRailgun);
    crc->FUN_004A1CA0(Charges);
    crc->FUN_004A1CA0(Bright);
    crc->FUN_004A1CA0(UseSparkParticles);
    crc->FUN_004A1CA0(OmniFire);
    crc->FUN_004A1CA0(DistributedWeaponFire);
}
