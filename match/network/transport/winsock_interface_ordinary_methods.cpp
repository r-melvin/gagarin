// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Frozen M1 recovery, reconfirmed against pinned retail entry spans and
// winsock.rows.tsv. Unattested virtuals are named vf_<slot>.
// The selected methods are the unclaimed ordinary WinsockInterfaceClass base
// entries only; StartListening and both buffer-drain methods remain in their
// existing TUs. No constructor, destructor, or ShutdownWinsock body is here.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
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

// FUNCTION: GAMEMD 0x7B1B80  WinsockInterfaceClass::vf_1 (slot 1)
void WinsockInterfaceClass::vf_1()
{
    if (Socket != -1)
    {
        closesocket(Socket);
        Socket = -1;
    }
    if (unknown_3F070 != -1)
    {
        closesocket(unknown_3F070);
        unknown_3F070 = -1;
    }
}

// FUNCTION: GAMEMD 0x7B1C50  WinsockInterfaceClass::StopListening (slot 8)
void WinsockInterfaceClass::StopListening()
{
    if (Socket != -1 && DAT_00B73550)
        WSAAsyncSelect(Socket, DAT_00B73550, 0, 0);
    if (unknown_3F070 != -1 && DAT_00B73550)
        WSAAsyncSelect(unknown_3F070, DAT_00B73550, 0, 0);
}

// FUNCTION: GAMEMD 0x7B1FD0  WinsockInterfaceClass::ComputePacketCrc (slot 21)
void WinsockInterfaceClass::ComputePacketCrc(WinsockBufferType* packet)
{
    int i;
    packet->Crc = 0;
    unsigned long* data = (unsigned long*)packet->Payload;
    for (i = 0; i < packet->BufferLen / 4; i++)
        FUN_0064DE80(&packet->Crc, *data++);

    i = packet->BufferLen & 3;
    if (i != 0)
        FUN_0064DE80(&packet->Crc, (0xFFFFFFFFul >> (32 - i * 8)) & *data);
}

// FUNCTION: GAMEMD 0x7B2050  WinsockInterfaceClass::VerifyPacketCrc (slot 22)
bool WinsockInterfaceClass::VerifyPacketCrc(WinsockBufferType* packet)
{
    if (packet->BufferLen < 0x280)
    {
        int i = 0;
        unsigned long crc = 0;
        unsigned long* data = (unsigned long*)packet->Payload;
        for (; i < packet->BufferLen / 4; i++)
            FUN_0064DE80(&crc, *data++);

        int remainder = packet->BufferLen & 3;
        if (remainder != 0)
            FUN_0064DE80(&crc, (0xFFFFFFFFul >> (32 - remainder * 8)) & *data);

        if (crc == packet->Crc)
            return true;
        FUN_004068E0("Error in Winsock packet CRC\n");
    }
    return false;
}

// FUNCTION: GAMEMD 0x7B22E0  WinsockInterfaceClass::GetPacket (slot 2)
int WinsockInterfaceClass::GetPacket(void* packet, int* packetLen, void* address,
                                     unsigned int* addressLen, unsigned short* unknown1A)
{
    DAT_0087F770->FUN_0054F000();
    if (InBuffers.Count == 0)
        return 0;

    WinsockBufferType* buffer = InBuffers.Items[0];
    memcpy(packet, buffer->Payload, buffer->BufferLen);
    unsigned int length = *addressLen;
    if (length > 0x10)
        length = 0x10;
    *addressLen = length;
    memcpy(address, buffer->Address, length);
    *unknown1A = buffer->unknown_1A;
    *packetLen = buffer->BufferLen;

    if (InBuffers.Count > 0)
    {
        InBuffers.Count--;
        for (int i = 0; i < InBuffers.Count; i++)
            InBuffers.Items[i] = InBuffers.Items[i + 1];
    }

    if (buffer->IsAllocated)
        operator delete(buffer);
    else
    {
        buffer->InUse = 0;
        StaticInBuffersInUse--;
    }
    return *packetLen;
}

// FUNCTION: GAMEMD 0x7B23B0  WinsockInterfaceClass::SendPacket (slot 3)
void WinsockInterfaceClass::SendPacket(void* packet, int packetLen, void* address,
                                       int addressLen, bool alternate,
                                       unsigned char unknown18, unsigned short unknown1A)
{
    WinsockBufferType* buffer = AllocOutBuffer(alternate);
    memcpy(buffer->Payload, packet, packetLen);
    buffer->BufferLen = packetLen;
    buffer->IsBroadcast = 0;
    buffer->unknown_18 = unknown18;
    memcpy(buffer->Address, address, addressLen);
    buffer->unknown_1A = unknown1A;
    ComputePacketCrc(buffer);

    SOCKET socket;
    if (alternate)
    {
        WinsockAddItem(AltOutBuffers, buffer);
        socket = unknown_3F070;
    }
    else
    {
        WinsockAddItem(OutBuffers, buffer);
        socket = Socket;
    }
    SendMessageA(DAT_00B73550, MessageForSocket(socket), 0, 2);
    DAT_0087F770->FUN_0054F000();
}

// FUNCTION: GAMEMD 0x7B24E0  WinsockInterfaceClass::Broadcast (slot 4)
void WinsockInterfaceClass::Broadcast(void* packet, int packetLen, bool alternate)
{
    WinsockBufferType* buffer = AllocOutBuffer(alternate);
    memcpy(buffer->Payload, packet, packetLen);
    buffer->BufferLen = packetLen;
    ComputePacketCrc(buffer);
    buffer->IsBroadcast = 1;

    SOCKET socket;
    if (alternate)
    {
        WinsockAddItem(AltOutBuffers, buffer);
        socket = unknown_3F070;
    }
    else
    {
        WinsockAddItem(OutBuffers, buffer);
        socket = Socket;
    }
    SendMessageA(DAT_00B73550, MessageForSocket(socket), 0, 2);
    DAT_0087F770->FUN_0054F000();
}

// FUNCTION: GAMEMD 0x7B25E0  WinsockInterfaceClass::vf_9 (slot 9)
void WinsockInterfaceClass::vf_9(SOCKET socket)
{
    int error;
    int length = 4;
    getsockopt(socket, SOL_SOCKET, SO_ERROR, (char*)&error, &length);
    error = 0;
    setsockopt(socket, SOL_SOCKET, SO_ERROR, (char*)&error, length);
}

// FUNCTION: GAMEMD 0x7B2630  WinsockInterfaceClass::SetSocketBuffers (slot 10)
bool WinsockInterfaceClass::SetSocketBuffers(SOCKET socket)
{
    if (socket == -1)
        socket = Socket;

    if (setsockopt(socket, SOL_SOCKET, SO_RCVBUF, (const char*)&DAT_0084DDA0, 4) == -1)
        FUN_004068E0("Failed to set socket option SO_RCVBUF - error code %d.\n",
                     WSAGetLastError());
    else
        FUN_004068E0("Socket option SO_RCVBUF set OK\n");

    if (setsockopt(socket, SOL_SOCKET, SO_SNDBUF, (const char*)&DAT_0084DD9C, 4) == -1)
        FUN_004068E0("Failed to set socket option SO_SNDBUF - error code %d.\n",
                     WSAGetLastError());
    else
        FUN_004068E0("Socket option SO_SNDBUF set OK\n");
    return true;
}

// FUNCTION: GAMEMD 0x7B26D0  WinsockInterfaceClass::GetHostName (slot 17)
bool WinsockInterfaceClass::GetHostName(char* name, int nameLen)
{
    if (gethostname(name, nameLen) == -1)
    {
        FUN_004068E0("Error - WinsockInterface Unable to get host name. Error code %d\n",
                     WSAGetLastError());
        return false;
    }
    FUN_004068E0("WinsockInterface Host name is %s\n", name);
    return true;
}

// FUNCTION: GAMEMD 0x7B2740  WinsockInterfaceClass::Slot13 (base; slot 13)
int WinsockInterfaceClass::Slot13()
{
    return 0;
}

// FUNCTION: GAMEMD 0x7B2750  WinsockInterfaceClass::MessageForSocket (base; slot 14)
unsigned int WinsockInterfaceClass::MessageForSocket(int)
{
    return 0;
}

// FUNCTION: GAMEMD 0x7B2760  WinsockInterfaceClass::Init (base; slot 15)
bool WinsockInterfaceClass::Init(int)
{
    return false;
}

// FUNCTION: GAMEMD 0x7B2770  WinsockInterfaceClass::vf_16 (base; slot 16)
int WinsockInterfaceClass::vf_16(HWND, unsigned int, unsigned int, long)
{
    return 1;
}
