// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc18_methods.h"

// FUNCTION: GAMEMD 0x4101C0
// The first two stores are dead - both slots are overwritten below - and VC6
// removes them. Retail keeps them, because in the original they are a base
// constructor's vtable installs that the derived constructor then replaces.
// Volatile qualifiers stop the dead-store elimination and hold the six writes
// in order.
Obj_004101C0* Obj_004101C0::FUN_004101C0(int)
{
    *(char* volatile*)&vt2 = VT_007E1FBC;
    *(char* volatile*)&vt3 = VT_007E1FB4;

    *(char* volatile*)&vt0 = VT_007E1F50b;
    *(char* volatile*)&vt1 = VT_007E1F34b;
    *(char* volatile*)&vt2 = VT_007E1F2Cb;
    *(char* volatile*)&vt3 = VT_007E1F24b;

    return this;
}

// FUNCTION: GAMEMD 0x43ADC0
// The length is recorded whatever the size; only the buffer and the ownership
// flag depend on the allocation happening.
Owned_0043ADC0* Owned_0043ADC0::FUN_0043ADC0(int size)
{
    Buffer = 0;
    Length = size;
    IsAllocated = 0;

    if (size > 0) {
        Buffer = FUN_007C8E17(size);
        IsAllocated = 1;
    }

    return this;
}
