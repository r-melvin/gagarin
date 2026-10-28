// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below. Member bodies of the
//   public-key big number declared in pk_key_pipes.h.
//
// Address index: 0x6329C0 0x632A20 0x632A70 0x632AA0 0x632AC0 0x632B20 0x632B70 0x632BC0

#include "pk_key_pipes.h"

// FUNCTION: GAMEMD 0x632BC0
bool BigInt_00632740::operator>(const BigInt_00632740& other) const
{
    return Compare(other) > 0;
}

// FUNCTION: GAMEMD 0x5C8E40 (decl; reloc) -- fill a number with random digits between two bounds.
void FUN_005c8e40(unsigned long* digits, Straw* random, const unsigned long* low,
                  const unsigned long* high, int precision);
// FUNCTION: GAMEMD 0x5C6A30 (decl; reloc) -- add with carry.
char FUN_005c6a30(unsigned long* result, const unsigned long* left,
                  const unsigned long* right, int carry, int precision);
// GLOBAL: GAMEMD 0xA8F8FC
extern char DAT_00a8f8fc;

// FUNCTION: GAMEMD 0x632A70
// Fill with a random odd value between the bounds.
void BigInt_00632740::Randomize(Straw* random, const BigInt_00632740& low, const BigInt_00632740& high)
{
    FUN_005c8e40(Digit, random, low.Digit, high.Digit, 64);
    Digit[0] |= 1;
}

// FUNCTION: GAMEMD 0x632AA0
BigInt_00632740& BigInt_00632740::operator+=(const BigInt_00632740& other)
{
    DAT_00a8f8fc = FUN_005c6a30(Digit, Digit, other.Digit, 0, 64);
    return *this;
}

// FUNCTION: GAMEMD 0x5C6B60 (decl; reloc) -- the same subtraction with the value pushed as a full word.
char FUN_005c6b60_word(unsigned long* result, const unsigned long* source,
                       unsigned long value, int borrow, int precision);
// FUNCTION: GAMEMD 0x5C7740 (decl; reloc) -- modular inverse.
void FUN_005c7740(unsigned long* result, const unsigned long* source,
                  const unsigned long* modulus, int precision);
// FUNCTION: GAMEMD 0x5C6AA0 (decl; reloc) -- add a 16-bit value with carry.
char FUN_005c6aa0(unsigned long* result, const unsigned long* source,
                  unsigned long value, int carry, int precision);
// FUNCTION: GAMEMD 0x5C6D90 (decl; reloc) -- multiply by a 16-bit value.
int FUN_005c6d90(unsigned long* result, const unsigned long* source,
                 unsigned short value, int precision);
// FUNCTION: GAMEMD 0x5C67A0 (decl; reloc)
void FUN_005c67a0(unsigned long* digits, int shift, int precision);

// FUNCTION: GAMEMD 0x6329C0
BigInt_00632740 BigInt_00632740::operator-(int value) const
{
    BigInt_00632740 result;
    DAT_00a8f8fd = FUN_005c6b60_word(result.Digit, Digit, value, 0, 64);
    return result;
}

// FUNCTION: GAMEMD 0x632A20
BigInt_00632740 BigInt_00632740::Inverse(const BigInt_00632740& modulus) const
{
    BigInt_00632740 result;
    FUN_005c7740(result.Digit, Digit, modulus.Digit, 64);
    return result;
}

// FUNCTION: GAMEMD 0x632AC0
BigInt_00632740 BigInt_00632740::operator+(int value) const
{
    BigInt_00632740 result;
    DAT_00a8f8fc = FUN_005c6aa0(result.Digit, Digit, value & 0xFFFF, 0, 64);
    return result;
}

// FUNCTION: GAMEMD 0x632B20
BigInt_00632740 BigInt_00632740::operator*(int value) const
{
    BigInt_00632740 result;
    DAT_00a8f8f8 = FUN_005c6d90(result.Digit, Digit, value, 64);
    return result;
}

// FUNCTION: GAMEMD 0x632B70
BigInt_00632740 BigInt_00632740::operator<<(int bits) const
{
    BigInt_00632740 result = *this;
    FUN_005c67a0(result.Digit, bits, 64);
    return result;
}
