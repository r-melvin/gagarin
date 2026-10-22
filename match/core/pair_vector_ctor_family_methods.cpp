// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Four instances of the VectorClass<T>(int, T*) capacity constructor over an
// eight-byte element. Ordered ascending by retail address.

#include "pair_vector_ctor_family_methods.h"

// FUNCTION: GAMEMD 0x005106E0
template class VectorClass<AngerStruct>;

// FUNCTION: GAMEMD 0x00510780
template class VectorClass<ScoutStruct>;

// FUNCTION: GAMEMD 0x0058AC70
template class VectorClass<SubzoneConnectionStruct>;

// FUNCTION: GAMEMD 0x006CF8F0
template class VectorClass<SwizzlePointerClass>;
