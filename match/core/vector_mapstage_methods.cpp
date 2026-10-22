// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Paired flag probes: /GX shortens the dynamic deleting entry to 0x20
// bytes; no-GX matches its full 0x49-byte span. Other 11 bodies match both.
// Retail RTTI TypeDescriptors 0x00830200 and 0x00830230 identify
// VectorClass<MapStage*> and DynamicVectorClass<MapStage*>; COLs 0x008069F0
// and 0x00806928 point at them, and the dynamic hierarchy (CHD 0x00806918,
// two base classes) records the vector as its zero-offset base.
// VectorClass<T> address point 0x007EEAB4 and DynamicVectorClass<T> address
// point 0x007EEA94 are each seven-slot tables whose COL is at address-4.
// Complete function spans (control-flow closure from each entry, not the
// first RET) were checked against the pinned retail PE. This TU recovers the
// vector specialization only; it makes no constructor, original-TU, or
// complete MapStage layout claim.
#include "vector_class_operations.h"

class MapStage;

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete(void*), ??3@YAXPAX@Z.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// FUNCTION: GAMEMD 0x005D06D0
// FUNCTION: GAMEMD 0x005D0700
// FUNCTION: GAMEMD 0x005D0720
// FUNCTION: GAMEMD 0x005D0FA0
// FUNCTION: GAMEMD 0x005D0FE0
// FUNCTION: GAMEMD 0x005D1090
// FUNCTION: GAMEMD 0x005D10C0
// FUNCTION: GAMEMD 0x005D1100
// FUNCTION: GAMEMD 0x005D1120
// FUNCTION: GAMEMD 0x005D11D0
// FUNCTION: GAMEMD 0x005D18A0
// FUNCTION: GAMEMD 0x005D18F0
template class VectorClass<MapStage*>;
template class DynamicVectorClass<MapStage*>;

// VTABLE: GAMEMD 0x007EEAB4 -- VectorClass<MapStage*>.
// VTABLE: GAMEMD 0x007EEA94 -- DynamicVectorClass<MapStage*>.

typedef VectorClass<MapStage*> GgMapStageVector;
typedef DynamicVectorClass<MapStage*> GgMapStageDynamicVector;
GG_STATIC_ASSERT(sizeof(MapStage*) == 4);
GG_STATIC_ASSERT(sizeof(GgMapStageVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMapStageVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMapStageVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMapStageVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMapStageVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMapStageVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgMapStageDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgMapStageDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMapStageDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMapStageDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMapStageDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMapStageDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgMapStageDynamicVector, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMapStageDynamicVector, CapacityIncrement) == 0x14);
