// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// VectorClass<T> over four eight-byte elements, and
// DynamicVectorClass<SubzoneConnectionStruct>. Each address is a slot target
// of the retail vtable named with it: VectorClass<AngerStruct> 0x7EA984,
// VectorClass<ScoutStruct> 0x7EA9A4, VectorClass<SubzoneConnectionStruct>
// 0x7E177C, VectorClass<SwizzlePointerClass> 0x7F4154 and
// DynamicVectorClass<SubzoneConnectionStruct> 0x7ED5A0, each named by the
// RTTI locator four bytes below it. The markers are listed in ascending
// retail address order; the explicit instantiations that emit them follow.
//
// Flags: without /GX. Under /GX cl calls the base SetCapacity and destructor
// out of line from DynamicVectorClass<SubzoneConnectionStruct>'s SetCapacity
// and deleting destructor, where retail 0x589190 and 0x5890B0 inline both, and
// the four VectorClass<T>::SetCapacity bodies fall to about 19%. The
// constructors, operator==, FindItemIndex, Slot5 and Slot6 match either way.

#include "pair_vector_ctor_family_methods.h"

// FUNCTION: GAMEMD 0x0040B120
// VectorClass<SubzoneConnectionStruct>::Slot6 (slot 6 of 0x7E177C and 0x7ED5A0)
// FUNCTION: GAMEMD 0x0040B140
// VectorClass<SubzoneConnectionStruct>::operator== (slot 1 of 0x7E177C and 0x7ED5A0)
// FUNCTION: GAMEMD 0x0040B180
// VectorClass<SubzoneConnectionStruct>::SetCapacity (slot 2)
// FUNCTION: GAMEMD 0x0040B2A0
// VectorClass<SubzoneConnectionStruct>::FindItemIndex (slot 4)
// FUNCTION: GAMEMD 0x0040B2E0
// VectorClass<SubzoneConnectionStruct>::Slot5 (slot 5)
// FUNCTION: GAMEMD 0x0050E5B0
// VectorClass<AngerStruct>::Slot6 (slot 6)
// FUNCTION: GAMEMD 0x0050E620
// VectorClass<ScoutStruct>::Slot6 (slot 6)
// FUNCTION: GAMEMD 0x0050EE80
// VectorClass<AngerStruct>::operator== (slot 1)
// FUNCTION: GAMEMD 0x0050EEE0
// VectorClass<AngerStruct>::SetCapacity (slot 2)
// FUNCTION: GAMEMD 0x0050F000
// VectorClass<AngerStruct>::FindItemIndex (slot 4)
// FUNCTION: GAMEMD 0x0050F050
// VectorClass<AngerStruct>::Slot5 (slot 5)
// FUNCTION: GAMEMD 0x0050F1B0
// VectorClass<ScoutStruct>::operator== (slot 1)
// FUNCTION: GAMEMD 0x0050F210
// VectorClass<ScoutStruct>::SetCapacity (slot 2)
// FUNCTION: GAMEMD 0x0050F330
// VectorClass<ScoutStruct>::FindItemIndex (slot 4)
// FUNCTION: GAMEMD 0x0050F380
// VectorClass<ScoutStruct>::Slot5 (slot 5)
// FUNCTION: GAMEMD 0x005106E0
// VectorClass<AngerStruct>::VectorClass(int, AngerStruct*)
// FUNCTION: GAMEMD 0x00510780
// VectorClass<ScoutStruct>::VectorClass(int, ScoutStruct*)
// FUNCTION: GAMEMD 0x00588CC0
// DynamicVectorClass<SubzoneConnectionStruct>::Slot5 (slot 5 of 0x7ED5A0)
// FUNCTION: GAMEMD 0x005890B0
// DynamicVectorClass<SubzoneConnectionStruct>::`scalar deleting destructor' (slot 0 of 0x7ED5A0)
// FUNCTION: GAMEMD 0x00589190
// DynamicVectorClass<SubzoneConnectionStruct>::SetCapacity (slot 2 of 0x7ED5A0)
// FUNCTION: GAMEMD 0x005892D0
// DynamicVectorClass<SubzoneConnectionStruct>::FindItemIndex (slot 4 of 0x7ED5A0)
// FUNCTION: GAMEMD 0x0058AC70
// VectorClass<SubzoneConnectionStruct>::VectorClass(int, SubzoneConnectionStruct*)
// FUNCTION: GAMEMD 0x006CF540
// VectorClass<SwizzlePointerClass>::Slot6 (slot 6)
// FUNCTION: GAMEMD 0x006CF560
// VectorClass<SwizzlePointerClass>::operator== (slot 1)
// FUNCTION: GAMEMD 0x006CF5A0
// VectorClass<SwizzlePointerClass>::SetCapacity (slot 2)
// FUNCTION: GAMEMD 0x006CF6C0
// VectorClass<SwizzlePointerClass>::FindItemIndex (slot 4)
// FUNCTION: GAMEMD 0x006CF700
// VectorClass<SwizzlePointerClass>::Slot5 (slot 5)
// SYNTHETIC: GAMEMD 0x006CF850
// VectorClass<SwizzlePointerClass>::scalar deleting destructor (slot 0).
// FUNCTION: GAMEMD 0x006CF8F0
// VectorClass<SwizzlePointerClass>::VectorClass(int, SwizzlePointerClass*)

// VTABLE: GAMEMD 0x007EA984 -- VectorClass<AngerStruct>.
template class VectorClass<AngerStruct>;
// VTABLE: GAMEMD 0x007EA9A4 -- VectorClass<ScoutStruct>.
template class VectorClass<ScoutStruct>;
// VTABLE: GAMEMD 0x007E177C -- VectorClass<SubzoneConnectionStruct>.
template class VectorClass<SubzoneConnectionStruct>;
// VTABLE: GAMEMD 0x007ED5A0 -- DynamicVectorClass<SubzoneConnectionStruct>.
template class DynamicVectorClass<SubzoneConnectionStruct>;
// VTABLE: GAMEMD 0x007F4154 -- VectorClass<SwizzlePointerClass>.
template class VectorClass<SwizzlePointerClass>;
