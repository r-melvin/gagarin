// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA
// 6D53D7 loads this object, calls slot11 and requires type6 before6D544B.
// Sidebar resets this same pointer after placement cancellation.
// 4FB8B3 reads the placed object type at+520 and stores it to880990 at4FB8BF.
// 4FB3A0/4FB3CC copy the secondary placement type88097C to this type pointer.
#ifndef GG_PLACEMENT_OBJECT_H
#define GG_PLACEMENT_OBJECT_H
#include "../_rt/gg_static_assert.h"
class ObjectClass;
class ObjectTypeClass;
// GLOBAL: GAMEMD 0x0088098C
extern ObjectClass* PlacementObject_0088098C;
// GLOBAL: GAMEMD 0x00880990
extern ObjectTypeClass* PlacementType_00880990;
GG_STATIC_ASSERT(sizeof(ObjectTypeClass*) == 4);
GG_STATIC_ASSERT(sizeof(ObjectClass*) == 4);
#endif
