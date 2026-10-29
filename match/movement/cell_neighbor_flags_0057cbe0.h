// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary; gamemd.exe v1.001, entry 0x57CBE0 and switch tables.
#ifndef GG_CELL_NEIGHBOR_FLAGS_0057CBE0_H
#define GG_CELL_NEIGHBOR_FLAGS_0057CBE0_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
struct NeighborCoord_0057CBE0 { short X, Y; };
GG_STATIC_ASSERT(offsetof(NeighborCoord_0057CBE0, X) == 0);
GG_STATIC_ASSERT(offsetof(NeighborCoord_0057CBE0, Y) == 2);
GG_STATIC_ASSERT(sizeof(NeighborCoord_0057CBE0) == 4);
// Only the accessed cell prefix is represented.
struct NeighborCell_0057CBE0 {
    char unknown_00[0x24];
    NeighborCoord_0057CBE0 Coordinates;
    char unknown_28[0x1C];
    int At_44;
};
GG_STATIC_ASSERT(offsetof(NeighborCell_0057CBE0, Coordinates) == 0x24);
GG_STATIC_ASSERT(offsetof(NeighborCell_0057CBE0, At_44) == 0x44);
GG_STATIC_ASSERT(sizeof(NeighborCell_0057CBE0) == 0x48);
// GLOBAL: GAMEMD 0x87F924
extern NeighborCell_0057CBE0** NeighborCells;
// GLOBAL: GAMEMD 0xABDC50
extern NeighborCell_0057CBE0 NeighborFallback;
// NeighborFallback.Coordinates at 0xABDC74 is written on a failed lookup.
// Reconstructed inline lookup: the two retail copies share the table load.
static inline NeighborCell_0057CBE0* LookupNeighbor(const NeighborCoord_0057CBE0* cell)
{
    int index = cell->Y * 512 + cell->X;
    if (index >= 0 && index < 0x40000) {
        NeighborCell_0057CBE0* found = NeighborCells[index];
        if (found) return found;
    }
    NeighborFallback.Coordinates = *cell;
    return &NeighborFallback;
}
#endif
