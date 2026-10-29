// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x480510.

#include "cell_class_overlay_connect_methods.h"

// FUNCTION: GAMEMD 0x480510
//
// Does this cell join a wall of the given overlay from the given direction?
// The same overlay always joins; asked about no overlay, any of the three
// wall overlays counts. Otherwise a live gate building in the cell joins the
// wall it belongs to along its own axis (directions 2/6 or 0/4), and the
// wall tower joins the first two from every side.
//
// Health and Type are both read into locals before the health test: retail
// loads the type ahead of `TEST ECX,ECX`, and testing `obj->Health` in the
// same condition as WhatAmI defers the type load past the rules load.
bool Cell_00480510::ConnectsToOverlay(int overlay, int direction)
{
    if (OverlayTypeIndex == overlay && OverlayTypeIndex != -1) {
        return true;
    }
    if (overlay == -1) {
        if (OverlayTypeIndex == 2 || OverlayTypeIndex == 0x1A || OverlayTypeIndex == 0xF3) {
            return true;
        }
    } else {
        if (overlay == 2 || overlay == 0) {
            for (Obj_00480510* obj = FirstObject; obj != 0; obj = obj->NextObject) {
                if ((obj->*obj->Vptr->WhatAmI)() == 6) {
                    int health = obj->Health;
                    BuildingType_00480510* type = obj->Type;
                    if (health > 0) {
                    if (type == DAT_008871E0->unknown_86C && (direction == 2 || direction == 6)) {
                        return true;
                    }
                    if (type == DAT_008871E0->unknown_870 && (direction == 0 || direction == 4)) {
                        return true;
                    }
                    if (type == DAT_008871E0->unknown_87C) {
                        return true;
                    }
                    }
                }
            }
        }
        if (overlay == 0x1A) {
            for (Obj_00480510* obj = FirstObject; obj != 0; obj = obj->NextObject) {
                if ((obj->*obj->Vptr->WhatAmI)() == 6) {
                    int health = obj->Health;
                    BuildingType_00480510* type = obj->Type;
                    if (health > 0) {
                    if (type == DAT_008871E0->unknown_874 && (direction == 2 || direction == 6)) {
                        return true;
                    }
                    if (type == DAT_008871E0->unknown_878 && (direction == 0 || direction == 4)) {
                        return true;
                    }
                    }
                }
            }
        }
    }
    return false;
}
