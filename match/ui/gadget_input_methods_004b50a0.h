// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Entry-origin bodies at 0x004B50A0 (0x1F), 0x004B50C0 (0xC8),
//   0x004B5190 (0x5B), and 0x004B51F0 (0x1F) establish every member offset
//   below. Parent table 0x007E7FCC slots 6/18 target 0x00556640/0x004E1960.
//   Constructor 0x004B53E0 delegates the +0xB0 part to 0x00557380; its table
//   0x007ED10C slots 3/9/18/39 target 0x00557E10/0x00557F00/0x00557FD0/
//   0x00557AE0. The helper at 0x007CA422 is a retail count-bounded 16-bit copy.
#ifndef GG_GADGET_INPUT_METHODS_004B50A0_H
#define GG_GADGET_INPUT_METHODS_004B50A0_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "gadget_class_methods.h"

struct GadgetInputPartView_004B50A0 {
    virtual void Slot0(); virtual void Slot1(); virtual void Slot2();
    virtual void Slot3(LinkClass* value); virtual void Slot4(); virtual void Slot5();
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
    virtual void Slot36(); virtual void Slot37(); virtual void Slot38();
    virtual unsigned short* Slot39();
};

struct GadgetInputView_004B50A0 : public GadgetClass {
    void FUN_004B50A0();
    void FUN_004B50C0(unsigned char flags, unsigned int* state, int* target);
    void FUN_004B5190();
    void FUN_004B51F0();
    int unknown_24;
    char unknown_28[0x0C];
    unsigned short* unknown_34;
    int unknown_38;
    char unknown_3C[0x0C];
    unsigned char unknown_48;
    char unknown_49[0x03];
    int unknown_4C;
    char unknown_50[0x60];
    GadgetInputPartView_004B50A0 PartB0;
    char unknown_B4[0x08];
    int cache_BC;
    int cache_C0;
    int cache_C4;
    int cache_C8;
};

// VTABLE: GAMEMD 0x007E7FCC — touched parent-table prefix.
struct GadgetInputParentVtable_004B50A0 {
    void* slots[6];
    void* Slot6;
    void* slots_7_17[11];
    void* Slot18;
};
// VTABLE: GAMEMD 0x007ED10C — touched embedded-part table prefix.
struct GadgetInputPartVtable_004B50A0 {
    void* slots[3];
    void* Slot3;
    void* slots_4_8[5];
    void* Slot9;
    void* slots_10_17[8];
    void* Slot18;
    void* slots_19_38[20];
    void* Slot39;
};

GG_STATIC_ASSERT(sizeof(void*) == 4);
GG_STATIC_ASSERT(sizeof(GadgetInputPartView_004B50A0) == 4);
GG_STATIC_ASSERT(offsetof(GadgetInputView_004B50A0, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(GadgetInputView_004B50A0, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(GadgetInputView_004B50A0, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(GadgetInputView_004B50A0, unknown_48) == 0x48);
GG_STATIC_ASSERT(offsetof(GadgetInputView_004B50A0, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(GadgetInputView_004B50A0, unknown_50) == 0x50);
GG_STATIC_ASSERT(offsetof(GadgetInputView_004B50A0, PartB0) == 0xB0);
GG_STATIC_ASSERT(offsetof(GadgetInputView_004B50A0, cache_BC) == 0xBC);
GG_STATIC_ASSERT(offsetof(GadgetInputView_004B50A0, cache_C0) == 0xC0);
GG_STATIC_ASSERT(offsetof(GadgetInputView_004B50A0, cache_C4) == 0xC4);
GG_STATIC_ASSERT(offsetof(GadgetInputView_004B50A0, cache_C8) == 0xC8);
GG_STATIC_ASSERT(sizeof(GadgetInputView_004B50A0) == 0xCC);
GG_STATIC_ASSERT(offsetof(GadgetInputParentVtable_004B50A0, Slot6) == 0x18);
GG_STATIC_ASSERT(offsetof(GadgetInputParentVtable_004B50A0, Slot18) == 0x48);
GG_STATIC_ASSERT(sizeof(GadgetInputParentVtable_004B50A0) == 0x4C);
GG_STATIC_ASSERT(offsetof(GadgetInputPartVtable_004B50A0, Slot3) == 0x0C);
GG_STATIC_ASSERT(offsetof(GadgetInputPartVtable_004B50A0, Slot9) == 0x24);
GG_STATIC_ASSERT(offsetof(GadgetInputPartVtable_004B50A0, Slot18) == 0x48);
GG_STATIC_ASSERT(offsetof(GadgetInputPartVtable_004B50A0, Slot39) == 0x9C);
GG_STATIC_ASSERT(sizeof(GadgetInputPartVtable_004B50A0) == 0xA0);
#endif
