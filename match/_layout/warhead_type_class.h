// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: ctor 0x75CEC0 (docs/decomp_spec/type_hierarchy_layout.md,
//   "### WarheadTypeClass (start 0x98, size 0x1D0)"), member offsets from the
//   ctor member-access sites, cross-checked vs YRpp WarheadTypeClass.h. The
//   ctor chains the AbstractTypeClass parent ctor 0x410800. P2 layout-spine.
//
// WarheadTypeClass — the INI [Warheads] blueprint: damage Verses[] table,
// deform/debris/locomotor-disable behaviour. Derives AbstractTypeClass.
#ifndef GG_MATCH_LAYOUT_WARHEAD_TYPE_CLASS_H
#define GG_MATCH_LAYOUT_WARHEAD_TYPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_type_class.h"

// Pointer / TypeList / GUID members read as undefined4 / fixed-size blocks in
// the decomp. Pointers become real 4-byte pointers to opaque forward decls;
// the TypeList<T> (DynamicVectorClass + trailing dword, 0x1C) and the Locomotor
// _GUID (0x10) are modelled here as exact-size byte blocks.
struct AnimTypeClass;        // opaque (4-byte ptr target)
struct ParticleTypeClass;    // opaque (4-byte ptr target)

// TypeList<T> — DynamicVectorClass(0x18) + trailing dword; size = 0x1C.
struct WHT_TypeListBlock
{
    unsigned char _raw[0x1C];   // +0x00..0x1B
};
GG_STATIC_ASSERT(sizeof(WHT_TypeListBlock) == 0x1C);

// _GUID — Locomotor class id; size = 0x10.
struct WHT_GUIDBlock
{
    unsigned char _raw[0x10];   // +0x00..0x0F
};
GG_STATIC_ASSERT(sizeof(WHT_GUIDBlock) == 0x10);

// WarheadTypeClass  (0x98..0x1CF, sizeof = 0x1D0)
struct WarheadTypeClass : AbstractTypeClass
{
    double            Deform;              // +0x98
    double            Verses[0xB];         // +0xA0  (0xA0..0xF7)
    double            ProneDamage;         // +0xF8
    int               DeformTreshold;      // +0x100
    WHT_TypeListBlock AnimList;            // +0x104 (TypeList<AnimTypeClass*>)
    int               InfDeath;            // +0x120 (enum)
    float             CellSpread;          // +0x124
    float             CellInset;           // +0x128
    float             PercentAtMax;        // +0x12C
    bool              CausesDelayKill;     // +0x130
    unsigned char     _pad_131[3];         // +0x131 (align DelayKillFrames)
    int               DelayKillFrames;     // +0x134
    float             DelayKillAtMax;      // +0x138
    float             CombatLightSize;     // +0x13C
    ParticleTypeClass* Particle;           // +0x140

    // +0x144..0x15B — 24 × bool
    bool Wall;                   // +0x144
    bool WallAbsoluteDestroyer;  // +0x145
    bool PenetratesBunker;       // +0x146
    bool Wood;                   // +0x147
    bool Tiberium;               // +0x148
    bool unknown_bool_149;       // +0x149
    bool Sparky;                 // +0x14A
    bool Sonic;                  // +0x14B
    bool Fire;                   // +0x14C
    bool Conventional;           // +0x14D
    bool Rocker;                 // +0x14E
    bool DirectRocker;           // +0x14F
    bool Bright;                 // +0x150
    bool CLDisableRed;           // +0x151
    bool CLDisableGreen;         // +0x152
    bool CLDisableBlue;          // +0x153
    bool EMEffect;               // +0x154
    bool MindControl;            // +0x155
    bool Poison;                 // +0x156
    bool IvanBomb;               // +0x157
    bool ElectricAssault;        // +0x158
    bool Parasite;               // +0x159
    bool Temporal;               // +0x15A
    bool IsLocomotor;            // +0x15B

    WHT_GUIDBlock     Locomotor;           // +0x15C (_GUID, 0x10)

    // +0x16C..0x16E — 3 × bool
    bool Airstrike;              // +0x16C
    bool Psychedelic;            // +0x16D
    bool BombDisarm;             // +0x16E
    unsigned char     _pad_16F[1];         // +0x16F (align Paralyzes)
    int               Paralyzes;           // +0x170

    // +0x174..0x17B — 8 × bool
    bool Culling;                // +0x174
    bool MakesDisguise;          // +0x175
    bool NukeMaker;              // +0x176
    bool Radiation;              // +0x177
    bool PsychicDamage;          // +0x178
    bool AffectsAllies;          // +0x179
    bool Bullets;                // +0x17A
    bool Veinhole;               // +0x17B

    // +0x17C..0x18B — int × 4
    int ShakeXlo;                // +0x17C
    int ShakeXhi;                // +0x180
    int ShakeYlo;                // +0x184
    int ShakeYhi;                // +0x188

    WHT_TypeListBlock DebrisTypes;         // +0x18C (TypeList<VoxelAnimTypeClass*>)
    WHT_TypeListBlock DebrisMaximums;      // +0x1A8 (TypeList<int>)
    int               MaxDebris;           // +0x1C4
    int               MinDebris;           // +0x1C8
    unsigned long     unused_1CC;          // +0x1CC (DWORD)
};

GG_STATIC_ASSERT(offsetof(WarheadTypeClass, Deform)          == 0x98);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, Verses)          == 0xA0);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, ProneDamage)     == 0xF8);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, AnimList)        == 0x104);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, Particle)        == 0x140);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, Wall)            == 0x144);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, unknown_bool_149)== 0x149);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, Locomotor)       == 0x15C);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, Paralyzes)       == 0x170);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, ShakeXlo)        == 0x17C);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, DebrisTypes)     == 0x18C);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, DebrisMaximums)  == 0x1A8);
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, unused_1CC)      == 0x1CC);
GG_STATIC_ASSERT(sizeof(WarheadTypeClass)                    == 0x1D0);

#endif  // GG_MATCH_LAYOUT_WARHEAD_TYPE_CLASS_H
