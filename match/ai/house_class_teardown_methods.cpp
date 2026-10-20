// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4FB920.

#include "house_class_teardown_methods.h"

// FUNCTION: GAMEMD 0x4FB920
//
// Scalar-deleting-destroy everything that belongs to this house, then the
// house itself: every techno whose Owner is this house, every trigger whose
// type is bound to this house's country, and finally `delete this`.  Each
// deletion pulls the array in by one, so the index is stepped back to
// re-examine the slot.
//
// Two shapes are load-bearing for the bytes.  The Items pointer is cached in a
// local before each loop and re-fetched after the delete (the call may
// reallocate the vector) while Count is re-read from the global every
// iteration — that is the preheader `MOV EAX,[Items]` with the reload after
// `CALL [EDX+0x20]` and the `MOV ECX,[Count]` at the loop bottom.  And the
// element is read through the global for the ownership test but through the
// cached local for the delete: VC6 folds the global's Items load into the
// cached register but does not CSE the two element reads, which keeps the
// cached pointer live across the call (vtable temp in EDX, not EAX) and, in
// the trigger loop, re-reads the element after the compare instead of
// spending EBX on it.  One local copy of the element scores 96.3% / 94.4%.
void HouseClass::SDDTORAllAndTriggers()
{
    int i;

    i = 0;
    if (i < TechnoArray.Count) {
        TechnoClass** technos = (TechnoClass**)TechnoArray.Items;
        do {
            if (((TechnoClass**)TechnoArray.Items)[i]->Owner == this) {
                delete technos[i];
                technos = (TechnoClass**)TechnoArray.Items;
                i--;
            }
            i++;
        } while (i < TechnoArray.Count);
    }

    i = 0;
    if (i < TriggerArray.Count) {
        TriggerClass** triggers = (TriggerClass**)TriggerArray.Items;
        do {
            if (((TriggerClass**)TriggerArray.Items)[i]->Type->House == this->Type) {
                delete triggers[i];
                triggers = (TriggerClass**)TriggerArray.Items;
                i--;
            }
            i++;
        } while (i < TriggerArray.Count);
    }

    delete this;
}
