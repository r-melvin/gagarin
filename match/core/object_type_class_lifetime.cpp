// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native 0x5F7400 unregisters the object, releases its owned image, clears
// charger resources and destroys cache/voxel members in reverse order.
// Native 0x5F8080 clears the paired charger arrays in forward index order.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
// /Ob2 expands the registry removal and four cache destructors as in retail.
#include "../_layout/object_type_class.h"
#include "object_type_registry.h"
#include "vector_class_operations.h"
#include <new.h>

GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Image) == 0xA4);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->Image) == 4);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ImageAllocated) == 0xA8);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->ImageAllocated) == 1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ChargerTurrets) == 0xC8);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ChargerBarrels) == 0x158);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->ChargerTurrets) == 0x90);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->ChargerBarrels) == 0x90);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, VoxelMainCache) == 0x244);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, VoxelTurretWeaponCache) == 0x258);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, VoxelShadowCache) == 0x26C);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, VoxelTurretBarrelCache) == 0x280);
GG_STATIC_ASSERT(sizeof(IndexClass) == 0x14);

// FUNCTION: GAMEMD 0x5F7400
ObjectTypeClass::~ObjectTypeClass()
{
    StaticVectorHolder_00AC1418::DAT_00AC1418.RemoveItem(this);
    if (ImageAllocated && Image)
    {
        ::operator delete(Image);
        Image = 0;
        ImageAllocated = false;
    }
    FUN_005F8080();
}

// FUNCTION: GAMEMD 0x5F8080
void ObjectTypeClass::FUN_005F8080()
{
    for (int i = 0; i < 18; ++i)
    {
        if (ChargerTurrets[i].unknown_00)
        {
            delete ChargerTurrets[i].unknown_00;
            ChargerTurrets[i].unknown_00 = 0;
        }
        if (ChargerTurrets[i].HVAData)
        {
            delete ChargerTurrets[i].HVAData;
            ChargerTurrets[i].HVAData = 0;
        }
        if (ChargerBarrels[i].unknown_00)
        {
            delete ChargerBarrels[i].unknown_00;
            ChargerBarrels[i].unknown_00 = 0;
        }
        if (ChargerBarrels[i].HVAData)
        {
            delete ChargerBarrels[i].HVAData;
            ChargerBarrels[i].HVAData = 0;
        }
    }
}
