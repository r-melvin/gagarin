// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: AnimTypeClass ctor FUN_0x00427530 member-access sites
//   Parent
//   ctor 0x5F7090 (ObjectTypeClass). Pad anchors unknown_2A4@0x2A4 and
//   unknown_double_320@0x320 confirmed; double slots (Damage@0x2A8,
//   Elasticity@0x310) and Layer@0x364 land only if the base sizeof == 0x294.
//
// AnimTypeClass — blueprint for SHP-based animations (explosions, fire, smoke,
// tiberium, craters, …). Derives ObjectTypeClass (the drawable-object-type
// spine) at offset 0, and adds the anim-specific frame/timing/spawn fields from
// 0x294 up to sizeof 0x378.
#ifndef GG_MATCH_LAYOUT_ANIM_TYPE_CLASS_H
#define GG_MATCH_LAYOUT_ANIM_TYPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "object_type_class.h"

// Opaque type targets — modelled as real 4-byte pointers (decomp shows
// undefined4 truncation at these member-write sites).
class WarheadTypeClass;
class OverlayTypeClass;

// RandomStruct — ranged-random pair (min/max ints), size = 8. Modelled
// as an exact-size byte block so downstream offsets stay byte-exact.
struct RandomStruct
{
    unsigned char _raw[8];   // +0x00..0x07
};

GG_STATIC_ASSERT(sizeof(RandomStruct) == 8);

// AnimTypeClass  (0x294..0x377, sizeof = 0x378)
class AnimTypeClass : public ObjectTypeClass
{
public:
    int           ArrayIndex;              // +0x294
    int           MiddleFrameIndex;        // +0x298
    int           MiddleFrameWidth;        // +0x29C
    int           MiddleFrameHeight;       // +0x2A0
    unsigned char unknown_2A4;             // +0x2A4
    unsigned char align_2A5[3];            // +0x2A5
    double        Damage;                  // +0x2A8
    int           Rate;                    // +0x2B0
    int           Start;                   // +0x2B4
    int           LoopStart;               // +0x2B8
    int           LoopEnd;                 // +0x2BC
    int           End;                     // +0x2C0
    int           LoopCount;               // +0x2C4
    AnimTypeClass* Next;                   // +0x2C8  (truncation)
    int           SpawnsParticle;          // +0x2CC
    int           NumParticles;            // +0x2D0
    int           DetailLevel;             // +0x2D4
    int           TranslucencyDetailLevel; // +0x2D8
    RandomStruct  RandomLoopDelay;         // +0x2DC  (8)
    RandomStruct  RandomRate;              // +0x2E4  (8)
    int           Translucency;            // +0x2EC
    AnimTypeClass* Spawns;                 // +0x2F0  (truncation)
    int           SpawnCount;              // +0x2F4
    int           Report;                  // +0x2F8
    int           StopSound;               // +0x2FC
    AnimTypeClass* BounceAnim;             // +0x300  (truncation)
    AnimTypeClass* ExpireAnim;             // +0x304  (truncation)
    AnimTypeClass* TrailerAnim;            // +0x308  (truncation)
    int           TrailerSeperation;       // +0x30C
    double        Elasticity;              // +0x310
    double        MinZVel;                 // +0x318
    double        unknown_double_320;      // +0x320
    double        MaxXYVel;                // +0x328
    WarheadTypeClass* Warhead;             // +0x330  (truncation)
    int           DamageRadius;            // +0x334
    OverlayTypeClass* TiberiumSpawnType;   // +0x338  (truncation)
    int           TiberiumSpreadRadius;    // +0x33C
    int           YSortAdjust;             // +0x340
    int           YDrawOffset;             // +0x344
    int           ZAdjust;                 // +0x348
    int           MakeInfantry;            // +0x34C
    int           RunningFrames;           // +0x350
    bool          IsFlamingGuy;            // +0x354
    bool          IsVeins;                 // +0x355
    bool          IsMeteor;                // +0x356
    bool          TiberiumChainReaction;   // +0x357
    bool          IsTiberium;              // +0x358
    bool          HideIfNoOre;             // +0x359
    bool          Bouncer;                 // +0x35A
    bool          Tiled;                   // +0x35B
    bool          ShouldUseCellDrawer;     // +0x35C
    bool          UseNormalLight;          // +0x35D
    bool          DemandLoad;              // +0x35E
    bool          FreeLoad;                // +0x35F
    bool          IsAnimatedTiberium;      // +0x360
    bool          AltPalette;              // +0x361
    bool          Normalized;              // +0x362
    unsigned char align_363;               // +0x363
    int           Layer;                   // +0x364  (enum)
    bool          DoubleThick;             // +0x368
    bool          Flat;                    // +0x369
    bool          Translucent;             // +0x36A
    bool          Scorch;                  // +0x36B
    bool          Flamer;                  // +0x36C
    bool          Crater;                  // +0x36D
    bool          ForceBigCraters;         // +0x36E
    bool          Sticky;                  // +0x36F
    bool          PingPong;                // +0x370
    bool          Reverse;                 // +0x371
    bool          Shadow;                  // +0x372
    bool          PsiWarning;              // +0x373
    bool          ShouldFogRemove;         // +0x374
    unsigned char align_375[3];            // +0x375
};

GG_STATIC_ASSERT(offsetof(AnimTypeClass, ArrayIndex)         == 0x294);
GG_STATIC_ASSERT(offsetof(AnimTypeClass, unknown_2A4)        == 0x2A4);
GG_STATIC_ASSERT(offsetof(AnimTypeClass, Damage)             == 0x2A8);
GG_STATIC_ASSERT(offsetof(AnimTypeClass, Rate)               == 0x2B0);
GG_STATIC_ASSERT(offsetof(AnimTypeClass, Next)               == 0x2C8);
GG_STATIC_ASSERT(offsetof(AnimTypeClass, RandomLoopDelay)    == 0x2DC);
GG_STATIC_ASSERT(offsetof(AnimTypeClass, Translucency)       == 0x2EC);
GG_STATIC_ASSERT(offsetof(AnimTypeClass, BounceAnim)         == 0x300);
GG_STATIC_ASSERT(offsetof(AnimTypeClass, Elasticity)         == 0x310);
GG_STATIC_ASSERT(offsetof(AnimTypeClass, unknown_double_320) == 0x320);
GG_STATIC_ASSERT(offsetof(AnimTypeClass, Warhead)            == 0x330);
GG_STATIC_ASSERT(offsetof(AnimTypeClass, TiberiumSpreadRadius)== 0x33C);
GG_STATIC_ASSERT(offsetof(AnimTypeClass, IsFlamingGuy)       == 0x354);
GG_STATIC_ASSERT(offsetof(AnimTypeClass, Normalized)         == 0x362);
GG_STATIC_ASSERT(offsetof(AnimTypeClass, Layer)              == 0x364);
GG_STATIC_ASSERT(offsetof(AnimTypeClass, DoubleThick)        == 0x368);
GG_STATIC_ASSERT(offsetof(AnimTypeClass, ShouldFogRemove)    == 0x374);
GG_STATIC_ASSERT(sizeof(AnimTypeClass)                       == 0x378);

#endif  // GG_MATCH_LAYOUT_ANIM_TYPE_CLASS_H
