// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below.
//
// Growable array of 0x18-byte elements (count, capacity, storage).
//
// Address index: 0x624810 0x6248A0

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

struct Vector24_00624810
{
    int   Count;       // +0x00
    int   Capacity;    // +0x04
    char* Items;       // +0x08

    // FUNCTION: GAMEMD 0x624810 (__thiscall)
    bool FUN_00624810();
    // FUNCTION: GAMEMD 0x6248A0 (__thiscall)
    bool FUN_006248A0();
};
GG_STATIC_ASSERT(offsetof(Vector24_00624810, Capacity) == 0x04);
GG_STATIC_ASSERT(offsetof(Vector24_00624810, Items) == 0x08);
GG_STATIC_ASSERT(sizeof(Vector24_00624810) == 0x0C);

// FUNCTION: GAMEMD 0x624810
// Doubles the storage (at least ten elements) once the count reaches the
// capacity; the new storage is zeroed before the old contents are copied in.
bool Vector24_00624810::FUN_00624810()
{
    if (Count < Capacity)
        return false;

    int nNew = Count * 2;

    if (nNew < 10)
        nNew = 10;

    char* pNew = new char[nNew * 24];
    memset(pNew, 0, nNew * 24);

    if (Items)
        memcpy(pNew, Items, Count * 24);

    delete Items;
    Capacity = nNew;
    Items = pNew;
    return true;
}

// FUNCTION: GAMEMD 0x6248A0
// Halves the storage (never below ten elements) when the count has fallen
// to a third of the capacity.
bool Vector24_00624810::FUN_006248A0()
{
    if (Count * 3 > Capacity)
        return false;

    int nNew = Capacity / 2;

    if (nNew < 10)
        nNew = 10;

    if (nNew >= Capacity)
        return false;

    char* pNew = new char[nNew * 24];

    if (Items)
        memcpy(pNew, Items, Count * 24);

    delete Items;
    Items = pNew;
    Capacity = nNew;
    return true;
}
