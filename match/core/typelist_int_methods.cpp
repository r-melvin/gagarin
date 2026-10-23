// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// /GX outlines destructor calls absent from the complete retail deleting body.
#include "vector_class_operations.h"
#include "type_list.h"

// FUNCTION: GAMEMD 0x4777B0
// TypeList<int>::TypeList(const TypeList<int>&), full 0x88 through RET 4.

// SYNTHETIC: GAMEMD 0x477990
// TypeList<int> scalar deleting destructor, full 0x49 through RET 4.

// FUNCTION: GAMEMD 0x67A4F0
// TypeList<int>::TypeList(), full 0x22 through final RET.

// VTABLE: GAMEMD 0x7E4DD8 -- TypeList<int>, seven slots.
template class TypeList<int>;
typedef TypeList<int> GgTypeListInt;
GG_STATIC_ASSERT(offsetof(GgTypeListInt, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTypeListInt, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTypeListInt, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTypeListInt, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTypeListInt, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTypeListInt, CapacityIncrement) == 0x14);
