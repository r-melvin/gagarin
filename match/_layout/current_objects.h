// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
#ifndef GG_MATCH_LAYOUT_CURRENT_OBJECTS_H
#define GG_MATCH_LAYOUT_CURRENT_OBJECTS_H
#include "../core/vector_class.h"
class ObjectClass;
// RTTI: native vptr7E4F64 -> COL7FD0B0 -> TD816AD8 names
// DynamicVectorClass<ObjectClass*>. Store at4E7D5D targets A8ECB8.
// Selection vector: A8ECBC Items and A8ECC8 Count in48DC90/6DA9D0.
// GLOBAL: GAMEMD 0xA8ECB8
extern DynamicVectorClass<ObjectClass*> CurrentObjects;
// Object chain vector:6DB53C reads Items atA8E364 and Count atA8E370.
// GLOBAL: GAMEMD 0xA8E360
extern DynamicVectorClass<ObjectClass*> DAT_00A8E360;
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<ObjectClass*>, Items) == 4);
GG_STATIC_ASSERT(offsetof(DynamicVectorClass<ObjectClass*>, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<ObjectClass*>) == 0x18);
#endif
