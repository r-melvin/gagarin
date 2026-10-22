// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Public-key pair generation (0x632050): __fastcall, random source in ECX,
// bit precision in EDX, the two keys on the stack (`ret 8`); 0x96CC-byte
// frame (__chkstk). Two primes are drawn by the same inlined search: a
// random odd value a in [2^(bits-2), 2^(bits-1) - 1] (0x632A70), b = 2a + 1,
// two small-prime sieves (0x1B70 bytes each, composite flag at +0; set up by
// 0x632BE0, stepped by 0x632C40) and the probable-prime test 0x5C9020 on
// both, stepping a by 2 and b by 4. The keys get modulus n = p * q, the
// first exponent 0x10001 and the second its inverse modulo
// (p - 1)(q - 1) (0x632A20); unknown_200 is the bit count of n minus one.
// A random plain block is then sent through Encrypt/Decrypt and the whole
// search repeats until it round-trips.
#include <stdlib.h>
#include <string.h>
#include "pk_key_pipes.h"

class PrimeSieve_00632050
{
public:
    bool Composite;                 // +0x0000
    char unknown_0001[0x1B6F];      // +0x0001

    // FUNCTION: GAMEMD 0x632BE0 (decl; reloc)
    void Set(const BigInt_00632740& value);
    // FUNCTION: GAMEMD 0x632C40 (decl; reloc)
    void Step(int amount);
};
GG_STATIC_ASSERT(sizeof(PrimeSieve_00632050) == 0x1B70);

inline BigInt_00632740 MakePrimeFromSieve(Straw* random, int bits)
{
    BigInt_00632740 low = BigInt_00632740(1) << (unsigned short)(bits - 2);
    BigInt_00632740 high = (BigInt_00632740(1) << (unsigned short)(bits - 1)) - 1;
    BigInt_00632740 a;
    BigInt_00632740 b;
    PrimeSieve_00632050 sieve_a;
    PrimeSieve_00632050 sieve_b;

    do {
        a.Randomize(random, low, high);
        b = a * 2 + 1;
        sieve_a.Set(a);
        sieve_b.Set(b);
        while (sieve_a.Composite || sieve_b.Composite || !a.Call_005C9020() || !b.Call_005C9020()) {
            a += BigInt_00632740(2);
            b += BigInt_00632740(4);
            if (a.Compare(high) > 0) break;
            sieve_a.Step(2);
            sieve_b.Step(4);
        }
    } while (a > high);
    return b;
}

// FUNCTION: GAMEMD 0x632050
void __fastcall FUN_00632050(Straw* random, int bits, PKey_00632740* fast, PKey_00632740* slow)
{
    unsigned char plain[256];
    unsigned char crypt[256];

    do {
        BigInt_00632740 p = MakePrimeFromSieve(random, bits);
        BigInt_00632740 q = MakePrimeFromSieve(random, bits);
        BigInt_00632740 e(0x10001);
        BigInt_00632740 n = p * q;
        BigInt_00632740 phi = p.MinusOneCopy() * q.MinusOneCopy();
        BigInt_00632740 d = e.Inverse(phi);

        fast->Exponent = e;
        fast->Modulus = n;
        fast->unknown_200 = n.Call_005C6960() - 1;
        slow->Exponent = d;
        slow->Modulus = n;
        slow->unknown_200 = fast->unknown_200;

        for (int index = 0; index < fast->PlainBlockBytes(); index++) {
            plain[index] = (unsigned char)rand();
        }
        fast->Encrypt(plain, fast->PlainBlockBytes(), crypt);
        slow->Decrypt(crypt, slow->CipherBlockBytes(), crypt);
    } while (memcmp(plain, crypt, fast->PlainBlockBytes()) != 0);
}
