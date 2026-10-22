// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Paired flag probes: /GX shortens the dynamic deleting entry to 0x20
// bytes; no-GX matches its full 0x49-byte span. Other 11 bodies match both.
// Retail RTTI TypeDescriptors 0x00829D48 and 0x00829D78 identify
// VectorClass<LineTrail*> and DynamicVectorClass<LineTrail*>; COLs 0x008051D8
// and 0x008051A8 point at them, and the dynamic hierarchy (CHD 0x00805198,
// two base classes) records the vector as its zero-offset base.
// VectorClass<T> address point 0x007ED0EC and DynamicVectorClass<T> address
// point 0x007ED0CC are each seven-slot tables whose COL is at address-4.
// Complete function spans (control-flow closure from each entry, not the
// first RET) were checked against the pinned retail PE. This TU recovers the
// vector specialization only; it makes no constructor, original-TU, or
// complete LineTrail layout claim.
#include "vector_class_operations.h"

class LineTrail;

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete(void*), ??3@YAXPAX@Z.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// FUNCTION: GAMEMD 0x00556EB0
// FUNCTION: GAMEMD 0x00556EE0
// FUNCTION: GAMEMD 0x00556F00
// FUNCTION: GAMEMD 0x00556F10
// FUNCTION: GAMEMD 0x00556F50
// FUNCTION: GAMEMD 0x00557000
// FUNCTION: GAMEMD 0x00557030
// FUNCTION: GAMEMD 0x00557070
// FUNCTION: GAMEMD 0x00557090
// FUNCTION: GAMEMD 0x00557140
// FUNCTION: GAMEMD 0x00557170
// FUNCTION: GAMEMD 0x005571C0
template class VectorClass<LineTrail*>;
template class DynamicVectorClass<LineTrail*>;

// VTABLE: GAMEMD 0x007ED0EC -- VectorClass<LineTrail*>.
// VTABLE: GAMEMD 0x007ED0CC -- DynamicVectorClass<LineTrail*>.

typedef VectorClass<LineTrail*> GgLineTrailVector;
typedef DynamicVectorClass<LineTrail*> GgLineTrailDynamicVector;
GG_STATIC_ASSERT(sizeof(LineTrail*) == 4);
GG_STATIC_ASSERT(sizeof(GgLineTrailVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgLineTrailVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgLineTrailVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgLineTrailVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgLineTrailVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgLineTrailVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgLineTrailDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgLineTrailDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgLineTrailDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgLineTrailDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgLineTrailDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgLineTrailDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgLineTrailDynamicVector, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgLineTrailDynamicVector, CapacityIncrement) == 0x14);
