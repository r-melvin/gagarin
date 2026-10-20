// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4DA230.

#include "foot_class_recruit_methods.h"

// FUNCTION: GAMEMD 0x4DA230  FootClass::CanBeRecruited (__thiscall, ret 0x4)
// Whether a team-building AI may draft this unit: it has to exist, belong to
// the asking house, be on the map, be unattached, be of a recruitable kind, and
// still carry its recruitable flag. Each disqualifier returns early, which is
// why retail repeats the `XOR AL,AL; POP ESI; RET 4` epilogue five times.
bool FootClass::CanBeRecruited(HouseClass* house)
{
    if (house == 0)
        return false;

    if (house != Owner)
        return false;

    if (InLimbo)
        return false;

    if (Team != 0)
        return false;

    if (!IsRecruitableRTTI(FOOT_WHAT_AM_I(this)))
        return false;

    // The temporary is load-bearing: `return RecruitableA != 0;` makes VC6
    // zero-extend through a spare register (XOR EAX,EAX; TEST CL,CL), where
    // retail keeps the loaded byte in AL and sets the result on it directly.
    bool recruitable = RecruitableA != 0;
    return recruitable;
}
