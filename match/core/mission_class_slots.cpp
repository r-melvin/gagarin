// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// MissionClass bodies in retail address order (0x5B2E10..0x5B3A52): the
// mission-state slots of the primary table 0x7EDCC0 (RTTI
// ".?AVMissionClass@@") and ObjectClass slot 69, which is emitted here. Slot
// numbers come from the table; names are placeholders (mission_class.h).
// Mission values 5, 19 and 28 are compared as numbers only.
#include "../_layout/mission_class.h"
#include "frame_counter.h"
#include "../_layout/obj_004a1d30.h"

// Frames left on a count-down timer (-1 start = stopped). Descriptive local
// helper for code retail has inlined; no original name is attested.
static inline int TimerRemaining(const CDTimerClass& t)
{
    int left = t.TimeLeft;
    if (t.StartTime != -1) {
        int elapsed = CurrentFrame - t.StartTime;
        if (elapsed < left) {
            return left - elapsed;
        }
        return 0;
    }
    return left;
}

// A timer temporary started now with `delay` frames left. Retail never
// writes the middle word of the temporary it copies into the member.
static inline CDTimerClass MissionTimer(int delay)
{
    CDTimerClass timer;
    timer.StartTime = CurrentFrame;
    timer.TimeLeft = delay;
    return timer;
}

// FUNCTION: GAMEMD 0x5B2E10
int MissionClass::vf_129()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2E20
int MissionClass::vf_130()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2E30
int MissionClass::vf_131()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2E40
int MissionClass::vf_132()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2E50
int MissionClass::vf_133()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2E60
int MissionClass::vf_134()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2E70
int MissionClass::vf_135()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2E80
int MissionClass::vf_136()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2E90
int MissionClass::vf_137()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2EA0
int MissionClass::vf_138()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2EB0
int MissionClass::vf_139()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2EC0
int MissionClass::vf_140()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2ED0
int MissionClass::vf_141()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2EE0
int MissionClass::vf_142()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2EF0
int MissionClass::vf_143()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2F00
int MissionClass::vf_144()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2F10
int MissionClass::vf_145()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2F20
int MissionClass::vf_146()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2F30
int MissionClass::vf_147()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2F40
int MissionClass::vf_148()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2F50
int MissionClass::vf_149()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2F60
int MissionClass::vf_150()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2F70
int MissionClass::vf_151()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2F80
int MissionClass::vf_152()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2F90
int MissionClass::vf_153()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2FA0
int MissionClass::vf_154()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2FB0
int MissionClass::vf_155()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2FC0
int MissionClass::vf_156()
{
    return 450;
}

// FUNCTION: GAMEMD 0x5B2FD0
// Retail copies a whole timer temporary into UpdateTimer; the temporary's
// middle word is never written, so neither is it here.
void MissionClass::vf_124(int mission)
{
    if (CurrentMission == 28 && mission == 5) {
        return;
    }
    CurrentMission = mission;
    QueuedMission = -1;
    unknown_bool_B8 = 0;
    MissionStatus = 0;
    CurrentMissionStartTime = CurrentFrame;
    MissionAccumulateTime = 0;
    CDTimerClass timer;
    timer.StartTime = CurrentFrame;
    timer.TimeLeft = 0;
    UpdateTimer = timer;
}

// FUNCTION: GAMEMD 0x5B3040
int MissionClass::vf_97()
{
    int mission = CurrentMission;
    if (mission == -1) {
        mission = QueuedMission;
    }
    return mission;
}

// FUNCTION: GAMEMD 0x5B3060
// The per-frame mission dispatch: once the update timer has run out, the
// current mission's handler slot (129-156) runs and its result rearms the
// timer. Mission values outside the handled set use slot 129.
void MissionClass::vf_23()
{
    ObjectClass::vf_23();
    if (!IsAlive) {
        return;
    }
    if (TimerRemaining(UpdateTimer) != 0) {
        return;
    }
    if (Health <= 0) {
        return;
    }
    switch (CurrentMission) {
    case 0:
        UpdateTimer = MissionTimer(vf_129());
        break;
    case 23:
        UpdateTimer = MissionTimer(vf_130());
        break;
    case 7:
        UpdateTimer = MissionTimer(vf_144());
        break;
    case 18:
        UpdateTimer = MissionTimer(vf_145());
        break;
    case 19:
        UpdateTimer = MissionTimer(vf_146());
        break;
    case 1:
        UpdateTimer = MissionTimer(vf_132());
        break;
    case 4:
        UpdateTimer = MissionTimer(vf_140());
        break;
    case 10:
        UpdateTimer = MissionTimer(vf_137());
        break;
    case 11:
        UpdateTimer = MissionTimer(vf_136());
        break;
    case 12:
        UpdateTimer = MissionTimer(vf_141());
        break;
    case 13:
        UpdateTimer = MissionTimer(vf_142());
        break;
    case 14:
        UpdateTimer = MissionTimer(vf_131());
        break;
    case 16:
        UpdateTimer = MissionTimer(vf_143());
        break;
    case 20:
        UpdateTimer = MissionTimer(vf_147());
        break;
    case 24:
        UpdateTimer = MissionTimer(vf_149());
        break;
    case 22:
        UpdateTimer = MissionTimer(vf_148());
        break;
    case 5:
        UpdateTimer = MissionTimer(vf_135());
        break;
    case 8:
        UpdateTimer = MissionTimer(vf_133());
        break;
    case 9:
        UpdateTimer = MissionTimer(vf_134());
        break;
    case 2:
        UpdateTimer = MissionTimer(vf_139());
        break;
    case 15:
        UpdateTimer = MissionTimer(vf_138());
        break;
    case 21:
        UpdateTimer = MissionTimer(vf_150());
        break;
    case 25:
        UpdateTimer = MissionTimer(vf_151());
        break;
    case 26:
        UpdateTimer = MissionTimer(vf_152());
        break;
    case 27:
        UpdateTimer = MissionTimer(vf_153());
        break;
    case 30:
        UpdateTimer = MissionTimer(vf_155());
        break;
    case 31:
        UpdateTimer = MissionTimer(vf_156());
        break;
    case 28:
        UpdateTimer = MissionTimer(vf_154());
        break;
    case 6:
        UpdateTimer = MissionTimer(vf_135());
        break;
    case 17:
        UpdateTimer = MissionTimer(vf_133());
        break;
    default:
        UpdateTimer = MissionTimer(vf_129());
        break;
    }
}

// FUNCTION: GAMEMD 0x5B3570
bool MissionClass::vf_123()
{
    if (QueuedMission != -1) {
        CurrentMission = QueuedMission;
        QueuedMission = -1;
        CDTimerClass timer;
        timer.StartTime = CurrentFrame;
        MissionStatus = 0;
        timer.TimeLeft = 0;
        UpdateTimer = timer;
        CurrentMissionStartTime = CurrentFrame;
        MissionAccumulateTime = 0;
        unknown_bool_B8 = 0;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x5B35E0
void MissionClass::vf_122(int mission, bool a2)
{
    if (CurrentMission == 28 && mission == 5) {
        return;
    }
    if (CurrentMission == 19) {
        return;
    }
    if (mission != -1) {
        if (CurrentMission != mission || (QueuedMission != mission && QueuedMission != -1)) {
            QueuedMission = mission;
            unknown_bool_B8 = 0;
        }
    }
    if (a2 && vf_128()) {
        vf_123();
    }
}

// FUNCTION: GAMEMD 0x5B3650
void MissionClass::vf_125(int mission, int a2, int a3)
{
    if (CurrentMission == 28 && mission == 5) {
        return;
    }
    if (CurrentMission == 19) {
        return;
    }
    if (QueuedMission != -1) {
        CurrentMission = mission;
        SuspendedMission = QueuedMission;
        unknown_bool_B8 = 0;
    } else {
        SuspendedMission = CurrentMission;
        CurrentMission = mission;
        unknown_bool_B8 = 0;
    }
}

// FUNCTION: GAMEMD 0x5B36B0
bool MissionClass::vf_126()
{
    if (SuspendedMission != -1) {
        CurrentMission = SuspendedMission;
        SuspendedMission = -1;
        unknown_bool_B8 = 0;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x5B3970
void MissionClass::vf_13(Obj_004A1D30* crc)
{
    ObjectClass::vf_13(crc);
    crc->FUN_004A1D50(CurrentMission);
    crc->FUN_004A1D50(SuspendedMission);
    crc->FUN_004A1D50(QueuedMission);
    crc->FUN_004A1D50(MissionStatus);
    crc->FUN_004A1D50(TimerRemaining(UpdateTimer));
    crc->FUN_004A1D50(CurrentMissionStartTime);
}

// FUNCTION: GAMEMD 0x5B3A10
bool MissionClass::vf_127()
{
    return SuspendedMission != -1;
}

// FUNCTION: GAMEMD 0x5B3A50 -- ObjectClass slot 69, emitted in this block.
void ObjectClass::vf_69(int a1, int a2)
{
}
