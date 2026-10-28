// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail gamemd.exe v1.001 raw instructions and function extents confirmed
//   with the focused REA Ghidra analysis and local disassembly.

#include "../_layout/aircraft_class.h"
#include "../_layout/aircraft_type_class.h"

// FUNCTION: GAMEMD 0x41BB30
// While attacking or in a guard/area-guard style mission with no airstrike
// pending, only those same missions may replace the current one.
void AircraftClass::vf_125(int mission, int a2, int a3)
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

    FootClass::vf_125(mission, a2, a3);
}

// FUNCTION: GAMEMD 0x41BBD0
// Airport-bound aircraft keep a dock that still answers radio query 0xF with
// 1; otherwise pick a new one with the FootClass slot-330 search.
void* AircraftClass::vf_330(DynamicVectorClassLayout* a1, int, int a3)
{
    if (Type->AirportBound && DockNowHeadingTo != 0) {
        if (this->vf_158(0xF, (RadioClass*)DockNowHeadingTo) != 1) {
            DockNowHeadingTo = 0;
        } else {
            goto retainTarget;
        }
    }

    DockNowHeadingTo = FootClass::vf_330(a1, 0, a3);
    return DockNowHeadingTo;

retainTarget:
    return DockNowHeadingTo;
}
