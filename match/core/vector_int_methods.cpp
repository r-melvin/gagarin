// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Raw RTTI at 0x81C038/0x81C058 identifies the int base/dynamic templates.
// Entry-origin span 0x4779E0..0x477A68 proves this copy constructor and all
// touched offsets, asserted in vector_class_layout_asserts.cpp. Other emitted
// template specializations remain unclaimed until separately verified.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
#include "vector_class_operations.h"

// FUNCTION: GAMEMD 0x477840
// DynamicVectorClass<int>::Clear

// FUNCTION: GAMEMD 0x477870
// DynamicVectorClass<int>::Slot5

// FUNCTION: GAMEMD 0x477890
// VectorClass<int>::Slot6

// FUNCTION: GAMEMD 0x4779E0
// DynamicVectorClass<int> copy constructor

// SYNTHETIC: GAMEMD 0x477B10
// DynamicVectorClass<int> scalar deleting destructor

// FUNCTION: GAMEMD 0x477BE0
// VectorClass<int> capacity constructor

// FUNCTION: GAMEMD 0x477C30
// VectorClass<int>::operator==

// FUNCTION: GAMEMD 0x477C70
// VectorClass<int>::SetCapacity

// FUNCTION: GAMEMD 0x477D20
// VectorClass<int>::Clear

// FUNCTION: GAMEMD 0x477D50
// VectorClass<int>::FindItemIndex

// FUNCTION: GAMEMD 0x477D90
// VectorClass<int>::Slot5

// FUNCTION: GAMEMD 0x477DB0
// DynamicVectorClass<int> capacity constructor

// FUNCTION: GAMEMD 0x477E10
// DynamicVectorClass<int>::SetCapacity

// FUNCTION: GAMEMD 0x477F10
// DynamicVectorClass<int>::FindItemIndex

// SYNTHETIC: GAMEMD 0x478630
// VectorClass<int> scalar deleting destructor

template class VectorClass<int>;
template class DynamicVectorClass<int>;
