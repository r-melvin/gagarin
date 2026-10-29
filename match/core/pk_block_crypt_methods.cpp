// Provenance: own-binary-via-Ghidra
// Public-key block transforms (__thiscall, `ret 0xC`: source, length,
// destination). The key holds two 64-word big integers, at +0x000 and
// +0x100, and a bit precision at +0x200; the plain block is
// (bits - 1) / 8 bytes and the cipher block one byte more. Each block goes
// through the modular exponentiation 0x5C8500 (__fastcall: result ECX,
// base EDX, then exponent, modulus and the 64-word precision on the
// stack), whose status is kept in 0xA8F8F8. 0x5C6940 (__fastcall: digits
// ECX, value EDX, precision pushed) sets a big integer to a small value.
#include <string.h>
#include "pk_key_pipes.h"

// FUNCTION: GAMEMD 0x632740
int PKey_00632740::Encrypt(const void* source, int length, void* dest) const
{
    int total = 0;
    while (length >= PlainBlockBytes()) {
        BigInt_00632740 temp;
        memmove(&temp, source, PlainBlockBytes());
        temp = temp.ModPow(Exponent, Modulus);
        memmove(dest, &temp, CipherBlockBytes());
        length -= PlainBlockBytes();
        source = (const char*)source + PlainBlockBytes();
        dest = (char*)dest + CipherBlockBytes();
        total += CipherBlockBytes();
    }
    return total;
}

// FUNCTION: GAMEMD 0x632870
int PKey_00632740::Decrypt(const void* source, int length, void* dest) const
{
    int total = 0;
    BigInt_00632740 temp;
    while (length >= CipherBlockBytes()) {
        temp = 0;
        memmove(&temp, source, CipherBlockBytes());
        temp = temp.ModPow(Exponent, Modulus);
        memmove(dest, &temp, PlainBlockBytes());
        length -= CipherBlockBytes();
        source = (const char*)source + CipherBlockBytes();
        dest = (char*)dest + PlainBlockBytes();
        total += PlainBlockBytes();
    }
    return total;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA8F8F8
int DAT_00a8f8f8;
// END defined globals
