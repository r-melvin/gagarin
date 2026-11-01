// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary; retail gamemd.exe v1.001, full entry 0x57CCF0. | YRpp-cross-check
#ifndef GG_CELL_PROBE_0057CCF0_H
#define GG_CELL_PROBE_0057CCF0_H
#include "cell_neighbor_flags_0057cbe0.h"
// Interface views: only receiver addresses and call conventions are modeled.
struct ProbeMap_0057CCF0 {
    // FUNCTION: GAMEMD 0x5657A0
    NeighborCell_0057CBE0* GetCell(const NeighborCoord_0057CBE0* cell);
};
// GLOBAL: GAMEMD 0x87F7E8
extern ProbeMap_0057CCF0 ProbeMap;
struct ProbeCoord_0057CCF0 : NeighborCoord_0057CBE0 {
    // Entry 0x588C60 subtracts the two signed-short components and RET 8.
    // FUNCTION: GAMEMD 0x588C60
    NeighborCoord_0057CBE0* Subtract(NeighborCoord_0057CBE0* out,
                               const NeighborCoord_0057CBE0* delta);
};
GG_STATIC_ASSERT(offsetof(ProbeCoord_0057CCF0, X) == 0);
GG_STATIC_ASSERT(offsetof(ProbeCoord_0057CCF0, Y) == 2);
GG_STATIC_ASSERT(sizeof(ProbeCoord_0057CCF0) == 4);
struct CellProbe_0057CCF0 {
    // FUNCTION: GAMEMD 0x57CCF0
    char FUN_0057CCF0(NeighborCoord_0057CBE0* cell);
    // FUNCTION: GAMEMD 0x57CF60
    char FUN_0057CF60(NeighborCoord_0057CBE0* cell);
    // FUNCTION: GAMEMD 0x57D530
    char FUN_0057D530(NeighborCoord_0057CBE0* cell);
};
#endif
