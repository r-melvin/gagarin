// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail RTTI names VectorClass over RGBClass and HSVClass (3-byte elements). HSVClass compares through
// two out-of-line bodies: operator!= at 0x517590 (thiscall) and operator== at 0x5175D0 (fastcall).
#include "vector_class_operations.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

struct RGBClass { unsigned char R; unsigned char G; unsigned char B; RGBClass() : R(0), G(0), B(0) {} bool operator==(const RGBClass& o) const { return R==o.R && G==o.G && B==o.B; } bool operator!=(const RGBClass& o) const { return !(*this==o); } };
// FUNCTION: GAMEMD 0x004782E0
// VectorClass<RGBClass>::operator==
// FUNCTION: GAMEMD 0x00478340
// VectorClass<RGBClass>::SetCapacity
// FUNCTION: GAMEMD 0x00478470
// VectorClass<RGBClass>::FindItemIndex
// FUNCTION: GAMEMD 0x004784C0
// VectorClass<RGBClass>::Slot5
// FUNCTION: GAMEMD 0x00477960
// VectorClass<RGBClass>::Slot6
// FUNCTION: GAMEMD 0x004784F0
// DynamicVectorClass<RGBClass>::SetCapacity
// FUNCTION: GAMEMD 0x004785F0
// DynamicVectorClass<RGBClass>::FindItemIndex
// FUNCTION: GAMEMD 0x00477930
// DynamicVectorClass<RGBClass>::Slot5
// VTABLE: GAMEMD 0x007E4E38 -- VectorClass<RGBClass>.
// VTABLE: GAMEMD 0x007F022C -- DynamicVectorClass<RGBClass>.
template class VectorClass<RGBClass>;
template class DynamicVectorClass<RGBClass>;

struct HSVClass { unsigned char unknown_00; unsigned char unknown_01; unsigned char unknown_02; HSVClass() : unknown_00(0), unknown_01(0), unknown_02(0) {} bool __fastcall operator==(const HSVClass& o) const; bool operator!=(const HSVClass& o) const; };
template class DynamicVectorClass<HSVClass>;

