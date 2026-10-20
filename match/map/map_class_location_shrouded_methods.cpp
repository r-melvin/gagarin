// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x586360.

#include "map_class_location_shrouded_methods.h"

// Resolve the cell under a world coordinate, shifted back towards the
// viewer by `level` cells on both axes so that raised terrain is looked up
// where it is drawn; MapClass::GetCellAt is expanded inline. The found path
// must be an early `return p` out of the range check: with the pointer
// assigned inside the miss condition (`(p = Cells[i]) == 0`, the 0x56BCD0
// form) the odd-level copy stays in EAX and is moved to ECX only at the
// neighbour call, where retail keeps the cell in ECX from the load on
// (`MOV ECX,EAX; JMP` on the hit, `MOV ECX,0xABDC50` on the miss).
static inline CellClass* CellAtLevel(CoordStruct const& coords, int level)
{
    CellStruct cell;
    cell.X = (short)(coords.X / 256);
    cell.Y = (short)(coords.Y / 256);

    CellStruct adjusted;
    adjusted.X = cell.X - level;
    adjusted.Y = cell.Y - level;

    int index = adjusted.Y * 512 + adjusted.X;
    if (index >= 0 && index < 0x40000) {
        CellClass* p = Cells_00586360[index];
        if (p != 0) {
            return p;
        }
    }
    InvalidCell_00586360.MapCoords = adjusted;
    return &InvalidCell_00586360;
}

// FUNCTION: GAMEMD 0x586360
//
// Is the world location clear of shroud? The coordinate's height is turned
// into a cell level; on an odd level both the projected cell and its
// neighbour in facing 3 must be clear, on an even level just the projected
// cell. `this` is unused — the cell array is reached through the singleton.
// Every rejecting test jumps to the one `XOR AL,AL` tail, so the guards are
// per-branch `return false` / `return true` early exits falling through to a
// single final `return false` (banked shared-constant-tail rule); a final
// `return !(flags & 8)` or `if (flags & 8) return false; return true;`
// becomes `NOT/SHR/AND` bit arithmetic instead of the branchy bool.
//
// PARTIAL (96.9%, 94/97): the residual is scheduling only — retail loads the
// two cell words (`MOV EAX,[ESP+6]; MOV EDX,[ESP+4]`) before the odd
// level's `INC ECX`, cl 8804 emits the INC first. Variants tried: the level
// passed as `z / 2 + 1` (this form), `int level = z / 2` hoisted above the
// branch with `level + 1` (2.8%, spills), the `+1` folded into the
// subtraction as `cell.X - (z / 2 + 1)` / `- (level + 1)` in explicit
// per-branch blocks and via a `bump` parameter (all become `DEC`, 1.9%).
// Re-measured this pass against the named-local levers, which is the other
// side of the same question — retail reads the two cell words back out of
// their stack slots before the `INC`, so giving each its own local ought to
// pull the loads forward. It does not: `short cy = cell.Y; short cx = cell.X;`
// ahead of the subtractions (retail's own load order), the same pair declared
// X-first, the two subtractions written Y-first without locals, and int-typed
// locals with the narrowing cast moved onto the store all score 96.9%
// unchanged; volatile reads of the two words are 93.8%.
bool MapClass::IsLocationShrouded(CoordStruct const& coords) const
{
    int z = coords.Z / LevelHeight_00586360;
    CellClass* pCell;

    if (z & 1) {
        pCell = CellAtLevel(coords, z / 2 + 1);
        if (pCell->AltFlags & 8) {
            return false;
        }
        if (!(pCell->GetNeighbourCell(3)->AltFlags & 8)) {
            return true;
        }
    } else {
        pCell = CellAtLevel(coords, z / 2);
        if (!(pCell->AltFlags & 8)) {
            return true;
        }
    }
    return false;
}
