// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x439150.

#include "bomb_list_class_pointer_methods.h"

// FUNCTION: GAMEMD 0x439150  BombListClass::PointerGotInvalid (__thiscall, ret 0x4)
// Two passes over a dying object: drop it from the bomb list if it *is* a bomb,
// then clear it from every surviving bomb's target. The removal is
// DynamicVectorClass::RemoveItem written out inline — bounds check, decrement
// the count, shift the tail down.
void BombListClass::PointerGotInvalid(AbstractClass* invalid)
{
    BombClass* bomb = (BombClass*)invalid;

    int idx = FindItemIndex(bomb);
    if (idx != -1 && idx < Count)
    {
        Count--;
        for (int j = idx; j < Count; j++)
            Items[j] = Items[j + 1];
    }

    for (int i = 0; i < Count; i++)
    {
        BombClass* item = Items[i];
        if (item != 0 && item->Target == invalid)
            item->Target = 0;
    }
}
