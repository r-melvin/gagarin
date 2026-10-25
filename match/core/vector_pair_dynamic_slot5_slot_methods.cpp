// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Slot 5 of the retail DynamicVectorClass<AngerStruct>, <ScoutStruct> and
// <SwizzlePointerClass> vtables (owners read from retail RTTI). The bodies
// divide the byte offset by 8 (shr 3), agreeing with the eight-byte element
// asserts in the canonical pair-vector header. VC6 emits nothing for an
// explicit member instantiation, so the dynamic class is instantiated whole;
// Slot 5 and the actual dynamic scalar deleting destructor are claimed here.
#include "pair_vector_ctor_family_methods.h"

// Retail vtable 0x7F4134 belongs to DynamicVectorClass<SwizzlePointerClass>.
// TEMPLATE: GAMEMD 0x6CF520
// DynamicVectorClass<SwizzlePointerClass>::Slot5 (slot 5)
// SYNTHETIC: GAMEMD 0x6CF8A0 -- actual slot 0 of 0x7F4134.
// The wrapper expands base destruction and stores the base vptr 0x7F4154.
template class DynamicVectorClass<SwizzlePointerClass>;
