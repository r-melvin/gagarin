// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | behaviour-confirmed-name
// RTTI type names from the pinned image: 0x7EB754 .?AVCacheStraw@@,
// 0x7E6200 .?AVBufferPipe@@, 0x7E61E0 .?AVBufferStraw@@. The pipe and
// straw bodies at 0x4A2030/0x4A20B0 have no table reference in the image, so
// their classes carry address placeholders (they feed the block hash
// 0x4A1DE0).
//
// Member evidence:
//   HashPipe/HashStraw: `LEA ECX,[ESI+0xC]; CALL 0x4A1DE0` -- the hash state is embedded at
//     +0x0C. 0x4A1DE0 reads +0x04 of that state as a fill count and stages
//     bytes from +0x08; 0x4A2060 reads the state's +0x00 as the running value.
//   CacheStraw (0x4A2780): +0x0C buffer pointer and +0x10 size handed to the
//     base Get, +0x18 read index, +0x1C bytes held.
//   BufferPipe/BufferStraw (0x7BA3C0/0x7BA4D0): +0x0C buffer pointer, +0x10
//     size (0 = unbounded), +0x18 index.
// The three-word buffer at +0x0C reuses MemoryBuffer's layout; whether the
// retail member is that class is not proven by these bodies alone.
#ifndef GG_MATCH_PLATFORM_BUFFER_STRAWS_H
#define GG_MATCH_PLATFORM_BUFFER_STRAWS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"
#include "../_layout/memory_buffer.h"

// LIBRARY: GAMEMD 0x7CA090 (decl; reloc) -- CRT memmove.
extern "C" void* __cdecl memmove(void* destination, const void* source, unsigned int count);

class BlockHashView
{
public:
    // FUNCTION: GAMEMD 0x4A1DE0 (decl; reloc) -- feed a byte run.
    int Feed(const void* data, int length);

    int  unknown_00;          // +0x00 running value
    int  StageCount;          // +0x04
    char unknown_8[4];      // +0x08
};
GG_STATIC_ASSERT(offsetof(BlockHashView, StageCount)  == 0x04);
GG_STATIC_ASSERT(offsetof(BlockHashView, unknown_8) == 0x08);

class HashPipe_004A2030 : public Pipe
{
public:
    // FUNCTION: GAMEMD 0x4A2030
    virtual int FUN_00631D10(int first, int second);

    BlockHashView Hash;   // +0x0C
};
GG_STATIC_ASSERT(offsetof(HashPipe_004A2030, Hash) == 0x0C);

class HashStraw_004A20B0 : public Straw
{
public:
    // FUNCTION: GAMEMD 0x4A20B0
    virtual int FUN_006C98E0(void* first, int second);

    BlockHashView Hash;   // +0x0C
};
GG_STATIC_ASSERT(offsetof(HashStraw_004A20B0, Hash) == 0x0C);

class CacheStraw : public Straw
{
public:
    // FUNCTION: GAMEMD 0x4A2780
    virtual int FUN_006C98E0(void* first, int second);   // slot 2

    MemoryBuffer Buffer;  // +0x0C
    int          Index;   // +0x18
    int          Length;  // +0x1C
};
GG_STATIC_ASSERT(offsetof(CacheStraw, Buffer) == 0x0C);
GG_STATIC_ASSERT(offsetof(CacheStraw, Index)  == 0x18);
GG_STATIC_ASSERT(offsetof(CacheStraw, Length) == 0x1C);
// VTABLE: GAMEMD 0x7EB754 -- [0x52AE70, 0x6C9890, 0x4A2780]

class BufferPipe : public Pipe
{
public:
    // FUNCTION: GAMEMD 0x7BA3C0
    virtual int FUN_00631D10(int first, int second);   // slot 4

    MemoryBuffer Buffer;  // +0x0C
    int          Index;   // +0x18
};
GG_STATIC_ASSERT(offsetof(BufferPipe, Buffer) == 0x0C);
GG_STATIC_ASSERT(offsetof(BufferPipe, Index)  == 0x18);
// VTABLE: GAMEMD 0x7E6200 -- [0x4AECA0, 0x631D30, 0x477740, 0x631CC0, 0x7BA3C0]

class BufferStraw : public Straw
{
public:
    // Inlined at 0x6996EA..0x699720 and 0x69977F..0x6997B5.
    BufferStraw(void* data, int size) : Buffer(data, size), Index(0) {}
    // FUNCTION: GAMEMD 0x7BA4D0
    virtual int FUN_006C98E0(void* first, int second);   // slot 2

    MemoryBuffer Buffer;  // +0x0C
    int          Index;   // +0x18
};
GG_STATIC_ASSERT(sizeof(BufferStraw) == 0x1C);
GG_STATIC_ASSERT(offsetof(BufferStraw, Buffer) == 0x0C);
GG_STATIC_ASSERT(sizeof(((BufferStraw*)0)->Buffer) == 0x0C);
GG_STATIC_ASSERT(offsetof(BufferStraw, Index)  == 0x18);
GG_STATIC_ASSERT(sizeof(((BufferStraw*)0)->Index) == 4);
// VTABLE: GAMEMD 0x7E61E0 -- [0x4AEC30, 0x6C9890, 0x7BA4D0]

#endif // GG_MATCH_PLATFORM_BUFFER_STRAWS_H
