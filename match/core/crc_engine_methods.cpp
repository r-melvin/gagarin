// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | own-binary-via-REA
//   Evidence: disassembly of 0x4A1C10, 0x4A1CA0, 0x4A1FB0 and 0x4A1FF0 in the user's
//   retail gamemd.exe v1.001; the standard CRC-32 table is at 0x81F7B4 (crc_pad_methods.cpp).
//
// WWLib CRC engine (CRCEngine): a running value (+0x00), a staging index (+0x04) and a four-byte
// staging word (+0x08). Bytes collect in the staging word; when it fills, or when the value is
// read with a partial word pending, the pending bytes are padded (the index is stored at its own
// slot and the bytes after it repeat the first byte) and run through the table-driven CRC-32
// update at 0x4A1FB0, seeded with the running value. The padding store at index 4 lands on the
// byte after the word (+0x0C), as observed in the binary.
//
// Original translation unit: not attested (the address sits between coopcamp.cpp and Credits.CPP).
// The block feed at 0x4A1DE0 is not in this file yet (held; it needs a call kept at its first fold).
#include <stddef.h>
#include "../_layout/obj_004a1d30.h"

// GLOBAL: GAMEMD 0x81F7B4 -- the 256-entry CRC-32 table (defined in crc_pad_methods.cpp).
extern const unsigned int DAT_0081F7B4[256];

// FUNCTION: GAMEMD 0x4A1FB0 (decl; defined below, after its first users)
unsigned int FUN_004A1FB0(const void* data, int length, unsigned int seed);

// The running value with any pending staged bytes folded in.
static unsigned int PendingValue_004A1D30(Obj_004A1D30* self)
{
    if (self->unknown_04 != 0) {
        self->unknown_08.bytes[self->unknown_04] = (unsigned char)self->unknown_04;
        for (unsigned int i = self->unknown_04 + 1; i < 4; ++i)
            self->unknown_08.bytes[i] = self->unknown_08.bytes[0];
        Staging_004A1D30 copy = self->unknown_08;
        return FUN_004A1FB0(&copy, 4, self->unknown_00);
    }
    return self->unknown_00;
}

// FUNCTION: GAMEMD 0x004A1C10
// Append one byte; a full staging word is folded into the running value.
void Obj_004A1D30::FUN_004A1C10(unsigned char value)
{
    if (unknown_04 == 0)
        unknown_08.word = 0;
    unknown_08.bytes[unknown_04] = value;
    unknown_04++;
    if (unknown_04 == 4) {
        unknown_00 = PendingValue_004A1D30(this);
        unknown_04 = 0;
    }
}

// FUNCTION: GAMEMD 0x004A1CA0
// Append one boolean as the byte 0 or 1.
void Obj_004A1D30::FUN_004A1CA0(bool value)
{
    if (unknown_04 == 0)
        unknown_08.word = 0;
    unknown_08.bytes[unknown_04] = (value != false);
    unknown_04++;
    if (unknown_04 == 4) {
        unknown_00 = PendingValue_004A1D30(this);
        unknown_04 = 0;
    }
}

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
