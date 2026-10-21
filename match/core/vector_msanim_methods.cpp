// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Paired flag probes: /GX shortens the dynamic deleting entry to 0x20
// bytes; no-GX reproduces its full 0x49-byte span. Other 11 bodies match both.
// Retail RTTI TypeDescriptors 0x00830558 and 0x00830580 identify
// VectorClass<MSAnim*> and DynamicVectorClass<MSAnim*>; COLs 0x00806D48 and
// 0x00806CB8 point at them, and the dynamic hierarchy (CHD 0x00806CA8, two
// base classes, BCD 0x00806C68 for the vector at zero offset) records the
// vector as its zero-offset base.
// VectorClass<T> address point 0x007EEC24 and DynamicVectorClass<T> address
// point 0x007EEC04 are each seven-slot tables whose COL is at address-4.
// Complete function spans (control-flow closure from each entry, not the
// first RET) were checked against the pinned retail PE. This TU recovers the
// vector specialization only; it makes no constructor, original-TU, or
// complete MSAnim layout claim.
#include "vector_class_operations.h"

class MSAnim;

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete(void*), ??3@YAXPAX@Z.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// FUNCTION: GAMEMD 0x005D2720
// FUNCTION: GAMEMD 0x005D2750
// FUNCTION: GAMEMD 0x005D2770
// FUNCTION: GAMEMD 0x005D27E0
// FUNCTION: GAMEMD 0x005D2820
// FUNCTION: GAMEMD 0x005D28D0
// FUNCTION: GAMEMD 0x005D2900
// FUNCTION: GAMEMD 0x005D2940
// FUNCTION: GAMEMD 0x005D2960
// FUNCTION: GAMEMD 0x005D2A10
// FUNCTION: GAMEMD 0x005D2CA0
// FUNCTION: GAMEMD 0x005D2CF0
template class VectorClass<MSAnim*>;
template class DynamicVectorClass<MSAnim*>;

// VTABLE: GAMEMD 0x007EEC24 -- VectorClass<MSAnim*>.
// VTABLE: GAMEMD 0x007EEC04 -- DynamicVectorClass<MSAnim*>.

typedef VectorClass<MSAnim*> GgMSAnimVector;
typedef DynamicVectorClass<MSAnim*> GgMSAnimDynamicVector;
GG_STATIC_ASSERT(sizeof(MSAnim*) == 4);
GG_STATIC_ASSERT(sizeof(GgMSAnimVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMSAnimVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMSAnimVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMSAnimVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMSAnimVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMSAnimVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgMSAnimDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgMSAnimDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMSAnimDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMSAnimDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMSAnimDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMSAnimDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgMSAnimDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMSAnimDynamicVector, CapacityIncrement) == 0x14);
