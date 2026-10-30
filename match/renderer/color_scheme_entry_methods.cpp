// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x4F4CE0 and 0x4F4D30.
//   Kept apart from color_scheme_iterator_methods.cpp so the palette iterator
//   there calls the comparison as retail does instead of expanding it.

#include "color_scheme_iterator_methods.h"

extern "C" int __cdecl strcmp(const char* a, const char* b);
#pragma intrinsic(strcmp)

// FUNCTION: GAMEMD 0x4F4CE0
// True when the two keys hold the same text.
bool Entry_00626690::Equals(Entry_00626690* other)
{
    return strcmp(Key, other->Key) == 0;
}

// FUNCTION: GAMEMD 0x4F4D30
// True when the two keys differ.
bool Entry_00626690::FUN_004F4D30(Entry_00626690* other)
{
    return strcmp(Key, other->Key) != 0;
}
