// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x4251F0.

#include "spawn_effect_methods.h"
#include "../_layout/session_class.h"

// FUNCTION: GAMEMD 0x4251F0
//
// Play an effect at the centre of a cell, and register the follow-up callback the
// first time round.
//
// The coordinate is built from the cell pair by scaling each component to leptons
// and adding half a cell, leaving the height at zero — the effect sits on the
// ground at the cell's centre rather than at its corner.
void FUN_004251F0(int, const short* cell)
{
    Coord_004251F0 where;
    where.X = cell[0] * 0x100 + 0x80;
    where.Y = cell[1] * 0x100 + 0x80;
    where.Z = 0;

    FUN_00489280(&where, DAT_008871E0->At_1530, 0, DAT_008871E0->At_F8C, 0, 0);

    if (Session_00A8B238.GameMode == 0) {
        FUN_004A3C30(&DAT_00885780, 0x1E, FUN_0048D080);
    }
}
