// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at the address below.

#include <string.h>
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/node_name_type.h"

// Two short name strings stored back to back; only the starts of the two
// buffers are established by the body (the length of the second is not).
struct NamePair_0049B760
{
    char First[0x1C];   // +0x00
    char Second[1];     // +0x1C
    void FUN_0049B760(const unsigned short* first, const unsigned short* second);
};
GG_STATIC_ASSERT(offsetof(NamePair_0049B760, First) == 0x00);
GG_STATIC_ASSERT(offsetof(NamePair_0049B760, Second) == 0x1C);

// FUNCTION: GAMEMD 0x49B760
// Stores two UTF16 names as narrow strings, or an empty string for a missing name.
void NamePair_0049B760::FUN_0049B760(const unsigned short* first, const unsigned short* second)
{
    if (first)
        strcpy(First, NarrowName_007350C0(first));
    else
        First[0] = 0;
    if (second)
        strcpy(Second, NarrowName_007350C0(second));
    else
        Second[0] = 0;
}
