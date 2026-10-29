// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Retail RTTI names VectorClass/DynamicVectorClass over the 8-byte pair structs, HashObject<K,V> and
// AcceleratorTracker/UndoInfoStruct. Only slots that reproduce retail bytes are claimed.
#include "vector_class_operations.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

#include "pair_vector_ctor_family_methods.h"

template class DynamicVectorClass<ScoutStruct>;

#include "pair_vector_ctor_family_methods.h"

template class DynamicVectorClass<AngerStruct>;

#include "pair_vector_ctor_family_methods.h"

// FUNCTION: GAMEMD 0x006CF720
// DynamicVectorClass<SwizzlePointerClass>::SetCapacity
// FUNCTION: GAMEMD 0x006CF820
// DynamicVectorClass<SwizzlePointerClass>::FindItemIndex
// VTABLE: GAMEMD 0x007F4154 -- VectorClass<SwizzlePointerClass>.
// VTABLE: GAMEMD 0x007F4134 -- DynamicVectorClass<SwizzlePointerClass>.
template class VectorClass<SwizzlePointerClass>;
template class DynamicVectorClass<SwizzlePointerClass>;

template<class K,class V> struct HashObject { K Key; V Value; HashObject() {} HashObject(const HashObject<K,V>& o) : Key(o.Key), Value(o.Value) {} bool operator==(const HashObject<K,V>& o) const { return Key==o.Key; } bool operator!=(const HashObject<K,V>& o) const { return !(*this==o); } };
// FUNCTION: GAMEMD 0x0058A6E0
// VectorClass<HashObject<unsigned int, unsigned int>>::SetCapacity
// FUNCTION: GAMEMD 0x0058A7E0
// VectorClass<HashObject<unsigned int, unsigned int>>::FindItemIndex
// FUNCTION: GAMEMD 0x0058A820
// VectorClass<HashObject<unsigned int, unsigned int>>::Slot5
// FUNCTION: GAMEMD 0x0058A150
// DynamicVectorClass<HashObject<unsigned int, unsigned int>>::SetCapacity
// VTABLE: GAMEMD 0x007ED5C0 -- VectorClass<HashObject<unsigned int, unsigned int>>.
template class VectorClass<HashObject<unsigned int,unsigned int> >;
template class DynamicVectorClass<HashObject<unsigned int,unsigned int> >;

#include "pair_vector_ctor_family_methods.h"

// FUNCTION: GAMEMD 0x0058A8F0
// VectorClass<HashObject<unsigned int, SubzoneConnectionStruct>>::SetCapacity
// FUNCTION: GAMEMD 0x0058AA20
// VectorClass<HashObject<unsigned int, SubzoneConnectionStruct>>::FindItemIndex
// FUNCTION: GAMEMD 0x0058AA60
// VectorClass<HashObject<unsigned int, SubzoneConnectionStruct>>::Slot5
// FUNCTION: GAMEMD 0x0058A2A0
// DynamicVectorClass<HashObject<unsigned int, SubzoneConnectionStruct>>::SetCapacity
// VTABLE: GAMEMD 0x007ED5E0 -- VectorClass<HashObject<unsigned int, SubzoneConnectionStruct>>.
template class VectorClass<HashObject<unsigned int,SubzoneConnectionStruct> >;
template class DynamicVectorClass<HashObject<unsigned int,SubzoneConnectionStruct> >;

struct RadarTrackingStruct { int unknown_00; int unknown_04; int unknown_08; RadarTrackingStruct() {} RadarTrackingStruct(const RadarTrackingStruct& o) : unknown_00(o.unknown_00), unknown_04(o.unknown_04), unknown_08(o.unknown_08) {} bool operator==(const RadarTrackingStruct& o) const { return unknown_00==o.unknown_00 && unknown_04==o.unknown_04 && unknown_08==o.unknown_08; } bool operator!=(const RadarTrackingStruct& o) const { return !(*this==o); } }; class TechnoClass; 
template class DynamicVectorClass<HashObject<RadarTrackingStruct,TechnoClass*> >;

struct AcceleratorTracker { int A; int B; AcceleratorTracker() : A(0), B(0) {} bool operator==(const AcceleratorTracker& o) const { return A==o.A && B==o.B; } bool operator!=(const AcceleratorTracker& o) const { return !(*this==o); } };
// FUNCTION: GAMEMD 0x005D53B0
// VectorClass<AcceleratorTracker>::operator==
// FUNCTION: GAMEMD 0x005D5410
// VectorClass<AcceleratorTracker>::SetCapacity
// FUNCTION: GAMEMD 0x005D5530
// VectorClass<AcceleratorTracker>::FindItemIndex
// FUNCTION: GAMEMD 0x005D5580
// VectorClass<AcceleratorTracker>::Slot5
// FUNCTION: GAMEMD 0x005D5130
// VectorClass<AcceleratorTracker>::Slot6
// FUNCTION: GAMEMD 0x005D55A0
// DynamicVectorClass<AcceleratorTracker>::SetCapacity
// FUNCTION: GAMEMD 0x005D56A0
// DynamicVectorClass<AcceleratorTracker>::FindItemIndex
// FUNCTION: GAMEMD 0x005D5110
// DynamicVectorClass<AcceleratorTracker>::Slot5
// VTABLE: GAMEMD 0x007EECEC -- VectorClass<AcceleratorTracker>.
// VTABLE: GAMEMD 0x007EECCC -- DynamicVectorClass<AcceleratorTracker>.
template class VectorClass<AcceleratorTracker>;
template class DynamicVectorClass<AcceleratorTracker>;

#include "undo_info_struct.h"
// FUNCTION: GAMEMD 0x006B4440
// VectorClass<UndoInfoStruct>::operator==
// FUNCTION: GAMEMD 0x006B45D0
// VectorClass<UndoInfoStruct>::FindItemIndex
// FUNCTION: GAMEMD 0x006B4620
// VectorClass<UndoInfoStruct>::Slot5
// FUNCTION: GAMEMD 0x006B4410
// VectorClass<UndoInfoStruct>::Slot6
// FUNCTION: GAMEMD 0x006B4760
// DynamicVectorClass<UndoInfoStruct>::FindItemIndex
// FUNCTION: GAMEMD 0x006B43E0
// DynamicVectorClass<UndoInfoStruct>::Slot5
template class VectorClass<UndoInfoStruct>;
template class DynamicVectorClass<UndoInfoStruct>;

