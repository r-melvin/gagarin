// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Retail PAVRadBeam RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class RadBeam;

// FUNCTION: GAMEMD 0x65A1E0
// DynamicVectorClass<RadBeam*>::Clear

// FUNCTION: GAMEMD 0x65A210
// DynamicVectorClass<RadBeam*>::Slot5

// FUNCTION: GAMEMD 0x65A230
// VectorClass<RadBeam*>::Slot6

// FUNCTION: GAMEMD 0x65A240
// VectorClass<RadBeam*>::operator==

// FUNCTION: GAMEMD 0x65A280
// VectorClass<RadBeam*>::SetCapacity

// FUNCTION: GAMEMD 0x65A330
// VectorClass<RadBeam*>::Clear

// FUNCTION: GAMEMD 0x65A360
// VectorClass<RadBeam*>::FindItemIndex

// FUNCTION: GAMEMD 0x65A3A0
// VectorClass<RadBeam*>::Slot5

// FUNCTION: GAMEMD 0x65A3C0
// DynamicVectorClass<RadBeam*>::SetCapacity

// FUNCTION: GAMEMD 0x65A470
// DynamicVectorClass<RadBeam*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x65A4A0
// VectorClass<RadBeam*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x65A4F0
// DynamicVectorClass<RadBeam*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7F04A4 -- VectorClass<RadBeam*>.
template class VectorClass<RadBeam*>;
typedef VectorClass<RadBeam*> GgRadbeamVectorClass;
GG_STATIC_ASSERT(offsetof(GgRadbeamVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgRadbeamVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgRadbeamVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgRadbeamVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F0484 -- DynamicVectorClass<RadBeam*>.
template class DynamicVectorClass<RadBeam*>;
typedef DynamicVectorClass<RadBeam*> GgRadbeamDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgRadbeamDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgRadbeamDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgRadbeamDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgRadbeamDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgRadbeamDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgRadbeamDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(RadBeam*) == 4);
