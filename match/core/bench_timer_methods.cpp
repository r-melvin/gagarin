// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// A small timing accumulator. Its neighbour at 0x4319D0 stores a start stamp
// at +0x00/+0x04 and adds an elapsed span into +0x08 while bumping +0x0C and
// +0x10; the two leaves below read and clear exactly those three dwords.
// The class name and member names are descriptive; no allocation site was
// found, so the object size is not asserted.
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class BenchTimer
{
public:
    void Reset();
    unsigned int Average();

    unsigned int StartLo;   // +0x00
    unsigned int StartHi;   // +0x04
    unsigned int Total;     // +0x08
    unsigned int Count;     // +0x0C
    unsigned int Samples;   // +0x10
};
GG_STATIC_ASSERT(offsetof(BenchTimer, StartLo) == 0x00);
GG_STATIC_ASSERT(offsetof(BenchTimer, StartHi) == 0x04);
GG_STATIC_ASSERT(offsetof(BenchTimer, Total)   == 0x08);
GG_STATIC_ASSERT(offsetof(BenchTimer, Count)   == 0x0C);
GG_STATIC_ASSERT(offsetof(BenchTimer, Samples) == 0x10);

// FUNCTION: GAMEMD 0x431920
void BenchTimer::Reset()
{
    Total = 0;
    Count = 0;
    Samples = 0;
}

// FUNCTION: GAMEMD 0x431A10
unsigned int BenchTimer::Average()
{
    if (Count != 0) {
        return Total / Count;
    }
    return 0;
}
