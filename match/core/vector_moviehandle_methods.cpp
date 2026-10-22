// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVMovieHandle RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

class MovieHandle;

// FUNCTION: GAMEMD 0x75A430
// DynamicVectorClass<MovieHandle*>::Clear

// FUNCTION: GAMEMD 0x75A460
// DynamicVectorClass<MovieHandle*>::Slot5

// FUNCTION: GAMEMD 0x75A480
// VectorClass<MovieHandle*>::Slot6

// FUNCTION: GAMEMD 0x75A490
// VectorClass<MovieHandle*>::operator==

// FUNCTION: GAMEMD 0x75A4D0
// VectorClass<MovieHandle*>::SetCapacity

// FUNCTION: GAMEMD 0x75A580
// VectorClass<MovieHandle*>::Clear

// FUNCTION: GAMEMD 0x75A5B0
// VectorClass<MovieHandle*>::FindItemIndex

// FUNCTION: GAMEMD 0x75A5F0
// VectorClass<MovieHandle*>::Slot5

// FUNCTION: GAMEMD 0x75A610
// DynamicVectorClass<MovieHandle*>::SetCapacity

// FUNCTION: GAMEMD 0x75A6C0
// DynamicVectorClass<MovieHandle*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x75A6F0
// VectorClass<MovieHandle*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x75A740
// DynamicVectorClass<MovieHandle*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7F69A4 -- VectorClass<MovieHandle*>.
template class VectorClass<MovieHandle*>;
typedef VectorClass<MovieHandle*> GgMovieHandleVectorClass;
GG_STATIC_ASSERT(offsetof(GgMovieHandleVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMovieHandleVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMovieHandleVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMovieHandleVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F6984 -- DynamicVectorClass<MovieHandle*>.
template class DynamicVectorClass<MovieHandle*>;
typedef DynamicVectorClass<MovieHandle*> GgMovieHandleDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgMovieHandleDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMovieHandleDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMovieHandleDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMovieHandleDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMovieHandleDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMovieHandleDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(MovieHandle*) == 4);
