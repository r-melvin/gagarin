// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra (gamemd.exe v1.001 entry instructions, field reads, and embedded/parent vtable contents).
#ifndef GG_MATCH_UI_GADGET_DISPATCH_004B55A0_H
#define GG_MATCH_UI_GADGET_DISPATCH_004B55A0_H

#include "gadget_class_methods.h"
#include "../_rt/gg_static_assert.h"

struct GadgetDispatchView_004B55A0;

struct GadgetDispatchWordAt04_004B55A0 {
    char unknown_00[4];
    short unknown_04;
};

struct GadgetDispatchPart_004B55A0 : public GadgetClass {
    virtual void Slot33();
    virtual void Slot34();
    virtual void Slot35();
    virtual void Slot36();
    virtual int Slot37(); // touched at vtable +0x94
    virtual void Slot38();
    virtual void Slot39();
    virtual unsigned short* GetItem(int index); // touched at +0xA0
};

struct GadgetDispatchWidePart_004B55A0 : public GadgetClass {
    char unknown_24[0x34];
    GadgetDispatchWordAt04_004B55A0* unknown_58;
    char unknown_5C[4];
};

struct GadgetDispatchView_004B55A0 : public GadgetClass {
    int unknown_24;
    int unknown_28;
    int unknown_2C;
    int unknown_30;
    int unknown_34;
    int unknown_38;
    int unknown_3C;
    int unknown_40;
    int unknown_44;
    unsigned char unknown_48;
    char unknown_49[3];
    int unknown_4C;
    GadgetDispatchWidePart_004B55A0 Part50;
    GadgetDispatchPart_004B55A0 PartB0;

    virtual void Slot33();
    virtual void Slot34();
    virtual int FUN_004B55A0(); // slot 35
    virtual void Slot36();
    virtual void Slot37();
    virtual void Slot38();
    virtual void Slot39();
    virtual void Slot40();
    virtual void Slot41();
    virtual void FUN_004B5530(unsigned short* text); // slot 42
    virtual void Slot43();
    virtual int FUN_004B55B0(); // slot 44
    void FUN_004B54E0(int x, int y);
    void FUN_004B55D0(int value);
};

// VTABLE: GAMEMD 0x007E7FCC — parent address point; touched slots 35/42/44
// are 0x4B55A0/0x4B5530/0x4B55B0 from the retail memory image.
struct GadgetDispatchParentVtable_004B55A0 {
    void* slots_00_34[35];
    void* Slot35;
    void* slots_36_41[6];
    void* Slot42;
    void* Slot43;
    void* Slot44;
};

// VTABLE: GAMEMD 0x007ED10C — embedded +0xB0 part; touched slot 25=0x4E1A20,
// slot 37=0x4886B0, and slot 40=0x557AC0.
struct GadgetDispatchPartVtable_004B55A0 {
    void* slots_00_24[25];
    void* Slot25;
    void* slots_26_36[11];
    void* Slot37;
    void* slots_38_39[2];
    void* Slot40;
};

// VTABLE: GAMEMD 0x007E8088 — embedded +0x50 part; slot 25 is 0x4E1A20.
struct GadgetDispatchWideVtable_004B55A0 {
    void* slots_00_24[25];
    void* Slot25;
};

GG_STATIC_ASSERT(sizeof(void*) == 4);
GG_STATIC_ASSERT(offsetof(GadgetDispatchWordAt04_004B55A0, unknown_04) == 4);
GG_STATIC_ASSERT(sizeof(GadgetDispatchWordAt04_004B55A0) == 6);
GG_STATIC_ASSERT(offsetof(GadgetDispatchView_004B55A0, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(GadgetDispatchView_004B55A0, unknown_48) == 0x48);
GG_STATIC_ASSERT(offsetof(GadgetDispatchView_004B55A0, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(GadgetDispatchView_004B55A0, Part50) == 0x50);
GG_STATIC_ASSERT(offsetof(GadgetDispatchWidePart_004B55A0, unknown_58) == 0x58);
GG_STATIC_ASSERT(sizeof(GadgetDispatchWidePart_004B55A0) == 0x60);
GG_STATIC_ASSERT(offsetof(GadgetDispatchView_004B55A0, PartB0) == 0xB0);
GG_STATIC_ASSERT(sizeof(GadgetDispatchPart_004B55A0) == 0x24);
GG_STATIC_ASSERT(sizeof(GadgetDispatchView_004B55A0) == 0xD4);
GG_STATIC_ASSERT(offsetof(GadgetDispatchParentVtable_004B55A0, Slot35) == 0x8C);
GG_STATIC_ASSERT(offsetof(GadgetDispatchParentVtable_004B55A0, Slot42) == 0xA8);
GG_STATIC_ASSERT(offsetof(GadgetDispatchParentVtable_004B55A0, Slot44) == 0xB0);
GG_STATIC_ASSERT(sizeof(GadgetDispatchParentVtable_004B55A0) == 0xB4);
GG_STATIC_ASSERT(offsetof(GadgetDispatchPartVtable_004B55A0, Slot25) == 0x64);
GG_STATIC_ASSERT(offsetof(GadgetDispatchPartVtable_004B55A0, Slot37) == 0x94);
GG_STATIC_ASSERT(offsetof(GadgetDispatchPartVtable_004B55A0, Slot40) == 0xA0);
GG_STATIC_ASSERT(sizeof(GadgetDispatchPartVtable_004B55A0) == 0xA4);
GG_STATIC_ASSERT(offsetof(GadgetDispatchWideVtable_004B55A0, Slot25) == 0x64);
GG_STATIC_ASSERT(sizeof(GadgetDispatchWideVtable_004B55A0) == 0x68);

#endif
