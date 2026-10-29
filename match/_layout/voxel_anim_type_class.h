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
    virtual bool vf_32(const CellStruct* cell, HouseClass* house); // 32 0x74BA10
    virtual void* vf_35(void* house);                           // 35  0x74BA20

    bool unknown_294;           // +0x294
    bool unknown_295;           // +0x295
    bool unknown_296;           // +0x296
    char unknown_297[0x2D4 - 0x297];
    void* unknown_2D4;          // +0x2D4
    char unknown_2D8[0x2E4 - 0x2D8];
    void* unknown_2E4;          // +0x2E4
    void* unknown_2E8;          // +0x2E8
    void* unknown_2EC;          // +0x2EC
    char unknown_2F0[0x2F8 - 0x2F0];
    void* unknown_2F8;          // +0x2F8
    void* unknown_2FC;          // +0x2FC
    char unknown_300[0x308 - 0x300];
};
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, unknown_296) == 0x296);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, unknown_2D4) == 0x2D4);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, unknown_2E4) == 0x2E4);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, unknown_2F8) == 0x2F8);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, unknown_2FC) == 0x2FC);
GG_STATIC_ASSERT(sizeof(VoxelAnimTypeClass) == 0x308);

#endif
