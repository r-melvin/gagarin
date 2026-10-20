// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Buffer-holder deleting destructors, ordered ascending by retail address.

#include "buffer_holder_dtor_methods.h"

// FUNCTION: GAMEMD 0x40B300
void* BufferHolderDtor::FUN_0040B300(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E177C;

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

// FUNCTION: GAMEMD 0x40BBC0
void* BufferHolderDtor::FUN_0040BBC0(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E17EC;

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

// FUNCTION: GAMEMD 0x40BC10
void* BufferHolderDtor::FUN_0040BC10(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E17EC;

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

// FUNCTION: GAMEMD 0x40BC60
void* BufferHolderDtor::FUN_0040BC60(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E180C;

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

// FUNCTION: GAMEMD 0x40BCB0
void* BufferHolderDtor::FUN_0040BCB0(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E180C;

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

// FUNCTION: GAMEMD 0x40C4F0
void* BufferHolderDtor::FUN_0040C4F0(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E188C;

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

// FUNCTION: GAMEMD 0x40C540
void* BufferHolderDtor::FUN_0040C540(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E188C;

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

// FUNCTION: GAMEMD 0x40CF30
void* BufferHolderDtor::FUN_0040CF30(unsigned int flags)
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

// FUNCTION: GAMEMD 0x40D800
void* BufferHolderDtor::FUN_0040D800(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E1A64;

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

// FUNCTION: GAMEMD 0x40D850
void* BufferHolderDtor::FUN_0040D850(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E1A64;

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

// FUNCTION: GAMEMD 0x40F8A0
void* BufferHolderDtor::FUN_0040F8A0(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E1EA4;

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

// FUNCTION: GAMEMD 0x40F8F0
void* BufferHolderDtor::FUN_0040F8F0(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E1EA4;

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

// FUNCTION: GAMEMD 0x41E0A0
void* BufferHolderDtor::FUN_0041E0A0(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E295C;

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

// FUNCTION: GAMEMD 0x41E0F0
void* BufferHolderDtor::FUN_0041E0F0(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E295C;

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

// FUNCTION: GAMEMD 0x420630
void* BufferHolderDtor::FUN_00420630(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E2AF0;

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

// FUNCTION: GAMEMD 0x420680
void* BufferHolderDtor::FUN_00420680(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E2AF0;

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

// FUNCTION: GAMEMD 0x421AC0
void* BufferHolderDtor::FUN_00421AC0(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E3258;

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

// FUNCTION: GAMEMD 0x421B10
void* BufferHolderDtor::FUN_00421B10(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E3258;

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

// FUNCTION: GAMEMD 0x42DBB0
void* BufferHolderDtor::FUN_0042DBB0(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E3824;

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

// FUNCTION: GAMEMD 0x42DC00
void* BufferHolderDtor::FUN_0042DC00(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E3824;

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

// FUNCTION: GAMEMD 0x42F970
void* BufferHolderDtor::FUN_0042F970(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E38F0;

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

// FUNCTION: GAMEMD 0x42FB50
void* BufferHolderDtor::FUN_0042FB50(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E38F0;

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

// FUNCTION: GAMEMD 0x42FBA0
void* BufferHolderDtor::FUN_0042FBA0(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E38D0;

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

// FUNCTION: GAMEMD 0x42FBF0
void* BufferHolderDtor::FUN_0042FBF0(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E38D0;

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

// FUNCTION: GAMEMD 0x45ACE0
void* BufferHolderDtor::FUN_0045ACE0(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E4468;

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

// FUNCTION: GAMEMD 0x45AD30
void* BufferHolderDtor::FUN_0045AD30(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E4468;

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

// FUNCTION: GAMEMD 0x466080
void* BufferHolderDtor::FUN_00466080(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E4638;

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

// FUNCTION: GAMEMD 0x46B8C0
void* BufferHolderDtor::FUN_0046B8C0(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E4698;

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

// FUNCTION: GAMEMD 0x46B910
void* BufferHolderDtor::FUN_0046B910(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E4698;

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

// FUNCTION: GAMEMD 0x473000
void* BufferHolderDtor::FUN_00473000(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E4BC4;

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

// FUNCTION: GAMEMD 0x473050
void* BufferHolderDtor::FUN_00473050(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E4BC4;

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

// FUNCTION: GAMEMD 0x4730A0
void* BufferHolderDtor::FUN_004730A0(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E4AF4;

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

// FUNCTION: GAMEMD 0x4730F0
void* BufferHolderDtor::FUN_004730F0(unsigned int flags)
{
    void* buffer = Buffer;

    *(char**)this = VTABLE_007E4AF4;

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
