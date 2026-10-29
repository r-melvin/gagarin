// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below.
//
// Growable array of 0x8008-byte elements (count, capacity, storage).
//
// Address index: 0x6C8870 0x6C8900

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

struct VectorBig_006C8870
{
    int   Count;       // +0x00
    int   Capacity;    // +0x04
    char* Items;       // +0x08

    // FUNCTION: GAMEMD 0x6C8900 (__thiscall)
    bool FUN_006C8900();
    // FUNCTION: GAMEMD 0x6C8870 (__thiscall)
    bool FUN_006C8870();
};
GG_STATIC_ASSERT(offsetof(VectorBig_006C8870, Capacity) == 0x04);
GG_STATIC_ASSERT(offsetof(VectorBig_006C8870, Items) == 0x08);
GG_STATIC_ASSERT(sizeof(VectorBig_006C8870) == 0x0C);

// FUNCTION: GAMEMD 0x6C8900
// Doubles the storage (at least ten elements) once the count reaches the
// capacity; the new storage is zeroed before the old contents are copied in.
bool VectorBig_006C8870::FUN_006C8900()
{
    if (Count < Capacity)
        return false;

    int nNew = Count * 2;

    if (nNew < 10)
        nNew = 10;

    char* pNew = new char[nNew * 0x8008];
    memset(pNew, 0, nNew * 0x8008);

    if (Items)
        memcpy(pNew, Items, Count * 0x8008);

    delete Items;
    Capacity = nNew;
    Items = pNew;
    return true;
}

// FUNCTION: GAMEMD 0x6C8870
// Halves the storage (never below ten elements) when the count has fallen
// to a third of the capacity.
bool VectorBig_006C8870::FUN_006C8870()
{
    if (Count * 3 > Capacity)
        return false;

    int nNew = Capacity / 2;

    if (nNew < 10)
        nNew = 10;

    if (nNew >= Capacity)
        return false;

    char* pNew = new char[nNew * 0x8008];

    if (Items)
        memcpy(pNew, Items, Count * 0x8008);

    delete Items;
    Items = pNew;
    Capacity = nNew;
    return true;
}
