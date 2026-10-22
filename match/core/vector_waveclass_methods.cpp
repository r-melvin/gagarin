// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVWaveClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class WaveClass;

// FUNCTION: GAMEMD 0x4E86C0
// DynamicVectorClass<WaveClass*>::Clear

// FUNCTION: GAMEMD 0x4E86F0
// DynamicVectorClass<WaveClass*>::Slot5

// FUNCTION: GAMEMD 0x4E8710
// VectorClass<WaveClass*>::Slot6

// FUNCTION: GAMEMD 0x4EADA0
// VectorClass<WaveClass*>::operator==

// FUNCTION: GAMEMD 0x4EADE0
// VectorClass<WaveClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EAE90
// VectorClass<WaveClass*>::Clear

// FUNCTION: GAMEMD 0x4EAEC0
// VectorClass<WaveClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4EAF00
// VectorClass<WaveClass*>::Slot5

// FUNCTION: GAMEMD 0x4EAF20
// DynamicVectorClass<WaveClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4EAFD0
// DynamicVectorClass<WaveClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4EFC10
// VectorClass<WaveClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4EFC60
// DynamicVectorClass<WaveClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E9D04 -- VectorClass<WaveClass*>.
template class VectorClass<WaveClass*>;
typedef VectorClass<WaveClass*> GgWaveClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgWaveClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgWaveClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgWaveClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgWaveClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E9CE4 -- DynamicVectorClass<WaveClass*>.
template class DynamicVectorClass<WaveClass*>;
typedef DynamicVectorClass<WaveClass*> GgWaveClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgWaveClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgWaveClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgWaveClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgWaveClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgWaveClassDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgWaveClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(WaveClass*) == 4);
