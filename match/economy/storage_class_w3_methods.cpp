// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly of 0x6C9740 and 0x6C97E0:
//   the four-float store's in-place arithmetic operators, each returning a copy of the result
//   by value (hidden result pointer, RET 8).
//
// Address index: 0x6C9740 operator+=, 0x6C97E0 operator-=.

#include "storage_class.h"

// FUNCTION: GAMEMD 0x6C9740
// Adds in place and hands back a copy.
StorageClass StorageClass::operator+=(const StorageClass& other)
{
    for (int i = 0; i < 4; i++) {
        (&Tiberium1)[i] = (&other.Tiberium1)[i] + (&Tiberium1)[i];
    }
    return *this;
}

// FUNCTION: GAMEMD 0x6C97E0
// Subtracts in place and hands back a copy.
StorageClass StorageClass::operator-=(const StorageClass& other)
{
    for (int i = 0; i < 4; i++) {
        (&Tiberium1)[i] = (&Tiberium1)[i] - (&other.Tiberium1)[i];
    }
    return *this;
}
