// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail RTTI TypeDescriptors 0x00839920 and 0x00839958 identify
// VectorClass<RadarEventClass*> and DynamicVectorClass<RadarEventClass*>;
// the dynamic hierarchy records the former as its zero-offset base.
// Complete function spans and the two slot arrays were checked against the
// pinned retail PE. This TU recovers the vector specialization only; it makes
// no constructor, original-TU, or complete RadarEventClass layout claim.
// The derived deleting-dtor full span requires /GX off; the base dtor also
// matches with /GX. Both table checks rely on VC6 weak defaults, so final-link
// resolution is not established here.
#include "vector_class_operations.h"

class RadarEventClass;

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// FUNCTION: GAMEMD 0x00660C80
// FUNCTION: GAMEMD 0x00660CB0
// FUNCTION: GAMEMD 0x00660CD0
// FUNCTION: GAMEMD 0x00660CE0
// FUNCTION: GAMEMD 0x00660D20
// FUNCTION: GAMEMD 0x00660DD0
// FUNCTION: GAMEMD 0x00660E00
// FUNCTION: GAMEMD 0x00660E40
// FUNCTION: GAMEMD 0x00660E60
// FUNCTION: GAMEMD 0x00660F50
// FUNCTION: GAMEMD 0x00660F80
// FUNCTION: GAMEMD 0x00660FD0
template class VectorClass<RadarEventClass*>;
template class DynamicVectorClass<RadarEventClass*>;

// VTABLE: GAMEMD 0x007F0ACC -- VectorClass<RadarEventClass*>.
// VTABLE: GAMEMD 0x007F0AAC -- DynamicVectorClass<RadarEventClass*>.

typedef VectorClass<RadarEventClass*> GgRadarEventVector;
typedef DynamicVectorClass<RadarEventClass*> GgRadarEventDynamicVector;
GG_STATIC_ASSERT(sizeof(RadarEventClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgRadarEventVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgRadarEventVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgRadarEventVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgRadarEventVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgRadarEventVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgRadarEventVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgRadarEventDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgRadarEventDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgRadarEventDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgRadarEventDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgRadarEventDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgRadarEventDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgRadarEventDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgRadarEventDynamicVector, CapacityIncrement) == 0x14);
