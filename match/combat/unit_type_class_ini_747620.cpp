// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   UnitTypeClass::vf_25 (retail 0x747620, 0x88C bytes): the INI reader of the vehicle type.
//   Every key string, destination offset, reader call and default was read off the user's retail
//   gamemd.exe v1.001 disassembly; field names are the INI key strings themselves.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../_layout/unit_type_class.h"
#include "../core/rules_class_ini_support.h"

// GLOBAL: GAMEMD 0x887180 -- the art INI selected by the native immediate receivers.
extern CCINIClass DAT_00887180;
// FUNCTION: GAMEMD 0x5B40B0 (decl; reloc), ECX=path, DL=force.
SHPStruct* __fastcall FUN_005B40B0(char* path, bool force);

// The readers this function uses that CCINIClass itself does not declare (same reader object in retail).
class UnitTypeIniView : public CCINIClass
{
public:
    // FUNCTION: GAMEMD 0x476FC0 (decl; reloc) -- movement speed class by name.
    int ReadSpeedType(const char* section, const char* key, int fallback);
    // FUNCTION: GAMEMD 0x4754B0 (decl; reloc) -- land type by name.
    int ReadLandType(const char* section, const char* key, int fallback);
    // FUNCTION: GAMEMD 0x529CA0 (decl; reloc) -- a coordinate triple; the result comes back through a hidden pointer.
    CoordStruct ReadCoord(const char* section, const char* key, const CoordStruct& fallback);
};

// FUNCTION: GAMEMD 0x747620
// PARTIAL: 99.7% (instruction multiset identical, 659 of 659). One delta: the final `add` of MaxDeathCounter
// sums into EAX where retail sums into ECX (`add ecx,eax` against `add eax,ecx`); operand order, a value
// temporary, a chained assignment and a compound assignment all give the same bytes.
// Reads the vehicle type's rules and art keys: the techno type reader first, then every key over its
// current value, then the frame-layout defaults derived from them.
bool UnitTypeClass::vf_25(CCINIClass* ini)
{
    int i;
    int j;
    int index;
    char previous[0x1C];
    char path[0x104];

    ini->Reset();
    if (TechnoTypeClass::vf_25(ini)) {
        // STRING: GAMEMD 0x845E20
        CrateGoodie = ini->ReadBool(ID.Data, "CrateGoodie", CrateGoodie);
        // STRING: GAMEMD 0x845E10
        DeployToFire = ini->ReadBool(ID.Data, "DeployToFire", DeployToFire);
        // STRING: GAMEMD 0x845DFC
        IsSimpleDeployer = ini->ReadBool(ID.Data, "IsSimpleDeployer", IsSimpleDeployer);
        // STRING: GAMEMD 0x83D4CC
        Harvester = ini->ReadBool(ID.Data, "Harvester", Harvester);
        // STRING: GAMEMD 0x81AC50
        Weeder = ini->ReadBool(ID.Data, "Weeder", Weeder);
        if (SpeedType == -1)
            SpeedType = Crusher ? 1 : 2;
        // STRING: GAMEMD 0x844504
        SpeedType = static_cast<UnitTypeIniView*>(ini)->ReadSpeedType(ID.Data, "SpeedType", SpeedType);
        // STRING: GAMEMD 0x845DF0
        IsTilter = ini->ReadBool(ID.Data, "IsTilter", IsTilter);
        // STRING: GAMEMD 0x845DE0
        CarriesCrate = ini->ReadBool(ID.Data, "CarriesCrate", CarriesCrate);
        HasTurret = Turret == 0;   // retail stores the inverse of the Turret flag here
        // STRING: GAMEMD 0x845DC8
        TooBigToFitUnderBridge = ini->ReadBool(ID.Data, "TooBigToFitUnderBridge", TooBigToFitUnderBridge);
        // STRING: GAMEMD 0x845DB0
        HalfDamageSmokeLocation = static_cast<UnitTypeIniView*>(ini)->ReadCoord(ID.Data, "HalfDamageSmokeLocation", HalfDamageSmokeLocation);
        unknown_int_398 = 15;
        if (Harvester || Weeder)
            unknown_int_398 = 10;
        // STRING: GAMEMD 0x845DA0
        UseTurretShadow = DAT_00887180.ReadBool(ImageFile.Data, "UseTurretShadow", UseTurretShadow);
        // STRING: GAMEMD 0x845D94
        WalkFrames = DAT_00887180.ReadInteger(ImageFile.Data, "WalkFrames", WalkFrames);
        // STRING: GAMEMD 0x845D84
        FiringFrames = DAT_00887180.ReadInteger(ImageFile.Data, "FiringFrames", FiringFrames);
        // STRING: GAMEMD 0x845D7C
        Passive = ini->ReadBool(ID.Data, "Passive", Passive);
        // STRING: GAMEMD 0x845D64
        MovementRestrictedTo = static_cast<UnitTypeIniView*>(ini)->ReadLandType(ID.Data, "MovementRestrictedTo", MovementRestrictedTo);
        // STRING: GAMEMD 0x845D58
        CanBeach = ini->ReadBool(ID.Data, "CanBeach", CanBeach);
        // STRING: GAMEMD 0x83CC84
        SmallVisceroid = ini->ReadBool(ID.Data, "SmallVisceroid", SmallVisceroid);
        // STRING: GAMEMD 0x83CC94
        LargeVisceroid = ini->ReadBool(ID.Data, "LargeVisceroid", LargeVisceroid);
        // STRING: GAMEMD 0x845D4C
        NonVehicle = ini->ReadBool(ID.Data, "NonVehicle", NonVehicle);
        if (FiringFrames > 0)
            StandingFrames = 1;
        // STRING: GAMEMD 0x845D3C
        StandingFrames = DAT_00887180.ReadInteger(ImageFile.Data, "StandingFrames", StandingFrames);
        // STRING: GAMEMD 0x845D30
        DeathFrames = DAT_00887180.ReadInteger(ImageFile.Data, "DeathFrames", DeathFrames);
        // STRING: GAMEMD 0x845D20
        DeathFrameRate = DAT_00887180.ReadInteger(ImageFile.Data, "DeathFrameRate", DeathFrameRate);
        if (DeathFrameRate < 1)
            DeathFrameRate = 1;
        if (FiringFrames == 0 && Turret == 0)
            Facings = 1;
        // STRING: GAMEMD 0x845D18
        Facings = DAT_00887180.ReadInteger(ImageFile.Data, "Facings", Facings);
        if (StartWalkFrame == -1)
            StartWalkFrame = 0;
        if (StartStandFrame == -1)
            StartStandFrame = StandingFrames == 0 ? StartWalkFrame : WalkFrames * Facings;
        if (StartFiringFrame == -1)
            StartFiringFrame = FiringFrames == 0 ? StartStandFrame : (WalkFrames + StandingFrames) * Facings;
        if (StartDeathFrame == -1) {
            StartDeathFrame = DeathFrames == 0 ? -1 : (FiringFrames + 1 + WalkFrames) * Facings;
            MaxDeathCounter = StartDeathFrame + DeathFrames;
        }
        // STRING: GAMEMD 0x845D08
        StartStandFrame = DAT_00887180.ReadInteger(ImageFile.Data, "StartStandFrame", StartStandFrame);
        // STRING: GAMEMD 0x845CF8
        StartWalkFrame = DAT_00887180.ReadInteger(ImageFile.Data, "StartWalkFrame", StartWalkFrame);
        // STRING: GAMEMD 0x845CE4
        StartFiringFrame = DAT_00887180.ReadInteger(ImageFile.Data, "StartFiringFrame", StartFiringFrame);
        // STRING: GAMEMD 0x845CD4
        StartDeathFrame = DAT_00887180.ReadInteger(ImageFile.Data, "StartDeathFrame", StartDeathFrame);
        // STRING: GAMEMD 0x845CC4
        MaxDeathCounter = DAT_00887180.ReadInteger(ImageFile.Data, "MaxDeathCounter", MaxDeathCounter);
        for (i = 0; i < 2; i++) {
            char key[0x14];
            // STRING: GAMEMD 0x845CB0
            sprintf(key, "FiringSyncFrame%d", i);
            FiringSyncFrame[i] = DAT_00887180.ReadInteger(ImageFile.Data, key, FiringSyncFrame[i]);
        }
        for (j = 0; j < 4; j++) {
            char key[0x14];
            // STRING: GAMEMD 0x845CA0
            sprintf(key, "BurstDelay%d", j);
            BurstDelay[j] = ini->ReadInteger(ID.Data, key, BurstDelay[j]);
        }
        {
            strcpy(previous, AltImageFile);
            // STRING: GAMEMD 0x845C94
            ini->ReadString(ID.Data, "AltImage", previous, AltImageFile, 0x19);
            _makepath(path, 0, 0, AltImageFile, ".SHP");
            AltImage = FUN_005B40B0(path, false);
        }
        if (FUN_00410A40("FV")) {
            // STRING: GAMEMD 0x845C80
            index = ini->ReadInteger(ID.Data, "NormalTurretIndex", 0);
            // STRING: GAMEMD 0x845C6C
            FUN_00717890(index, ini->ReadInteger(ID.Data, "NormalTurretWeapon", -1));
            // STRING: GAMEMD 0x845C58
            index = ini->ReadInteger(ID.Data, "RepairTurretIndex", 1);
            // STRING: GAMEMD 0x845C44
            FUN_00717890(index, ini->ReadInteger(ID.Data, "RepairTurretWeapon", -1));
            // STRING: GAMEMD 0x845C2C
            index = ini->ReadInteger(ID.Data, "MachineGunTurretIndex", 2);
            // STRING: GAMEMD 0x845C14
            FUN_00717890(index, ini->ReadInteger(ID.Data, "MachineGunTurretWeapon", -1));
            // STRING: GAMEMD 0x845C04
            index = ini->ReadInteger(ID.Data, "FlakTurretIndex", 3);
            // STRING: GAMEMD 0x845BF0
            FUN_00717890(index, ini->ReadInteger(ID.Data, "FlakTurretWeapon", -1));
            // STRING: GAMEMD 0x845BDC
            index = ini->ReadInteger(ID.Data, "PistolTurretIndex", 0);
            // STRING: GAMEMD 0x845BC8
            FUN_00717890(index, ini->ReadInteger(ID.Data, "PistolTurretWeapon", -1));
            // STRING: GAMEMD 0x845BB4
            index = ini->ReadInteger(ID.Data, "SniperTurretIndex", 0);
            // STRING: GAMEMD 0x845BA0
            FUN_00717890(index, ini->ReadInteger(ID.Data, "SniperTurretWeapon", -1));
            // STRING: GAMEMD 0x845B8C
            index = ini->ReadInteger(ID.Data, "ShockTurretIndex", 0);
            // STRING: GAMEMD 0x845B78
            FUN_00717890(index, ini->ReadInteger(ID.Data, "ShockTurretWeapon", -1));
            // STRING: GAMEMD 0x845B64
            index = ini->ReadInteger(ID.Data, "ExplodeTurretIndex", 0);
            // STRING: GAMEMD 0x845B50
            FUN_00717890(index, ini->ReadInteger(ID.Data, "ExplodeTurretWeapon", -1));
            // STRING: GAMEMD 0x845B38
            index = ini->ReadInteger(ID.Data, "BrainBlastTurretIndex", 0);
            // STRING: GAMEMD 0x845B20
            FUN_00717890(index, ini->ReadInteger(ID.Data, "BrainBlastTurretWeapon", -1));
            // STRING: GAMEMD 0x845B08
            index = ini->ReadInteger(ID.Data, "RadCannonTurretIndex", 0);
            // STRING: GAMEMD 0x845AF0
            FUN_00717890(index, ini->ReadInteger(ID.Data, "RadCannonTurretWeapon", -1));
            // STRING: GAMEMD 0x845ADC
            index = ini->ReadInteger(ID.Data, "ChronoTurretIndex", 0);
            // STRING: GAMEMD 0x845AC8
            FUN_00717890(index, ini->ReadInteger(ID.Data, "ChronoTurretWeapon", -1));
            // STRING: GAMEMD 0x845AAC
            index = ini->ReadInteger(ID.Data, "TerroristExplodeTurretIndex", 0);
            // STRING: GAMEMD 0x845A8C
            FUN_00717890(index, ini->ReadInteger(ID.Data, "TerroristExplodeTurretWeapon", -1));
            // STRING: GAMEMD 0x845A7C
            index = ini->ReadInteger(ID.Data, "CowTurretIndex", 0);
            // STRING: GAMEMD 0x845A6C
            FUN_00717890(index, ini->ReadInteger(ID.Data, "CowTurretWeapon", -1));
            // STRING: GAMEMD 0x845A58
            index = ini->ReadInteger(ID.Data, "InitiateTurretIndex", 0);
            // STRING: GAMEMD 0x845A40
            FUN_00717890(index, ini->ReadInteger(ID.Data, "InitiateTurretWeapon", -1));
            // STRING: GAMEMD 0x845A2C
            index = ini->ReadInteger(ID.Data, "VirusTurretIndex", 0);
            // STRING: GAMEMD 0x845A18
            FUN_00717890(index, ini->ReadInteger(ID.Data, "VirusTurretWeapon", -1));
            // STRING: GAMEMD 0x845A00
            index = ini->ReadInteger(ID.Data, "YuriPrimeTurretIndex", 0);
            // STRING: GAMEMD 0x8459E8
            FUN_00717890(index, ini->ReadInteger(ID.Data, "YuriPrimeTurretWeapon", -1));
            // STRING: GAMEMD 0x8459D4
            index = ini->ReadInteger(ID.Data, "GuardianTurretIndex", 0);
            // STRING: GAMEMD 0x8459BC
            FUN_00717890(index, ini->ReadInteger(ID.Data, "GuardianTurretWeapon", -1));
        }
        return true;
    }
    return false;
}
