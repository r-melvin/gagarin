// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below; further
//   multi-word integer helpers from the MPLayer.CPP object (0x5c5e90-0x5c91ef).
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2 /MT
//
// Address index: 0x5C6500 0x5C6550 0x5C8930

// FUNCTION: GAMEMD 0x5C6500
// Lay big-endian bytes out as little-endian words, extending the sign through the high bytes.
void BytesToWordsSigned(unsigned char* dst, const unsigned char* src, int length, int words)
{
    unsigned char sign = (src[0] & 0x80) ? 0xFF : 0;
    int total = words * 4;
    int pad = total - length;
    dst += total;
    if (pad > 0) {
        do { *--dst = sign; } while (--pad);
    }
    if (length > 0) {
        int n = length;
        do { *--dst = *src++; } while (--n);
    }
}

// FUNCTION: GAMEMD 0x5C6550
// Lay big-endian bytes out as little-endian words, padding the high bytes with zero.
void BytesToWords(unsigned char* dst, const unsigned char* src, int length, int words)
{
    int total = words * 4;
    int pad = total - length;
    dst += total;
    if (pad > 0) {
        do { *--dst = 0; } while (--pad);
    }
    if (length > 0) {
        int n = length;
        do { *--dst = *src++; } while (--n);
    }
}

// FUNCTION: GAMEMD 0x5C71E0 (decl; reloc)
unsigned short FUN_005c71e0(unsigned int* q, unsigned int* a, unsigned short d, int n);
// GLOBAL: GAMEMD 0x82E174 -- table of small primes (16-bit entries)
extern unsigned short DAT_0082E174[];
// GLOBAL: GAMEMD 0x82FCE2 -- end of the prime table
extern unsigned short DAT_0082FCE2[];

// FUNCTION: GAMEMD 0x5C8930
// True when no prime in the small-prime table divides the number.
bool FUN_005C8930(unsigned int* a, int n)
{
    unsigned int quotient[64];
    for (const unsigned short* p = DAT_0082E174; p < DAT_0082FCE2; p++) {
        if (FUN_005c71e0(quotient, a, *p, n) == 0) {
            return false;
        }
    }
    return true;
}
