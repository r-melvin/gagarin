// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | RTTI | existing repository ABI views
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
//   RTTI type descriptor 0x84E1C0 names UDPInterfaceClass; its COL at 0x80EBE0
//   identifies WinsockInterfaceClass as the zero-offset base. The retail table
//   address point 0x7F7A6C has 31 entries by direct PE read; no emitted-table
//   claim is made here. The functions below access the listed member offsets,
//   which are asserted in the shared header. Allocation at 0x52F443 requests
//   0x3F5CC bytes; the header models the observed prefix through that boundary,
//   not a complete original class size. Spans end at their RET instruction.
//   Required out-of-cluster callees are referenced through address-bound
//   declarations in winsock_interface_class.h and the shared input header; sscanf and
//   allocation routines are CRT/library bindings.
#include <stdio.h>
#include <string.h>
#include "udp_interface_class.h"

// LIBRARY: GAMEMD 0x7CA530 -- sscanf (CRT, cdecl).
// LIBRARY: GAMEMD 0x7C8E17 -- operator new.
// LIBRARY: GAMEMD 0x7C8B3D -- operator delete.

// STRING: GAMEMD 0x83D9FC "%d.%d.%d.%d"
// STRING: GAMEMD 0x84E250 "About to open primary UDP socket\n"
// STRING: GAMEMD 0x84E224 "About to bind the UDP socket to port %d\n"
// STRING: GAMEMD 0x84E204 "Bind failed with error code %d\n"
// STRING: GAMEMD 0x84E1E0 "Primary UDP Socket init complete\n"
// STRING: GAMEMD 0x84E2D4 "About to open spare UDP socket\n"
// STRING: GAMEMD 0x84E2BC "Got spare socket %d\n"
// STRING: GAMEMD 0x84E294 "Failed to bind spare socket to port %d\n"
// STRING: GAMEMD 0x84E274 "Spare UDP Socket init complete\n"
// STRING: GAMEMD 0x84E2F4 "Closing spare socket %d\n"
// STRING: GAMEMD 0x84E3B0 "About to query the host name\n"
// STRING: GAMEMD 0x84E39C "Host name is '%s'\n"
// STRING: GAMEMD 0x84CA08 "About to call gethostbyname\n"
// STRING: GAMEMD 0x830E28 "gethostbyname failed! Error code %d\n"
// STRING: GAMEMD 0x84E378 "Found local address: %d.%d.%d.%d\n"
// STRING: GAMEMD 0x84E354 "About to open alternate UDP socket\n"
// STRING: GAMEMD 0x84E334 "About to bind the UDP socket\n"
// STRING: GAMEMD 0x84E310 "Alternate UDP Socket init complete\n"
// STRING: GAMEMD 0x84E3D0 "Async select failed on spare socket.\n"
// STRING: GAMEMD 0x84E3F8 "Marking address %d.%d.%d.%d ; %d as unreachable\n"

// FUNCTION: GAMEMD 0x7B2F90  UDPInterfaceClass::ClearBroadcastAddresses (slot 12)
void UDPInterfaceClass::ClearBroadcastAddresses()
{
    while (BroadcastAddresses.Count != 0)
    {
        operator delete(BroadcastAddresses.Items[0]);
        if (BroadcastAddresses.Count > 0)
        {
            BroadcastAddresses.Count--;
            for (int i = 0; i < BroadcastAddresses.Count; i++)
                BroadcastAddresses.Items[i] = BroadcastAddresses.Items[i + 1];
        }
    }
}

// FUNCTION: GAMEMD 0x7B2FF0  UDPInterfaceClass::AddBroadcastAddress (slot 11)
void UDPInterfaceClass::AddBroadcastAddress(const char* dottedAddress, unsigned short port)
{
    unsigned char* address = (unsigned char*)operator new(4);
    int a, b, c, d;
    sscanf(dottedAddress, "%d.%d.%d.%d", &a, &b, &c, &d);
    address[0] = (unsigned char)a;
    address[1] = (unsigned char)b;
    address[2] = (unsigned char)c;
    address[3] = (unsigned char)d;
    if (port == 0)
        port = DAT_00841F30;
    BroadcastPorts[BroadcastAddresses.Count] = port;
    WinsockAddItem(BroadcastAddresses, address);
}

// FUNCTION: GAMEMD 0x7B30B0  UDPInterfaceClass::OpenPrimarySocket (slot 23)
bool UDPInterfaceClass::OpenPrimarySocket(unsigned short port)
{
    if (Socket != -1)
    {
        closesocket(Socket);
        Socket = -1;
    }
    FUN_004068E0("About to open primary UDP socket\n");
    Socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (Socket == -1)
        return false;

    SOCKADDR_IN address;
    LINGER linger;
    address.sin_family = AF_INET;
    if (port != 0)
    {
        PrimaryPort = port;
        address.sin_port = htons(port);
    }
    else
    {
        PrimaryPort = 0;
        address.sin_port = htons(DAT_00841F30);
    }
    address.sin_addr.s_addr = htonl(0);
    FUN_004068E0("About to bind the UDP socket to port %d\n", port);
    if (bind(Socket, (SOCKADDR*)&address, sizeof(address)) == -1)
    {
        FUN_004068E0("Bind failed with error code %d\n", WSAGetLastError());
        vf_1();
        return false;
    }
    linger.l_onoff = 0;
    linger.l_linger = 0;
    setsockopt(Socket, SOL_SOCKET, SO_LINGER, (char*)&linger, 4);
    WinsockInterfaceClass::SetSocketBuffers(-1);
    FUN_004068E0("Primary UDP Socket init complete\n");
    return true;
}

// FUNCTION: GAMEMD 0x7B31E0  UDPInterfaceClass::OpenSpareSocket (slot 26)
bool UDPInterfaceClass::OpenSpareSocket(unsigned short port)
{
    if (port == 0)
        return false;

    for (int i = 0; i < SpareSocketCount; i++)
    {
        if (SparePorts[i] == port)
            return false;
    }

    FUN_004068E0("About to open spare UDP socket\n");
    SOCKET spare = socket(AF_INET, SOCK_DGRAM, 0);
    if (spare == -1)
        return false;
    FUN_004068E0("Got spare socket %d\n", spare);

    SOCKADDR_IN address;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(0);
    FUN_004068E0("About to bind the UDP socket to port %d\n", port);
    if (bind(spare, (SOCKADDR*)&address, sizeof(address)) == -1)
    {
        closesocket(spare);
        FUN_004068E0("Failed to bind spare socket to port %d\n", port);
        return false;
    }

    SparePorts[SpareSocketCount] = port;
    SpareSockets[SpareSocketCount] = spare;
    SpareSocketCount++;
    WinsockInterfaceClass::SetSocketBuffers(spare);
    FUN_004068E0("Spare UDP Socket init complete\n");
    return true;
}

// FUNCTION: GAMEMD 0x7B3310  UDPInterfaceClass::CloseSpareSocket (slot 27)
void UDPInterfaceClass::CloseSpareSocket(unsigned short port)
{
    if (port == 0)
        return;

    for (int i = 0; i < SpareSocketCount; i++)
    {
        if (SparePorts[i] == port)
        {
            FUN_004068E0("Closing spare socket %d\n", SpareSockets[i]);
            closesocket(SpareSockets[i]);
            if (SpareSockets[i] == CurrentSpareSocket)
                CurrentSpareSocket = -1;
            for (int j = i; j < SpareSocketCount - 1; j++)
            {
                SpareSockets[j] = SpareSockets[j + 1];
                SparePorts[j] = SparePorts[j + 1];
            }
            SpareSocketCount--;
            return;
        }
    }
}

// FUNCTION: GAMEMD 0x7B33D0  UDPInterfaceClass::SelectSpareSocket (slot 29)
void UDPInterfaceClass::SelectSpareSocket(unsigned short port)
{
    if (port != 0 && port != DAT_00841F30)
    {
        for (int i = 0; i < SpareSocketCount; i++)
        {
            if (SparePorts[i] == port)
            {
                CurrentSpareSocket = SpareSockets[i];
                return;
            }
        }
    }
    CurrentSpareSocket = -1;
}

// FUNCTION: GAMEMD 0x7B3430  UDPInterfaceClass::StartupWinsockInit (slot 25)
bool UDPInterfaceClass::StartupWinsockInit()
{
    if (StartupWinsock())
    {
        SpareSocketCount = 0;
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x7B3450  UDPInterfaceClass::Init (slot 15)
bool UDPInterfaceClass::Init(int)
{
    char hostName[0x80];

    if (!WinsockInitialised)
    {
        if (!StartupWinsockInit())
            return false;
    }

    OpenPrimarySocket(DAT_00841F30);
    FUN_004068E0("About to query the host name\n");
    if (gethostname(hostName, 0x80) != 0)
        FUN_004068E0("Host name is '%s'\n", hostName);

    FUN_004068E0("About to call gethostbyname\n");
    HOSTENT* host = gethostbyname(hostName);
    if (host == 0)
        FUN_004068E0("gethostbyname failed! Error code %d\n", WSAGetLastError());

    while (LocalAddresses.Count != 0)
    {
        operator delete(LocalAddresses.Items[0]);
        if (LocalAddresses.Count > 0)
        {
            LocalAddresses.Count--;
            for (int i = 0; i < LocalAddresses.Count; i++)
                LocalAddresses.Items[i] = LocalAddresses.Items[i + 1];
        }
    }

    char** list = host->h_addr_list;
    while (*list != 0)
    {
        unsigned long ip = *(unsigned long*)*list;
        list++;
        FUN_004068E0("Found local address: %d.%d.%d.%d\n", ip & 0xFF, (ip >> 8) & 0xFF,
                     (ip >> 16) & 0xFF, ip >> 24);
        unsigned long* copy = (unsigned long*)operator new(4);
        *copy = ip;
        WinsockAddItem(LocalAddresses, (unsigned char*)copy);
    }

    FUN_004068E0("About to open alternate UDP socket\n");
    unknown_3F070 = socket(AF_INET, SOCK_DGRAM, 0);
    if (unknown_3F070 == -1)
        return false;

    SOCKADDR_IN address;
    LINGER linger;
    address.sin_family = AF_INET;
    address.sin_port = htons(DAT_00841F38);
    address.sin_addr.s_addr = htonl(0);
    FUN_004068E0("About to bind the UDP socket\n");
    if (bind(unknown_3F070, (SOCKADDR*)&address, sizeof(address)) == -1)
    {
        vf_1();
        return false;
    }
    linger.l_onoff = 0;
    linger.l_linger = 0;
    setsockopt(unknown_3F070, SOL_SOCKET, SO_LINGER, (char*)&linger, 4);
    WinsockInterfaceClass::SetSocketBuffers(unknown_3F070);
    FUN_004068E0("Alternate UDP Socket init complete\n");
    return true;
}

// FUNCTION: GAMEMD 0x7B36C0  UDPInterfaceClass::SendPacket (slot 3)
void UDPInterfaceClass::SendPacket(void* packet, int packetLen, void* address,
                                   int addressLen, bool alternate,
                                   unsigned char unknown18, unsigned short unknown1A)
{
    if (address != 0 && ((IPXAddressClass*)address)->IsBroadcast())
        Broadcast(packet, packetLen, alternate);
    else
        WinsockInterfaceClass::SendPacket(packet, packetLen, address, addressLen, alternate,
                                          unknown18, unknown1A);
}

// FUNCTION: GAMEMD 0x7B3720  UDPInterfaceClass::Broadcast (slot 4)
void UDPInterfaceClass::Broadcast(void* packet, int packetLen, bool alternate)
{
    int i = 0;
    if (BroadcastAddresses.Count > 0)
    {
        unsigned short* port = BroadcastPorts;
        do
        {
            WinsockBufferType* buffer = AllocOutBuffer(alternate);
            memcpy(buffer->Payload, packet, packetLen);
            buffer->BufferLen = packetLen;
            buffer->IsBroadcast = 1;
            memset(buffer->Address, 0, 16);
            *(unsigned long*)(buffer->Address + 4) = *(unsigned long*)BroadcastAddresses.Items[i];
            buffer->unknown_1A = *port;
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
            FUN_005D4D50();
            i++;
            port++;
        } while (i < BroadcastAddresses.Count);
    }
}

// FUNCTION: GAMEMD 0x7B3890  UDPInterfaceClass::StartListening (slot 7)
bool UDPInterfaceClass::StartListening()
{
    // Retail ignores a failure of the base call and still reports success.
    if (WinsockInterfaceClass::StartListening())
    {
        for (int i = 0; i < SpareSocketCount; i++)
        {
            if (WSAAsyncSelect(SpareSockets[i], DAT_00B73550, MessageForSocket(-1), 3) == -1)
            {
                FUN_004068E0("Async select failed on spare socket.\n");
                return false;
            }
        }
    }
    FUN_005D4D50();
    return true;
}

// FUNCTION: GAMEMD 0x7B3900  UDPInterfaceClass::StopListening (slot 8)
void UDPInterfaceClass::StopListening()
{
    WinsockInterfaceClass::StopListening();
    CloseAllSpareSockets();
}

// FUNCTION: GAMEMD 0x7B3920  UDPInterfaceClass::MarkAddressUnreachable (slot 30)
void UDPInterfaceClass::MarkAddressUnreachable(unsigned char* address, unsigned short port)
{
    if (UnreachableCount < 16)
    {
        for (int i = 0; i < UnreachableCount; i++)
        {
            if (port == UnreachablePorts[i] && *(unsigned long*)address == UnreachableAddresses[i])
                return;
        }
        FUN_004068E0("Marking address %d.%d.%d.%d ; %d as unreachable\n", address[0], address[1],
                     address[2], address[3], port);
        UnreachableAddresses[UnreachableCount] = *(unsigned long*)address;
        UnreachablePorts[UnreachableCount] = port;
        UnreachableCount++;
    }
}

// FUNCTION: GAMEMD 0x7B3A20  UDPInterfaceClass::CloseAllSpareSockets (slot 28)
void UDPInterfaceClass::CloseAllSpareSockets()
{
    for (int i = 0; i < SpareSocketCount; i++)
    {
        FUN_004068E0("Closing spare socket %d\n", SpareSockets[i]);
        WSAAsyncSelect(SpareSockets[i], DAT_00B73550, 0, 0);
        closesocket(SpareSockets[i]);
    }
    SpareSocketCount = 0;
    CurrentSpareSocket = -1;
}

// FUNCTION: GAMEMD 0x7B40F0  UDPInterfaceClass::Slot13 (slot 13)
int UDPInterfaceClass::Slot13()
{
    return 2;
}

// FUNCTION: GAMEMD 0x7B4100  UDPInterfaceClass::MessageForSocket (slot 14)
unsigned int UDPInterfaceClass::MessageForSocket(int socket)
{
    if (socket == Socket || socket == -1)
        return 0x474;
    return socket == unknown_3F070 ? 0x475 : 0;
}

// FUNCTION: GAMEMD 0x7B4140  UDPInterfaceClass::GetNumLocalAddresses (slot 18)
int UDPInterfaceClass::GetNumLocalAddresses()
{
    return LocalAddresses.Count;
}

// FUNCTION: GAMEMD 0x7B4150  UDPInterfaceClass::GetLocalAddress (slot 19)
unsigned char* UDPInterfaceClass::GetLocalAddress(int index)
{
    return LocalAddresses.Items[index];
}

// FUNCTION: GAMEMD 0x7B4160  UDPInterfaceClass::GetPrimaryPort (slot 24)
unsigned short UDPInterfaceClass::GetPrimaryPort()
{
    return PrimaryPort;
}
