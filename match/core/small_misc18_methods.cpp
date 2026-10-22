// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
// Ordered ascending by retail address.

#include "small_misc18_methods.h"

// FUNCTION: GAMEMD 0x4101C0
// PARTIAL, 12.5% (1/8). The first two stores are dead - both slots are
// overwritten below - and VC6 removes them, so this emits four stores where
// retail has six. In the original they are presumably a base constructor's
// vtable installs that the derived constructor then replaces.
Obj_004101C0* Obj_004101C0::FUN_004101C0(int)
{
    vt2 = VT_007E1FBC;
    vt3 = VT_007E1FB4;

    vt0 = VT_007E1F50b;
    vt1 = VT_007E1F34b;
    vt2 = VT_007E1F2Cb;
    vt3 = VT_007E1F24b;

    return this;
}
