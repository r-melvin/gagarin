// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2 /MT
// MissionClass constructor at 0x5B2DA0: runs the ObjectClass constructor (0x5F3900), sets the
// three mission slots to -1, clears the status fields, starts the update timer and seats the
// four MissionClass vtables (RTTI on 0x7EDCC0).
#include "../_layout/mission_class.h"

// FUNCTION: GAMEMD 0x5B2DA0
MissionClass::MissionClass()
    : CurrentMission(-1), SuspendedMission(-1), QueuedMission(-1),
      unknown_bool_B8(0), MissionStatus(0), CurrentMissionStartTime(0), MissionAccumulateTime(0),
      UpdateTimer(0)
{
}
