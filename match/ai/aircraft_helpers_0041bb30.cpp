// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail gamemd.exe v1.001 raw instructions and function extents confirmed
//   with the focused REA Ghidra analysis and local disassembly.

#include "aircraft_helpers_0041bb30.h"
#include "../_layout/aircraft_class.h"
#include "../_layout/aircraft_type_class.h"

// FUNCTION: GAMEMD 0x41BB30
void AircraftClass_0041BB30::FUN_0041BB30(int first, int second, int third)
{
    switch (At_AC) {
    case 4:
    case 26:
    case 27:
    case 30:
    case 31:
        if (At_294 == 0) {
            switch (first) {
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

    FUN_004D8F40(first, second, third);
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
