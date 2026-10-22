// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Dynamic-vector resize, two remaining instances, ordered ascending by retail address and
// written out longhand per the family rule.
//
// The two remaining bodies are matched, like the address-scoped instances in
// match/core/vector_resize_family_methods.cpp. The two levers that took the
// shape from 68.5% to 100% are written up there in full: the retail body is
// DynamicVectorClass::Resize with VectorClass::Resize inlined into it, so
// spelling it as the two nested functions puts the `return false` epilogue
// last where retail has it; and the ownership flag needs the RA1 spelling
// `IsAllocated = (Vector != 0 && array == 0)`, whose redundant leading
// short-circuit term is what splits retail's XOR/TEST/SETZ idiom across the
// two pointer stores. The shared inner half lives in VectorBase::ResizeBase
// in vector_resize_methods.h; each function below is the outer wrapper.

#include "vector_resize_methods.h"

// FUNCTION: GAMEMD 0x40CE50
bool VectorResize::FUN_0040CE50(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < Count) {
            Count = Length;
        }
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x42D780
bool VectorResize::FUN_0042D780(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < Count) {
            Count = Length;
        }
        return true;
    }

    return false;
}
