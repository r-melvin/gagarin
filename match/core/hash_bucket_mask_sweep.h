// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every entry point and every offset below was read off the user's own retail
//   gamemd.exe v1.001 with the local Ghidra CLI. The two offsets come straight
//   off the instructions: the stored hash function at `[ESI+0x18]`
//   (`CALL dword ptr [ESI+0x18]`) and the table's bit width at `[ESI+0xC]`
//   (`MOV ECX,[ESI+0xC]`, used as the SHL count).
//
// Six identical 29-byte hash-bucket index functions.
//
// Hash the key with the table's stored hash function, then mask the result down
// to the table's current bit width: `(1 << bits) - 1` is the bucket mask, so
// the index is always in range without a division. All six instances are
// byte-for-byte identical, relocations included -- the key type never reaches
// the code because the hash goes through the stored function pointer.
//
// The hash function pointer is called with the key in ECX and nothing on the
// stack, so it is a one-argument `__fastcall`, not a virtual slot: retail moves
// `this` out to ESI first and then loads ECX from the stack argument.
//
// Callers load the table into ECX (`MOV ECX,<table>`) and push the key, and
// each entry point ends `RET 4`, so all six are __thiscall members of the
// shared layout view. The view stands for six separate entry points spread
// from 0x624C80 to 0x7AECB0 whose layout is identical; each receiver's true
// class is undetermined.
#ifndef GG_MATCH_CORE_HASH_BUCKET_MASK_SWEEP_H
#define GG_MATCH_CORE_HASH_BUCKET_MASK_SWEEP_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

typedef int (__fastcall* HashFunction)(const void* key);

struct HashTableIndex
{
    char         _pad000[0x0C];   // +0x0000
    int          BitWidth;        // +0x000C  log2 of the bucket count
    char         _pad010[0x08];   // +0x0010
    HashFunction Hash;            // +0x0018

    int FUN_00624C80(const void* key);   // FUNCTION: GAMEMD 0x624C80
    int FUN_00625070(const void* key);   // FUNCTION: GAMEMD 0x625070
    int FUN_00625390(const void* key);   // FUNCTION: GAMEMD 0x625390
    int FUN_007AE0C0(const void* key);   // FUNCTION: GAMEMD 0x7AE0C0
    int FUN_007AE5B0(const void* key);   // FUNCTION: GAMEMD 0x7AE5B0
    int FUN_007AECB0(const void* key);   // FUNCTION: GAMEMD 0x7AECB0
};
GG_STATIC_ASSERT(offsetof(HashTableIndex, BitWidth) == 0x0C);
GG_STATIC_ASSERT(offsetof(HashTableIndex, Hash) == 0x18);

#endif  // GG_MATCH_CORE_HASH_BUCKET_MASK_SWEEP_H
