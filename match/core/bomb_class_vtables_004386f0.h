// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail BombClass tables and RTTI, confirmed by raw memory reads.
#ifndef GG_BOMB_CLASS_VTABLES_004386F0_H
#define GG_BOMB_CLASS_VTABLES_004386F0_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// VTABLE: GAMEMD 0x007E3D10 — BombClass main view. Retail memory words by
// slot: 410260, 410300, 410310, 438B00, 410450, 438B40, 438BD0, 4103E0,
// 438F00, 410470, 410480, 4393E0, 4393D0, 438A90, 410490, 4104A0.
struct BombClassVtable_004386F0
{
    void* slot_00;
    void* slot_04;
    void* slot_08;
    void* slot_0C;
    void* slot_10;
    void* slot_14;
    void* slot_18;
    void* slot_1C;
    void* slot_20;
    void* slot_24;
    void* slot_28;
    void* slot_2C;
    void* slot_30;
    void* slot_34;
    void* slot_38;
    void* slot_3C;
};
GG_STATIC_ASSERT(offsetof(BombClassVtable_004386F0, slot_00) == 0x00);
GG_STATIC_ASSERT(offsetof(BombClassVtable_004386F0, slot_04) == 0x04);
GG_STATIC_ASSERT(offsetof(BombClassVtable_004386F0, slot_08) == 0x08);
GG_STATIC_ASSERT(offsetof(BombClassVtable_004386F0, slot_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(BombClassVtable_004386F0, slot_10) == 0x10);
GG_STATIC_ASSERT(offsetof(BombClassVtable_004386F0, slot_14) == 0x14);
GG_STATIC_ASSERT(offsetof(BombClassVtable_004386F0, slot_18) == 0x18);
GG_STATIC_ASSERT(offsetof(BombClassVtable_004386F0, slot_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(BombClassVtable_004386F0, slot_20) == 0x20);
GG_STATIC_ASSERT(offsetof(BombClassVtable_004386F0, slot_24) == 0x24);
GG_STATIC_ASSERT(offsetof(BombClassVtable_004386F0, slot_28) == 0x28);
GG_STATIC_ASSERT(offsetof(BombClassVtable_004386F0, slot_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(BombClassVtable_004386F0, slot_30) == 0x30);
GG_STATIC_ASSERT(offsetof(BombClassVtable_004386F0, slot_34) == 0x34);
GG_STATIC_ASSERT(offsetof(BombClassVtable_004386F0, slot_38) == 0x38);
GG_STATIC_ASSERT(offsetof(BombClassVtable_004386F0, slot_3C) == 0x3C);
GG_STATIC_ASSERT(sizeof(BombClassVtable_004386F0) == 0x40);

// Secondary tables share BombClass TypeDescriptor 0x818C18. Their COL
// offsets are 4, 8 and 0xC respectively; the next COL bounds each table.
// VTABLE: GAMEMD 0x007E3CF4 — 4105E0, 4105F0, 410600, 410210, 410220, 410230.
struct BombClassSecondaryVtable_004386F0
{
    void* slot_00;
    void* slot_04;
    void* slot_08;
    void* slot_0C;
    void* slot_10;
    void* slot_14;
};
GG_STATIC_ASSERT(offsetof(BombClassSecondaryVtable_004386F0, slot_00) == 0x00);
GG_STATIC_ASSERT(offsetof(BombClassSecondaryVtable_004386F0, slot_04) == 0x04);
GG_STATIC_ASSERT(offsetof(BombClassSecondaryVtable_004386F0, slot_08) == 0x08);
GG_STATIC_ASSERT(offsetof(BombClassSecondaryVtable_004386F0, slot_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(BombClassSecondaryVtable_004386F0, slot_10) == 0x10);
GG_STATIC_ASSERT(offsetof(BombClassSecondaryVtable_004386F0, slot_14) == 0x14);
GG_STATIC_ASSERT(sizeof(BombClassSecondaryVtable_004386F0) == 0x18);

// VTABLE: GAMEMD 0x007E3CEC — sole target 410580, COL 7FC070.
// VTABLE: GAMEMD 0x007E3CE4 — sole target 410590, COL 7FC058.
struct BombClassSingleSlotVtable_004386F0 { void* slot_00; };
GG_STATIC_ASSERT(offsetof(BombClassSingleSlotVtable_004386F0, slot_00) == 0);
GG_STATIC_ASSERT(sizeof(BombClassSingleSlotVtable_004386F0) == 4);

#endif
