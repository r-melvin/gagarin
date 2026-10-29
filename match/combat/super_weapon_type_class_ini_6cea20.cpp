// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   SuperWeaponTypeClass::vf_25 (retail 0x6CEA20, 0x43D bytes): the INI reader of the super weapon type.
//   Every key string, destination offset, reader call and default was read off the user's retail
//   gamemd.exe v1.001 disassembly; field names are the INI key strings themselves.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../_layout/super_weapon_type_class.h"
#include "../core/rules_class_ini_support.h"
#include "../core/bounded_text.h"

// GLOBAL: GAMEMD 0x7E2800 -- 0.0, read from memory rather than FLDZ.
extern const double DAT_007E2800;
// GLOBAL: GAMEMD 0x7F4100 -- 900.0f, the recharge time scale (frames per minute).
extern const float DAT_007F4100;
// GLOBAL: GAMEMD 0x8425C0 -- the twelve super weapon type names.
extern const char* const Names_008425C0[12];
// STRING: GAMEMD 0x81834C -- ".SHP".
extern const char STR_0081834C[];
// STRING: GAMEMD 0x8204FC -- "XXICON.SHP".
extern const char STR_DEFAULT_ICON[];
// FUNCTION: GAMEMD 0x5B40B0 (decl; reloc) -- loads a shape file by path.
void* __fastcall FUN_005B40B0(const char* name, bool flag);

// The CCINIClass reader of a super weapon action that CCINIClass itself does not declare.
class SuperWeaponIniView : public CCINIClass
{
public:
    // FUNCTION: GAMEMD 0x474EE0 (decl; reloc) -- super weapon action by name.
    int ReadSuperWeaponAction(const char* section, const char* key, int fallback);
};

// FUNCTION: GAMEMD 0x6CEA20
// Reads the super weapon type's rules section: the abstract type reader first, then every key over its
// current value.
bool SuperWeaponTypeClass::vf_25(CCINIClass* ini)
{
    char buffer[0x80];
    char typeName[0x28];
    char preDependent[0x28];
    char cameo[0x100];
    char path[0x200];

    ini->Reset();
    if (AbstractTypeClass::vf_25(ini))
    {
        // STRING: GAMEMD 0x81725C
        { void* t = WeaponType; WeaponType = ini->ReadString(ID.Data, "WeaponType", STR_00889F64, buffer, 0x80) ? WeaponType_FindPtr(buffer) : t; }
        // STRING: GAMEMD 0x817270
        Action = static_cast<SuperWeaponIniView*>(ini)->ReadSuperWeaponAction(ID.Data, "Action", Action);
        // STRING: GAMEMD 0x84270C
        IsPowered = ini->ReadBool(ID.Data, "IsPowered", IsPowered);
        // STRING: GAMEMD 0x8426F4
        DisableableFromShell = ini->ReadBool(ID.Data, "DisableableFromShell", DisableableFromShell);
        // STRING: GAMEMD 0x8426DC
        FlashSidebarTabFrames = ini->ReadInteger(ID.Data, "FlashSidebarTabFrames", FlashSidebarTabFrames);
        // STRING: GAMEMD 0x8426CC
        AIDefendAgainst = ini->ReadBool(ID.Data, "AIDefendAgainst", AIDefendAgainst);
        // STRING: GAMEMD 0x8426C0
        PreClick = ini->ReadBool(ID.Data, "PreClick", PreClick);
        // STRING: GAMEMD 0x8426B4
        PostClick = ini->ReadBool(ID.Data, "PostClick", PostClick);
        // STRING: GAMEMD 0x8426A8
        ShowTimer = ini->ReadBool(ID.Data, "ShowTimer", ShowTimer);
        // STRING: GAMEMD 0x842698
        { int t = SpecialSound; int index; SpecialSound = (ini->ReadString(ID.Data, "SpecialSound", STR_00889F64, buffer, 0x80) && (index = VocClass::FindIndex(buffer)) != -1) ? index : t; }
        // STRING: GAMEMD 0x818418
        { int t = StartSound; int index; StartSound = (ini->ReadString(ID.Data, "StartSound", STR_00889F64, buffer, 0x80) && (index = VocClass::FindIndex(buffer)) != -1) ? index : t; }
        // STRING: GAMEMD 0x842690
        Range = (float)ini->ReadDouble(ID.Data, "Range", Range);
        // STRING: GAMEMD 0x842680
        LineMultiplier = ini->ReadInteger(ID.Data, "LineMultiplier", LineMultiplier);
        // STRING: GAMEMD 0x824314
        ini->ReadString(ID.Data, "Type", STR_00889F64, typeName, 0x28);
        if (strlen(typeName) != 0)
        {
            for (int i = 0; i < 12; i++)
            {
                if (_stricmp(Names_008425C0[i], typeName) == 0)
                {
                    if (i != -1)
                        Type = i;
                    break;
                }
            }
        }
        // STRING: GAMEMD 0x842670
        ini->ReadString(ID.Data, "PreDependent", STR_00889F64, preDependent, 0x28);
        if (strlen(preDependent) != 0)
        {
            for (int i = 0; i < 12; i++)
            {
                if (_stricmp(Names_008425C0[i], preDependent) == 0)
                {
                    if (i != -1)
                        PreDependent = i;
                    break;
                }
            }
        }
        // STRING: GAMEMD 0x842664
        { void* t = AuxBuilding; AuxBuilding = ini->ReadString(ID.Data, "AuxBuilding", STR_00889F64, buffer, 0x80) ? BuildingType_FindPtr(buffer) : t; }
        // STRING: GAMEMD 0x842654
        UseChargeDrain = ini->ReadBool(ID.Data, "UseChargeDrain", UseChargeDrain);
        // STRING: GAMEMD 0x842644
        ManualControl = ini->ReadBool(ID.Data, "ManualControl", ManualControl);
        // STRING: GAMEMD 0x842634
        double rechargeTime = ini->ReadDouble(ID.Data, "RechargeTime", 0.0);
        if (rechargeTime != DAT_007E2800)
            RechargeTime = (int)(DAT_007F4100 * (float)rechargeTime);
        // STRING: GAMEMD 0x842624
        ini->ReadString(ID.Data, "SidebarImage", CameoFile, cameo, 0x100);
        GgBoundedText<25>(cameo).CopyTo(CameoFile);
        // STRING: GAMEMD 0x81834C
        _makepath(path, 0, 0, CameoFile, STR_0081834C);
        SidebarImage = FUN_005B40B0(path, false);
        if (SidebarImage == 0)
            SidebarImage = FUN_005B40B0(STR_DEFAULT_ICON, false);
        return true;
    }
    return false;
}
