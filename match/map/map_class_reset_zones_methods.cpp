// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x56D460.

#include "map_class_reset_zones_methods.h"

// FUNCTION: GAMEMD 0x56D460  MapClass::ResetZones (__thiscall, ret 4)
//
// Patch the zone grid around one cell. The cell's zone record is located (its
// index clamped into the grid), and if it is not impassable the eight
// neighbours are scanned for an unassigned one. When such a neighbour exists
// and the neighbourhood spans at most four distinct connected zones, the cell
// simply inherits that neighbour's zone id; otherwise the whole map's zones
// are recalculated.
void Map_0056D460::ResetZones(const Cell_0056D460& cell)
{
    int index = (unknown_F8 + unknown_F4 + 1) * cell.Y + cell.X;
    if (index < 0)
        index = 0;
    else if (index >= ZoneCount)
        index = ZoneCount - 1;

    Zone_0056D460* here = &Zones[index];

    int len = DAT_0087F8DC + DAT_0087F8E0 + 1;
    int offsets[8];
    offsets[2] = 1;
    offsets[6] = -1;
    offsets[4] = len;
    offsets[0] = -len;
    offsets[1] = 1 - len;
    offsets[3] = len + 1;
    offsets[5] = len - 1;
    offsets[7] = -1 - len;

    if (here->Type != 7)
    {
        int i;
        int* step;
        for (i = 0, step = offsets; i < 8; i++, step++)
        {
            Zone_0056D460* found = here + *step;
            char type = found->Type;
            if (type == 0)
            {
                if (found != 0)
                {
                    int distinct = 0;
                    unsigned int last = 0;
                    int* probe = offsets;
                    int remaining = 8;
                    do
                    {
                        Zone_0056D460* other = here + *probe;
                        unsigned int id = other->Id;
                        if (ZoneConnections[id] != ZoneConnections[last] &&
                            other->Type != 7)
                        {
                            last = id;
                            distinct++;
                        }
                        probe++;
                        remaining--;
                    } while (remaining != 0);

                    if (distinct <= 3 && here->Type == 0)
                    {
                        here->Id = found->Id;
                        return;
                    }
                }
                break;
            }
        }

        DAT_0087F7E8.FUN_0056C510();
    }
}
