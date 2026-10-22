// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x46B280: the ScalableBullets vector at 0x89DE18
//   (vtable `[0x89DE18]` with slot `[EAX+8]`, Items `[0x89DE1C]`, Capacity
//   `[0x89DE20]`, IsAllocated as the byte `[0x89DE25]`, Count `[0x89DE28]`,
//   CapacityIncrement `[0x89DE2C]`), `[ESI+0xAC]` (BulletClass::Type) and
//   `[ECX+0x2E4]` (BulletTypeClass::SpawnDelay, immediately before the
//   ScaledSpawnDelay pinned at 0x2E8 by match/combat/bullet_type_class.h).
//   Names cross-checked against YRpp
//   (names only; no text copied).
#ifndef GG_MATCH_COMBAT_BULLET_CLASS_SCALABLE_METHODS_H
#define GG_MATCH_COMBAT_BULLET_CLASS_SCALABLE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// BulletTypeClass — local partial model. SpawnDelay @0x2E4 is the base
// spawn delay; SetScaledSpawnDelay (0x46C840, matched in bullet_type_class.cpp)
// stores the per-bullet scaled copy at 0x2E8.
struct BulletTypeClass
{
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
struct BulletClass
{
    char             _pad000[0xAC];   // +0x0000  ObjectClass base
    BulletTypeClass* Type;            // +0x00AC

    // FUNCTION: GAMEMD 0x46B280
    void InitScalable();
};
GG_STATIC_ASSERT(offsetof(BulletClass, Type) == 0xAC);

// DynamicVectorClass<BulletClass*> with IsAllocated as a real `bool` (the
// retail test is the byte load `MOV CL,[0x89DE25]`), which the shared
// match/_layout/vector_class.h models as an int cell; hence the local model.
// SetCapacity is the real virtual at slot 2 (`CALL [EAX+8]`); slots 0 and 1
// (deleting destructor, Clear) are placeholders so it lands at +0x8.
struct DynVec_ScalableBullets
{
    virtual void Slot0_Destroy();                       // vtbl +0x00
    virtual void Slot1_Clear();                         // vtbl +0x04
    virtual bool SetCapacity(int capacity, BulletClass** items);  // vtbl +0x08

    BulletClass**         Items;      // +0x0004
    int                   Capacity;   // +0x0008
    bool                  IsAllocated;// +0x000C
    char                  _pad00D[3]; // +0x000D
    int                   Count;      // +0x0010
    int                   CapacityIncrement;  // +0x0014

    // Inlined DynamicVectorClass::AddItem — grows through the virtual
    // SetCapacity slot when full.
    bool AddItem(BulletClass* item)
    {
        if (this->Count >= this->Capacity) {
            if ((this->IsAllocated || this->Capacity == 0) && this->CapacityIncrement > 0) {
                if (!this->SetCapacity(this->Capacity + this->CapacityIncrement, 0))
                    return false;
            } else {
                return false;
            }
        }
        int idx = this->Count++;
        this->Items[idx] = item;
        return true;
    }
};
GG_STATIC_ASSERT(offsetof(DynVec_ScalableBullets, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(DynVec_ScalableBullets, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(DynVec_ScalableBullets, IsAllocated) == 0x0C);
GG_STATIC_ASSERT(offsetof(DynVec_ScalableBullets, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(DynVec_ScalableBullets, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(DynVec_ScalableBullets) == 0x18);

// GLOBAL: GAMEMD 0x89DE18 — BulletClass::ScalableBullets.
extern DynVec_ScalableBullets ScalableBullets;

#endif  // GG_MATCH_COMBAT_BULLET_CLASS_SCALABLE_METHODS_H
