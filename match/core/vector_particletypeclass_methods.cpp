// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Paired flag probes: /GX emits only 0x20 bytes for the dynamic deleting
// entry; no-GX matches its full 0x49-byte span. The other 11 match both.
// Retail RTTI TypeDescriptors 0x00823C88 and 0x00823CC0 identify
// VectorClass<ParticleTypeClass*> and DynamicVectorClass<ParticleTypeClass*>;
// COLs 0x008020F0 and 0x008020C0 point at them, and the dynamic hierarchy
// (CHD 0x008020B0, two base classes) records the vector as its zero-offset base.
// VectorClass<T> address point 0x007EA444 and DynamicVectorClass<T> address
// point 0x007EA424 are each seven-slot tables whose COL is at address-4.
// Complete function spans (control-flow closure from each entry, not the
// first RET) were checked against the pinned retail PE. This TU recovers the
// vector specialization only; it makes no constructor, original-TU, or
// complete ParticleTypeClass layout claim.
#include "vector_class_operations.h"

class ParticleTypeClass;

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete(void*), ??3@YAXPAX@Z.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// FUNCTION: GAMEMD 0x004E9080
// FUNCTION: GAMEMD 0x004E90B0
// FUNCTION: GAMEMD 0x004E90D0
// FUNCTION: GAMEMD 0x004EEB60
// FUNCTION: GAMEMD 0x004EEBA0
// FUNCTION: GAMEMD 0x004EEC50
// FUNCTION: GAMEMD 0x004EEC80
// FUNCTION: GAMEMD 0x004EECC0
// FUNCTION: GAMEMD 0x004EECE0
// FUNCTION: GAMEMD 0x004EED90
// FUNCTION: GAMEMD 0x004F0C50
// FUNCTION: GAMEMD 0x004F0CA0
template class VectorClass<ParticleTypeClass*>;
template class DynamicVectorClass<ParticleTypeClass*>;

// VTABLE: GAMEMD 0x007EA444 -- VectorClass<ParticleTypeClass*>.
// VTABLE: GAMEMD 0x007EA424 -- DynamicVectorClass<ParticleTypeClass*>.

typedef VectorClass<ParticleTypeClass*> GgParticleTypeClassVector;
typedef DynamicVectorClass<ParticleTypeClass*> GgParticleTypeClassDynamicVector;
GG_STATIC_ASSERT(sizeof(ParticleTypeClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgParticleTypeClassVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgParticleTypeClassVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgParticleTypeClassVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgParticleTypeClassVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgParticleTypeClassVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgParticleTypeClassVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgParticleTypeClassDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgParticleTypeClassDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgParticleTypeClassDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgParticleTypeClassDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgParticleTypeClassDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgParticleTypeClassDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgParticleTypeClassDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgParticleTypeClassDynamicVector, CapacityIncrement) == 0x14);
