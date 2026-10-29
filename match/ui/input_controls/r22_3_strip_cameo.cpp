// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x6ABA60.
//
// Address index: 0x6ABA60

#include "sidebar_class_layout.h"

// FUNCTION: GAMEMD 0x6ABA60
// Find the cameo with this type and id and store value in its pointer slot, then mark the strip
// and the sidebar for redraw. False when the strip has no such cameo.
bool StripClass::FUN_006ABA60(void* value, int type, int id)
{
    for (int i = 0; i < CameoCount; i++) {
        if (*(int*)Cameos[i].unknown_04 == type && Cameos[i].unknown_00 == id) {
            Cameos[i].Pointer = value;
            unknown_3D = 1;
            At_3C = 1;
            Map_0087F7E8.FlagToRedraw(0);
            return true;
        }
    }
    return false;
}
