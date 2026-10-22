// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Paired flag probes: /GX shortens the dynamic deleting entry to 0x20
// bytes; no-GX matches its full 0x49-byte span. Other 11 bodies match both.
// Retail RTTI TypeDescriptors 0x008368F8 and 0x00836930 identify
// VectorClass<PlanningNodeClass*> and DynamicVectorClass<PlanningNodeClass*>;
// COLs 0x00807F08 and 0x00807ED8 point at them, and the dynamic hierarchy (CHD
// 0x00807EC8, two base classes) records the vector as its zero-offset base.
// VectorClass<T> address point 0x007EFE64 and DynamicVectorClass<T> address
// point 0x007EFE44 are each seven-slot tables whose COL is at address-4.
// Complete function spans (control-flow closure from each entry, not the
// first RET) were checked against the pinned retail PE. This TU recovers the
// vector specialization only; it makes no constructor, original-TU, or
// complete PlanningNodeClass layout claim.
#include "vector_class_operations.h"

class PlanningNodeClass;

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete(void*), ??3@YAXPAX@Z.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

// FUNCTION: GAMEMD 0x0063DC20
// FUNCTION: GAMEMD 0x0063DC50
// FUNCTION: GAMEMD 0x0063DC70
// FUNCTION: GAMEMD 0x0063E310
// FUNCTION: GAMEMD 0x0063E350
// FUNCTION: GAMEMD 0x0063E400
// FUNCTION: GAMEMD 0x0063E430
// FUNCTION: GAMEMD 0x0063E470
// FUNCTION: GAMEMD 0x0063E490
// FUNCTION: GAMEMD 0x0063E620
// FUNCTION: GAMEMD 0x0063ED90
// FUNCTION: GAMEMD 0x0063EDE0
template class VectorClass<PlanningNodeClass*>;
template class DynamicVectorClass<PlanningNodeClass*>;

// VTABLE: GAMEMD 0x007EFE64 -- VectorClass<PlanningNodeClass*>.
// VTABLE: GAMEMD 0x007EFE44 -- DynamicVectorClass<PlanningNodeClass*>.

typedef VectorClass<PlanningNodeClass*> GgPlanningNodeClassVector;
typedef DynamicVectorClass<PlanningNodeClass*> GgPlanningNodeClassDynamicVector;
GG_STATIC_ASSERT(sizeof(PlanningNodeClass*) == 4);
GG_STATIC_ASSERT(sizeof(GgPlanningNodeClassVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgPlanningNodeClassVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgPlanningNodeClassVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgPlanningNodeClassVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgPlanningNodeClassVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgPlanningNodeClassVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgPlanningNodeClassDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgPlanningNodeClassDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgPlanningNodeClassDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgPlanningNodeClassDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgPlanningNodeClassDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgPlanningNodeClassDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgPlanningNodeClassDynamicVector, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgPlanningNodeClassDynamicVector, CapacityIncrement) == 0x14);
