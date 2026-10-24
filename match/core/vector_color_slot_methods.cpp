// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Retail RTTI names VectorClass over RGBClass and HSVClass (3-byte elements). HSVClass compares through
// two out-of-line bodies: operator!= at 0x517590 (thiscall) and operator== at 0x5175D0 (fastcall).
#include "vector_class_operations.h"
#include "type_list.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

#include "../_layout/rgb_class.h"
// FUNCTION: GAMEMD 0x00477900
// DynamicVectorClass<RGBClass>::Clear
// FUNCTION: GAMEMD 0x00477930
// DynamicVectorClass<RGBClass>::Slot5
// FUNCTION: GAMEMD 0x00477960
// VectorClass<RGBClass>::Slot6
// FUNCTION: GAMEMD 0x00477AC0
// TypeList<RGBClass> scalar deleting destructor
// FUNCTION: GAMEMD 0x004782E0
// VectorClass<RGBClass>::operator==
// FUNCTION: GAMEMD 0x00478340
// VectorClass<RGBClass>::SetCapacity
// FUNCTION: GAMEMD 0x00478440
// VectorClass<RGBClass>::Clear
// FUNCTION: GAMEMD 0x00478470
// VectorClass<RGBClass>::FindItemIndex
// FUNCTION: GAMEMD 0x004784C0
// VectorClass<RGBClass>::Slot5
// FUNCTION: GAMEMD 0x004784F0
// DynamicVectorClass<RGBClass>::SetCapacity
// FUNCTION: GAMEMD 0x004785F0
// DynamicVectorClass<RGBClass>::FindItemIndex
// FUNCTION: GAMEMD 0x004786D0
// VectorClass<RGBClass> scalar deleting destructor
// FUNCTION: GAMEMD 0x00478850
// VectorClass<RGBClass>::VectorClass
// FUNCTION: GAMEMD 0x00645A70
// DynamicVectorClass<RGBClass>::DynamicVectorClass
// FUNCTION: GAMEMD 0x00645B10
// DynamicVectorClass<RGBClass> scalar deleting destructor
// VTABLE: GAMEMD 0x007E4E38 -- VectorClass<RGBClass>, seven slots.
// VTABLE: GAMEMD 0x007E4E58 -- TypeList<RGBClass>, seven slots.
// VTABLE: GAMEMD 0x007F022C -- DynamicVectorClass<RGBClass>, seven slots.
template class VectorClass<RGBClass>;
template class DynamicVectorClass<RGBClass>;
template class TypeList<RGBClass>;
typedef TypeList<RGBClass> GgTypeListRGB;
// Native 0x476B20 consumes a 0x1C-byte by-value default (RET 0x28,
// hidden result plus section/key); the object starts at entry ESP+0x10.
GG_STATIC_ASSERT(sizeof(GgTypeListRGB) == 0x1C);
GG_STATIC_ASSERT(offsetof(GgTypeListRGB, unknown_18) == 0x18);

struct HSVClass { unsigned char unknown_00; unsigned char unknown_01; unsigned char unknown_02; HSVClass() : unknown_00(0), unknown_01(0), unknown_02(0) {} bool __fastcall operator==(const HSVClass& o) const; bool operator!=(const HSVClass& o) const; };
template class DynamicVectorClass<HSVClass>;

