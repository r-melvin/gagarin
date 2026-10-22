// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
// RTTI: vtable 0x7ECF2C is preceded by COL 0x804E70, whose type descriptor
// 0x829778 names .?AVLCWPipe@@. The table words are 0x552390, 0x5522D0,
// 0x477740, 0x631CC0, 0x5520A0: slots 2/3 are inherited from Pipe, slots 1
// and 4 are this class's overrides of Pipe slots +0x04 and +0x10. The table
// address is stored only at 0x55201A (constructor entry 0x551FF0), 0x552066 and 0x552396.
// Member offsets are read from 0x5520A0/0x5522D0: `CMP [ESI+0xC],1` (mode),
// `[ESI+0x10]` (staged byte count), `[ESI+0x14]`/`[ESI+0x18]` (the two
// buffers freed by the destructor), `[ESI+0x1C]` (block size), and the block
// header at `LEA [ESI+0x24]` read as words +0x24 (compressed count, reset
// to 0xFFFF) and +0x26 (uncompressed count). +0x20 is written by the
// recovered constructor 0x551FF0 at instruction 0x552030 and unread by the
// other recovered methods.
#ifndef GG_MATCH_CORE_LCW_PIPE_H
#define GG_MATCH_CORE_LCW_PIPE_H

#include "../_layout/pipe.h"

// FUNCTION: GAMEMD 0x551E50 (decl; reloc) -- LCW compress, __fastcall
// (source ECX, destination EDX, count pushed); result used as a word.
unsigned int __fastcall FUN_00551E50(const void* source, void* destination,
                                     unsigned int count);
// FUNCTION: GAMEMD 0x551C60 (decl; reloc) -- LCW uncompress, __fastcall
// (source ECX, destination EDX, a literal 0 pushed).
void __fastcall FUN_00551C60(const void* source, void* destination, int length);

// The 4-byte header that prefixes every compressed block.
struct LCWBlockHeader
{
    unsigned short CompCount;     // +0x00
    unsigned short UncompCount;   // +0x02
};
GG_STATIC_ASSERT(offsetof(LCWBlockHeader, CompCount) == 0);
GG_STATIC_ASSERT(offsetof(LCWBlockHeader, UncompCount) == 2);
GG_STATIC_ASSERT(sizeof(LCWBlockHeader) == 4);

class LCWPipe : public Pipe
{
public:
    enum CompControl { COMPRESS = 0, DECOMPRESS = 1 };

    int            Control;       // +0x0C  1 = decompressing
    int            Counter;       // +0x10  bytes staged in Buffer
    char*          Buffer;        // +0x14
    char*          Buffer2;       // +0x18
    int            BlockSize;     // +0x1C
    int            unknown_20;    // +0x20
    LCWBlockHeader BlockHeader;   // +0x24

    // FUNCTION: GAMEMD 0x551FF0
    LCWPipe(CompControl control, int blocksize);
    // FUNCTION: GAMEMD 0x552060
    virtual ~LCWPipe();
    // Slot +0x04 override (Flush); name kept to override Pipe's slot.
    // FUNCTION: GAMEMD 0x5522D0
    virtual int FUN_00631D30();
    // Slot +0x10 override: source pointer and byte count.
    // FUNCTION: GAMEMD 0x5520A0
    virtual int FUN_00631D10(int first, int second);
};

GG_STATIC_ASSERT(offsetof(LCWPipe, Control)     == 0x0C);
GG_STATIC_ASSERT(offsetof(LCWPipe, Counter)     == 0x10);
GG_STATIC_ASSERT(offsetof(LCWPipe, Buffer)      == 0x14);
GG_STATIC_ASSERT(offsetof(LCWPipe, Buffer2)     == 0x18);
GG_STATIC_ASSERT(offsetof(LCWPipe, BlockSize)   == 0x1C);
GG_STATIC_ASSERT(offsetof(LCWPipe, unknown_20)  == 0x20);
GG_STATIC_ASSERT(offsetof(LCWPipe, BlockHeader) == 0x24);
// Observed field extent through +0x27; complete retail object size is unproven.
GG_STATIC_ASSERT(sizeof(LCWPipe) == 0x28);

// VTABLE: GAMEMD 0x7ECF2C -- [0x552390, 0x5522D0, 0x477740, 0x631CC0, 0x5520A0]

#endif // GG_MATCH_CORE_LCW_PIPE_H
