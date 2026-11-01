// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read off the user's retail gamemd.exe v1.001 with the local Ghidra CLI at the address in the annotation.

#include "mouse_ww_mouse_lock.h"

// FUNCTION: GAMEMD 0x7BA2C0
// The out-of-line instance of the cursor lock.
void __cdecl LockMouseCall()
{
    LockMouse();
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB78168
HANDLE MouseMutex;
// END defined globals
