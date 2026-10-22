// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, offsets and the layer-array base read off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x4A9770: the object's
//   LastLayer as `MOV EAX,[EDI+0x94]` / `MOV dword ptr [EDI+0x94],-1`
//   (ObjectClass spine, reconfirmed below); the 24-byte layer stride from
//   `LEA EAX,[EAX+EAX*2]` + `[EAX*8+0x8A0360]`; the layer's Items at +0x04
//   and Count at +0x10; the vector virtual at [vptr+0x10] called with the
//   address of the stacked object (`LEA EAX,[ESP+0xC]; PUSH EAX`), i.e.
//   DynamicVectorClass::ID(const T*); and the fallback sweep from 0x8A0370
//   (layer 0's Count) in 0x18 steps up to 0x8A03E8 = five layers. The method
//   name is YRpp's DisplayClass::Remove.
#ifndef GG_MATCH_UI_DISPLAY_CLASS_REMOVE_METHODS_H
#define GG_MATCH_UI_DISPLAY_CLASS_REMOVE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"
#include "../_layout/object_class.h"

GG_STATIC_ASSERT(offsetof(ObjectClass, LastLayer) == 0x94);

// Declaration order matters -- see match/_rt/gg_vslot.h.
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

struct DisplayClass
{
    // FUNCTION: GAMEMD 0x4A9770
    void Remove(ObjectClass* object);
};

#endif  // GG_MATCH_UI_DISPLAY_CLASS_REMOVE_METHODS_H
