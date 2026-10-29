// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Frozen M1 recovery, reconfirmed against pinned retail entry spans and
// winsock.rows.tsv. Unattested virtuals are named vf_<slot>.
// The selected methods are the unclaimed ordinary WinsockInterfaceClass base
// entries only; StartListening and both buffer-drain methods remain in their
// existing TUs. No constructor, destructor, or ShutdownWinsock body is here.
#include <string.h>
#include "winsock_interface_class.h"

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete used by GetPacket.
// LIBRARY: GAMEMD 0x7C8992 -- closesocket, __stdcall thunk.
// LIBRARY: GAMEMD 0x7C898C -- getsockopt, __stdcall thunk.
// LIBRARY: GAMEMD 0x7C89A4 -- setsockopt, __stdcall thunk.
// LIBRARY: GAMEMD 0x7C89CE -- gethostname, __stdcall thunk.
// LIBRARY: GAMEMD 0x7C89BC -- WSAAsyncSelect, __stdcall thunk.
// LIBRARY: GAMEMD 0x7C897A -- WSAGetLastError, __stdcall thunk.
// LIBRARY: GAMEMD 0x7E14A4 -- SendMessageA, user32 import.
// FUNCTION: GAMEMD 0x64DE80 (decl; reloc) -- packet checksum step.
// FUNCTION: GAMEMD 0x54F000 (decl; reloc) -- input/message pump.

// STRING: GAMEMD 0x84E040 "Error in Winsock packet CRC\n"
// STRING: GAMEMD 0x84E060 "Socket option SO_SNDBUF set OK\n"
// STRING: GAMEMD 0x84E080 "Failed to set socket option SO_SNDBUF - error code %d.\n"
// STRING: GAMEMD 0x84E0B8 "Socket option SO_RCVBUF set OK\n"
// STRING: GAMEMD 0x84E0D8 "Failed to set socket option SO_RCVBUF - error code %d.\n"
// STRING: GAMEMD 0x84E110 "WinsockInterface Host name is %s\n"
// STRING: GAMEMD 0x84E134 "Error - WinsockInterface Unable to get host name. Error code %d\n"

// GLOBAL: GAMEMD 0x84DD9C -- socket send-buffer size.
extern const int DAT_0084DD9C;
// GLOBAL: GAMEMD 0x84DDA0 -- socket receive-buffer size.
extern const int DAT_0084DDA0;

// FUNCTION: GAMEMD 0x7B1720  WinsockInterfaceClass::AddBroadcastAddress (base stub; slot 11)
void WinsockInterfaceClass::AddBroadcastAddress(const char*, unsigned short)
{
}

// FUNCTION: GAMEMD 0x7B1730  WinsockInterfaceClass::ClearBroadcastAddresses (base stub; slot 12)
void WinsockInterfaceClass::ClearBroadcastAddresses()
{
}

// FUNCTION: GAMEMD 0x7B1740  WinsockInterfaceClass::GetNumLocalAddresses (base; slot 18)
int WinsockInterfaceClass::GetNumLocalAddresses()
{
    return 0;
}

// FUNCTION: GAMEMD 0x7B1750  WinsockInterfaceClass::GetLocalAddress (base; slot 19)
unsigned char* WinsockInterfaceClass::GetLocalAddress(int)
{
    return 0;
}

// FUNCTION: GAMEMD 0x7B1760  WinsockInterfaceClass::Slot20 (slot 20)
void WinsockInterfaceClass::Slot20(int value)
{
    unknown_3F2F8 = value;
}

