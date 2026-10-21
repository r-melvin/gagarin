// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Address-scoped ABI prefix only. Retail evidence does not identify the
// original class or full object size.
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct FUN_0043AD40Prefix
{
    void* Buffer;          // +0x00
    int Size;              // +0x04
    bool Allocated;        // +0x08
    char unknown_09[3];    // +0x09

    FUN_0043AD40Prefix* FUN_0043AD40(void* pBuffer, int size);
};

GG_STATIC_ASSERT(offsetof(FUN_0043AD40Prefix, Buffer) == 0x00);
GG_STATIC_ASSERT(offsetof(FUN_0043AD40Prefix, Size) == 0x04);
GG_STATIC_ASSERT(offsetof(FUN_0043AD40Prefix, Allocated) == 0x08);
GG_STATIC_ASSERT(sizeof(FUN_0043AD40Prefix) == 0x0C);

extern "C" void* __cdecl FUN_007C8E17(unsigned int size); // LIBRARY: GAMEMD 0x7C8E17

// FUNCTION: GAMEMD 0x43AD40
FUN_0043AD40Prefix* FUN_0043AD40Prefix::FUN_0043AD40(void* pBuffer, int size)
{
    Buffer = pBuffer;
    Size = size;
    Allocated = 0;
    if (pBuffer == 0 && size > 0) {
        Buffer = FUN_007C8E17(size);
        Allocated = 1;
    }
    return this;
}
