// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check (names only, consult-only)
//   Layout, tables and vptr offsets read from the retail gamemd.exe v1.001: RTTI
//   .?AVParticleTypeClass@@ (TD 0x8370D0; COL 0x8082F0 base 0 / vtable 0x7F0188, COL 0x808280 base 4 /
//   0x7F016C, COL 0x808268 base 8 / 0x7F0164, COL 0x808250 base 12 / 0x7F015C; chain ParticleTypeClass
//   -> ObjectTypeClass -> AbstractTypeClass -> AbstractClass -> IPersistStream -> IPersist -> IUnknown,
//   IRTTITypeInfo -> IUnknown, INoticeSink, INoticeSource), the constructor 0x644BE0 (retained as a capped partial candidate), the allocation sites 0x64536B, 0x645474, 0x645876, 0x6C583C
//   (`PUSH 0x318; CALL 0x7C8E17`, four sites, all agreeing), and the INI reader 0x644F50 (every key
//   string and member offset below).
//
// ParticleTypeClass: the rules-INI template of a particle ([Particle] sections). Derives the
// ObjectTypeClass-shaped partial view below.
//
//   +0x00..+0x293  ParticleTypeObjectView (AbstractClass / AbstractTypeClass / ObjectTypeClass members;
//                  the type name is at +0x24, passed as the INI section by the reader)
//   +0x294 NextParticleOffset (three dwords)  +0x2A0 XVelocity  +0x2A4 YVelocity
//   +0x2A8 MinZVelocity  +0x2AC ZVelocityRange  +0x2B0 ColorSpeed (double)
//   +0x2B8 ColorList (0x1C bytes: vector of 3-byte colours + one dword)
//   +0x2D4 StartColor1  +0x2D7 StartColor2  +0x2DC MaxDC  +0x2E0 MaxEC  +0x2E4 Warhead  +0x2E8 Damage
//   +0x2EC StartFrame  +0x2F0 NumLoopFrames  +0x2F4 Translucency  +0x2F8 WindEffect
//   +0x2FC Velocity (float)  +0x300 Deacc (float)  +0x304 Radius  +0x308 DeleteOnStateLimit
//   +0x309 EndStateAI  +0x30A StartStateAI  +0x30B StateAIAdvance  +0x30C FinalDamageState
//   +0x30D Translucent25State  +0x30E Translucent50State  +0x30F Normalized
//   +0x310 NextParticle (int index)  +0x314 BehavesLike (int enum)  sizeof 0x318 (allocation)
#ifndef GG_MATCH_EFFECTS_PARTICLES_PARTICLE_TYPE_CLASS_H
#define GG_MATCH_EFFECTS_PARTICLES_PARTICLE_TYPE_CLASS_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "particle_common_types.h"
#include "particle_common_views.h"
#include "particle_type_vtable_layout.h"
#include "particle_vectors.h"
#include "particle_type_shared.h"

// VTABLE: GAMEMD 0x7F0188 // primary, complete-object offset +0
// VTABLE: GAMEMD 0x7F016C // ParticleRttiBase subobject at +4
// VTABLE: GAMEMD 0x7F0164 // ParticleNoticeSinkBase subobject at +8
// VTABLE: GAMEMD 0x7F015C // ParticleNoticeSourceBase subobject at +0xC

class ParticleTypeClass : public ParticleTypeObjectView
{
public:
    static ParticleTypeClass* __fastcall FindOrAllocate(const char* id);
    // ---- primary table (IPersistStream side) overrides ---------------------------------------
    // FUNCTION: GAMEMD 0x644BE0 - the named constructor, also what the INI reader calls to allocate a
    // type it has not seen yet.
    ParticleTypeClass(const char* id);
    // No-init constructor (Westwood NoInit idiom): Load re-runs it through placement new to restore
    // the vptrs and the colour list's vptr without touching any other member.
    ParticleTypeClass(const ParticleNoInit& noInit) : ParticleTypeObjectView(noInit), ColorList(0, 0) {}

    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                  // 3   0x645620
    virtual HRESULT __stdcall Load(IStream* pStm);                          // 5   0x645660
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);        // 6   0x6457A0
    // Slot 8: the scalar deleting destructor 0x645950 is compiler output; the destructor body is
    // inline (it is expanded into that entry) and the base body 0x5F7400 is out of line.
    virtual ~ParticleTypeClass()
    {
        ParticleAnnouncePointerExpired(this, true);
        ParticleAbstractTypeArray.RemoveItem(this);
        ParticleTypeArray.RemoveItem(this);
    }
    virtual void PointerExpired(void* ptr, bool removed);                   // 10  0x6458B0
    virtual int WhatAmI();                                                  // 11  0x645920
    virtual int Size();                                                     // 12  0x645910
    virtual void ComputeCRC(ParticleCrcView& crc);                           // 13  0x6454E0
    virtual bool ReadINI(ParticleIniView* ini);                              // 25  0x644F50
    virtual bool vf_32(int a, int b);                                       // 32  0x645930
    virtual int vf_35(int a);                                               // 35  0x645940

    // ---- members (complete-object offsets) ---------------------------------------------------
    ParticleCoord  NextParticleOffset;   // +0x294
    int            XVelocity;            // +0x2A0
    int            YVelocity;            // +0x2A4
    int            MinZVelocity;         // +0x2A8
    int            ZVelocityRange;       // +0x2AC
    double         ColorSpeed;           // +0x2B0
    ParticleColorList ColorList;         // +0x2B8
    ParticleColor  StartColor1;          // +0x2D4
    ParticleColor  StartColor2;          // +0x2D7
    char           unknown_2DA[2];       // +0x2DA
    int            MaxDC;                // +0x2DC
    int            MaxEC;                // +0x2E0
    ParticleWarheadView* Warhead;        // +0x2E4
    int            Damage;               // +0x2E8
    int            StartFrame;           // +0x2EC
    int            NumLoopFrames;        // +0x2F0
    int            Translucency;         // +0x2F4
    int            WindEffect;           // +0x2F8
    float          Velocity;             // +0x2FC
    float          Deacc;                // +0x300
    int            Radius;               // +0x304
    bool           DeleteOnStateLimit;   // +0x308
    signed char    EndStateAI;           // +0x309
    signed char    StartStateAI;         // +0x30A
    signed char    StateAIAdvance;       // +0x30B
    signed char    FinalDamageState;     // +0x30C
    unsigned char  Translucent25State;   // +0x30D
    unsigned char  Translucent50State;   // +0x30E
    bool           Normalized;           // +0x30F
    int            NextParticle;         // +0x310
    int            BehavesLike;          // +0x314
};

GG_STATIC_ASSERT(offsetof(ParticleTypeClass, NextParticleOffset) == 0x294);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, XVelocity) == 0x2A0);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, ZVelocityRange) == 0x2AC);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, ColorSpeed) == 0x2B0);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, ColorList) == 0x2B8);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, StartColor1) == 0x2D4);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, StartColor2) == 0x2D7);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, MaxDC) == 0x2DC);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, MaxEC) == 0x2E0);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, Warhead) == 0x2E4);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, Damage) == 0x2E8);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, StartFrame) == 0x2EC);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, NumLoopFrames) == 0x2F0);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, Translucency) == 0x2F4);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, WindEffect) == 0x2F8);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, Velocity) == 0x2FC);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, Deacc) == 0x300);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, Radius) == 0x304);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, DeleteOnStateLimit) == 0x308);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, EndStateAI) == 0x309);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, StartStateAI) == 0x30A);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, StateAIAdvance) == 0x30B);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, FinalDamageState) == 0x30C);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, Translucent25State) == 0x30D);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, Translucent50State) == 0x30E);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, Normalized) == 0x30F);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, NextParticle) == 0x310);
GG_STATIC_ASSERT(offsetof(ParticleTypeClass, BehavesLike) == 0x314);
// sizeof is from the allocation: `PUSH 0x318; CALL 0x7C8E17` at 0x64536B, 0x645474, 0x645876, 0x6C583C.
GG_STATIC_ASSERT(sizeof(ParticleTypeClass) == 0x318);

#endif  // GG_MATCH_EFFECTS_PARTICLES_PARTICLE_TYPE_CLASS_H
