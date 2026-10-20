// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x4AA2B0.

#include "map_class_next_object_methods.h"

// FUNCTION: GAMEMD 0x4AA2B0  MapClass::NextObject
//
// Tab-cycling: walk the three ordered layers and return the first selectable
// techno after `current`, wrapping round to the first selectable one found
// when `current` was last (or null). The techno view of the object is formed
// branchlessly from the flag bit before the first virtual, because it has to
// survive that call.
Obj_004AA2B0* Map_004AA2B0::NextObject(Obj_004AA2B0* current)
{
    Obj_004AA2B0* first = 0;
    bool found = false;
    if (current == 0)
        found = true;

    for (int n = 0; n < 3; ++n) {
        for (int i = 0; i < DAT_008A0360[DAT_00820030[n]].Count; ++i) {
            Obj_004AA2B0* obj = DAT_008A0360[DAT_00820030[n]].Items[i];
            if (obj != 0) {
                Obj_004AA2B0* techno = (obj->AbstractFlags & 1) ? obj : 0;
                if ((obj->*obj->Vptr->At_64)() && techno != 0
                    && (techno->*techno->Vptr->At_13C)()) {
                    if (first == 0)
                        first = obj;
                    if (found)
                        return obj;
                    if (current == obj)
                        found = true;
                }
            }
        }
    }
    return first;
}
