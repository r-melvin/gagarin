// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; retail TypeDescriptors/COLs and all 12
// entry-origin spans plus both address-point tables were confirmed directly.
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// The dynamic deleting-dtor full span needs /GX disabled; with /GX, only that
// emitted wrapper is short. The base deleting dtor also matches with /GX.
// Vtable checks use recorded weak defaults and are conditional, not final-link proof.
#include "vector_class_operations.h"

class MSAnimEntry;

// FUNCTION: GAMEMD 0x005D0730
// FUNCTION: GAMEMD 0x005D0760
// FUNCTION: GAMEMD 0x005D0780
// FUNCTION: GAMEMD 0x005D1200
// FUNCTION: GAMEMD 0x005D1240
// FUNCTION: GAMEMD 0x005D12F0
// FUNCTION: GAMEMD 0x005D1320
// FUNCTION: GAMEMD 0x005D1360
// FUNCTION: GAMEMD 0x005D1380
// FUNCTION: GAMEMD 0x005D1430
// FUNCTION: GAMEMD 0x005D1940
// FUNCTION: GAMEMD 0x005D1990
template class VectorClass<MSAnimEntry*>;
template class DynamicVectorClass<MSAnimEntry*>;

// VTABLE: GAMEMD 0x007EEA74 -- DynamicVectorClass<MSAnimEntry*>.
// VTABLE: GAMEMD 0x007EEAD4 -- VectorClass<MSAnimEntry*>.
typedef VectorClass<MSAnimEntry*> GgMsAnimEntryVector;
typedef DynamicVectorClass<MSAnimEntry*> GgMsAnimEntryDynamicVector;
GG_STATIC_ASSERT(sizeof(MSAnimEntry*) == 4);
GG_STATIC_ASSERT(sizeof(GgMsAnimEntryVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMsAnimEntryVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMsAnimEntryVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMsAnimEntryVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMsAnimEntryVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMsAnimEntryVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgMsAnimEntryDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgMsAnimEntryDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMsAnimEntryDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMsAnimEntryDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMsAnimEntryDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMsAnimEntryDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgMsAnimEntryDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMsAnimEntryDynamicVector, CapacityIncrement) == 0x14);
