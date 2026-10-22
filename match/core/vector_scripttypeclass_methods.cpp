// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail PAVScriptTypeClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"
class ScriptTypeClass;

// FUNCTION: GAMEMD 0x4E8C00
// DynamicVectorClass<ScriptTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4E8C30
// DynamicVectorClass<ScriptTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4E8C50
// VectorClass<ScriptTypeClass*>::Slot6

// FUNCTION: GAMEMD 0x4ECEE0
// VectorClass<ScriptTypeClass*>::operator==

// FUNCTION: GAMEMD 0x4ECF20
// VectorClass<ScriptTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4ECFD0
// VectorClass<ScriptTypeClass*>::Clear

// FUNCTION: GAMEMD 0x4ED000
// VectorClass<ScriptTypeClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x4ED040
// VectorClass<ScriptTypeClass*>::Slot5

// FUNCTION: GAMEMD 0x4ED060
// DynamicVectorClass<ScriptTypeClass*>::SetCapacity

// FUNCTION: GAMEMD 0x4ED110
// DynamicVectorClass<ScriptTypeClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x4F04D0
// VectorClass<ScriptTypeClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x4F0520
// DynamicVectorClass<ScriptTypeClass*>::scalar deleting destructor

// VTABLE: GAMEMD 0x7EA144 -- VectorClass<ScriptTypeClass*>.
template class VectorClass<ScriptTypeClass*>;
typedef VectorClass<ScriptTypeClass*> GgScriptTypeClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgScriptTypeClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgScriptTypeClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgScriptTypeClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgScriptTypeClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7EA124 -- DynamicVectorClass<ScriptTypeClass*>.
template class DynamicVectorClass<ScriptTypeClass*>;
typedef DynamicVectorClass<ScriptTypeClass*> GgScriptTypeClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgScriptTypeClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgScriptTypeClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgScriptTypeClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgScriptTypeClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgScriptTypeClassDynamicVectorClass, ActiveCount) == 0x10);
GG_STATIC_ASSERT(offsetof(GgScriptTypeClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(ScriptTypeClass*) == 4);
