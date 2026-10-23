// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Key hash of a narrow string object (core/string_class.h): seeded with the
// length, then for each character adds the signed character value and its
// index and rotates the accumulator left by eight bits. __fastcall, string
// object in ECX; the bucket-table constructor stores its address (see
// hash_table_ctor_methods.cpp).

#include "string_class.h"

// FUNCTION: GAMEMD 0x7B5400 (decl; reloc) -- character data of the string object.
extern const signed char* FUN_007B5400(const Obj_007B4620* self);

// FUNCTION: GAMEMD 0x006B94E0
unsigned int FUN_006B94E0(const Obj_007B4620* key)
{
    unsigned int hash = key->Length();
    for (unsigned int i = 0; i < (unsigned int)key->Length(); ++i) {
        hash += FUN_007B5400(key)[i] + i;
        hash = (hash << 8) ^ (hash >> 24);
    }
    return hash;
}
