// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Local REA evidence ev_60678dfa06e99487eb12af1b12241bcd3ee0a8db6aaca9d00dcd8a6e99777bb9
//   and ev_0f7fc9480d6080154cac53acbdce416d1af868fb3e74341de6fb1d898a13b0ca
//   records the complete entry-origin bodies at 0x004B4F80 (0x2F bytes) and
//   0x004B4FB0 (0x38 bytes). Each field displacement and virtual slot below is
//   read from those retail instructions; method names remain placeholders. The
//   qualified GadgetClass::Remove call and virtual MarkRedraw call identify the
//   shared GadgetClass base. Constructor 0x004B53E0 installs the +0x50
//   subobject vptr 0x007E8088; the +0xB0 subobject constructor installs
//   0x007ED10C. Retail table reads confirm +0x50 slot 9 at +0x24 targets
//   0x004E1480; +0xB0 slot 9 at +0x24 targets 0x00557F00, and slot 34 at
//   +0x88 targets 0x005576A0. These are the actual embedded tables invoked
//   by the two methods, not the base GadgetClass table.
#ifndef GG_GADGET_DERIVED_VIEWS_004B4F80_H
#define GG_GADGET_DERIVED_VIEWS_004B4F80_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "gadget_class_methods.h"

struct GadgetPartSlot9_004B4F80 {
    virtual void Slot0(); virtual void Slot1(); virtual void Slot2();
    virtual void Slot3(); virtual void Slot4(); virtual void Slot5();
    virtual void Slot6(); virtual void Slot7(); virtual void Slot8();
    virtual void Slot9();
};

struct GadgetPartSlot34_004B4F80 {
    virtual void Slot0(); virtual void Slot1(); virtual void Slot2();
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
    virtual void Slot33(); virtual void Slot34(void* value);
};

struct GadgetDerivedView_004B4F80 : public GadgetClass {
    void FUN_004B4F80();
    char unknown_24[0x24];
    unsigned char unknown_48;
    char unknown_49[0x07];
    GadgetPartSlot9_004B4F80 Part50;
    char unknown_54[0x5C];
    GadgetPartSlot9_004B4F80 PartB0;
};

struct GadgetDerivedMethodView_004B4FB0 : public GadgetClass {
    void FUN_004B4FB0(unsigned short* value);
    char unknown_24[0x10];
    unsigned short* unknown_34;
    int unknown_38;
    char unknown_3C[0x74];
    GadgetPartSlot34_004B4F80 PartB0;
};

GG_STATIC_ASSERT(sizeof(void*) == 4);
GG_STATIC_ASSERT(sizeof(GadgetPartSlot9_004B4F80) == 4);
GG_STATIC_ASSERT(sizeof(GadgetPartSlot34_004B4F80) == 4);
GG_STATIC_ASSERT(offsetof(GadgetDerivedView_004B4F80, unknown_48) == 0x48);
GG_STATIC_ASSERT(offsetof(GadgetDerivedView_004B4F80, Part50) == 0x50);
GG_STATIC_ASSERT(offsetof(GadgetDerivedView_004B4F80, PartB0) == 0xB0);
GG_STATIC_ASSERT(offsetof(GadgetDerivedMethodView_004B4FB0, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(GadgetDerivedMethodView_004B4FB0, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(GadgetDerivedMethodView_004B4FB0, PartB0) == 0xB0);
struct GadgetPartSlot9Vtable_004B4F80 { void* slots[9]; void* Slot9; };
struct GadgetPartSlot34Vtable_004B4F80 { void* slots[34]; void* Slot34; };
GG_STATIC_ASSERT(offsetof(GadgetPartSlot9Vtable_004B4F80, Slot9) == 0x24);
GG_STATIC_ASSERT(offsetof(GadgetPartSlot34Vtable_004B4F80, Slot34) == 0x88);
GG_STATIC_ASSERT(sizeof(GadgetPartSlot9Vtable_004B4F80) == 0x28);
GG_STATIC_ASSERT(sizeof(GadgetPartSlot34Vtable_004B4F80) == 0x8C);
GG_STATIC_ASSERT(sizeof(GadgetDerivedView_004B4F80) == 0xB4);
GG_STATIC_ASSERT(sizeof(GadgetDerivedMethodView_004B4FB0) == 0xB4);
#endif
