// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native ObjectType destruction 0x5F7426 removes this pointer through the
// vector at 0xAC1418. Its storage and guarded cleanup are emitted by
// static_vector_member_dtor_stubs_b.cpp; original declaring owner is unknown.
#ifndef GG_MATCH_CORE_OBJECT_TYPE_REGISTRY_H
#define GG_MATCH_CORE_OBJECT_TYPE_REGISTRY_H
#include "vector_class.h"
class ObjectTypeClass;
struct StaticVectorHolder_00AC1418
{
    // GLOBAL: GAMEMD 0xAC1418
    static DynamicVectorClass<ObjectTypeClass*> DAT_00AC1418;
};
#endif
