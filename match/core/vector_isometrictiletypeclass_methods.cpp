// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Paired flag probes: /GX shortens the dynamic deleting entry to 0x20
// bytes; no-GX matches its full 0x49-byte span. Other 11 bodies match both.
// Retail RTTI TypeDescriptors 0x00823C10 and 0x00823C48 identify
// VectorClass<IsometricTileTypeClass*> and DynamicVectorClass<IsometricTileTypeClass*>;
// COLs 0x00802058 and 0x00802028 point at them, and the dynamic hierarchy (CHD
// 0x00802018, two base classes) records the vector as its zero-offset base.
// VectorClass<T> address point 0x007EA404 and DynamicVectorClass<T> address
// point 0x007EA3E4 are each seven-slot tables whose COL is at address-4.
// Complete function spans (control-flow closure from each entry, not the
// first RET) were checked against the pinned retail PE. This TU recovers the
// vector specialization only; it makes no constructor, original-TU, or
// complete IsometricTileTypeClass layout claim.
#include "vector_class_operations.h"

class IsometricTileTypeClass;

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete(void*), ??3@YAXPAX@Z.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// FUNCTION: GAMEMD 0x004E9020
// FUNCTION: GAMEMD 0x004E9050
// FUNCTION: GAMEMD 0x004E9070
// FUNCTION: GAMEMD 0x004EE900
// FUNCTION: GAMEMD 0x004EE940
// FUNCTION: GAMEMD 0x004EE9F0
// FUNCTION: GAMEMD 0x004EEA20
// FUNCTION: GAMEMD 0x004EEA60
// FUNCTION: GAMEMD 0x004EEA80
// FUNCTION: GAMEMD 0x004EEB30
// FUNCTION: GAMEMD 0x004F0BB0
// FUNCTION: GAMEMD 0x004F0C00
template class VectorClass<IsometricTileTypeClass*>;
template class DynamicVectorClass<IsometricTileTypeClass*>;

// VTABLE: GAMEMD 0x007EA404 -- VectorClass<IsometricTileTypeClass*>.
// VTABLE: GAMEMD 0x007EA3E4 -- DynamicVectorClass<IsometricTileTypeClass*>.

typedef VectorClass<IsometricTileTypeClass*> GgIsometricTileTypeClassVector;
typedef DynamicVectorClass<IsometricTileTypeClass*> GgIsometricTileTypeClassDynamicVector;
GG_STATIC_ASSERT(sizeof(IsometricTileTypeClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgIsometricTileTypeClassVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgIsometricTileTypeClassVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgIsometricTileTypeClassVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgIsometricTileTypeClassVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgIsometricTileTypeClassVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgIsometricTileTypeClassVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgIsometricTileTypeClassDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgIsometricTileTypeClassDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgIsometricTileTypeClassDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgIsometricTileTypeClassDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgIsometricTileTypeClassDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgIsometricTileTypeClassDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgIsometricTileTypeClassDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgIsometricTileTypeClassDynamicVector, CapacityIncrement) == 0x14);
