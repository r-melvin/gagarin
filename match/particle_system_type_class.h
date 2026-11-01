// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check (names only)
//   Layout from the retail gamemd.exe v1.001: RTTI .?AVParticleSystemTypeClass@@,
//   tables 0x7F00A8 (primary, 40 slots) / 0x7F008C (6) / 0x7F0084 (1) / 0x7F007C (1),
//   constructor 0x6440A0 (three allocations `push 0x310; call 0x7C8E17`, e.g. 0x644683),
//   member offsets from the constructor and from ReadINI 0x6442D0 / CRC 0x644700.
//   Names follow YRpp where the bodies confirm the behaviour.
//
// ParticleSystemTypeClass: the rules-side description of a particle system.
//
//   +0x00..+0x293 ObjectTypeClass members (ParticleTypeObjectView), ID at +0x24
//   +0x294 HoldsWhat   int       ctor -1; INI key HoldsWhat, looked up by 0x645430
//   +0x298 Spawns      bool      ctor 0; key Spawns
//   +0x29C SpawnFrames int       ctor 1; key SpawnFrames
//   +0x2A0 Slowdown    float     ctor 0; key Slowdown
//   +0x2A4 ParticleCap int       ctor 50; key ParticleCap (vf_69 divides the particle count by it)
//   +0x2A8 SpawnRadius int       ctor 0; key SpawnRadius
//   +0x2AC SpawnCutoff float     ctor 0; key SpawnCutoff
//   +0x2B0 SpawnTranslucencyCutoff float  ctor 0; key SpawnTranslucencyCutoff
//   +0x2B4 BehavesLike int       ctor -1; key BehavesLike matched against the names Smoke, Gas,
//                                Fire, Spark, Railgun (table 0x836EE0); Update switches on it
//   +0x2B8 Lifetime    int       ctor -1; key Lifetime
//   +0x2BC SpawnDirection ParticleCoord  ctor 0; key SpawnDirection
//   +0x2C8 ParticlesPerCoord double   ctor 0.1; key ParticlesPerCoord
//   +0x2D0 SpiralDeltaPerCoord double ctor 0.025; key SpiralDeltaPerCoord
//   +0x2D8 SpiralRadius double   ctor 25.0; key SpiralRadius
//   +0x2E0 PositionPerturbationCoefficient double  ctor 0; key of the same name
//   +0x2E8 MovementPerturbationCoefficient double  ctor 0; key of the same name
//   +0x2F0 VelocityPerturbationCoefficient double  ctor 0; key of the same name
//   +0x2F8 SpawnSparkPercentage double ctor 0; key SpawnSparkPercentage
//   +0x300 SparkSpawnFrames int  ctor 0; key SparkSpawnFrames
//   +0x304 LightSize   int       ctor 0; key LightSize (vf_69 scales the light by it)
//   +0x308 LaserColor  ParticleColor ctor 0; key LaserColor
//   +0x30B Laser       bool      ctor 0; key Laser
//   +0x30C OneFrameLight bool    ctor 0; key OneFrameLight (vf_69 enable)
//   sizeof == 0x310 (allocation 0x644683)
#ifndef GG_MATCH_EFFECTS_PARTICLES_PARTICLE_SYSTEM_TYPE_CLASS_H
#define GG_MATCH_EFFECTS_PARTICLES_PARTICLE_SYSTEM_TYPE_CLASS_H

#include "particle_common_types.h"
#include "particle_common_vectors.h"
#include "particle_common_views.h"
#include "particle_type_vtable_layout.h"

// GLOBAL: GAMEMD 0xA83D68 - the class-wide array of particle system types.
extern ParticleInlineDynVector<ParticleSystemTypeClass*> DAT_00A83D68;

// VTABLE: GAMEMD 0x7F00A8 // primary, complete-object offset +0
// VTABLE: GAMEMD 0x7F008C // ParticleRttiBase subobject at +4
// VTABLE: GAMEMD 0x7F0084 // ParticleNoticeSinkBase subobject at +8
// VTABLE: GAMEMD 0x7F007C // ParticleNoticeSourceBase subobject at +0xC

class ParticleSystemTypeClass : public ParticleTypeObjectView
{
public:
    // FUNCTION: GAMEMD 0x6440A0
    ParticleSystemTypeClass(const char* id);
    static ParticleSystemTypeClass* FindOrAllocate(const char* id);
    // No-init constructor (Load re-runs it through placement new): only the base
    // no-init constructor (0x5F7320) and the four vptrs.
    ParticleSystemTypeClass(const ParticleNoInit& noInit) : ParticleTypeObjectView(noInit) {}
    // FUNCTION: GAMEMD 0x644250 (destructor; slot 8 holds the scalar deleting destructor 0x644960,
    // which expands this body).
    virtual ~ParticleSystemTypeClass();

    // ---- primary table overrides --------------------------------------------
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);              // 0x6447A0
    virtual HRESULT __stdcall Load(IStream* pStm);                      // 0x6447E0
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);    // 0x644830
    virtual int WhatAmI();                                              // 0x644930
    virtual int Size();                                                 // 0x644920
    virtual void ComputeCRC(ParticleCrcView& crc);                    // 0x644700
    virtual bool ReadINI(ParticleIniView* ini);                             // 0x6442D0
    virtual bool vf_32(int a, int b);                                   // 0x644940
    virtual int vf_35(int a);                                           // 0x644950

    // ---- members ------------------------------------------------------------
    int           HoldsWhat;       // +0x294
    bool          Spawns;     // +0x298
    int           SpawnFrames;     // +0x29C
    float         Slowdown;     // +0x2A0
    int           ParticleCap;     // +0x2A4
    int           SpawnRadius;     // +0x2A8
    float         SpawnCutoff;     // +0x2AC
    float         SpawnTranslucencyCutoff;     // +0x2B0
    int           BehavesLike;        // +0x2B4
    int           Lifetime;     // +0x2B8
    ParticleCoord     SpawnDirection;     // +0x2BC
    double        ParticlesPerCoord;     // +0x2C8
    double        SpiralDeltaPerCoord;     // +0x2D0
    double        SpiralRadius;     // +0x2D8
    double        PositionPerturbationCoefficient;     // +0x2E0
    double        MovementPerturbationCoefficient;     // +0x2E8
    double        VelocityPerturbationCoefficient;     // +0x2F0
    double        SpawnSparkPercentage;     // +0x2F8
    int           SparkSpawnFrames;     // +0x300
    int           LightSize;     // +0x304
    ParticleColor     LaserColor;     // +0x308
    bool          Laser;     // +0x30B
    bool          OneFrameLight;     // +0x30C
    unsigned char unknown_30D[3];  // +0x30D
};

GG_STATIC_ASSERT(offsetof(ParticleSystemTypeClass, HoldsWhat)   == 0x294);
GG_STATIC_ASSERT(offsetof(ParticleSystemTypeClass, Spawns) == 0x298);
GG_STATIC_ASSERT(offsetof(ParticleSystemTypeClass, SpawnFrames) == 0x29C);
GG_STATIC_ASSERT(offsetof(ParticleSystemTypeClass, Slowdown) == 0x2A0);
GG_STATIC_ASSERT(offsetof(ParticleSystemTypeClass, ParticleCap) == 0x2A4);
GG_STATIC_ASSERT(offsetof(ParticleSystemTypeClass, SpawnRadius) == 0x2A8);
GG_STATIC_ASSERT(offsetof(ParticleSystemTypeClass, SpawnCutoff) == 0x2AC);
GG_STATIC_ASSERT(offsetof(ParticleSystemTypeClass, SpawnTranslucencyCutoff) == 0x2B0);
GG_STATIC_ASSERT(offsetof(ParticleSystemTypeClass, BehavesLike)    == 0x2B4);
GG_STATIC_ASSERT(offsetof(ParticleSystemTypeClass, Lifetime) == 0x2B8);
GG_STATIC_ASSERT(offsetof(ParticleSystemTypeClass, SpawnDirection) == 0x2BC);
GG_STATIC_ASSERT(offsetof(ParticleSystemTypeClass, ParticlesPerCoord) == 0x2C8);
GG_STATIC_ASSERT(offsetof(ParticleSystemTypeClass, SpiralDeltaPerCoord) == 0x2D0);
GG_STATIC_ASSERT(offsetof(ParticleSystemTypeClass, SpiralRadius) == 0x2D8);
GG_STATIC_ASSERT(offsetof(ParticleSystemTypeClass, PositionPerturbationCoefficient) == 0x2E0);
GG_STATIC_ASSERT(offsetof(ParticleSystemTypeClass, MovementPerturbationCoefficient) == 0x2E8);
GG_STATIC_ASSERT(offsetof(ParticleSystemTypeClass, VelocityPerturbationCoefficient) == 0x2F0);
GG_STATIC_ASSERT(offsetof(ParticleSystemTypeClass, SpawnSparkPercentage) == 0x2F8);
GG_STATIC_ASSERT(offsetof(ParticleSystemTypeClass, SparkSpawnFrames) == 0x300);
GG_STATIC_ASSERT(offsetof(ParticleSystemTypeClass, LightSize) == 0x304);
GG_STATIC_ASSERT(offsetof(ParticleSystemTypeClass, LaserColor) == 0x308);
GG_STATIC_ASSERT(offsetof(ParticleSystemTypeClass, Laser) == 0x30B);
GG_STATIC_ASSERT(offsetof(ParticleSystemTypeClass, OneFrameLight) == 0x30C);
GG_STATIC_ASSERT(sizeof(ParticleSystemTypeClass) == 0x310);   // allocation 0x644683

#endif  // GG_MATCH_EFFECTS_PARTICLES_PARTICLE_SYSTEM_TYPE_CLASS_H
