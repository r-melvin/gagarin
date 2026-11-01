// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail vtable 0x7F47D0 (primary; +4 0x7F47B4, +8 0x7F47AC, +0xC 0x7F47A4) names
//   .?AVTeamTypeClass@@ in its locator. The constructor 0x6F06E0 initialises every
//   member from 0x98 to 0xF7, slot 12 (0x6F20B0) returns the object size 0xF8, and the
//   stream loader 0x6F1BB0 queues four pointer fields (+0xC4, +0xD0, +0xE0, +0xE4) for
//   swizzling. Field meanings past the pointer kinds are not proven, so they keep
//   offset-based names.
#ifndef GG_MATCH_LAYOUT_TEAM_TYPE_CLASS_H
#define GG_MATCH_LAYOUT_TEAM_TYPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_type_class.h"
#include "../vector_class.h"
#include "cell.h"
#include "task_force_class.h"

class HouseClass;
class TechnoClass;
class TeamClass;

class TeamTypeClass : public AbstractTypeClass
{
public:
    // FUNCTION: GAMEMD 0x6F06E0 (constructor)
    TeamTypeClass(const char* id);
    // The class factory's construction (TClassFactory<TeamTypeClass>): the same constructor with a default argument.
    TeamTypeClass(int unknown_arg0 = 0);
    // The stream loader's in-place construction.
    TeamTypeClass(const AbstractNoInit& noInit) : AbstractTypeClass(noInit) {}
    // FUNCTION: GAMEMD 0x6F08F0 (destructor; scalar deleting form 0x6F20D0)
    virtual ~TeamTypeClass();

    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                // 3   0x6F1C40
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 5   0x6F1BB0
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);      // 6   0x6F1B90
    virtual void vf_10(void* target, bool removed);                       // 10  0x6F1030
    virtual int vf_11();                                                  // 11  0x6F20A0
    virtual int vf_12();                                                  // 12  0x6F20B0
    virtual void vf_13(Obj_004A1D30* crc);                                // 13  0x6F1C80
    virtual int vf_16();                                                  // 16  0x6F20C0
    virtual bool vf_25(CCINIClass* ini);                                  // 25  0x6F1090
    virtual bool vf_26(CCINIClass* ini);                                  // 26  0x6F1550

    // GAMEMD 0x6F2070 -- the owning house (cached Owner, else the country index).
    HouseClass* GetHouse() const;
    // GAMEMD 0x6F0A70 -- remove every live team spawned from this type.
    void DestroyAllInstances();
    // GAMEMD 0x6F2040 -- run ProcessTaskForce over every team type.
    static void ProcessAllTaskforces();
    // FUNCTION: GAMEMD 0x6F1FA0 -- derive the summary flags from the task force.
    void ProcessTaskForce();
    // FUNCTION: GAMEMD 0x6F1E20 (decl; reloc) -- whether the techno can fill a slot of this team for the house, RET 8.
    bool FUN_006F1E20(TechnoClass* techno, HouseClass* house);
    // GAMEMD 0x6F1F30 / 0x6F1F70 -- instance enumeration helpers.
    void FlashAllInstances(int duration);
    TeamClass* FindFirstInstance() const;
    // FUNCTION: GAMEMD 0x6F09C0 -- instantiate one team of this type for `house`.
    TeamClass* CreateTeam(HouseClass* house);
    // GAMEMD 0x6F18E0 / 0x6F1870 / 0x6F18A0 accessors.
    int GetGroup() const;
    CellStruct* GetWaypoint(CellStruct* buffer) const;
    CellStruct* GetTransportWaypoint(CellStruct* buffer) const;

    int            ArrayIndex;      // +0x98  index in the type array
    int            Group;           // +0x9C
    int            VeteranLevel;      // +0xA0
    bool           Loadable;         // +0xA4
    bool           Full;         // +0xA5
    bool           Annoyance;         // +0xA6
    bool           GuardSlower;         // +0xA7
    bool           Recruiter;         // +0xA8
    bool           Autocreate;         // +0xA9
    bool           Prebuild;         // +0xAA
    bool           Reinforce;         // +0xAB
    bool           Whiner;         // +0xAC
    bool           Aggressive;         // +0xAD
    bool           LooseRecruit;         // +0xAE
    bool           Suicide;         // +0xAF
    bool           Droppod;         // +0xB0
    bool           UseTransportOrigin;         // +0xB1
    bool           Flag_B2;         // +0xB2
    bool           OnTransOnly;         // +0xB3
    int            Priority;      // +0xB4
    int            Max;             // +0xB8 instance cap, -1 = none
    int            unknown_BC;      // +0xBC
    int            MindControlDecision;      // +0xC0
    HouseClass*    Owner;           // +0xC4 owner house (INI "House")
    int            idxHouse;        // +0xC8 country index while no house is set
    int            TechLevel;      // +0xCC
    AbstractClass* Tag;          // +0xD0 tag type (INI "Tag")
    int            Waypoint;        // +0xD4 INI "Waypoint"
    int            TransportWaypoint; // +0xD8 INI "TransportWaypoint"
    int            InstanceCount;   // +0xDC live instances (compared against Max in campaign mode)
    AbstractClass* Script;          // +0xE0 script type (INI "Script")
    TaskForceClass* TaskForce;      // +0xE4 task force (INI "TaskForce"; GetGroup reads its +0x98)
    int            unknown_E8;      // +0xE8
    int            unknown_EC;      // +0xEC
    bool           Flag_F0;         // +0xF0
    bool           Flag_F1;         // +0xF1
    bool           AvoidThreats;         // +0xF2
    bool           IonImmune;         // +0xF3
    bool           TransportsReturnOnUnload;         // +0xF4
    bool           AreTeamMembersRecruitable;         // +0xF5
    bool           IsBaseDefense;         // +0xF6
    bool           OnlyTargetHouseEnemy;         // +0xF7
};

GG_STATIC_ASSERT(offsetof(TeamTypeClass, ArrayIndex) == 0x98);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, Group) == 0x9C);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, Loadable) == 0xA4);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, Priority) == 0xB4);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, Max) == 0xB8);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, Owner) == 0xC4);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, idxHouse) == 0xC8);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, Waypoint) == 0xD4);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, TransportWaypoint) == 0xD8);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, InstanceCount) == 0xDC);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, Tag) == 0xD0);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, Script) == 0xE0);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, TaskForce) == 0xE4);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, OnlyTargetHouseEnemy) == 0xF7);
GG_STATIC_ASSERT(sizeof(TeamTypeClass) == 0xF8);

#endif
