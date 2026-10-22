// Provenance: own-binary-via-Ghidra
//   LZOPipe's Put override (vtable slot +0x10). The block codecs it calls,
//   0x55BB90 and 0x55C0E0, are declared in lz_pipe.h and not defined here.

#include <string.h>
#include "lz_pipe.h"

// FUNCTION: GAMEMD 0x55C350
// Stage incoming bytes into blocks. Decompressing: collect the 4-byte header,
// then the compressed bytes, decode and pass on. Compressing: top up the
// staging buffer, then encode whole blocks straight from the source (each with
// a fresh 64 KiB work buffer) and keep the remainder.
int LZOPipe::FUN_00631D10(int first, int second)
{
    const char* src = (const char*)first;
    int length = second;
    if (src == NULL || length < 1) {
        return Pipe::FUN_00631D10(first, second);
    }

    int total = 0;

    if (Control == 1) {
        while (length > 0) {
            if (BlockHeader.CompCount == 0xFFFF) {
                int len = (length < sizeof(BlockHeader) - Counter) ? length : (sizeof(BlockHeader) - Counter);
                memmove(Buffer + Counter, src, len);
                src += len;
                length -= len;
                Counter += len;
                if (Counter == sizeof(BlockHeader)) {
                    memmove(&BlockHeader, Buffer, sizeof(BlockHeader));
                    Counter = 0;
                }
            }
            if (length > 0) {
                int len = (length < BlockHeader.CompCount - Counter) ? length : (BlockHeader.CompCount - Counter);
                memmove(Buffer + Counter, src, len);
                length -= len;
                src += len;
                Counter += len;
                if (Counter == BlockHeader.CompCount) {
                    unsigned int outlen = 4;
                    FUN_0055C0E0((unsigned char*)Buffer, BlockHeader.CompCount, (unsigned char*)Buffer2, &outlen, NULL);
                    total += Pipe::FUN_00631D10((int)Buffer2, BlockHeader.UncompCount);
                    Counter = 0;
                    BlockHeader.CompCount = 0xFFFF;
                }
            }
        }
    } else {
        if (Counter > 0) {
            int len = (length < BlockSize - Counter) ? length : (BlockSize - Counter);
            memmove(Buffer + Counter, src, len);
            src += len;
            length -= len;
            Counter += len;
            if (Counter == BlockSize) {
                unsigned int clen = 4;
                char* work = new char[0x10000];
                FUN_0055BB90((unsigned char*)Buffer, BlockSize, (unsigned char*)Buffer2, &clen, work);
                delete [] work;
                BlockHeader.CompCount = (unsigned short)clen;
                BlockHeader.UncompCount = (unsigned short)BlockSize;
                total += Pipe::FUN_00631D10((int)&BlockHeader, sizeof(BlockHeader));
                total += Pipe::FUN_00631D10((int)Buffer2, clen);
                Counter = 0;
            }
        }
        while (length >= BlockSize) {
            unsigned int clen = 0;
            char* work = new char[0x10000];
            FUN_0055BB90((unsigned char*)src, BlockSize, (unsigned char*)Buffer2, &clen, work);
            delete [] work;
            src += BlockSize;
            length -= BlockSize;
            BlockHeader.CompCount = (unsigned short)clen;
            BlockHeader.UncompCount = (unsigned short)BlockSize;
            total += Pipe::FUN_00631D10((int)&BlockHeader, sizeof(BlockHeader));
            total += Pipe::FUN_00631D10((int)Buffer2, clen);
        }
        if (length > 0) {
            memmove(Buffer, src, length);
            Counter = length;
        }
    }
    return total;
}
