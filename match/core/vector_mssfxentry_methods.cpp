// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Paired flag probes: /GX shortens the dynamic deleting entry to 0x20
// bytes; no-GX matches its full 0x49-byte span. Other 11 bodies match both.
// Retail RTTI TypeDescriptors 0x00830268 and 0x00830298 identify
// VectorClass<MSSfxEntry*> and DynamicVectorClass<MSSfxEntry*>; COLs 0x00806A20
// and 0x00806990 point at them, and the dynamic hierarchy (CHD 0x00806980,
// two base classes) records the vector as its zero-offset base.
// VectorClass<T> address point 0x007EEAF4 and DynamicVectorClass<T> address
// point 0x007EEA54 are each seven-slot tables whose COL is at address-4.
// Complete function spans (control-flow closure from each entry, not the
// first RET) were checked against the pinned retail PE. This TU recovers the
// vector specialization only; it makes no constructor, original-TU, or
// complete MSSfxEntry layout claim.
#include "vector_class_operations.h"

class MSSfxEntry;

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete(void*), ??3@YAXPAX@Z.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// FUNCTION: GAMEMD 0x005D0790
// FUNCTION: GAMEMD 0x005D07C0
// FUNCTION: GAMEMD 0x005D07E0
// FUNCTION: GAMEMD 0x005D1460
// FUNCTION: GAMEMD 0x005D14A0
// FUNCTION: GAMEMD 0x005D1550
// FUNCTION: GAMEMD 0x005D1580
// FUNCTION: GAMEMD 0x005D15C0
// FUNCTION: GAMEMD 0x005D15E0
// FUNCTION: GAMEMD 0x005D1690
// FUNCTION: GAMEMD 0x005D19E0
// FUNCTION: GAMEMD 0x005D1A30
template class VectorClass<MSSfxEntry*>;
template class DynamicVectorClass<MSSfxEntry*>;

// VTABLE: GAMEMD 0x007EEAF4 -- VectorClass<MSSfxEntry*>.
// VTABLE: GAMEMD 0x007EEA54 -- DynamicVectorClass<MSSfxEntry*>.

typedef VectorClass<MSSfxEntry*> GgMSSfxEntryVector;
typedef DynamicVectorClass<MSSfxEntry*> GgMSSfxEntryDynamicVector;
GG_STATIC_ASSERT(sizeof(MSSfxEntry*) == 4);
GG_STATIC_ASSERT(sizeof(GgMSSfxEntryVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMSSfxEntryVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMSSfxEntryVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMSSfxEntryVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMSSfxEntryVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMSSfxEntryVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgMSSfxEntryDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgMSSfxEntryDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMSSfxEntryDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMSSfxEntryDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMSSfxEntryDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMSSfxEntryDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgMSSfxEntryDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMSSfxEntryDynamicVector, CapacityIncrement) == 0x14);
