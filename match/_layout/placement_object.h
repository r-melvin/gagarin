// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA
// 6D53D7 loads this object, calls slot11 and requires type6 before6D544B.
// Sidebar resets this same pointer after placement cancellation.
#ifndef GG_PLACEMENT_OBJECT_H
#define GG_PLACEMENT_OBJECT_H
#include "../_rt/gg_static_assert.h"
class ObjectClass;
// GLOBAL: GAMEMD 0x0088098C
extern ObjectClass* PlacementObject_0088098C;
GG_STATIC_ASSERT(sizeof(ObjectClass*) == 4);
#endif
