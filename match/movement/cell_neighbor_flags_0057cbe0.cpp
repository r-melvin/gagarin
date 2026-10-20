// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary; entry disassembly 0x57CAB0..0x57CB89 and
// 0x57CBE0..0x57CCB3.
// REA ev_58558985c84c4e088aab1c3d10719f80e5bd67e006c93042543b8c3cfb3a9291
// Sibling REA ev_e0a3f311b4979e86407b68a66bdf502a864a986a84e5c2d8065abcf41139af02
// Switch targets and selector maps checked at 0x57CB8C/0x57CB98,
// 0x57CBB0/0x57CBBC, 0x57CCB4/0x57CCC0 and
// 0x57CCD0/0x57CCDC. No engine names are inferred for the numeric cases.
#include "cell_neighbor_flags_0057cbe0.h"
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
// FUNCTION: GAMEMD 0x57CAB0
int __fastcall FUN_0057CAB0(NeighborCoord_0057CBE0* cell)
{
    NeighborCoord_0057CBE0 left = {(short)(cell->X - 1), cell->Y};
    int leftType = LookupNeighbor(&left)->At_44;
    NeighborCoord_0057CBE0 right = {(short)(cell->X + 1), cell->Y};
    int rightType = LookupNeighbor(&right)->At_44;
    int flags = 0;
    switch (rightType) {
    case 209: case 211: case 213: case 224: flags = 1; break;
    case 212: case 231: flags = 2; break;
    }
    switch (leftType) {
    case 210: case 211: case 212: case 226: flags |= 4; break;
    case 213: case 231: flags |= 8; break;
    }
    return flags;
}
// FUNCTION: GAMEMD 0x57CBE0
unsigned char __fastcall FUN_0057CBE0(NeighborCoord_0057CBE0* cell)
{
    NeighborCoord_0057CBE0 above = {cell->X, (short)(cell->Y - 1)};
    int aboveType = LookupNeighbor(&above)->At_44;
    NeighborCoord_0057CBE0 below = {cell->X, (short)(cell->Y + 1)};
    int belowType = LookupNeighbor(&below)->At_44;
    int flags = 0;
    switch (aboveType) {
    case 218: case 220: case 222: case 228: flags = 1; break;
    case 221: case 232: flags = 2; break;
    }
    switch (belowType) {
    case 219: case 220: case 221: case 230: flags |= 4; break;
    case 222: case 232: flags |= 8; break;
    }
    return flags;
}
