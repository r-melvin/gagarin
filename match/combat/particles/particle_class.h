// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check (names only, consult-only)
//   Layout, tables and vptr offsets read from the retail gamemd.exe v1.001: RTTI .?AVParticleClass@@
//   (particle_common_views.h), the two constructors 0x62B5E0 / 0x62BB20 (every member store below), the
//   scalar deleting destructor 0x62D9A0, and the allocation sites 0x62E397, 0x62E434, 0x62E4D8,
//   0x62E9A3 and 0x6C56BC (`PUSH 0x138; CALL 0x7C8E17`, seven sites, all agreeing).
//
// ParticleClass: one live particle of a ParticleSystemClass (smoke, spark, gas, fire, "railgun"
// streaks). Derives the ObjectClass-shaped partial view of particle_common_views.h.
//
//   +0x00..+0xAB  ParticleObjectView (particle_common_views.h)
//   +0xAC  Type           (ParticleTypeClass*)  ctor argument 1
//   +0xB0  Color          (three bytes)         ctor 0; a copy of the type's first colour
//   +0xB4  ColorIndex     (int)                 ctor 0; index into the type's colour list
//   +0xB8  ColorBlend     (double)              ctor 0 (two dword stores)
//   +0xC0..+0xD0          five dwords, ctor 0
//   +0xD4  (float)        ctor -1.0f
//   +0xD8..+0xE0          three dwords, ctor 0
//   +0xE4  Velocity       (float)               ctor: Type->Velocity (+0x2FC); plus a random 0/1
//   +0xE8  TargetCoord    (three dwords)        ctor argument 3
//   +0xF4  Coord          (three dwords)        ctor argument 2
//   +0x100 Coord2         (three dwords)        ctor: copy of the empty-coordinate global 0xAC49D8
//   +0x10C Direction      (three floats)        ctor: argument 3 - argument 2, normalised
//   +0x118 Position       (three floats)        ctor: argument 2 as floats
//   +0x124 Owner          (ParticleSystemClass*) ctor argument 4; swizzled by Load
//   +0x128 (short)        +0x12A (short)        ctor: random value / Type->+0x2DC
//   +0x12C..+0x131        six bytes
//   +0x132..+0x137        padding (sizeof 0x138, from the allocation)
#ifndef GG_MATCH_EFFECTS_PARTICLES_PARTICLE_CLASS_H
#define GG_MATCH_EFFECTS_PARTICLES_PARTICLE_CLASS_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "particle_runtime_vtable_layout.h"
#include "particle_common_types.h"
#include "particle_common_views.h"
#include "particle_views.h"
#include "particle_type_class.h"
#include "particle_shared.h"

// VTABLE: GAMEMD 0x7EF954 (primary IPersistStream side)
// VTABLE: GAMEMD 0x7EF938
// VTABLE: GAMEMD 0x7EF930
// VTABLE: GAMEMD 0x7EF928
class ParticleClass : public ParticleObjectView
{
public:
    // FUNCTION: GAMEMD 0x62B5E0
    ParticleClass(ParticleTypeClass* type, const ParticleCoord* coord, const ParticleCoord* targetCoord,
                  ParticleSystemClass* owner) throw();
    // FUNCTION: GAMEMD 0x62BB20
    ParticleClass();
    // No-init constructor (Westwood NoInit idiom): Load re-runs it through placement new to
    // restore the vptrs without touching members.
    ParticleClass(const ParticleNoInit& noInit) : ParticleObjectView(noInit) {}

    // ---- primary table (IPersistStream side) overrides ---------------------------------------
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                  // 3   0x62D930
    virtual HRESULT __stdcall Load(IStream* pStm);                          // 5   0x62D7A0
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);        // 6   0x62D810
    // Slot 8: the scalar deleting destructor 0x62D9A0 is compiler output; the destructor body is
    // inline (it is expanded into that entry, and retail has no separate destructor).
    virtual ~ParticleClass()
    {
        vf_53();
        ParticleAnnouncePointerExpired(this, true);
        Type = 0;
        ParticleArray.RemoveItem(this);
    }
    virtual int WhatAmI();                                                  // 11  0x62D980
    virtual int Size();                                                     // 12  0x62D970
    virtual int InWhichLayer();                                             // 30  0x62D770
    virtual ParticleTypeObjectView* GetType();                               // 34  0x62D990
    virtual ParticleCellCoord* vf_66(void* unused);                          // 66  0x62D710
    virtual void vf_69(void* where, ParticleRect* clip);                    // 69  0x62CEC0
    virtual bool vf_73(int arg);                                   // 73  0x62D6F0
    // Slot 122 is not part of the shared ObjectClass table (122 slots): ParticleClass adds it.
    virtual int vf_122();                                                   // 122 0x62D830

    // ---- members (complete-object offsets) ---------------------------------------------------
    ParticleTypeClass*    Type;          // +0xAC
    ParticleColor         Color;         // +0xB0
    int                   ColorIndex;    // +0xB4
    double                ColorBlend;    // +0xB8
    int                   unknown_C0;    // +0xC0
    int                   unknown_C4;    // +0xC4
    int                   unknown_C8;    // +0xC8
    int                   unknown_CC;    // +0xCC
    int                   unknown_D0;    // +0xD0
    float                 unknown_D4;    // +0xD4
    int                   unknown_D8;    // +0xD8
    int                   unknown_DC;    // +0xDC
    int                   unknown_E0;    // +0xE0
    float                 Velocity;      // +0xE4
    ParticleCoord         TargetCoord;   // +0xE8
    ParticleCoord         Coord;         // +0xF4
    ParticleCoord         Coord2;        // +0x100
    ParticleVec3          Direction;     // +0x10C
    ParticleVec3          Position;      // +0x118
    ParticleSystemClass*  Owner;         // +0x124
    short                 unknown_128;   // +0x128
    short                 unknown_12A;   // +0x12A
    unsigned char         unknown_12C;   // +0x12C
    unsigned char         unknown_12D;   // +0x12D
    signed char           unknown_12E;   // +0x12E
    signed char           unknown_12F;   // +0x12F
    unsigned char         unknown_130;   // +0x130
    unsigned char         unknown_131;   // +0x131
};

GG_STATIC_ASSERT(offsetof(ParticleClass, Type) == 0xAC);
GG_STATIC_ASSERT(offsetof(ParticleClass, Color) == 0xB0);
GG_STATIC_ASSERT(offsetof(ParticleClass, ColorIndex) == 0xB4);
GG_STATIC_ASSERT(offsetof(ParticleClass, ColorBlend) == 0xB8);
GG_STATIC_ASSERT(offsetof(ParticleClass, unknown_C0) == 0xC0);
GG_STATIC_ASSERT(offsetof(ParticleClass, unknown_C4) == 0xC4);
GG_STATIC_ASSERT(offsetof(ParticleClass, unknown_C8) == 0xC8);
GG_STATIC_ASSERT(offsetof(ParticleClass, unknown_CC) == 0xCC);
GG_STATIC_ASSERT(offsetof(ParticleClass, unknown_D0) == 0xD0);
GG_STATIC_ASSERT(offsetof(ParticleClass, unknown_D4) == 0xD4);
GG_STATIC_ASSERT(offsetof(ParticleClass, unknown_D8) == 0xD8);
GG_STATIC_ASSERT(offsetof(ParticleClass, unknown_DC) == 0xDC);
GG_STATIC_ASSERT(offsetof(ParticleClass, unknown_E0) == 0xE0);
GG_STATIC_ASSERT(offsetof(ParticleClass, Velocity) == 0xE4);
GG_STATIC_ASSERT(offsetof(ParticleClass, TargetCoord) == 0xE8);
GG_STATIC_ASSERT(offsetof(ParticleClass, Coord) == 0xF4);
GG_STATIC_ASSERT(offsetof(ParticleClass, Coord2) == 0x100);
GG_STATIC_ASSERT(offsetof(ParticleClass, Direction) == 0x10C);
GG_STATIC_ASSERT(offsetof(ParticleClass, Position) == 0x118);
GG_STATIC_ASSERT(offsetof(ParticleClass, Owner) == 0x124);
GG_STATIC_ASSERT(offsetof(ParticleClass, unknown_128) == 0x128);
GG_STATIC_ASSERT(offsetof(ParticleClass, unknown_12A) == 0x12A);
GG_STATIC_ASSERT(offsetof(ParticleClass, unknown_12C) == 0x12C);
GG_STATIC_ASSERT(offsetof(ParticleClass, unknown_12D) == 0x12D);
GG_STATIC_ASSERT(offsetof(ParticleClass, unknown_12E) == 0x12E);
GG_STATIC_ASSERT(offsetof(ParticleClass, unknown_12F) == 0x12F);
GG_STATIC_ASSERT(offsetof(ParticleClass, unknown_130) == 0x130);
GG_STATIC_ASSERT(offsetof(ParticleClass, unknown_131) == 0x131);
// sizeof is from the allocation: `PUSH 0x138; CALL 0x7C8E17` at all seven sites (0x62E397 ...).
GG_STATIC_ASSERT(sizeof(ParticleClass) == 0x138);

#endif  // GG_MATCH_EFFECTS_PARTICLES_PARTICLE_CLASS_H
