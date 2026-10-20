// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy /GX
// Entry-origin 0x22-byte bodies end in RET at +0x21. Raw RTTI PBV encodings
// identify TypeList<const Class*> and its zero-offset vector base chain.
// Both GX/no-GX constructor probes match; this TU retains the pointer copy
// cluster flags. Other emitted COMDATs are unclaimed; original TU boundaries,
// final-link selection and complete TypeList sizes remain unestablished.
#include "vector_class_operations.h"
#include "type_list.h"

class SmudgeTypeClass;

// FUNCTION: GAMEMD 0x67A600
// TypeList<const SmudgeTypeClass*>::TypeList(); retail vptr 0x7F0D1C.
template class TypeList<const SmudgeTypeClass*>;
typedef TypeList<const SmudgeTypeClass*> GgTypeListDefault4;
GG_STATIC_ASSERT(offsetof(GgTypeListDefault4, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault4, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault4, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault4, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault4, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTypeListDefault4, CapacityIncrement) == 0x14);