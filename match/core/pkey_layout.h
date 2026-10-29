// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
#ifndef GG_MATCH_CORE_PKEY_LAYOUT_H
#define GG_MATCH_CORE_PKEY_LAYOUT_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
// FUNCTION: GAMEMD 0x5C6940 (decl; reloc)
void FUN_005c6940(unsigned long* digits, unsigned long value, int precision);
// FUNCTION: GAMEMD 0x5C8500 (decl; reloc)
int FUN_005c8500(unsigned long* result, const unsigned long* base,
                 const unsigned long* exponent, const unsigned long* modulus,
                 int precision);

// FUNCTION: GAMEMD 0x5C6960 (decl; reloc) -- significant bit count.
int FUN_005c6960(const unsigned long* digits, int precision);
// FUNCTION: GAMEMD 0x5C69E0 (decl; reloc) -- signed three-way compare.
int FUN_005c69e0(const unsigned long* left, const unsigned long* right, int precision);
// FUNCTION: GAMEMD 0x5C6B60 (decl; reloc) -- subtract a 16-bit value with borrow.
char FUN_005c6b60(unsigned long* result, const unsigned long* source,
                  unsigned short value, int borrow, int precision);
// FUNCTION: GAMEMD 0x5C62B0 (decl; reloc) -- store the number as length-prefixed big-endian bytes.
int FUN_005c62b0(const unsigned long* digits, unsigned char* out, int precision);
// FUNCTION: GAMEMD 0x5C6370 (decl; reloc) -- load a number from length-prefixed big-endian bytes.
void FUN_005c6370(unsigned long* digits, const unsigned char* data, int precision);
// FUNCTION: GAMEMD 0x5C6FE0 (decl; reloc) -- multiply.
int FUN_005c6fe0(unsigned long* result, const unsigned long* left,
                 const unsigned long* right, int precision);
// FUNCTION: GAMEMD 0x5C9020 (decl; reloc) -- probable-prime test.
bool FUN_005c9020(const unsigned long* digits, int precision);

// GLOBAL: GAMEMD 0xA8F8F8
extern int DAT_00a8f8f8;
// GLOBAL: GAMEMD 0xA8F8FD
extern char DAT_00a8f8fd;

class Straw;

class BigInt_00632740
{
public:
    unsigned long Digit[64];   // +0x00

    BigInt_00632740(unsigned long value = 0) { FUN_005c6940(Digit, value, 64); }

    BigInt_00632740 ModPow(const BigInt_00632740& exponent, const BigInt_00632740& modulus) const
    {
        BigInt_00632740 result;
        DAT_00a8f8f8 = FUN_005c8500(result.Digit, Digit, exponent.Digit, modulus.Digit, 64);
        return result;
    }

    // Out-of-line helpers used by the key generator 0x632050 (all
    // __thiscall; the by-value results come back through a hidden pointer).
    // FUNCTION: GAMEMD 0x6329C0 (decl; reloc)
    BigInt_00632740 operator-(int value) const;
    // FUNCTION: GAMEMD 0x632A20 (decl; reloc) -- modular inverse.
    BigInt_00632740 Inverse(const BigInt_00632740& modulus) const;
    // FUNCTION: GAMEMD 0x632A70 (decl; reloc) -- random odd value in [low, high].
    void Randomize(Straw* random, const BigInt_00632740& low, const BigInt_00632740& high);
    // FUNCTION: GAMEMD 0x632AA0 (decl; reloc)
    BigInt_00632740& operator+=(const BigInt_00632740& other);
    // FUNCTION: GAMEMD 0x632AC0 (decl; reloc)
    BigInt_00632740 operator+(int value) const;
    // FUNCTION: GAMEMD 0x632B20 (decl; reloc)
    BigInt_00632740 operator*(int value) const;
    // FUNCTION: GAMEMD 0x632B70 (decl; reloc)
    BigInt_00632740 operator<<(int bits) const;
    // FUNCTION: GAMEMD 0x632BC0 (decl; reloc)
    bool operator>(const BigInt_00632740& other) const;

    int Compare(const BigInt_00632740& other) const { return FUN_005c69e0(Digit, other.Digit, 64); }
    bool Call_005C9020() const { return FUN_005c9020(Digit, 64); }
    int Call_005C6960() const { return FUN_005c6960(Digit, 64); }
    BigInt_00632740 MinusOneCopy() const
    {
        BigInt_00632740 result;
        DAT_00a8f8fd = FUN_005c6b60(result.Digit, Digit, 1, 0, 64);
        return result;
    }
    BigInt_00632740 operator*(const BigInt_00632740& other) const
    {
        BigInt_00632740 result;
        DAT_00a8f8f8 = FUN_005c6fe0(result.Digit, Digit, other.Digit, 64);
        return result;
    }
};
GG_STATIC_ASSERT(sizeof(BigInt_00632740) == 0x100);

class PKey_00632740
{
public:
    BigInt_00632740 Modulus;    // +0x000
    BigInt_00632740 Exponent;   // +0x100
    int unknown_200;           // +0x200

    int PlainBlockBytes() const { return (unknown_200 - 1) / 8; }
    int CipherBlockBytes() const { return PlainBlockBytes() + 1; }

    int BlockCountFor(int length) const { return (length - 1) / PlainBlockBytes() + 1; }

    // FUNCTION: GAMEMD 0x632740
    int Encrypt(const void* source, int length, void* dest) const;
    // FUNCTION: GAMEMD 0x632870
    int Decrypt(const void* source, int length, void* dest) const;

    // FUNCTION: GAMEMD 0x631FC0 -- serialise the modulus; 0 when no buffer is given.
    int StoreModulus(unsigned char* out) const;
    // FUNCTION: GAMEMD 0x631FE0 -- serialise the exponent; 0 when no buffer is given.
    int StoreExponent(unsigned char* out) const;
    // FUNCTION: GAMEMD 0x632000 -- load the modulus and record its bit length minus one.
    void LoadModulus(const unsigned char* data);
    // FUNCTION: GAMEMD 0x632030 -- load the exponent.
    void LoadExponent(const unsigned char* data);
};
GG_STATIC_ASSERT(offsetof(PKey_00632740, Modulus) == 0x000);
GG_STATIC_ASSERT(offsetof(PKey_00632740, Exponent) == 0x100);
GG_STATIC_ASSERT(offsetof(PKey_00632740, unknown_200) == 0x200);


#endif
