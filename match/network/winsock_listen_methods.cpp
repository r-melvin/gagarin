// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x7B1BC0.
//
// STRING: GAMEMD 0x84DEA4 "Async select failed on primary socket - error code %d.\n"
// STRING: GAMEMD 0x84DE68 "Async select failed on alternate socket - error code %d.\n"

#include "winsock_listen_methods.h"

// FUNCTION: GAMEMD 0x7B1BC0
//
// Register both sockets for asynchronous read/write notification on the main
// window (lEvent 3 = FD_READ | FD_WRITE). The message id comes from the
// virtual slot at +0x38 (-1 asks for the primary socket's). Either failure logs
// the Winsock error and reports false; the alternate socket is skipped when it
// is not open.
//
// Retail pushes the constant 3 before evaluating the slot call — that is just
// right-to-left argument evaluation, not a five-argument import.
bool WinsockInterfaceClass::StartListening()
{
    if (WSAAsyncSelect(this->Socket, DAT_00B73550,
                       (this->*this->Vtbl->At_38)(-1), 3) == -1) {
        FUN_004068E0("Async select failed on primary socket - error code %d.\n",
                     WSAGetLastError());
        return false;
    }

    if (this->ListenSocket != -1) {
        if (WSAAsyncSelect(this->ListenSocket, DAT_00B73550,
                           (this->*this->Vtbl->At_38)(this->ListenSocket), 3) == -1) {
            FUN_004068E0("Async select failed on alternate socket - error code %d.\n",
                         WSAGetLastError());
            return false;
        }
    }

    return true;
}
