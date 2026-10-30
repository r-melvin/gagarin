// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Buffer-holder deleting destructors, ordered ascending by retail address.

#include "buffer_holder_dtor_methods.h"

// FUNCTION: GAMEMD 0x40C110
void* BufferHolderDtor::FUN_0040C110(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E184C;

    if (buffer != 0 && IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        Buffer = 0;
    }

    IsAllocated = 0;
    Length = 0;

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x40C160
void* BufferHolderDtor::FUN_0040C160(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E184C;

    if (buffer != 0 && IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        Buffer = 0;
    }

    IsAllocated = 0;
    Length = 0;

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x40CAE0
void* BufferHolderDtor::FUN_0040CAE0(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E18DC;

    if (buffer != 0 && IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        Buffer = 0;
    }

    IsAllocated = 0;
    Length = 0;

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x40CB30
void* BufferHolderDtor::FUN_0040CB30(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E18DC;

    if (buffer != 0 && IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        Buffer = 0;
    }

    IsAllocated = 0;
    Length = 0;

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x40CC20
void* BufferHolderDtor::FUN_0040CC20(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E192C;

    if (buffer != 0 && IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        Buffer = 0;
    }

    IsAllocated = 0;
    Length = 0;

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x40EAB0
void* BufferHolderDtor::FUN_0040EAB0(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E1B44;

    if (buffer != 0 && IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        Buffer = 0;
    }

    IsAllocated = 0;
    Length = 0;

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x40EB00
void* BufferHolderDtor::FUN_0040EB00(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E1B44;

    if (buffer != 0 && IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        Buffer = 0;
    }

    IsAllocated = 0;
    Length = 0;

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x40F180
void* BufferHolderDtor::FUN_0040F180(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E1E4C;

    if (buffer != 0 && IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        Buffer = 0;
    }

    IsAllocated = 0;
    Length = 0;

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x40F1D0
void* BufferHolderDtor::FUN_0040F1D0(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E1E4C;

    if (buffer != 0 && IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        Buffer = 0;
    }

    IsAllocated = 0;
    Length = 0;

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x40FE70
void* BufferHolderDtor::FUN_0040FE70(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E1EF4;

    if (buffer != 0 && IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        Buffer = 0;
    }

    IsAllocated = 0;
    Length = 0;

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x40FEC0
void* BufferHolderDtor::FUN_0040FEC0(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E1EF4;

    if (buffer != 0 && IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        Buffer = 0;
    }

    IsAllocated = 0;
    Length = 0;

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x42DB10
void* BufferHolderDtor::FUN_0042DB10(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E37EC;

    if (buffer != 0 && IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        Buffer = 0;
    }

    IsAllocated = 0;
    Length = 0;

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x42DB60
void* BufferHolderDtor::FUN_0042DB60(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E37EC;

    if (buffer != 0 && IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        Buffer = 0;
    }

    IsAllocated = 0;
    Length = 0;

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}





// FUNCTION: GAMEMD 0x43ACB0
void* BufferHolderDtor::FUN_0043ACB0(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E3E54;

    if (buffer != 0 && IsAllocated != 0) {
        FUN_007C8B3D(buffer);
        Buffer = 0;
    }

    IsAllocated = 0;
    Length = 0;

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

