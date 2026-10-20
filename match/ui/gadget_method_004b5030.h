// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Entry-origin disassembly of 0x004B5030 establishes the +0x34 short-string
//   field, +0xB0 subobject, and dispatch offsets 0x94/0xA0/0xA4/0xB8. The
//   parent constructor at 0x004B53E0 writes the +0x50/+0xB0 embedded vptrs;
//   the +0xB0 subobject table at 0x007ED10C has slot 37 -> 0x004886B0,
//   slot 40 -> 0x00557AC0, and slot 46 -> 0x00557F40. Parent table
//   0x007E7FCC slot 41 -> 0x004B5010. Names remain binary-derived placeholders.
#ifndef GG_GADGET_METHOD_004B5030_H
#define GG_GADGET_METHOD_004B5030_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "gadget_class_methods.h"

struct GadgetSubobjectView_004B5030 {
    virtual unsigned int Slot0(); virtual void Slot1(); virtual void Slot2();
    virtual void Slot3(); virtual void Slot4(); virtual void Slot5();
    virtual void Slot6(); virtual void Slot7(); virtual void Slot8();
    virtual void Slot9(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14();
    virtual void Slot15(); virtual void Slot16(); virtual void Slot17();
    virtual void Slot18(); virtual void Slot19(); virtual void Slot20();
    virtual void Slot21(); virtual void Slot22(); virtual void Slot23();
    virtual void Slot24(); virtual void Slot25(); virtual void Slot26();
    virtual void Slot27(); virtual void Slot28(); virtual void Slot29();
    virtual void Slot30(); virtual void Slot31(); virtual void Slot32();
    virtual void Slot33(); virtual void Slot34(); virtual void Slot35();
    virtual void Slot36(); virtual unsigned int Slot37();
    virtual void Slot38(); virtual void Slot39();
    virtual unsigned short* Slot40(unsigned int value);
    virtual void Slot41(); virtual void Slot42(); virtual void Slot43();
    virtual void Slot44(); virtual void Slot45();
    virtual void Slot46(unsigned int value);
};

struct GadgetMethodView_004B5030 : public GadgetClass {
    virtual void ExtraSlot33(); virtual void ExtraSlot34(); virtual void ExtraSlot35();
    virtual void ExtraSlot36(); virtual void ExtraSlot37(); virtual void ExtraSlot38();
    virtual void ExtraSlot39(); virtual void ExtraSlot40();
    virtual unsigned int Slot41();
    char unknown_24[0x10];
    unsigned short* unknown_34;
    char unknown_38[0x78];
    GadgetSubobjectView_004B5030 PartB0;
    void FUN_004B5030(unsigned int value);
};

struct GadgetParentVtable_004B5030 { void* slots[41]; void* Slot41; };
struct GadgetPartVtable_004B5030 {
    void* slots[37];
    void* Slot37;
    void* Slot38;
    void* Slot39;
    void* Slot40;
    void* Slot41;
    void* Slot42;
    void* Slot43;
    void* Slot44;
    void* Slot45;
    void* Slot46;
};

GG_STATIC_ASSERT(sizeof(void*) == 4);
GG_STATIC_ASSERT(sizeof(GadgetSubobjectView_004B5030) == 4);
GG_STATIC_ASSERT(offsetof(GadgetMethodView_004B5030, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(GadgetMethodView_004B5030, PartB0) == 0xB0);
GG_STATIC_ASSERT(sizeof(GadgetMethodView_004B5030) == 0xB4);
GG_STATIC_ASSERT(offsetof(GadgetParentVtable_004B5030, Slot41) == 0xA4);
GG_STATIC_ASSERT(sizeof(GadgetParentVtable_004B5030) == 0xA8);
GG_STATIC_ASSERT(offsetof(GadgetPartVtable_004B5030, Slot37) == 0x94);
GG_STATIC_ASSERT(offsetof(GadgetPartVtable_004B5030, Slot40) == 0xA0);
GG_STATIC_ASSERT(offsetof(GadgetPartVtable_004B5030, Slot46) == 0xB8);
GG_STATIC_ASSERT(sizeof(GadgetPartVtable_004B5030) == 0xBC);
#endif
