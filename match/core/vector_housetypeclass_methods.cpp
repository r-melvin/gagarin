// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail RTTI TypeDescriptors 0x8235E8 and 0x823618 identify
// VectorClass<HouseTypeClass*> and DynamicVectorClass<HouseTypeClass*>; the latter's
// CHD names the former as its zero-offset base.
// Full entry spans bind these methods; original TUs and standalone constructors
// are not established. No GX matches the complete derived deleting wrapper.
#include "vector_class_operations.h"
class HouseTypeClass;

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// FUNCTION: GAMEMD 0x4E8AE0
// DynamicVectorClass<HouseTypeClass*>::Clear
// FUNCTION: GAMEMD 0x4E8B10
// DynamicVectorClass<HouseTypeClass*>::Slot5
// FUNCTION: GAMEMD 0x4E8B30
// VectorClass<HouseTypeClass*>::Slot6
// FUNCTION: GAMEMD 0x4EC7C0
// VectorClass<HouseTypeClass*>::operator==
// FUNCTION: GAMEMD 0x4EC800
// VectorClass<HouseTypeClass*>::SetCapacity
// FUNCTION: GAMEMD 0x4EC8B0
// VectorClass<HouseTypeClass*>::Clear
// FUNCTION: GAMEMD 0x4EC8E0
// VectorClass<HouseTypeClass*>::FindItemIndex
// FUNCTION: GAMEMD 0x4EC920
// VectorClass<HouseTypeClass*>::Slot5
// FUNCTION: GAMEMD 0x4EC940
// DynamicVectorClass<HouseTypeClass*>::SetCapacity
// FUNCTION: GAMEMD 0x4EC9F0
// DynamicVectorClass<HouseTypeClass*>::FindItemIndex
// SYNTHETIC: GAMEMD 0x4F02F0
// VectorClass<HouseTypeClass*>::scalar deleting destructor
// SYNTHETIC: GAMEMD 0x4F0340
// DynamicVectorClass<HouseTypeClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EA084 -- VectorClass<HouseTypeClass*>.
template class VectorClass<HouseTypeClass*>;
// VTABLE: GAMEMD 0x7EA064 -- DynamicVectorClass<HouseTypeClass*>.
template class DynamicVectorClass<HouseTypeClass*>;

typedef VectorClass<HouseTypeClass*> GgHouseTypeVector;
typedef DynamicVectorClass<HouseTypeClass*> GgHouseTypeDynamicVector;
GG_STATIC_ASSERT(sizeof(HouseTypeClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgHouseTypeVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgHouseTypeVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgHouseTypeVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgHouseTypeVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgHouseTypeVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgHouseTypeVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgHouseTypeDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgHouseTypeDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgHouseTypeDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgHouseTypeDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgHouseTypeDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgHouseTypeDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgHouseTypeDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgHouseTypeDynamicVector, CapacityIncrement) == 0x14);
