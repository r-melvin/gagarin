// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x56BEC0.

#include "map_class_powerup_crate_methods.h"

// MapClass::GetCellAt, expanded inline (twice) at 0x56BEC0: the flat index is
// bounds-checked against 0x40000, and a miss stamps the requested coordinates
// into InvalidCell and hands that back.
static inline CellClass_0056BEC0* GetCellAt_0056BEC0(Cell_0056BEC0 cell)
{
    int index = cell.Y * 512 + cell.X;
    if (index >= 0 && index < 0x40000) {
        CellClass_0056BEC0* p = Cells_0056BEC0[index];
        if (p != 0) {
            return p;
        }
    }
    InvalidCellCoords_0056BEC0 = cell;
    return &InvalidCell_0056BEC0;
}

// FUNCTION: GAMEMD 0x56BEC0  MapClass::PlacePowerupCrate (__thiscall, ret 8)
//
// Drop a powerup crate near a cell. Water cells search with the float speed
// type, everything else with the foot type; either way a free 1x1 spot is
// asked for. The first crate slot whose location is still the free sentinel
// takes it, and unless the caller passed the "leave it alone" type 0x14 the
// chosen cell's overlay data records which powerup it is.
//
// PARTIAL (22.3%, 27/121 by the positional aligner; the real residual is four
// instructions). Frame, prologue, both inlined GetCellAt expansions, the
// shared zero in EBX, the crate scan (`LEA ECX,[EDI+0x164]`, `CMP word[ECX],DX`,
// `CMP word[ECX+2],SI`, `ADD ECX,0x10`), the slot call, the overlay store and
// both epilogues are byte-identical; everything after the first NearByLocation
// argument group is merely shifted by the four retail-only `MOV EAX,1` /
// `MOV ECX,EAX` pairs (one per arm). Retail keeps the repeated constant 1 in
// EAX with a copy in ECX and pushes the registers; cl 12.00.8804 pushes three
// `1` immediates instead. That is the already-recorded 8447-vs-8804
// materialised-push-constant class at every NearByLocation call site
// (0x4FBF60, 0x703590, 0x41A2C0) and is not reachable by phrasing: a named
// `int one = 1` used for SpaceSizeX/SpaceSizeY/IgnoreOccupied is
// constant-propagated straight back to immediates and scores identically.
// Variants tried: one `closeTo` local shared by both arms (10.7% — cl hoists
// the twelve common pushes above the land-type branch and loses the EBX zero);
// per-arm `closeTo` locals, which is what defeats the hoist and restores the
// full duplicated argument setup plus `MOV EBX,0` (22.3%); a named `int one`
// for the three 1s together with a `CellStruct*` crate cursor re-derived as
// `&Crates[i].Location` each iteration — the cursor half of that is kept
// because it moves the loop base from `EDI+0x166`/`[ECX-2]` to retail's
// `EDI+0x164`/`[ECX]`, the `one` half is reverted as a no-op.
bool Map_0056BEC0::PlacePowerupCrate(Cell_0056BEC0 cell, int type)
{
    if (GetCellAt_0056BEC0(cell)->LandType == 2) {
        Cell_0056BEC0 closeTo;
        closeTo.X = 0;
        closeTo.Y = 0;
        cell = DAT_0087F7E8.NearByLocation(cell, 5, -1, 0, false, 1, 1,
                                           false, false, false, true, closeTo,
                                           false, false);
    } else {
        Cell_0056BEC0 closeTo;
        closeTo.X = 0;
        closeTo.Y = 0;
        cell = DAT_0087F7E8.NearByLocation(cell, 1, -1, 0, false, 1, 1,
                                           false, false, false, true, closeTo,
                                           false, false);
    }

    int i = 0;
    Cell_0056BEC0* loc = &this->Crates[0].Location;
    do {
        if (loc->X == DAT_00ABD480.X && loc->Y == DAT_00ABD480.Y) {
            break;
        }
        i++;
        loc = &this->Crates[i].Location;
    } while (i < 0x100);

    if (i != 0x100) {
        if (this->Crates[i].FUN_004A17C0(cell)) {
            if (type != 0x14) {
                GetCellAt_0056BEC0(cell)->OverlayData = (unsigned char)type;
            }
            return true;
        }
    }
    return false;
}
