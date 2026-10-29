// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | RTTI
//   Original translation unit TU291 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x7b17d0-0x7b2b9f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
//
// Frozen M1 recovery, reconfirmed against pinned retail entry spans and
// winsock.rows.tsv. Unattested virtuals are named vf_<slot>.
// The selected methods are the unclaimed ordinary WinsockInterfaceClass base
// entries only; StartListening and both buffer-drain methods remain in their
// existing TUs. No constructor, destructor, or ShutdownWinsock body is here.
//
// Retail PAUWinsockBufferType@WinsockInterfaceClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.
//
//   The selected bodies and their referenced field offsets come from the
//   pinned retail gamemd.exe v1.001. The static pool arrays are address-scoped
//   layout fields, each 128 * 0x2A0 bytes; this TU does not claim constructor
//   initialization or ownership beyond the observed allocator accesses.

#include <string.h>
#include "transport/winsock_interface_class.h"

// Globals read by this TU's static initialisers (placeholder names).
// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F79A8
extern const double DAT_007F79A8;
// GLOBAL: GAMEMD 0xB78040
extern double DAT_00B78040;

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

#include "../core/vector_class_operations.h"
#include "transport/winsock_interface_class.h"

// VTABLE: GAMEMD 0x7F7A3C -- VectorClass<WinsockInterfaceClass::WinsockBufferType*>.
template class VectorClass<WinsockInterfaceClass::WinsockBufferType*>;
typedef VectorClass<WinsockInterfaceClass::WinsockBufferType*> GgWinsockbufferVectorClass;
GG_STATIC_ASSERT(offsetof(GgWinsockbufferVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgWinsockbufferVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgWinsockbufferVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgWinsockbufferVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7F7A1C -- DynamicVectorClass<WinsockInterfaceClass::WinsockBufferType*>.
template class DynamicVectorClass<WinsockInterfaceClass::WinsockBufferType*>;
typedef DynamicVectorClass<WinsockInterfaceClass::WinsockBufferType*> GgWinsockbufferDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgWinsockbufferDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgWinsockbufferDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgWinsockbufferDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgWinsockbufferDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgWinsockbufferDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgWinsockbufferDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(WinsockInterfaceClass::WinsockBufferType*) == 4);

#include <new>
#include "transport/winsock_interface_class.h"

#include "../core/global_getter_family_methods.h"

//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xB780A0
extern int DAT_00B780A0;


void FUN_007B2720(int a1);


#include "winsock_discard_methods.h"

static inline void DiscardQueue(WinsockInterfaceClass::WinsockBufferType**& items, int& count,
                                int& inUse, int& pos)
{
    while (count != 0)
    {
        WinsockInterfaceClass::WinsockBufferType* packet = items[0];

        if (packet->IsAllocated != 0)
        {
            operator delete(packet);
        }
        else
        {
            packet->InUse = 0;
            inUse--;
        }

        if (count > 0)
        {
            count--;
            for (int i = 0; i < count; i++)
                items[i] = items[i + 1];
        }
    }

    inUse = 0;
    pos = 0;
}

#include "winsock_interface_discard_methods.h"

#include "winsock_listen_methods.h"

// STRING: GAMEMD 0x84DEA4 "Async select failed on primary socket - error code %d.\n"
// STRING: GAMEMD 0x84DE68 "Async select failed on alternate socket - error code %d.\n"

// dynamic initializer for DAT_00B78090

// GLOBAL: GAMEMD 0x00B78090
extern double DAT_00B78090;

// dynamic initializer for DAT_00B78078

// GLOBAL: GAMEMD 0x00B78078
extern double DAT_00B78078;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7B1BC0  WinsockInterfaceClass::StartListening (slot 7)
// Register both sockets for asynchronous read/write notification on the main
// window (lEvent 3 = FD_READ | FD_WRITE). The message id comes from slot 14
// (-1 asks for the primary socket's). Either failure logs the Winsock error and
// reports false; the alternate socket is skipped when it is not open.
bool WinsockInterfaceClass::StartListening()
{
    if (WSAAsyncSelect(Socket, DAT_00B73550, MessageForSocket(-1), 3) == -1)
    {
        FUN_004068E0("Async select failed on primary socket - error code %d.\n",
                     WSAGetLastError());
        return false;
    }

    if (unknown_3F070 != -1)
    {
        if (WSAAsyncSelect(unknown_3F070, DAT_00B73550, MessageForSocket(unknown_3F070), 3) == -1)
        {
            FUN_004068E0("Async select failed on alternate socket - error code %d.\n",
                         WSAGetLastError());
            return false;
        }
    }

    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7B1C50  WinsockInterfaceClass::StopListening (slot 8)
void WinsockInterfaceClass::StopListening()
{
    if (Socket != -1 && DAT_00B73550)
        WSAAsyncSelect(Socket, DAT_00B73550, 0, 0);
    if (unknown_3F070 != -1 && DAT_00B73550)
        WSAAsyncSelect(unknown_3F070, DAT_00B73550, 0, 0);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7B1CA0  WinsockInterfaceClass::DiscardInBuffers (slot 5)
// Drain the inbound queue. Each head packet is either handed back to the game
// heap or merely un-marked, then unlinked with DynamicVectorClass::RemoveItem(0)
// written out inline: bounds check, decrement, shift the tail down. Both
// counters are zeroed at the end rather than trusted to have reached zero.
void WinsockInterfaceClass::DiscardInBuffers()
{
    while (InBuffers.Count != 0)
    {
        WinsockBufferType* packet = InBuffers.Items[0];

        if (packet->IsAllocated != 0)
        {
            operator delete(packet);
        }
        else
        {
            packet->InUse = 0;
            StaticInBuffersInUse--;
        }

        if (InBuffers.Count > 0)
        {
            InBuffers.Count--;
            for (int i = 0; i < InBuffers.Count; i++)
                InBuffers.Items[i] = InBuffers.Items[i + 1];
        }
    }

    StaticInBuffersInUse = 0;
    StaticInBufferPos = 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7B1D10  WinsockInterfaceClass::DiscardOutBuffers (slot 6)
void WinsockInterfaceClass::DiscardOutBuffers()
{
    DiscardQueue(OutBuffers.Items, OutBuffers.Count, StaticOutBuffersInUse, StaticOutBufferPos);
    DiscardQueue(AltOutBuffers.Items, AltOutBuffers.Count, StaticAltOutBuffersInUse,
                 StaticAltOutBufferPos);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7B20E0 -- WinsockInterfaceClass::AllocOutBuffer.
WinsockInterfaceClass::WinsockBufferType* WinsockInterfaceClass::AllocOutBuffer(bool alternate)
{
    WinsockBufferType* buffer = 0;

    if (!alternate)
    {
        if (StaticOutBuffersInUse == 128)
        {
            buffer = (WinsockBufferType*)operator new(sizeof(WinsockBufferType));
            buffer->IsAllocated = 1;
            buffer->InUse = 1;
        }
        else
        {
            for (int i = 0; i < 128; i++)
            {
                int pos = StaticOutBufferPos++;
                if (StaticOutBufferPos > 127)
                    StaticOutBufferPos = 0;
                if (!StaticOutBuffers[pos].InUse)
                {
                    buffer = &StaticOutBuffers[pos];
                    buffer->InUse = 1;
                    StaticOutBuffersInUse++;
                    break;
                }
            }
        }
        if (buffer)
        {
            buffer->unknown_17 = 0;
            buffer->unknown_18 = 0;
        }
    }
    else
    {
        if (StaticAltOutBuffersInUse == 128)
        {
            buffer = (WinsockBufferType*)operator new(sizeof(WinsockBufferType));
            buffer->IsAllocated = 1;
            buffer->InUse = 1;
        }
        else
        {
            for (int i = 0; i < 128; i++)
            {
                int pos = StaticAltOutBufferPos++;
                if (StaticAltOutBufferPos > 127)
                    StaticAltOutBufferPos = 0;
                if (!StaticAltOutBuffers[pos].InUse)
                {
                    buffer = &StaticAltOutBuffers[pos];
                    buffer->InUse = 1;
                    StaticAltOutBuffersInUse++;
                    break;
                }
            }
        }
        if (buffer)
        {
            buffer->unknown_17 = 1;
            buffer->unknown_18 = 0;
        }
    }
    return buffer;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7B2240 -- WinsockInterfaceClass::AllocInBuffer.
WinsockInterfaceClass::WinsockBufferType* WinsockInterfaceClass::AllocInBuffer()
{
    WinsockBufferType* buffer = 0;

    if (StaticInBuffersInUse == 128)
    {
        buffer = (WinsockBufferType*)operator new(sizeof(WinsockBufferType));
        buffer->IsAllocated = 1;
        buffer->InUse = 1;
    }
    else
    {
        for (int i = 0; i < 128; i++)
        {
            int pos = StaticInBufferPos++;
            if (StaticInBufferPos > 127)
                StaticInBufferPos = 0;
            if (!StaticInBuffers[pos].InUse)
            {
                buffer = &StaticInBuffers[pos];
                buffer->InUse = 1;
                StaticInBuffersInUse++;
                break;
            }
        }
    }
    if (buffer)
    {
        buffer->unknown_17 = 0;
        buffer->unknown_18 = 0;
    }
    return buffer;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7B25E0  WinsockInterfaceClass::vf_9 (slot 9)
void WinsockInterfaceClass::vf_9(SOCKET socket)
{
    int error;
    int length = 4;
    getsockopt(socket, SOL_SOCKET, SO_ERROR, (char*)&error, &length);
    error = 0;
    setsockopt(socket, SOL_SOCKET, SO_ERROR, (char*)&error, length);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
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

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7B2720
// Stores to a global.
void FUN_007B2720(int a1)
{
    DAT_00B780A0 = a1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x007B2730
int FUN_007B2730()
{
    return DAT_00B780A0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7B2740  WinsockInterfaceClass::Slot13 (base; slot 13)
int WinsockInterfaceClass::Slot13()
{
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7B2750  WinsockInterfaceClass::MessageForSocket (base; slot 14)
unsigned int WinsockInterfaceClass::MessageForSocket(int)
{
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7B2760  WinsockInterfaceClass::Init (base; slot 15)
bool WinsockInterfaceClass::Init(int)
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7B2770  WinsockInterfaceClass::vf_16 (base; slot 16)
int WinsockInterfaceClass::vf_16(HWND, unsigned int, unsigned int, long)
{
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x7B2840
// DynamicVectorClass<WinsockInterfaceClass::WinsockBufferType*>::Clear

// FUNCTION: GAMEMD 0x7B2870
// DynamicVectorClass<WinsockInterfaceClass::WinsockBufferType*>::Slot5

// FUNCTION: GAMEMD 0x7B2890
// VectorClass<WinsockInterfaceClass::WinsockBufferType*>::Slot6

// FUNCTION: GAMEMD 0x7B28A0
// VectorClass<WinsockInterfaceClass::WinsockBufferType*>::operator==

// FUNCTION: GAMEMD 0x7B28E0
// VectorClass<WinsockInterfaceClass::WinsockBufferType*>::SetCapacity

// FUNCTION: GAMEMD 0x7B2990
// VectorClass<WinsockInterfaceClass::WinsockBufferType*>::Clear

// FUNCTION: GAMEMD 0x7B29C0
// VectorClass<WinsockInterfaceClass::WinsockBufferType*>::FindItemIndex

// FUNCTION: GAMEMD 0x7B2A00
// VectorClass<WinsockInterfaceClass::WinsockBufferType*>::Slot5

// FUNCTION: GAMEMD 0x7B2A20
// DynamicVectorClass<WinsockInterfaceClass::WinsockBufferType*>::SetCapacity

// FUNCTION: GAMEMD 0x7B2AD0
// DynamicVectorClass<WinsockInterfaceClass::WinsockBufferType*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x7B2B00
// VectorClass<WinsockInterfaceClass::WinsockBufferType*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x7B2B50
// DynamicVectorClass<WinsockInterfaceClass::WinsockBufferType*>::scalar deleting destructor

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xB780A0
int DAT_00B780A0;
// GLOBAL: GAMEMD 0x84DD9C
extern const int DAT_0084DD9C = 131072;
// GLOBAL: GAMEMD 0x84DDA0
extern const int DAT_0084DDA0 = 131072;
// END defined globals
