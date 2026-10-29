// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
// Placement lead: this file regresses under the project /Ob2 default, so a
// definition it can see probably lived in another original file.
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

// GLOBAL: GAMEMD 0x81F7B4 -- the 256-entry CRC-32 table.
extern const unsigned int DAT_0081F7B4[256];

// FUNCTION: GAMEMD 0x004A1FB0
// Table-driven CRC-32 update over `length` bytes, starting from `seed`.
unsigned int FUN_004A1FB0(const void* data, int length, unsigned int seed)
{
    const unsigned char* bytes = (const unsigned char*)data;
    unsigned int crc = ~seed;
    while (length--) {
        crc = (crc >> 8) ^ DAT_0081F7B4[(crc & 0xFF) ^ *bytes];
        bytes++;
    }
    return ~crc;
}

// FUNCTION: GAMEMD 0x004A1FF0
// PARTIAL: 90% - xor operands come out as esi,edx instead of edx,esi (2 instructions differ).
// The same CRC-32 update over a NUL-terminated string, starting from `seed`.
unsigned int FUN_004A1FF0(const char* text, unsigned int seed)
{
    unsigned int crc = ~seed;
    while (*text) {
        crc = (crc >> 8) ^ DAT_0081F7B4[(unsigned char)*text ^ (crc & 0xFF)];
        text++;
    }
    return ~crc;
}

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
