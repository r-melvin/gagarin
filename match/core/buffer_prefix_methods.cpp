// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Entry-origin instructions establish these address-scoped prefix views.
// Each 0x0C size describes only the minimum modeled prefix, not the original
// full object. Class identities, source parameter spellings and original TU
// boundaries are unknown; grouping here does not claim a shared owner.
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void* __cdecl FUN_007C8E17(unsigned int size); // LIBRARY: GAMEMD 0x7C8E17

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

struct FUN_0043AD80Prefix
{
    void* Buffer;          // +0x00
    int Size;              // +0x04
    bool Allocated;        // +0x08
    char unknown_09[3];    // +0x09
    FUN_0043AD80Prefix* FUN_0043AD80(void* pBuffer, int size);
};

GG_STATIC_ASSERT(offsetof(FUN_0043AD80Prefix, Buffer) == 0x00);
GG_STATIC_ASSERT(offsetof(FUN_0043AD80Prefix, Size) == 0x04);
GG_STATIC_ASSERT(offsetof(FUN_0043AD80Prefix, Allocated) == 0x08);
GG_STATIC_ASSERT(sizeof(FUN_0043AD80Prefix) == 0x0C);


// FUNCTION: GAMEMD 0x43AD80
FUN_0043AD80Prefix* FUN_0043AD80Prefix::FUN_0043AD80(void* pBuffer, int size)
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

struct FUN_0043ADF0Prefix
{
    void* Buffer;          // +0x00
    int Size;              // +0x04
    bool Allocated;        // +0x08
    char unknown_09[3];    // +0x09
    FUN_0043ADF0Prefix* FUN_0043ADF0(const FUN_0043ADF0Prefix* source);
};
GG_STATIC_ASSERT(offsetof(FUN_0043ADF0Prefix, Buffer) == 0x00);
GG_STATIC_ASSERT(offsetof(FUN_0043ADF0Prefix, Size) == 0x04);
GG_STATIC_ASSERT(offsetof(FUN_0043ADF0Prefix, Allocated) == 0x08);
GG_STATIC_ASSERT(sizeof(FUN_0043ADF0Prefix) == 0x0C);

// FUNCTION: GAMEMD 0x43ADF0
FUN_0043ADF0Prefix* FUN_0043ADF0Prefix::FUN_0043ADF0(const FUN_0043ADF0Prefix* source)
{
    Allocated = 0;
    Buffer = source->Buffer;
    Size = source->Size;
    return this;
}

struct FUN_0043AEB0Prefix
{
    void* Buffer;          // +0x00
    int Size;              // +0x04
    bool Allocated;        // +0x08
    char unknown_09[3];    // +0x09
    FUN_0043AEB0Prefix* FUN_0043AEB0(void* pBuffer, int size);
};
GG_STATIC_ASSERT(offsetof(FUN_0043AEB0Prefix, Buffer) == 0x00);
GG_STATIC_ASSERT(offsetof(FUN_0043AEB0Prefix, Size) == 0x04);
GG_STATIC_ASSERT(offsetof(FUN_0043AEB0Prefix, Allocated) == 0x08);
GG_STATIC_ASSERT(sizeof(FUN_0043AEB0Prefix) == 0x0C);


// FUNCTION: GAMEMD 0x43AEB0
FUN_0043AEB0Prefix* FUN_0043AEB0Prefix::FUN_0043AEB0(void* pBuffer, int size)
{
    Size = size;
    if (pBuffer != 0) {
        Buffer = pBuffer;
        Allocated = 0;
        return this;
    }
    Buffer = FUN_007C8E17(size);
    Allocated = 1;
    return this;
}

struct FUN_0043AEF0Prefix
{
    void* Buffer;          // +0x00
    int Size;              // +0x04
    bool Allocated;        // +0x08
    char unknown_09[3];    // +0x09
    FUN_0043AEF0Prefix* FUN_0043AEF0(int size);
};
GG_STATIC_ASSERT(offsetof(FUN_0043AEF0Prefix, Buffer) == 0x00);
GG_STATIC_ASSERT(offsetof(FUN_0043AEF0Prefix, Size) == 0x04);
GG_STATIC_ASSERT(offsetof(FUN_0043AEF0Prefix, Allocated) == 0x08);
GG_STATIC_ASSERT(sizeof(FUN_0043AEF0Prefix) == 0x0C);


// FUNCTION: GAMEMD 0x43AEF0
FUN_0043AEF0Prefix* FUN_0043AEF0Prefix::FUN_0043AEF0(int size)
{
    Size = size;
    Buffer = FUN_007C8E17(size);
    Allocated = 1;
    return this;
}
