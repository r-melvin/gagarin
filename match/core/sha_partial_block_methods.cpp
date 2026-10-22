// Provenance: own-binary-via-Ghidra
// Partial-block buffering step of the SHA-1 engine whose field offsets are
// pinned in combat/random_straw.h (Acc +0x18, Length +0x2C,
// PartialCount +0x30, Partial[64] +0x34). This TU-local view adds the
// out-of-line helpers called from 0x69D960.
// Pinned here by 0x69D8C0: `LEA EDI,[EDX+EBX+0x34]`, `[EBX+0x30]`,
// `LEA EAX,[EBX+0x18]`, `[EBX+0x2C]`, block size 0x40.
#include "../_rt/gg_static_assert.h"
#include <stddef.h>
#include <string.h>

struct ShaEngineView_0069D8C0
{
    bool          IsCached;        // +0x00
    unsigned long FinalResult[5];  // +0x04
    unsigned long Acc[5];          // +0x18
    long          Length;          // +0x2C
    int           PartialCount;    // +0x30
    char          Partial[64];     // +0x34

    void FUN_0069D8C0(const void*& data, long& length);
    // FUNCTION: GAMEMD 0x69DB30 -- one 64-byte block into the accumulator.
    void FUN_0069DB30(const void* block, unsigned long* acc) const;
};

GG_STATIC_ASSERT(offsetof(ShaEngineView_0069D8C0, Acc) == 0x18);
GG_STATIC_ASSERT(offsetof(ShaEngineView_0069D8C0, Length) == 0x2C);
GG_STATIC_ASSERT(offsetof(ShaEngineView_0069D8C0, PartialCount) == 0x30);
GG_STATIC_ASSERT(offsetof(ShaEngineView_0069D8C0, Partial) == 0x34);

// FUNCTION: GAMEMD 0x69D8C0
void ShaEngineView_0069D8C0::FUN_0069D8C0(const void*& data, long& length)
{
    if (length == 0 || data == 0) return;
    if (PartialCount == 0 && length >= 64) return;

    int take = 64 - PartialCount;
    if (length < take) take = length;
    memcpy(&Partial[PartialCount], data, take);
    data = ((const char*)data) + take;
    PartialCount += take;
    length -= take;

    if (PartialCount == 64) {
        FUN_0069DB30(&Partial[0], Acc);
        Length += 64;
        PartialCount = 0;
    }
}
