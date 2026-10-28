// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail gamemd.exe v1.001 disassembly at each address below; the slots sit
//   in AircraftClass's primary table (indices 122..124).
//
//   0x41B870  AircraftClass::vf_123
//   0x41B9F0  AircraftClass::vf_124
//   0x41BA90  AircraftClass::vf_122

#include "../_layout/aircraft_class.h"

// FUNCTION: GAMEMD 0x41B870
// Outside mission 0x1E the lock flag is cleared; the base starts the queued mission.
bool AircraftClass::vf_123()
{
    if (CurrentMission != 0x1E) {
        IsLocked = 0;
    }
    return MissionClass::vf_123();
}

// FUNCTION: GAMEMD 0x41B9F0
// While attacking or in a guard/area-guard style mission with no airstrike
// pending, only those same missions may replace the current one.
void AircraftClass::vf_124(int mission)
{
    switch (CurrentMission) {
    case 4:
    case 26:
    case 27:
    case 30:
    case 31:
        if (Airstrike == 0) {
            switch (mission) {
            case 4:
            case 26:
            case 27:
            case 30:
            case 31:
                break;
            default:
                return;
            }
        }
        break;
    }

    MissionClass::vf_124(mission);
}

// FUNCTION: GAMEMD 0x41BA90
// Same gate as vf_124 for the queued-mission setter.
void AircraftClass::vf_122(int mission, bool a2)
{
    switch (CurrentMission) {
    case 4:
    case 26:
    case 27:
    case 30:
    case 31:
        if (Airstrike == 0) {
            switch (mission) {
            case 4:
            case 26:
            case 27:
            case 30:
            case 31:
                break;
            default:
                return;
            }
        }
        break;
    }

    MissionClass::vf_122(mission, a2);
}
