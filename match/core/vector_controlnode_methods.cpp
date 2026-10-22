// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAUControlNode RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

#include "../_layout/control_node.h"

// FUNCTION: GAMEMD 0x472A80
// DynamicVectorClass<ControlNode*>::Clear

// FUNCTION: GAMEMD 0x472AB0
// DynamicVectorClass<ControlNode*>::Slot5

// FUNCTION: GAMEMD 0x472AD0
// VectorClass<ControlNode*>::Slot6

// FUNCTION: GAMEMD 0x472B40
// VectorClass<ControlNode*>::operator==

// FUNCTION: GAMEMD 0x472B80
// VectorClass<ControlNode*>::SetCapacity

// FUNCTION: GAMEMD 0x472C30
// VectorClass<ControlNode*>::Clear

// FUNCTION: GAMEMD 0x472C60
// VectorClass<ControlNode*>::FindItemIndex

// FUNCTION: GAMEMD 0x472CA0
// VectorClass<ControlNode*>::Slot5

// FUNCTION: GAMEMD 0x472CC0
// DynamicVectorClass<ControlNode*>::SetCapacity

// FUNCTION: GAMEMD 0x472D70
// DynamicVectorClass<ControlNode*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x473000
// VectorClass<ControlNode*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x473050
// DynamicVectorClass<ControlNode*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7E4BC4 -- VectorClass<ControlNode*>.
template class VectorClass<ControlNode*>;
typedef VectorClass<ControlNode*> GgControlnodeVectorClass;
GG_STATIC_ASSERT(offsetof(GgControlnodeVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgControlnodeVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgControlnodeVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgControlnodeVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7E4BA4 -- DynamicVectorClass<ControlNode*>.
template class DynamicVectorClass<ControlNode*>;
typedef DynamicVectorClass<ControlNode*> GgControlnodeDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgControlnodeDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgControlnodeDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgControlnodeDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgControlnodeDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgControlnodeDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgControlnodeDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(ControlNode*) == 4);
