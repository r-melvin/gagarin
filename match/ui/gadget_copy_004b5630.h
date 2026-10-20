// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra (gamemd.exe v1.001 entry instruction reads and field widths).
#ifndef GG_GADGET_COPY_004B5630_H
#define GG_GADGET_COPY_004B5630_H
#include "gadget_class_methods.h"
#include "../_rt/gg_static_assert.h"

struct GadgetCopyBaseView_004B5600 : public GadgetClass {
    // FUNCTION: GAMEMD 0x00556600 (decl; reloc)
    GadgetCopyBaseView_004B5600* FUN_00556600(GadgetCopyBaseView_004B5600* source);
};
struct GadgetCopySmallView_004B5780 : public GadgetCopyBaseView_004B5600 {
    // FUNCTION: GAMEMD 0x004B5780
    GadgetCopySmallView_004B5780* FUN_004B5780(GadgetCopySmallView_004B5780* source);
};
struct GadgetCopyWideView_004B5630 : public GadgetCopyBaseView_004B5600 {
    int unknown_24; int unknown_28;
    unsigned char unknown_2C; unsigned char unknown_2D; char unknown_2E[2];
    int unknown_30;
    unsigned char unknown_34; char unknown_35[3];
    int unknown_38; int unknown_3C;
    unsigned char unknown_40; char unknown_41[3];
    int unknown_44; int unknown_48;
    unsigned char unknown_4C; char unknown_4D[3];
    int unknown_50;
    unsigned char unknown_54; unsigned char unknown_55; char unknown_56[2];
    int unknown_58;
    unsigned char unknown_5C; char unknown_5D[3];
    // FUNCTION: GAMEMD 0x004B5630
    GadgetCopyWideView_004B5630* FUN_004B5630(GadgetCopyWideView_004B5630* source);
};
struct GadgetCopyOtherView_004B56E0 : public GadgetCopyBaseView_004B5600 {
    int unknown_24; int unknown_28;
    unsigned char unknown_2C; unsigned char unknown_2D; unsigned char unknown_2E; char unknown_2F;
    int unknown_30; int unknown_34; int unknown_38; int unknown_3C; int unknown_40;
    unsigned char unknown_44; char unknown_45[3];
    int unknown_48; int unknown_4C; int unknown_50;
    // FUNCTION: GAMEMD 0x004B56E0
    GadgetCopyOtherView_004B56E0* FUN_004B56E0(GadgetCopyOtherView_004B56E0* source);
};
GG_STATIC_ASSERT(sizeof(GadgetCopyBaseView_004B5600)==0x24);
GG_STATIC_ASSERT(sizeof(GadgetCopySmallView_004B5780)==0x24);
GG_STATIC_ASSERT(offsetof(GadgetCopyWideView_004B5630, unknown_24)==0x24);
GG_STATIC_ASSERT(offsetof(GadgetCopyWideView_004B5630, unknown_28)==0x28);
GG_STATIC_ASSERT(offsetof(GadgetCopyWideView_004B5630, unknown_2C)==0x2C);
GG_STATIC_ASSERT(offsetof(GadgetCopyWideView_004B5630, unknown_2D)==0x2D);
GG_STATIC_ASSERT(offsetof(GadgetCopyWideView_004B5630, unknown_30)==0x30);
GG_STATIC_ASSERT(offsetof(GadgetCopyWideView_004B5630, unknown_34)==0x34);
GG_STATIC_ASSERT(offsetof(GadgetCopyWideView_004B5630, unknown_38)==0x38);
GG_STATIC_ASSERT(offsetof(GadgetCopyWideView_004B5630, unknown_3C)==0x3C);
GG_STATIC_ASSERT(offsetof(GadgetCopyWideView_004B5630, unknown_40)==0x40);
GG_STATIC_ASSERT(offsetof(GadgetCopyWideView_004B5630, unknown_44)==0x44);
GG_STATIC_ASSERT(offsetof(GadgetCopyWideView_004B5630, unknown_48)==0x48);
GG_STATIC_ASSERT(offsetof(GadgetCopyWideView_004B5630, unknown_4C)==0x4C);
GG_STATIC_ASSERT(offsetof(GadgetCopyWideView_004B5630, unknown_50)==0x50);
GG_STATIC_ASSERT(offsetof(GadgetCopyWideView_004B5630, unknown_54)==0x54);
GG_STATIC_ASSERT(offsetof(GadgetCopyWideView_004B5630, unknown_55)==0x55);
GG_STATIC_ASSERT(offsetof(GadgetCopyWideView_004B5630, unknown_58)==0x58);
GG_STATIC_ASSERT(offsetof(GadgetCopyWideView_004B5630, unknown_5C)==0x5C);
GG_STATIC_ASSERT(sizeof(GadgetCopyWideView_004B5630)==0x60);
GG_STATIC_ASSERT(offsetof(GadgetCopyOtherView_004B56E0, unknown_24)==0x24);
GG_STATIC_ASSERT(offsetof(GadgetCopyOtherView_004B56E0, unknown_28)==0x28);
GG_STATIC_ASSERT(offsetof(GadgetCopyOtherView_004B56E0, unknown_2C)==0x2C);
GG_STATIC_ASSERT(offsetof(GadgetCopyOtherView_004B56E0, unknown_2D)==0x2D);
GG_STATIC_ASSERT(offsetof(GadgetCopyOtherView_004B56E0, unknown_2E)==0x2E);
GG_STATIC_ASSERT(offsetof(GadgetCopyOtherView_004B56E0, unknown_30)==0x30);
GG_STATIC_ASSERT(offsetof(GadgetCopyOtherView_004B56E0, unknown_34)==0x34);
GG_STATIC_ASSERT(offsetof(GadgetCopyOtherView_004B56E0, unknown_38)==0x38);
GG_STATIC_ASSERT(offsetof(GadgetCopyOtherView_004B56E0, unknown_3C)==0x3C);
GG_STATIC_ASSERT(offsetof(GadgetCopyOtherView_004B56E0, unknown_40)==0x40);
GG_STATIC_ASSERT(offsetof(GadgetCopyOtherView_004B56E0, unknown_44)==0x44);
GG_STATIC_ASSERT(offsetof(GadgetCopyOtherView_004B56E0, unknown_48)==0x48);
GG_STATIC_ASSERT(offsetof(GadgetCopyOtherView_004B56E0, unknown_4C)==0x4C);
GG_STATIC_ASSERT(offsetof(GadgetCopyOtherView_004B56E0, unknown_50)==0x50);
GG_STATIC_ASSERT(sizeof(GadgetCopyOtherView_004B56E0)==0x54);
#endif
