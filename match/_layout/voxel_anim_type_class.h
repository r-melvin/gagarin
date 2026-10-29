// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail vtable 0x7F6548 names .?AVVoxelAnimTypeClass@@. The constructor 0x74AD80
//   (allocation size 0x308 in the registry lookup 0x74BB20), the destructor 0x74AF70 and
//   the stream loader 0x74B810 pin the members below; the rest of the class is padding.
#ifndef GG_MATCH_LAYOUT_VOXEL_ANIM_TYPE_CLASS_H
#define GG_MATCH_LAYOUT_VOXEL_ANIM_TYPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "object_type_class.h"
#include "obj_004a1d30.h"

class VoxelAnimTypeClass : public ObjectTypeClass
{
public:
    // FUNCTION: GAMEMD 0x74AD80 (decl; reloc) - the constructor taking the type's ID.
    VoxelAnimTypeClass(const char* id);
    // The class factory's construction (TClassFactory<VoxelAnimTypeClass>): the same constructor
    // with a default argument.
    VoxelAnimTypeClass(int unknown_arg0 = 0);
    // The stream loader's in-place construction.
    VoxelAnimTypeClass(const AbstractNoInit& noInit) : ObjectTypeClass(noInit) {}
    virtual ~VoxelAnimTypeClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);      // 3   0x74B7D0
    virtual HRESULT __stdcall Load(IStream* pStm);              // 5   0x74B810
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty); // 6
    virtual int vf_11();                                        // 11  0x74B9F0
    virtual int vf_12();                                        // 12  0x74BA00
    virtual void vf_13(Obj_004A1D30* crc);                      // 13  0x74B690
    virtual bool vf_25(CCINIClass* ini);                        // 25  0x74B050
    virtual bool vf_32(const CellStruct* cell, HouseClass* house); // 32 0x74BA10
    virtual ObjectClass* vf_35(HouseClass* house);                           // 35  0x74BA20

    bool Normalized;              // +0x294
    bool Translucent;             // +0x295
    bool unknown_296;             // +0x296
    char unknown_297[0x298 - 0x297];
    int VoxelIndex;               // +0x298
    int Duration;                 // +0x29C
    double Elasticity;            // +0x2A0
    double MinAngularVelocity;    // +0x2A8
    double MaxAngularVelocity;    // +0x2B0
    double MinZVel;               // +0x2B8
    double MaxZVel;               // +0x2C0
    double MaxXYVel;              // +0x2C8
    bool IsMeteor;                // +0x2D0
    char unknown_2D1[0x2D4 - 0x2D1];
    void* Spawns;                 // +0x2D4
    int SpawnCount;               // +0x2D8
    int StartSound;               // +0x2DC
    int StopSound;                // +0x2E0
    void* BounceAnim;             // +0x2E4
    void* ExpireAnim;             // +0x2E8
    void* TrailerAnim;            // +0x2EC
    int Damage;                   // +0x2F0
    int DamageRadius;             // +0x2F4
    void* Warhead;                // +0x2F8
    void* AttachedSystem;         // +0x2FC
    bool IsTiberium;              // +0x300
    char unknown_301[0x308 - 0x301];
};
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, Normalized) == 0x294);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, Translucent) == 0x295);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, unknown_296) == 0x296);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, VoxelIndex) == 0x298);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, Duration) == 0x29C);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, Elasticity) == 0x2A0);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, MinAngularVelocity) == 0x2A8);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, MaxAngularVelocity) == 0x2B0);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, MinZVel) == 0x2B8);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, MaxZVel) == 0x2C0);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, MaxXYVel) == 0x2C8);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, IsMeteor) == 0x2D0);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, Spawns) == 0x2D4);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, SpawnCount) == 0x2D8);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, StartSound) == 0x2DC);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, StopSound) == 0x2E0);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, BounceAnim) == 0x2E4);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, ExpireAnim) == 0x2E8);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, TrailerAnim) == 0x2EC);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, Damage) == 0x2F0);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, DamageRadius) == 0x2F4);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, Warhead) == 0x2F8);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, AttachedSystem) == 0x2FC);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, IsTiberium) == 0x300);
GG_STATIC_ASSERT(sizeof(VoxelAnimTypeClass) == 0x308);

#endif
