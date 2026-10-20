// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy /GX
// Complete entry-origin spans (0x88 bytes, RET 4 at +0x85) and raw RTTI
// identify the remaining SmudgeType copy constructor and inherited prefix.
// Its PBV RTTI encoding retains pointee const. Other family entries now use
// their native specialization implementations.
// Flags retain the verified constructor cluster. Whole-class instantiation
// is used under VC6; extra emitted virtuals/destructors remain unclaimed, and
// their final-link selection and complete class sizes are not established.
// Original TU grouping is unknown. Constructors are ordered by retail address.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
#include "type_list.h"

class SmudgeTypeClass;

// FUNCTION: GAMEMD 0x67C280
// TypeList<const SmudgeTypeClass*> copy constructor; base vptr 0x7F0D7C.
// VTABLE: GAMEMD 0x7F0D1C -- TypeList<const SmudgeTypeClass*>.
template class TypeList<const SmudgeTypeClass*>;
typedef TypeList<const SmudgeTypeClass*> GgVectorCopy8;
GG_STATIC_ASSERT(offsetof(GgVectorCopy8, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVectorCopy8, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVectorCopy8, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVectorCopy8, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgVectorCopy8, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgVectorCopy8, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(const SmudgeTypeClass*) == 4);
