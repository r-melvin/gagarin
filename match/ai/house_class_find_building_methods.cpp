// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4FD060.

#include "house_class_find_building_methods.h"

// Index of a type in BuildingTypeClass::Array, or -1. Inlined into the search
// below (`XOR EAX,EAX; TEST EDI,EDI; JLE; ... OR EAX,-1`).
static inline int TypeIndex_004FD060(BuildingType_004FD060* type)
{
    for (int i = 0; i < DAT_00A83C78; ++i) {
        if (DAT_00A83C6C[i] == type) {
            return i;
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x4FD060
//
// The first live building this house owns whose type has the given array
// index, optionally restricted to one map sector. The per-type counter is
// consulted first so houses without such a building skip the walk.
Building_004FD060* House_004FD060::FindBuildingOfType(int index, int sector)
{
    if (this->At_5500.GetCount(index) > 0) {
        int count = this->BuildingCount;
        for (int i = 0; i < count; ++i) {
            Building_004FD060* building = this->BuildingItems[i];
            if (building != 0 && building->InLimbo == 0) {
                if (TypeIndex_004FD060(building->Type) == index) {
                    if (sector == -1) {
                        return building;
                    }
                    Coord_004FD060 buf;
                    if (this->SectorOf((building->*building->Vtbl->GetCoords)(&buf)) == sector) {
                        return building;
                    }
                }
            }
        }
    }
    return 0;
}
