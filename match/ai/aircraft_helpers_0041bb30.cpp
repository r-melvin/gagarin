// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail gamemd.exe v1.001 raw instructions and function extents confirmed
//   with the focused REA Ghidra analysis and local disassembly.

#include "aircraft_helpers_0041bb30.h"

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
void* AircraftClass_0041BB30::FUN_0041BBD0(int first, int, int third)
{
    if (At_6C4->At_E0D != 0 && At_6CC != 0) {
        if ((this->*Vtbl->At_278)(0xF, At_6CC) != 1) {
            At_6CC = 0;
        } else {
            goto retainTarget;
        }
    }

    At_6CC = FUN_004DF040(first, 0, third);
    return At_6CC;

retainTarget:
    return At_6CC;
}
