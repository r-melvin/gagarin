// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The WWMouseClass cursor lock as wwmous.cpp inlines it (out-of-line instance 0x7BA2C0: WaitForSingleObject on the
//   mutex 0xB78168 with a 10000 ms timeout, the "Probable deadlock" message at line 0x4FD, then ReleaseMutex). Split
//   from mouse_ww_mouse_class.h because it needs <windows.h>.
#ifndef GG_MATCH_UI_INPUT_CONTROLS_MOUSE_WW_MOUSE_LOCK_H
#define GG_MATCH_UI_INPUT_CONTROLS_MOUSE_WW_MOUSE_LOCK_H

#include <windows.h>
#include "mouse_ww_mouse_class.h"

// GLOBAL: GAMEMD 0x00B78168 - the cursor mutex.
extern HANDLE MouseMutex;

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) - printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);

// The cursor lock: WaitForSingleObject(MouseMutex, 10000) with the deadlock warning, as inlined throughout
// wwmous.cpp (out-of-line instance at 0x7BA2C0).
inline void LockMouse()
{
    if (WaitForSingleObject(MouseMutex, 10000) == WAIT_TIMEOUT)
        FUN_004068E0("Warning: Probable deadlock occurred on MouseMutex. %s, line %d\n",
                     "D:\\ra2mdpost\\wwmous.cpp", 1277);
}

// FUNCTION: GAMEMD 0x7BA2C0 (decl; reloc) - the out-of-line instance of the lock above; vf_4 and CaptureMouse
// call it from the cursor-frame step instead of expanding the lock inline.
void __cdecl LockMouseCall();

inline void UnlockMouse()
{
    ReleaseMutex(MouseMutex);
}

#endif  // GG_MATCH_UI_INPUT_CONTROLS_MOUSE_WW_MOUSE_LOCK_H
