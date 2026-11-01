// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Disassembly of gamemd.exe v1.001 at 0x57B990, the same neighbour-lookup shape as 0x57CAB0 /
//   0x57CBE0 (see cell_neighbor_flags_0057cbe0.h) with different switch tables. No engine names are inferred
//   for the numeric cases.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x57B990

#include "cell_neighbor_flags_0057cbe0.h"

// FUNCTION: GAMEMD 0x57B990
// Neighbour flags from the cells above and below the given cell.
unsigned int FUN_0057B990(NeighborCoord_0057CBE0* cell)
{
    NeighborCoord_0057CBE0 above = {cell->X, (short)(cell->Y - 1)};
    int aboveType = LookupNeighbor(&above)->At_44;
    NeighborCoord_0057CBE0 below = {cell->X, (short)(cell->Y + 1)};
    int belowType = LookupNeighbor(&below)->At_44;
    unsigned int flags = 0;
    switch (aboveType) {
    case 87: case 89: case 91: case 97: flags = 1; break;
    case 90: case 101: flags = 2; break;
    }
    switch (belowType) {
    case 88: case 89: case 90: case 99: return flags | 4;
    case 91: case 101: flags |= 8;
    }
    return flags;
}
