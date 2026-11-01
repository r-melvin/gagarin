// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x41C490.

#include "vector_dtor_methods.h"

// FUNCTION: GAMEMD 0x41C490
//
// The array path destroys the elements back to front with the CRT's own
// `while (--count >= 0)` idiom: the pre-decrement leaves the sign flag for the
// entry test (`DEC EAX; LEA ESI,[ESI+ECX*4]; JS`) and VC6 then strength-
// reduces the loop into a down-counter (`LEA EDI,[EAX+1]; ... DEC EDI; JNZ`).
// A named `remaining = count - 1` tested with `>= 0` (or a `for` with an
// explicit `i--`) inserts a `TEST EAX,EAX; JL` instead and scores 23.3%; a
// do/while with the pre-decrement in its condition gets 64.3%.
void* Element_0041C490::FUN_0041C490(char flags)
{
    if (flags & 2) {
        int count = ((int*)this)[-1];

        char* block = (char*)this - 4;
        char* cursor = (char*)this + count * 12;

        while (--count >= 0) {
            cursor -= 12;

            FUN_00763720(cursor);
        }

        if (flags & 1) {
            FUN_007C8B3D(block);
        }

        return block;
    }

    FUN_00763720(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}
