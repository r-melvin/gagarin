// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | RTTI
// The two primary particle-type tables have 40 observed entries; their RTTI
// secondary tables have six entries and the two notice tables one each.
// These layouts pin slot indices, not final-link selection or method bodies.
#ifndef GG_MATCH_COMBAT_PARTICLES_TYPE_VTABLE_LAYOUT_H
#define GG_MATCH_COMBAT_PARTICLES_TYPE_VTABLE_LAYOUT_H
#include <stddef.h>
#include "../../_rt/gg_static_assert.h"

struct ParticleTypePrimaryVtableLayout
{
    void* slot_00;
    void* slot_01;
    void* slot_02;
    void* slot_03;
    void* slot_04;
    void* slot_05;
    void* slot_06;
    void* slot_07;
    void* slot_08;
    void* slot_09;
    void* slot_0A;
    void* slot_0B;
    void* slot_0C;
    void* slot_0D;
    void* slot_0E;
    void* slot_0F;
    void* slot_10;
    void* slot_11;
    void* slot_12;
    void* slot_13;
    void* slot_14;
    void* slot_15;
    void* slot_16;
    void* slot_17;
    void* slot_18;
    void* slot_19;
    void* slot_1A;
    void* slot_1B;
    void* slot_1C;
    void* slot_1D;
    void* slot_1E;
    void* slot_1F;
    void* slot_20;
    void* slot_21;
    void* slot_22;
    void* slot_23;
    void* slot_24;
    void* slot_25;
    void* slot_26;
    void* slot_27;
};
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_00) == 0x00);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_01) == 0x04);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_02) == 0x08);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_03) == 0x0C);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_04) == 0x10);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_05) == 0x14);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_06) == 0x18);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_07) == 0x1C);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_08) == 0x20);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_09) == 0x24);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_0A) == 0x28);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_0B) == 0x2C);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_0C) == 0x30);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_0D) == 0x34);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_0E) == 0x38);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_0F) == 0x3C);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_10) == 0x40);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_11) == 0x44);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_12) == 0x48);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_13) == 0x4C);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_14) == 0x50);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_15) == 0x54);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_16) == 0x58);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_17) == 0x5C);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_18) == 0x60);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_19) == 0x64);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_1A) == 0x68);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_1B) == 0x6C);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_1C) == 0x70);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_1D) == 0x74);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_1E) == 0x78);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_1F) == 0x7C);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_20) == 0x80);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_21) == 0x84);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_22) == 0x88);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_23) == 0x8C);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_24) == 0x90);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_25) == 0x94);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_26) == 0x98);
GG_STATIC_ASSERT(offsetof(ParticleTypePrimaryVtableLayout, slot_27) == 0x9C);
GG_STATIC_ASSERT(sizeof(ParticleTypePrimaryVtableLayout) == 0xA0);

struct ParticleTypeRttiVtableLayout
{
    void* slot_00;
    void* slot_01;
    void* slot_02;
    void* slot_03;
    void* slot_04;
    void* slot_05;
};
GG_STATIC_ASSERT(offsetof(ParticleTypeRttiVtableLayout, slot_00) == 0x00);
GG_STATIC_ASSERT(offsetof(ParticleTypeRttiVtableLayout, slot_01) == 0x04);
GG_STATIC_ASSERT(offsetof(ParticleTypeRttiVtableLayout, slot_02) == 0x08);
GG_STATIC_ASSERT(offsetof(ParticleTypeRttiVtableLayout, slot_03) == 0x0C);
GG_STATIC_ASSERT(offsetof(ParticleTypeRttiVtableLayout, slot_04) == 0x10);
GG_STATIC_ASSERT(offsetof(ParticleTypeRttiVtableLayout, slot_05) == 0x14);
GG_STATIC_ASSERT(sizeof(ParticleTypeRttiVtableLayout) == 0x18);

struct ParticleTypeNoticeVtableLayout
{
    void* slot_00;
};
GG_STATIC_ASSERT(offsetof(ParticleTypeNoticeVtableLayout, slot_00) == 0x00);
GG_STATIC_ASSERT(sizeof(ParticleTypeNoticeVtableLayout) == 0x4);

#endif
