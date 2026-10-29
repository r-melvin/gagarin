// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm @ 0x65C780,
//   0x65C7E0). Names cross-checked against YRpp (each offset reconfirmed against the user's binary).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x65C780  Randomizer::Random       (__thiscall)
//   FUNCTION: GAMEMD 0x65C7E0  Randomizer::RandomRanged (__thiscall)

#include "randomizer.h"

// GLOBAL: GAMEMD 0x839644 -- first key table
extern int DAT_00839644[4];
// GLOBAL: GAMEMD 0x839694 -- second key table
extern int DAT_00839694[4];

// Keyed mixing step shared by the seeding loop below and the generator at 0x65C8B0.
struct RandomizerMix
{
    int Left;
    int Counter;

    int Step()
    {
        int right = Counter;
        int left = Left;
        Counter = right + 1;
        for (int i = 0; i < 4; i++) {
            int saved = right;
            int x = DAT_00839644[i] ^ right;
            int lo = x & 0xFFFF;
            int hi = x >> 16;
            int m = ~(hi * hi) + lo * lo;
            right = (m >> 16) | (m << 16);
            right ^= DAT_00839694[i];
            right += hi * lo;
            right ^= left;
            left = saved;
        }
        return right;
    }
};

// FUNCTION: GAMEMD 0x65C6D0  (__thiscall, RET 4)
// Seed the table: each entry is the next output of the mixing step, keyed by the seed and a running counter.
Randomizer::Randomizer(int seed)
{
    Next1 = 0;
    Next2 = 103;
    RandomizerMix mix;
    mix.Left = seed;
    mix.Counter = 0;
    for (int n = 0; n < 250; n++)
        Table[n] = mix.Step();
    unknown_00 = false;
}

// FUNCTION: GAMEMD 0x65C780  (__thiscall)
// Advance the XOR lagged-table generator one step and return the new value.
//   if (disabled) return 0;
//   Table[Next1] ^= Table[Next2];          // mix the two lagged taps
//   result = Table[Next1];                  // the value produced
//   if (++Next1 >= 250) Next1 = 0;          // wrap both cursors at 250
//   if (++Next2 >= 250) Next2 = 0;
// The compiler re-reads Next1/Next2 from memory after the table store (the
// store can alias the cursors), so they are accessed directly, not cached.
int Randomizer::Random()
{
    if (this->unknown_00)
        return 0;

    this->Table[this->Next1] ^= this->Table[this->Next2];

    int next1 = this->Next1;
    int next2 = this->Next2;
    int result = this->Table[next1];
    ++next1;
    ++next2;
    this->Next1 = next1;
    this->Next2 = next2;
    if (next1 >= 250)
        this->Next1 = 0;
    if (next2 >= 250)
        this->Next2 = 0;

    return result;
}

// FUNCTION: GAMEMD 0x65C7E0  (__thiscall)
//
// Uniform integer in [min,max] by rejection sampling. Orders the bounds into
// lo/hi, builds a power-of-two-minus-one mask covering the magnitude, then
// draws generator steps (inlined here in retail) and masks until one falls
// within range, finally biasing by `lo`.
//
// Shape notes: the bounds are ordered into two fresh locals (`lo = min;
// hi = max; if (min > max) { lo = max; hi = min; }`) — that is retail's
// `MOV EBX,EAX` ahead of the equality test and the two-move swap
// (`MOV EBX,ECX; MOV ECX,EAX`); a temp-swap of the parameters costs a third
// move through ESI. The draw is a real inlined call (RandomStep in the
// header), whose return in EAX is what puts the masked pick in EAX and
// `lo` in EBX (16.7% with the body hand-expanded, where cl keeps `min` in
// EAX and the pick in EDI). The `pick = magnitude + 1; while (pick >
// magnitude)` pre-test gives `LEA EAX,[EDI+1]; CMP EAX,EDI; JLE`.
//
// The draw is two statements, the step result and then the mask applied to
// it. Written as one expression (`pick = RandomStep() & mask`) cl swaps the
// ESI/EDI homes of the magnitude and the step's table temporaries (77.3%);
// the two-statement form gives retail's assignment. Found by a permuter run
// under the current /Gr flag set and reduced by hand to this one change.
int Randomizer::RandomRanged(int min, int max)
{
    int lo = min;
    int hi = max;
    if (min == max)
        return min;
    if (min > max)
    {
        lo = max;
        hi = min;
    }

    int magnitude = hi - lo;

    // Highest set bit position of the magnitude (>= 0).
    int highbit = 31;
    while ((magnitude & (1 << highbit)) == 0 && highbit > 0)
        --highbit;

    // Mask covering bits 0..highbit.
    int mask = ~(-1 << (highbit + 1));

    // Draw until the masked value lands within the magnitude. `pick` starts one
    // past the magnitude so the while-guard always enters in the normal case.
    int pick = magnitude + 1;
    while (pick > magnitude)
    {
        pick = this->RandomStep();
        pick &= mask;
    }

    return pick + lo;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x839644
int DAT_00839644[4] = {-1163302777, 504877868, 62708796, 255054258};
// GLOBAL: GAMEMD 0x839694
int DAT_00839694[4] = {1259289432, -394989373, 1767228838, 1437059654};
// END defined globals
