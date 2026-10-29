// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   TechnoTypeClass::vf_25 (retail 0x712170, 0x3FD1 bytes): the INI reader of the techno type blueprint.
//   Every key string, destination offset, reader call and default was read off the user's retail
//   gamemd.exe v1.001 disassembly; field names are the INI key strings themselves.
//
//   Build notes (all read off the retail bytes):
//   - The first half of the reader (up to the Dock list) destroys its list temporaries one inline level
//     deeper than the second half: retail keeps their VectorClass::Clear out of line there and expands it
//     inline from MoveSound onwards. The Early* helpers and the inline depth limit reproduce that split.
//   - `sound` and `index` are function-level variables: retail reuses the same two registers across all of
//     the sound-index reads, and the scheduling of every one of those reads depends on it.
//   - The section is passed as the bare ID bytes through the first half, and through the identity call
//     0x524EC0 in every list read and from RadarVisible on; the art INI sections go through it too.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../_layout/techno_type_class.h"
#include "../_layout/rules_class.h"
#include "../_layout/voxel_resource_data.h"
#include "../combat/weapon_type_class.h"
#include "../movement/waypoint_queue_accessors.h"
#include "rules_class_ini_support.h"
#include "../platform/ccini_class_type_list_methods.h"

class InfantryTypeClass;
class AircraftTypeClass;

// FUNCTION: GAMEMD 0x41CEF0 (decl; reloc) -- AircraftType lookup-or-create by name.
AircraftTypeClass* AircraftType_FindPtr(const char* id);

// The CCINIClass readers this function uses that CCINIClass itself does not declare. Retail keeps
// them on the same reader object (INIClass/CCINIClass), so the view derives from it.
class TechnoTypeIniView : public CCINIClass
{
public:
    // FUNCTION: GAMEMD 0x476FC0 (decl; reloc) -- movement speed class by name.
    int ReadSpeedType(const char* section, const char* key, int fallback);
    // FUNCTION: GAMEMD 0x477590 (decl; reloc) -- VHP scan class by name.
    int ReadVHPScan(const char* section, const char* key, int fallback);
    // FUNCTION: GAMEMD 0x4749E0 (decl; reloc) -- build category by name.
    int ReadCategory(const char* section, const char* key, int fallback);
    // FUNCTION: GAMEMD 0x474940 (decl; reloc) -- pip scale by name.
    int ReadPipScale(const char* section, const char* key, int fallback);
    // FUNCTION: GAMEMD 0x4750D0 (decl; reloc) -- house list as a bit mask.
    unsigned long ReadHouseTypesList(const char* section, const char* key, unsigned long fallback);
    // FUNCTION: GAMEMD 0x474E40 (decl; reloc) -- movement zone by name.
    int ReadMovementZone(const char* section, const char* key, int fallback);
    // FUNCTION: GAMEMD 0x67BAC0 (decl; reloc) -- infantry type by name; this in ECX, section in EDX.
    InfantryTypeClass* __fastcall ReadInfantryType(const char* section, const char* key, InfantryTypeClass* fallback);
    // FUNCTION: GAMEMD 0x67BD30 (decl; reloc) -- aircraft type by name; this in ECX, section in EDX.
    AircraftTypeClass* __fastcall ReadAircraftType(const char* section, const char* key, AircraftTypeClass* fallback);
    // FUNCTION: GAMEMD 0x476420 (decl; reloc) -- three integers; the result comes back through a hidden pointer.
    CoordStruct ReadIntTriple(const char* section, const char* key, const CoordStruct& fallback);
    // FUNCTION: GAMEMD 0x529CA0 (decl; reloc) -- a coordinate triple, same convention.
    CoordStruct ReadCoord(const char* section, const char* key, const CoordStruct& fallback);
    // FUNCTION: GAMEMD 0x477640 (decl; reloc) -- ability list; raw ABI: the result buffer is the first stack argument and comes back in EAX.
    AbilitiesStruct* ReadAbilitiesRaw(AbilitiesStruct* result, const char* section, const char* key, const AbilitiesStruct* fallback);
    // FUNCTION: GAMEMD 0x527920 (decl; reloc) -- a GUID; the default goes by value.
    GUIDStruct ReadGUID(const char* section, const char* key, GUIDStruct fallback);
};
// The assignment 0x7179D0 of an ability block, in the same raw ABI: result buffer first, EAX = result.
struct AbilitiesView : AbilitiesStruct
{
    // FUNCTION: GAMEMD 0x7179D0 (decl; reloc)
    AbilitiesStruct* AssignRaw(AbilitiesStruct* result, const AbilitiesStruct* source);
};

// GLOBAL: GAMEMD 0x887180 -- art INI selected by native immediate receivers.
extern CCINIClass DAT_00887180;

// FUNCTION: GAMEMD 0x524EC0 (decl; reloc) -- `MOV EAX,ECX; RET`: the identity on a name pointer.
const char* NameOf(const char* name);
char* NameOfBuf(char* name);
// FUNCTION: GAMEMD 0x525430 (decl; reloc) -- comma-separated sound names as registry indices.
TypeList<int> FUN_00525430(CCINIClass* ini, const char* section, const char* key, TypeList<int> fallback);
// FUNCTION: GAMEMD 0x4770E0 (decl; reloc) -- comma-separated building names as a list of ids.
TypeList<int> FUN_004770E0(CCINIClass* ini, const char* section, const char* key, TypeList<int> fallback);
// FUNCTION: GAMEMD 0x4770E0 (decl; reloc) -- the same reader entered with a list built through the other copy (0x477B60).
TypeList<int> FUN_004770E0FromBuilt(CCINIClass* ini, const char* section, const char* key, TypeListInt fallback);
// FUNCTION: GAMEMD 0x7179C0 (decl; reloc) -- the empty AbilitiesStruct destructor; ECX is the object.
void FUN_007179C0(const AbilitiesStruct* self);
// FUNCTION: GAMEMD 0x626DA0 (decl; reloc)
int FUN_00626DA0();
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);
// FUNCTION: GAMEMD 0x6BEC50 (decl; reloc)
void FUN_006BEC50(int);

// Turret/barrel animation block: the recoil block (0x10) plus the flag byte that follows it.
struct TurretAnimBlock : WaypointQueue_00717A30
{
    bool unknown_10;
    unsigned char unknown_11[3];
    // FUNCTION: GAMEMD 0x717A70 (decl; reloc)
    int GetSize() const;
};
GG_STATIC_ASSERT(sizeof(TurretAnimBlock) == 0x14);

// Comma-separated type lists, expanded inline in the reader like the animation list in the support header.
static __forceinline TypeList<const VoxelAnimTypeClass*> BuildVoxelAnimTypeList(char* buffer)
{
    TypeList<const VoxelAnimTypeClass*> list(0, 0);
    for (char* token = strtok(buffer, STR_00817F70); token && *token; token = strtok(0, STR_00817F70)) {
        const VoxelAnimTypeClass* type = VoxelAnimType_FindPtr(token);
        if (type)
            list.AddItem(type);
    }
    return list;
}
static __forceinline TypeList<const VoxelAnimTypeClass*> ReadVoxelAnimTypeList(CCINIClass* ini, const char* section,
    const char* key, const TypeList<const VoxelAnimTypeClass*>& defaultValue, char* buffer)
{
    if (ini->ReadString(section, key, STR_00889F64, buffer, 0x80))
        return BuildVoxelAnimTypeList(buffer);
    return defaultValue;
}
static __forceinline TypeList<const BuildingTypeClass*> BuildBuildingTypeList(char* buffer)
{
    TypeList<const BuildingTypeClass*> list(0, 0);
    for (char* token = strtok(buffer, STR_00817F70); token && *token; token = strtok(0, STR_00817F70)) {
        const BuildingTypeClass* type = BuildingType_FindPtr(token);
        if (type)
            list.AddItem(type);
    }
    return list;
}
static __forceinline TypeList<const BuildingTypeClass*> ReadBuildingTypeList(CCINIClass* ini, const char* section,
    const char* key, const TypeList<const BuildingTypeClass*>& defaultValue, char* buffer)
{
    if (ini->ReadString(section, key, STR_00889F64, buffer, 0x80))
        return BuildBuildingTypeList(buffer);
    return defaultValue;
}
static __forceinline TypeList<const ParticleSystemTypeClass*> BuildParticleSystemTypeList(char* buffer)
{
    TypeList<const ParticleSystemTypeClass*> list(0, 0);
    for (char* token = strtok(buffer, STR_00817F70); token && *token; token = strtok(0, STR_00817F70)) {
        const ParticleSystemTypeClass* type = ParticleSystemType_FindPtr(token);
        if (type)
            list.AddItem(type);
    }
    return list;
}
static __forceinline TypeList<const ParticleSystemTypeClass*> ReadParticleSystemTypeList(CCINIClass* ini, const char* section,
    const char* key, const TypeList<const ParticleSystemTypeClass*>& defaultValue, char* buffer)
{
    if (ini->ReadString(section, key, STR_00889F64, buffer, 0x80))
        return BuildParticleSystemTypeList(buffer);
    return defaultValue;
}

// The first half of the reader destroys its list temporaries one inline level deeper than the second half;
// under the inline depth limit below that is what keeps their VectorClass::Clear calls out of line, as retail has them.
static __forceinline void EarlyDebrisTypes(TechnoTypeClass* t, CCINIClass* ini, char* buffer)
{
    // STRING: GAMEMD 0x844384
    t->DebrisTypes = ReadVoxelAnimTypeList(ini, t->ID.Data, "DebrisTypes", t->DebrisTypes, buffer);
}
static __forceinline void EarlyDebrisMaximums(TechnoTypeClass* t, CCINIClass* ini)
{
    // STRING: GAMEMD 0x844374
    t->DebrisMaximums = ini->ReadIntegerList(NameOf(t->ID.Data), "DebrisMaximums", t->DebrisMaximums);
}
static __forceinline void EarlyDebrisAnims(TechnoTypeClass* t, CCINIClass* ini, char* buffer)
{
    // STRING: GAMEMD 0x844368
    t->DebrisAnims = ReadAnimTypeList(ini, t->ID.Data, "DebrisAnims", t->DebrisAnims, buffer);
}
static __forceinline void EarlyVoiceMove(TechnoTypeClass* t, CCINIClass* ini)
{
    // STRING: GAMEMD 0x8442C0
    t->VoiceMove = FUN_00525430(ini, NameOf(t->ID.Data), "VoiceMove", t->VoiceMove);
}
static __forceinline void EarlyVoiceSelect(TechnoTypeClass* t, CCINIClass* ini)
{
    // STRING: GAMEMD 0x8442B4
    t->VoiceSelect = FUN_00525430(ini, NameOf(t->ID.Data), "VoiceSelect", t->VoiceSelect);
}
static __forceinline void EarlyVoiceSelectEnslaved(TechnoTypeClass* t, CCINIClass* ini)
{
    // STRING: GAMEMD 0x8442A0
    t->VoiceSelectEnslaved = FUN_00525430(ini, NameOf(t->ID.Data), "VoiceSelectEnslaved", t->VoiceSelectEnslaved);
}
static __forceinline void EarlyVoiceSelectDeactivated(TechnoTypeClass* t, CCINIClass* ini)
{
    // STRING: GAMEMD 0x844288
    t->VoiceSelectDeactivated = FUN_00525430(ini, NameOf(t->ID.Data), "VoiceSelectDeactivated", t->VoiceSelectDeactivated);
}
static __forceinline void EarlyVoiceAttack(TechnoTypeClass* t, CCINIClass* ini)
{
    // STRING: GAMEMD 0x84427C
    t->VoiceAttack = FUN_00525430(ini, NameOf(t->ID.Data), "VoiceAttack", t->VoiceAttack);
}
static __forceinline void EarlyVoiceSpecialAttack(TechnoTypeClass* t, CCINIClass* ini)
{
    // STRING: GAMEMD 0x844268
    t->VoiceSpecialAttack = FUN_00525430(ini, NameOf(t->ID.Data), "VoiceSpecialAttack", t->VoiceSpecialAttack);
}
static __forceinline void EarlyVoiceDie(TechnoTypeClass* t, CCINIClass* ini)
{
    // STRING: GAMEMD 0x84425C
    t->VoiceDie = FUN_00525430(ini, NameOf(t->ID.Data), "VoiceDie", t->VoiceDie);
}
static __forceinline void EarlyVoiceFeedback(TechnoTypeClass* t, CCINIClass* ini)
{
    // STRING: GAMEMD 0x84424C
    t->VoiceFeedback = FUN_00525430(ini, NameOf(t->ID.Data), "VoiceFeedback", t->VoiceFeedback);
}
static __forceinline void EarlyDock(TechnoTypeClass* t, CCINIClass* ini, char* buffer)
{
    // STRING: GAMEMD 0x84418C
    t->Dock = ReadBuildingTypeList(ini, t->ID.Data, "Dock", t->Dock, buffer);
}


#pragma inline_depth(4)

// PARTIAL: 98.5% -- identical instruction multiset and relocation targets; what remains is the stack offsets of
// the aggregate temporaries (the list under construction sits at ESP+0x3C where retail has ESP+0x40, and the
// coordinate/ability return buffers use a different slot), which moves about 70 displacement bytes.
// FUNCTION: GAMEMD 0x712170
//
// Read this type's keys from the rules INI section named by its ID and from the art INI section named
// by its image file. Reports whether the base type read succeeded.
bool TechnoTypeClass::vf_25(CCINIClass* ini)
{
    double coefficient;
    int sound;
    int index;
    char path[0x200];
    char cameoText[32];
    char bufA[128];
    char bufB[128];

    ini->Reset();
    if (ObjectTypeClass::vf_25(ini))
    {
        // STRING: GAMEMD 0x844520
        LandTargeting = ini->ReadInteger(ID.Data, "LandTargeting", LandTargeting);
        // STRING: GAMEMD 0x844510
        NavalTargeting = ini->ReadInteger(ID.Data, "NavalTargeting", NavalTargeting);
        // STRING: GAMEMD 0x844504
        SpeedType = static_cast<TechnoTypeIniView*>(ini)->ReadSpeedType(ID.Data, "SpeedType", SpeedType);
        // STRING: GAMEMD 0x8444F8
        CanBeHidden = DAT_00887180.ReadBool(ID.Data, "CanBeHidden", CanBeHidden);
        // STRING: GAMEMD 0x8444EC
        TypeImmune = ini->ReadBool(ID.Data, "TypeImmune", TypeImmune);
        // STRING: GAMEMD 0x8444E0
        WalkRate = ini->ReadInteger(ID.Data, "WalkRate", WalkRate);
        // STRING: GAMEMD 0x8444D4
        IdleRate = ini->ReadInteger(ID.Data, "IdleRate", IdleRate);
        // STRING: GAMEMD 0x8444C4
        MoveToShroud = ini->ReadBool(ID.Data, "MoveToShroud", MoveToShroud);
        // STRING: GAMEMD 0x8444BC
        IsTrain = ini->ReadBool(ID.Data, "IsTrain", IsTrain);
        // STRING: GAMEMD 0x8444B0
        DoubleOwned = ini->ReadBool(ID.Data, "DoubleOwned", DoubleOwned);
        // STRING: GAMEMD 0x8444A4
        GuardRange = ini->ReadFraction(ID.Data, "GuardRange", GuardRange);
        // STRING: GAMEMD 0x83355C
        Explodes = ini->ReadBool(ID.Data, "Explodes", Explodes);
        // STRING: GAMEMD 0x83B11C
        { WeaponTypeClass* t = DeathWeapon; DeathWeapon = ini->ReadString(ID.Data, "DeathWeapon", STR_00889F64, bufA, 0x80) ? WeaponType_FindPtr(bufA) : t; }
        // STRING: GAMEMD 0x844488
        DeathWeaponDamageModifier = ini->ReadDouble(ID.Data, "DeathWeaponDamageModifier", DeathWeaponDamageModifier);
        // STRING: GAMEMD 0x83C854
        FlightLevel = ini->ReadInteger(ID.Data, "FlightLevel", FlightLevel);
        // STRING: GAMEMD 0x84447C
        IsDropship = ini->ReadBool(ID.Data, "IsDropship", IsDropship);
        {
            // STRING: GAMEMD 0x844470
            double pitchAngle = ini->ReadDouble(ID.Data, "PitchAngle", -1.0);
            if (pitchAngle != -1.0)
                PitchAngle = pitchAngle * 0.017453292519943295;
            // STRING: GAMEMD 0x844464
            double rollAngle = ini->ReadDouble(ID.Data, "RollAngle", -1.0);
            if (rollAngle != -1.0)
                RollAngle = rollAngle * 0.017453292519943295;
        }
        // STRING: GAMEMD 0x844458
        PitchSpeed = ini->ReadDouble(ID.Data, "PitchSpeed", PitchSpeed);
        // STRING: GAMEMD 0x84444C
        Locomotor = static_cast<TechnoTypeIniView*>(ini)->ReadGUID(ID.Data, "Locomotor", Locomotor);
        // STRING: GAMEMD 0x84443C
        CloakingSpeed = ini->ReadInteger(ID.Data, "CloakingSpeed", CloakingSpeed);
        // STRING: GAMEMD 0x844420
        ThreatAvoidanceCoefficient = ini->ReadDouble(ID.Data, "ThreatAvoidanceCoefficient", ThreatAvoidanceCoefficient);
        // STRING: GAMEMD 0x84440C
        SlowdownDistance = ini->ReadInteger(ID.Data, "SlowdownDistance", SlowdownDistance);
        // STRING: GAMEMD 0x8443F4
        DecelerationFactor = ini->ReadDouble(ID.Data, "DeaccelerationFactor", DecelerationFactor);
        // STRING: GAMEMD 0x8443E0
        AccelerationFactor = ini->ReadDouble(ID.Data, "AccelerationFactor", AccelerationFactor);
        // STRING: GAMEMD 0x8443D8
        Weight = ini->ReadDouble(ID.Data, "Weight", Weight);
        // STRING: GAMEMD 0x8443C8
        PhysicalSize = ini->ReadDouble(ID.Data, "PhysicalSize", PhysicalSize);
        // STRING: GAMEMD 0x820178
        Size = ini->ReadDouble(ID.Data, "Size", Size);
        // STRING: GAMEMD 0x8443BC
        SizeLimit = ini->ReadDouble(ID.Data, "SizeLimit", SizeLimit);
        // STRING: GAMEMD 0x8443B0
        HoverAttack = ini->ReadBool(ID.Data, "HoverAttack", HoverAttack);
        // STRING: GAMEMD 0x8443A8
        VHPScan = static_cast<TechnoTypeIniView*>(ini)->ReadVHPScan(ID.Data, "VHPScan", VHPScan);
        // STRING: GAMEMD 0x84439C
        MaxDebris = ini->ReadInteger(ID.Data, "MaxDebris", MaxDebris);
        // STRING: GAMEMD 0x844390
        MinDebris = ini->ReadInteger(ID.Data, "MinDebris", MinDebris);
        if (MinDebris < 0)
            MinDebris = 0;
        if (MaxDebris < MinDebris)
            MaxDebris = MinDebris;
        EarlyDebrisTypes(this, ini, bufA);
        EarlyDebrisMaximums(this, ini);
        EarlyDebrisAnims(this, ini, bufA);
        // STRING: GAMEMD 0x844354
        HasTurretTooltips = ini->ReadBool(ID.Data, "HasTurretTooltips", HasTurretTooltips);
        // STRING: GAMEMD 0x844348
        TurretCount = ini->ReadInteger(ID.Data, "TurretCount", TurretCount);
        // STRING: GAMEMD 0x84433C
        WeaponCount = ini->ReadInteger(ID.Data, "WeaponCount", WeaponCount);
        // STRING: GAMEMD 0x84432C
        IsChargeTurret = ini->ReadBool(ID.Data, "IsChargeTurret", IsChargeTurret);
        // STRING: GAMEMD 0x84431C
        ClearAllWeapons = ini->ReadBool(ID.Data, "ClearAllWeapons", ClearAllWeapons);
        if (TurretCount > 0)
        {
            {
                for (int i = 0; i < WeaponCount; i++)
                {
                    char eliteKey[32];
                    char weaponKey[28];
                    // STRING: GAMEMD 0x844310
                    sprintf(weaponKey, "Weapon%d", i + 1);
                    // STRING: GAMEMD 0x844300
                    sprintf(eliteKey, "EliteWeapon%d", i + 1);
                    { WeaponTypeClass* t = Weapon[i].WeaponType; Weapon[i].WeaponType = ini->ReadString(ID.Data, weaponKey, STR_00889F64, bufA, 0x80) ? WeaponType_FindPtr(bufA) : t; }
                    { WeaponTypeClass* t = EliteWeapon[i].WeaponType; EliteWeapon[i].WeaponType = ini->ReadString(ID.Data, eliteKey, STR_00889F64, bufB, 0x80) ? WeaponType_FindPtr(bufB) : t; }
                }
            }
        }
        else
        {
            if (!ClearAllWeapons)
            {
                // STRING: GAMEMD 0x8442F8
                { WeaponTypeClass* t = Weapon[0].WeaponType; Weapon[0].WeaponType = ini->ReadString(ID.Data, "Primary", STR_00889F64, bufB, 0x80) ? WeaponType_FindPtr(bufB) : t; }
                // STRING: GAMEMD 0x8442EC
                { WeaponTypeClass* t = Weapon[1].WeaponType; Weapon[1].WeaponType = ini->ReadString(ID.Data, "Secondary", STR_00889F64, bufB, 0x80) ? WeaponType_FindPtr(bufB) : t; }
                // STRING: GAMEMD 0x8442DC
                { WeaponTypeClass* t = EliteWeapon[0].WeaponType; EliteWeapon[0].WeaponType = ini->ReadString(ID.Data, "ElitePrimary", STR_00889F64, bufB, 0x80) ? WeaponType_FindPtr(bufB) : t; }
                // STRING: GAMEMD 0x8442CC
                { WeaponTypeClass* t = EliteWeapon[1].WeaponType; EliteWeapon[1].WeaponType = ini->ReadString(ID.Data, "EliteSecondary", STR_00889F64, bufB, 0x80) ? WeaponType_FindPtr(bufB) : t; }
            }
        }
        if (ClearAllWeapons)
        {
            Weapon[0].WeaponType = 0;
            Weapon[1].WeaponType = 0;
            EliteWeapon[0].WeaponType = 0;
            EliteWeapon[1].WeaponType = 0;
        }
        EarlyVoiceMove(this, ini);
        EarlyVoiceSelect(this, ini);
        EarlyVoiceSelectEnslaved(this, ini);
        EarlyVoiceSelectDeactivated(this, ini);
        EarlyVoiceAttack(this, ini);
        EarlyVoiceSpecialAttack(this, ini);
        EarlyVoiceDie(this, ini);
        EarlyVoiceFeedback(this, ini);
        // STRING: GAMEMD 0x844240
        { int sound = AuxSound1; if (ini->ReadString(ID.Data, "AuxSound1", STR_00889F64, bufB, 0x80)) { int index = VocClass::FindIndex(bufB); if (index != -1) sound = index; } AuxSound1 = sound; }
        // STRING: GAMEMD 0x844234
        sound = AuxSound2; index = ini->ReadString(ID.Data, "AuxSound2", STR_00889F64, bufB, 0x80); AuxSound2 = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x844228
        sound = CreateSound; index = ini->ReadString(ID.Data, "CreateSound", STR_00889F64, bufB, 0x80); CreateSound = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x84421C
        sound = DamageSound; index = ini->ReadString(ID.Data, "DamageSound", STR_00889F64, bufB, 0x80); DamageSound = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x83A9D4
        sound = ImpactWaterSound; index = ini->ReadString(ID.Data, "ImpactWaterSound", STR_00889F64, bufB, 0x80); ImpactWaterSound = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x83A9C4
        sound = ImpactLandSound; index = ini->ReadString(ID.Data, "ImpactLandSound", STR_00889F64, bufB, 0x80); ImpactLandSound = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x84420C
        sound = CrashingSound; index = ini->ReadString(ID.Data, "CrashingSound", STR_00889F64, bufB, 0x80); CrashingSound = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x83A9B4
        sound = SinkingSound; index = ini->ReadString(ID.Data, "SinkingSound", STR_00889F64, bufB, 0x80); SinkingSound = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x8441FC
        sound = VoiceFalling; index = ini->ReadString(ID.Data, "VoiceFalling", STR_00889F64, bufB, 0x80); VoiceFalling = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x8441EC
        sound = VoiceCrashing; index = ini->ReadString(ID.Data, "VoiceCrashing", STR_00889F64, bufB, 0x80); VoiceCrashing = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x8441DC
        sound = VoiceSinking; index = ini->ReadString(ID.Data, "VoiceSinking", STR_00889F64, bufB, 0x80); VoiceSinking = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x8441D0
        sound = VoiceEnter; index = ini->ReadString(ID.Data, "VoiceEnter", STR_00889F64, bufB, 0x80); VoiceEnter = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x8441C0
        sound = VoiceCapture; index = ini->ReadString(ID.Data, "VoiceCapture", STR_00889F64, bufB, 0x80); VoiceCapture = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x8441B4
        CloakStop = ini->ReadBool(ID.Data, "CloakStop", CloakStop);
        // STRING: GAMEMD 0x8441AC
        Storage = ini->ReadInteger(ID.Data, "Storage", Storage);
        // STRING: GAMEMD 0x8441A0
        BuildLimit = ini->ReadInteger(ID.Data, "BuildLimit", BuildLimit);
        // STRING: GAMEMD 0x844194
        Category = static_cast<TechnoTypeIniView*>(ini)->ReadCategory(ID.Data, "Category", Category);
        EarlyDock(this, ini, bufB);
        // STRING: GAMEMD 0x844180
        { BuildingTypeClass* t = DeploysInto; DeploysInto = ini->ReadString(ID.Data, "DeploysInto", STR_00889F64, bufB, 0x80) ? BuildingType_FindPtr(bufB) : t; }
        // STRING: GAMEMD 0x844170
        { UnitTypeClass* t = UndeploysInto; UndeploysInto = ini->ReadString(ID.Data, "UndeploysInto", STR_00889F64, bufB, 0x80) ? UnitType_FindPtr(bufB) : t; }
        // STRING: GAMEMD 0x844164
        { UnitTypeClass* t = PowersUnit; PowersUnit = ini->ReadString(ID.Data, "PowersUnit", STR_00889F64, bufB, 0x80) ? UnitType_FindPtr(bufB) : t; }
        // STRING: GAMEMD 0x844158
        PoweredUnit = ini->ReadBool(ID.Data, "PoweredUnit", PoweredUnit);
        // STRING: GAMEMD 0x844148
        LightningRod = ini->ReadBool(ID.Data, "LightningRod", LightningRod);
        // STRING: GAMEMD 0x844138
        ManualReload = ini->ReadBool(ID.Data, "ManualReload", ManualReload);
        // STRING: GAMEMD 0x84412C
        TurretSpins = ini->ReadBool(ID.Data, "TurretSpins", TurretSpins);
        // STRING: GAMEMD 0x844118
        TiltCrashJumpjet = ini->ReadBool(ID.Data, "TiltCrashJumpjet", TiltCrashJumpjet);
        // STRING: GAMEMD 0x844110
        Turret = ini->ReadBool(ID.Data, "Turret", Turret);
        // STRING: GAMEMD 0x8440FC
        sound = TurretRotateSound; index = ini->ReadString(ID.Data, "TurretRotateSound", STR_00889F64, bufB, 0x80); TurretRotateSound = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x8440E8
        sound = EnterTransportSound; index = ini->ReadString(ID.Data, "EnterTransportSound", STR_00889F64, bufB, 0x80); EnterTransportSound = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x8440D4
        sound = LeaveTransportSound; index = ini->ReadString(ID.Data, "LeaveTransportSound", STR_00889F64, bufB, 0x80); LeaveTransportSound = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x8440C8
        MoveSound = FUN_00525430(ini, NameOf(ID.Data), "MoveSound", MoveSound);
        // STRING: GAMEMD 0x8440BC
        DieSound = FUN_00525430(ini, NameOf(ID.Data), "DieSound", DieSound);
        // STRING: GAMEMD 0x8440B0
        sound = DeploySound; index = ini->ReadString(ID.Data, "DeploySound", STR_00889F64, bufB, 0x80); DeploySound = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x8440A0
        sound = UndeploySound; index = ini->ReadString(ID.Data, "UndeploySound", STR_00889F64, bufB, 0x80); UndeploySound = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x83A9A4
        sound = ChronoInSound; index = ini->ReadString(ID.Data, "ChronoInSound", STR_00889F64, bufB, 0x80); ChronoInSound = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x83A994
        sound = ChronoOutSound; index = ini->ReadString(ID.Data, "ChronoOutSound", STR_00889F64, bufB, 0x80); ChronoOutSound = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x844090
        sound = VoiceHarvest; index = ini->ReadString(ID.Data, "VoiceHarvest", STR_00889F64, bufB, 0x80); VoiceHarvest = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x844074
        sound = VoicePrimaryWeaponAttack; index = ini->ReadString(ID.Data, "VoicePrimaryWeaponAttack", STR_00889F64, bufB, 0x80); VoicePrimaryWeaponAttack = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x844054
        sound = VoicePrimaryEliteWeaponAttack; index = ini->ReadString(ID.Data, "VoicePrimaryEliteWeaponAttack", STR_00889F64, bufB, 0x80); VoicePrimaryEliteWeaponAttack = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x844038
        sound = VoiceSecondaryWeaponAttack; index = ini->ReadString(ID.Data, "VoiceSecondaryWeaponAttack", STR_00889F64, bufB, 0x80); VoiceSecondaryWeaponAttack = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x844018
        sound = VoiceSecondaryEliteWeaponAttack; index = ini->ReadString(ID.Data, "VoiceSecondaryEliteWeaponAttack", STR_00889F64, bufB, 0x80); VoiceSecondaryEliteWeaponAttack = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x84400C
        sound = VoiceDeploy; index = ini->ReadString(ID.Data, "VoiceDeploy", STR_00889F64, bufB, 0x80); VoiceDeploy = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x843FFC
        sound = VoiceUndeploy; index = ini->ReadString(ID.Data, "VoiceUndeploy", STR_00889F64, bufB, 0x80); VoiceUndeploy = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x83A730
        sound = EnterGrinderSound; index = ini->ReadString(ID.Data, "EnterGrinderSound", STR_00889F64, bufB, 0x80); EnterGrinderSound = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x83A71C
        sound = LeaveGrinderSound; index = ini->ReadString(ID.Data, "LeaveGrinderSound", STR_00889F64, bufB, 0x80); LeaveGrinderSound = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x83A704
        sound = EnterBioReactorSound; index = ini->ReadString(ID.Data, "EnterBioReactorSound", STR_00889F64, bufB, 0x80); EnterBioReactorSound = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x83A6EC
        sound = LeaveBioReactorSound; index = ini->ReadString(ID.Data, "LeaveBioReactorSound", STR_00889F64, bufB, 0x80); LeaveBioReactorSound = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x83A6DC
        sound = ActivateSound; index = ini->ReadString(ID.Data, "ActivateSound", STR_00889F64, bufB, 0x80); ActivateSound = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x83A6CC
        sound = DeactivateSound; index = ini->ReadString(ID.Data, "DeactivateSound", STR_00889F64, bufB, 0x80); DeactivateSound = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x83A744
        sound = MindClearedSound; index = ini->ReadString(ID.Data, "MindClearedSound", STR_00889F64, bufB, 0x80); MindClearedSound = index && (index = VocClass::FindIndex(bufB)) != -1 ? index : sound;
        // STRING: GAMEMD 0x81DA00
        Explosion = ReadAnimTypeList(ini, ID.Data, "Explosion", Explosion, bufB);
        // STRING: GAMEMD 0x843FF0
        DestroyAnim = ReadAnimTypeList(ini, ID.Data, "DestroyAnim", DestroyAnim, bufB);
        // STRING: GAMEMD 0x843FD8
        { ParticleSystemTypeClass* t = NaturalParticleSystem; NaturalParticleSystem = ini->ReadString(ID.Data, "NaturalParticleSystem", STR_00889F64, bufB, 0x80) ? ParticleSystemType_FindPtr(bufB) : t; }
        // STRING: GAMEMD 0x843FBC
        { ParticleSystemTypeClass* t = RefinerySmokeParticleSystem; RefinerySmokeParticleSystem = ini->ReadString(ID.Data, "RefinerySmokeParticleSystem", STR_00889F64, bufB, 0x80) ? ParticleSystemType_FindPtr(bufB) : t; }
        // STRING: GAMEMD 0x843FA4
        NaturalParticleSystemLocation = static_cast<TechnoTypeIniView*>(ini)->ReadIntTriple(ID.Data, "NaturalParticleLocation", NaturalParticleSystemLocation);
        // STRING: GAMEMD 0x843F8C
        DamageParticleSystems = ReadParticleSystemTypeList(ini, ID.Data, "DamageParticleSystems", DamageParticleSystems, bufB);
        // STRING: GAMEMD 0x843F74
        DestroyParticleSystems = ReadParticleSystemTypeList(ini, ID.Data, "DestroyParticleSystems", DestroyParticleSystems, bufB);
        // STRING: GAMEMD 0x843F60
        DamageSmokeOffset = static_cast<TechnoTypeIniView*>(ini)->ReadIntTriple(ID.Data, "DamageSmokeOffset", DamageSmokeOffset);
        // STRING: GAMEMD 0x843F4C
        DamSmkOffScrnRel = ini->ReadBool(ID.Data, "DamSmkOffScrnRel", DamSmkOffScrnRel);
        // STRING: GAMEMD 0x843F38
        DestroySmokeOffset = static_cast<TechnoTypeIniView*>(ini)->ReadIntTriple(ID.Data, "DestroySmokeOffset", DestroySmokeOffset);
        // STRING: GAMEMD 0x843F20
        RefinerySmokeOffsetOne = static_cast<TechnoTypeIniView*>(ini)->ReadIntTriple(ID.Data, "RefinerySmokeOffsetOne", RefinerySmokeOffsetOne);
        // STRING: GAMEMD 0x843F08
        RefinerySmokeOffsetTwo = static_cast<TechnoTypeIniView*>(ini)->ReadIntTriple(ID.Data, "RefinerySmokeOffsetTwo", RefinerySmokeOffsetTwo);
        // STRING: GAMEMD 0x843EEC
        RefinerySmokeOffsetThree = static_cast<TechnoTypeIniView*>(ini)->ReadIntTriple(ID.Data, "RefinerySmokeOffsetThree", RefinerySmokeOffsetThree);
        // STRING: GAMEMD 0x843ED4
        RefinerySmokeOffsetFour = static_cast<TechnoTypeIniView*>(ini)->ReadIntTriple(ID.Data, "RefinerySmokeOffsetFour", RefinerySmokeOffsetFour);
        // STRING: GAMEMD 0x843ECC
        Nominal = ini->ReadBool(ID.Data, "Nominal", Nominal);
        // STRING: GAMEMD 0x843EC0
        DontScore = ini->ReadBool(ID.Data, "DontScore", DontScore);
        // STRING: GAMEMD 0x843EB4
        DamageSelf = ini->ReadBool(ID.Data, "DamageSelf", DamageSelf);
        // STRING: GAMEMD 0x843EA8
        Cloakable = ini->ReadBool(ID.Data, "Cloakable", Cloakable);
        // STRING: GAMEMD 0x843E98
        GapGenerator = ini->ReadBool(ID.Data, "GapGenerator", GapGenerator);
        // STRING: GAMEMD 0x843E84
        GapRadiusInCells = ini->ReadInteger(ID.Data, "GapRadiusInCells", GapRadiusInCells);
        // STRING: GAMEMD 0x843E6C
        SuperGapRadiusInCells = ini->ReadInteger(ID.Data, "SuperGapRadiusInCells", SuperGapRadiusInCells);
        // STRING: GAMEMD 0x843E60
        Teleporter = ini->ReadBool(ID.Data, "Teleporter", Teleporter);
        // STRING: GAMEMD 0x843E58
        Sensors = ini->ReadBool(ID.Data, "Sensors", Sensors);
        // STRING: GAMEMD 0x843E4C
        IsGattling = ini->ReadBool(ID.Data, "IsGattling", IsGattling);
        // STRING: GAMEMD 0x843E3C
        WeaponStages = ini->ReadInteger(ID.Data, "WeaponStages", WeaponStages);
        // STRING: GAMEMD 0x843E34
        RateUp = ini->ReadInteger(ID.Data, "RateUp", RateUp);
        // STRING: GAMEMD 0x843E28
        RateDown = ini->ReadInteger(ID.Data, "RateDown", RateDown);
        if (IsGattling && WeaponStages > 1)
        {
            for (int i = 0; i < WeaponStages; i++)
            {
                char stageKey[16];
                char eliteStageKey[16];
                // STRING: GAMEMD 0x843E20
                sprintf(stageKey, "Stage%d", i + 1);
                // STRING: GAMEMD 0x843E10
                sprintf(eliteStageKey, "EliteStage%d", i + 1);
                WeaponStage[i] = ini->ReadInteger(ID.Data, stageKey, WeaponStage[i]);
                EliteStage[i] = ini->ReadInteger(ID.Data, eliteStageKey, EliteStage[i]);
            }
        }
        // STRING: GAMEMD 0x843E04
        PipScale = static_cast<TechnoTypeIniView*>(ini)->ReadPipScale(ID.Data, "PipScale", PipScale);
        // STRING: GAMEMD 0x843DF4
        PipsDrawForAll = ini->ReadBool(ID.Data, "PipsDrawForAll", PipsDrawForAll);
        // STRING: GAMEMD 0x843DDC
        LeptonMindControlOffset = ini->ReadInteger(ID.Data, "LeptonMindControlOffset", LeptonMindControlOffset);
        // STRING: GAMEMD 0x843DC0
        PixelSelectionBracketDelta = ini->ReadInteger(ID.Data, "PixelSelectionBracketDelta", PixelSelectionBracketDelta);
        // STRING: GAMEMD 0x843DB8
        PipWrap = ini->ReadInteger(ID.Data, "PipWrap", PipWrap);
        // STRING: GAMEMD 0x843DA8
        Prerequisite = FUN_004770E0(ini, NameOf(ID.Data), "Prerequisite", Prerequisite);
        // STRING: GAMEMD 0x843D90
        PrerequisiteOverride = FUN_004770E0FromBuilt(ini, NameOf(ID.Data), "PrerequisiteOverride", TypeListInt(reinterpret_cast<const TypeListInt&>(PrerequisiteOverride), 0));
        // STRING: GAMEMD 0x843D88
        Sight = ini->ReadInteger(ID.Data, "Sight", Sight);
        // STRING: GAMEMD 0x843D74
        ReselectIfLimboed = ini->ReadBool(ID.Data, "ReselectIfLimboed", ReselectIfLimboed);
        // STRING: GAMEMD 0x843D60
        RejoinTeamIfLimboed = ini->ReadBool(ID.Data, "RejoinTeamIfLimboed", RejoinTeamIfLimboed);
        // STRING: GAMEMD 0x843D50
        SensorsSight = ini->ReadInteger(ID.Data, "SensorsSight", SensorsSight);
        // STRING: GAMEMD 0x843D3C
        DetectDisguiseRange = ini->ReadInteger(ID.Data, "DetectDisguiseRange", DetectDisguiseRange);
        // STRING: GAMEMD 0x843D30
        BombSight = ini->ReadInteger(ID.Data, "BombSight", BombSight);
        // STRING: GAMEMD 0x843D1C
        LeadershipRating = ini->ReadInteger(ID.Data, "LeadershipRating", LeadershipRating);
        // STRING: GAMEMD 0x843D04
        MindControlRingOffset = ini->ReadInteger(ID.Data, "MindControlRingOffset", MindControlRingOffset);
        // STRING: GAMEMD 0x843CF0
        BuildTimeMultiplier = ini->ReadDouble(ID.Data, "BuildTimeMultiplier", BuildTimeMultiplier);
        // STRING: GAMEMD 0x843CE4
        RevealToAll = ini->ReadBool(ID.Data, "RevealToAll", RevealToAll);
        // STRING: GAMEMD 0x843CD8
        Drainable = ini->ReadBool(ID.Data, "Drainable", Drainable);
        // STRING: GAMEMD 0x843CCC
        OpenTopped = ini->ReadBool(ID.Data, "OpenTopped", OpenTopped);
        // STRING: GAMEMD 0x843CB8
        ResourceGatherer = ini->ReadBool(ID.Data, "ResourceGatherer", ResourceGatherer);
        // STRING: GAMEMD 0x843CA4
        ResourceDestination = ini->ReadBool(ID.Data, "ResourceDestination", ResourceDestination);
        // STRING: GAMEMD 0x843C98
        CanDisguise = ini->ReadBool(ID.Data, "CanDisguise", CanDisguise);
        // STRING: GAMEMD 0x843C88
        PermaDisguise = ini->ReadBool(ID.Data, "PermaDisguise", PermaDisguise);
        // STRING: GAMEMD 0x843C78
        DetectDisguise = ini->ReadBool(ID.Data, "DetectDisguise", DetectDisguise);
        // STRING: GAMEMD 0x843C64
        DisguiseWhenStill = ini->ReadBool(ID.Data, "DisguiseWhenStill", DisguiseWhenStill);
        // STRING: GAMEMD 0x843C50
        CanPassiveAquire = ini->ReadBool(ID.Data, "CanPassiveAquire", CanPassiveAquire);
        // STRING: GAMEMD 0x843C40
        CanRetaliate = ini->ReadBool(ID.Data, "CanRetaliate", CanRetaliate);
        // STRING: GAMEMD 0x843C2C
        CanApproachTarget = ini->ReadBool(ID.Data, "CanApproachTarget", CanApproachTarget);
        // STRING: GAMEMD 0x843C14
        CanRecalcApproachTarget = ini->ReadBool(ID.Data, "CanRecalcApproachTarget", CanRecalcApproachTarget);
        // STRING: GAMEMD 0x843BFC
        RequiresStolenThirdTech = ini->ReadBool(ID.Data, "RequiresStolenThirdTech", RequiresStolenThirdTech);
        // STRING: GAMEMD 0x843BE0
        RequiresStolenSovietTech = ini->ReadBool(ID.Data, "RequiresStolenSovietTech", RequiresStolenSovietTech);
        // STRING: GAMEMD 0x843BC4
        RequiresStolenAlliedTech = ini->ReadBool(ID.Data, "RequiresStolenAlliedTech", RequiresStolenAlliedTech);
        // STRING: GAMEMD 0x843BB4
        RequiredHouses = static_cast<TechnoTypeIniView*>(ini)->ReadHouseTypesList(ID.Data, "RequiredHouses", RequiredHouses);
        // STRING: GAMEMD 0x843BA4
        SecretHouses = static_cast<TechnoTypeIniView*>(ini)->ReadHouseTypesList(ID.Data, "SecretHouses", SecretHouses);
        // STRING: GAMEMD 0x843B94
        ForbiddenHouses = static_cast<TechnoTypeIniView*>(ini)->ReadHouseTypesList(ID.Data, "ForbiddenHouses", ForbiddenHouses);
        // STRING: GAMEMD 0x824E40
        TechLevel = ini->ReadInteger(ID.Data, "TechLevel", TechLevel);
        // STRING: GAMEMD 0x843B84
        AirstrikeTeam = ini->ReadInteger(ID.Data, "AirstrikeTeam", AirstrikeTeam);
        // STRING: GAMEMD 0x843B70
        EliteAirstrikeTeam = ini->ReadInteger(ID.Data, "EliteAirstrikeTeam", AirstrikeTeam);
        {
            AircraftTypeClass* team = AirstrikeTeamType;
            // STRING: GAMEMD 0x843B5C
            if (ini->ReadString(ID.Data, "AirstrikeTeamType", STR_00889F64, bufB, 0x80))
                team = AircraftType_FindPtr(bufB);
            AirstrikeTeamType = team;
            // STRING: GAMEMD 0x843B44
            EliteAirstrikeTeamType = ini->ReadString(ID.Data, "EliteAirstrikeTeamType", STR_00889F64, bufB, 0x80) ? AircraftType_FindPtr(bufB) : team;
        }
        // STRING: GAMEMD 0x843B2C
        AirstrikeRechargeTime = ini->ReadInteger(ID.Data, "AirstrikeRechargeTime", AirstrikeRechargeTime);
        // STRING: GAMEMD 0x843B10
        EliteAirstrikeRechargeTime = ini->ReadInteger(ID.Data, "EliteAirstrikeRechargeTime", AirstrikeRechargeTime);
        {
            // STRING: GAMEMD 0x81D9CC
            int percent = ini->ReadInteger(ID.Data, "Speed", -1);
            if (percent != -1)
            {
                if (percent >= 100)
                    percent = 100;
                int speed = ((percent > 0 ? percent : 0) << 8) / 100;
                if (speed >= 255)
                    speed = 255;
                Speed = speed;
            }
        }
        // STRING: GAMEMD 0x825470
        Cost = ini->ReadInteger(ID.Data, "Cost", Cost);
        // STRING: GAMEMD 0x843B08
        Soylent = ini->ReadInteger(ID.Data, "Soylent", Soylent);
        // STRING: GAMEMD 0x843AF8
        { UnitTypeClass* t = UnloadingClass; UnloadingClass = ini->ReadString(ID.Data, "UnloadingClass", STR_00889F64, bufB, 0x80) ? UnitType_FindPtr(bufB) : t; }
        // STRING: GAMEMD 0x819490
        { AnimTypeClass* t = DeployingAnim; DeployingAnim = ini->ReadString(ID.Data, "DeployingAnim", STR_00889F64, bufB, 0x80) ? AnimType_FindPtr(bufB) : t; }
        // STRING: GAMEMD 0x843AEC
        InitialAmmo = ini->ReadInteger(ID.Data, "InitialAmmo", InitialAmmo);
        // STRING: GAMEMD 0x81BBE0
        Ammo = ini->ReadInteger(ID.Data, "Ammo", Ammo);
        // STRING: GAMEMD 0x843AE4
        IFVMode = ini->ReadInteger(ID.Data, "IFVMode", IFVMode);
        // STRING: GAMEMD 0x843AD4
        AirRangeBonus = ini->ReadFraction(ID.Data, "AirRangeBonus", AirRangeBonus);
        // STRING: GAMEMD 0x843AC0
        RadialFireSegments = ini->ReadInteger(ID.Data, "RadialFireSegments", RadialFireSegments);
        // STRING: GAMEMD 0x843AAC
        DeployFireWeapon = ini->ReadInteger(ID.Data, "DeployFireWeapon", DeployFireWeapon);
        // STRING: GAMEMD 0x843AA0
        DeployFire = ini->ReadBool(ID.Data, "DeployFire", DeployFire);
        // STRING: GAMEMD 0x843A90
        DeployToLand = ini->ReadBool(ID.Data, "DeployToLand", DeployToLand);
        // STRING: GAMEMD 0x843A84
        MobileFire = ini->ReadBool(ID.Data, "MobileFire", MobileFire);
        // STRING: GAMEMD 0x843A74
        OpportunityFire = ini->ReadBool(ID.Data, "OpportunityFire", OpportunityFire);
        // STRING: GAMEMD 0x843A64
        DistributedFire = ini->ReadBool(ID.Data, "DistributedFire", DistributedFire);
        // STRING: GAMEMD 0x843A5C
        Reload = ini->ReadInteger(ID.Data, "Reload", Reload);
        // STRING: GAMEMD 0x843A50
        EmptyReload = ini->ReadInteger(ID.Data, "EmptyReload", EmptyReload);
        // STRING: GAMEMD 0x843A40
        ReloadIncrement = ini->ReadInteger(ID.Data, "ReloadIncrement", ReloadIncrement);
        // STRING: GAMEMD 0x843A28
        DamageReducesReadiness = ini->ReadBool(ID.Data, "DamageReducesReadiness", DamageReducesReadiness);
        // STRING: GAMEMD 0x843A08
        ReadinessReductionMultiplier = ini->ReadDouble(ID.Data, "ReadinessReductionMultiplier", ReadinessReductionMultiplier);
        // STRING: GAMEMD 0x8439F8
        BerserkFriendly = ini->ReadBool(ID.Data, "BerserkFriendly", BerserkFriendly);
        // STRING: GAMEMD 0x8439EC
        SprayAttack = ini->ReadBool(ID.Data, "SprayAttack", SprayAttack);
        // STRING: GAMEMD 0x8439E4
        Pushy = ini->ReadBool(ID.Data, "Pushy", Pushy);
        // STRING: GAMEMD 0x8439DC
        Natural = ini->ReadBool(ID.Data, "Natural", Natural);
        // STRING: GAMEMD 0x8439D0
        Unnatural = ini->ReadBool(ID.Data, "Unnatural", Unnatural);
        // STRING: GAMEMD 0x8439C4
        CloseRange = ini->ReadBool(ID.Data, "CloseRange", CloseRange);
        // STRING: GAMEMD 0x8439B0
        PreventAttackMove = ini->ReadBool(ID.Data, "PreventAttackMove", PreventAttackMove);
        // STRING: GAMEMD 0x8439A8
        Points = Points2 = ini->ReadInteger(ID.Data, "Points", Points2);
        // STRING: GAMEMD 0x84399C
        ThreatPosed = ini->ReadInteger(ID.Data, "ThreatPosed", ThreatPosed);
        // STRING: GAMEMD 0x843994
        OwnerFlags = static_cast<TechnoTypeIniView*>(ini)->ReadHouseTypesList(ID.Data, "Owner", OwnerFlags);
        // STRING: GAMEMD 0x843980
        AIBasePlanningSide = ini->ReadInteger(ID.Data, "AIBasePlanningSide", AIBasePlanningSide);
        // STRING: GAMEMD 0x843974
        Trainable = ini->ReadBool(ID.Data, "Trainable", Trainable);
        // STRING: GAMEMD 0x84396C
        Crewed = ini->ReadBool(ID.Data, "Crewed", Crewed);
        // STRING: GAMEMD 0x843964
        Gunner = ini->ReadBool(ID.Data, "Gunner", Gunner);
        // STRING: GAMEMD 0x84395C
        Naval = ini->ReadBool(ID.Data, "Naval", Naval);
        // STRING: GAMEMD 0x843950
        Repairable = ini->ReadBool(ID.Data, "Repairable", Repairable);
        // STRING: GAMEMD 0x843944
        Invisible = ini->ReadBool(ID.Data, "Invisible", Invisible);
        // STRING: GAMEMD 0x843934
        RadarVisible = ini->ReadBool(NameOf(ID.Data), "RadarVisible", RadarVisible);
        // STRING: GAMEMD 0x843928
        SelfHealing = ini->ReadBool(NameOf(ID.Data), "SelfHealing", SelfHealing);
        // STRING: GAMEMD 0x84391C
        NoAutoFire = ini->ReadBool(NameOf(ID.Data), "NoAutoFire", NoAutoFire);
        // STRING: GAMEMD 0x81B164
        ROT = ini->ReadInteger(NameOf(ID.Data), "ROT", ROT);
        // STRING: GAMEMD 0x81BBD4
        Passengers = ini->ReadInteger(NameOf(ID.Data), "Passengers", Passengers);
        // STRING: GAMEMD 0x843910
        FireAngle = ini->ReadInteger(NameOf(ID.Data), "FireAngle", FireAngle);
        // STRING: GAMEMD 0x843904
        DeployTime = ini->ReadDouble(NameOf(ID.Data), "DeployTime", DeployTime);
        // STRING: GAMEMD 0x8438F4
        UndeployDelay = ini->ReadInteger(NameOf(ID.Data), "UndeployDelay", UndeployDelay);
        // STRING: GAMEMD 0x8438E8
        Disableable = ini->ReadBool(NameOf(ID.Data), "Disableable", Disableable);
        // STRING: GAMEMD 0x8438DC
        ToProtect = ini->ReadBool(NameOf(ID.Data), "ToProtect", ToProtect);
        // STRING: GAMEMD 0x83CC74
        TiberiumHeal = ini->ReadBool(NameOf(ID.Data), "TiberiumHeal", TiberiumHeal);
        // STRING: GAMEMD 0x8438CC
        ImmuneToVeins = ini->ReadBool(NameOf(ID.Data), "ImmuneToVeins", ImmuneToVeins);
        // STRING: GAMEMD 0x8438B0
        AllowedToStartInMultiplayer = ini->ReadBool(NameOf(ID.Data), "AllowedToStartInMultiplayer", AllowedToStartInMultiplayer);
        // STRING: GAMEMD 0x8438A4
        StupidHunt = ini->ReadBool(NameOf(ID.Data), "StupidHunt", StupidHunt);
        // STRING: GAMEMD 0x843898
        TargetLaser = ini->ReadBool(NameOf(ID.Data), "TargetLaser", TargetLaser);
        // STRING: GAMEMD 0x843888
        HunterSeeker = ini->ReadBool(NameOf(ID.Data), "HunterSeeker", HunterSeeker);
        // STRING: GAMEMD 0x81BB58
        Crusher = ini->ReadBool(NameOf(ID.Data), "Crusher", Crusher);
        // STRING: GAMEMD 0x84387C
        OmniCrusher = ini->ReadBool(NameOf(ID.Data), "OmniCrusher", OmniCrusher);
        // STRING: GAMEMD 0x843868
        OmniCrushResistant = ini->ReadBool(NameOf(ID.Data), "OmniCrushResistant", OmniCrushResistant);
        // STRING: GAMEMD 0x83D4D8
        AutoCrush = ini->ReadBool(NameOf(ID.Data), "AutoCrush", AutoCrush);
        // STRING: GAMEMD 0x843854
        ImmuneToRadiation = ini->ReadBool(NameOf(ID.Data), "ImmuneToRadiation", ImmuneToRadiation);
        // STRING: GAMEMD 0x843848
        Underwater = ini->ReadBool(NameOf(ID.Data), "Underwater", Underwater);
        // STRING: GAMEMD 0x843838
        BalloonHover = ini->ReadBool(NameOf(ID.Data), "BalloonHover", BalloonHover);
        // STRING: GAMEMD 0x843830
        Slaved = ini->ReadBool(NameOf(ID.Data), "Slaved", Slaved);
        // STRING: GAMEMD 0x843824
        Enslaves = static_cast<TechnoTypeIniView*>(ini)->ReadInfantryType(NameOf(ID.Data), "Enslaves", Enslaves);
        // STRING: GAMEMD 0x843814
        SlaveRegenRate = ini->ReadInteger(NameOf(ID.Data), "SlaveRegenRate", SlaveRegenRate);
        // STRING: GAMEMD 0x843804
        SlavesNumber = ini->ReadInteger(NameOf(ID.Data), "SlavesNumber", SlavesNumber);
        // STRING: GAMEMD 0x8437F4
        SlaveReloadRate = ini->ReadInteger(NameOf(ID.Data), "SlaveReloadRate", SlaveReloadRate);
        // STRING: GAMEMD 0x8437E0
        OpenTransportWeapon = ini->ReadInteger(NameOf(ID.Data), "OpenTransportWeapon", OpenTransportWeapon);
        // STRING: GAMEMD 0x8437D8
        Spawned = ini->ReadBool(NameOf(ID.Data), "Spawned", Spawned);
        // STRING: GAMEMD 0x8184C8
        Spawns = static_cast<TechnoTypeIniView*>(ini)->ReadAircraftType(NameOf(ID.Data), "Spawns", Spawns);
        // STRING: GAMEMD 0x8437C8
        SpawnRegenRate = ini->ReadInteger(NameOf(ID.Data), "SpawnRegenRate", SpawnRegenRate);
        // STRING: GAMEMD 0x8437B8
        SpawnsNumber = ini->ReadInteger(NameOf(ID.Data), "SpawnsNumber", SpawnsNumber);
        // STRING: GAMEMD 0x8437A8
        SpawnReloadRate = ini->ReadInteger(NameOf(ID.Data), "SpawnReloadRate", SpawnReloadRate);
        // STRING: GAMEMD 0x843798
        MissileSpawn = ini->ReadBool(NameOf(ID.Data), "MissileSpawn", MissileSpawn);
        // STRING: GAMEMD 0x843784
        DefaultToGuardArea = ini->ReadBool(NameOf(ID.Data), "DefaultToGuardArea", DefaultToGuardArea);
        // STRING: GAMEMD 0x843778
        Warpable = ini->ReadBool(NameOf(ID.Data), "Warpable", Warpable);
        // STRING: GAMEMD 0x843768
        Parasiteable = ini->ReadBool(NameOf(ID.Data), "Parasiteable", Parasiteable);
        // STRING: GAMEMD 0x843754
        ImmuneToPsionics = ini->ReadBool(NameOf(ID.Data), "ImmuneToPsionics", ImmuneToPsionics);
        // STRING: GAMEMD 0x84373C
        ImmuneToPsionicWeapons = ini->ReadBool(NameOf(ID.Data), "ImmuneToPsionicWeapons", ImmuneToPsionicWeapons);
        // STRING: GAMEMD 0x843728
        ConsideredAircraft = ini->ReadBool(NameOf(ID.Data), "ConsideredAircraft", ConsideredAircraft);
        // STRING: GAMEMD 0x84371C
        Bunkerable = ini->ReadBool(NameOf(ID.Data), "Bunkerable", Bunkerable);
        // STRING: GAMEMD 0x843714
        Organic = ini->ReadBool(NameOf(ID.Data), "Organic", Organic);
        // STRING: GAMEMD 0x843704
        ImmuneToPoison = ini->ReadBool(NameOf(ID.Data), "ImmuneToPoison", ImmuneToPoison);
        // STRING: GAMEMD 0x8436EC
        SuppressionThreshold = ini->ReadInteger(NameOf(ID.Data), "SuppressionThreshold", SuppressionThreshold);
        // STRING: GAMEMD 0x8436E0
        NoShadow = ini->ReadBool(NameOf(ID.Data), "NoShadow", NoShadow);
        // STRING: GAMEMD 0x8436D0
        JumpjetTurnRate = ini->ReadInteger(NameOf(ID.Data), "JumpjetTurnRate", JumpjetTurnRate);
        // STRING: GAMEMD 0x8436C0
        JumpjetSpeed = ini->ReadInteger(NameOf(ID.Data), "JumpjetSpeed", JumpjetSpeed);
        // STRING: GAMEMD 0x8436B0
        JumpjetClimb = ini->ReadDouble(NameOf(ID.Data), "JumpjetClimb", JumpjetClimb);
        // STRING: GAMEMD 0x8436A0
        JumpjetCrash = ini->ReadDouble(NameOf(ID.Data), "JumpjetCrash", JumpjetCrash);
        // STRING: GAMEMD 0x843690
        JumpjetHeight = ini->ReadInteger(NameOf(ID.Data), "JumpjetHeight", JumpjetHeight);
        // STRING: GAMEMD 0x843680
        JumpjetAccel = ini->ReadDouble(NameOf(ID.Data), "JumpjetAccel", JumpjetAccel);
        // STRING: GAMEMD 0x843670
        JumpjetWobbles = ini->ReadDouble(NameOf(ID.Data), "JumpjetWobbles", JumpjetWobbles);
        // STRING: GAMEMD 0x84365C
        JumpjetNoWobbles = ini->ReadBool(NameOf(ID.Data), "JumpjetNoWobbles", JumpjetNoWobbles);
        // STRING: GAMEMD 0x843648
        JumpjetDeviation = ini->ReadInteger(NameOf(ID.Data), "JumpjetDeviation", JumpjetDeviation);
        // STRING: GAMEMD 0x843640
        JumpJet = ini->ReadBool(NameOf(ID.Data), "JumpJet", JumpJet);
        // STRING: GAMEMD 0x843634
        Crashable = ini->ReadBool(NameOf(ID.Data), "Crashable", Crashable);
        // STRING: GAMEMD 0x843620
        AttackFriendlies = ini->ReadBool(NameOf(ID.Data), "AttackFriendlies", AttackFriendlies);
        // STRING: GAMEMD 0x843604
        AttackCursorOnFriendlies = ini->ReadBool(NameOf(ID.Data), "AttackCursorOnFriendlies", AttackCursorOnFriendlies);
        // STRING: GAMEMD 0x8435F4
        TurretRecoil = ini->ReadBool(NameOf(ID.Data), "TurretRecoil", TurretRecoil);
        {
            TurretAnimBlock* turret = (TurretAnimBlock*)&TurretAnimData;
            // STRING: GAMEMD 0x8435E4
            turret->SetHead(ini->ReadInteger(NameOf(ID.Data), "TurretTravel", turret->GetHead()));
            // STRING: GAMEMD 0x8435CC
            turret->SetSize(ini->ReadInteger(NameOf(ID.Data), "TurretCompressFrames", turret->GetSize()));
            // STRING: GAMEMD 0x8435B8
            turret->SetExtra(ini->ReadInteger(NameOf(ID.Data), "TurretHoldFrames", turret->GetExtra()));
            // STRING: GAMEMD 0x8435A4
            turret->SetTail(ini->ReadInteger(NameOf(ID.Data), "TurretRecoverFrames", turret->GetTail()));
            *(TurretAnimBlock*)&BarrelAnimData = *turret;
            TurretAnimBlock* barrel = (TurretAnimBlock*)&BarrelAnimData;
            // STRING: GAMEMD 0x843594
            barrel->SetHead(ini->ReadInteger(NameOf(ID.Data), "BarrelTravel", turret->GetHead()));
            // STRING: GAMEMD 0x84357C
            barrel->SetSize(ini->ReadInteger(NameOf(ID.Data), "BarrelCompressFrames", turret->GetSize()));
            // STRING: GAMEMD 0x843568
            barrel->SetExtra(ini->ReadInteger(NameOf(ID.Data), "BarrelHoldFrames", turret->GetExtra()));
            // STRING: GAMEMD 0x843554
            barrel->SetTail(ini->ReadInteger(NameOf(ID.Data), "BarrelRecoverFrames", turret->GetTail()));
        }
        // STRING: GAMEMD 0x843540
        TiltsWhenCrushes = ini->ReadBool(NameOf(ID.Data), "TiltsWhenCrushes", TiltsWhenCrushes);
        // STRING: GAMEMD 0x843534
        Accelerates = ini->ReadBool(NameOf(ID.Data), "Accelerates", Accelerates);
        // STRING: GAMEMD 0x843528
        ZFudgeCliff = ini->ReadInteger(NameOf(ID.Data), "ZFudgeCliff", ZFudgeCliff);
        // STRING: GAMEMD 0x843518
        ZFudgeColumn = ini->ReadInteger(NameOf(ID.Data), "ZFudgeColumn", ZFudgeColumn);
        // STRING: GAMEMD 0x843508
        ZFudgeTunnel = ini->ReadInteger(NameOf(ID.Data), "ZFudgeTunnel", ZFudgeTunnel);
        // STRING: GAMEMD 0x8434F8
        ZFudgeBridge = ini->ReadInteger(NameOf(ID.Data), "ZFudgeBridge", ZFudgeBridge);
        {
            AbilitiesStruct veteranResult;
            AbilitiesStruct veteranRead;
            // STRING: GAMEMD 0x8434E4
            static_cast<AbilitiesView&>(VeteranAbilities).AssignRaw(&veteranResult, static_cast<TechnoTypeIniView*>(ini)->ReadAbilitiesRaw(&veteranRead, NameOf(ID.Data), "VeteranAbilities", &VeteranAbilities));
            FUN_007179C0(&veteranResult);
            FUN_007179C0(&veteranRead);
        }
        {
            AbilitiesStruct eliteResult;
            AbilitiesStruct eliteRead;
            // STRING: GAMEMD 0x8434D4
            static_cast<AbilitiesView&>(EliteAbilities).AssignRaw(&eliteResult, static_cast<TechnoTypeIniView*>(ini)->ReadAbilitiesRaw(&eliteRead, NameOf(ID.Data), "EliteAbilities", &EliteAbilities));
            FUN_007179C0(&eliteResult);
            FUN_007179C0(&eliteRead);
        }
        coefficient = MyEffectivenessCoefficient == 0.0 ? RulesInstance->MyEffectivenessCoefficientDefault : MyEffectivenessCoefficient;
        // STRING: GAMEMD 0x8434B8
        MyEffectivenessCoefficient = ini->ReadDouble(NameOf(ID.Data), "MyEffectivenessCoefficient", coefficient);
        coefficient = TargetEffectivenessCoefficient == 0.0 ? RulesInstance->TargetEffectivenessCoefficientDefault : TargetEffectivenessCoefficient;
        // STRING: GAMEMD 0x843498
        TargetEffectivenessCoefficient = ini->ReadDouble(NameOf(ID.Data), "TargetEffectivenessCoefficient", coefficient);
        coefficient = TargetSpecialThreatCoefficient == 0.0 ? RulesInstance->TargetSpecialThreatCoefficientDefault : TargetSpecialThreatCoefficient;
        // STRING: GAMEMD 0x843478
        TargetSpecialThreatCoefficient = ini->ReadDouble(NameOf(ID.Data), "TargetSpecialThreatCoefficient", coefficient);
        coefficient = TargetStrengthCoefficient == 0.0 ? RulesInstance->TargetStrengthCoefficientDefault : TargetStrengthCoefficient;
        // STRING: GAMEMD 0x84345C
        TargetStrengthCoefficient = ini->ReadDouble(NameOf(ID.Data), "TargetStrengthCoefficient", coefficient);
        coefficient = TargetDistanceCoefficient == 0.0 ? RulesInstance->TargetDistanceCoefficientDefault : TargetDistanceCoefficient;
        // STRING: GAMEMD 0x843440
        TargetDistanceCoefficient = ini->ReadDouble(NameOf(ID.Data), "TargetDistanceCoefficient", coefficient);
        // STRING: GAMEMD 0x84342C
        SpecialThreatValue = ini->ReadDouble(NameOf(ID.Data), "SpecialThreatValue", SpecialThreatValue);
        // STRING: GAMEMD 0x843414
        IsSelectableCombatant = ini->ReadBool(NameOf(ID.Data), "IsSelectableCombatant", IsSelectableCombatant);
        // STRING: GAMEMD 0x843408
        UseBuffer = DAT_00887180.ReadBool(NameOf(ID.Data), "UseBuffer", UseBuffer);
        unknown_C9C = false;
        if (Weapon[0].WeaponType != 0 && Weapon[0].WeaponType->Damage > 0)
            unknown_C9C = true;
        // STRING: GAMEMD 0x81834C
        _makepath(path, 0, 0, NameOf(ImageFile.Data), ".SHP");
        if (ImageAllocated && Image != 0)
        {
            ::operator delete(Image);
            Image = 0;
            ImageAllocated = false;
        }
        if (vf_11() != 7)
            Image = MapObjLoadShape(path, false);
        // STRING: GAMEMD 0x824254
        DAT_00887180.ReadString(NameOf(ImageFile.Data), "Palette", STR_00889F64, PaletteFile, 0x20);
        FUN_00717820();
        if (FUN_00626DA0() > 1)
        {
            FUN_004068E0("You have violated the limit of having only one extra building palette.\n");
            FUN_006BEC50(-1);
        }
        // STRING: GAMEMD 0x8433B0
        TurretOffset = DAT_00887180.ReadInteger(NameOf(ImageFile.Data), "TurretOffset", TurretOffset);
        // STRING: GAMEMD 0x8433A4
        RotCount = DAT_00887180.ReadInteger(NameOf(ImageFile.Data), "RotCount", RotCount);
        // STRING: GAMEMD 0x843398
        Remapable = DAT_00887180.ReadBool(NameOf(ImageFile.Data), "Remapable", Remapable);
        // STRING: GAMEMD 0x818610
        Normalized = DAT_00887180.ReadBool(NameOf(ImageFile.Data), "Normalized", Normalized);
        // STRING: GAMEMD 0x84338C
        VisibleLoad = DAT_00887180.ReadBool(NameOf(ImageFile.Data), "VisibleLoad", VisibleLoad);
        // STRING: GAMEMD 0x843380
        ShadowIndex = DAT_00887180.ReadInteger(NameOf(ImageFile.Data), "ShadowIndex", ShadowIndex);
        // STRING: GAMEMD 0x84336C
        DisableVoxelCache = DAT_00887180.ReadBool(NameOf(ImageFile.Data), "DisableVoxelCache", DisableVoxelCache);
        // STRING: GAMEMD 0x843358
        DisableShadowCache = DAT_00887180.ReadBool(NameOf(ImageFile.Data), "DisableShadowCache", DisableShadowCache);
        // STRING: GAMEMD 0x843350
        DAT_00887180.ReadString(NameOf(ImageFile.Data), "Cameo", STR_00889F64, cameoText, 0x19);
        if (strlen(cameoText) != 0)
        {
            strcpy(NameOfBuf(CameoFile), cameoText);
            // STRING: GAMEMD 0x81834C
            _makepath(path, 0, 0, NameOf(CameoFile), ".SHP");
            if (Cameo == 0)
                Cameo = (SHPStruct*)MapObjLoadShape(path, false);
        }
        if (Cameo == 0)
            // STRING: GAMEMD 0x8204FC
            Cameo = (SHPStruct*)MapObjLoadShape("XXICON.SHP", false);
        // STRING: GAMEMD 0x843344
        DAT_00887180.ReadString(NameOf(ImageFile.Data), "AltCameo", STR_00889F64, cameoText, 0x19);
        if (strlen(cameoText) != 0)
        {
            strcpy(NameOfBuf(AltCameoFile), cameoText);
            // STRING: GAMEMD 0x81834C
            _makepath(path, 0, 0, NameOf(AltCameoFile), ".SHP");
            if (AltCameo == 0)
                AltCameo = (SHPStruct*)MapObjLoadShape(path, false);
        }
        if (FUN_00717880())
        {
            for (int i = 0; i < WeaponCount; i++)
            {
                char weaponKey[16];
                // STRING: GAMEMD 0x844310
                sprintf(weaponKey, "Weapon%d", i + 1);
                // STRING: GAMEMD 0x84333C
                sprintf(bufA, "%sFLH", weaponKey);
                Weapon[i].FLH = static_cast<TechnoTypeIniView&>(DAT_00887180).ReadCoord(NameOf(ImageFile.Data), bufA, Weapon[i].FLH);
                // STRING: GAMEMD 0x84332C
                sprintf(bufA, "%sBarrelLength", weaponKey);
                Weapon[i].BarrelLength = DAT_00887180.ReadInteger(NameOf(ImageFile.Data), bufA, Weapon[i].BarrelLength);
                // STRING: GAMEMD 0x843318
                sprintf(bufA, "%sBarrelThickness", weaponKey);
                Weapon[i].BarrelThickness = DAT_00887180.ReadInteger(NameOf(ImageFile.Data), bufA, Weapon[i].BarrelThickness);
                // STRING: GAMEMD 0x843308
                sprintf(bufA, "%sTurretLocked", weaponKey);
                Weapon[i].TurretLocked = DAT_00887180.ReadBool(NameOf(ImageFile.Data), bufA, Weapon[i].TurretLocked);
                // STRING: GAMEMD 0x844300
                sprintf(weaponKey, "EliteWeapon%d", i + 1);
                // STRING: GAMEMD 0x84333C
                sprintf(bufA, "%sFLH", weaponKey);
                EliteWeapon[i].FLH = static_cast<TechnoTypeIniView&>(DAT_00887180).ReadCoord(NameOf(ImageFile.Data), bufA, Weapon[i].FLH);
                // STRING: GAMEMD 0x84332C
                sprintf(bufA, "%sBarrelLength", weaponKey);
                EliteWeapon[i].BarrelLength = DAT_00887180.ReadInteger(NameOf(ImageFile.Data), bufA, Weapon[i].BarrelLength);
                // STRING: GAMEMD 0x843318
                sprintf(bufA, "%sBarrelThickness", weaponKey);
                EliteWeapon[i].BarrelThickness = DAT_00887180.ReadInteger(NameOf(ImageFile.Data), bufA, Weapon[i].BarrelThickness);
                // STRING: GAMEMD 0x843308
                sprintf(bufA, "%sTurretLocked", weaponKey);
                EliteWeapon[i].TurretLocked = DAT_00887180.ReadBool(NameOf(ImageFile.Data), bufA, Weapon[i].TurretLocked);
            }
        }
        else
        {
            // STRING: GAMEMD 0x8432F8
            Weapon[0].FLH = static_cast<TechnoTypeIniView&>(DAT_00887180).ReadCoord(NameOf(ImageFile.Data), "PrimaryFireFLH", Weapon[0].FLH);
            // STRING: GAMEMD 0x8432E8
            Weapon[0].BarrelLength = DAT_00887180.ReadInteger(NameOf(ImageFile.Data), "PBarrelLength", Weapon[0].BarrelLength);
            // STRING: GAMEMD 0x8432D4
            Weapon[0].BarrelThickness = DAT_00887180.ReadInteger(NameOf(ImageFile.Data), "PBarrelThickness", Weapon[0].BarrelThickness);
            // STRING: GAMEMD 0x8432C0
            Weapon[1].FLH = static_cast<TechnoTypeIniView&>(DAT_00887180).ReadCoord(NameOf(ImageFile.Data), "SecondaryFireFLH", Weapon[1].FLH);
            // STRING: GAMEMD 0x8432B0
            Weapon[1].BarrelLength = DAT_00887180.ReadInteger(NameOf(ImageFile.Data), "SBarrelLength", Weapon[1].BarrelLength);
            // STRING: GAMEMD 0x84329C
            Weapon[1].BarrelThickness = DAT_00887180.ReadInteger(NameOf(ImageFile.Data), "SBarrelThickness", Weapon[1].BarrelThickness);
            // STRING: GAMEMD 0x843288
            EliteWeapon[0].FLH = static_cast<TechnoTypeIniView&>(DAT_00887180).ReadCoord(NameOf(ImageFile.Data), "ElitePrimaryFireFLH", Weapon[0].FLH);
            // STRING: GAMEMD 0x843274
            EliteWeapon[0].BarrelLength = DAT_00887180.ReadInteger(NameOf(ImageFile.Data), "ElitePBarrelLength", Weapon[0].BarrelLength);
            // STRING: GAMEMD 0x84325C
            EliteWeapon[0].BarrelThickness = DAT_00887180.ReadInteger(NameOf(ImageFile.Data), "ElitePBarrelThickness", Weapon[0].BarrelThickness);
            // STRING: GAMEMD 0x843244
            EliteWeapon[1].FLH = static_cast<TechnoTypeIniView&>(DAT_00887180).ReadCoord(NameOf(ImageFile.Data), "EliteSecondaryFireFLH", Weapon[1].FLH);
            // STRING: GAMEMD 0x843230
            EliteWeapon[1].BarrelLength = DAT_00887180.ReadInteger(NameOf(ImageFile.Data), "EliteSBarrelLength", Weapon[1].BarrelLength);
            // STRING: GAMEMD 0x843218
            EliteWeapon[1].BarrelThickness = DAT_00887180.ReadInteger(NameOf(ImageFile.Data), "EliteSBarrelThickness", Weapon[1].BarrelThickness);
        }
        for (int i = 0; i < 5; ++i)
        {
            char weaponKey[16];
            // STRING: GAMEMD 0x843208
            sprintf(weaponKey, "AlternateFLH%d", i);
            AlternativeFLH[i] = static_cast<TechnoTypeIniView&>(DAT_00887180).ReadCoord(NameOf(ImageFile.Data), weaponKey, Weapon[0].FLH);
        }
        // STRING: GAMEMD 0x8431EC
        TurretNotExportedOnGround = DAT_00887180.ReadBool(NameOf(ImageFile.Data), "TurretNotExportedOnGround", TurretNotExportedOnGround);
        // STRING: GAMEMD 0x8431D8
        SecondSpawnOffset = static_cast<TechnoTypeIniView&>(DAT_00887180).ReadCoord(NameOf(ImageFile.Data), "SecondSpawnOffset", SecondSpawnOffset);
        // STRING: GAMEMD 0x8431C8
        MovementZone = static_cast<TechnoTypeIniView*>(ini)->ReadMovementZone(NameOf(ID.Data), "MovementZone", MovementZone);
        unknown_D2C = MovementZone == 6;
        if (Voxel)
            FUN_005F8110();
        else if (Turret)
            FUN_005F8CE0();
        if (MainVoxel.unknown_00 != 0)
        {
            if (((WaypointQueue_00717A30*)MainVoxel.unknown_00)->IsEmpty())
            {
                VoxelScaleX = (float)MainVoxel.unknown_00->FUN_007564b0(0, 0)->unknown_A0[1] * 0.5f + 0.5;
                VoxelScaleY = (float)MainVoxel.unknown_00->FUN_007564b0(0, 0)->unknown_A0[0] * 0.5f;
            }
        }
        return true;
    }
    return false;
}
