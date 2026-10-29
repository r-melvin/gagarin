// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Evidence: 0x642980 loads 0xAC4F58 into ECX, calls the constructor 0x6429E0 and registers the
//   thunk at 0x6429A0 with atexit; both come from the one global definition below. The thunk is the
//   destructor body inlined (restore the vptr, release the owned buffer).

#include "progress_screen_class.h"

// FUNCTION: GAMEMD 0x642A30
// Destructor body: restore the vtable, free the owned buffer and clear it.
ProgressScreenClass::~ProgressScreenClass()
{
    if (BufferOwned) {
        delete Buffer;
        BufferOwned = false;
    }
    Buffer = 0;
}

// GLOBAL: GAMEMD 0xAC4F58
// SYNTHETIC: GAMEMD 0x6429A0 -- exit-time destructor thunk
// SYNTHETIC: GAMEMD 0x00642980 -- initialiser of DAT_00AC4F58
ProgressScreenClass DAT_00AC4F58;
