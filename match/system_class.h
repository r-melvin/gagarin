// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check (names only) | behaviour-confirmed-name
//   Layout from the retail gamemd.exe v1.001: RTTI .?AVParticleSystemClass@@ (TD 0x836748),
//   tables 0x7EFB9C (primary, 122 slots) / 0x7EFB80 (6) / 0x7EFB78 (1) / 0x7EFB70 (1),
//   constructor 0x62DF20 (allocation `push 0x100; call 0x7C8E17` at 0x6C59BC), member
//   offsets from the constructor, Load/Save/ComputeCRC/Update bodies in system_class.cpp.
//   Names follow YRpp where the bodies confirm the behaviour.
//
// ParticleSystemClass: an object that owns a vector of particles and spawns/updates them
// according to its ParticleSystemTypeClass behaviour.
//
//   +0x00..+0x0F  four vptr words (primary 0x7EFB9C, +4 0x7EFB80, +8 0x7EFB78, +0xC 0x7EFB70)
//   +0x10..+0xAB  ObjectClass members (ParticleObjectView)
//   +0xAC  Type         ParticleSystemTypeClass*  ctor 0
//   +0xB0  unknown_B0   12 bytes, not touched by the constructor
//   +0xBC  Particles    dynamic pointer vector (0x18), Count at +0xCC
//   +0xD4  unknown_D4   coordinate, ctor copies the empty coordinate 0xAC4A58
//   +0xE0  unknown_E0   ctor 0, object pointer (Detach clears it, swizzled by Load)
//   +0xE4  unknown_E4   ctor 0, object pointer (same)
//   +0xE8  unknown_E8   float, ctor 0
//   +0xEC  FrameCountdown int, ctor 0, decremented by Update
//   +0xF0  unknown_F0   ctor 0
//   +0xF4  unknown_F4   ctor 0, color/int handed to the temporary light
//   +0xF8  unknown_F8   bool, ctor 0
//   +0xF9  unknown_F9   bool, ctor 0
//   sizeof == 0x100 (allocation 0x6C59BC)
#ifndef GG_MATCH_EFFECTS_PARTICLES_SYSTEM_CLASS_H
#define GG_MATCH_EFFECTS_PARTICLES_SYSTEM_CLASS_H

#include "particle_runtime_vtable_layout.h"

#include "particle_common_types.h"
#include "particle_common_vectors.h"
#include "particle_common_views.h"
#include "particle_system_type_class.h"

// VTABLE: GAMEMD 0x7EFB9C (primary)
// VTABLE: GAMEMD 0x7EFB80
// VTABLE: GAMEMD 0x7EFB78
// VTABLE: GAMEMD 0x7EFB70
class ParticleSystemClass : public ParticleObjectView
{
public:
    // FUNCTION: GAMEMD 0x62DF20
    ParticleSystemClass();
    void FUN_0062E650(); // GAMEMD 0x62E650, caller0x685618
    bool FUN_0062E5D0(int index); // GAMEMD 0x62E5D0
    ParticleClass* SpawnParticle(const ParticleCoord& coords1, const ParticleCoord& coords2);
    ParticleClass* SpawnParticle(ParticleTypeClass* pType, const ParticleCoord& coords);
    // FUNCTION: GAMEMD 0x62DC50
    ParticleSystemClass(ParticleSystemTypeClass* type, const ParticleCoord& coord,
                        ParticleObjectView* owner, ParticleObjectView* target,
                        const ParticleCoord& ownerCoord, int unknownFC);
    // No-init constructor (Load re-runs it through placement new). Retail has it
    // inlined into Load: base 0x5F3B50, vector (0, 0) via 0x6302A0, four vptrs.
    ParticleSystemClass(const ParticleNoInit& noInit)
        : ParticleObjectView(noInit), Particles(0, 0)
    {
    }
    // Slot 8: the ordinary destructor is an external declaration view; the scalar deleting
    // destructor is emitted by the compiler in system_class.cpp.
    // FUNCTION: GAMEMD 0x62E070 (decl; reloc)
    virtual ~ParticleSystemClass();

    // ---- primary table overrides --------------------------------------------
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);              // 0x6301A0
    virtual HRESULT __stdcall Load(IStream* pStm);                      // 0x62FF20
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);    // 0x630090
    virtual void PointerExpired(void* target, bool removed);            // 0x62FE90
    virtual int WhatAmI();                                              // 0x630210
    virtual int Size();                                                 // 0x630200
    virtual void ComputeCRC(ParticleCrcView& crc);                    // 0x630100
    virtual bool IsFinished();                                          // 0x62FE60
    virtual void Update();                                              // 0x62FD60
    virtual int InWhichLayer();                                         // 0x62FE80
    virtual ParticleTypeObjectView* GetType();                               // 0x630220
    virtual void MarkFinished();                                        // 0x6301E0
    virtual void vf_69(void* where, ParticleRect* clip);                 // 0x62E280

    // Behaviour bodies Update dispatches to by Type->behavior (read-only, not in the
    // partition; EXPANSION candidates).
    void UpdateBehavior0();                                             // 0x62ED40
    void UpdateBehavior1();                                             // 0x62E6D0
    void UpdateBehavior2();                                             // 0x62F9A0
    void UpdateBehavior3();                                             // 0x62E840
    void UpdateBehavior4();                                             // 0x62F230

    // ---- members ------------------------------------------------------------
    ParticleSystemTypeClass*       Type;            // +0xAC
    ParticleCoord                      unknown_B0;      // +0xB0
    ParticleInlineDynVector<ParticleClass*>  Particles;       // +0xBC
    ParticleCoord                      unknown_D4;      // +0xD4
    ParticleObjectView*      unknown_E0;      // +0xE0
    ParticleObjectView*      unknown_E4;      // +0xE4
    float                          unknown_E8;      // +0xE8
    int                            FrameCountdown;  // +0xEC
    int                            unknown_F0;      // +0xF0
    int                            unknown_F4;      // +0xF4
    bool                           unknown_F8;      // +0xF8
    bool                           unknown_F9;      // +0xF9
    unsigned char                  unknown_FA[2];   // +0xFA
    int                            unknown_FC;      // +0xFC
};

GG_STATIC_ASSERT(offsetof(ParticleSystemClass, Type)           == 0xAC);
GG_STATIC_ASSERT(offsetof(ParticleSystemClass, Particles)      == 0xBC);
GG_STATIC_ASSERT(offsetof(ParticleSystemClass, unknown_D4)     == 0xD4);
GG_STATIC_ASSERT(offsetof(ParticleSystemClass, unknown_E0)     == 0xE0);
GG_STATIC_ASSERT(offsetof(ParticleSystemClass, unknown_E4)     == 0xE4);
GG_STATIC_ASSERT(offsetof(ParticleSystemClass, unknown_E8)     == 0xE8);
GG_STATIC_ASSERT(offsetof(ParticleSystemClass, FrameCountdown) == 0xEC);
GG_STATIC_ASSERT(offsetof(ParticleSystemClass, unknown_F0)     == 0xF0);
GG_STATIC_ASSERT(offsetof(ParticleSystemClass, unknown_F4)     == 0xF4);
GG_STATIC_ASSERT(offsetof(ParticleSystemClass, unknown_F8)     == 0xF8);
GG_STATIC_ASSERT(offsetof(ParticleSystemClass, unknown_F9)     == 0xF9);
GG_STATIC_ASSERT(offsetof(ParticleSystemClass, unknown_B0)     == 0xB0);
GG_STATIC_ASSERT(offsetof(ParticleSystemClass, unknown_FC)     == 0xFC);
GG_STATIC_ASSERT(sizeof(ParticleSystemClass) == 0x100);   // allocation 0x6C59BC

#endif  // GG_MATCH_EFFECTS_PARTICLES_SYSTEM_CLASS_H
