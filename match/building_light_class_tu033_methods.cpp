// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Disassembled from retail gamemd.exe v1.001 at 0x436950 (IPersistStream::Load) and 0x4370C0
//   (scalar deleting destructor, slot 8, with the destructor expanded); offsets read numerically.

#include <new.h>
#include "vector_class_operations.h"
#include "_layout/building_light_class.h"
#include "_layout/layer_class.h"
#include "_layout/swizzle_manager_class.h"

// GLOBAL: GAMEMD 0x8B4190 -- the list every BuildingLightClass joins.
extern DynamicVectorClass<BuildingLightClass*> DAT_008B4190;

// FUNCTION: GAMEMD 0x436950
// Loads the object prefix, rebuilds the object around the loaded bytes and registers the two
// building pointers for swizzling.
HRESULT __stdcall BuildingLightClass::Load(IStream* pStm)
{
    HRESULT hr = ObjectClass::Load(pStm);
    if (hr >= 0) {
        new(this) BuildingLightClass(AbstractNoInit());
        DAT_00B0C110.SwizzleManagerClass::vf_4(&source);
        DAT_00B0C110.SwizzleManagerClass::vf_4(&unknown_E0);
    }
    return hr;
}

// SYNTHETIC: GAMEMD 0x4370C0
// Scalar deleting destructor (primary slot 8), the destructor expanded in place.
BuildingLightClass::~BuildingLightClass()
{
    if (vf_53())
        DAT_0087F778.RemoveObject(this);
    DAT_008B4190.RemoveItem(this);
}
