// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary | original
// Retail Fly 0x7E89F4 and DropPod 0x7E8278 have 50 ILocomotion
// pointer slots, followed by a pointer to the next primary-table RTTI COL.
// This evidence layout pins pointer positions, not semantic signatures or
// compiler-emitted table selection. Interface names remain separate evidence.
#ifndef GG_MATCH_MOVEMENT_LOCO_VTABLE_LAYOUT_H
#define GG_MATCH_MOVEMENT_LOCO_VTABLE_LAYOUT_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
struct LocoInterfaceVtableLayout
{
    void* slot_00; // +0x00
    void* slot_01; // +0x04
    void* slot_02; // +0x08
    void* slot_03; // +0x0C
    void* slot_04; // +0x10
    void* slot_05; // +0x14
    void* slot_06; // +0x18
    void* slot_07; // +0x1C
    void* slot_08; // +0x20
    void* slot_09; // +0x24
    void* slot_10; // +0x28
    void* slot_11; // +0x2C
    void* slot_12; // +0x30
    void* slot_13; // +0x34
    void* slot_14; // +0x38
    void* slot_15; // +0x3C
    void* slot_16; // +0x40
    void* slot_17; // +0x44
    void* slot_18; // +0x48
    void* slot_19; // +0x4C
    void* slot_20; // +0x50
    void* slot_21; // +0x54
    void* slot_22; // +0x58
    void* slot_23; // +0x5C
    void* slot_24; // +0x60
    void* slot_25; // +0x64
    void* slot_26; // +0x68
    void* slot_27; // +0x6C
    void* slot_28; // +0x70
    void* slot_29; // +0x74
    void* slot_30; // +0x78
    void* slot_31; // +0x7C
    void* slot_32; // +0x80
    void* slot_33; // +0x84
    void* slot_34; // +0x88
    void* slot_35; // +0x8C
    void* slot_36; // +0x90
    void* slot_37; // +0x94
    void* slot_38; // +0x98
    void* slot_39; // +0x9C
    void* slot_40; // +0xA0
    void* slot_41; // +0xA4
    void* slot_42; // +0xA8
    void* slot_43; // +0xAC
    void* slot_44; // +0xB0
    void* slot_45; // +0xB4
    void* slot_46; // +0xB8
    void* slot_47; // +0xBC
    void* slot_48; // +0xC0
    void* slot_49; // +0xC4
};
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_00) == 0x00);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_01) == 0x04);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_02) == 0x08);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_03) == 0x0C);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_04) == 0x10);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_05) == 0x14);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_06) == 0x18);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_07) == 0x1C);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_08) == 0x20);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_09) == 0x24);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_10) == 0x28);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_11) == 0x2C);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_12) == 0x30);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_13) == 0x34);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_14) == 0x38);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_15) == 0x3C);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_16) == 0x40);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_17) == 0x44);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_18) == 0x48);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_19) == 0x4C);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_20) == 0x50);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_21) == 0x54);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_22) == 0x58);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_23) == 0x5C);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_24) == 0x60);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_25) == 0x64);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_26) == 0x68);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_27) == 0x6C);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_28) == 0x70);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_29) == 0x74);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_30) == 0x78);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_31) == 0x7C);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_32) == 0x80);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_33) == 0x84);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_34) == 0x88);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_35) == 0x8C);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_36) == 0x90);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_37) == 0x94);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_38) == 0x98);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_39) == 0x9C);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_40) == 0xA0);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_41) == 0xA4);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_42) == 0xA8);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_43) == 0xAC);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_44) == 0xB0);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_45) == 0xB4);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_46) == 0xB8);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_47) == 0xBC);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_48) == 0xC0);
GG_STATIC_ASSERT(offsetof(LocoInterfaceVtableLayout, slot_49) == 0xC4);
GG_STATIC_ASSERT(sizeof(LocoInterfaceVtableLayout) == 0xC8);
#endif
