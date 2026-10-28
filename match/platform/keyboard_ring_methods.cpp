// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x54F000 and 0x54F6F0: the
//   key-state array at +0x14 and the 256-entry key queue (ring) at +0x114 whose indices
//   sit at +0x314 and +0x318.
//
// Address index: 0x54F000 0x54F6F0 (the constructor 0x54EE60 is unmatched)

#include "input_manager_class_methods.h"

// FUNCTION: GAMEMD 0x54F000
// Pumps input when the queue is not full, then returns the oldest queued key without
// removing it (0 when the queue is empty).
unsigned short InputManagerClass::FUN_0054F000()
{
    if ((field_318 + 1) % 256 != field_314)
        FUN_005D4D50();
    if (field_314 == field_318)
        return 0;
    return Ring[field_314];
}

// FUNCTION: GAMEMD 0x54F6F0
// Pumps input when the queue is not full.
void InputManagerClass::FUN_0054F6F0()
{
    if ((field_318 + 1) % 256 != field_314)
        FUN_005D4D50();
}
