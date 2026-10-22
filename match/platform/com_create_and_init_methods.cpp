// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x46B050.

#include "com_create_and_init_methods.h"

// FUNCTION: GAMEMD 0x46B050
//
// Create the object in-process (context 7 is INPROC_SERVER | INPROC_HANDLER |
// LOCAL_SERVER), hand all seven of this function's parameters straight to its
// configure method, and return it. A failed creation returns null without
// touching the parameters.
//
// The out-parameter is a local rather than the caller's storage, which is what
// makes the success path able to return it directly.
//
// It is then copied into a second local before use. Taking the address of a
// variable pins it to the stack, so using it directly makes VC6 reload it from
// there at each use; retail loads it once and keeps it in a callee-saved register
// for both the call and the return. The copy is what produces that (40.5% to
// byte parity), and it is also why retail saves one more register than the
// address-taken form needs.
Target_0046B050* FUN_0046B050(int a, int b, int c, int d, int e,
                              int f, int g)
{
    Target_0046B050* created = 0;

    if (CoCreateInstance(rclsid_007E96E0, 0, 7, riid_007F7C90,
                         (void**)&created) < 0) {
        return 0;
    }

    Target_0046B050* obj = created;
    obj->FUN_004664C0(a, b, c, d, e, f, g);
    return obj;
}
