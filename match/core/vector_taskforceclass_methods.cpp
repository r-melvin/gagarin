// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Paired flag probes: /GX shortens the dynamic deleting entry to 0x20
// bytes; no-GX matches its full 0x49-byte span. Other 11 bodies match both.
// Retail RTTI TypeDescriptors 0x00823650 and 0x00823680 identify
// VectorClass<TaskForceClass*> and DynamicVectorClass<TaskForceClass*>; COLs
// 0x008018A0 and 0x00801870 point at them, and the dynamic hierarchy (two base
// classes) records the vector as its zero-offset base.
// VectorClass<T> address point 0x007EA0C4 and DynamicVectorClass<T> address
// point 0x007EA0A4 are each seven-slot tables whose COL is at address-4.
// Complete function spans (control-flow closure from each entry, not the
// first RET) were checked against the pinned retail PE. This TU recovers the
// vector specialization only; it makes no constructor, original-TU, or
// complete TaskForceClass layout claim.
#include "vector_class_operations.h"

class TaskForceClass;

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete(void*), ??3@YAXPAX@Z.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// FUNCTION: GAMEMD 0x004E8B40
// FUNCTION: GAMEMD 0x004E8B70
// FUNCTION: GAMEMD 0x004E8B90
// FUNCTION: GAMEMD 0x004ECA20
// FUNCTION: GAMEMD 0x004ECA60
// FUNCTION: GAMEMD 0x004ECB10
// FUNCTION: GAMEMD 0x004ECB40
// FUNCTION: GAMEMD 0x004ECB80
// FUNCTION: GAMEMD 0x004ECBA0
// FUNCTION: GAMEMD 0x004ECC50
// FUNCTION: GAMEMD 0x004F0390
// FUNCTION: GAMEMD 0x004F03E0
template class VectorClass<TaskForceClass*>;
template class DynamicVectorClass<TaskForceClass*>;

// VTABLE: GAMEMD 0x007EA0C4 -- VectorClass<TaskForceClass*>.
// VTABLE: GAMEMD 0x007EA0A4 -- DynamicVectorClass<TaskForceClass*>.

typedef VectorClass<TaskForceClass*> GgTaskForceClassVector;
typedef DynamicVectorClass<TaskForceClass*> GgTaskForceClassDynamicVector;
GG_STATIC_ASSERT(sizeof(TaskForceClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgTaskForceClassVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTaskForceClassVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTaskForceClassVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTaskForceClassVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTaskForceClassVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTaskForceClassVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgTaskForceClassDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgTaskForceClassDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTaskForceClassDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTaskForceClassDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTaskForceClassDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTaskForceClassDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgTaskForceClassDynamicVector, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTaskForceClassDynamicVector, CapacityIncrement) == 0x14);
