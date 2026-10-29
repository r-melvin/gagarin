// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at 0x631F60. Big-number helpers (0x5C6940 fill,
//   0x5C6370 load from bytes, 0x5C6960 significant-length) are the ones the pk code around
//   0x5C6000 uses; the receiver is a placeholder view of the members touched.
//
// Address index: 0x631F60

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x5C6940 (decl; reloc) -- fill `count` words with `value`.
void __fastcall BigFill_005C6940(unsigned long* words, unsigned long value, int count);
// FUNCTION: GAMEMD 0x5C6370 (decl; reloc) -- load `count` words from big-endian bytes.
void __fastcall BigLoad_005C6370(unsigned long* words, const unsigned char* bytes, int count);
// FUNCTION: GAMEMD 0x5C6960 (decl; reloc) -- number of significant words.
int __fastcall BigLength_005C6960(const unsigned long* words, int count);

// Two 0x40-word big numbers and the length of the first, less one.
struct BigPair_00631F60
{
    unsigned long A[0x40];   // +0x000
    unsigned long B[0x40];   // +0x100
    int           LengthLessOne;   // +0x200

    BigPair_00631F60(const unsigned char* b, const unsigned char* a);
};
GG_STATIC_ASSERT(offsetof(BigPair_00631F60, B) == 0x100);
GG_STATIC_ASSERT(offsetof(BigPair_00631F60, LengthLessOne) == 0x200);

// FUNCTION: GAMEMD 0x631F60
// Load both numbers from their byte strings and record the length of the first.
BigPair_00631F60::BigPair_00631F60(const unsigned char* b, const unsigned char* a)
{
    BigFill_005C6940(A, 0, 0x40);
    BigFill_005C6940(B, 0, 0x40);
    BigLoad_005C6370(A, a, 0x40);
    BigLoad_005C6370(B, b, 0x40);
    LengthLessOne = BigLength_005C6960(A, 0x40) - 1;
}
