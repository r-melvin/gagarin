// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Paired flag probes: /GX shortens the dynamic deleting entry to 0x20
// bytes; no-GX matches its full 0x49-byte span. Other 11 bodies match both.
// Retail RTTI TypeDescriptors 0x008365D8 and 0x00836608 identify
// VectorClass<ParasiteClass*> and DynamicVectorClass<ParasiteClass*>; COLs
// 0x00807A80 and 0x00807A50 point at them, and the dynamic hierarchy (CHD
// 0x00807A40, two base classes) records the vector as its zero-offset base.
// VectorClass<T> address point 0x007EF844 and DynamicVectorClass<T> address
// point 0x007EF824 are each seven-slot tables whose COL is at address-4.
// Complete function spans (control-flow closure from each entry, not the
// first RET) were checked against the pinned retail PE. This TU recovers the
// vector specialization only; it makes no constructor, original-TU, or
// complete ParasiteClass layout claim.
#include "vector_class_operations.h"

class ParasiteClass;

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete(void*), ??3@YAXPAX@Z.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// FUNCTION: GAMEMD 0x0062B070
// FUNCTION: GAMEMD 0x0062B0A0
// FUNCTION: GAMEMD 0x0062B0C0
// FUNCTION: GAMEMD 0x0062B0D0
// FUNCTION: GAMEMD 0x0062B110
// FUNCTION: GAMEMD 0x0062B1C0
// FUNCTION: GAMEMD 0x0062B1F0
// FUNCTION: GAMEMD 0x0062B230
// FUNCTION: GAMEMD 0x0062B250
// FUNCTION: GAMEMD 0x0062B300
// FUNCTION: GAMEMD 0x0062B330
// FUNCTION: GAMEMD 0x0062B380
template class VectorClass<ParasiteClass*>;
template class DynamicVectorClass<ParasiteClass*>;

// VTABLE: GAMEMD 0x007EF844 -- VectorClass<ParasiteClass*>.
// VTABLE: GAMEMD 0x007EF824 -- DynamicVectorClass<ParasiteClass*>.

typedef VectorClass<ParasiteClass*> GgParasiteClassVector;
typedef DynamicVectorClass<ParasiteClass*> GgParasiteClassDynamicVector;
GG_STATIC_ASSERT(sizeof(ParasiteClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgParasiteClassVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgParasiteClassVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgParasiteClassVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgParasiteClassVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgParasiteClassVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgParasiteClassVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgParasiteClassDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgParasiteClassDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgParasiteClassDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgParasiteClassDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgParasiteClassDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgParasiteClassDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgParasiteClassDynamicVector, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgParasiteClassDynamicVector, CapacityIncrement) == 0x14);
