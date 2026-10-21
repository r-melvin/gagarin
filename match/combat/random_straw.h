// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference
//   Every offset, call target and vtable address below was read numerically off
//   the user's own retail gamemd.exe v1.001 through the local Ghidra CLI. EA's
//   GPLv3 Red Alert 1 release (CODE/RNDSTRAW.H, CODE/RNDSTRAW.CPP, CODE/SHA.H,
//   CODE/STRAW.H) was read for member NAMES and algorithm shape only; nothing is
//   transcribed from it and every offset is re-derived from the binary. No YRpp
//   header was consulted for this cluster.
//
// The RandomStraw cluster at 0x6616B0-0x661CA9 - one complete retail
// translation unit (Westwood's RNDSTRAW.CPP, carried near-verbatim from RA1
// into the MSVC6 build). RandomStraw is the cryptographic random-number
// terminator of the Straw chain: it accumulates 2048 seed bits into a 256-byte
// pool that doubles as an array of 32 RandomClass generators, SHA-1 scrambles
// the pool once it is full, and then serves bytes from the generators forever.
//
// CLASS IDENTIFICATION (the word four bytes before each vtable is the complete
// object locator; its field at +0x0C is the type descriptor; the name string
// starts eight bytes into that):
//   0x7E61F0 -> 0x7FFD38 -> 0x81BFB0 -> ".?AVStraw@@"
//   0x7F0AFC -> 0x8088F0 -> 0x839990 -> ".?AVRandomStraw@@"
// Both vtables are three slots wide:
//   Straw       0x7E61F0: {0x4AEC10 dtor thunk, 0x6C9890 Get_From, 0x6C98E0 Get}
//   RandomStraw 0x7F0AFC: {0x661C70 dtor thunk, 0x6C9890 Get_From, 0x661C10 Get}
// so RandomStraw overrides slot 0 and slot 2 and inherits slot 1.
//
// HOW THE ADDRESS RUN WAS FOUND. The cluster was swept as raw bytes
// (`ghidra memory read` + `objdump -D -b binary -m i386`) and its entry points
// taken from the 0x90 pad runs that end on a four-byte boundary. The Ghidra
// function list knew five of the eleven bodies (0x6616B0, 0x661770, 0x661850,
// 0x661C10, 0x661C70); the sweep recovered Reset, Seed_Bits_Needed, Seed_Short,
// Seed_Long, Scramble_Seed and the out-of-line destructor as well. The
// out-of-line destructor at 0x661700 has NO pad at all in front of it - it
// begins on the four-byte boundary immediately after the constructor's `RET` -
// so an aligned address directly after a terminating RET is an entry candidate
// in its own right, not only a pad-preceded one.
//
// MODELLING NOTE. Following this tree's convention for Westwood library
// classes, RandomStraw is written as ONE flat struct carrying the Straw base's
// three words inline and its vtable pointer as an ordinary `void* Vtable`
// member at +0x00. Slot zero is an ordinary method holding the scalar deleting
// thunk rather than a C++ virtual destructor, which keeps the two seat stores
// (the Straw seat then the RandomStraw seat) under our control and avoids the
// unwind frame `/GX` would otherwise wrap around a member-array constructor.
#ifndef GG_MATCH_COMBAT_RANDOM_STRAW_H
#define GG_MATCH_COMBAT_RANDOM_STRAW_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/straw.h"

// ---------------------------------------------------------------------------
// Vtable stand-ins. Only the relocation is emitted, so one extern symbol per
// retail vtable address reproduces the `MOV dword ptr [reg],imm32` seat store.
// ---------------------------------------------------------------------------
// VTABLE: GAMEMD 0x7E61F0  Straw
extern "C" void* GG_VTABLE_STRAW;
// VTABLE: GAMEMD 0x7F0AFC  RandomStraw
extern "C" void* GG_VTABLE_RANDOMSTRAW;

// ---------------------------------------------------------------------------
// CRT primitives, declared so cl emits reloc-normalised calls.
// ---------------------------------------------------------------------------
// LIBRARY: GAMEMD 0x7C8B3D  operator delete
extern "C" void  __cdecl FUN_007C8B3D(void* block);
// LIBRARY: GAMEMD 0x7CA090  CRT memmove
extern "C" void* __cdecl FUN_007CA090(void* dest, const void* src, unsigned int count);

// `memset` is left to the compiler: retail's `Reset` clears the 256-byte pool
// with an inline `REP STOSD` of 0x40 dwords, which is exactly cl's /Oi
// expansion of a constant-sized, dword-aligned memset. Declared here rather
// than pulled from <string.h> so the translation unit stays self-contained.
extern "C" void* __cdecl memset(void* dest, int value, size_t count);
#pragma intrinsic(memset)

// ---------------------------------------------------------------------------
// RandomClass - the 8-byte generator RandomStraw keeps 32 of.
//
// Size read off `LEA ECX,[ESI+EAX*8+0x14]` in RandomStraw::Get (0x661C33) and
// off the constructor loop's `ADD EBX,8` stride at 0x6616DB. The constructor at
// 0x65C890 takes two dwords and stores them at +0x00 and +0x04; the extractor
// at 0x65C8B0 reads +0x04, increments it, and returns the next value in EAX.
// Both are declared, never defined: only the call relocation matters and the
// differ normalises it.
// ---------------------------------------------------------------------------
struct RandomClass
{
    unsigned long Seed;   // +0x0000
    unsigned long Index;  // +0x0004

    // FUNCTION: GAMEMD 0x65C890  RandomClass::RandomClass
    void Construct(unsigned long seed, unsigned long index);
    // FUNCTION: GAMEMD 0x65C8B0  RandomClass::operator()
    int  Next();
};

GG_STATIC_ASSERT(offsetof(RandomClass, Seed) == 0x00);
GG_STATIC_ASSERT(offsetof(RandomClass, Index) == 0x04);
GG_STATIC_ASSERT(sizeof(RandomClass) == 0x08);

// ---------------------------------------------------------------------------
// SHAEngine - the SHA-1 engine Scramble_Seed builds on its own frame.
//
// Every offset here is read off the inlined constructor at 0x661B7E-0x661BB1,
// whose frame slot for the engine is `[ESP+0x14]` (base-relative):
//   BYTE  [+0x00] = 0                       IsCached
//   DWORD [+0x18] = 0x67452301 .. [+0x28] = 0xC3D2E1F0   Acc[0..4]
//   DWORD [+0x2C] = 0                       Length
//   DWORD [+0x30] = 0                       PartialCount
// and the total is pinned by the 0x88-byte frame of Scramble_Seed, which holds
// exactly the 20-byte digest buffer plus this object: 0x88 - 0x14 = 0x74.
// ---------------------------------------------------------------------------
struct SHAEngine
{
    bool          IsCached;        // +0x0000
    unsigned long FinalResult[5];  // +0x0004
    unsigned long Acc[5];          // +0x0018
    long          Length;          // +0x002C
    int           PartialCount;    // +0x0030
    char          Partial[64];     // +0x0034

    // The constructor is forced inline because retail has no out-of-line copy
    // of it: it appears expanded at every one of the five scramble sites.
    __forceinline SHAEngine();

    // FUNCTION: GAMEMD 0x69D9E0  SHAEngine::Result
    int  Result(void* result) const;
    // FUNCTION: GAMEMD 0x69D960  SHAEngine::Hash
    void Hash(const void* data, long length);
};

GG_STATIC_ASSERT(offsetof(SHAEngine, IsCached) == 0x00);
GG_STATIC_ASSERT(offsetof(SHAEngine, FinalResult) == 0x04);
GG_STATIC_ASSERT(offsetof(SHAEngine, Acc) == 0x18);
GG_STATIC_ASSERT(offsetof(SHAEngine, Length) == 0x2C);
GG_STATIC_ASSERT(offsetof(SHAEngine, PartialCount) == 0x30);
GG_STATIC_ASSERT(offsetof(SHAEngine, Partial) == 0x34);
GG_STATIC_ASSERT(sizeof(SHAEngine) == 0x74);

// The five SHA-1 chaining seeds, as they are stored at 0x661B8A-0x661BB1.
#define GG_SHA_SA 0x67452301L
#define GG_SHA_SB 0xEFCDAB89L
#define GG_SHA_SC 0x98BADCFEL
#define GG_SHA_SD 0x10325476L
#define GG_SHA_SE 0xC3D2E1F0L

// ---------------------------------------------------------------------------
// RandomStraw, flattened over its Straw base.
//
// Offsets, all read numerically off the run:
//   +0x00 Vtable     `MOV dword ptr [ESI],0x7E61F0` / `0x7F0AFC` at 0x6616C3
//                    and 0x6616F1.
//   +0x04 ChainTo    `MOV dword ptr [ESI+0x4],EDI` (EDI=0) at 0x6616BD.
//   +0x08 ChainFrom  `MOV dword ptr [ESI+0x8],EDI` at 0x6616C0.
//   +0x0C SeedBits   `MOV ECX,dword ptr [EDI+0xC]` at 0x661779, compared to
//                    0x800 at 0x6617AE and at 0x661753.
//   +0x10 Current    `MOV EAX,dword ptr [ESI+0x10]` at 0x661C30, masked with
//                    0x1F at 0x661C45.
//   +0x14 Random[32] `LEA EBX,[ESI+0x14]` at 0x6616CF, `REP STOSD` of 0x40
//                    dwords at 0x6616F7, `LEA ECX,[ESI+EAX*8+0x14]` at
//                    0x661C33.
// Size 0x14 + 32*8 = 0x114.
// ---------------------------------------------------------------------------
struct RandomStraw
{
    void*        Vtable;      // +0x0000
    RandomStraw* ChainTo;     // +0x0004
    RandomStraw* ChainFrom;   // +0x0008
    int          SeedBits;    // +0x000C
    int          Current;     // +0x0010
    RandomClass  Random[32];  // +0x0014

    // Address-scoped forwarding view of Straw slot 2. Cleanup calls use the
    // canonical Straw destructor through the confirmed 12-byte prefix.
    // FUNCTION: GAMEMD 0x6C98E0  Straw::Get
    int  StrawGet(void* source, int slen);

    // The three shapes retail keeps BOTH out of line and expanded at every use
    // site. Each is written once as a forced-inline member and the out-of-line
    // address gets its own one-line wrapper below, which is the recipe this
    // tree has banked for a helper that exists in both forms.
    __forceinline void ResetInline();
    __forceinline void ScrambleSeedInline();
    __forceinline void SeedBitInline(int seed);

    RandomStraw* Construct();
    void  Destruct();
    void  Reset();
    int   Seed_Bits_Needed() const;
    void  Seed_Bit(int seed);
    void  Seed_Byte(char seed);
    void  Seed_Short(short seed);
    void  Seed_Long(long seed);
    void  Scramble_Seed();
    int   Get(void* source, int slen);
    void* ScalarDeletingDestructor(unsigned char flags);
};

GG_STATIC_ASSERT(offsetof(RandomStraw, Vtable) == 0x00);
GG_STATIC_ASSERT(offsetof(RandomStraw, ChainTo) == 0x04);
GG_STATIC_ASSERT(offsetof(RandomStraw, ChainFrom) == 0x08);
GG_STATIC_ASSERT(offsetof(RandomStraw, SeedBits) == 0x0C);
GG_STATIC_ASSERT(offsetof(RandomStraw, Current) == 0x10);
GG_STATIC_ASSERT(offsetof(RandomStraw, Random) == 0x14);
GG_STATIC_ASSERT(sizeof(RandomStraw) == 0x114);
// 2048 seed bits is exactly the pool, which is what 0x6617AE compares against.
GG_STATIC_ASSERT(sizeof(((RandomStraw*)0)->Random) * 8 == 0x800);

#endif  // GG_MATCH_COMBAT_RANDOM_STRAW_H
