// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x671EA0.

#include "rules_class_ini_support.h"

// FUNCTION: GAMEMD 0x671EA0
//
// Read the [MultiplayerDialogSettings] section into the rules object. Reports whether the section exists.
bool RulesClass::Read_MultiplayerDialogSettings(CCINIClass* pINI)
{
    bool        ok  = false;
    const char* key = 0;

    if (key == 0) {
        ok = pINI->GetSection(MultiplayerDialogSettingsSection) != 0;
    } else {
        ok = pINI->GetEntry(MultiplayerDialogSettingsSection, key) != 0;
    }
    if (ok) {
        char buffer[0x80];

        MinMoney = pINI->ReadInteger(MultiplayerDialogSettingsSection, "MinMoney", MinMoney);
        Money = pINI->ReadInteger(MultiplayerDialogSettingsSection, "Money", Money);
        MaxMoney = pINI->ReadInteger(MultiplayerDialogSettingsSection, "MaxMoney", MaxMoney);
        MoneyIncrement = pINI->ReadInteger(MultiplayerDialogSettingsSection, "MoneyIncrement", MoneyIncrement);
        MinUnitCount = pINI->ReadInteger(MultiplayerDialogSettingsSection, "MinUnitCount", MinUnitCount);
        UnitCount = pINI->ReadInteger(MultiplayerDialogSettingsSection, "UnitCount", UnitCount);
        MaxUnitCount = pINI->ReadInteger(MultiplayerDialogSettingsSection, "MaxUnitCount", MaxUnitCount);
        TechLevel = pINI->ReadInteger(MultiplayerDialogSettingsSection, "TechLevel", TechLevel);
        GameSpeed = pINI->ReadInteger(MultiplayerDialogSettingsSection, "GameSpeed", GameSpeed);
        AIDifficulty = pINI->ReadInteger(MultiplayerDialogSettingsSection, "AIDifficulty", AIDifficulty);
        AIPlayers = pINI->ReadInteger(MultiplayerDialogSettingsSection, "AIPlayers", AIPlayers);
        BridgeDestruction = pINI->ReadBool(MultiplayerDialogSettingsSection, "BridgeDestruction", BridgeDestruction);
        ShadowGrow = pINI->ReadBool(MultiplayerDialogSettingsSection, "ShadowGrow", ShadowGrow);
        Shroud = pINI->ReadBool(MultiplayerDialogSettingsSection, "Shroud", Shroud);
        Bases = pINI->ReadBool(MultiplayerDialogSettingsSection, "Bases", Bases);
        TiberiumGrows = pINI->ReadBool(MultiplayerDialogSettingsSection, "TiberiumGrows", TiberiumGrows);
        Crates = pINI->ReadBool(MultiplayerDialogSettingsSection, "Crates", Crates);
        CaptureTheFlag = pINI->ReadBool(MultiplayerDialogSettingsSection, "CaptureTheFlag", CaptureTheFlag);
        HarvesterTruce = pINI->ReadBool(MultiplayerDialogSettingsSection, "HarvesterTruce", HarvesterTruce);
        MultiEngineer = pINI->ReadBool(MultiplayerDialogSettingsSection, "MultiEngineer", MultiEngineer);
        AlliesAllowed = pINI->ReadBool(MultiplayerDialogSettingsSection, "AlliesAllowed", AlliesAllowed);
        AllyChangeAllowed = pINI->ReadBool(MultiplayerDialogSettingsSection, "AllyChangeAllowed", AllyChangeAllowed);
        ShortGame = pINI->ReadBool(MultiplayerDialogSettingsSection, "ShortGame", ShortGame);
        SuperWeaponsAllowed = pINI->ReadBool(MultiplayerDialogSettingsSection, "SuperWeaponsAllowed", SuperWeaponsAllowed);
        BuildOffAlly = pINI->ReadBool(MultiplayerDialogSettingsSection, "BuildOffAlly", BuildOffAlly);
        FogOfWar = pINI->ReadBool(MultiplayerDialogSettingsSection, "FogOfWar", FogOfWar);
        MCVRedeploys = pINI->ReadBool(MultiplayerDialogSettingsSection, "MCVRedeploys", MCVRedeploys);
        return true;
    }
    return false;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x83079C
extern const char STR_0083079C[] = "MultiplayerDialogSettings";
// GLOBAL: GAMEMD 0x83079C
extern const char STR_0083079C[];
// END defined globals
