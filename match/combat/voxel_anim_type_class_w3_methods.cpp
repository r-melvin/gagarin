// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//   VoxelAnimTypeClass destruction and stream loading, read off retail gamemd.exe v1.001
//   (vtable 0x7F6548). /Ob2: the scalar deleting destructor carries the destructor body
//   inline, and the no-initialisation constructor is expanded in Load.
//   Address index: 0x74AF70 dtor, 0x74B810 Load, 0x74BA30 deleting dtor.

#include <new.h>
#include "../_layout/object_type_class.h"
#include "../_layout/swizzle_manager_class.h"
#include "../core/vector_class_operations.h"

// The members the loader and destructor touch; the rest of the class is not laid out here.
class VoxelAnimTypeClass : public ObjectTypeClass
{
public:
    VoxelAnimTypeClass(const AbstractNoInit& noInit) : ObjectTypeClass(noInit) {}
    virtual ~VoxelAnimTypeClass();
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);      // 3   0x74B7D0
    virtual HRESULT __stdcall Load(IStream* pStm);              // 5   0x74B810
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
};
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, unknown_296) == 0x296);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, unknown_2D4) == 0x2D4);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, unknown_2E4) == 0x2E4);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, unknown_2F8) == 0x2F8);
GG_STATIC_ASSERT(offsetof(VoxelAnimTypeClass, unknown_2FC) == 0x2FC);

// GLOBAL: GAMEMD 0xB0F670 -- the shared object registry.
extern DynamicVectorClass<AbstractClass*> DAT_00B0F670;
// GLOBAL: GAMEMD 0xA8EB28 -- the voxel animation type registry.
extern DynamicVectorClass<VoxelAnimTypeClass*> DAT_00A8EB28;
// GLOBAL: GAMEMD 0xB0C110 -- the swizzle manager.
extern SwizzleManagerClass DAT_00B0C110;

// FUNCTION: GAMEMD 0x74AF70
VoxelAnimTypeClass::~VoxelAnimTypeClass()
{
    AnnounceExpiredPointer(1);
    DAT_00B0F670.RemoveItem(this);
    DAT_00A8EB28.RemoveItem(this);
    if (unknown_296) {
        MainVoxel.unknown_00 = 0;
        MainVoxel.HVAData = 0;
    }
}

// FUNCTION: GAMEMD 0x74B810
// Reads the stream, rebuilds the object in place and re-registers its pointers.
HRESULT __stdcall VoxelAnimTypeClass::Load(IStream* pStm)
{
    HRESULT hr = ObjectTypeClass::Load(pStm);
    if (hr < 0) {
        return hr;
    }
    new (this) VoxelAnimTypeClass(AbstractNoInit());
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_2F8);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_2E4);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_2E8);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_2EC);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_2D4);
    DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_2FC);
    FUN_005F8110();
    return 0;
}

// SYNTHETIC: GAMEMD 0x74BA30
// VoxelAnimTypeClass scalar deleting destructor (primary slot 8), the destructor expanded in place.
