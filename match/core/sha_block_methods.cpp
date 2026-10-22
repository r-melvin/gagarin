// Provenance: own-binary-via-Ghidra
// SHA-1 block transform. __thiscall (`ret 8`; callers 0x69D939/0x69D99C/
// 0x69DA61/0x69DAC3 load ECX with the state object and push the 64-byte
// block and the accumulator at state+0x18), but `this` is never read.
// 0x160-byte frame: an 80-word schedule at [esp+0x30] and a five-word
// working copy at [esp+0x1C] taken with `rep movs`.
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct ShaState_0069DB30
{
    unsigned long Long[5];   // +0x00
};
GG_STATIC_ASSERT(sizeof(ShaState_0069DB30) == 0x14);

// The state forwarded at SHAPipe +0x0C (_layout/sha_pipe_layout.h
// places Acc at pipe+0x24, PartialCount at +0x3C and Partial at +0x40).
class SHAState_0069DB30
{
public:
    char IsCached;               // +0x00
    char unknown_01[3];          // +0x01
    char FinalResult[0x14];      // +0x04
    ShaState_0069DB30 Acc;               // +0x18
    int Length;                  // +0x2C
    int PartialCount;            // +0x30
    char Partial[0x40];          // +0x34

    void FUN_0069DB30(const void* source, ShaState_0069DB30& acc) const;
};
GG_STATIC_ASSERT(offsetof(SHAState_0069DB30, Acc) == 0x18);
GG_STATIC_ASSERT(offsetof(SHAState_0069DB30, PartialCount) == 0x30);
GG_STATIC_ASSERT(offsetof(SHAState_0069DB30, Partial) == 0x34);

inline unsigned long ByteSwap32(unsigned long value)
{
    return (((value << 16) | (value & 0xFF00)) << 8) | (unsigned char)(value >> 24) | ((unsigned short)((value >> 8) & 0xFF00));
}

inline unsigned long Rotl32(unsigned long value, int bits)
{
    return (value << bits) | (value >> (32 - bits));
}

inline unsigned long Function(int index, unsigned long x, unsigned long y, unsigned long z)
{
    if (index < 20) return ((y ^ z) & x) ^ z;
    if (index >= 40 && index < 60) return ((x | y) & z) | (x & y);
    return x ^ y ^ z;
}

inline unsigned long Constant(int index)
{
    if (index < 20) return 0x5A827999UL;
    if (index < 40) return 0x6ED9EBA1UL;
    return (index < 60) ? 0x8F1BBCDCUL : 0xCA62C1D6UL;
}

// FUNCTION: GAMEMD 0x69DB30
void SHAState_0069DB30::FUN_0069DB30(const void* source, ShaState_0069DB30& acc) const
{
    unsigned long block[80];
    const unsigned long* data = (const unsigned long*)source;

    int index;
    for (index = 0; index < 16; index++) {
        block[index] = ByteSwap32(*data++);
    }
    for (index = 16; index < 80; index++) {
        block[index] = Rotl32(block[index - 3] ^ block[index - 8] ^ block[index - 16] ^ block[index - 14], 1);
    }

    ShaState_0069DB30 work = acc;

    for (unsigned int round = 0; round < 80; round++) {
        unsigned long temp = Rotl32(work.Long[0], 5) + Function(round, work.Long[1], work.Long[2], work.Long[3]) + work.Long[4] + block[round] + Constant(round);
        work.Long[4] = work.Long[3];
        work.Long[3] = work.Long[2];
        work.Long[2] = Rotl32(work.Long[1], 30);
        work.Long[1] = work.Long[0];
        work.Long[0] = temp;
    }

    acc.Long[0] += work.Long[0];
    acc.Long[1] += work.Long[1];
    acc.Long[2] += work.Long[2];
    acc.Long[3] += work.Long[3];
    acc.Long[4] += work.Long[4];
}
