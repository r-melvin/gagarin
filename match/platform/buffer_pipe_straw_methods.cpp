// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// The parameters keep the canonical Pipe/Straw int ABI view (pointer, count).
#include "buffer_straws.h"


// FUNCTION: GAMEMD 0x7BA3C0
int BufferPipe::FUN_00631D10(int first, int second)
{
    int total = 0;
    if (Buffer.Buffer != 0 && first != 0 && second > 0) {
        int len = second;
        if (Buffer.Size != 0) {
            int avail = Buffer.Size - Index;
            len = (second < avail) ? second : avail;
        }
        if (len > 0) {
            memmove((char*)Buffer.Buffer + Index, (const void*)first, len);
        }
        Index += len;
        total = len;
    }
    return total;
}

// FUNCTION: GAMEMD 0x7BA4D0
int BufferStraw::FUN_006C98E0(int first, int second)
{
    int total = 0;
    if (Buffer.Buffer != 0 && first != 0 && second > 0) {
        int len = second;
        if (Buffer.Size != 0) {
            int avail = Buffer.Size - Index;
            len = (second < avail) ? second : avail;
        }
        if (len > 0) {
            memmove((void*)first, (char*)Buffer.Buffer + Index, len);
        }
        Index += len;
        total = len;
    }
    return total;
}
