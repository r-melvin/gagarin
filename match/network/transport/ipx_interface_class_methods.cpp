// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | RTTI; frozen method transcription used only as a hypothesis.
// The original four entry spans are revalidated from pinned retail bytes and focused REA
// at 0x7B10C0/0x7B13D0/0x7B1770/0x7B1780. Member offsets and the derived
// table identity are checked against retail; this file does not claim constructor
// ownership or a complete emitted/final-linked IPX vtable.
// GetAdapterAddressString at 0x7B0F50 is independently checked against the
// entry-origin retail span and strict relocation targets.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
#include <string.h>
#include <stdio.h>
#include "../../_layout/ipx_address_class.h"
#include "winsock_interface_class.h"
#include "ipx_interface_class.h"
#include "../../core/randomizer.h"
#include "../../core/global_getter_family_methods.h"

// GLOBAL: GAMEMD 0xB7801C -- set after malformed packet discard.
extern unsigned char DAT_00B7801C;
// LIBRARY: GAMEMD 0x7C8968 -- htons import thunk.
// LIBRARY: GAMEMD 0x7C897A -- WSAGetLastError import thunk.
// LIBRARY: GAMEMD 0x7C8992 -- closesocket import thunk.
// LIBRARY: GAMEMD 0x7C8998 -- bind import thunk.
// LIBRARY: GAMEMD 0x7C899E -- socket import thunk.
// LIBRARY: GAMEMD 0x7C89A4 -- setsockopt import thunk.
// LIBRARY: GAMEMD 0x7C89AA -- recvfrom import thunk.
// LIBRARY: GAMEMD 0x7C89B0 -- sendto import thunk.
// STRING: GAMEMD 0x84DD54 "IPX Socket number is %04x\n"
// STRING: GAMEMD 0x84DD34 "About to create an IPX socket\n"
// STRING: GAMEMD 0x84DD04 "Failed to create IPX socket - error code %d.\n"
// STRING: GAMEMD 0x84DCEC "IPX Socket created OK\n"
// STRING: GAMEMD 0x84DCBC "IPX Error - failed to get the net card address\n"
// STRING: GAMEMD 0x84DC6C "IPX net card address is %02x %02x %02x %02x : %02x %02x %02x %02x %02x %02x\n"
// STRING: GAMEMD 0x84DC50 "About to bind IPX Socket\n"
// STRING: GAMEMD 0x84DC24 "IPX socket bind failed with error code %d.\n"
// STRING: GAMEMD 0x84DC0C "IPX Socket bound OK\n"
// STRING: GAMEMD 0x84DBDC "About to set IPX socket option SO_BROADCAST\n"
// STRING: GAMEMD 0x84DB9C "Failed to set IPX socket option SO_BROADCAST - error code %d.\n"
// STRING: GAMEMD 0x84DB74 "IPX socket option SO_BROADCAST set OK\n"
// STRING: GAMEMD 0x84DB48 "About to set IPX socket option IPX_PTYPE\n"
// STRING: GAMEMD 0x84DB08 "Failed to set IPX protocol option IPX_PTYPE - error code %d.\n"
// STRING: GAMEMD 0x84DAE4 "IPX socket option IPX_PTYPE set OK\n"
// STRING: GAMEMD 0x84DAB4 "About to set IPX socket option IPX_FILTERTYPE\n"
// STRING: GAMEMD 0x84DA70 "Failed to set IPX protocol option IPX_FILTERTYPE - error code %d.\n"
// STRING: GAMEMD 0x84DA44 "IPX socket option IPX_FILTERTYPE set OK\n"
// STRING: GAMEMD 0x84DA28 "IPX Socket init complete\n"
// STRING: GAMEMD 0x84DD70 "Throwing away malformed packet\n"

// STRING: GAMEMD 0x84D9FC -- address without network portion.
// STRING: GAMEMD 0x84D9C8 -- full network and node address.
// LIBRARY: GAMEMD 0x7C8EF4 -- sprintf.

// FUNCTION: GAMEMD 0x7B0F50 IPXInterfaceClass::GetAdapterAddressString
int IPXInterfaceClass::GetAdapterAddressString(int adapter, char* buffer, int bufferLen)
{
    SOCKADDR_IPX address;
    char text[0x100];

    if (!WinsockInitialised)
        return 0;

    int result = FUN_007B0DD0(adapter, &address);
    if (result)
    {
        if (result == 2)
            sprintf(text, "?? ?? ?? ?? : %02x %02x %02x %02x %02x %02x",
                    (unsigned char)address.sa_nodenum[0], (unsigned char)address.sa_nodenum[1],
                    (unsigned char)address.sa_nodenum[2], (unsigned char)address.sa_nodenum[3],
                    (unsigned char)address.sa_nodenum[4], (unsigned char)address.sa_nodenum[5]);
        else
            sprintf(text, "%02x %02x %02x %02x : %02x %02x %02x %02x %02x %02x",
                    (unsigned char)address.sa_netnum[0], (unsigned char)address.sa_netnum[1],
                    (unsigned char)address.sa_netnum[2], (unsigned char)address.sa_netnum[3],
                    (unsigned char)address.sa_nodenum[0], (unsigned char)address.sa_nodenum[1],
                    (unsigned char)address.sa_nodenum[2], (unsigned char)address.sa_nodenum[3],
                    (unsigned char)address.sa_nodenum[4], (unsigned char)address.sa_nodenum[5]);
        if ((int)strlen(text) >= bufferLen)
            return 0;
        strcpy(buffer, text);
    }
    return result;
}

// FUNCTION: GAMEMD 0x7B10C0  IPXInterfaceClass::Init (slot 15)
bool IPXInterfaceClass::Init(int socketNumber)
{
    if (!WinsockInitialised)
    {
        if (!StartupWinsock())
            return false;
    }
    else if (Socket != -1)
        return false;

    SocketNumber = socketNumber;
    FUN_004068E0("IPX Socket number is %04x\n", socketNumber);

    SOCKADDR_IPX address;
    address.sa_family = AF_IPX;
    memset(address.sa_netnum, 0, sizeof(address.sa_netnum));
    memset(address.sa_nodenum, 0xFF, sizeof(address.sa_nodenum));
    address.sa_socket = htons((unsigned short)socketNumber);

    FUN_004068E0("About to create an IPX socket\n");
    Socket = socket(AF_IPX, SOCK_DGRAM, NSPROTO_IPX);
    if (Socket == -1)
    {
        FUN_004068E0("Failed to create IPX socket - error code %d.\n", WSAGetLastError());
        closesocket(Socket);
        return false;
    }
    FUN_004068E0("IPX Socket created OK\n");

    if (!FUN_007B0DD0(unknown_3F2F8, &address))
    {
        FUN_004068E0("IPX Error - failed to get the net card address\n");
        closesocket(Socket);
        return false;
    }
    FUN_004068E0("IPX net card address is %02x %02x %02x %02x : %02x %02x %02x %02x %02x %02x\n",
                 (unsigned char)address.sa_netnum[0], (unsigned char)address.sa_netnum[1],
                 (unsigned char)address.sa_netnum[2], (unsigned char)address.sa_netnum[3],
                 (unsigned char)address.sa_nodenum[0], (unsigned char)address.sa_nodenum[1],
                 (unsigned char)address.sa_nodenum[2], (unsigned char)address.sa_nodenum[3],
                 (unsigned char)address.sa_nodenum[4], (unsigned char)address.sa_nodenum[5]);
    memcpy(LocalNode, address.sa_nodenum, sizeof(address.sa_nodenum));

    FUN_004068E0("About to bind IPX Socket\n");
    if (bind(Socket, (SOCKADDR*)&address, sizeof(SOCKADDR)) == -1)
    {
        FUN_004068E0("IPX socket bind failed with error code %d.\n", WSAGetLastError());
        closesocket(Socket);
        return false;
    }
    FUN_004068E0("IPX Socket bound OK\n");

    int broadcast = 1;
    int packetType = 4;
    FUN_004068E0("About to set IPX socket option SO_BROADCAST\n");
    if (setsockopt(Socket, SOL_SOCKET, SO_BROADCAST, (char*)&broadcast, 4) == -1)
        FUN_004068E0("Failed to set IPX socket option SO_BROADCAST - error code %d.\n",
                     WSAGetLastError());
    else
        FUN_004068E0("IPX socket option SO_BROADCAST set OK\n");

    FUN_004068E0("About to set IPX socket option IPX_PTYPE\n");
    if (setsockopt(Socket, NSPROTO_IPX, 0x4000, (char*)&packetType, 4) == -1)
        FUN_004068E0("Failed to set IPX protocol option IPX_PTYPE - error code %d.\n",
                     WSAGetLastError());
    else
        FUN_004068E0("IPX socket option IPX_PTYPE set OK\n");

    FUN_004068E0("About to set IPX socket option IPX_FILTERTYPE\n");
    if (setsockopt(Socket, NSPROTO_IPX, 0x4001, (char*)&packetType, 4) == -1)
        FUN_004068E0("Failed to set IPX protocol option IPX_FILTERTYPE - error code %d.\n",
                     WSAGetLastError());
    else
        FUN_004068E0("IPX socket option IPX_FILTERTYPE set OK\n");

    WinsockInterfaceClass::SetSocketBuffers(-1);
    FUN_004068E0("IPX Socket init complete\n");
    return true;
}

// FUNCTION: GAMEMD 0x7B13D0  IPXInterfaceClass::vf_16 (slot 16)
int IPXInterfaceClass::vf_16(HWND, unsigned int message, unsigned int, long lParam)
{
    if (message != 0x473)
        return 1;

    SOCKADDR_IPX address;
    unsigned long network;
    unsigned char node[6];
    int addressLength;

    switch (lParam & 0xFFFF)
    {
    case FD_WRITE:
        if (HIWORD(lParam) != 0)
        {
            vf_9(Socket);
            return 0;
        }
        while (OutBuffers.Count != 0)
        {
            WinsockBufferType* buffer = OutBuffers.Items[0];
            address.sa_family = AF_IPX;
            address.sa_socket = htons((unsigned short)SocketNumber);
            if (buffer->IsBroadcast)
            {
                memcpy(address.sa_netnum, LocalNetwork, 4);
                memcpy(address.sa_nodenum, BroadcastNode, 6);
            }
            else
            {
                ((IPXAddressClass*)buffer)->GetAddress((unsigned char*)&network, node);
                memcpy(address.sa_netnum, &network, 4);
                memcpy(address.sa_nodenum, node, 6);
            }
            if (sendto(Socket, (char*)&buffer->Crc, buffer->BufferLen + 4, 0,
                       (SOCKADDR*)&address, sizeof(SOCKADDR_IPX)) == -1 &&
                WSAGetLastError() != WSAEWOULDBLOCK)
            {
                vf_9(Socket);
                return 0;
            }

            if (OutBuffers.Count > 0)
            {
                OutBuffers.Count--;
                for (int i = 0; i < OutBuffers.Count; i++)
                    OutBuffers.Items[i] = OutBuffers.Items[i + 1];
            }
            if (buffer->IsAllocated)
                operator delete(buffer);
            else
            {
                buffer->InUse = 0;
                StaticOutBuffersInUse--;
            }
        }
        return 0;

    case FD_READ:
        if (HIWORD(lParam) != 0)
        {
            vf_9(Socket);
            return 0;
        }
        addressLength = sizeof(SOCKADDR_IPX);
        int received = recvfrom(Socket, (char*)&ReceiveCrc, 0x280, 0, (SOCKADDR*)&address,
                                &addressLength);
        if (received == -1)
        {
            if (WSAGetLastError() == WSAEWOULDBLOCK)
                return 0;
            vf_9(Socket);
            return 0;
        }
        if (received == 0)
            return 0;

        memcpy(&network, address.sa_netnum, 4);
        memcpy(node, address.sa_nodenum, 6);
        if (memcmp(&network, LocalNetwork, 4) == 0 &&
            memcmp(node, LocalNode, 6) == 0)
            return 0;

        int loss = FUN_007B2730();
        if (loss > 0 && DAT_00886B88.RandomRanged(0, 99) <= loss)
            return 0;

        WinsockBufferType* buffer = AllocInBuffer();
        buffer->BufferLen = received - 4;
        buffer->Crc = ReceiveCrc;
        memcpy(buffer->Payload, ReceiveBuffer, received - 4);
        if (!VerifyPacketCrc(buffer))
        {
            FUN_004068E0("Throwing away malformed packet\n");
            if (!DAT_00B7801C)
                DAT_00B7801C = 1;
            if (buffer->IsAllocated)
                operator delete(buffer);
            else
            {
                buffer->InUse = 0;
                StaticOutBuffersInUse--;  // retail decrements the out counter here
            }
            return 0;
        }
        ((IPXAddressClass*)buffer)->FUN_0053ED20(*(NetworkNumberType*)&network,
                                              *(NodeAddressType*)node, 0);
        WinsockAddItem(InBuffers, buffer);
        return 0;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x7B1770  IPXInterfaceClass::Slot13 (slot 13)
int IPXInterfaceClass::Slot13()
{
    return 1;
}

// FUNCTION: GAMEMD 0x7B1780  IPXInterfaceClass::MessageForSocket (slot 14)
unsigned int IPXInterfaceClass::MessageForSocket(int)
{
    return 0x473;
}
