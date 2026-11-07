// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu260_methods.h"
#include "_layout/voxel_anim_class.h"
#include "_layout/voxel_anim_noinit.h"
#include "_layout/swizzle_manager_class.h"
#include <new>

// GLOBAL: GAMEMD 0xB0C110 -- the swizzle manager.
extern SwizzleManagerClass DAT_00B0C110;

// FUNCTION: GAMEMD 0x74A960
// Returns a constant. Vtable slot 30 of VoxelAnimClass (RTTI).
int VoxelAnimClass::vf_30()
{
    return 3;
}

// FUNCTION: GAMEMD 0x74A970
HRESULT __stdcall VoxelAnimClass::Load(IStream* pStm)
{
    HRESULT hr = ObjectClass::Load(pStm);
    if (hr >= 0) {
        new (this) VoxelAnimClass(AbstractNoInit());
        unknown_114.FUN_00405BE0();
        unknown_128.FUN_00405BE0();
        DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_104);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_108);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_10C);
    }
    return hr;
}

// FUNCTION: GAMEMD 0x74AB10
// Returns a constant. Vtable slot 12 of VoxelAnimClass (RTTI).
int VoxelAnimClass::vf_12()
{
    return 0x148;
}

// FUNCTION: GAMEMD 0x74AB20
// Returns a constant. Vtable slot 11 of VoxelAnimClass (RTTI).
int VoxelAnimClass::vf_11()
{
    return 0x29;
}

// FUNCTION: GAMEMD 0x74AB30
// Member getter (dword). Vtable slot 34 of VoxelAnimClass (RTTI).
int Obj_0074AB30::FUN_0074AB30() const
{
    return unknown_104;
}

// FUNCTION: GAMEMD 0x74AB40
// Returns zero; pops its stack arguments. Vtable slot 66 of VoxelAnimClass (RTTI).
void* VoxelAnimClass::vf_66(int a1)
{
    return 0;
}

// SYNTHETIC: GAMEMD 0x74AB50 -- compiler-generated scalar deleting destructor of ~VoxelAnimClass (slot 8;
// calls the out-of-line destructor 0x7499F0), emitted where Load seats the vtable.
