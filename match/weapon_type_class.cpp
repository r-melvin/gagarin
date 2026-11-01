// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x771C70  WeaponTypeClass::WeaponTypeClass(const char*)
//   FUNCTION: GAMEMD 0x771F00  WeaponTypeClass::WeaponTypeClass(const AbstractNoInit&)
//   FUNCTION: GAMEMD 0x7729F0  WeaponTypeClass::CalculateSpeed  (__thiscall)
//   FUNCTION: GAMEMD 0x772A90  WeaponTypeClass::AllowedThreats  (__thiscall)
//   FUNCTION: GAMEMD 0x772FA0  WeaponTypeClass::FindOrAllocate  (__fastcall)
//   GLOBAL:   GAMEMD 0x887568  WeaponTypeClass::Array
//   GLOBAL:   GAMEMD 0x8871E0  GameRulesPtr
//   STRING:   GAMEMD 0x817474  "<none>"
//   STRING:   GAMEMD 0x817694  "none"

#include <new.h>
#include "weapon_type_class.h"
#include "vector_class_dynamic_ctor.h"
#include "vector_class_mutation.h"
#include "vector_class_operations.h"

// CRT case-insensitive compare (_strcmpi @ GAMEMD 0x7C8D20). Declared (no body)
// so the call is a reloc; excluded from the match target.
int __cdecl gg_strcmpi(const char* a, const char* b);

// FUNCTION: GAMEMD 0x771C70
WeaponTypeClass::WeaponTypeClass(const char* id)
    : AbstractTypeClass(id),
      AmbientDamage(0),
      Burst(1),
      Projectile(0),
      Damage(0),
      Speed(0),
      Warhead(0),
      ROF(0),
      Range(0),
      MinimumRange(0),
      Reports(),
      DownReport(),
      Anim(),
      OccupantAnim(0),
      AssaultAnim(0),
      OpenToppedAnim(0),
      AttachedParticleSystem(0),
      LaserInnerColor(0, 0, 0),
      LaserOuterColor(0, 0, 0),
      LaserOuterSpread(0, 0, 0),
      UseFireParticles(false),
      UseSparkParticles(false),
      OmniFire(false),
      DistributedWeaponFire(false),
      IsRailgun(false),
      Lobber(false),
      Bright(false),
      IsSonic(false),
      Spawner(false),
      LimboLaunch(false),
      DecloakToFire(true),
      CellRangefinding(false),
      FireOnce(false),
      NeverUse(false),
      RevealOnFire(true),
      TerrainFire(false),
      SabotageCursor(false),
      MigAttackCursor(false),
      DisguiseFireOnly(false),
      DisguiseFakeBlinkTime(0),
      InfiniteMindControl(false),
      FireWhileMoving(true),
      DrainWeapon(false),
      FireInTransport(true),
      Suicide(false),
      TurboBoost(false),
      Supress(false),
      Camera(false),
      Charges(false),
      IsLaser(false),
      DiskLaser(false),
      IsLine(false),
      IsBigLaser(false),
      IsHouseColor(false),
      LaserDuration(10),
      IonSensitive(false),
      AreaFire(false),
      IsElectricBolt(false),
      DrawBoltAsLaser(false),
      IsAlternateColor(false),
      IsRadBeam(false),
      IsRadEruption(false),
      RadLevel(0),
      IsMagBeam(false)
{
    AbstractClass::vf_rtti_5();
    WeaponTypeClass_Array.AddItem(this);
}

// FUNCTION: GAMEMD 0x771F00
WeaponTypeClass::WeaponTypeClass(const AbstractNoInit& noInit)
    : AbstractTypeClass(noInit), Reports(noInit), DownReport(noInit), Anim(noInit)
{
}

// FUNCTION: GAMEMD 0x7729F0  (__thiscall)
// Recompute the launch Speed of this weapon: if the projectile exists and its
// gating field @0x2DC is clear, take the gravity baseline (Rules int @0x16B8)
// — or the Func_0048ACF0 value when the projectile byte at +0x295 is set — and feed
// it with the weapon Range to Func_0048AB90, storing the result in Speed.
void WeaponTypeClass::CalculateSpeed()
{
    BulletTypeClass* proj = this->Projectile;
    if (proj != 0 && proj->ROT == 0)
    {
        double v = (double)GameRulesPtr->Field16B8;
        if (proj->Floater != 0)
            v = Func_0048ACF0();
        this->Speed = (int)Func_0048AB90(this->Range, v);
    }
}

// FUNCTION: GAMEMD 0x772A90  (__thiscall)
// Build the projectile threat mask from native byte fields +0x2A4 and +0x2A5;
// the second condition corresponds to the retail `or al,0xB8` operation.
int WeaponTypeClass::AllowedThreats()
{
    BulletTypeClass* proj = this->Projectile;
    int threats = 0;
    if (proj->AA)
        threats = 4;
    if (proj->AG)
        threats |= 0xB8;
    return threats;
}

// FUNCTION: GAMEMD 0x772FA0  (__fastcall)
// Find the weapon type named `id` in the global Array (case-insensitive); if it
// is not present, allocate and construct a fresh one. The reserved names
// "<none>" and "none" are rejected (return null).
WeaponTypeClass* WeaponTypeClass::FindOrAllocate(const char* id)
{
    if (gg_strcmpi("<none>", id) != 0 && gg_strcmpi("none", id) != 0)
    {
        for (int i = 0; i < WeaponTypeClass_Array.Count; ++i)
        {
            if (gg_strcmpi(WeaponTypeClass_Array.Items[i]->ID, id) == 0)
                return WeaponTypeClass_Array.Items[i];
        }

        // Hand-rolled `new WeaponTypeClass(id)`: raw operator new + null guard +
        // construct (no /GX exception-cleanup frame around construction).
        WeaponTypeClass* p = (WeaponTypeClass*)::operator new(sizeof(WeaponTypeClass));
        if (p)
            return new (p) WeaponTypeClass(id);
    }
    return 0;
}

// FUNCTION: GAMEMD 0x7730F0
WeaponTypeClass::~WeaponTypeClass()
{
    AnnounceExpiredPointer(1);
    Projectile = 0;
    Warhead = 0;
    WeaponTypeClass_Array.RemoveItem(this);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x887568
extern DynamicVectorClass<WeaponTypeClass*> WeaponTypeClass_Array;
// END defined globals
