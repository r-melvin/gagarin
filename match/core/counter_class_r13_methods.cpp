// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, slot displacements and increments read numerically off the user's
//   retail gamemd.exe v1.001 with the local Ghidra CLI at the addresses below.
//
// CounterClass (a VectorClass<int> plus the cached total at +0x10): the
// grow-on-index accessors. Ordered ascending by retail address.
#include "../_layout/house_class.h"

// FUNCTION: GAMEMD 0x49FA00
// Grows the vector to hold `index` (zeroing the new slots), counts it up and
// returns the new count; 0 if the vector could not grow.
int CounterClass::FUN_0049FA00(int index)
{
    int oldCapacity = Capacity;
    if (index >= oldCapacity) {
        if (SetCapacity(index + 10, 0)) {
            for (int i = oldCapacity; i < Capacity; i++)
                Items[i] = 0;
        } else {
            return 0;
        }
    }
    Items[index]++;
    Total++;
    return Items[index];
}

// FUNCTION: GAMEMD 0x49FA70
// As 0x49FA00 but counts the slot down; 0 if the vector could not grow.
int CounterClass::FUN_0049FA70(int index)
{
    int oldCapacity = Capacity;
    if (index >= oldCapacity) {
        if (SetCapacity(index + 10, 0)) {
            for (int i = oldCapacity; i < Capacity; i++)
                Items[i] = 0;
        } else {
            return 0;
        }
    }
    Items[index]--;
    Total--;
    return Items[index];
}

// FUNCTION: GAMEMD 0x49FAE0
// Grows the vector to hold `index` (zeroing the new slots) and reads it.
int CounterClass::FUN_0049FAE0(int index)
{
    int oldCapacity = Capacity;
    if (index >= oldCapacity) {
        if (SetCapacity(index + 10, 0)) {
            for (int i = oldCapacity; i < Capacity; i++)
                Items[i] = 0;
        } else {
            return 0;
        }
    }
    return Items[index];
}

// FUNCTION: GAMEMD 0x49FC80
// Grows the vector to hold `index`; false if it could not.
bool CounterClass::FUN_0049FC80(int index)
{
    int oldCapacity = Capacity;
    if (index < oldCapacity)
        return true;
    if (SetCapacity(index + 10, 0)) {
        for (int i = oldCapacity; i < Capacity; i++)
            Items[i] = 0;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x49FB70
// Writes the total, the capacity and then every slot; stops at the first failure.
HRESULT CounterClass::Save(IStream* stream)
{
    HRESULT hr = stream->Write(&Total, 4, 0);
    if (hr < 0)
        return hr;
    int capacity = Capacity;
    hr = stream->Write(&capacity, 4, 0);
    if (hr < 0)
        return hr;
    for (int i = 0; i < capacity; i++) {
        hr = stream->Write(&Items[i], 4, 0);
        if (hr < 0)
            return hr;
    }
    return 0;
}
