// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// The four remaining identity tests, ordered ascending by retail address.
//
// The two conditions have to sit in one `&&` with the `true` inline: split
// into two early-return `if`s the failure block is duplicated and the score
// drops to 18.2%.

#include "same_object_test_sweep.h"


// FUNCTION: GAMEMD 0x55F6C0
bool HandleHolder::FUN_0055F6C0(void** other)
{
    if (this->Held != 0 && *this->Held == *other) {
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x746EA0
bool HandleHolder::FUN_00746EA0(void** other)
{
    if (this->Held != 0 && *this->Held == *other) {
        return true;
    }

    return false;
}

