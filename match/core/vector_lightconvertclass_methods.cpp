// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail RTTI TypeDescriptors 0x8169B8 and 0x8169F0 identify
// VectorClass<LightConvertClass*> and DynamicVectorClass<LightConvertClass*>; the latter's
// CHD names the former as its zero-offset base.
// Complete entry spans bind these methods. Original TUs and standalone
// constructors are unestablished; the derived deleting body needs GX off.
#include "vector_class_operations.h"
class LightConvertClass;

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// FUNCTION: GAMEMD 0x40C230
// DynamicVectorClass<LightConvertClass*>::Clear
// FUNCTION: GAMEMD 0x40C260
// DynamicVectorClass<LightConvertClass*>::Slot5
// FUNCTION: GAMEMD 0x40C280
// VectorClass<LightConvertClass*>::Slot6
// FUNCTION: GAMEMD 0x40C290
// VectorClass<LightConvertClass*>::operator==
// FUNCTION: GAMEMD 0x40C2D0
// VectorClass<LightConvertClass*>::SetCapacity
// FUNCTION: GAMEMD 0x40C380
// VectorClass<LightConvertClass*>::Clear
// FUNCTION: GAMEMD 0x40C3B0
// VectorClass<LightConvertClass*>::FindItemIndex
// FUNCTION: GAMEMD 0x40C3F0
// VectorClass<LightConvertClass*>::Slot5
// FUNCTION: GAMEMD 0x40C410
// DynamicVectorClass<LightConvertClass*>::SetCapacity
// FUNCTION: GAMEMD 0x40C4C0
// DynamicVectorClass<LightConvertClass*>::FindItemIndex
// SYNTHETIC: GAMEMD 0x40C4F0
// VectorClass<LightConvertClass*>::scalar deleting destructor
// SYNTHETIC: GAMEMD 0x40C540
// DynamicVectorClass<LightConvertClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E188C -- VectorClass<LightConvertClass*>.
template class VectorClass<LightConvertClass*>;
// VTABLE: GAMEMD 0x7E186C -- DynamicVectorClass<LightConvertClass*>.
template class DynamicVectorClass<LightConvertClass*>;

typedef VectorClass<LightConvertClass*> GgLightConvertVector;
typedef DynamicVectorClass<LightConvertClass*> GgLightConvertDynamicVector;
GG_STATIC_ASSERT(sizeof(LightConvertClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgLightConvertVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgLightConvertVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgLightConvertVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgLightConvertVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgLightConvertVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgLightConvertVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgLightConvertDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgLightConvertDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgLightConvertDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgLightConvertDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgLightConvertDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgLightConvertDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgLightConvertDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgLightConvertDynamicVector, CapacityIncrement) == 0x14);
