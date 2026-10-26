// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | RTTI-confirmed-inheritance
// Retail RTTI CHD identifies ObjectTypeClass as the direct base; field widths
// and accessed tail offsets are pinned below from the native Bullet methods.
#ifndef GG_MATCH_COMBAT_BULLET_TYPE_CLASS_H
#define GG_MATCH_COMBAT_BULLET_TYPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/object_type_class.h"

class HouseClass;

class BulletTypeClass : public ObjectTypeClass
{
public:
    // STATIC: GAMEMD 0x46C790 (__fastcall)
    static BulletTypeClass* FindOrAllocate(const char* id);
    // FUNCTION: GAMEMD 0x46C840 (__thiscall)
    void SetScaledSpawnDelay(int delay);

    // Constructor target is recovered in its owning source TU.
    BulletTypeClass* Construct(const char* id);

    // ObjectTypeClass's two pure slots have concrete BulletType table entries.
    virtual bool vf_32(const CellStruct* cell, HouseClass* house); // slot 32, table 0x7E4948
    virtual void* vf_35(void* house);                             // slot 35, table 0x7E4948

    unsigned char unknown_294[6];
    unsigned char unknown_29A;
    unsigned char unknown_29B[3];
    unsigned char unknown_29E;
    unsigned char unknown_29F[2];
    unsigned char unknown_2A1;
    unsigned char unknown_2A2;
    unsigned char unknown_2A3;
    unsigned char unknown_2A4[4];
    unsigned char unknown_2A8;
    unsigned char unknown_2A9;
    unsigned char unknown_2AA[0x2DC - 0x2AA];
    int unknown_2DC;
    unsigned char unknown_2E0[4];
    int unknown_2E4;
    int ScaledSpawnDelay;
    unsigned char unknown_2EC;
    unsigned char unknown_2ED[3];
    int unknown_2F0;
    unsigned char unknown_2F4;
    unsigned char unknown_2F5;
    unsigned char unknown_2F6;
    unsigned char unknown_2F7;
};

GG_STATIC_ASSERT(sizeof(ObjectTypeClass) == 0x294);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_294) == 0x294);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_29A) == 0x29A);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_29A) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_29E) == 0x29E);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_29E) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2A1) == 0x2A1);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2A1) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2A3) == 0x2A3);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2A3) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2A8) == 0x2A8);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2A8) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2A9) == 0x2A9);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2A9) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2DC) == 0x2DC);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2DC) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2EC) == 0x2EC);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2EC) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2F0) == 0x2F0);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2F0) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, ScaledSpawnDelay) == 0x2E8);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2F4) == 0x2F4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2F5) == 0x2F5);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2F6) == 0x2F6);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2F7) == 0x2F7);
GG_STATIC_ASSERT(sizeof(BulletTypeClass) == 0x2F8);

// VectorClass head for BulletTypeClass::Array.
struct BulletTypeVector
{
    void* vtable;
    BulletTypeClass** Items;
    int Capacity;
    int IsAllocated;
    int Count;
};
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(BulletTypeVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(BulletTypeVector, Count) == 0x10);
#endif
// GLOBAL: GAMEMD 0xA83C80
extern BulletTypeVector BulletTypeClass_Array;

#endif  // GG_MATCH_COMBAT_BULLET_TYPE_CLASS_H
