// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Paired flag probes: /GX shortens the dynamic deleting entry to 0x20
// bytes; no-GX matches its full 0x49-byte span. Other 11 bodies match both.
// Retail RTTI TypeDescriptors 0x00830830 and 0x00830868 identify
// VectorClass<MultiplayerTeam*> and DynamicVectorClass<MultiplayerTeam*>; COLs
// 0x00807020 and 0x00806FF0 point at them, and the dynamic hierarchy (CHD
// 0x00806FE0, two base classes, base array 0x00806FD0) records the vector as
// its zero-offset base.
// VectorClass<T> address point 0x007EEE54 and DynamicVectorClass<T> address
// point 0x007EEE34 are each seven-slot tables whose COL is at address-4.
// Complete function spans (control-flow closure from each entry, not the
// first RET) were checked against the pinned retail PE. This TU recovers the
// vector specialization only; it makes no constructor, original-TU, or
// complete MultiplayerTeam layout claim.
#include "vector_class_operations.h"

class MultiplayerTeam;

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete(void*), ??3@YAXPAX@Z.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// FUNCTION: GAMEMD 0x005D80B0
// FUNCTION: GAMEMD 0x005D80E0
// FUNCTION: GAMEMD 0x005D8100
// FUNCTION: GAMEMD 0x005D82F0
// FUNCTION: GAMEMD 0x005D8330
// FUNCTION: GAMEMD 0x005D83E0
// FUNCTION: GAMEMD 0x005D8410
// FUNCTION: GAMEMD 0x005D8450
// FUNCTION: GAMEMD 0x005D8470
// FUNCTION: GAMEMD 0x005D8520
// FUNCTION: GAMEMD 0x005D8810
// FUNCTION: GAMEMD 0x005D8860
template class VectorClass<MultiplayerTeam*>;
template class DynamicVectorClass<MultiplayerTeam*>;

// VTABLE: GAMEMD 0x007EEE54 -- VectorClass<MultiplayerTeam*>.
// VTABLE: GAMEMD 0x007EEE34 -- DynamicVectorClass<MultiplayerTeam*>.

typedef VectorClass<MultiplayerTeam*> GgMultiplayerTeamVector;
typedef DynamicVectorClass<MultiplayerTeam*> GgMultiplayerTeamDynamicVector;
GG_STATIC_ASSERT(sizeof(MultiplayerTeam*) == 4);
GG_STATIC_ASSERT(sizeof(GgMultiplayerTeamVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMultiplayerTeamVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMultiplayerTeamVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMultiplayerTeamVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMultiplayerTeamVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMultiplayerTeamVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgMultiplayerTeamDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgMultiplayerTeamDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMultiplayerTeamDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMultiplayerTeamDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMultiplayerTeamDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMultiplayerTeamDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgMultiplayerTeamDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMultiplayerTeamDynamicVector, CapacityIncrement) == 0x14);
