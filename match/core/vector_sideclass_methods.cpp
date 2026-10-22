// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Paired flag probes: /GX shortens the dynamic deleting entry to 0x20
// bytes; no-GX matches its full 0x49-byte span. Other 11 bodies match both.
// Retail RTTI TypeDescriptors 0x00823580 and 0x008235B0 identify
// VectorClass<SideClass*> and DynamicVectorClass<SideClass*>; COLs 0x00801770
// and 0x00801740 point at them, and the dynamic hierarchy (CHD 0x00801730,
// two base classes) records the vector as its zero-offset base.
// VectorClass<T> address point 0x007EA044 and DynamicVectorClass<T> address
// point 0x007EA024 are each seven-slot tables whose COL is at address-4.
// Complete function spans (control-flow closure from each entry, not the
// first RET) were checked against the pinned retail PE. This TU recovers the
// vector specialization only; it makes no constructor, original-TU, or
// complete SideClass layout claim.
#include "vector_class_operations.h"

class SideClass;

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete(void*), ??3@YAXPAX@Z.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// FUNCTION: GAMEMD 0x004E8A80
// FUNCTION: GAMEMD 0x004E8AB0
// FUNCTION: GAMEMD 0x004E8AD0
// FUNCTION: GAMEMD 0x004EC560
// FUNCTION: GAMEMD 0x004EC5A0
// FUNCTION: GAMEMD 0x004EC650
// FUNCTION: GAMEMD 0x004EC680
// FUNCTION: GAMEMD 0x004EC6C0
// FUNCTION: GAMEMD 0x004EC6E0
// FUNCTION: GAMEMD 0x004EC790
// FUNCTION: GAMEMD 0x004F0250
// FUNCTION: GAMEMD 0x004F02A0
template class VectorClass<SideClass*>;
template class DynamicVectorClass<SideClass*>;

// VTABLE: GAMEMD 0x007EA044 -- VectorClass<SideClass*>.
// VTABLE: GAMEMD 0x007EA024 -- DynamicVectorClass<SideClass*>.

typedef VectorClass<SideClass*> GgSideClassVector;
typedef DynamicVectorClass<SideClass*> GgSideClassDynamicVector;
GG_STATIC_ASSERT(sizeof(SideClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgSideClassVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgSideClassVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgSideClassVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgSideClassVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgSideClassVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgSideClassVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgSideClassDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgSideClassDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgSideClassDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgSideClassDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgSideClassDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgSideClassDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgSideClassDynamicVector, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgSideClassDynamicVector, CapacityIncrement) == 0x14);
