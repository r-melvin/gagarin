// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Paired flag probes: /GX shortens the dynamic deleting entry to 0x20
// bytes; no-GX matches its full 0x49-byte span. Other 11 bodies match both.
// Retail RTTI TypeDescriptors 0x00832A10 and 0x00832A48 identify
// VectorClass<ObjectTypeClass*> and DynamicVectorClass<ObjectTypeClass*>; COLs
// 0x008074E0 and 0x008074B0 point at them, and the dynamic hierarchy (CHD
// 0x008074A0, two base classes) records the vector as its zero-offset base.
// VectorClass<T> address point 0x007EF28C and DynamicVectorClass<T> address
// point 0x007EF26C are each seven-slot tables whose COL is at address-4.
// Complete function spans (control-flow closure from each entry, not the
// first RET) were checked against the pinned retail PE. This TU recovers the
// vector specialization only; it makes no constructor, original-TU, or
// complete ObjectTypeClass layout claim.
#include "vector_class_operations.h"

class ObjectTypeClass;

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete(void*), ??3@YAXPAX@Z.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// FUNCTION: GAMEMD 0x005F9B00
// FUNCTION: GAMEMD 0x005F9B30
// FUNCTION: GAMEMD 0x005F9B50
// FUNCTION: GAMEMD 0x005F9B80
// FUNCTION: GAMEMD 0x005F9BC0
// FUNCTION: GAMEMD 0x005F9C70
// FUNCTION: GAMEMD 0x005F9CA0
// FUNCTION: GAMEMD 0x005F9CE0
// FUNCTION: GAMEMD 0x005F9D00
// FUNCTION: GAMEMD 0x005F9DB0
// FUNCTION: GAMEMD 0x005F9DE0
// FUNCTION: GAMEMD 0x005F9E30
template class VectorClass<ObjectTypeClass*>;
template class DynamicVectorClass<ObjectTypeClass*>;

// VTABLE: GAMEMD 0x007EF28C -- VectorClass<ObjectTypeClass*>.
// VTABLE: GAMEMD 0x007EF26C -- DynamicVectorClass<ObjectTypeClass*>.

typedef VectorClass<ObjectTypeClass*> GgObjectTypeClassVector;
typedef DynamicVectorClass<ObjectTypeClass*> GgObjectTypeClassDynamicVector;
GG_STATIC_ASSERT(sizeof(ObjectTypeClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgObjectTypeClassVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgObjectTypeClassVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgObjectTypeClassVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgObjectTypeClassVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgObjectTypeClassVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgObjectTypeClassVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgObjectTypeClassDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgObjectTypeClassDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgObjectTypeClassDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgObjectTypeClassDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgObjectTypeClassDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgObjectTypeClassDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgObjectTypeClassDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgObjectTypeClassDynamicVector, CapacityIncrement) == 0x14);
