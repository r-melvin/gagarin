// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4834A0.

#include "cell_class_clear_to_move_methods.h"

// FUNCTION: GAMEMD 0x4834A0  CellClass::IsClearToMove (__thiscall, ret 0x1C)
//
// Can something of this speed type enter the cell? Flyers are never blocked.
// A caller-supplied zone must agree with the cell's movement zone, and a
// caller-supplied level must be either the cell's own level or, on a bridge
// cell, the bridge deck four levels above it. Whichever of the two occupation
// bytes applies must be empty once the caller's "ignore infantry" and "ignore
// vehicles" masks have been applied, a wall overlay blocks everything except
// the movement zones that can cross it, and finally the terrain must carry a
// non-zero movement cost for this speed type — unless we are on the bridge
// deck, where the terrain underneath does not matter.
bool Cell_Class_004834A0::IsClearToMove(int speedType, bool ignoreInfantry,
                                        bool ignoreVehicles, int zone,
                                        int movementZone, int level, bool isBridge)
{
    if (speedType == 4) {
        return true;
    }

    if (zone != -1) {
        if (zone != DAT_0087F7E8.GetMovementZoneType(this->MapCoords, movementZone,
                                                     isBridge)) {
            return false;
        }
    }

    if (level != -1) {
        if (level != this->Level) {
            if (!(this->Flags & 0x100) || level != this->Level + 4) {
                return false;
            }
        } else {
            if ((this->Flags & 0x100) && !isBridge) {
                return false;
            }
        }
    }

    bool onBridge = false;
    int occupy;
    if ((level == -1 || level == this->Level + 4) && (this->Flags & 0x100)) {
        onBridge = true;
        occupy = this->AltOccupationFlags;
    } else {
        occupy = this->OccupationFlags;
    }

    if (ignoreInfantry) {
        occupy &= 0xE0;
    }
    if (ignoreVehicles) {
        occupy &= 0x5F;
    }
    if (occupy != 0) {
        return false;
    }

    int landType = this->LandType;

    if (this->OverlayTypeIndex != -1) {
        OverlayTypeClass* pOverlay = DAT_00A83D84[this->OverlayTypeIndex];
        if (pOverlay != 0) {
            if (pOverlay->Wall != 0) {
                if (movementZone == 2 || movementZone == 3 || movementZone == 8
                    || ((movementZone == 1 || movementZone == 4)
                        && pOverlay->unknown_22D[0] != 0)
                    || movementZone == 0xC) {
                    landType = 0;
                } else {
                    return false;
                }
            }
        }
    }

    if (Grounds_004834A0[landType].Cost[speedType] == DAT_007E1748 && !onBridge) {
        return false;
    }

    return true;
}
