// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference
//   Every body below was written against the retail disassembly of the user's
//   gamemd.exe v1.001 read through the local Ghidra CLI. EA's GPLv3 RA1 release
//   (CODE/RNDSTRAW.CPP, CODE/SHA.H) supplied function and member NAMES and the
//   algorithm's shape only; nothing is transcribed from it.
//
// RandomStraw - the whole retail translation unit, bodies ascending by address.

#include "random_straw.h"

// ---------------------------------------------------------------------------
// The shapes retail expands at every use site.
// ---------------------------------------------------------------------------

// The SHA-1 engine's constructor. Retail's store order - the IsCached byte,
// then Length, then PartialCount, then the five chaining seeds - is the
// initialiser list followed by the body, so it is written that way.
__forceinline SHAEngine::SHAEngine() : IsCached(false), Length(0), PartialCount(0)
{
    Acc[0] = GG_SHA_SA;
    Acc[1] = GG_SHA_SB;
    Acc[2] = GG_SHA_SC;
    Acc[3] = GG_SHA_SD;
    Acc[4] = GG_SHA_SE;
}

// Clear the object back to its post-construction state, so no seed material is
// left behind. The pool clear is a constant-sized dword-aligned memset, which
// is where retail's `REP STOSD` of 0x40 dwords comes from.
__forceinline void RandomStraw::ResetInline()
{
    SeedBits = 0;
    Current = 0;
    memset(Random, '\0', sizeof(Random));
}

// Hash the seed pool over itself twenty bytes at a time, so every seed bit ends
// up influencing every other one. `tocopy` is an unsigned comparison because
// both arms are sizeof expressions, which is what makes 0x661BDD a `JBE`.
__forceinline void RandomStraw::ScrambleSeedInline()
{
    SHAEngine sha;

    for (int index = 0; index < sizeof(Random); index++) {
        char digest[20];

        sha.Hash(&Random[0], sizeof(Random));
        sha.Result(digest);

        int tocopy = sizeof(digest) < (sizeof(Random) - index) ? sizeof(digest) : (sizeof(Random) - index);
        FUN_007CA090(((char*)&Random[0]) + index, digest, tocopy);
    }
}

// Fold one bit of entropy into the pool. The byte index is a signed divide by
// eight wrapped into the pool's length, which is the `CDQ; AND EDX,7; SAR 3;
// AND EAX,0xFF` run at 0x66177C. The bit is only formed inside the guarded arm,
// which is where retail sinks it too.
__forceinline void RandomStraw::SeedBitInline(int seed)
{
    char* ptr = ((char*)&Random[0]) + ((SeedBits / 8) % sizeof(Random));

    if (seed & 0x01) {
        char frac = (char)(1 << (SeedBits & (8 - 1)));
        *ptr ^= frac;
    }
    SeedBits++;

    if (SeedBits == (sizeof(Random) * 8)) {
        ScrambleSeedInline();
    }
}

// ---------------------------------------------------------------------------
// The retail bodies, ascending by address.
// ---------------------------------------------------------------------------

// Build a RandomStraw in a known - and cryptographically useless - state. The
// Straw base's two chain links are zeroed and its vtable seated first, then the
// two counters are initialised, then the 32 generators are default-constructed
// in a loop, then the derived vtable is seated and the pool cleared.
// FUNCTION: GAMEMD 0x6616B0
RandomStraw* RandomStraw::Construct()
{
    ChainTo = 0;
    ChainFrom = 0;
    Vtable = &GG_VTABLE_STRAW;

    SeedBits = 0;
    Current = 0;

    RandomClass* gen = &Random[0];
    for (int index = 0; index < 32; index++) {
        gen->Construct(0, 0);
        gen++;
    }

    Vtable = &GG_VTABLE_RANDOMSTRAW;
    ResetInline();
    return this;
}

// Tear a RandomStraw down. The pool is cleared before the base runs so that no
// sensitive seed material survives in the freed memory.
// FUNCTION: GAMEMD 0x661700
void RandomStraw::Destruct()
{
    Vtable = &GG_VTABLE_RANDOMSTRAW;
    ResetInline();
    ((Straw*)this)->Straw::~Straw();
}

// The out-of-line copy of the pool clear.
// FUNCTION: GAMEMD 0x661730
void RandomStraw::Reset()
{
    ResetInline();
}

// How many more seed bits the pool still wants. `total` is bound to a const int
// rather than left as the unsigned sizeof product, which is what makes the
// compare at 0x661759 a signed `JGE`.
// FUNCTION: GAMEMD 0x661750
int RandomStraw::Seed_Bits_Needed() const
{
    const int total = sizeof(Random) * 8;
    if (SeedBits < total) {
        return total - SeedBits;
    }
    return 0;
}

// The out-of-line copy of the single-bit seed step.
// FUNCTION: GAMEMD 0x661770
void RandomStraw::Seed_Bit(int seed)
{
    SeedBitInline(seed);
}

// Feed eight bits, lowest first. The shift is an eight-bit `SAR` on the
// parameter's own stack home because the parameter really is a char.
// FUNCTION: GAMEMD 0x661850
void RandomStraw::Seed_Byte(char seed)
{
    for (int index = 0; index < 8; index++) {
        SeedBitInline(seed);
        seed >>= 1;
    }
}

// Feed sixteen bits, lowest first.
// FUNCTION: GAMEMD 0x661960
void RandomStraw::Seed_Short(short seed)
{
    for (int index = 0; index < (sizeof(seed) * 8); index++) {
        SeedBitInline(seed);
        seed >>= 1;
    }
}

// Feed a full thirty-two bits, lowest first.
// FUNCTION: GAMEMD 0x661A60
void RandomStraw::Seed_Long(long seed)
{
    for (int index = 0; index < (sizeof(seed) * 8); index++) {
        SeedBitInline(seed);
        seed >>= 1;
    }
}

// The out-of-line copy of the SHA-1 pool scramble.
// FUNCTION: GAMEMD 0x661B70
void RandomStraw::Scramble_Seed()
{
    ScrambleSeedInline();
}

// Serve random bytes. A null buffer or a non-positive length is handed back to
// the base straw, which is what terminates the chain; otherwise the generators
// are walked round-robin, one byte per call, and the pool never runs dry.
// FUNCTION: GAMEMD 0x661C10
int RandomStraw::Get(void* source, int slen)
{
    if (source == 0 || slen < 1) {
        return ((Straw*)this)->Straw::FUN_006C98E0((int)source, slen);
    }

    int total = 0;
    while (slen > 0) {
        *(char*)source = (char)Random[Current++].Next();
        Current = Current % (sizeof(Random) / sizeof(Random[0]));
        source = (char*)source + sizeof(char);
        slen--;
        total++;
    }
    return total;
}

// Vtable slot zero: the scalar deleting thunk, with the destructor expanded
// into it rather than called. Retail carries both this copy and the out-of-line
// one at 0x661700.
// FUNCTION: GAMEMD 0x661C70
void* RandomStraw::ScalarDeletingDestructor(unsigned char flags)
{
    Vtable = &GG_VTABLE_RANDOMSTRAW;
    ResetInline();
    ((Straw*)this)->Straw::~Straw();
    if (flags & 0x01) {
        FUN_007C8B3D(this);
    }
    return this;
}
