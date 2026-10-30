// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The object slot 13 of the AbstractClass family receives: each override
//   feeds its fields to it through 0x4A1CA0 (one byte, RET 4) and 0x4A1D50
//   (one dword, RET 4), both __thiscall on the passed pointer; 0x4A1DB0
//   (RET 4) takes the address of a character field.
#ifndef GG_MATCH_LAYOUT_OBJ_004A1D30_H
#define GG_MATCH_LAYOUT_OBJ_004A1D30_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The four-byte staging word at +0x08, addressable as bytes (0x4A1C10 / 0x4A1CA0 / 0x4A1DE0).
union Staging_004A1D30
{
    int           word;
    unsigned char bytes[4];
};

struct Obj_004A1D30
{
    // Queue64F2B7 allocates12 bytes;64F2C5/64F2C7/64F2CA zero these.
    // Every following checksum block copies all12 bytes into varargs.
    // Primary ev_b9e977dcbc3a2f14122106db50ca84661b69c9019f8f456a37e077b1c1f868ad.
    int unknown_00;
    int unknown_04;
    Staging_004A1D30 unknown_08;

    // Inline construction shape is corroborated by64F2C1/C3 null test and
    //64F2C5/C7/CA zero stores. Original constructor source spelling is unknown.
    Obj_004A1D30() : unknown_00(0), unknown_04(0) { unknown_08.word = 0; }

    // FUNCTION: GAMEMD 0x4A1C10 (decl; reloc) -- append the unnormalized byte.
    void FUN_004A1C10(unsigned char value);
    // FUNCTION: GAMEMD 0x4A1CA0 (decl; reloc) -- add one byte.
    void FUN_004A1CA0(bool value);
    // FUNCTION: GAMEMD 0x4A1CA0 (decl; reloc) -- the same entry for a flag stored as a plain byte.
    void FUN_004A1CA0(unsigned char value);
    // FUNCTION: GAMEMD 0x4A1D30 (decl; reloc) -- add one word.
    void FUN_004A1D30(unsigned short value);
    // FUNCTION: GAMEMD 0x4A1D50 (decl; reloc) -- add one dword.
    void FUN_004A1D50(int value);
    // FUNCTION: GAMEMD 0x4A1D70 (decl; reloc) -- consumes the original four float bytes, RET4.
    void FUN_004A1D70(float value);
    // FUNCTION: GAMEMD 0x4A1D90 (decl; reloc) -- add one double (RET 8).
    void FUN_004A1D90(double value);
    // FUNCTION: GAMEMD 0x4A1DB0 (decl; reloc) -- add a NUL-terminated string.
    void FUN_004A1DB0(const char* text);
    // FUNCTION: GAMEMD 0x4A1DE0 (decl; reloc) -- append a byte span, return the running value.
    int FUN_004A1DE0(const void* data, int length);
};

GG_STATIC_ASSERT(offsetof(Obj_004A1D30, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(Obj_004A1D30, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(Obj_004A1D30, unknown_08) == 8);
GG_STATIC_ASSERT(sizeof(Obj_004A1D30) == 12);
#endif  // GG_MATCH_LAYOUT_OBJ_004A1D30_H
