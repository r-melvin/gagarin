// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Slot 5 of the retail DynamicVectorClass<AngerStruct>, <ScoutStruct> and
// <SwizzlePointerClass> vtables (owners read from retail RTTI). The bodies
// divide the byte offset by 8 (shr 3), agreeing with the eight-byte element
// asserts in the canonical pair-vector header. VC6 emits nothing for an
// explicit member instantiation, so the dynamic class is instantiated whole;
// only slot 5 is claimed here.
#include "pair_vector_ctor_family_methods.h"

// TEMPLATE: GAMEMD 0x50E590
// DynamicVectorClass<AngerStruct>::Slot5 (slot 5)
template class DynamicVectorClass<AngerStruct>;
// TEMPLATE: GAMEMD 0x50E600
// DynamicVectorClass<ScoutStruct>::Slot5 (slot 5)
template class DynamicVectorClass<ScoutStruct>;
// TEMPLATE: GAMEMD 0x6CF520
// DynamicVectorClass<SwizzlePointerClass>::Slot5 (slot 5)
template class DynamicVectorClass<SwizzlePointerClass>;
