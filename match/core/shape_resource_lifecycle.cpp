// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// /Ob1 and /Ob2 reproduce the matched lifetime entries.
// Native 69E090..69E429: tagged-resource loading and list/cache cleanup.
// The receiver identity is not attested, so address-based names are retained.
#include "../_layout/obj_0069e430.h"
#include "../platform/ccfile_class.h"

// GLOBAL: GAMEMD 0x00B077B0
Obj_0069E430* DAT_00B077B0;
// GLOBAL: GAMEMD 0x00B077B4
extern Obj_0069E430* DAT_00B077B4;
// GLOBAL: GAMEMD 0x00B077B8
extern int DAT_00B077B8;
// GLOBAL: GAMEMD 0x00B077BC
extern unsigned int DAT_00B077BC;

// FUNCTION: GAMEMD 0x69E100 -- inline body declared in obj_0069e430.h, emitted out of line here.
// FUNCTION: GAMEMD 0x69E090
void FUN_0069E090(Obj_0069E430* resource)
{
    if (resource->unknown_00 == -1 && !resource->unknown_10) {
        CCFileClass file(resource->unknown_08);
        Obj_0069E430* loaded = static_cast<Obj_0069E430*>(file.ReadWholeFile());
        if (loaded) {
            resource->unknown_0C = loaded;
            resource->unknown_10 = 1;
        }
    }
}

// FUNCTION: GAMEMD 0x69E180
void FUN_0069E180()
{
    Obj_0069E430* resource = DAT_00B077B0;
    while (resource) {
        Obj_0069E430* previous = resource->unknown_18;
        delete resource;
        resource = previous;
    }
    DAT_00B077B0 = 0;
}

// Partial 52.6%: list walk matches; native cache destruction retains member
// addresses in registers. /Ob1 and /Ob2 agree; further matching is held.
// FUNCTION: GAMEMD 0x69E210
void FUN_0069E210()
{
    for (Obj_0069E430* resource = DAT_00B077B0; resource; resource = resource->unknown_18)
        FUN_0069E100(resource);
    if (DAT_00B077B4) {
        delete DAT_00B077B4;
        DAT_00B077B4 = 0;
        DAT_00B077B8 = 0;
        DAT_00B077BC = 0;
    }
}

// Partial 54.1%: same shared-cache destruction delta as 69E210.
// FUNCTION: GAMEMD 0x69E320
void FUN_0069E320(unsigned int age)
{
    for (Obj_0069E430* resource = DAT_00B077B0; resource; resource = resource->unknown_18)
        if (resource->unknown_20 <= age) FUN_0069E100(resource);
    if (DAT_00B077B4) {
        delete DAT_00B077B4;
        DAT_00B077B4 = 0;
        DAT_00B077B8 = 0;
        DAT_00B077BC = 0;
    }
}

// SYNTHETIC: GAMEMD 0x69E930
// Obj_0069E430 scalar deleting destructor, emitted for the deletes above.
