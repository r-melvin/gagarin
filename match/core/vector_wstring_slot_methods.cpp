// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail RTTI names VectorClass<Wstring> and DynamicVectorClass<Wstring> (4-byte string-handle elements).
// The element copy ctor 0x7B4690 (fastcall), dtor 0x7B46F0, operator== 0x7B4780 and operator!= are out-of-line bodies bound by symbol map.
#include "vector_class_operations.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

struct Wstring { char* unknown_00; Wstring(); Wstring(const Wstring& o); ~Wstring(); bool operator==(const Wstring& o) const; bool operator!=(const Wstring& o) const; };
// FUNCTION: GAMEMD 0x0069D4B0
// VectorClass<Wstring>::scalar deleting destructor
// FUNCTION: GAMEMD 0x0069C970
// VectorClass<Wstring>::operator==
// FUNCTION: GAMEMD 0x0069CB00
// VectorClass<Wstring>::Clear
// FUNCTION: GAMEMD 0x0069CB50
// VectorClass<Wstring>::FindItemIndex
// FUNCTION: GAMEMD 0x0069CBA0
// VectorClass<Wstring>::Slot5
// FUNCTION: GAMEMD 0x0069C580
// VectorClass<Wstring>::Slot6
// FUNCTION: GAMEMD 0x0069D520
// DynamicVectorClass<Wstring>::scalar deleting destructor
// FUNCTION: GAMEMD 0x0069C500
// DynamicVectorClass<Wstring>::Clear
// FUNCTION: GAMEMD 0x0069CD00
// DynamicVectorClass<Wstring>::FindItemIndex
// FUNCTION: GAMEMD 0x0069C560
// DynamicVectorClass<Wstring>::Slot5
template class VectorClass<Wstring>;
template class DynamicVectorClass<Wstring>;

