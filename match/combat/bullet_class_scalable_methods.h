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
#include "../_layout/bullet_class.h"
#include "bullet_type_class.h"



// GLOBAL: GAMEMD 0x89DE18 — BulletClass::ScalableBullets.
extern DynamicVectorClass<BulletClass*> ScalableBullets;

#endif  // GG_MATCH_COMBAT_BULLET_CLASS_SCALABLE_METHODS_H
