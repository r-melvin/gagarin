// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail RTTI TypeDescriptors 0x00823448 and 0x00823478 identify
// VectorClass<TeamClass*> and DynamicVectorClass<TeamClass*>; the dynamic
// hierarchy records the former as its zero-offset base. Full function spans
// and slot arrays were checked against the pinned retail PE. This TU recovers
// the vector specialization only; it does not claim a standalone constructor,
// original TU, or complete TeamClass layout. The derived deleting-dtor full
// span requires /GX off; the base dtor also matches with /GX. The deleting
// wrapper slots rely on conditional weak defaults, not final-link proof.
#include "vector_class_operations.h"

class TeamClass;

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// FUNCTION: GAMEMD 0x004E84D0
// FUNCTION: GAMEMD 0x004E8500
// FUNCTION: GAMEMD 0x004E8520
// FUNCTION: GAMEMD 0x004EA040
// FUNCTION: GAMEMD 0x004EA080
// FUNCTION: GAMEMD 0x004EA130
// FUNCTION: GAMEMD 0x004EA160
// FUNCTION: GAMEMD 0x004EA1A0
// FUNCTION: GAMEMD 0x004EA1C0
// FUNCTION: GAMEMD 0x004EA270
// FUNCTION: GAMEMD 0x004EF8A0
// FUNCTION: GAMEMD 0x004EF8F0
template class VectorClass<TeamClass*>;
template class DynamicVectorClass<TeamClass*>;

// VTABLE: GAMEMD 0x007E9F84 -- VectorClass<TeamClass*>.
// VTABLE: GAMEMD 0x007E9F64 -- DynamicVectorClass<TeamClass*>.

typedef VectorClass<TeamClass*> GgTeamVector;
typedef DynamicVectorClass<TeamClass*> GgTeamDynamicVector;
GG_STATIC_ASSERT(sizeof(TeamClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgTeamVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTeamVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTeamVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTeamVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTeamVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTeamVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgTeamDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgTeamDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgTeamDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgTeamDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgTeamDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgTeamDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgTeamDynamicVector, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgTeamDynamicVector, CapacityIncrement) == 0x14);
