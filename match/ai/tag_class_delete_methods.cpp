// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Primary TagClass vtable 0x7F44E0 slot +0x20 targets this 30-byte body.
// It calls the destructor at 0x6E4F60 and deallocates when flag bit 0 is set.
// The explicit method represents this ABI; it does not add a compiler vptr
// to the shared layout or establish the complete COM inheritance graph.
// LIBRARY: GAMEMD 0x7C8B3D -- the observed object-deallocation target.
#include "../_layout/tag_class.h"

// FUNCTION: GAMEMD 0x6E58B0
void* TagClass::FUN_006E58B0(unsigned int flags)
{
    this->~TagClass();
    if (flags & 1)
        ::operator delete(this);
    return this;
}
