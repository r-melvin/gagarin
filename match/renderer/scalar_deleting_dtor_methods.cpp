// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x4272A0.

#include "scalar_deleting_dtor_methods.h"

// FUNCTION: GAMEMD 0x4272A0
//
// This is MSVC's scalar deleting destructor (`??_G`): it takes a flags byte,
// runs the destructor body, and frees the object itself only when bit 0 is set.
// Both vptr stores are part of that shape — the class's own vtable is installed
// on entry and the base's restored before the free, which is what a destructor
// chain does as it unwinds.
//
// It is written out as an ordinary member rather than by declaring a virtual
// destructor and letting VC6 generate the thunk. The generated form would also
// have to inline both the derived and the base destructor bodies to land here,
// and writing it directly keeps the three cleanup blocks and the two vptr stores
// in retail's order without depending on those inlining decisions.
//
// The `Owner` pointer is cleared after the attached-flag block rather than with
// its own — retail's `MOV [ESI+0x84],EBX` at 0x4272CD sits between that block and
// the sink's read.
AnimFile_004272A0* AnimFile_004272A0::Destroy(int flags)
{
    int zero = 0;

    char attached = this->Attached;
    this->Vptr = VTBL_007E3584;

    if (attached != (char)zero) {
        (this->Owner->*this->Owner->Vptr->At_34)();
        this->Attached = (char)zero;
    }

    this->Owner = (Owner_004272A0*)zero;

    if (this->Sink != (Sink_004272A0*)zero) {
        (this->Sink->*this->Sink->Vptr->At_00)(1);
        this->Sink = (Sink_004272A0*)zero;
    }

    if (this->Buffer != (void*)zero) {
        FUN_007C8B3D(this->Buffer);
        this->Buffer = (void*)zero;
    }

    this->At_88 = (char)zero;
    this->Vptr = VTBL_007E35A8;

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}
