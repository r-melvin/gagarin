// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Entry 438A90..438AF8, REA ev_5474ce0feecd99da094e63cb3b259d0fe7b6a1d2695f3deb32d9b9a29d3b6273.
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/abstract_class.h"
#include "../_layout/obj_004a1d30.h"
// The three runtime references select their own tables. Retail proves the
// stdcall slot at +0x10; their concrete dynamic types are not established here.
struct BombReferencedInterface_00438A90 {
    virtual void __stdcall Slot00();
    virtual void __stdcall Slot04();
    virtual void __stdcall Slot08();
    virtual void __stdcall Slot0C();
    virtual int __stdcall Slot10();
};
struct BombReferencedObject_00438A90 {
    void* unknown_00;
    BombReferencedInterface_00438A90 interface_04;
};
struct BombSerializeView_00438A90 {
    char unknown_00[0x24];
    BombReferencedObject_00438A90* unknown_24;
    BombReferencedObject_00438A90* unknown_28;
    BombReferencedObject_00438A90* unknown_2C;
    char unknown_30[0x28];
    bool unknown_58;
    void FUN_00438A90(Obj_004A1D30* sink);
};
GG_STATIC_ASSERT(sizeof(void*) == 4);
GG_STATIC_ASSERT(sizeof(BombReferencedInterface_00438A90) == 4);
GG_STATIC_ASSERT(offsetof(BombReferencedObject_00438A90, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(BombReferencedObject_00438A90, interface_04) == 4);
GG_STATIC_ASSERT(sizeof(BombReferencedObject_00438A90) == 8);
GG_STATIC_ASSERT(offsetof(BombSerializeView_00438A90, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(BombSerializeView_00438A90, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(BombSerializeView_00438A90, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(BombSerializeView_00438A90, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(BombSerializeView_00438A90, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(BombSerializeView_00438A90, unknown_58) == 0x58);
GG_STATIC_ASSERT(sizeof(BombSerializeView_00438A90) == 0x5C);
struct BombReferenceSlots_00438A90 {
    void* slot00;
    void* slot04;
    void* slot08;
    void* slot0C;
    int (__stdcall* slot10)(BombReferencedInterface_00438A90*);
};
GG_STATIC_ASSERT(offsetof(BombReferenceSlots_00438A90, slot00) == 0);
GG_STATIC_ASSERT(offsetof(BombReferenceSlots_00438A90, slot04) == 4);
GG_STATIC_ASSERT(offsetof(BombReferenceSlots_00438A90, slot08) == 8);
GG_STATIC_ASSERT(offsetof(BombReferenceSlots_00438A90, slot0C) == 0xC);
GG_STATIC_ASSERT(offsetof(BombReferenceSlots_00438A90, slot10) == 0x10);
GG_STATIC_ASSERT(sizeof(BombReferenceSlots_00438A90) == 0x14);

// The AbstractClass slot-13 base body 410410 and helpers 4A1D50 and 4A1CA0 are thiscall with one stack word,
// confirmed by their entry disassembly and RET 4. The last takes a byte.
// FUNCTION: GAMEMD 0x00438A90
void BombSerializeView_00438A90::FUN_00438A90(Obj_004A1D30* sink) {
    ((AbstractClass*)this)->AbstractClass::vf_13(sink);
    if (unknown_28) sink->FUN_004A1D50(unknown_28->interface_04.Slot10());
    if (unknown_24) sink->FUN_004A1D50(unknown_24->interface_04.Slot10());
    if (unknown_2C) sink->FUN_004A1D50(unknown_2C->interface_04.Slot10());
    sink->FUN_004A1CA0(unknown_58);
}
