// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT
// Entry-origin 0x551FF0, 0x552060, 0x5520A0, 0x5522D0 and 0x552390 (scalar deleting
// destructor, compiler-emitted), checked against the pinned retail image.
#include "lcw_pipe.h"
#include <string.h>

// FUNCTION: GAMEMD 0x551FF0
// The inline Pipe constructor zeroes the chain links; buffers are sized
// BlockSize plus a margin of at least 128 bytes.
LCWPipe::LCWPipe(CompControl control, int blocksize) :
    Control(control),
    Counter(0),
    Buffer(0),
    Buffer2(0),
    BlockSize(blocksize)
{
    int margin = BlockSize / 128 + 1;
    if (margin < 128) {
        margin = 128;
    }
    unknown_20 = margin;
    Buffer = new char[BlockSize + unknown_20];
    Buffer2 = new char[BlockSize + unknown_20];
    BlockHeader.CompCount = 0xFFFF;
}

// FUNCTION: GAMEMD 0x552060
LCWPipe::~LCWPipe()
{
    delete[] Buffer;
    Buffer = 0;
    delete[] Buffer2;
    Buffer2 = 0;
}

// FUNCTION: GAMEMD 0x5520A0
// Put: stage incoming bytes; each complete block is (de)compressed and
// passed down the chain. Returns the byte count reported by the chain.
int LCWPipe::FUN_00631D10(int first, int slen)
{
    if (first == 0 || slen < 1) {
        return Pipe::FUN_00631D10(first, slen);
    }

    int total = 0;

    if (Control == DECOMPRESS) {
        while (slen > 0) {
            if (BlockHeader.CompCount == 0xFFFF) {
                int len = (slen < sizeof(BlockHeader) - Counter)
                              ? slen : sizeof(BlockHeader) - Counter;
                memmove(Buffer + Counter, (const char*)first, len);
                first += len;
                slen -= len;
                Counter += len;
                if (Counter == sizeof(BlockHeader)) {
                    memmove(&BlockHeader, Buffer, sizeof(BlockHeader));
                    Counter = 0;
                }
            }

            if (slen > 0) {
                int len = (slen < BlockHeader.CompCount - Counter)
                              ? slen : BlockHeader.CompCount - Counter;
                memmove(Buffer + Counter, (const char*)first, len);
                Counter += len;
                slen -= len;
                first += len;
                if (Counter == BlockHeader.CompCount) {
                    FUN_00551C60(Buffer, Buffer2, 0);
                    total += Pipe::FUN_00631D10((int)Buffer2, BlockHeader.UncompCount);
                    Counter = 0;
                    BlockHeader.CompCount = 0xFFFF;
                }
            }
        }
    } else {
        if (Counter > 0) {
            int len = (slen < BlockSize - Counter) ? slen : BlockSize - Counter;
            memmove(Buffer + Counter, (const char*)first, len);
            Counter += len;
            first += len;
            slen -= len;
            if (Counter == BlockSize) {
                int clen = FUN_00551E50(Buffer, Buffer2, BlockSize);
                BlockHeader.CompCount = (unsigned short)clen;
                BlockHeader.UncompCount = (unsigned short)BlockSize;
                total += Pipe::FUN_00631D10((int)&BlockHeader, sizeof(BlockHeader));
                total += Pipe::FUN_00631D10((int)Buffer2, clen);
                Counter = 0;
            }
        }

        while (slen >= BlockSize) {
            int clen = FUN_00551E50((const char*)first, Buffer2, BlockSize);
            BlockHeader.UncompCount = (unsigned short)BlockSize;
            first += BlockSize;
            slen -= BlockSize;
            BlockHeader.CompCount = (unsigned short)clen;
            total += Pipe::FUN_00631D10((int)&BlockHeader, sizeof(BlockHeader));
            total += Pipe::FUN_00631D10((int)Buffer2, clen);
        }

        if (slen > 0) {
            memmove(Buffer, (const char*)first, slen);
            Counter = slen;
        }
    }

    return total;
}

// FUNCTION: GAMEMD 0x5522D0
// Flush: push out whatever is staged, then flush the rest of the chain.
int LCWPipe::FUN_00631D30()
{
    int total = 0;

    if (Counter > 0) {
        if (Control == DECOMPRESS) {
            if (BlockHeader.CompCount == 0xFFFF) {
                total += Pipe::FUN_00631D10((int)Buffer, Counter);
                Counter = 0;
            }
            if (Counter > 0) {
                total += Pipe::FUN_00631D10((int)&BlockHeader, sizeof(BlockHeader));
                total += Pipe::FUN_00631D10((int)Buffer, Counter);
                Counter = 0;
                BlockHeader.CompCount = 0xFFFF;
            }
        } else {
            int clen = FUN_00551E50(Buffer, Buffer2, Counter);
            BlockHeader.CompCount = (unsigned short)clen;
            BlockHeader.UncompCount = (unsigned short)Counter;
            total += Pipe::FUN_00631D10((int)&BlockHeader, sizeof(BlockHeader));
            total += Pipe::FUN_00631D10((int)Buffer2, clen);
            Counter = 0;
        }
    }

    return Pipe::FUN_00631D30() + total;
}

// SYNTHETIC: GAMEMD 0x552390 LCWPipe::`scalar deleting destructor'
