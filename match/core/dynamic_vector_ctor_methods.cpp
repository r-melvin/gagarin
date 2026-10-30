// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x42F670.

#include "dynamic_vector_ctor_methods.h"
#include "../_layout/cell.h"
#include "vector_class_operations.h"

// FUNCTION: GAMEMD 0x42F670
// DynamicVectorClass<Cell>::DynamicVectorClass(int capacity, Cell* pMem), emitted by the explicit instantiation.
// Construct a growable vector, either over storage the caller supplies or over
// storage of its own. A zero size leaves it empty and allocates nothing; a
// failed allocation still marks the vector as owning its storage, which is what
// the `MOV byte [ESI+0xD],1` after the null path at 0x42F6C6 records.
template class DynamicVectorClass<Cell>;
