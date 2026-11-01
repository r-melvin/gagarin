// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary; complete entry disassembly 0x57CCF0..0x57CF59.
// REA ev_704bdf1aec79249ebacf495fd480a1cf4c995a8f53636d812e5e90275cf0a749
// Numeric type ranges and coordinate offsets are taken from instructions.
#include "cell_probe_0057ccf0.h"
static inline NeighborCell_0057CBE0* InitialProbeCell(const NeighborCoord_0057CBE0* cell)
{
    int index = cell->Y * 512 + cell->X;
    if (index >= 0 && index < 0x40000) {
        NeighborCell_0057CBE0* found = NeighborCells[index];
        if (found) return found;
    }
    NeighborFallback.Coordinates = *cell;
    return &NeighborFallback;
}
// Construct a coordinate value before handing its address to the lookup.
static inline NeighborCoord_0057CBE0 ProbeCoordinate(short x, short y)
{
    NeighborCoord_0057CBE0 value = {x, y};
    return value;
}
// FUNCTION: GAMEMD 0x57CCF0
// PARTIAL: 100/186 instructions (53.8%); 86 differing after source, flag
// bisection and a bounded permuter run. No assembly or padding is used.
char CellProbe_0057CCF0::FUN_0057CCF0(NeighborCoord_0057CBE0* cell)
{
    NeighborCoord_0057CBE0 candidate;
    int type = InitialProbeCell(cell)->At_44;
    if ((type >= 205 && type <= 213) || (type >= 223 && type <= 226) || type == 231) {
        candidate = ProbeCoordinate(cell->X, (short)(cell->Y - 1));
        type = ProbeMap.GetCell(&candidate)->At_44;
        if (type < 205 || type > 232) {
            candidate = ProbeCoordinate(cell->X, (short)(cell->Y + 1));
            return FUN_0057CF60(&candidate);
        }
        candidate = ProbeCoordinate(cell->X, (short)(cell->Y - 2));
        type = ProbeMap.GetCell(&candidate)->At_44;
        if (type < 205 || type > 232) return FUN_0057CF60(cell);
        candidate = ProbeCoordinate(cell->X, (short)(cell->Y - 1));
        return FUN_0057CF60(&candidate);
    }
    if ((type >= 214 && type <= 222) || (type >= 227 && type <= 230) || type == 232) {
        candidate = ProbeCoordinate((short)(cell->X - 1), cell->Y);
        type = ProbeMap.GetCell(&candidate)->At_44;
        // Explicit zero comparison preserves the period compiler's branch layout.
        if ((type < 205 || type > 232) != 0) {
            candidate = ProbeCoordinate((short)(cell->X + 1), cell->Y);
            return FUN_0057D530(&candidate);
        }
        candidate = ProbeCoordinate((short)(cell->X - 2), cell->Y);
        type = ProbeMap.GetCell(&candidate)->At_44;
        if (type < 205 || type > 232) return FUN_0057D530(cell);
        candidate.X = 1;
        candidate.Y = 0;
        NeighborCoord_0057CBE0 temporary;
        candidate = *((ProbeCoord_0057CCF0*)cell)->Subtract(&temporary, &candidate);
        return FUN_0057D530(&candidate);
    }
    return 0;
}
