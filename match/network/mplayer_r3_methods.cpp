// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. Further helpers of the
//   multi-word integer block of MPLayer.CPP (see MPLayer.cpp), matched in this sibling file.
//
// Address index: 0x5C6370 0x5C83C0 0x5C88B0

// Number of bytes needed to hold `value` (0 for zero).
static inline unsigned int BytePrecisionOf(unsigned int value)
{
    unsigned int i;
    for (i = 4; i; --i) {
        if (value >> ((i - 1) * 8))
            break;
    }
    return i;
}

#include <string.h>

// Sets the n-word number `r` to the small value `v`.
static inline void WordsSetSmallR3(unsigned int* r, unsigned int v, int n)
{
    memset(r, 0, n * 4);
    *r = v;
}

// Modulus state of the modular multiplication (see MPLayer.cpp).
// GLOBAL: GAMEMD 0xABF59C
extern int DAT_00abf59c;
// GLOBAL: GAMEMD 0xABF5A0
extern unsigned short DAT_00abf5a0;
// GLOBAL: GAMEMD 0xABF5A4
extern unsigned int DAT_00abf5a4[4];
// GLOBAL: GAMEMD 0xABF5B4
extern unsigned int DAT_00abf5b4[64];
// GLOBAL: GAMEMD 0xABF6B4
extern unsigned short DAT_00abf6b4;
// GLOBAL: GAMEMD 0xABF6B8
extern int DAT_00abf6b8;
// GLOBAL: GAMEMD 0xABF6BC
extern unsigned int DAT_00abf6bc[130];
// GLOBAL: GAMEMD 0xABF8C4
extern int DAT_00abf8c4;
// GLOBAL: GAMEMD 0xABF8C8
extern unsigned int DAT_00abf8c8[4];

// FUNCTION: GAMEMD 0x5C6370
// Reads a tag-2 record (a one or two byte length, then the value bytes) and stores the value
// big-endian bytes into the `words`-word little-endian buffer `out`, sign-extended.
void __fastcall FUN_005C6370(unsigned char* out, const unsigned char* in, int words)
{
    if (*in++ != 2)
        return;
    unsigned int len;
    if (!(*in & 0x80)) {
        len = *in++;
    } else {
        unsigned int lenBytes = *in++ & 0x7F;
        if ((int)lenBytes > 2)
            return;
        len = *in++;
        if ((int)lenBytes > 1)
            len = (len << 8) | *in++;
    }
    unsigned int size = words * 4;
    if (len > size)
        return;
    const unsigned char* src = in;
    unsigned char fill = (*src & 0x80) ? 0xFF : 0;
    int pad = size - len;
    unsigned char* dst = out + size;
    while (pad > 0) {
        *--dst = fill;
        pad--;
    }
    while ((int)len > 0) {
        *--dst = *src++;
        len--;
    }
}

// FUNCTION: GAMEMD 0x5C83C0
// Clears the modulus state of the modular multiplication (w words).
void __fastcall FUN_005C83C0(int w)
{
    WordsSetSmallR3(DAT_00abf5b4, 0, w);
    DAT_00abf6b8 = 0;
    WordsSetSmallR3(DAT_00abf6bc, 0, w);
    DAT_00abf8c4 = 0;
    DAT_00abf5a0 = 0;
    WordsSetSmallR3(DAT_00abf5a4, 0, 4);
    WordsSetSmallR3(DAT_00abf8c8, 0, 4);
    DAT_00abf6b4 = 0;
    DAT_00abf59c = 0;
}

// GLOBAL: GAMEMD 0x82E174
extern unsigned short DAT_0082e174[3511];
// GLOBAL: GAMEMD 0x82FCE0 -- the last element of the table, read as a dword.
extern unsigned int DAT_0082fce0;

// Looks `key` up in the ascending table of small primes.
static inline const unsigned short* FindTablePrimeR3(unsigned short key)
{
    const unsigned short* base = DAT_0082e174;
    int count = 3511;
    while (count > 0) {
        int mid = count / 2;
        const unsigned short* e = &base[mid];
        if (*e > key) {
            count = mid;
        } else if (*e == key) {
            return e;
        } else {
            base = e + 1;
            count -= mid + 1;
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x5C88B0
// True when the n-word number `a` is one of the table's small primes.
bool __fastcall FUN_005C88B0(const unsigned int* a, int n)
{
    const unsigned int* top = a + n - 1;
    while (*top == 0) {
        if (--n == 0)
            break;
        top--;
    }
    if (n > 1)
        return false;
    if (*a > (DAT_0082fce0 & 0xFFFF))
        return false;
    return FindTablePrimeR3((unsigned short)*a) != 0;
}
