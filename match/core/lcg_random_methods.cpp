// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// 0x65C640 reads and rewrites the single dword at +0x00 (`MOV EAX,[ECX]` ...
// `MOV [ECX],EAX`) and returns bits 10..24 of the new value. No table, caller
// or allocation site references it, so the class name is descriptive and no
// size is asserted.
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class LCGRandom
{
public:
    // FUNCTION: GAMEMD 0x65C640
    int operator()();

    unsigned long Seed;   // +0x00
};
GG_STATIC_ASSERT(offsetof(LCGRandom, Seed) == 0x00);

// FUNCTION: GAMEMD 0x65C640
int LCGRandom::operator()()
{
    Seed = Seed * 0x41C64E6D + 0x3039;
    return (Seed >> 10) & 0x7FFF;
}
