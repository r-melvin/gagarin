// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary; complete entry-origin retail instructions.
// REA: ev_2d3e69f099da1c7c4d1ed5ea91e56aedd902f16d3ec00ca15477a29270594435.
// Invalid buffers return zero in the first four entries, as encoded in retail.
#include "vector_lookup_family_00589dc0.h"
// FUNCTION: GAMEMD 0x589DC0
int VectorLookup4_00589DC0::FindFirst(const int& value) const
{
    if (!Valid) return 0;
    for (int i = 0; i < Count_08; ++i) if (Data[i] == value) return i;
    return -1;
}
// FUNCTION: GAMEMD 0x589E00
unsigned int VectorLookup4_00589DC0::IndexFirst(const int* item) const
{
    if (!Valid) return 0;
    return ((unsigned int)item - (unsigned int)Data) / 4;
}
// FUNCTION: GAMEMD 0x589FD0
int VectorLookup4_00589DC0::FindSecond(const int& value) const
{
    if (!Valid) return 0;
    for (int i = 0; i < Count_08; ++i) if (Data[i] == value) return i;
    return -1;
}
// FUNCTION: GAMEMD 0x58A010
unsigned int VectorLookup4_00589DC0::IndexSecond(const int* item) const
{
    if (!Valid) return 0;
    return ((unsigned int)item - (unsigned int)Data) / 4;
}
// FUNCTION: GAMEMD 0x58A0E0
int VectorLookup4_00589DC0::FindActive(const int& value) const
{
    for (int i = 0; i < Count_10; ++i) if (Data[i] == value) return i;
    return -1;
}
// FUNCTION: GAMEMD 0x58A230
int VectorLookup8_0058A230::Find(const int& value) const
{
    for (int i = 0; i < Count; ++i) if (Data[i].Key == value) return i;
    return -1;
}
// FUNCTION: GAMEMD 0x58A3A0
int VectorLookup12_0058A3A0::Find(const int& value) const
{
    for (int i = 0; i < Count; ++i) if (Data[i].Key == value) return i;
    return -1;
}
