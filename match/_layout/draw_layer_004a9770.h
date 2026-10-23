// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Existing layer declaration extracted unchanged from display_class_remove_methods.h.
#ifndef GG_MATCH_LAYOUT_DRAW_LAYER_004A9770_H
#define GG_MATCH_LAYOUT_DRAW_LAYER_004A9770_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"
#include "object_class.h"

struct LayerVtbl_004A9770;

// One draw layer: a DynamicVectorClass<ObjectClass*>. Only the slot the
// inlined Delete dispatches through is typed.
struct Layer_004A9770
{
    LayerVtbl_004A9770* Vptr;      // +0x00
    ObjectClass**       Items;     // +0x04
    int                 Capacity;  // +0x08
    int                 IsAllocated; // +0x0C
    int                 Count;     // +0x10
    int                 CapacityIncrement; // +0x14

    // DynamicVectorClass::Delete, expanded inline at both call sites: look
    // the element up through the virtual ID, then close the gap. The element
    // is taken BY VALUE: ID wants its address, and retail passes the address
    // of the caller's parameter slot while keeping the parameter in EDI and
    // writing it back before each call (`MOV [ESP+0xC],EDI; LEA EAX,[ESP+0xC]`)
    // -- the by-value copy is a local whose home VC6 folds onto the stacked
    // parameter. A `const T&` parameter instead pins the caller's parameter
    // in memory for the whole function (no EDI, 4.5%).
    bool Delete(ObjectClass* object);
};
GG_STATIC_ASSERT(offsetof(Layer_004A9770, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(Layer_004A9770, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(Layer_004A9770) == 0x18);

typedef int (Layer_004A9770::*Fn10_004A9770)(ObjectClass* const* object);

struct LayerVtbl_004A9770
{
    char           _pad000[0x10];   // +0x0000
    Fn10_004A9770  ID;              // +0x0010
};
GG_STATIC_ASSERT(offsetof(LayerVtbl_004A9770, ID) == 0x10);

inline bool Layer_004A9770::Delete(ObjectClass* object)
{
    int id = (this->*this->Vptr->ID)(&object);
    if (id != -1 && id < this->Count)
    {
        this->Count--;
        for (int i = id; i < this->Count; i++)
            this->Items[i] = this->Items[i + 1];
        return true;
    }
    return false;
}

// GLOBAL: GAMEMD 0x8A0360 -- the draw-layer array (five layers).
extern Layer_004A9770 DAT_008A0360[5];

#endif
