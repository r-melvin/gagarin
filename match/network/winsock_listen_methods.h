// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, offsets and imports read off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x7B1BC0:
//     Socket        `MOV EDX,[ESI+0x3F06C]` @0x7B1BD2
//     ListenSocket  `MOV EAX,[ESI+0x3F070]` @0x7B1BFC (compared with -1)
//     slot +0x38    `PUSH -1; MOV EAX,[ESI]; CALL [EAX+0x38]` @0x7B1BC9 —
//                   one stack argument, callee-cleaned, result becomes the
//                   wMsg argument of the import below.
//   Imports resolved from the binary's own IAT labels: 0x7E156C = WSOCK32
//   ordinal 101 (WSAAsyncSelect, four __stdcall args — the four-arg form is
//   visible at 0x7B1C50) via thunk 0x7C89BC; 0x7E1574 = ordinal 111
//   (WSAGetLastError) via thunk 0x7C897A. Both are direct CALLs to the thunk
//   in retail (no dllimport), so they are declared plain __stdcall here.
//   YRpp (consult-only) names 0x7B1BC0 WinsockInterfaceClass::StartListening
//   and 0xB73550 Unsorted::hWnd.
#ifndef GG_MATCH_NETWORK_WINSOCK_LISTEN_METHODS_H
#define GG_MATCH_NETWORK_WINSOCK_LISTEN_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// WSOCK32 imports, through the binary's own thunks (direct CALL, reloc).
extern "C" int __stdcall WSAAsyncSelect(unsigned int s, void* hWnd,
                                        unsigned int wMsg, long lEvent);
extern "C" int __stdcall WSAGetLastError(void);

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) — printf-style log sink.
extern "C" void __cdecl FUN_004068E0(const char* format, ...);

// GLOBAL: GAMEMD 0xB73550 — the main window handle (Unsorted::hWnd).
extern void* DAT_00B73550;

// STRING: GAMEMD 0x84DEA4 "Async select failed on primary socket - error code %d.\n"
// STRING: GAMEMD 0x84DE68 "Async select failed on alternate socket - error code %d.\n"

struct WinsockVtbl_007B1BC0;

struct WinsockInterfaceClass
{
    WinsockVtbl_007B1BC0* Vtbl;              // +0x00000
    char _pad00004[0x3F06C - 0x4];           // +0x00004
    int  Socket;                             // +0x3F06C
    int  ListenSocket;                       // +0x3F070  -1 when absent

    // FUNCTION: GAMEMD 0x7B1BC0
    bool StartListening();
};
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, Socket)       == 0x3F06C);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, ListenSocket) == 0x3F070);

// Slot 14 (+0x38): maps a socket (-1 = the primary) to the window message
// the async-select notifications should arrive as.
typedef unsigned int (WinsockInterfaceClass::*FnMsg_007B1BC0)(int socket);

struct WinsockVtbl_007B1BC0
{
    char _pad00[0x38];          // +0x0000
    FnMsg_007B1BC0 At_38;       // +0x0038
};
GG_STATIC_ASSERT(offsetof(WinsockVtbl_007B1BC0, At_38) == 0x38);

#endif  // GG_MATCH_NETWORK_WINSOCK_LISTEN_METHODS_H
