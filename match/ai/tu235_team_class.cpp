// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit TU235 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x6e8880-0x6f046f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// Walk of a sibling-linked list of child objects (first child at +0x54 of the
// owner, next sibling at +0x5D8 of a child): every child whose virtual slot 11
// returns 1 and whose type (virtual slot 33; identifier text at +0x24) equals a
// fixed name receives a pointer chosen by the index a global lookup object
// returns (stored at +0x6C4); finally the owner's flag at +0x80 is set. Two
// copies at different addresses with their own name and lookup object (the two
// globals are swapped between them); owner, child and type are placeholders and
// each address is verified separately.
//
//   Names cross-checked against an outside reference (
//   every offset reconfirmed against the user's binary in the header).
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.
//
// Small forwarding bodies that repeat at two or more retail addresses. Each
// address is compiled and checked on its own; the copies differ in the callee
// or the table. Owners that are not modelled elsewhere are placeholders
// `Obj_<ADDR>` declaring only the callees the body uses, which are named by
// address.

//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.

#include <stddef.h>
#include "../_layout/foot_class.h"
#include "../movement/loco_interfaces.h"
#include "../_rt/gg_static_assert.h"

struct Arg1_006EDEF0;
struct Obj_006EDE40;
struct Obj_006EDE80;
struct Obj_006EDEF0;
struct Obj_006EDF90;
struct Obj_006EDF90_2C;
struct Obj_006EDFB0;
struct Obj_006EDFB0_2C;
struct Obj_006EE1B0;
struct Obj_006EE1D0;

// GLOBAL: GAMEMD 0x87F7E8
extern char DAT_0087F7E8[];
// GLOBAL: GAMEMD 0xA83D10
extern char DAT_00A83D10[];
// GLOBAL: GAMEMD 0xA83D4C
extern int DAT_00A83D4C;

// FUNCTION: GAMEMD 0x4FC9E0 (decl; reloc)
void FUN_004FC9E0(int, int, int);
// FUNCTION: GAMEMD 0x577BB0 (decl; reloc)
void FUN_00577BB0(void*, int, int);
// FUNCTION: GAMEMD 0x577F30 (decl; reloc)
void FUN_00577F30(void*, int, int);
// FUNCTION: GAMEMD 0x720B20 (decl; reloc)
void FUN_00720B20(void*, int, int);

struct Arg1_006EDEF0
{
    char unknown_00[0x4];
    int unknown_04;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(Arg1_006EDEF0, unknown_04) == 0x4);

struct Obj_006EDE40
{
    char unknown_00[0x80];
    unsigned char unknown_80;   // +0x0080
};
GG_STATIC_ASSERT(offsetof(Obj_006EDE40, unknown_80) == 0x80);

struct Obj_006EDE80
{
    char unknown_00[0x80];
    unsigned char unknown_80;   // +0x0080
    // FUNCTION: GAMEMD 0x6EDE80
    void FUN_006EDE80(int a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_006EDE80, unknown_80) == 0x80);

struct Obj_006EDEF0
{
    char unknown_00[0x80];
    unsigned char unknown_80;   // +0x0080
};
GG_STATIC_ASSERT(offsetof(Obj_006EDEF0, unknown_80) == 0x80);

struct Obj_006EDF90
{
    char unknown_00[0x2C];
    Obj_006EDF90_2C* unknown_2C;   // +0x002C
    char unknown_30[0x50];
    bool unknown_80;   // +0x0080
    // FUNCTION: GAMEMD 0x6EDF90
    void FUN_006EDF90(int a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_006EDF90, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(Obj_006EDF90, unknown_80) == 0x80);

struct Obj_006EDF90_2C
{
    char unknown_00[0x1EE];
    bool unknown_1EE;   // +0x01EE
};
GG_STATIC_ASSERT(offsetof(Obj_006EDF90_2C, unknown_1EE) == 0x1EE);

struct Obj_006EDFB0
{
    char unknown_00[0x2C];
    Obj_006EDFB0_2C* unknown_2C;   // +0x002C
    char unknown_30[0x50];
    unsigned char unknown_80;   // +0x0080
    // FUNCTION: GAMEMD 0x6EDFB0
    void FUN_006EDFB0(int a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_006EDFB0, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(Obj_006EDFB0, unknown_80) == 0x80);

struct Obj_006EDFB0_2C
{
    char unknown_00[0x250];
    int unknown_250;   // +0x0250
};
GG_STATIC_ASSERT(offsetof(Obj_006EDFB0_2C, unknown_250) == 0x250);

struct Obj_006EE1B0
{
    char unknown_00[0x80];
    unsigned char unknown_80;   // +0x0080
};
GG_STATIC_ASSERT(offsetof(Obj_006EE1B0, unknown_80) == 0x80);

struct Obj_006EE1D0
{
    char unknown_00[0x80];
    unsigned char unknown_80;   // +0x0080
};
GG_STATIC_ASSERT(offsetof(Obj_006EE1D0, unknown_80) == 0x80);



void FUN_006EDE40(Obj_006EDE40* a1, int a2, int a3, int a4);
void FUN_006EDEF0(Obj_006EDEF0* a1, int a2, Arg1_006EDEF0* a3, int a4);
void FUN_006EE1B0(Obj_006EE1B0* a1, int a2, int a3, int a4);
void FUN_006EE1D0(Obj_006EE1D0* a1, int a2, int a3, int a4);


//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Arg1_006EDA90;
struct Arg1_006EDAC0;
struct Arg1_006EDAF0;
struct Arg1_006EDB20;
struct Arg1_006EDE10;
struct Arg1_006EDEC0;
struct Gptr_00A8B230;
struct Obj_006EDA90;
struct Obj_006EDAC0;
struct Obj_006EDAF0;
struct Obj_006EDB20;
struct Obj_006EDE10;
struct Obj_006EDE10_28;
struct Obj_006EDE60;
struct Obj_006EDEC0;

// GLOBAL: GAMEMD 0xA83D4C
extern int DAT_00A83D4C;
// GLOBAL: GAMEMD 0xA8B230
#include "../core/scenario_class_methods.h"
extern ScenarioClass* DAT_00A8B230;

// FUNCTION: GAMEMD 0x4FCBD0 (decl; reloc)
void FUN_004FCBD0(int, int, int);
// FUNCTION: GAMEMD 0x5BF260 (decl; reloc)
void FUN_005BF260(int, int, int, int, int);

struct Arg1_006EDA90
{
    char unknown_00[0x4];
    int unknown_04;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(Arg1_006EDA90, unknown_04) == 0x4);

struct Arg1_006EDAC0
{
    char unknown_00[0x4];
    int unknown_04;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(Arg1_006EDAC0, unknown_04) == 0x4);

struct Arg1_006EDAF0
{
    char unknown_00[0x4];
    int unknown_04;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(Arg1_006EDAF0, unknown_04) == 0x4);

struct Arg1_006EDB20
{
    char unknown_00[0x4];
    int unknown_04;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(Arg1_006EDB20, unknown_04) == 0x4);

struct Arg1_006EDE10
{
    char unknown_00[0x4];
    int unknown_04;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(Arg1_006EDE10, unknown_04) == 0x4);

struct Arg1_006EDEC0
{
    char unknown_00[0x4];
    int unknown_04;   // +0x0004
};
GG_STATIC_ASSERT(offsetof(Arg1_006EDEC0, unknown_04) == 0x4);


struct Obj_006EDA90
{
    char unknown_00[0x80];
    unsigned char unknown_80;   // +0x0080
    // FUNCTION: GAMEMD 0x6EDA90
    void FUN_006EDA90(Arg1_006EDA90* a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_006EDA90, unknown_80) == 0x80);

struct Obj_006EDAC0
{
    char unknown_00[0x80];
    unsigned char unknown_80;   // +0x0080
    // FUNCTION: GAMEMD 0x6EDAC0
    void FUN_006EDAC0(Arg1_006EDAC0* a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_006EDAC0, unknown_80) == 0x80);

struct Obj_006EDAF0
{
    char unknown_00[0x80];
    unsigned char unknown_80;   // +0x0080
    // FUNCTION: GAMEMD 0x6EDAF0
    void FUN_006EDAF0(Arg1_006EDAF0* a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_006EDAF0, unknown_80) == 0x80);

struct Obj_006EDB20
{
    char unknown_00[0x80];
    unsigned char unknown_80;   // +0x0080
    // FUNCTION: GAMEMD 0x6EDB20
    void FUN_006EDB20(Arg1_006EDB20* a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_006EDB20, unknown_80) == 0x80);

struct Obj_006EDE10
{
    char unknown_00[0x28];
    Obj_006EDE10_28* unknown_28;   // +0x0028
    char unknown_2C[0x54];
    unsigned char unknown_80;   // +0x0080
    // FUNCTION: GAMEMD 0x6EDE10
    void FUN_006EDE10(Arg1_006EDE10* a1, int a2);
};
GG_STATIC_ASSERT(offsetof(Obj_006EDE10, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(Obj_006EDE10, unknown_80) == 0x80);

struct Obj_006EDE10_28
{
    // FUNCTION: GAMEMD 0x6915A0
    void FUN_006915A0(int);
};

struct Obj_006EDE60
{
    char unknown_00[0x80];
    unsigned char unknown_80;   // +0x0080
};
GG_STATIC_ASSERT(offsetof(Obj_006EDE60, unknown_80) == 0x80);

struct Obj_006EDEC0
{
    char unknown_00[0x80];
    unsigned char unknown_80;   // +0x0080
};
GG_STATIC_ASSERT(offsetof(Obj_006EDEC0, unknown_80) == 0x80);


void FUN_006EDE60(Obj_006EDE60* a1, int a2, int a3, int a4);
void FUN_006EDEC0(Obj_006EDEC0* a1, int a2, Arg1_006EDEC0* a3, int a4);


#include <stddef.h>
#include "../core/vector_class.h"
#include "../_rt/gg_static_assert.h"

// LIBRARY: GAMEMD 0x7C8D20 -- CRT case-insensitive string compare (cdecl, two pointers).
extern "C" int __cdecl strcmpi(const char* a, const char* b);

struct Type_006EE230 {
    unsigned char unknown_00[0x24];
    char unknown_24[1];
};
GG_STATIC_ASSERT(offsetof(Type_006EE230, unknown_24) == 0x24);

struct Child_006EE230 {
    virtual void vf_00();
    virtual void vf_01();
    virtual void vf_02();
    virtual void vf_03();
    virtual void vf_04();
    virtual void vf_05();
    virtual void vf_06();
    virtual void vf_07();
    virtual void vf_08();
    virtual void vf_09();
    virtual void vf_10();
    virtual int vf_11();
    virtual void vf_12();
    virtual void vf_13();
    virtual void vf_14();
    virtual void vf_15();
    virtual void vf_16();
    virtual void vf_17();
    virtual void vf_18();
    virtual void vf_19();
    virtual void vf_20();
    virtual void vf_21();
    virtual void vf_22();
    virtual void vf_23();
    virtual void vf_24();
    virtual void vf_25();
    virtual void vf_26();
    virtual void vf_27();
    virtual void vf_28();
    virtual void vf_29();
    virtual void vf_30();
    virtual void vf_31();
    virtual void vf_32();
    virtual Type_006EE230* vf_33();
    unsigned char unknown_04[0x5D4];
    Child_006EE230* unknown_5D8;
    unsigned char unknown_5DC[0xE8];
    void* unknown_6C4;
};
GG_STATIC_ASSERT(offsetof(Child_006EE230, unknown_5D8) == 0x5D8);
GG_STATIC_ASSERT(offsetof(Child_006EE230, unknown_6C4) == 0x6C4);

struct Lookup_00747370 {
    // FUNCTION: GAMEMD 0x747370 (decl; reloc) -- __thiscall, returns an index.
    int FUN_00747370();
};

extern VectorClass<void*> DAT_00A83CE0;

struct Owner_006EE230 {
    unsigned char unknown_00[0x54];
    Child_006EE230* unknown_54;
    unsigned char unknown_58[0x28];
    bool unknown_80;
    void FUN_006EE230(int a, int b);
    void FUN_006EE2A0(int a, int b);
};
GG_STATIC_ASSERT(offsetof(Owner_006EE230, unknown_54) == 0x54);
GG_STATIC_ASSERT(offsetof(Owner_006EE230, unknown_80) == 0x80);

extern Lookup_00747370 DAT_00842DCC;
extern char DAT_00842DD4[];

extern char DAT_00842DCC_name[];
extern Lookup_00747370 DAT_00842DD4_obj;

#include "team_class_add_member_methods.h"
#include "../_layout/object_class.h"

#include "team_class_methods.h"
#include "../_layout/anim_class.h"
#include "../_layout/anim_type_class.h"
#include "../_layout/script_type_class.h"

#include "team_class_missing_members_methods.h"

#include "team_class_mission_target_methods.h"

#include "../core/deleting_dtor_sweep.h"
#include "../network/transport/winsock_interface_class.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

const char* FUN_0048E030(unsigned int index);
const char* FUN_0048E090(unsigned int index);

#include "../_layout/obj_00477020.h"

#include "../_layout/obj_004770b0.h"

#include "../_layout/obj_005175e0.h"

#include "../_layout/rec_00549b50.h"
#include "../_layout/obj_00549b50.h"

#include "../_layout/obj_006ea4f0.h"

#include "../_layout/obj_007719c0.h"

// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F46F0
extern const double DAT_007F46F0;
// GLOBAL: GAMEMD 0xB0E950
extern double DAT_00B0E950;

// SYNTHETIC: GAMEMD 0x006E88B0
// dynamic initializer for DAT_00B0E9A0

// GLOBAL: GAMEMD 0x00B0E9A0
double DAT_00B0E9A0 = DAT_00B0E950 / DAT_007F46F0;

// SYNTHETIC: GAMEMD 0x006E88D0
// dynamic initializer for DAT_00B0E988

// GLOBAL: GAMEMD 0x00B0E988
double DAT_00B0E988 = DAT_007E1718 / DAT_00B0E9A0;

#include "../_layout/ai_trigger_type_class.h"
#include "../_layout/team_type_class.h"
#include "../_layout/house_class.h"
#include "../_layout/tag_class.h"
#include "../core/vector_class_operations.h"

// GLOBAL: GAMEMD 0x8B4150 -- AnimTypeClass::Array.
extern DynamicVectorClass<AnimTypeClass*> DAT_008B4150;

// GLOBAL: GAMEMD 0xA8E9A0
extern unsigned char DAT_00A8E9A0;
// GLOBAL: GAMEMD 0xB0F6F0
extern DynamicVectorClass<AbstractClass*> DAT_00B0F6F0;
// GLOBAL: GAMEMD 0xB0F720
extern DynamicVectorClass<AbstractClass*> DAT_00B0F720;
// GLOBAL: GAMEMD 0xB0F670
extern DynamicVectorClass<AbstractClass*> DAT_00B0F670;
// GLOBAL: GAMEMD 0xB0F618
extern DynamicVectorClass<AbstractClass*> DAT_00B0F618;
// GLOBAL: GAMEMD 0x8B40E8
extern DynamicVectorClass<TeamClass*> DAT_008B40E8;
GG_STATIC_ASSERT(offsetof(TeamClass, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(TeamClass, unknown_70) == 0x70);
GG_STATIC_ASSERT(offsetof(TeamClass, unknown_74) == 0x74);
GG_STATIC_ASSERT(offsetof(TeamClass, unknown_84) == 0x84);
GG_STATIC_ASSERT(offsetof(TeamTypeClass, Flag_F6) == 0xF6);
GG_STATIC_ASSERT(offsetof(HouseClass, BaseDefenseTeamCount) == 0x566C);
GG_STATIC_ASSERT(sizeof(((HouseClass*)0)->BaseDefenseTeamCount) == 4);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->unknown_2C) == 4);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->unknown_70) == 4);
GG_STATIC_ASSERT(sizeof(((TeamTypeClass*)0)->Flag_F6) == 1);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->unknown_74) == 1);
GG_STATIC_ASSERT(sizeof(((TeamClass*)0)->unknown_84) == 1);

// FUNCTION: GAMEMD 0x6E8DE0
TeamClass::~TeamClass()
{
    for (int i = 0; i < AITriggerTypes.Count; ++i) {
        AITriggerTypeClass* trigger = AITriggerTypes.Items[i];
        if (trigger->unknown_DC == Type) {
            if (unknown_84) trigger->RegisterSuccess();
            else trigger->RegisterFailure();
        }
    }
    if (unknown_2C && Type && Type->Flag_F6)
        --unknown_2C->BaseDefenseTeamCount;
    if (DAT_00A8E9A0 && Type) {
        while (FirstUnit) LiberateMember(FirstUnit, -1, 0);
        --Type->InstanceCount;
        if (unknown_70) {
            if (!unknown_70->InstanceCount) unknown_70->Destroy();
            unknown_70 = 0;
        }
    }
    AnnounceExpiredPointer(1);
    DAT_00B0F6F0.RemoveItem(this);
    DAT_00B0F720.RemoveItem(this);
    DAT_00B0F670.RemoveItem(this);
    DAT_00B0F618.RemoveItem(this);
    DAT_008B40E8.RemoveItem(this);
    if (unknown_74 && Type) delete Type;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6E9050  TeamClass::AssignMissionTarget
//
// Switch the team's target. Members still aimed at or heading for the old
// one are told to guard (mission 5) and have that target or destination
// cleared; the secondary at +0x40 follows when it tracked the old target or
// was empty. A cell target off the usable map flags the team and sends every
// member home; an on-map cell clears the flag. The member cursor is loaded
// before the old-target null test, as retail schedules it.
void Team_006E9050::AssignMissionTarget(Abstract_006E9050* target)
{
    if (target != Target) {
        Foot_006E9050* member = FirstUnit;
        if (Target != 0)
        for (; member != 0; member = member->NextTeamMember) {
            Abstract_006E9050* old = Target;
            bool aimed = member->Target == old;
            bool heading = member->Destination == old;
            if (aimed || heading) {
                (member->*member->Vptr->QueueMission)(5, false);
                if (heading)
                    (member->*member->Vptr->SetDestination)(0, true);
                if (aimed)
                    (member->*member->Vptr->SetTarget)(0);
            }
        }
    }

    if (At_40 == Target || At_40 == 0)
        At_40 = target;
    Target = target;

    if (target != 0 && (target->*target->Vptr->WhatAmI)() == 0xB) {
        if (!MapInstance_006E9050.IsWithinUsableArea(target, true)) {
            Foot_006E9050* member = FirstUnit;
            At_82 = 1;
            for (; member != 0; member = member->NextTeamMember)
                (member->*member->Vptr->SetDestination)(0, true);
        } else {
            At_82 = 0;
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x006EA4F0
void Obj_006EA4F0::FUN_006EA4F0(int a)
{
    FUN_006EA500(a, 1);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6EA500
//
// Recruit a unit into the team. The fit test hands back the task-force slot
// the unit fills; the unit is freed from any team it already belongs to, the
// slot count is bumped (unless the caller asked not to), the unit is pushed on
// the member chain (marking whether it is the last one), takes the team's
// group, and gets the team's trigger unless its type opts out. The object and
// threat totals are updated, the lazily-built pair at +0x34 is filled if still
// empty, the two recalc bytes are raised and the unit inherits the type's byte
// at +0xF5.
bool Team_006EA500::AddMember(Foot_006EA500* member, bool flag)
{
    if (member == 0) {
        return false;
    }

    int slot;
    if (!this->FUN_006EA610(member, &slot, flag)) {
        return false;
    }

    if (member->Team != 0) {
        member->Team->LiberateMember(member, -1, false);
    }

    if (!flag) {
        this->CountObjects[slot]++;
    }

    member->At_689 = this->FirstUnit == 0;
    member->NextTeamMember = this->FirstUnit;
    this->FirstUnit = member;
    member->Team = this;
    member->Group = this->Type->GetGroup();

    if (this->Trigger != 0) {
        if (this->Type->At_B3 == 0
            || (member->*member->Vtbl->GetTechnoType)()->At_5E0 > 0) {
            // Retail passes member in ECX unchanged to ObjectClass::AttachTrigger.
            reinterpret_cast<ObjectClass*>(member)->AttachTrigger(
                static_cast<TagClass*>(this->Trigger));
        }
    }

    this->TotalObjects = this->TotalObjects + 1;
    this->TotalThreatValue += (member->*member->Vtbl->At_2C0)();
    if (this->At_34 == 0) {
        this->FUN_006EAEE0(&this->At_34, &this->At_38);
    }

    this->At_7E = 1;
    this->At_7D = 1;
    member->At_422 = this->Type->At_F5;
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
GG_STATIC_ASSERT(offsetof(FootClass, NextTeamMember) == 0x5D8);
GG_STATIC_ASSERT(sizeof(((FootClass*)0)->NextTeamMember) == 4);

// FUNCTION: GAMEMD 0x6EAE60
void TeamClass::vf_10(void* target, bool removed)
{
    if (target == unknown_70) unknown_70 = 0;
    if (target == FirstUnit && removed) FirstUnit = FirstUnit->NextTeamMember;
    if (target == unknown_2C) unknown_2C = 0;
    if (target == Target28) Target28 = 0;
    if (unknown_40 == target) unknown_40 = 0;
    if (unknown_3C == target) unknown_3C = 0;
    if (Member34 == target) Member34 = 0;
    if (Type == target) Type = 0;
    if (unknown_38 == target) unknown_38 = 0;
    if (unknown_44 == target) unknown_44 = 0;
    if (unknown_30 == target) unknown_30 = 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6EC3A0  (__thiscall)
// Drop the team's mission target, then walk the member list flagging each as
// scan-limited.  For every member it fires the slot-242 (byte 0x3C8) virtual
// with argument 0, then sets IsScanLimited = 1.
void TeamClass::ScanLimit()
{
    this->AssignMissionTarget(0);

    for (FootClass* member = this->FirstUnit; member; member = member->NextTeamMember)
    {
        member->vf_242(0);
        member->IsScanLimited = 1;
    }
}

#include <new>
#include "../_layout/swizzle_manager_class.h"

// FUNCTION: GAMEMD 0x6EC450
HRESULT __stdcall TeamClass::Load(IStream* pStm)
{
    HRESULT hr = AbstractClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }

    if (this) {
        // Native reuses the stream argument's stack home as the no-init token.
        AbstractNoInit& noInit = *reinterpret_cast<AbstractNoInit*>(&pStm);
        new (this) TeamClass(noInit);
    }

    DAT_00B0C110.SwizzleManagerClass::vf_4(&Type);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Target28);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_2C);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_70);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&FirstUnit);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_38);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_40);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&Member34);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_3C);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_30);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_44);
    return S_OK;
}

#include "../_layout/obj_004a1d30.h"

// FUNCTION: GAMEMD 0x6EC5A0
void TeamClass::vf_13(Obj_004A1D30* crc)
{
    AbstractClass::vf_13(crc);
    crc->FUN_004A1D50(Type->vf_rtti_4());
    crc->FUN_004A1D50(unknown_2C->vf_rtti_4());
    if (unknown_38) crc->FUN_004A1D50(unknown_38->vf_rtti_4());
    crc->FUN_004A1D50(unknown_48);
    crc->FUN_004A1D50(unknown_4C);
    if (FirstUnit) crc->FUN_004A1D50(FirstUnit->vf_rtti_4());
    crc->FUN_004A1D50(unknown_58.GetTimeLeft());
    crc->FUN_004A1D50(unknown_64.GetTimeLeft());
    if (unknown_70) crc->FUN_004A1D50(unknown_70->vf_rtti_4());
    crc->FUN_004A1CA0(Flag77);
    crc->FUN_004A1CA0(Flag78);
    crc->FUN_004A1CA0(unknown_79);
    crc->FUN_004A1CA0(Flag7A);
    crc->FUN_004A1CA0(Flag7B);
    crc->FUN_004A1CA0(unknown_7C);
    crc->FUN_004A1CA0(unknown_7D);
    crc->FUN_004A1CA0(unknown_7E);
    crc->FUN_004A1CA0(Flag7F);
    crc->FUN_004A1CA0(Done);
    crc->FUN_004A1CA0(Flag82);
    crc->FUN_004A1CA0(unknown_83);
    crc->FUN_004A1DE0(unknown_88, sizeof(unknown_88));
}



// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6EDA90
// Calls other functions.
void Obj_006EDA90::FUN_006EDA90(Arg1_006EDA90* a1, int a2)
{
    DAT_00A8B230->FUN_00689670(a1->unknown_04, 1);
    unknown_80 = 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6EDAC0
// Calls other functions.
void Obj_006EDAC0::FUN_006EDAC0(Arg1_006EDAC0* a1, int a2)
{
    DAT_00A8B230->FUN_00689670(a1->unknown_04, 0);
    unknown_80 = 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6EDAF0
// Calls other functions.
void Obj_006EDAF0::FUN_006EDAF0(Arg1_006EDAF0* a1, int a2)
{
    DAT_00A8B230->FUN_00689910(a1->unknown_04, 1);
    unknown_80 = 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6EDB20
// Calls other functions.
void Obj_006EDB20::FUN_006EDB20(Arg1_006EDB20* a1, int a2)
{
    DAT_00A8B230->FUN_00689910(a1->unknown_04, 0);
    unknown_80 = 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// Native 6EDB50 entry reads these canonical object fields and COM slot 4.
// GLOBAL: GAMEMD 0xA8E7AC
extern int DAT_00A8E7AC;
// Native target 0x40DD70 (declaration; native ECX input).
// The body is annotated in core/whatami_dispatch_methods.cpp.
// Physical ABI proposal; the differently typed existing provider is not unified here.
TechnoClass* FUN_0040DD70(AbstractClass* object);
void __stdcall _com_issue_error(long);
GG_STATIC_ASSERT(offsetof(FootClass, IsInitiated) == 0x689);
GG_STATIC_ASSERT(sizeof(((FootClass*)0)->IsInitiated) == 1);
GG_STATIC_ASSERT(sizeof(((FootClass*)0)->Locomotor) == 4);
GG_STATIC_ASSERT(sizeof(((FootClass*)0)->NextTeamMember) == 4);
GG_STATIC_ASSERT(sizeof(((TechnoClass*)0)->Target) == 4);

// FUNCTION: GAMEMD 0x6EDB50
void TeamClass::FUN_006EDB50(ScriptActionNode*, bool)
{
    this->FUN_006EAEE0(&this->Member34, &this->unknown_38);
    this->unknown_40 = this->Member34;
    this->FUN_006EBAD0();
    TechnoClass* target = FUN_0040DD70(this->Member34);
    if (target) {
        for (FootClass* foot = this->FirstUnit; foot; foot = foot->NextTeamMember) {
            if (foot->IsAlive && foot->Health && (DAT_00A8E7AC || !foot->InLimbo) &&
                (foot->IsInitiated || foot->vf_11() == 2)) {
                if (foot->Target && foot->Target != target->Target) foot->vf_242(0);
                if (target->Target) {
                    if (!foot->Locomotor) _com_issue_error(0x80004003);
                    if (!static_cast<ILocomotion*>(foot->Locomotor)->IsMoving() &&
                        foot->IsArmed() && foot->vf_97() == 5) {
                        foot->vf_122(1, false);
                        foot->vf_242(target->Target);
                    }
                }
            }
        }
    }
}

// FUNCTION: GAMEMD 0x6EDE10
// Calls other functions.
void Obj_006EDE10::FUN_006EDE10(Arg1_006EDE10* a1, int a2)
{
    unknown_28->FUN_006915A0(a1->unknown_04 - 2);
    unknown_80 = 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6EDE40
// Calls other functions.
void FUN_006EDE40(Obj_006EDE40* a1, int a2, int a3, int a4)
{
    FUN_004FC9E0(DAT_00A83D4C, a2, 0);
    a1->unknown_80 = 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6EDE60
// Calls other functions.
void FUN_006EDE60(Obj_006EDE60* a1, int a2, int a3, int a4)
{
    FUN_004FCBD0(DAT_00A83D4C, a2, 0);
    a1->unknown_80 = 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6EDE80
// Stores its argument in a member; pops its stack arguments.
void Obj_006EDE80::FUN_006EDE80(int a1, int a2)
{
    unknown_80 = 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6EDEC0
// Calls other functions.
void FUN_006EDEC0(Obj_006EDEC0* a1, int a2, Arg1_006EDEC0* a3, int a4)
{
    FUN_005BF260(a3->unknown_04, -1, 1, 1, 1);
    a1->unknown_80 = 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6EDEF0
// Calls other functions.
void FUN_006EDEF0(Obj_006EDEF0* a1, int a2, Arg1_006EDEF0* a3, int a4)
{
    FUN_00720B20(DAT_00A83D10, a2, a3->unknown_04);
    a1->unknown_80 = 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6EDF90
// Stores several members; pops its stack arguments.
void Obj_006EDF90::FUN_006EDF90(int a1, int a2)
{
    unknown_2C->unknown_1EE = true;
    unknown_80 = true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6EDFB0
// Stores several members; pops its stack arguments.
void Obj_006EDFB0::FUN_006EDFB0(int a1, int a2)
{
    unknown_2C->unknown_250 = 4;
    unknown_80 = 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6EE1B0
// Calls other functions.
void FUN_006EE1B0(Obj_006EE1B0* a1, int a2, int a3, int a4)
{
    FUN_00577BB0(DAT_0087F7E8, a2, 0);
    a1->unknown_80 = 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6EE1D0
// Calls other functions.
void FUN_006EE1D0(Obj_006EE1D0* a1, int a2, int a3, int a4)
{
    FUN_00577F30(DAT_0087F7E8, a2, 0);
    a1->unknown_80 = 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x006EE230
void Owner_006EE230::FUN_006EE230(int a, int b)
{
    for (Child_006EE230* child = unknown_54; child != 0; child = child->unknown_5D8) {
        if (child->vf_11() == 1) {
            const char* name = child->vf_33()->unknown_24;
            if (strcmpi(name, DAT_00842DD4) == 0)
                child->unknown_6C4 = DAT_00A83CE0[DAT_00842DCC.FUN_00747370()];
        }
    }
    unknown_80 = true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x006EE2A0
void Owner_006EE230::FUN_006EE2A0(int a, int b)
{
    for (Child_006EE230* child = unknown_54; child != 0; child = child->unknown_5D8) {
        if (child->vf_11() == 1) {
            const char* name = child->vf_33()->unknown_24;
            if (strcmpi(name, DAT_00842DCC_name) == 0)
                child->unknown_6C4 = DAT_00A83CE0[DAT_00842DD4_obj.FUN_00747370()];
        }
    }
    unknown_80 = true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6EF4D0
//
// Fill `out` with the techno types the team still needs: every taskforce
// entry's type is appended Amount times, then each live member's type strikes
// one copy out again.
//
// The taskforce is re-read through the team type on every access (the inlined
// AddItem calls a virtual, so nothing is hoisted); the per-entry amount is a
// local, which is what lets the inner loop count down through a spilled slot.
void Team_006EF4D0::GetTaskForceMissingMemberTypes(TypeVector_006EF4D0* out)
{
    int i;
    int j;

    for (i = 0; i < this->Type->TaskForce->CountEntries; i++) {
        TechnoType_006EF4D0* type = this->Type->TaskForce->Entries[i].Type;
        int amount = this->Type->TaskForce->Entries[i].Amount;
        for (j = 0; j < amount; j++) {
            out->AddItem(type);
        }
    }

    for (Foot_006EF4D0* member = this->FirstUnit; member != 0;
         member = member->NextTeamMember) {
        TechnoType_006EF4D0* type = (member->*member->Vtbl->GetTechnoType)();
        int index = out->FindItemIndex(type);
        if (index != -1) {
            out->RemoveItem(index);
        }
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6EF610
// Uses a packed ScriptActionNode argument to build the selected animation for
// each current team member, then marks the team update complete.
void TeamClass::FUN_006EF610(ScriptActionNode* action, bool enabled)
{
    int packed = action->Argument;
    int typeIndex = packed & 0xFFFF;

    if (enabled && typeIndex >= 0 && typeIndex < DAT_008B4150.Count) {
        FootClass* member = FirstUnit;
        int loopCount = packed >> 16;
        loopCount &= 0xFFFF;
        AnimTypeClass* type = DAT_008B4150.Items[typeIndex];

        while (member != 0) {
            AnimClass* animation = new AnimClass(type, member->vf_18(), 0,
                                                 loopCount, 0x600, 0, false);
            if (animation != 0) {
                animation->FUN_00424B50(member);
            }
            member = member->NextTeamMember;
        }
    }

    Done = true;
}

// FUNCTION: GAMEMD 0x6F0430
// Returns a constant. Vtable slot 12 of TeamClass (RTTI).
int TeamClass::vf_12()
{
    return 0xA0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x6F0440
// Returns a constant. Vtable slot 11 of TeamClass (RTTI).
int TeamClass::vf_11()
{
    return 0x22;
}

// SYNTHETIC: GAMEMD 0x6F0450 -- compiler-generated TeamClass scalar deleting destructor.

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA83D4C
int DAT_00A83D4C;
// GLOBAL: GAMEMD 0x7F46F0
extern const double DAT_007F46F0 = 60.0;
// GLOBAL: GAMEMD 0xA83CE0
VectorClass<void*> DAT_00A83CE0;
// END defined globals
