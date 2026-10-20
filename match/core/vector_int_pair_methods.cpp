// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference
//   Every body below was written against the retail disassembly of the user's
//   gamemd.exe v1.001 read through the local Ghidra CLI. RA1's CODE/VECTOR.H
//   supplied method NAMES and loop shape only.
//
// The dword-element vector pair, bodies ascending by retail address.

#include "vector_int_pair_methods.h"

// Index of an element addressed by pointer. An invalid vector answers zero
// rather than a negative index, and the subtraction is unsigned, which is what
// makes the divide a `SHR` rather than a signed sequence.
// FUNCTION: GAMEMD 0x660CB0
int VectorIntPair::ID_00660CB0(const int* ptr) const
{
    if (!IsValid) {
        return 0;
    }
    return ((unsigned long)ptr - (unsigned long)Vector) / sizeof(int);
}

// Plain subscript, returned by value.
// FUNCTION: GAMEMD 0x660CD0
int VectorIntPair::Item_00660CD0(int index) const
{
    return ((int*)Vector)[index];
}

// Element-wise comparison. Retail hoists the length into a register and turns
// the other vector's base into a displacement off ours, which is cl's own
// strength reduction of the two subscripts; the source just reads both.
// FUNCTION: GAMEMD 0x660CE0
bool VectorIntPair::Equals_00660CE0(const VectorIntPair& other) const
{
    if (Length == other.Length) {
        for (int index = 0; index < Length; index++) {
            if (((int*)Vector)[index] != ((int*)other.Vector)[index]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

// The plain vector's resize: the shared inner half and nothing else, so this
// one has no ActiveCount clamp and is two bytes shorter than the dynamic form
// below.
// FUNCTION: GAMEMD 0x660D20
bool VectorIntPair::Resize_00660D20(int newsize, void** array)
{
    return ResizeBase(newsize, array);
}

// Index of an element addressed by value. The reference is dereferenced once
// before the loop, which is the `MOV ESI,[ESI]` at 0x660E1E.
// FUNCTION: GAMEMD 0x660E00
int VectorIntPair::ID_00660E00(const int& object) const
{
    if (!IsValid) {
        return 0;
    }
    for (int index = 0; index < Length; index++) {
        if (((int*)Vector)[index] == object) {
            return index;
        }
    }
    return -1;
}

// The second instantiation of the pointer form.
// FUNCTION: GAMEMD 0x660E40
int VectorIntPair::ID_00660E40(const int* ptr) const
{
    if (!IsValid) {
        return 0;
    }
    return ((unsigned long)ptr - (unsigned long)Vector) / sizeof(int);
}

// The dynamic vector's resize: the shared inner half wrapped so the active
// count is clamped to the new length. The wrapper is what places the failing
// return last, which is the lever written up in
// match/core/vector_resize_family_methods.cpp.
// FUNCTION: GAMEMD 0x660E60
bool VectorIntPair::Resize_00660E60(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < ActiveCount) {
            ActiveCount = Length;
        }
        return true;
    }

    return false;
}

// Index of an element by value over the active range. The dynamic vector does
// not gate this on the valid flag - it walks the active count directly.
// FUNCTION: GAMEMD 0x660F50
int VectorIntPair::ID_00660F50(const int& object) const
{
    for (int index = 0; index < ActiveCount; index++) {
        if (((int*)Vector)[index] == object) {
            return index;
        }
    }
    return -1;
}
