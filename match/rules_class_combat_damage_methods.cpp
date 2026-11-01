// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Compared against retail gamemd.exe v1.001 at 0x66BBB0.

#include "rules_class_ini_support.h"

// Single animation type read (key present: look the name up, otherwise keep the default).
static inline AnimTypeClass* ReadAnimType(CCINIClass* ini, const char* section, const char* key, AnimTypeClass* defaultValue, char* buffer)
{
    return ini->ReadString(section, key, STR_00889F64, buffer, 0x80) ? AnimType_FindPtr(buffer) : defaultValue;
}

// FUNCTION: GAMEMD 0x66BBB0
//
// Read the [CombatDamage] section into the rules object. Reports whether the section exists.
// PARTIAL: 92.2% positional. Same instruction count (1380) and same instruction multiset as retail; what is
// left is register choice. Retail's temporaries rotate EAX/ECX/EDX one place ahead of ours at every Scorches
// and SplashList type-list read (retail takes ECX for the strtok buffer where we take EAX), which also
// reorders the push/lea pairs and the three trailing field copies in those six blocks.
// The DrainAnimationType and ControlledAnimationType reads go through ReadAnimType: with that
// helper VC6 keeps all six list destructors as calls and the first list's vptr store, as retail does.
bool RulesClass::Read_CombatDamage(CCINIClass* pINI)
{
    bool        ok  = false;
    const char* key = 0;

    if (key == 0) {
        ok = pINI->GetSection(CombatDamageSection) != 0;
    } else {
        ok = pINI->GetEntry(CombatDamageSection, key) != 0;
    }
    if (ok) {
        char buffer[0x80];

        AmmoCrateDamage = pINI->ReadInteger(CombatDamageSection, "AmmoCrateDamage", AmmoCrateDamage);
        IonCannonDamage = pINI->ReadInteger(CombatDamageSection, "IonCannonDamage", IonCannonDamage);
        RailgunDamageRadius = pINI->ReadInteger(CombatDamageSection, "RailgunDamageRadius", RailgunDamageRadius);
        TiberiumExplosionDamage = pINI->ReadInteger(CombatDamageSection, "TiberiumExplosionDamage", TiberiumExplosionDamage);
        TiberiumStrength = pINI->ReadInteger(CombatDamageSection, "TiberiumStrength", TiberiumStrength);
        list_07C4 = ReadSmudgeTypeList(pINI, CombatDamageSection, "Scorches", list_07C4, buffer);
        list_07E0 = ReadSmudgeTypeList(pINI, CombatDamageSection, "Scorches1", list_07E0, buffer);
        list_07FC = ReadSmudgeTypeList(pINI, CombatDamageSection, "Scorches2", list_07FC, buffer);
        list_0818 = ReadSmudgeTypeList(pINI, CombatDamageSection, "Scorches3", list_0818, buffer);
        list_0834 = ReadSmudgeTypeList(pINI, CombatDamageSection, "Scorches4", list_0834, buffer);
        list_0BC0 = ReadAnimTypeList(pINI, CombatDamageSection, "SplashList", list_0BC0, buffer);
        { WarheadTypeClass* t0 = FlameDamage; FlameDamage = pINI->ReadString(CombatDamageSection, "FlameDamage", STR_00889F64, buffer, 0x80) ? WarheadType_FindPtr(buffer) : t0; }
        { WarheadTypeClass* t1 = FlameDamage2; FlameDamage2 = pINI->ReadString(CombatDamageSection, "FlameDamage2", STR_00889F64, buffer, 0x80) ? WarheadType_FindPtr(buffer) : t1; }
        { WarheadTypeClass* t2 = C4Warhead; C4Warhead = pINI->ReadString(CombatDamageSection, "C4Warhead", STR_00889F64, buffer, 0x80) ? WarheadType_FindPtr(buffer) : t2; }
        { WarheadTypeClass* t3 = CrushWarhead; CrushWarhead = pINI->ReadString(CombatDamageSection, "CrushWarhead", STR_00889F64, buffer, 0x80) ? WarheadType_FindPtr(buffer) : t3; }
        { WarheadTypeClass* t4 = V3Warhead; V3Warhead = pINI->ReadString(CombatDamageSection, "V3Warhead", STR_00889F64, buffer, 0x80) ? WarheadType_FindPtr(buffer) : t4; }
        { WarheadTypeClass* t5 = DMislWarhead; DMislWarhead = pINI->ReadString(CombatDamageSection, "DMislWarhead", STR_00889F64, buffer, 0x80) ? WarheadType_FindPtr(buffer) : t5; }
        { WarheadTypeClass* t6 = V3Warhead; V3EliteWarhead = pINI->ReadString(CombatDamageSection, "V3EliteWarhead", STR_00889F64, buffer, 0x80) ? WarheadType_FindPtr(buffer) : t6; }
        { WarheadTypeClass* t7 = DMislWarhead; DMislEliteWarhead = pINI->ReadString(CombatDamageSection, "DMislEliteWarhead", STR_00889F64, buffer, 0x80) ? WarheadType_FindPtr(buffer) : t7; }
        { WarheadTypeClass* t8 = CMislWarhead; CMislWarhead = pINI->ReadString(CombatDamageSection, "CMislWarhead", STR_00889F64, buffer, 0x80) ? WarheadType_FindPtr(buffer) : t8; }
        { WarheadTypeClass* t9 = CMislWarhead; CMislEliteWarhead = pINI->ReadString(CombatDamageSection, "CMislEliteWarhead", STR_00889F64, buffer, 0x80) ? WarheadType_FindPtr(buffer) : t9; }
        { WarheadTypeClass* t10 = IvanWarhead; IvanWarhead = pINI->ReadString(CombatDamageSection, "IvanWarhead", STR_00889F64, buffer, 0x80) ? WarheadType_FindPtr(buffer) : t10; }
        CanDetonateTimeBomb = pINI->ReadBool(CombatDamageSection, "CanDetonateTimeBomb", CanDetonateTimeBomb);
        CanDetonateDeathBomb = pINI->ReadBool(CombatDamageSection, "CanDetonateDeathBomb", CanDetonateDeathBomb);
        { WeaponTypeClass* t11 = DeathWeapon; DeathWeapon = pINI->ReadString(CombatDamageSection, "DeathWeapon", STR_00889F64, buffer, 0x80) ? WeaponType_FindPtr(buffer) : t11; }
        IvanDamage = pINI->ReadInteger(CombatDamageSection, "IvanDamage", IvanDamage);
        IvanTimedDelay = pINI->ReadInteger(CombatDamageSection, "IvanTimedDelay", IvanTimedDelay);
        unknown_FE0 = MapObjLoadShape("BOMBCURS.SHP", 0);
        unknown_FE4 = MapObjLoadShape("CHRONOSK.SHP", 0);
        IvanIconFlickerRate = pINI->ReadInteger(CombatDamageSection, "IvanIconFlickerRate", IvanIconFlickerRate);
        IronCurtainDuration = pINI->ReadInteger(CombatDamageSection, "IronCurtainDuration", IronCurtainDuration);
        PsychicRevealRadius = pINI->ReadInteger(CombatDamageSection, "PsychicRevealRadius", PsychicRevealRadius);
        OccupyDamageMultiplier = pINI->ReadDouble(CombatDamageSection, "OccupyDamageMultiplier", (double)OccupyDamageMultiplier);
        OccupyROFMultiplier = pINI->ReadDouble(CombatDamageSection, "OccupyROFMultiplier", (double)OccupyROFMultiplier);
        OccupyWeaponRange = pINI->ReadInteger(CombatDamageSection, "OccupyWeaponRange", OccupyWeaponRange);
        BunkerDamageMultiplier = pINI->ReadDouble(CombatDamageSection, "BunkerDamageMultiplier", (double)BunkerDamageMultiplier);
        BunkerROFMultiplier = pINI->ReadDouble(CombatDamageSection, "BunkerROFMultiplier", (double)BunkerROFMultiplier);
        BunkerWeaponRangeBonus = pINI->ReadInteger(CombatDamageSection, "BunkerWeaponRangeBonus", BunkerWeaponRangeBonus);
        OpenToppedDamageMultiplier = pINI->ReadDouble(CombatDamageSection, "OpenToppedDamageMultiplier", (double)OpenToppedDamageMultiplier);
        OpenToppedRangeBonus = pINI->ReadInteger(CombatDamageSection, "OpenToppedRangeBonus", OpenToppedRangeBonus);
        OpenToppedWarpDistance = pINI->ReadInteger(CombatDamageSection, "OpenToppedWarpDistance", OpenToppedWarpDistance);
        list_0EE8 = pINI->ReadIntegerList(CombatDamageSection, "OverloadCount", list_0EE8);
        list_0F04 = pINI->ReadIntegerList(CombatDamageSection, "OverloadDamage", list_0F04);
        list_0F20 = pINI->ReadIntegerList(CombatDamageSection, "OverloadFrames", list_0F20);
        MindControlAttackLineFrames = pINI->ReadInteger(CombatDamageSection, "MindControlAttackLineFrames", MindControlAttackLineFrames);
        DrainAnimationType = ReadAnimType(pINI, CombatDamageSection, "DrainAnimationType", DrainAnimationType, buffer);
        DrainMoneyFrameDelay = pINI->ReadInteger(CombatDamageSection, "DrainMoneyFrameDelay", DrainMoneyFrameDelay);
        DrainMoneyAmount = pINI->ReadInteger(CombatDamageSection, "DrainMoneyAmount", DrainMoneyAmount);
        FallingDamageMultiplier = pINI->ReadDouble(CombatDamageSection, "FallingDamageMultiplier", (double)FallingDamageMultiplier);
        CurrentStrengthDamage = pINI->ReadBool(CombatDamageSection, "CurrentStrengthDamage", CurrentStrengthDamage);
        ControlledAnimationType = ReadAnimType(pINI, CombatDamageSection, "ControlledAnimationType", ControlledAnimationType, buffer);
        { AnimTypeClass* t14 = PermaControlledAnimationType; PermaControlledAnimationType = pINI->ReadString(CombatDamageSection, "PermaControlledAnimationType", STR_00889F64, buffer, 0x80) ? AnimType_FindPtr(buffer) : t14; }
        { WarheadTypeClass* t15 = IonCannonWarhead; IonCannonWarhead = pINI->ReadString(CombatDamageSection, "IonCannonWarhead", STR_00889F64, buffer, 0x80) ? WarheadType_FindPtr(buffer) : t15; }
        { ParticleSystemTypeClass* t16 = DefaultLargeGreySmokeSystem; DefaultLargeGreySmokeSystem = pINI->ReadString(CombatDamageSection, "DefaultLargeGreySmokeSystem", STR_00889F64, buffer, 0x80) ? ParticleSystemType_FindPtr(buffer) : t16; }
        { ParticleSystemTypeClass* t17 = DefaultSmallGreySmokeSystem; DefaultSmallGreySmokeSystem = pINI->ReadString(CombatDamageSection, "DefaultSmallGreySmokeSystem", STR_00889F64, buffer, 0x80) ? ParticleSystemType_FindPtr(buffer) : t17; }
        { ParticleSystemTypeClass* t18 = DefaultSparkSystem; DefaultSparkSystem = pINI->ReadString(CombatDamageSection, "DefaultSparkSystem", STR_00889F64, buffer, 0x80) ? ParticleSystemType_FindPtr(buffer) : t18; }
        { ParticleSystemTypeClass* t19 = DefaultLargeRedSmokeSystem; DefaultLargeRedSmokeSystem = pINI->ReadString(CombatDamageSection, "DefaultLargeRedSmokeSystem", STR_00889F64, buffer, 0x80) ? ParticleSystemType_FindPtr(buffer) : t19; }
        { ParticleSystemTypeClass* t20 = DefaultSmallRedSmokeSystem; DefaultSmallRedSmokeSystem = pINI->ReadString(CombatDamageSection, "DefaultSmallRedSmokeSystem", STR_00889F64, buffer, 0x80) ? ParticleSystemType_FindPtr(buffer) : t20; }
        { ParticleSystemTypeClass* t21 = DefaultDebrisSmokeSystem; DefaultDebrisSmokeSystem = pINI->ReadString(CombatDamageSection, "DefaultDebrisSmokeSystem", STR_00889F64, buffer, 0x80) ? ParticleSystemType_FindPtr(buffer) : t21; }
        { ParticleSystemTypeClass* t22 = DefaultFireStreamSystem; DefaultFireStreamSystem = pINI->ReadString(CombatDamageSection, "DefaultFireStreamSystem", STR_00889F64, buffer, 0x80) ? ParticleSystemType_FindPtr(buffer) : t22; }
        { ParticleSystemTypeClass* t23 = DefaultTestParticleSystem; DefaultTestParticleSystem = pINI->ReadString(CombatDamageSection, "DefaultTestParticleSystem", STR_00889F64, buffer, 0x80) ? ParticleSystemType_FindPtr(buffer) : t23; }
        { ParticleSystemTypeClass* t24 = DefaultRepairParticleSystem; DefaultRepairParticleSystem = pINI->ReadString(CombatDamageSection, "DefaultRepairParticleSystem", STR_00889F64, buffer, 0x80) ? ParticleSystemType_FindPtr(buffer) : t24; }
        BerzerkAllowed = pINI->ReadBool(CombatDamageSection, "BerzerkAllowed", BerzerkAllowed);
        TurboBoost = pINI->ReadDouble(CombatDamageSection, "TurboBoost", TurboBoost);
        AtomDamage = pINI->ReadInteger(CombatDamageSection, "AtomDamage", AtomDamage);
        BallisticScatter = pINI->ReadFraction(CombatDamageSection, "BallisticScatter", BallisticScatter);
        BridgeStrength = pINI->ReadInteger(CombatDamageSection, "BridgeStrength", BridgeStrength);
        C4Delay = pINI->ReadDouble(CombatDamageSection, "C4Delay", C4Delay);
        Crush = pINI->ReadFraction(CombatDamageSection, "Crush", Crush);
        ExpSpread = pINI->ReadDouble(CombatDamageSection, "ExpSpread", ExpSpread);
        FireSupress = pINI->ReadFraction(CombatDamageSection, "FireSupress", FireSupress);
        HomingScatter = pINI->ReadFraction(CombatDamageSection, "HomingScatter", HomingScatter);
        MaxDamage = pINI->ReadInteger(CombatDamageSection, "MaxDamage", MaxDamage);
        MinDamage = pINI->ReadInteger(CombatDamageSection, "MinDamage", MinDamage);
        TiberiumExplosive = pINI->ReadBool(CombatDamageSection, "TiberiumExplosive", TiberiumExplosive);
        PlayerAutoCrush = pINI->ReadBool(CombatDamageSection, "PlayerAutoCrush", PlayerAutoCrush);
        PlayerReturnFire = pINI->ReadBool(CombatDamageSection, "PlayerReturnFire", PlayerReturnFire);
        PlayerScatter = pINI->ReadBool(CombatDamageSection, "PlayerScatter", PlayerScatter);
        TreeTargeting = pINI->ReadBool(CombatDamageSection, "TreeTargeting", TreeTargeting);
        Incoming = pINI->ReadPercentAsByte(CombatDamageSection, "Incoming", Incoming);
        CollapseChance = pINI->ReadInteger(CombatDamageSection, "CollapseChance", CollapseChance);
        return true;
    }
    return false;
}
