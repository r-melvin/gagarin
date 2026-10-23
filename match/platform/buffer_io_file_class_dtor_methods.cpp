// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2 /MT
// Expand real BufferIO teardown in the native deleting destructor.
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
    if (unknown_30) {
        if (unknown_bool_24) {
            FUN_007C8B3D(unknown_30);
            unknown_bool_24 = 0;
        }
        unknown_30 = 0;
    }

    unknown_34 = 0;
    unknown_bool_25 = 0;
    unknown_bool_27 = 0;
    unknown_bool_28 = 0;
    unknown_bool_29 = 0;

}

// FUNCTION: GAMEMD 0x431D90
// Close: release the buffer if owned, then reset every flag. The destructor at
// 0x431B80 is this plus the vtable install and the base call, and the two agree
// on the layout - which is the cross-check that makes both trustworthy.
void BufferIOFileClass::FUN_00431D90()
{
    if (unknown_30) {
        if (unknown_bool_24) {
            FUN_007C8B3D(unknown_30);
            unknown_bool_24 = 0;
        }
        unknown_30 = 0;
    }

    unknown_34 = 0;
    unknown_bool_25 = 0;
    unknown_bool_27 = 0;
    unknown_bool_28 = 0;
    unknown_bool_29 = 0;
}

// SYNTHETIC: GAMEMD 0x432610
// BufferIOFileClass scalar deleting destructor is compiler-generated.
