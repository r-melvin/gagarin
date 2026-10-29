// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Body disassembled from retail gamemd.exe v1.001 at the address below.
//
// Address index:
//   0x759200  FUN_00759200

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// MSG, as the message pump at 0x53E730 sees it.
struct MsgView_00759200
{
    void* hwnd;            // +0x00
    unsigned int message;  // +0x04
    unsigned int wParam;   // +0x08
    long lParam;           // +0x0C
    unsigned long time;    // +0x10
    long pt[2];            // +0x14
};
GG_STATIC_ASSERT(sizeof(MsgView_00759200) == 0x1C);

// LIBRARY: IAT 0x7E14BC USER32!TranslateMessage, 0x7E14C0 USER32!DispatchMessageA.
extern "C" __declspec(dllimport) int __stdcall TranslateMessage(const MsgView_00759200* msg);
extern "C" __declspec(dllimport) long __stdcall DispatchMessageA(const MsgView_00759200* msg);

// GLOBAL: GAMEMD 0xAA0430 -- count of message-pump calls.
extern int DAT_00AA0430;

// FUNCTION: GAMEMD 0x53E770 (decl; reloc) -- fetch or peek one message into *msg; 0 when none.
int __fastcall FUN_0053E770(MsgView_00759200* msg, void* hwnd, unsigned int filterMin,
                            unsigned int filterMax, int remove);
// FUNCTION: GAMEMD 0x53E730 (decl; reloc) -- waits for a message; 0 for WM_QUIT.
int __fastcall FUN_0053E730(MsgView_00759200* msg, void* hwnd, unsigned int filterMin,
                            unsigned int filterMax);

// FUNCTION: GAMEMD 0x759200
// Pumps one message: peeks, then waits for and dispatches it. Returns false on WM_QUIT.
bool FUN_00759200()
{
    MsgView_00759200 msg;
    DAT_00AA0430++;
    if (FUN_0053E770(&msg, 0, 0, 0, 0)) {
        if (FUN_0053E730(&msg, 0, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
            return true;
        }
        return false;
    }
    return true;
}
