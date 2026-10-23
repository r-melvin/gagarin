// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Retail RTTI names VectorClass/DynamicVectorClass over unsigned short, bool, double and unsigned char.
// Scalar elements need no element type; the canonical templates are instantiated as-is.
#include "vector_class_operations.h"

// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.


// FUNCTION: GAMEMD 0x0042D8B0
// VectorClass<unsigned short>::operator==
// FUNCTION: GAMEMD 0x0042D8F0
// VectorClass<unsigned short>::SetCapacity
// FUNCTION: GAMEMD 0x0042D9D0
// VectorClass<unsigned short>::FindItemIndex
// FUNCTION: GAMEMD 0x0042DA10
// VectorClass<unsigned short>::Slot5
// FUNCTION: GAMEMD 0x0042D5F0
// VectorClass<unsigned short>::Slot6
// FUNCTION: GAMEMD 0x0042DA30
// DynamicVectorClass<unsigned short>::SetCapacity
// FUNCTION: GAMEMD 0x0042DAE0
// DynamicVectorClass<unsigned short>::FindItemIndex
// FUNCTION: GAMEMD 0x0042D5D0
// DynamicVectorClass<unsigned short>::Slot5
// VTABLE: GAMEMD 0x007E3824 -- VectorClass<unsigned short>.
// VTABLE: GAMEMD 0x007E3844 -- DynamicVectorClass<unsigned short>.
template class VectorClass<unsigned short>;
template class DynamicVectorClass<unsigned short>;


template class DynamicVectorClass<bool>;


template class DynamicVectorClass<double>;


// FUNCTION: GAMEMD 0x0074BFF0
// VectorClass<unsigned char>::operator==
// FUNCTION: GAMEMD 0x0074C030
// VectorClass<unsigned char>::SetCapacity
// FUNCTION: GAMEMD 0x0074C110
// VectorClass<unsigned char>::FindItemIndex
// FUNCTION: GAMEMD 0x0074C150
// VectorClass<unsigned char>::Slot5
// FUNCTION: GAMEMD 0x0074BF90
// VectorClass<unsigned char>::Slot6
// VTABLE: GAMEMD 0x007F65F4 -- VectorClass<unsigned char>.
template class VectorClass<unsigned char>;

