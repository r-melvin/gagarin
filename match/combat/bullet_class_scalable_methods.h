// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x46B280: the ScalableBullets vector at 0x89DE18
//   (vtable `[0x89DE18]` with slot `[EAX+8]`, Items `[0x89DE1C]`, Capacity
//   `[0x89DE20]`, IsAllocated as the byte `[0x89DE25]` (+0xD, the canonical layout), Count `[0x89DE28]`,
//   CapacityIncrement `[0x89DE2C]`), `[ESI+0xAC]` (BulletClass::Type) and
//   `[ECX+0x2E4]` (BulletTypeClass::SpawnDelay, immediately before the
//   ScaledSpawnDelay pinned at 0x2E8 by match/combat/bullet_type_class.h).
//   Names cross-checked against YRpp
//   (names only; no text copied).
#ifndef GG_MATCH_COMBAT_BULLET_CLASS_SCALABLE_METHODS_H
#define GG_MATCH_COMBAT_BULLET_CLASS_SCALABLE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/vector_class_operations.h"

// BulletTypeClass — local partial model. SpawnDelay @0x2E4 is the base
// spawn delay; SetScaledSpawnDelay (0x46C840, matched in bullet_type_class.cpp)
// stores the per-bullet scaled copy at 0x2E8.
class BulletTypeClass
{
public:
    char _pad000[0x2E4];      // +0x0000
    int  SpawnDelay;          // +0x02E4
    int  ScaledSpawnDelay;    // +0x02E8
    char _pad2EC[0xC];        // +0x02EC

    // FUNCTION: GAMEMD 0x46C840 (decl; reloc)
    void SetScaledSpawnDelay(int delay);
};
GG_STATIC_ASSERT(offsetof(BulletTypeClass, SpawnDelay) == 0x2E4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, ScaledSpawnDelay) == 0x2E8);
GG_STATIC_ASSERT(sizeof(BulletTypeClass) == 0x2F8);

// BulletClass : ObjectClass (0xAC) — only Type is reached here.
class BulletClass
{
public:
    char             _pad000[0xAC];   // +0x0000  ObjectClass base
    BulletTypeClass* Type;            // +0x00AC

    // FUNCTION: GAMEMD 0x46B280
    void InitScalable();
};
GG_STATIC_ASSERT(offsetof(BulletClass, Type) == 0xAC);

// GLOBAL: GAMEMD 0x89DE18 — BulletClass::ScalableBullets.
extern DynamicVectorClass<BulletClass*> ScalableBullets;

#endif  // GG_MATCH_COMBAT_BULLET_CLASS_SCALABLE_METHODS_H
