// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x746000.

#include <stdlib.h>
#include "unit_class_astar_attempt_methods.h"

// FUNCTION: GAMEMD 0x746000
//
// Should a short hop between two cells be handed to the A* search? A unit
// below ground, a failed pre-check, a far hop (twelve cells or more) or an
// off-map endpoint all say yes; the same cell or an adjacent one says no.
// In between, the search is run for real and only a long result counts.
//
// Every `return true` is the one fall-through tail: the guards are nested
// (`&&` chains) rather than early returns, which is what makes retail jump
// forward to a single MOV AL,1 block while the false returns stay inline.
// The flag word is unsigned so the level bit comes out with SHR.
bool Unit_00746000::AStarAttempt(const Cell_00746000* from, const Cell_00746000* to)
{
    if ((this->*Vptr->GetHeight)() >= 0
        && MapInstance_00746000.FUN_0056D100(from, to, 0, 0, 0, 0)) {
        if (from->X == to->X && from->Y == to->Y) {
            return false;
        }

        int dy = abs(to->Y - from->Y);
        int dx = abs(to->X - from->X);
        int dist = dx > dy ? dx : dy;
        if (dist == 1) {
            return false;
        }
        if (dist < 12
            && MapInstance_00746000.IsWithinUsableArea(from, true)
            && MapInstance_00746000.IsWithinUsableArea(to, true)) {
            int steps = DAT_0087E8B8.AttemptPath(
                from, to, this, false,
                (MapInstance_00746000.GetCellAt(to)->Flags >> 8) & 1, 0);
            return steps > 15;
        }
    }
    return true;
}
