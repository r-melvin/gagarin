// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4A9770.

#include "display_class_remove_methods.h"

// FUNCTION: GAMEMD 0x4A9770  DisplayClass::Remove (__thiscall, ret 0x4; `this` unused)
// Pull an object out of its draw layer. The remembered layer is tried first;
// if the object was not actually there, every layer is swept, deleting it as
// many times as it is found. Either way the remembered layer ends up -1.
void DisplayClass::Remove(ObjectClass* object)
{
    if (object == 0)
        return;

    int layer = object->LastLayer;
    if (layer == -1)
        return;

    if (DAT_008A0360[layer].Delete(object))
        object->LastLayer = -1;

    if (object->LastLayer != -1)
    {
        for (int i = 0; i < 5; i++)
        {
            while (DAT_008A0360[i].Delete(object))
                ;
        }
        object->LastLayer = -1;
    }
}
