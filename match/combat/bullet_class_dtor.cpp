// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | RTTI-confirmed-inheritance
// BulletClass destructor (0x466560), kept apart from bullet_class_new_methods.cpp
// so the scalar deleting destructor emitted there calls it as retail does
// instead of expanding it.
#include "../_layout/bullet_class.h"
#include "../core/object_class_uninit_methods.h"
#include "../core/vector_class_operations.h"

// GLOBAL: GAMEMD 0xB0F5B8 -- actual existing storage is AbstractClass* vector.
extern DynamicVectorClass<AbstractClass*> DAT_00B0F5B8;
// GLOBAL: GAMEMD 0xA8ED40 -- vector removed from by the Bullet destructor.
extern DynamicVectorClass<BulletClass*> DAT_00A8ED40;
// GLOBAL: GAMEMD 0xA8E9A0 -- destruction-time virtual cleanup guard.
extern bool DAT_00A8E9A0;

// FUNCTION: GAMEMD 0x466560
BulletClass::~BulletClass()
{
    AnnounceExpiredPointer(1);
    if (SpawnNextAnim)
        DAT_00B0F5B8.RemoveItem(this);
    if (DAT_00A8E9A0)
        ObjectClass::vf_53();
    Type = 0;
    Owner = 0;
    NextAnim = 0;
    DAT_00A8ED40.RemoveItem(this);
}
