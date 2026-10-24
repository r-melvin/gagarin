// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA
// 0x6D9BA2/0x6D9CAA and 0x6D9D38/0x6D9ECE read Items/Count.
#ifndef GG_BUILDING_ARRAY_H
#define GG_BUILDING_ARRAY_H
#include "../core/vector_class.h"
class BuildingClass;
// GLOBAL: GAMEMD 0x00A8EB40
extern DynamicVectorClass<BuildingClass*> DAT_00A8EB40;
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<BuildingClass*>, Items) == 4);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<BuildingClass*>, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<BuildingClass*>) == 0x18);
GG_STATIC_ASSERT(sizeof(BuildingClass*) == 4);
#endif
