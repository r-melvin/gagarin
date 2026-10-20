// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4A9720.

#include "display_class_submit_methods.h"

// FUNCTION: GAMEMD 0x4A9720  DisplayClass::Submit (__thiscall, ret 0x4)
// Put an object into its draw layer. An object already filed somewhere is
// pulled out first, an object that belongs nowhere (-1) is dropped, and only a
// successful insert updates the remembered layer. Layer 2 is the sorted one.
void DisplayClass::Submit(ObjectClass* object)
{
    if (object == 0)
        return;

    if (object->LastLayer != -1)
        Remove(object);

    int layer = OBJ_IN_WHICH_LAYER(object);
    if (layer == -1)
        return;

    if (DisplayLayers[layer].AddItem(object, layer == 2))
        object->LastLayer = layer;
}
