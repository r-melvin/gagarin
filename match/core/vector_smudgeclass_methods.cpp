// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Paired flag probes: /GX shortens the dynamic deleting entry to 0x20
// bytes; no-GX matches its full 0x49-byte span. Other 11 bodies match both.
// Retail RTTI TypeDescriptors 0x00823170 and 0x008231A0 identify
// VectorClass<SmudgeClass*> and DynamicVectorClass<SmudgeClass*>; COLs 0x00801180
// and 0x00801150 point at them, and the dynamic hierarchy (CHD 0x00801140,
// two base classes) records the vector as its zero-offset base.
// VectorClass<T> address point 0x007E9DC4 and DynamicVectorClass<T> address
// point 0x007E9DA4 are each seven-slot tables whose COL is at address-4.
// Complete function spans (control-flow closure from each entry, not the
// first RET) were checked against the pinned retail PE. This TU recovers the
// vector specialization only; it makes no constructor, original-TU, or
// complete SmudgeClass layout claim.
#include "vector_class_operations.h"

class SmudgeClass;

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete(void*), ??3@YAXPAX@Z.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// FUNCTION: GAMEMD 0x004E8780
// FUNCTION: GAMEMD 0x004E87B0
// FUNCTION: GAMEMD 0x004E87D0
// FUNCTION: GAMEMD 0x004EB260
// FUNCTION: GAMEMD 0x004EB2A0
// FUNCTION: GAMEMD 0x004EB350
// FUNCTION: GAMEMD 0x004EB380
// FUNCTION: GAMEMD 0x004EB3C0
// FUNCTION: GAMEMD 0x004EB3E0
// FUNCTION: GAMEMD 0x004EB490
// FUNCTION: GAMEMD 0x004EFD50
// FUNCTION: GAMEMD 0x004EFDA0
template class VectorClass<SmudgeClass*>;
template class DynamicVectorClass<SmudgeClass*>;

// VTABLE: GAMEMD 0x007E9DC4 -- VectorClass<SmudgeClass*>.
// VTABLE: GAMEMD 0x007E9DA4 -- DynamicVectorClass<SmudgeClass*>.

typedef VectorClass<SmudgeClass*> GgSmudgeClassVector;
typedef DynamicVectorClass<SmudgeClass*> GgSmudgeClassDynamicVector;
GG_STATIC_ASSERT(sizeof(SmudgeClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgSmudgeClassVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgSmudgeClassVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgSmudgeClassVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgSmudgeClassVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgSmudgeClassVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgSmudgeClassVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgSmudgeClassDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgSmudgeClassDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgSmudgeClassDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgSmudgeClassDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgSmudgeClassDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgSmudgeClassDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgSmudgeClassDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgSmudgeClassDynamicVector, CapacityIncrement) == 0x14);
