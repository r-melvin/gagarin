// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Constructors that seat their object's first word and return `this`.
// Ten remaining instantiations across three sub-shapes; within a sub-shape every
// byte outside the vtable constant is identical, so each body is written once
// as a macro and expanded per instantiation. Ordered ascending by retail
// address.

#include "vtable_seating_ctor_family_methods.h"
#include "vector_class_operations.h"
#include "type_list.h"
#include "vector_cursor.h"

class AnimTypeClass;
class BuildingTypeClass;
class VoxelAnimTypeClass;
class MSSfxEntry;
template <class T> class rc_ptr;
namespace WorldDominationTour {
class Territory;
}

// FUNCTION: GAMEMD 0x006406E0
GG_SEATNULL_BODY(006406E0)

// FUNCTION: GAMEMD 0x00717BC0
// DynamicVectorClass<VoxelAnimTypeClass const*>::DynamicVectorClass(const AbstractNoInit&), emitted by the explicit instantiation.
template class DynamicVectorClass<VoxelAnimTypeClass const*>;

// FUNCTION: GAMEMD 0x00717BD0
// DynamicVectorClass<int>::DynamicVectorClass(const AbstractNoInit&), emitted by the explicit instantiation.
template class DynamicVectorClass<int>;

// FUNCTION: GAMEMD 0x00717BE0
// DynamicVectorClass<BuildingTypeClass const*>::DynamicVectorClass(const AbstractNoInit&), emitted by the explicit instantiation.
template class DynamicVectorClass<BuildingTypeClass const*>;

// FUNCTION: GAMEMD 0x00717BF0
// DynamicVectorClass<AnimTypeClass const*>::DynamicVectorClass(const AbstractNoInit&), emitted by the explicit instantiation.
template class DynamicVectorClass<AnimTypeClass const*>;

// FUNCTION: GAMEMD 0x0074FF30
GG_SEATNULL_BODY(0074FF30)

// FUNCTION: GAMEMD 0x0075E690
// TypeList<VoxelAnimTypeClass const*>::TypeList(const AbstractNoInit&), emitted by the explicit instantiation.
template class TypeList<VoxelAnimTypeClass const*>;

// FUNCTION: GAMEMD 0x0075E6A0
// TypeList<int>::TypeList(const AbstractNoInit&), emitted by the explicit instantiation.
template class TypeList<int>;

// FUNCTION: GAMEMD 0x0076F090
// VectorCursor<MSSfxEntry*, DynamicVectorClass<MSSfxEntry*>>::VectorCursor(vector, index), emitted by the explicit instantiation.
template class VectorCursor<MSSfxEntry*, DynamicVectorClass<MSSfxEntry*> >;

// FUNCTION: GAMEMD 0x0076F0C0
// VectorCursor<rc_ptr<Territory>, DynamicVectorClass<rc_ptr<Territory>>>::VectorCursor(vector, index), emitted by the explicit instantiation.
template class VectorCursor<rc_ptr<WorldDominationTour::Territory>, DynamicVectorClass<rc_ptr<WorldDominationTour::Territory> > >;

typedef VectorCursor<MSSfxEntry*, DynamicVectorClass<MSSfxEntry*> > MSSfxEntryCursor;
GG_STATIC_ASSERT(offsetof(MSSfxEntryCursor, unknown_04) == 0x4 &&
                 offsetof(MSSfxEntryCursor, unknown_08) == 0x8 &&
                 sizeof(MSSfxEntryCursor) == 0xC);
