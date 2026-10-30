// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   TeamTypeClass construction, destruction and stream loading, read off retail
//   gamemd.exe v1.001 (vtable 0x7F47D0). The layout is match/_layout/team_type_class.h.
//   /Ob2: the registry AddItem/RemoveItem bodies are expanded in place, and the
//   scalar deleting destructor carries the destructor body inline.

#include "../FUNCTION.H"
#include "team_type_class_create_methods.h"
#include "team_type_class_methods.h"
#include "team_type_class_instance_methods.h"
#include "team_type_class_taskforce_methods.h"
#include "../platform/ccini_class_methods.h"

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


// GLOBAL: GAMEMD 0xA8ECA0 -- the team type registry.
extern DynamicVectorClass<TeamTypeClass*> DAT_00A8ECA0;
// GLOBAL: GAMEMD 0xB0F670 -- the shared abstract-type registry.
extern DynamicVectorClass<TeamTypeClass*> DAT_00B0F670;
// GLOBAL: GAMEMD 0xB0C110 -- the swizzle manager.
extern SwizzleManagerClass DAT_00B0C110;

// Registry append, expanded in place: the growth increment is tested before the sum.
static inline bool TeamTypeRegistryAdd(DynamicVectorClass<TeamTypeClass*>* vector, TeamTypeClass* item)
{
    if (vector->Count >= vector->Capacity) {
        if (!vector->IsAllocated && vector->Capacity != 0)
            return false;
        if (vector->CapacityIncrement <= 0)
            return false;
        if (!vector->SetCapacity(vector->Capacity + vector->CapacityIncrement, 0))
            return false;
    }
    int index = vector->Count++;
    vector->Items[index] = item;
    return true;
}

// FUNCTION: GAMEMD 0x6F06E0
TeamTypeClass::TeamTypeClass(const char* id)
    : AbstractTypeClass(id),
      ArrayIndex(-1),
      Group(-1),
      unknown_A0(1),
      Flag_A4(false),
      Flag_A5(false),
      Flag_A6(false),
      Flag_A7(false),
      Flag_A8(false),
      Flag_A9(false),
      Flag_AA(false),
      Flag_AB(false),
      Flag_AC(false),
      Flag_AD(false),
      Flag_AE(false),
      Flag_AF(false),
      Flag_B0(false),
      Flag_B1(false),
      Flag_B2(false),
      Flag_B3(false),
      unknown_B4(7),
      Max(-1),
      unknown_BC(0),
      unknown_C0(0),
      Owner(0),
      idxHouse(-1),
      unknown_CC(0),
      Ptr_D0(0),
      Waypoint(-1),
      TransportWaypoint(-1),
      InstanceCount(0),
      Ptr_E0(0),
      TaskForce(0),
      unknown_E8(0),
      unknown_EC(9),
      Flag_F0(true),
      Flag_F1(false),
      Flag_F2(false),
      Flag_F3(false),
      Flag_F4(false),
      Flag_F5(true),
      Flag_F6(false),
      Flag_F7(false)
{
    TeamTypeRegistryAdd(&DAT_00A8ECA0, this);
    ArrayIndex = DAT_00A8ECA0.FindItemIndex(this);
    TeamTypeRegistryAdd(&DAT_00B0F670, this);
}

// FUNCTION: GAMEMD 0x6F08F0
TeamTypeClass::~TeamTypeClass()
{
    AnnounceExpiredPointer(1);
    DAT_00A8ECA0.RemoveItem(this);
    DAT_00B0F670.RemoveItem(this);
}

// FUNCTION: GAMEMD 0x6F09C0
TeamClass* TeamTypeClass::CreateTeam(HouseClass* house)
{
    // STRING: GAMEMD 0x842E7C
    FUN_004068E0("Create_One_Of...\n");

    if (house == 0) {
        house = this->Owner;
        if (house == 0) {
            if (!FUN_00510F60(this->idxHouse)) {
                return 0;
            }
            house = FindHouseByCountryIndex(this->idxHouse);
            if (house == 0) {
                return 0;
            }
        }
    }

    if (ScenarioInit_00A8E7AC == 0 && this->Max >= 0) {
        if (Session_00A8B238.GameMode == 0) {
            if (this->InstanceCount >= this->Max) {
                return 0;
            }
        } else {
            if (house->FUN_005095D0(this) >= this->Max) {
                return 0;
            }
        }
    }

    // STRING: GAMEMD 0x842E58
    FUN_004068E0("Creating a new team named '%s'.\n", this->Name.Data);

    TeamClass* team = (TeamClass*)operator new(sizeof(TeamClass));
    return team ? team->Construct(this, house, 0) : 0;
}

// FUNCTION: GAMEMD 0x6F1090
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

// FUNCTION: GAMEMD 0x6F1870
int TeamTypeClass::GetGroup() const
{
    int group = this->Group;
    if (group != -2 && group == -1 && this->TaskForce != 0) {
        group = this->TaskForce->ArrayIndex;
    }
    return group;
}

// FUNCTION: GAMEMD 0x6F18A0
CellStruct* TeamTypeClass::GetWaypoint(CellStruct* buffer) const
{
    CellStruct local;

    if (this->Waypoint == -1) {
        *buffer = DefaultWaypointCell;
        return buffer;
    }
    *buffer = *WaypointLocatorPtr->GetCoords(&local, this->Waypoint);
    return buffer;
}

// FUNCTION: GAMEMD 0x6F18E0
CellStruct* TeamTypeClass::GetTransportWaypoint(CellStruct* buffer) const
{
    CellStruct local;

    if (this->TransportWaypoint == -1) {
        *buffer = DefaultWaypointCell;
        return buffer;
    }
    *buffer = *WaypointLocatorPtr->GetCoords(&local, this->TransportWaypoint);
    return buffer;
}

// FUNCTION: GAMEMD 0x6F1BB0
HRESULT __stdcall TeamTypeClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) TeamTypeClass(AbstractNoInit());
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Owner);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Ptr_D0);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Ptr_E0);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&TaskForce);
    return 0;
}

// FUNCTION: GAMEMD 0x6F1C80
// Feeds the type's settings, and the identity of the objects it points at, to the checksum.
void TeamTypeClass::vf_13(Obj_004A1D30* crc)
{
    AbstractTypeClass::vf_13(crc);
    crc->FUN_004A1D50(Group);
    crc->FUN_004A1CA0(Flag_A8);
    crc->FUN_004A1CA0(Flag_A9);
    crc->FUN_004A1CA0(Flag_AA);
    crc->FUN_004A1CA0(Flag_AB);
    crc->FUN_004A1CA0(Flag_AC);
    crc->FUN_004A1CA0(Flag_AD);
    crc->FUN_004A1CA0(Flag_AE);
    crc->FUN_004A1CA0(Flag_AF);
    crc->FUN_004A1CA0(Flag_B0);
    crc->FUN_004A1CA0(Flag_B1);
    crc->FUN_004A1D50(unknown_B4);
    crc->FUN_004A1D50(Max);
    crc->FUN_004A1D50(unknown_BC);
    if (Owner) {
        crc->FUN_004A1D50(Owner->vf_11());
    }
    if (Owner) {
        crc->FUN_004A1D50(Owner->vf_rtti_4());
    }
    crc->FUN_004A1D50(unknown_CC);
    if (Ptr_D0) {
        crc->FUN_004A1D50(Ptr_D0->vf_rtti_4());
    }
    crc->FUN_004A1D50(Waypoint);
    crc->FUN_004A1D50(TransportWaypoint);
    crc->FUN_004A1D50(InstanceCount);
    if (Ptr_E0) {
        crc->FUN_004A1D50(Ptr_E0->vf_rtti_4());
    }
    if (TaskForce) {
        crc->FUN_004A1D50(TaskForce->vf_rtti_4());
    }
}

// FUNCTION: GAMEMD 0x6F1F30
void TeamTypeClass::FlashAllInstances(int duration)
{
    for (int i = 0; i < DAT_008B40E8.Count; i++) {
        TeamClass* team = ((TeamClass**)DAT_008B40E8.Items)[i];
        if (team->Type == this) {
            team->Flash(duration);
        }
    }
}

// FUNCTION: GAMEMD 0x6F1F70
TeamClass* TeamTypeClass::FindFirstInstance() const
{
    int count = DAT_008B40E8.Count;
    for (int i = 0; i < count; i++) {
        TeamClass* team = ((TeamClass**)DAT_008B40E8.Items)[i];
        if (team->Type == this) {
            return team;
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x6F1FA0
void TeamTypeClass::ProcessTaskForce()
{
    this->Flag_F0 = true;
    this->Flag_F1 = false;
    this->unknown_EC = 9;

    for (int i = 0; i < this->TaskForce->EntryCount; i++) {
        TechnoTypeClass* type = this->TaskForce->Entries[i].Type;

        if (type->Naval) {
            if (type->Passengers == 0) {
                this->Flag_F0 = false;
            } else {
                this->Flag_F1 = true;
            }
        }

        this->unknown_EC = FUN_005889F0(type->MovementZone, this->unknown_EC);
    }

    if (this->Flag_F6) {
        this->Flag_F0 = false;
    }
}

// SYNTHETIC: GAMEMD 0x6F20D0
// TeamTypeClass scalar deleting destructor (primary slot 8), the destructor expanded in place.

