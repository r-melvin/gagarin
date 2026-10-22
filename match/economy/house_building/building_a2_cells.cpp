// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Slot 309 of the building-a2 cluster: the search for a free cell next to a building. Read from the
//   retail gamemd.exe v1.001 from its entry to its last RET with a LINEAR decode of the retail bytes
//   (Ghidra's function-flow listing drops instructions after some calls); offsets are pinned in
//   building_a2_views.h. Method names are slot labels (vf_N = primary-table byte offset / 4).

#include "building_a2_views.h"

// EXACT: 100.0% (494/494 instructions, 57 relocation fields verified, raw span identical modulo relocations).
// What made it match: slot 110 as a by-value return (hidden temporary shared with the constructor temporaries),
// the HBCell constructor temporaries reusing the argument slot, and separate loop variables (i, j) per loop.
// FUNCTION: GAMEMD 0x44EFB0
// Finds a cell next to the building where the mover may stand: the type's fixed exit cells first, then the
// cells around the building's centre, the preferred cell, the type's own offset list (terminated by
// 0x7FFF,0x7FFF) or else the rows and columns around the foundation. Returns the invalid cell on failure.
HBCell BA2Building::vf_309(BA2Obj* who, HBCell preferred)
{
    HBCell base = vf_110();
    HBCell c;

    if (Type->unknown_16E4) {
        c = HBCell(base.X + 1, base.Y + 2);
        if (DAT_0087F7E8.FUN_00568300(&c) && !who->vf_107(DAT_0087F7E8.FUN_005657A0(&c), -1, -1, 0, 1)) {
            return c;
        }
    }
    if (Type->unknown_16E5) {
        c = HBCell(base.X + 2, base.Y + 2);
        if (DAT_0087F7E8.FUN_00568300(&c) && !who->vf_107(DAT_0087F7E8.FUN_005657A0(&c), -1, -1, 0, 1)) {
            return c;
        }
    }
    if (Type->unknown_16E6) {
        c = HBCell(base.X + 2, base.Y + 1);
        if (DAT_0087F7E8.FUN_00568300(&c) && !who->vf_107(DAT_0087F7E8.FUN_005657A0(&c), -1, -1, 0, 1)) {
            return c;
        }
    }
    if (Type->unknown_CCE && Type->unknown_16BD) {
        HBCoord out;
        HBCoord* centre = vf_42(&out, who);
        c = HBCell(centre->X / 256, centre->Y / 256);
        c.X++;
        c.Y++;
        if (DAT_0087F7E8.FUN_00568300(&c) && !who->vf_107(DAT_0087F7E8.FUN_005657A0(&c), -1, -1, 0, 0)) {
            return c;
        }
        c.Y--;
        if (DAT_0087F7E8.FUN_00568300(&c) && !who->vf_107(DAT_0087F7E8.FUN_005657A0(&c), -1, -1, 0, 0)) {
            return c;
        }
        c.Y++;
        c.X--;
        if (DAT_0087F7E8.FUN_00568300(&c) && !who->vf_107(DAT_0087F7E8.FUN_005657A0(&c), -1, -1, 0, 0)) {
            return c;
        }
    }
    if (preferred.X != DAT_0089C818.X || preferred.Y != DAT_0089C818.Y) {
        if (DAT_0087F7E8.FUN_00568300(&preferred)
            && !who->vf_107(DAT_0087F7E8.FUN_005657A0(&preferred), -1, -1, 0, 0)) {
            return preferred;
        }
    }

    HBCell* offsets = Type->unknown_ED4;
    if (offsets && !Type->unknown_16C1) {
        while (!(offsets->X == 0x7FFF && offsets->Y == 0x7FFF)) {
            HBCell* entry = offsets++;
            c = HBCell(base.X + entry->X, base.Y + entry->Y);
            if (DAT_0087F7E8.FUN_00568300(&c) && !who->vf_107(DAT_0087F7E8.FUN_005657A0(&c), -1, -1, 0, 0)) {
                return c;
            }
        }
    } else {
        int rows = Type->FUN_0045ECA0(0);
        for (int i = -1; i <= Type->FUN_0045EC90(); i++) {
            c = HBCell(base.X + i, base.Y + rows);
            if (DAT_0087F7E8.FUN_00568300(&c) && !who->vf_107(DAT_0087F7E8.FUN_005657A0(&c), -1, -1, 0, 1)) {
                return c;
            }
            c = HBCell(base.X + i, base.Y - 1);
            if (DAT_0087F7E8.FUN_00568300(&c) && !who->vf_107(DAT_0087F7E8.FUN_005657A0(&c), -1, -1, 0, 1)) {
                return c;
            }
        }
        int columns = Type->FUN_0045EC90();
        for (int j = -1; j <= Type->FUN_0045ECA0(0); j++) {
            c = HBCell(base.X + columns, base.Y + j);
            if (DAT_0087F7E8.FUN_00568300(&c) && !who->vf_107(DAT_0087F7E8.FUN_005657A0(&c), -1, -1, 0, 1)) {
                return c;
            }
            c = HBCell(base.X - 1, base.Y + j);
            if (DAT_0087F7E8.FUN_00568300(&c) && !who->vf_107(DAT_0087F7E8.FUN_005657A0(&c), -1, -1, 0, 1)) {
                return c;
            }
        }
    }
    return DAT_0089C818;
}
