// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Paired flag probes: /GX shortens the dynamic deleting entry to 0x20
// bytes; no-GX matches its full 0x49-byte span. Other 11 bodies match both.
// Retail RTTI TypeDescriptors 0x00830500 and 0x00830528 identify
// VectorClass<MSSfx*> and DynamicVectorClass<MSSfx*>; COLs 0x00806D18 and
// 0x00806C50 point at them, and the dynamic hierarchy (CHD 0x00806C40, two
// base classes) records the vector as its zero-offset base.
// VectorClass<T> address point 0x007EEC44 and DynamicVectorClass<T> address
// point 0x007EEBE4 are each seven-slot tables whose COL is at address-4; the
// words after each table's seventh slot are the next table's COL.
// Complete function spans (control-flow closure from each entry, not the
// first RET) were checked against the pinned retail PE. This TU recovers the
// vector specialization only; it makes no constructor, original-TU, or
// complete MSSfx layout claim.
#include "vector_class_operations.h"

class MSSfx;

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete(void*), ??3@YAXPAX@Z.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// FUNCTION: GAMEMD 0x005D2780
// FUNCTION: GAMEMD 0x005D27B0
// FUNCTION: GAMEMD 0x005D27D0
// FUNCTION: GAMEMD 0x005D2A40
// FUNCTION: GAMEMD 0x005D2A80
// FUNCTION: GAMEMD 0x005D2B30
// FUNCTION: GAMEMD 0x005D2B60
// FUNCTION: GAMEMD 0x005D2BA0
// FUNCTION: GAMEMD 0x005D2BC0
// FUNCTION: GAMEMD 0x005D2C70
// FUNCTION: GAMEMD 0x005D2D40
// FUNCTION: GAMEMD 0x005D2D90
template class VectorClass<MSSfx*>;
template class DynamicVectorClass<MSSfx*>;

// VTABLE: GAMEMD 0x007EEC44 -- VectorClass<MSSfx*>.
// VTABLE: GAMEMD 0x007EEBE4 -- DynamicVectorClass<MSSfx*>.

typedef VectorClass<MSSfx*> GgMSSfxVector;
typedef DynamicVectorClass<MSSfx*> GgMSSfxDynamicVector;
GG_STATIC_ASSERT(sizeof(MSSfx*) == 4);
GG_STATIC_ASSERT(sizeof(GgMSSfxVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMSSfxVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMSSfxVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMSSfxVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMSSfxVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMSSfxVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgMSSfxDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgMSSfxDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMSSfxDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMSSfxDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMSSfxDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMSSfxDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgMSSfxDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMSSfxDynamicVector, CapacityIncrement) == 0x14);
