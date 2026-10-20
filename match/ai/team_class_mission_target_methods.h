// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, slots and offsets read off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x6E9050: the team's Target at +0x3C, the
//   dword at +0x40, FirstUnit at +0x54 and the byte at +0x82; each member's
//   Target at +0x2B4, Destination at +0x5A4 and NextTeamMember at +0x5D8;
//   member slots +0x1E8 (mission, bool), +0x480 (destination, bool) and
//   +0x3C8 (target); the target's WhatAmI slot +0x2C (0xB = cell); and
//   MapClass::IsWithinUsableArea(CellClass*, bool) at 0x578540 on the map
//   object 0x87F7E8. YRpp (consult-only, no LICENSE) names
//   AssignMissionTarget, Target, FirstUnit, NextTeamMember.
#ifndef GG_MATCH_AI_TEAM_CLASS_MISSION_TARGET_METHODS_H
#define GG_MATCH_AI_TEAM_CLASS_MISSION_TARGET_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct VtblA_006E9050;

struct Abstract_006E9050
{
    VtblA_006E9050* Vptr;   // +0x0000
};

typedef int (Abstract_006E9050::*Fn2C_006E9050)();

struct VtblA_006E9050
{
    char _pad000[0x2C];         // +0x0000
    Fn2C_006E9050 WhatAmI;      // +0x002C
};
GG_STATIC_ASSERT(offsetof(VtblA_006E9050, WhatAmI) == 0x2C);

struct VtblF_006E9050;

struct Foot_006E9050
{
    VtblF_006E9050* Vptr;                 // +0x0000
    char _pad0004[0x2B4 - 0x04];          // +0x0004
    Abstract_006E9050* Target;            // +0x02B4
    char _pad02B8[0x5A4 - 0x2B8];         // +0x02B8
    Abstract_006E9050* Destination;       // +0x05A4
    char _pad05A8[0x5D8 - 0x5A8];         // +0x05A8
    Foot_006E9050* NextTeamMember;        // +0x05D8
};
GG_STATIC_ASSERT(offsetof(Foot_006E9050, Target) == 0x2B4);
GG_STATIC_ASSERT(offsetof(Foot_006E9050, Destination) == 0x5A4);
GG_STATIC_ASSERT(offsetof(Foot_006E9050, NextTeamMember) == 0x5D8);

typedef void (Foot_006E9050::*Fn1E8_006E9050)(int mission, bool immediate);
typedef void (Foot_006E9050::*Fn480_006E9050)(Abstract_006E9050* dest, bool flag);
typedef void (Foot_006E9050::*Fn3C8_006E9050)(Abstract_006E9050* target);

struct VtblF_006E9050
{
    char _pad000[0x1E8];            // +0x0000
    Fn1E8_006E9050 QueueMission;    // +0x01E8
    char _pad1EC[0x3C8 - 0x1EC];    // +0x01EC
    Fn3C8_006E9050 SetTarget;       // +0x03C8
    char _pad3CC[0x480 - 0x3CC];    // +0x03CC
    Fn480_006E9050 SetDestination;  // +0x0480
};
GG_STATIC_ASSERT(offsetof(VtblF_006E9050, QueueMission) == 0x1E8);
GG_STATIC_ASSERT(offsetof(VtblF_006E9050, SetTarget) == 0x3C8);
GG_STATIC_ASSERT(offsetof(VtblF_006E9050, SetDestination) == 0x480);

struct Map_006E9050
{
    // FUNCTION: GAMEMD 0x578540 (decl; reloc) — MapClass::IsWithinUsableArea.
    bool IsWithinUsableArea(Abstract_006E9050* cell, bool checkLevel);
};
// GLOBAL: GAMEMD 0x87F7E8 — the map instance.
extern Map_006E9050 MapInstance_006E9050;

struct Team_006E9050
{
    char _pad0000[0x3C];            // +0x0000
    Abstract_006E9050* Target;      // +0x003C
    Abstract_006E9050* At_40;       // +0x0040
    char _pad0044[0x54 - 0x44];     // +0x0044
    Foot_006E9050* FirstUnit;       // +0x0054
    char _pad0058[0x82 - 0x58];     // +0x0058
    char At_82;                     // +0x0082

    // FUNCTION: GAMEMD 0x6E9050 — TeamClass::AssignMissionTarget.
    void AssignMissionTarget(Abstract_006E9050* target);
};
GG_STATIC_ASSERT(offsetof(Team_006E9050, Target) == 0x3C);
GG_STATIC_ASSERT(offsetof(Team_006E9050, At_40) == 0x40);
GG_STATIC_ASSERT(offsetof(Team_006E9050, FirstUnit) == 0x54);
GG_STATIC_ASSERT(offsetof(Team_006E9050, At_82) == 0x82);

#endif  // GG_MATCH_AI_TEAM_CLASS_MISSION_TARGET_METHODS_H
