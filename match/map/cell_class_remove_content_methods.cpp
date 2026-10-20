// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x47EA90.

#include "cell_class_remove_content_methods.h"

// AbstractType discriminants returned by WhatAmI().
#define ABS_BUILDING 6      // CMP EAX,0x06
#define ABS_INFANTRY 0xF    // CMP EAX,0x0F

#define VTBL(obj) (*(Vtbl_0047EA90**)(obj))

// FUNCTION: GAMEMD 0x47EA90
//
// Unlink an occupier from the cell's ground (or, with `alt`, on-bridge) singly
// linked occupier list. When the object was the head the head is advanced;
// otherwise the list is walked for its predecessor. In either found case the
// object's own link is cleared. Afterwards every non-infantry object that
// answers slot +0xC0 gets its slot +0xF4 called with a coordinate: buildings
// are handed the centre of this cell, everything else its own Location.
void CellClass::RemoveContent(ObjectClass* object, bool alt)
{
    if (object == 0)
        return;

    ObjectClass* head = alt ? this->AltObject : this->FirstObject;
    if (head == object) {
        if (alt)
            this->AltObject = (ObjectClass*)object->NextObject;
        else
            this->FirstObject = (ObjectClass*)object->NextObject;
        object->NextObject = 0;
    } else {
        ObjectClass* prev = head;
        while (prev != 0) {
            if (prev->NextObject == object) {
                prev->NextObject = object->NextObject;
                object->NextObject = 0;
                break;
            }
            prev = (ObjectClass*)prev->NextObject;
        }
    }

    if ((object->*VTBL(object)->WhatAmI)() != ABS_INFANTRY
        && (object->*VTBL(object)->At_C0)()) {
        if ((object->*VTBL(object)->WhatAmI)() == ABS_BUILDING) {
            CoordStruct coord;
            coord.X = (this->MapCoords.X << 8) + 0x80;
            coord.Y = (this->MapCoords.Y << 8) + 0x80;
            coord.Z = 0;
            (object->*VTBL(object)->At_F4)(&coord);
        } else {
            CoordStruct coord = object->Location;
            (object->*VTBL(object)->At_F4)(&coord);
        }
    }
}
