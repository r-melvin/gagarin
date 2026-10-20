// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x46C790 / 0x46C840), cross-checked
//   against YRpp BulletTypeClass.h (consult-only, no LICENSE; every offset and
//   address reconfirmed numerically below).
//
// BulletTypeClass — a projectile *type* (rules-driven template for bullets).
// Only the two methods in this TU are modelled here: the static type-array
// lookup/allocate factory (FindOrAllocate) and the ScaledSpawnDelay setter.
// The full BulletTypeClass layout (every Rules field) is P2 work; here the
// class is padded to its confirmed retail size (0x2F8) so `operator new` emits
// the exact `push 0x2F8` allocation seen in FindOrAllocate.
#ifndef GG_MATCH_COMBAT_BULLET_TYPE_CLASS_H
#define GG_MATCH_COMBAT_BULLET_TYPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// BulletTypeClass — partial model (only the touched members are named).
//   * ID         char[] @ 0x24 — confirmed by `MOV ECX,[EAX+ESI*4]; ADD ECX,0x24`
//                in the FindOrAllocate match loop (the `add ecx,0x24` immediate
//                pins ID to +0x24); strcmpi'd against the query id.
//   * ScaledSpawnDelay int @ 0x2E8 — `MOV [ECX+0x2E8],EAX` in SetScaledSpawnDelay.
//   * sizeof == 0x2F8 — `PUSH 0x2F8` before `operator new` in FindOrAllocate.
class BulletTypeClass
{
public:
    // STATIC: GAMEMD 0x46C790  (__fastcall)
    static BulletTypeClass* __fastcall FindOrAllocate(const char* id);
    // FUNCTION: GAMEMD 0x46C840  (__thiscall)
    void SetScaledSpawnDelay(int delay);

    // GAMEMD 0x46BBC0  BulletTypeClass::BulletTypeClass(const char*) (__thiscall;
    // returns `this` in EAX). Declared (no body) so FindOrAllocate emits the
    // reloc'd construct call; matched in its own TU.
    BulletTypeClass* Construct(const char* id);

    char          _base[0x24];               // +0x000  AbstractType/ObjectType base (P2)
    char          ID[0x18];                  // +0x024  type id string (strcmpi key)
    char          _members[0x2E8 - 0x3C];    // +0x03C  remaining Rules fields (P2)
    int           ScaledSpawnDelay;          // +0x2E8
    char          _tail[0x2F8 - 0x2EC];      // +0x2EC  remaining fields (P2)
};

GG_STATIC_ASSERT(offsetof(BulletTypeClass, ID)               == 0x024);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, ScaledSpawnDelay) == 0x2E8);
GG_STATIC_ASSERT(sizeof(BulletTypeClass)                     == 0x2F8);

// VectorClass head for BulletTypeClass::Array. Items @ +0x04, Count @ +0x10.
//   Array @ 0xA83C80  =>  &Items == 0xA83C84, &Count == 0xA83C90 (both confirmed
//   by the absolute loads in FindOrAllocate).
struct BulletTypeVector
{
    void*              vtable;        // +0x00
    BulletTypeClass**  Items;        // +0x04
    int                Capacity;     // +0x08
    int                IsAllocated;  // +0x0C
    int                Count;        // +0x10
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(BulletTypeVector, Items) == 0x04);  // pointer-width-sensitive
GG_STATIC_ASSERT(offsetof(BulletTypeVector, Count) == 0x10);
#endif

// GLOBAL: GAMEMD 0xA83C80 — BulletTypeClass::Array.
extern BulletTypeVector BulletTypeClass_Array;

#endif  // GG_MATCH_COMBAT_BULLET_TYPE_CLASS_H
