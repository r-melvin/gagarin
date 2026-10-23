// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Checksum of a short record: a fill count at +0x10 and a four-byte buffer at
// +0x14. With a non-zero fill count the byte at that index is set to the count
// and the bytes after it repeat the first byte; the four bytes are then run
// through the table-driven checksum at 0x4A1FB0 (data in ECX, length in EDX,
// seed on the stack), seeded with the word at +0x0C. With a zero fill count
// the seed is returned unchanged. Two copies at different addresses, owners
// are placeholders `Obj_<ADDR>`; each address is verified separately.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x4A1FB0 (decl; reloc) -- table-driven checksum.
extern unsigned int FUN_004A1FB0(const void* data, int length, unsigned int seed);

union Word_004A2060 {
    unsigned char bytes[4];
    unsigned int word;
};

struct Obj_004A2060 {
    unsigned char unknown_00[0xC];
    unsigned int unknown_0C;
    unsigned int unknown_10;
    Word_004A2060 unknown_14;
    unsigned int FUN_004A2060();
    unsigned int FUN_004A20F0();
};
GG_STATIC_ASSERT(offsetof(Obj_004A2060, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(Obj_004A2060, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(Obj_004A2060, unknown_14) == 0x14);

// FUNCTION: GAMEMD 0x004A2060
unsigned int Obj_004A2060::FUN_004A2060()
{
    if (unknown_10 != 0) {
        unknown_14.bytes[unknown_10] = (unsigned char)unknown_10;
        for (unsigned int i = unknown_10 + 1; i < 4; ++i)
            unknown_14.bytes[i] = unknown_14.bytes[0];
        Word_004A2060 copy = unknown_14;
        return FUN_004A1FB0(&copy, 4, unknown_0C);
    }
    return unknown_0C;
}

// FUNCTION: GAMEMD 0x004A20F0
unsigned int Obj_004A2060::FUN_004A20F0()
{
    if (unknown_10 != 0) {
        unknown_14.bytes[unknown_10] = (unsigned char)unknown_10;
        for (unsigned int i = unknown_10 + 1; i < 4; ++i)
            unknown_14.bytes[i] = unknown_14.bytes[0];
        Word_004A2060 copy = unknown_14;
        return FUN_004A1FB0(&copy, 4, unknown_0C);
    }
    return unknown_0C;
}
