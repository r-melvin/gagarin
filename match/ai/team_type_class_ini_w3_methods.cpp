// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   TeamTypeClass INI reader (virtual slot 25), read off retail gamemd.exe v1.001.
//   The layout is match/_layout/team_type_class.h. Member meanings, from the INI keys:
//   +0xA0 VeteranLevel, +0xC0 MindControlDecision, +0xC4 owner house (or +0xC8 country
//   index), +0xD0 Tag, +0xD4/+0xD8 Waypoint/TransportWaypoint, +0xE0 Script, +0xE4 TaskForce.
//   Address index: 0x6F1090 vf_25.

#include "../_layout/team_type_class.h"
#include "../_layout/house_class.h"
#include "../_layout/house_type_class.h"
#include "../platform/ccini_class_methods.h"
#include "../core/vector_class_operations.h"

// FUNCTION: GAMEMD 0x510F60 (decl; reloc) -- is this country index a pseudo-house code?
bool __fastcall FUN_00510F60(int code);
// FUNCTION: GAMEMD 0x502D30 (decl; reloc) -- the house of a country index.
HouseClass* __fastcall FUN_00502D30(int index);
// FUNCTION: GAMEMD 0x6E6310 (decl; reloc) -- find or make the tag type of that name.
AbstractClass* __fastcall FUN_006E6310(const char* id);
// FUNCTION: GAMEMD 0x691C00 (decl; reloc) -- find or make the script type of that name.
AbstractClass* __fastcall FUN_00691C00(const char* id);
// FUNCTION: GAMEMD 0x6E85F0 (decl; reloc) -- find or make the task force of that name.
AbstractClass* __fastcall FUN_006E85F0(const char* id);
// FUNCTION: GAMEMD 0x763610 (decl; reloc) -- the letter name of a waypoint number.
const char* __fastcall FUN_00763610(int waypoint);
// FUNCTION: GAMEMD 0x763690 (decl; reloc) -- the waypoint number of a letter name.
int __fastcall FUN_00763690(const char* name);

// GLOBAL: GAMEMD 0x889F64 -- the empty default string.
extern const char DAT_00889F64[];
// GLOBAL: GAMEMD 0xA8E8D0 -- the task force registry.
extern DynamicVectorClass<AbstractClass*> DAT_00A8E8D0;
// GLOBAL: GAMEMD 0x8B41C8 -- the script type registry.
extern DynamicVectorClass<AbstractClass*> DAT_008B41C8;

// FUNCTION: GAMEMD 0x6F1090
// Reads every team type key from its INI section; fails when no task force or script exists.
bool TeamTypeClass::vf_25(CCINIClass* ini)
{
    char buffer[128];
    char waypoint[64];
    ini->Reset();
    if (AbstractTypeClass::vf_25(ini)) {
        int current = -1;
        if (Owner) {
            current = Owner->Type->ArrayIndex2;
        }
        int country = ini->FUN_00475540(ID.Data, "House", current);
        if (FUN_00510F60(country)) {
            idxHouse = country;
            Owner = 0;
        } else if (country != -1) {
            Owner = FUN_00502D30(country);
            idxHouse = -1;
        }
        unknown_A0 = ini->FUN_005276D0(ID.Data, "VeteranLevel", unknown_A0);
        unknown_C0 = ini->FUN_005276D0(ID.Data, "MindControlDecision", unknown_C0);
        Flag_A4 = ini->FUN_005295F0(ID.Data, "Loadable", Flag_A4);
        Flag_A5 = ini->FUN_005295F0(ID.Data, "Full", Flag_A5);
        Flag_A6 = ini->FUN_005295F0(ID.Data, "Annoyance", Flag_A6);
        Flag_A7 = ini->FUN_005295F0(ID.Data, "GuardSlower", Flag_A7);
        Flag_A9 = ini->FUN_005295F0(ID.Data, "Autocreate", Flag_A9);
        Flag_AA = ini->FUN_005295F0(ID.Data, "Prebuild", Flag_AA);
        Flag_AB = ini->FUN_005295F0(ID.Data, "Reinforce", Flag_AB);
        Flag_B0 = ini->FUN_005295F0(ID.Data, "Droppod", Flag_B0);
        Flag_B1 = ini->FUN_005295F0(ID.Data, "UseTransportOrigin", Flag_B1);
        Flag_A8 = ini->FUN_005295F0(ID.Data, "Recruiter", Flag_A8);
        Flag_AC = ini->FUN_005295F0(ID.Data, "Whiner", Flag_AC);
        Flag_AF = ini->FUN_005295F0(ID.Data, "Suicide", Flag_AF);
        Flag_AE = ini->FUN_005295F0(ID.Data, "LooseRecruit", Flag_AE);
        Flag_AD = ini->FUN_005295F0(ID.Data, "Aggressive", Flag_AD);
        Flag_B3 = ini->FUN_005295F0(ID.Data, "OnTransOnly", Flag_B3);
        unknown_B4 = ini->FUN_005276D0(ID.Data, "Priority", unknown_B4);
        Max = ini->FUN_005276D0(ID.Data, "Max", Max);
        unknown_CC = ini->FUN_005276D0(ID.Data, "TechLevel", unknown_CC);
        AbstractClass* tag = Ptr_D0;
        Ptr_D0 = ini->FUN_00528A10(ID.Data, "Tag", DAT_00889F64, buffer, 128) ? FUN_006E6310(buffer) : tag;
        Group = ini->FUN_005276D0(ID.Data, "Group", Group);
        Flag_F2 = ini->FUN_005295F0(ID.Data, "AvoidThreats", Flag_F2);
        Flag_F3 = ini->FUN_005295F0(ID.Data, "IonImmune", Flag_F3);
        Flag_F6 = ini->FUN_005295F0(ID.Data, "IsBaseDefense", Flag_F6);
        Flag_F7 = ini->FUN_005295F0(ID.Data, "OnlyTargetHouseEnemy", Flag_F7);
        Flag_F4 = ini->FUN_005295F0(ID.Data, "TransportsReturnOnUnload", Flag_F4);
        Flag_F5 = ini->FUN_005295F0(ID.Data, "AreTeamMembersRecruitable", Flag_F5);
        if (ini->FUN_00528A10(ID.Data, "Waypoint", FUN_00763610(Waypoint), waypoint, 64) > 0) {
            Waypoint = FUN_00763690(waypoint);
        }
        if (ini->FUN_00528A10(ID.Data, "TransportWaypoint", FUN_00763610(TransportWaypoint), waypoint, 64) > 0) {
            TransportWaypoint = FUN_00763690(waypoint);
        }
        AbstractClass* script = Ptr_E0;
        AbstractClass* newScript = ini->FUN_00528A10(ID.Data, "Script", DAT_00889F64, buffer, 128) ? FUN_00691C00(buffer) : script;
        TaskForceClass* taskForce = TaskForce;
        Ptr_E0 = newScript;
        TaskForce = ini->FUN_00528A10(ID.Data, "TaskForce", DAT_00889F64, buffer, 128) ? static_cast<TaskForceClass*>(FUN_006E85F0(buffer)) : taskForce;
        if (!TaskForce) {
            if (DAT_00A8E8D0.Count <= 0) {
                return false;
            }
            TaskForce = static_cast<TaskForceClass*>(DAT_00A8E8D0.Items[0]);
        }
        if (!Ptr_E0) {
            if (DAT_008B41C8.Count <= 0) {
                return false;
            }
            Ptr_E0 = DAT_008B41C8.Items[0];
        }
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x6F1550
// Writes every team type key back to its INI section, naming the tag, script and task force.
bool TeamTypeClass::vf_26(CCINIClass* ini)
{
    if (AbstractTypeClass::vf_26(ini)) {
        int house = -1;
        if (Owner) {
            house = Owner->Type->ArrayIndex2;
        } else if (FUN_00510F60(idxHouse)) {
            house = idxHouse;
        }
        ini->WriteInteger(ID.Data, "VeteranLevel", unknown_A0, 0);
        ini->WriteInteger(ID.Data, "MindControlDecision", unknown_C0, 0);
        ini->WriteBool(ID.Data, "Loadable", Flag_A4);
        ini->WriteBool(ID.Data, "Full", Flag_A5);
        ini->WriteBool(ID.Data, "Annoyance", Flag_A6);
        ini->WriteBool(ID.Data, "GuardSlower", Flag_A7);
        ini->FUN_00475610(ID.Data, "House", house);
        ini->WriteBool(ID.Data, "Recruiter", Flag_A8);
        ini->WriteBool(ID.Data, "Autocreate", Flag_A9);
        ini->WriteBool(ID.Data, "Prebuild", Flag_AA);
        ini->WriteBool(ID.Data, "Reinforce", Flag_AB);
        ini->WriteBool(ID.Data, "Droppod", Flag_B0);
        ini->WriteBool(ID.Data, "UseTransportOrigin", Flag_B1);
        ini->WriteBool(ID.Data, "Whiner", Flag_AC);
        ini->WriteBool(ID.Data, "LooseRecruit", Flag_AE);
        ini->WriteBool(ID.Data, "Aggressive", Flag_AD);
        ini->WriteBool(ID.Data, "Suicide", Flag_AF);
        ini->WriteInteger(ID.Data, "Priority", unknown_B4, 0);
        ini->WriteInteger(ID.Data, "Max", Max, 0);
        ini->WriteInteger(ID.Data, "TechLevel", unknown_CC, 0);
        ini->WriteInteger(ID.Data, "Group", Group, 0);
        ini->WriteBool(ID.Data, "OnTransOnly", Flag_B3);
        ini->WriteBool(ID.Data, "AvoidThreats", Flag_F2);
        ini->WriteBool(ID.Data, "IonImmune", Flag_F3);
        ini->WriteBool(ID.Data, "TransportsReturnOnUnload", Flag_F4);
        ini->WriteBool(ID.Data, "AreTeamMembersRecruitable", Flag_F5);
        ini->WriteBool(ID.Data, "IsBaseDefense", Flag_F6);
        ini->WriteBool(ID.Data, "OnlyTargetHouseEnemy", Flag_F7);
        if (Ptr_D0) {
            ini->WriteString(ID.Data, "Tag", static_cast<AbstractTypeClass*>(Ptr_D0)->ID.Data);
        }
        ini->WriteString(ID.Data, "Waypoint", FUN_00763610(Waypoint));
        ini->WriteString(ID.Data, "TransportWaypoint", FUN_00763610(TransportWaypoint));
        if (Ptr_E0) {
            ini->WriteString(ID.Data, "Script", static_cast<AbstractTypeClass*>(Ptr_E0)->ID.Data);
        }
        if (TaskForce) {
            ini->WriteString(ID.Data, "TaskForce", static_cast<AbstractTypeClass*>(TaskForce)->ID.Data);
        }
        return true;
    }
    return false;
}
