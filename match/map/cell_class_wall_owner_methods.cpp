// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x47D210.

#include "cell_class_wall_owner_methods.h"

// FUNCTION: GAMEMD 0x47D210  CellClass::SetWallOwner (__thiscall)
//
// When the cell carries a wall overlay, find the nearest building whose owner
// is a wall-owning house (and whose two state bytes at +0x90/+0x74 are set)
// and record that building's owning-house index in the cell. With no such
// building the cell's wall owner becomes -1. Cells without a wall overlay are
// left untouched.
void CellClass::SetWallOwner()
{
    if (OverlayTypeIndex != -1 && DAT_00A83D84[OverlayTypeIndex]->Wall) {
        int owner = -1;
        int best = 0x7FFFFFFF;

        for (int i = 0; i < DAT_00A8EB50; i++) {
            Building_0047D210* b = DAT_00A8EB44[i];
            if (b->At_90 && b->At_74 && b->Owner->Type->WallOwner) {
                int dist = b->DistanceFrom3D(this);
                if (dist < best) {
                    best = dist;
                    owner = (b->*b->Vtbl->GetOwningHouseIndex)();
                }
            }
        }
        WallOwnerIndex = owner;
    }
}
