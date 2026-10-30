// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Team mission action handlers read off the user's retail gamemd.exe v1.001 with the local Ghidra
//   CLI at the address in each annotation. Each takes (this = team, action record*, first-time flag).
//   The team, the record and the helper objects are placeholder views verified by the offsets
//   asserted below.
//   Address index: 0x6EC250, 0x6EC770, 0x6EC9A0, 0x6ECA70, 0x6ECE60, 0x6ECFB0, 0x6ED030, 0x6ED770.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/frame_timer.h"
#include "../_layout/cell.h"
#include "../_layout/map_0087f7e8.h"

// The action record: only the parameter at +0x04.
struct MissionArg_R15
{
    unsigned char unknown_00[4];
    int unknown_04;   // +0x04
};
GG_STATIC_ASSERT(offsetof(MissionArg_R15, unknown_04) == 0x4);

class CellClass;


// The 0x30-byte helper the 0x6ED030 handler installs at +0x28 of the team.
class MissionHelper_006913C0
{
public:
    // FUNCTION: GAMEMD 0x6913C0 (decl; reloc)
    MissionHelper_006913C0(void* arg);
    // FUNCTION: GAMEMD 0x691590 (decl; reloc)
    void FUN_00691590();
    virtual void vf_0();
    virtual void vf_1();
    virtual void vf_2();
    virtual void vf_3();
    virtual void vf_4();
    virtual void vf_5();
    virtual void vf_6();
    virtual void vf_7();
    virtual ~MissionHelper_006913C0();   // slot 8 (+0x20)
    unsigned char unknown_04[0x2C];
};
GG_STATIC_ASSERT(sizeof(MissionHelper_006913C0) == 0x30);

// GLOBAL: GAMEMD 0x8B41CC -- the table the 0x6ED030 handler indexes by the parameter.
extern void** DAT_008B41CC;
// GLOBAL: GAMEMD 0xA8ECA4 -- the table the 0x6ECFB0 handler indexes by the parameter.
extern void** DAT_00A8ECA4;

// A member's type, as far as the dword at +0x684.
struct MemberType_R15
{
    unsigned char unknown_00[0x684];
    int unknown_684;   // +0x684
};
GG_STATIC_ASSERT(offsetof(MemberType_R15, unknown_684) == 0x684);

class TeamMember_R15
{
public:
    virtual void vf_0();
    virtual void vf_1();
    virtual void vf_2();
    virtual void vf_3();
    virtual void vf_4();
    virtual void vf_5();
    virtual void vf_6();
    virtual void vf_7();
    virtual void vf_8();
    virtual void vf_9();
    virtual void vf_10();
    virtual void vf_11();
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
    virtual MemberType_R15* vf_33();
    unsigned char unknown_04[0x2F8];
    int unknown_2FC;                // +0x2FC
    unsigned char unknown_300[0x2D8];
    TeamMember_R15* unknown_5D8;    // +0x5D8
};
GG_STATIC_ASSERT(offsetof(TeamMember_R15, unknown_2FC) == 0x2FC);
GG_STATIC_ASSERT(offsetof(TeamMember_R15, unknown_5D8) == 0x5D8);

// The 0xA0-byte team the 0x6ECFB0 handler splits the members off to.
class TeamPeer_006E8A90
{
public:
    // FUNCTION: GAMEMD 0x6E8A90 (decl; reloc)
    TeamPeer_006E8A90(void* type, int house, int flag);
    // FUNCTION: GAMEMD 0x6EA500 (decl; reloc)
    void FUN_006EA500(TeamMember_R15* member, int flag);
    unsigned char unknown_00[0xA0];
};
GG_STATIC_ASSERT(sizeof(TeamPeer_006E8A90) == 0xA0);

// A mission target (a cell or a building): slot 11 reports its kind; +0x140 holds the cell flags.
class Target_R15
{
public:
    virtual void vf_0();
    virtual void vf_1();
    virtual void vf_2();
    virtual void vf_3();
    virtual void vf_4();
    virtual void vf_5();
    virtual void vf_6();
    virtual void vf_7();
    virtual void vf_8();
    virtual void vf_9();
    virtual void vf_10();
    virtual int vf_11();
    unsigned char unknown_04[0x13C];
    unsigned int unknown_140;   // +0x140
    // FUNCTION: GAMEMD 0x47C5A0 (decl; reloc) -- the occupant of a cell.
    Target_R15* FUN_0047C5A0(int* out, bool flag);
};
GG_STATIC_ASSERT(offsetof(Target_R15, unknown_140) == 0x140);

// The scenario (GLOBAL 0xA8B230), as far as the cell lookup 0x68BCE0.
struct MissionScenario_R15
{
    // FUNCTION: GAMEMD 0x68BCE0 (decl; reloc)
    Target_R15* FUN_0068BCE0(int index);
};
// GLOBAL: GAMEMD 0xA8B230
extern MissionScenario_R15* DAT_00A8B230_MissionR15;

struct TeamType_R15
{
    unsigned char unknown_00[0xB4];
    int unknown_B4;   // +0xB4
};
GG_STATIC_ASSERT(offsetof(TeamType_R15, unknown_B4) == 0xB4);

// The rules (GLOBAL 0x8871E0), as far as the double at +0x14E8.
struct Rules_R15
{
    unsigned char unknown_00[0x14E8];
    double unknown_14E8;   // +0x14E8
};
GG_STATIC_ASSERT(offsetof(Rules_R15, unknown_14E8) == 0x14E8);
// GLOBAL: GAMEMD 0x8871E0
extern Rules_R15* DAT_008871E0_R15;
// GLOBAL: GAMEMD 0x8B40EC / 0x8B40F8 -- TeamClass array items and count.
class Team_R15;
extern Team_R15** DAT_008B40EC;
extern int DAT_008B40F8;

class Team_R15
{
public:
    virtual void vf_0();
    virtual void vf_1();
    virtual void vf_2();
    virtual void vf_3();
    virtual void vf_4();
    virtual void vf_5();
    virtual void vf_6();
    virtual void vf_7();
    virtual ~Team_R15();   // slot 8 (+0x20)

    unsigned char unknown_04[0x20];
    struct TeamType_R15* unknown_24;      // +0x24
    MissionHelper_006913C0* unknown_28;   // +0x28
    int unknown_2C;                       // +0x2C
    unsigned char unknown_30[0xC];
    Target_R15* unknown_3C;               // +0x3C the mission target
    unsigned char unknown_40[0x14];
    TeamMember_R15* unknown_54;           // +0x54 first member
    CDTimerClass unknown_58;              // +0x58
    CDTimerClass unknown_64;              // +0x64
    unsigned char unknown_70[0xD];
    bool unknown_7D;                      // +0x7D
    bool unknown_7E;                      // +0x7E
    bool unknown_7F;                      // +0x7F
    bool unknown_80;                      // +0x80 the action is done
    unsigned char unknown_81[2];
    bool unknown_83;                      // +0x83

    // FUNCTION: GAMEMD 0x6E9050 (decl; reloc) -- assigns the team's mission target.
    void FUN_006E9050(void* target);
    // FUNCTION: GAMEMD 0x6EBAD0 (decl; reloc)
    void FUN_006EBAD0();
    // FUNCTION: GAMEMD 0x6EB870 (decl; reloc)
    void FUN_006EB870();
    // FUNCTION: GAMEMD 0x6EA870 (decl; reloc) -- takes a member out of the team.
    void FUN_006EA870(TeamMember_R15* member, int a, int b);

    // FUNCTION: GAMEMD 0x6EB490 (decl; reloc)
    void FUN_006EB490();

    void SetCellTarget(MissionArg_R15* arg, bool first);    // 0x6EC770
    void ClearIfBusy(MissionArg_R15* arg, bool first);      // 0x6EC9A0
    void ClearIfBuilding(MissionArg_R15* arg, bool first);  // 0x6ECA70
    void StepToOccupant(MissionArg_R15* arg, bool first);   // 0x6ECE60


    void SplitOff(MissionArg_R15* arg, bool first);         // 0x6ECFB0
    void InstallHelper(MissionArg_R15* arg, bool first);    // 0x6ED030
    void WaitFrames(MissionArg_R15* arg, bool first);       // 0x6ED770
};
GG_STATIC_ASSERT(offsetof(Team_R15, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(Team_R15, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(Team_R15, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(Team_R15, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(Team_R15, unknown_54) == 0x54);
GG_STATIC_ASSERT(offsetof(Team_R15, unknown_58) == 0x58);
GG_STATIC_ASSERT(offsetof(Team_R15, unknown_64) == 0x64);
GG_STATIC_ASSERT(offsetof(Team_R15, unknown_7F) == 0x7F);
GG_STATIC_ASSERT(offsetof(Team_R15, unknown_80) == 0x80);
GG_STATIC_ASSERT(offsetof(Team_R15, unknown_83) == 0x83);

// GLOBAL: GAMEMD 0xA8ED84 is the frame counter (frame_timer.h).

// FUNCTION: GAMEMD 0x6EC770
// First time in: point the team at the cell encoded in the parameter (128 columns per row).
void Team_R15::SetCellTarget(MissionArg_R15* arg, bool first)
{
    if (first) {
        CellStruct cell;
        cell.X = (short)(arg->unknown_04 % 128);
        cell.Y = (short)(arg->unknown_04 / 128);
        FUN_006E9050(DAT_0087F7E8.FUN_005657A0(&cell));
    }
    FUN_006EBAD0();
}

// FUNCTION: GAMEMD 0x6ECFB0
// Move every member into a fresh team of the parameter's type, then dissolve this one.
void Team_R15::SplitOff(MissionArg_R15* arg, bool first)
{
    TeamPeer_006E8A90* peer = new TeamPeer_006E8A90(DAT_00A8ECA4[arg->unknown_04], unknown_2C, 0);
    while (unknown_54 != 0) {
        TeamMember_R15* member = unknown_54;
        FUN_006EA870(member, -1, 0);
        peer->FUN_006EA500(member, 0);
    }
    delete this;
}

// FUNCTION: GAMEMD 0x6ED030
// Replace the team's helper object with a fresh one built from the parameter's table entry.
void Team_R15::InstallHelper(MissionArg_R15* arg, bool first)
{
    if (unknown_28)
        delete unknown_28;
    unknown_28 = new MissionHelper_006913C0(DAT_008B41CC[arg->unknown_04]);
    unknown_28->FUN_00691590();
}

// FUNCTION: GAMEMD 0x6ED770
// First time in: start a wait of (parameter x 15) frames; done once the wait has run out.
void Team_R15::WaitFrames(MissionArg_R15* arg, bool first)
{
    if (first) {
        CDTimerClass timer(arg->unknown_04 * 15);
        unknown_58 = timer;
    }
    FUN_006EB870();
    if (unknown_58.GetTimeLeft() == 0)
        unknown_80 = true;
}

// FUNCTION: GAMEMD 0x6EC9A0
// First time in: aim at the occupant of the waypoint cell. Keep stepping while a member is still
// busy (its type's count is positive and its own count is not); else drop the target and finish.
void Team_R15::ClearIfBusy(MissionArg_R15* arg, bool first)
{
    if (first) {
        Target_R15* cell = DAT_00A8B230_MissionR15->FUN_0068BCE0(arg->unknown_04);
        if (cell != 0 && cell->vf_11() == 0xB) {
            int tmp[2];
            tmp[0] = 0;
            tmp[1] = 0;
            Target_R15* occupant = cell->FUN_0047C5A0(tmp, ((cell->unknown_140 >> 8) & 1) != 0);
            if (occupant != 0)
                cell = occupant;
        }
        FUN_006E9050(cell);
    }
    if (unknown_3C != 0) {
        for (TeamMember_R15* m = unknown_54; m != 0; m = m->unknown_5D8) {
            int typeCount = m->vf_33()->unknown_684;
            if (typeCount <= 0 || m->unknown_2FC > 0) {
                FUN_006EB490();
                return;
            }
        }
    }
    FUN_006E9050(0);
    unknown_80 = true;
}

// FUNCTION: GAMEMD 0x6ECA70
// As 0x6EC9A0, but the first-time target is the building occupying the waypoint cell (else none).
void Team_R15::ClearIfBuilding(MissionArg_R15* arg, bool first)
{
    if (first) {
        Target_R15* target = DAT_00A8B230_MissionR15->FUN_0068BCE0(arg->unknown_04);
        if (target == 0 || target->vf_11() != 0xB) {
            target = 0;
        } else {
            int tmp[2];
            tmp[0] = 0;
            tmp[1] = 0;
            target = target->FUN_0047C5A0(tmp, ((target->unknown_140 >> 8) & 1) != 0);
            if (target == 0 || target->vf_11() != 6)
                target = 0;
        }
        FUN_006E9050(target);
    }
    if (unknown_3C != 0) {
        for (TeamMember_R15* m = unknown_54; m != 0; m = m->unknown_5D8) {
            int typeCount = m->vf_33()->unknown_684;
            if (typeCount <= 0 || m->unknown_2FC > 0) {
                FUN_006EB490();
                return;
            }
        }
    }
    FUN_006E9050(0);
    unknown_80 = true;
}

// The target as a cell, or null.
static __inline Target_R15* AsCell_R15(Target_R15* p)
{
    if (p == 0)
        return 0;
    return p->vf_11() == 0xB ? p : 0;
}

// FUNCTION: GAMEMD 0x6ECE60
// First time in: aim at the waypoint cell. If the target is a cell, retarget to its occupant and
// step; with no target at all, finish.
void Team_R15::StepToOccupant(MissionArg_R15* arg, bool first)
{
    if (first)
        FUN_006E9050(DAT_00A8B230_MissionR15->FUN_0068BCE0(arg->unknown_04));
    if (unknown_3C != 0 && unknown_3C->vf_11() == 0xB) {
        Target_R15* cellTarget = AsCell_R15(unknown_3C);
        int tmp[2] = {0, 0};
        Target_R15* occupant = cellTarget->FUN_0047C5A0(tmp, false);
        if (occupant == 0)
            return;
        FUN_006E9050(occupant);
    } else if (unknown_3C == 0) {
        FUN_006E9050(0);
        unknown_80 = true;
        return;
    }
    FUN_006EB490();
}

// FUNCTION: GAMEMD 0x6EC250
// PARTIAL: 89.7% -- identical instruction multiset; retail addresses the timer through an LEA of
// the slot at +0x64 where this build adds 0x64 to the team register.
// Dissolve every team of the house whose type is below the threshold, and arm its cool-down.
void __fastcall FUN_006EC250(int threshold, int house)
{
    for (int i = 0; i < DAT_008B40F8; i++) {
        Team_R15* team = DAT_008B40EC[i];
        if (team != 0 && house == team->unknown_2C && team->unknown_24->unknown_B4 < threshold) {
            while (team->unknown_54 != 0)
                team->FUN_006EA870(team->unknown_54, -1, 0);
            team->unknown_7E = true;
            team->unknown_7D = true;
            CDTimerClass timer((int)(DAT_008871E0_R15->unknown_14E8 * 900.0));
            team->unknown_83 = true;
            team->unknown_64 = timer;
        }
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x8B40F8
int DAT_008B40F8;
// GLOBAL: GAMEMD 0x8B41CC
void** DAT_008B41CC;
// GLOBAL: GAMEMD 0xA8ECA4
void** DAT_00A8ECA4;
// GLOBAL: GAMEMD 0xA8B230
MissionScenario_R15* DAT_00A8B230_MissionR15;
// END defined globals
