// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x6A87F0.
//
// Address index: 0x6A87F0

#include "sidebar_class_layout.h"
#include "../../audio/vox_class_methods.h"

// GLOBAL: GAMEMD 0xA8E7AC -- nonzero suppresses the EVA line.
extern int DAT_00A8E7AC;

// FUNCTION: GAMEMD 0x6A87F0
// Add a cameo of this type and id to the strip unless it is full or already present, announce the
// new construction options (except for type 0x1F, or when announcements are suppressed) and flag
// the strip and sidebar for redraw.
bool StripClass::FUN_006A87F0(int type, int id)
{
    if (CameoCount <= 0x4B) {
        for (int i = 0; i < CameoCount; i++) {
            if (Cameos[i].unknown_04.Word == type && Cameos[i].unknown_00 == id) {
                return false;
            }
        }
        if (!DAT_00A8E7AC && type != 0x1F) {
            VoxClass::Play("EVA_NewConstructionOptions", -1, -1);
        }
        FUN_006A8710(type, id);
        At_3C = 1;
        SidebarNeedsRedraw_00884B8F = 1;
        return true;
    }
    return false;
}
