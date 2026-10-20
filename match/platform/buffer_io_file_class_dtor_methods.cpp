// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x431B80.
//
// reccmp annotations:
//   FUNCTION: GAMEMD 0x431B80   BufferIOFileClass::~BufferIOFileClass (__thiscall)
//   VTABLE:   GAMEMD 0x7E3A2C   BufferIOFileClass

#include "buffer_io_file_class_dtor_methods.h"

// FUNCTION: GAMEMD 0x431B80  BufferIOFileClass::~BufferIOFileClass (__thiscall)
//
// The buffer is only freed when this object allocated it; a caller-supplied
// buffer is dropped without being released, which is why the allocated flag is
// tested inside the non-null branch rather than alongside it.
BufferIOFileClass::~BufferIOFileClass()
{
    if (Buffer) {
        if (IsAllocated) {
            FUN_007C8B3D(Buffer);
            IsAllocated = 0;
        }
        Buffer = 0;
    }

    BufferSize = 0;
    IsOpen = 0;
    IsDiskOpen = 0;
    IsCached = 0;
    IsChanged = 0;

    ((RawFileClassBase*)this)->FUN_0065CA00();
}

// FUNCTION: GAMEMD 0x431D90
// Close: release the buffer if owned, then reset every flag. The destructor at
// 0x431B80 is this plus the vtable install and the base call, and the two agree
// on the layout - which is the cross-check that makes both trustworthy.
void BufferIOFileClass::FUN_00431D90()
{
    if (Buffer) {
        if (IsAllocated) {
            FUN_007C8B3D(Buffer);
            IsAllocated = 0;
        }
        Buffer = 0;
    }

    BufferSize = 0;
    IsOpen = 0;
    IsDiskOpen = 0;
    IsCached = 0;
    IsChanged = 0;
}
