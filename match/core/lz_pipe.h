// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
// RTTI: vtable 0x7ED37C names .?AVLZOPipe@@ (COL before the table). Table
// words [0x55C6D0, 0x55C5E0, 0x477740, 0x631CC0, 0x55C350]: slot +0x10 is
// the Put override at 0x55C350. Member offsets from 0x55C350: `[ESI+0xC]`
// compared with 1 (mode), `[ESI+0x10]` staged count, `[ESI+0x14]`/`[ESI+0x18]`
// staging and output buffers, `[ESI+0x1C]` block size, words +0x24/+0x26
// of the block header (compressed count, reset to 0xFFFF; uncompressed count).
#ifndef GG_MATCH_CORE_LZ_PIPE_H
#define GG_MATCH_CORE_LZ_PIPE_H

#include "../_layout/pipe.h"

// FUNCTION: GAMEMD 0x55BB90 (decl; reloc) -- block compress, __fastcall
// (source ECX, length EDX; destination, out-length pointer, work buffer).
int FUN_0055BB90(const unsigned char* in, unsigned int in_len,
    unsigned char* out, unsigned int* out_len, void* work);
// FUNCTION: GAMEMD 0x55C0E0 (decl; reloc) -- block decompress, same convention.
int FUN_0055C0E0(const unsigned char* in, unsigned int in_len,
    unsigned char* out, unsigned int* out_len, void* work);

struct LZOBlockHeader
{
    unsigned short CompCount;     // +0x00
    unsigned short UncompCount;   // +0x02
};
GG_STATIC_ASSERT(offsetof(LZOBlockHeader, UncompCount) == 2);

class LZOPipe : public Pipe
{
public:
    int            Control;       // +0x0C  1 = decompressing
    int            Counter;       // +0x10
    char*          Buffer;        // +0x14
    char*          Buffer2;       // +0x18
    int            BlockSize;     // +0x1C
    int            unknown_20;    // +0x20
    LZOBlockHeader BlockHeader;   // +0x24

    // FUNCTION: GAMEMD 0x55C350
    virtual int FUN_00631D10(int first, int second);
};
GG_STATIC_ASSERT(offsetof(LZOPipe, Control) == 0x0C);
GG_STATIC_ASSERT(offsetof(LZOPipe, Counter) == 0x10);
GG_STATIC_ASSERT(offsetof(LZOPipe, Buffer) == 0x14);
GG_STATIC_ASSERT(offsetof(LZOPipe, Buffer2) == 0x18);
GG_STATIC_ASSERT(offsetof(LZOPipe, BlockSize) == 0x1C);
GG_STATIC_ASSERT(offsetof(LZOPipe, BlockHeader) == 0x24);

#endif
