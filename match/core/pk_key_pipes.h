// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Public-key and cipher pipe/straw views shared by pk_block_crypt_methods.cpp
// and pk_pipe_straw_io_methods.cpp.
// RTTI type names from the pinned image: 0x7EFDAC .?AVPKPipe@@,
// 0x7EFDE0 .?AVPKStraw@@ (vtable words listed at each VTABLE marker).
// PKPipe/PKStraw member evidence: 0x632CB0 and 0x633050 store byte 1 at
// +0x0C, the random source at +0x10, the embedded cipher pipe/straw at
// +0x14, the control at +0x34, and zero +0x38, +0x13C and +0x140.
// 0x632DC0/0x633130 read the key pointer at +0x38, stage the key exchange in
// the 0x100-byte buffer at +0x3C, and track it with +0x13C/+0x140.
// The embedded cipher objects are 0x20 bytes (+0x14..+0x34); their key
// submission entries are 0x4381D0 (pipe) and 0x438300 (straw), each
// __thiscall with a buffer and the literal length 0x38.
#ifndef GG_MATCH_CORE_PK_KEY_PIPES_H
#define GG_MATCH_CORE_PK_KEY_PIPES_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

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

// The embedded cipher pipe (+0x14 of PKPipe); 0x20 bytes.
class BlowPipe_00632DC0 : public Pipe
{
public:
    char unknown_0C[0x14];   // +0x0C

    // FUNCTION: GAMEMD 0x4381D0 (decl; reloc)
    void Key(const void* key, int length);
};
GG_STATIC_ASSERT(sizeof(BlowPipe_00632DC0) == 0x20);

// The embedded cipher straw (+0x14 of PKStraw); 0x20 bytes.
class BlowStraw_00633130 : public Straw
{
public:
    char unknown_0C[0x14];   // +0x0C

    // FUNCTION: GAMEMD 0x438300 (decl; reloc)
    void Key(const void* key, int length);
};
GG_STATIC_ASSERT(sizeof(BlowStraw_00633130) == 0x20);

enum { PK_SESSION_KEY_BYTES = 56 };

class PKPipe : public Pipe
{
public:
    enum PipeDirection { PIPE_DIR_0 = 0, PIPE_DIR_1 = 1 };

    // Slot +0x10 (Put-style: source bytes and count).
    // FUNCTION: GAMEMD 0x632DC0
    virtual int FUN_00631D10(int first, int second);

    int SessionKeyCipherBytes() const
    {
        if (Key == NULL) return 0;
        return Key->BlockCountFor(PK_SESSION_KEY_BYTES) * Key->CipherBlockBytes();
    }
    int SessionKeyPlainBytes() const
    {
        if (Key == NULL) return 0;
        return Key->BlockCountFor(PK_SESSION_KEY_BYTES) * Key->PlainBlockBytes();
    }

    bool                unknown_C;     // +0x0C
    Straw*              unknown_10;   // +0x10
    BlowPipe_00632DC0   Cipher;         // +0x14
    PipeDirection        Control;        // +0x34
    PKey_00632740*      Key;            // +0x38
    char                Buffer[256];    // +0x3C
    int                 Counter;        // +0x13C
    int                 unknown_140;      // +0x140
};
GG_STATIC_ASSERT(offsetof(PKPipe, unknown_C)   == 0x0C);
GG_STATIC_ASSERT(offsetof(PKPipe, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(PKPipe, Cipher)       == 0x14);
GG_STATIC_ASSERT(offsetof(PKPipe, Control)      == 0x34);
GG_STATIC_ASSERT(offsetof(PKPipe, Key)          == 0x38);
GG_STATIC_ASSERT(offsetof(PKPipe, Buffer)       == 0x3C);
GG_STATIC_ASSERT(offsetof(PKPipe, Counter)      == 0x13C);
GG_STATIC_ASSERT(offsetof(PKPipe, unknown_140)    == 0x140);
// VTABLE: GAMEMD 0x7EFDAC -- [0x632FF0, 0x631D30, 0x477740, 0x632D10, 0x632DC0, 0x632FE0]

class PKStraw : public Straw
{
public:
    enum PipeDirection { PIPE_DIR_0 = 0, PIPE_DIR_1 = 1 };

    // Slot +0x08 (Get-style: destination bytes and count).
    // FUNCTION: GAMEMD 0x633130
    virtual int FUN_006C98E0(void* first, int second);

    int SessionKeyCipherBytes() const
    {
        if (Key == NULL) return 0;
        return Key->BlockCountFor(PK_SESSION_KEY_BYTES) * Key->CipherBlockBytes();
    }
    int SessionKeyPlainBytes() const
    {
        if (Key == NULL) return 0;
        return Key->BlockCountFor(PK_SESSION_KEY_BYTES) * Key->PlainBlockBytes();
    }

    bool                unknown_C;     // +0x0C
    Straw*              unknown_10;   // +0x10
    BlowStraw_00633130  Cipher;         // +0x14
    PipeDirection        Control;        // +0x34
    PKey_00632740*      Key;            // +0x38
    char                Buffer[256];    // +0x3C
    int                 Counter;        // +0x13C
    int                 unknown_140;      // +0x140
};
GG_STATIC_ASSERT(offsetof(PKStraw, unknown_C)   == 0x0C);
GG_STATIC_ASSERT(offsetof(PKStraw, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(PKStraw, Cipher)       == 0x14);
GG_STATIC_ASSERT(offsetof(PKStraw, Control)      == 0x34);
GG_STATIC_ASSERT(offsetof(PKStraw, Key)          == 0x38);
GG_STATIC_ASSERT(offsetof(PKStraw, Buffer)       == 0x3C);
GG_STATIC_ASSERT(offsetof(PKStraw, Counter)      == 0x13C);
GG_STATIC_ASSERT(offsetof(PKStraw, unknown_140)    == 0x140);
// VTABLE: GAMEMD 0x7EFDE0 -- [0x633370, 0x6330C0, 0x633130, 0x633360]

#endif // GG_MATCH_CORE_PK_KEY_PIPES_H
