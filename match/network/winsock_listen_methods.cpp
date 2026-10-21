// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy
#include "winsock_listen_methods.h"

// STRING: GAMEMD 0x84DEA4 "Async select failed on primary socket - error code %d.\n"
// STRING: GAMEMD 0x84DE68 "Async select failed on alternate socket - error code %d.\n"

// FUNCTION: GAMEMD 0x7B1BC0  WinsockInterfaceClass::StartListening (slot 7)
// Register both sockets for asynchronous read/write notification on the main
// window (lEvent 3 = FD_READ | FD_WRITE). The message id comes from slot 14
// (-1 asks for the primary socket's). Either failure logs the Winsock error and
// reports false; the alternate socket is skipped when it is not open.
bool WinsockInterfaceClass::StartListening()
{
    if (WSAAsyncSelect(Socket, DAT_00B73550, MessageForSocket(-1), 3) == -1)
    {
        Debug_Printf("Async select failed on primary socket - error code %d.\n",
                     WSAGetLastError());
        return false;
    }

    if (ListenSocket != -1)
    {
        if (WSAAsyncSelect(ListenSocket, DAT_00B73550, MessageForSocket(ListenSocket), 3) == -1)
        {
            Debug_Printf("Async select failed on alternate socket - error code %d.\n",
                         WSAGetLastError());
            return false;
        }
    }

    return true;
}
