// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// RTTI at tables 0x7ED92C/0x7ED94C identifies the find-data pointer vector.
// Its base constructor is the out-of-line 0x5AD9F0 body called by 0x595CEF.
#ifndef GG_MATCH_CORE_VECTOR_FIND_DATA_H
#define GG_MATCH_CORE_VECTOR_FIND_DATA_H
#include <windows.h>
#include "vector_class.h"

// FUNCTION: GAMEMD 0x5AD9F0 (declaration)
template<> VectorClass<WIN32_FIND_DATAA*>::VectorClass(int capacity,
    WIN32_FIND_DATAA** pMem);
#endif
