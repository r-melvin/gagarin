// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Body disassembled from retail gamemd.exe v1.001 at the address below, in the wwmous.cpp
//   code range (globals: mouse_ww_mouse_lock.h).
//
// Address index:
//   0x7B86B0  FUN_007B86B0

#include <windows.h>
#include "mouse_ww_mouse_lock.h"

// The thread control block at 0xB78138 is shared with the mouse thread: CreateThread at 0x7B8562 passes
// its address as lpParameter to the thread procedure 0x7B8610, which reads the stop request (+0x00,
// 0x7B8624/0x7B8691) and writes the acknowledgement (+0x08, 0x7B861A). This function writes the request
// (0x7B86C0) and polls the acknowledgement (0x7B86D0/0x7B86DF).
// GLOBAL: GAMEMD 0xB78138 -- the mouse thread's stop request.
extern volatile int DAT_00B78138;
// GLOBAL: GAMEMD 0xB78140 -- set by the mouse thread once it has noticed the request.
extern volatile int DAT_00B78140;
// GLOBAL: GAMEMD 0xB78154 -- the mouse thread handle.
extern HANDLE DAT_00B78154;
// GLOBAL: GAMEMD 0xB7816C -- the mouse thread is running.
extern int DAT_00B7816C;

// FUNCTION: GAMEMD 0x7B86B0
// Stops the mouse thread (request, spin until acknowledged, wait up to 5 s) and closes its handles.
void FUN_007B86B0()
{
    if (DAT_00B7816C) {
        DAT_00B78138 = 1;
        while (DAT_00B78140 == 0)
            Sleep(0);
        WaitForSingleObject(DAT_00B78154, 5000);
        CloseHandle(DAT_00B78154);
        DAT_00B7816C = 0;
    }
    if (MouseMutex) {
        CloseHandle(MouseMutex);
        MouseMutex = 0;
    }
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB78154
HANDLE DAT_00B78154;
// GLOBAL: GAMEMD 0xB7816C
int DAT_00B7816C;
// END defined globals
