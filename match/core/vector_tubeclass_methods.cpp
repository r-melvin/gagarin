// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Retail RTTI TypeDescriptors 0x00822FD0 and 0x00823000 identify
// VectorClass<TubeClass*> and DynamicVectorClass<TubeClass*>; COLs 0x00800F20
// and 0x00800EF0 point at them, and the dynamic hierarchy (CHD 0x00800EE0,
// two base classes) records the vector as its zero-offset base.
// VectorClass<T> address point 0x007E9CC4 and DynamicVectorClass<T> address
// point 0x007E9CA4 are each seven-slot tables whose COL is at address-4.
// Complete function spans (control-flow closure from each entry, not the
// first RET) were checked against the pinned retail PE. This TU recovers the
// vector specialization only; it makes no constructor, original-TU, or
// complete TubeClass layout claim. /GX is omitted because it changes the
// DynamicVectorClass deleting-destructor entry at 0x004EFB20 into a wrapper;
// the no-/GX emission matches the retail body, while the other 11 spans match
// with either flag set.
#include "vector_class_operations.h"

class TubeClass;

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
// LIBRARY: GAMEMD 0x7C8B3D -- operator delete(void*), ??3@YAXPAX@Z.

// FUNCTION: GAMEMD 0x004E8600
// FUNCTION: GAMEMD 0x004E8630
// FUNCTION: GAMEMD 0x004E8650
// FUNCTION: GAMEMD 0x004EA8E0
// FUNCTION: GAMEMD 0x004EA920
// FUNCTION: GAMEMD 0x004EA9D0
// FUNCTION: GAMEMD 0x004EAA00
// FUNCTION: GAMEMD 0x004EAA40
// FUNCTION: GAMEMD 0x004EAA60
// FUNCTION: GAMEMD 0x004EAB10
// FUNCTION: GAMEMD 0x004EFAD0
// FUNCTION: GAMEMD 0x004EFB20
template class VectorClass<TubeClass*>;
template class DynamicVectorClass<TubeClass*>;

// VTABLE: GAMEMD 0x007E9CC4 -- VectorClass<TubeClass*>.
// VTABLE: GAMEMD 0x007E9CA4 -- DynamicVectorClass<TubeClass*>.

typedef VectorClass<TubeClass*> GgTubeClassVector;
typedef DynamicVectorClass<TubeClass*> GgTubeClassDynamicVector;
GG_STATIC_ASSERT(sizeof(TubeClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgTubeClassVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTubeClassVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTubeClassVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTubeClassVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTubeClassVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTubeClassVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgTubeClassDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgTubeClassDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTubeClassDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTubeClassDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTubeClassDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTubeClassDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgTubeClassDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTubeClassDynamicVector, CapacityIncrement) == 0x14);
