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
class AnimTypeClass;

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

    unsigned char unknown_294;
    unsigned char unknown_295;
    unsigned char unknown_296;
    unsigned char unknown_297;
    unsigned char unknown_298;
    unsigned char unknown_299;
    unsigned char unknown_29A;
    unsigned char unknown_29B;
    unsigned char unknown_29C;
    unsigned char unknown_29D;
    unsigned char unknown_29E;
    unsigned char unknown_29F;
    unsigned char unknown_2A0;
    unsigned char unknown_2A1;
    unsigned char unknown_2A2;
    unsigned char unknown_2A3;
    unsigned char unknown_2A4[2];
    unsigned char unknown_2A6;
    unsigned char unknown_2A7;
    unsigned char unknown_2A8;
    unsigned char unknown_2A9;
    unsigned char unknown_2AA[2];
    int unknown_2AC;
    unsigned char unknown_2B0[0x2BC - 0x2B0];
    int unknown_2BC;
    unsigned char unknown_2C0;
    unsigned char unknown_2C1[7];
    double unknown_2C8;
    int unknown_2D0;
    unsigned char unknown_2D4[4];
    AnimTypeClass* unknown_2D8;
    int unknown_2DC;
    int unknown_2E0;
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
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_294) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_295) == 0x295);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_295) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_296) == 0x296);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_296) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_297) == 0x297);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_297) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_298) == 0x298);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_298) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_299) == 0x299);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_299) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_29A) == 0x29A);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_29A) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_29B) == 0x29B);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_29B) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_29C) == 0x29C);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_29C) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_29D) == 0x29D);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_29D) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_29E) == 0x29E);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_29E) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2A0) == 0x2A0);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2A0) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2A1) == 0x2A1);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2A1) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2A2) == 0x2A2);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2A2) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2A3) == 0x2A3);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2A3) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2A4) == 0x2A4);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2A4) == 2);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2A6) == 0x2A6);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2A6) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2A8) == 0x2A8);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2A8) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2A9) == 0x2A9);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2A9) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2AC) == 0x2AC);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2AC) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2BC) == 0x2BC);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2BC) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2C0) == 0x2C0);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2C0) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2C8) == 0x2C8);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2C8) == 8);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2D0) == 0x2D0);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2D0) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2D8) == 0x2D8);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2D8) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2DC) == 0x2DC);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2DC) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2E0) == 0x2E0);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2E0) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2E4) == 0x2E4);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2E4) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, ScaledSpawnDelay) == 0x2E8);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->ScaledSpawnDelay) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2EC) == 0x2EC);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2EC) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2F0) == 0x2F0);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2F0) == 4);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2F4) == 0x2F4);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2F4) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2F5) == 0x2F5);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2F5) == 1);
GG_STATIC_ASSERT(offsetof(BulletTypeClass, unknown_2F6) == 0x2F6);
GG_STATIC_ASSERT(sizeof(((BulletTypeClass*)0)->unknown_2F6) == 1);
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
