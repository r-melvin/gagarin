// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// LayerClass::Sort 0x551A30 and LogicClass methods 0x55BAA0/
// 0x55BAE0 use Items+0x04, Count+0x10 and ObjectClass::IsInLogic+0x98.
#ifndef GG_MATCH_MAP_MAP_CLASS_OBJECT_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_OBJECT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/layer_class.h"   // DynamicVectorClassLayout (Items@0x4, Count@0x10)
#include "../_layout/object_class.h"   // ObjectClass (IsInLogic@0x98)

GG_STATIC_ASSERT(offsetof(ObjectClass, IsInLogic) == 0x98);
GG_STATIC_ASSERT(offsetof(LayerClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(LayerClass, Count) == 0x10);


#endif  // GG_MATCH_MAP_MAP_CLASS_OBJECT_METHODS_H
