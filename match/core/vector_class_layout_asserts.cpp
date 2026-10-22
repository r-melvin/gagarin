// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
// Use the ToolTip cluster flags for the instantiations forced by this ledger;
// /GX otherwise emits a different derived deleting-destructor COMDAT.
// Compile the actual shared-template member/size assertions. VC6 requires
// explicit instantiation before offsetof; the header itself forces none.
// Offsets follow entry-origin instructions at 0x477D20, 0x477840,
// 0x724000, 0x724C30 and 0x724D80; vtable slot order follows raw tables.
#include "vector_class.h"
#include "../_rt/gg_static_assert.h"
class ToolTip;
template class VectorClass<int>;
template class DynamicVectorClass<int>;
template class VectorClass<const ToolTip*>;
template class DynamicVectorClass<const ToolTip*>;
typedef VectorClass<int> GgVectorInt;
typedef DynamicVectorClass<int> GgDynamicVectorInt;
typedef VectorClass<const ToolTip*> GgVectorToolTipPointer;
typedef DynamicVectorClass<const ToolTip*> GgDynamicVectorToolTipPointer;
GG_STATIC_ASSERT(offsetof(GgVectorInt, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVectorInt, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVectorInt, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVectorInt, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgVectorInt, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgVectorInt) == 0x10);
GG_STATIC_ASSERT(offsetof(GgDynamicVectorInt, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgDynamicVectorInt, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgDynamicVectorInt, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgDynamicVectorInt, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgDynamicVectorInt, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgDynamicVectorInt, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(GgDynamicVectorInt) == 0x18);
GG_STATIC_ASSERT(offsetof(GgVectorToolTipPointer, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgVectorToolTipPointer, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgVectorToolTipPointer, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgVectorToolTipPointer, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgVectorToolTipPointer, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(sizeof(GgVectorToolTipPointer) == 0x10);
GG_STATIC_ASSERT(offsetof(GgDynamicVectorToolTipPointer, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgDynamicVectorToolTipPointer, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgDynamicVectorToolTipPointer, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgDynamicVectorToolTipPointer, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgDynamicVectorToolTipPointer, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgDynamicVectorToolTipPointer, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgDynamicVectorToolTipPointer, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(GgDynamicVectorToolTipPointer) == 0x18);

struct VectorClassSevenSlotLayoutEvidence {
    void* Slot0; void* Slot1; void* Slot2; void* ClearSlot3;
    void* Slot4; void* Slot5; void* Slot6;
};
GG_STATIC_ASSERT(offsetof(VectorClassSevenSlotLayoutEvidence, ClearSlot3) == 0x0C);
GG_STATIC_ASSERT(sizeof(VectorClassSevenSlotLayoutEvidence) == 0x1C);

struct VectorClassVtableLayout {
    void* Destructor; void* Equals; void* SetCapacity; void* Clear;
    void* FindItemIndex; void* Slot5; void* Slot6;
};
GG_STATIC_ASSERT(offsetof(VectorClassVtableLayout, Destructor) == 0x00);
GG_STATIC_ASSERT(offsetof(VectorClassVtableLayout, Equals) == 0x04);
GG_STATIC_ASSERT(offsetof(VectorClassVtableLayout, SetCapacity) == 0x08);
GG_STATIC_ASSERT(offsetof(VectorClassVtableLayout, Clear) == 0x0C);
GG_STATIC_ASSERT(offsetof(VectorClassVtableLayout, FindItemIndex) == 0x10);
GG_STATIC_ASSERT(offsetof(VectorClassVtableLayout, Slot5) == 0x14);
GG_STATIC_ASSERT(offsetof(VectorClassVtableLayout, Slot6) == 0x18);
GG_STATIC_ASSERT(sizeof(VectorClassVtableLayout) == 0x1C);
