// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x41C500.

#include "pair_vector_resize_methods.h"

// FUNCTION: GAMEMD 0x41C500
//
// The out-of-line copy of IndexClass<int, AbstractClass*>::IncreaseTableSize (see _layout/index.h): allocate the
// grown node array, copy the live nodes across, free the old array and invalidate the cached lookup node. A
// negative request and a failed allocation both report false without touching anything. The five Load bodies
// call this copy where the constructors expand the same body inline.
template<>
bool IndexClass<int, AbstractClass*>::FUN_0041C500(int amount)
{
    return IncreaseTableSize(amount);
}
