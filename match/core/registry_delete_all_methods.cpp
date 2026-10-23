// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Two translation units each carry an identical "delete everything" sweep over
// one global registry of objects: walk the registry from the back, and for
// each live entry delete it. The object's own destructor (inlined) takes the
// entry out of the registry through the virtual find slot and the by-index
// removal, so the live count shrinks as the sweep goes.
#include "vector_class_operations.h"

struct Item_0065FD50;
// GLOBAL: GAMEMD 0xB04DA8 -- the registry.
extern DynamicVectorClass<Item_0065FD50*> DAT_00B04DA8;
struct Item_0065FD50 {
    ~Item_0065FD50() { Item_0065FD50* self = this; DAT_00B04DA8.RemoveItem(self); }
};

// FUNCTION: GAMEMD 0x0065FD50
void FUN_0065FD50()
{
    for (int i = DAT_00B04DA8.Count - 1; i >= 0; --i) {
        Item_0065FD50* item = DAT_00B04DA8.Items[i];
        if (item != 0) {
            delete item;
        }
    }
}

// FUNCTION: GAMEMD 0x00660B00
void FUN_00660B00()
{
    for (int i = DAT_00B04DA8.Count - 1; i >= 0; --i) {
        Item_0065FD50* item = DAT_00B04DA8.Items[i];
        if (item != 0) {
            delete item;
        }
    }
}
