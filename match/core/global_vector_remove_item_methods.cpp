// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// By-value removal of `this` from a global DynamicVectorClass<T*>: the
// canonical RemoveItem (virtual FindItemIndex, then Delete) applied to a
// file-scope vector. Five retail copies, one per
// global vector; the element types of three of them are placeholders.
#include "vector_class_operations.h"
#include "../_layout/vox_class.h"

// Owners: each function removes `this` from the global vector of its own class.
// Item_<ADDR> are placeholder owners; VocClass and VoxClass carry no RTTI.
struct VocClass
{
    void FUN_007503F0();
};
class Item_0053CB90
{
public:
    void FUN_0053CB90();
};
class Item_0054FFB0
{
public:
    void FUN_0054FFB0();
    static void FUN_00550000();
};
class Item_0065FD00
{
public:
    void FUN_0065FD00();
};

// GLOBAL: GAMEMD 0xAA0118
extern DynamicVectorClass<Item_0053CB90*> DAT_00AA0118;
// GLOBAL: GAMEMD 0xABC878
extern DynamicVectorClass<Item_0054FFB0*> DAT_00ABC878;
// GLOBAL: GAMEMD 0xB04DA8
extern DynamicVectorClass<Item_0065FD00*> DAT_00B04DA8;
// GLOBAL: GAMEMD 0xB1D378
extern DynamicVectorClass<VocClass*> DAT_00B1D378;

// FUNCTION: GAMEMD 0x53CB90
void Item_0053CB90::FUN_0053CB90()
{
    DAT_00AA0118.RemoveItem(this);
}

// FUNCTION: GAMEMD 0x54FFB0
void Item_0054FFB0::FUN_0054FFB0()
{
    DAT_00ABC878.RemoveItem(this);
}

// FUNCTION: GAMEMD 0x550000
// Free every element of the global vector, taking each one out before it is deleted.
void Item_0054FFB0::FUN_00550000()
{
    while (DAT_00ABC878.Count != 0) {
        Item_0054FFB0* item = DAT_00ABC878.Items[0];
        if (item != 0) {
            Item_0054FFB0* key = item;
            DAT_00ABC878.RemoveItem(key);
            delete item;
        }
    }
}

// FUNCTION: GAMEMD 0x65FD00
void Item_0065FD00::FUN_0065FD00()
{
    DAT_00B04DA8.RemoveItem(this);
}

// FUNCTION: GAMEMD 0x7503F0
void VocClass::FUN_007503F0()
{
    DAT_00B1D378.RemoveItem(this);
}

// FUNCTION: GAMEMD 0x752D60
void VoxClass::FUN_00752D60()
{
    DAT_00B1D4A0.RemoveItem(this);
}
