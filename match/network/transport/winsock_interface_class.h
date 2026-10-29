// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Base COL at 0x80EAF8 points to TypeDescriptor 0x84D8D0, whose name is
//   .?AVWinsockInterfaceClass@@. Base vtable address point 0x7F79BC has 23
//   slots, read directly from pinned retail PE.
//   Slot targets are documented below from the direct table read; this header
//   does not claim compiler emission or final-link selection of that table.
//   Buffer allocations at 0x7B20FF and 0x7B2255 push 0x2A0 before
//   operator new; direct PE disassembly reconfirms the queued-buffer extent.
//   Touched offsets are pinned by the three included functions' retail
//   instructions. Base size is a layout model (no direct base allocation
//   established); it is not an allocation-size claim.
#ifndef GG_MATCH_NETWORK_TRANSPORT_WINSOCK_INTERFACE_CLASS_H
#define GG_MATCH_NETWORK_TRANSPORT_WINSOCK_INTERFACE_CLASS_H

#include <stddef.h>
#include <windows.h>
#include <winsock.h>
#include <wsipx.h>
#include "../../_rt/gg_static_assert.h"
#include "../../core/vector_class.h"
#include "../../platform/input_manager_class_methods.h"
#include "packet_interface_global.h"

// Only imports/globals reached by StartListening and the two buffer drains.
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- log sink used on socket errors.
extern "C" int __cdecl FUN_004068E0(const char* format, ...);
// LIBRARY: GAMEMD 0x7C8B3D -- operator delete target used by the buffer drains;
// the vector object also has an _gg_free relocation to this address.
// GLOBAL: GAMEMD 0x00B73550 -- window passed to WSAAsyncSelect.
extern HWND DAT_00B73550;
// LIBRARY: GAMEMD 0x7C89BC (decl; reloc) -- imported WSAAsyncSelect target.
// LIBRARY: GAMEMD 0x7C897A (decl; reloc) -- imported WSAGetLastError target.

// Additional ordinary-base dependencies used by the isolated selected methods.
// FUNCTION: GAMEMD 0x64DE80 (decl; reloc) -- one checksum update.
void FUN_0064DE80(unsigned long* crc, unsigned long value);

// The retail SendPacket/Broadcast methods inline this vector AddItem behavior.
template<class T> inline bool WinsockAddItem(DynamicVectorClass<T>& v, T item)
{
    if (v.Count >= v.Capacity)
    {
        if ((v.IsAllocated || v.Capacity == 0) && v.CapacityIncrement > 0)
        {
            if (!v.SetCapacity(v.Capacity + v.CapacityIncrement, 0))
                return false;
        }
        else
            return false;
    }
    int index = v.Count++;
    v.Items[index] = item;
    return true;
}

// Base slot targets are pinned from the retail table at 0x7F79BC. Remaining
// slots are retained to keep slot indices.
// VTABLE: GAMEMD 0x7F79BC -- WinsockInterfaceClass base (23 retail slots;
//   address-point target order: 7B2780, 7B1B80, 7B22E0, 7B23B0, 7B24E0,
//   7B1CA0, 7B1D10, 7B1BC0, 7B1C50, 7B25E0, 7B2630, 7B1720, 7B1730,
//   7B2740, 7B2750, 7B2760, 7B2770, 7B26D0, 7B1740, 7B1750, 7B1760,
//   7B1FD0, 7B2050; this is a binary table binding, not emitted-table proof.)
struct WinsockInterfaceClassVtableLayout
{
    void* slot_00; void* slot_01; void* slot_02; void* slot_03;
    void* slot_04; void* slot_05; void* slot_06; void* slot_07;
    void* slot_08; void* slot_09; void* slot_0A; void* slot_0B;
    void* slot_0C; void* slot_0D; void* slot_0E; void* slot_0F;
    void* slot_10; void* slot_11; void* slot_12; void* slot_13;
    void* slot_14; void* slot_15; void* slot_16;
};
#define GG_WINSOCK_SLOT_ASSERT(n) \
    GG_STATIC_ASSERT(offsetof(WinsockInterfaceClassVtableLayout, slot_##n) == 4 * 0x##n)
GG_WINSOCK_SLOT_ASSERT(00); GG_WINSOCK_SLOT_ASSERT(01); GG_WINSOCK_SLOT_ASSERT(02);
GG_WINSOCK_SLOT_ASSERT(03); GG_WINSOCK_SLOT_ASSERT(04); GG_WINSOCK_SLOT_ASSERT(05);
GG_WINSOCK_SLOT_ASSERT(06); GG_WINSOCK_SLOT_ASSERT(07); GG_WINSOCK_SLOT_ASSERT(08);
GG_WINSOCK_SLOT_ASSERT(09); GG_WINSOCK_SLOT_ASSERT(0A); GG_WINSOCK_SLOT_ASSERT(0B);
GG_WINSOCK_SLOT_ASSERT(0C); GG_WINSOCK_SLOT_ASSERT(0D); GG_WINSOCK_SLOT_ASSERT(0E);
GG_WINSOCK_SLOT_ASSERT(0F); GG_WINSOCK_SLOT_ASSERT(10); GG_WINSOCK_SLOT_ASSERT(11);
GG_WINSOCK_SLOT_ASSERT(12); GG_WINSOCK_SLOT_ASSERT(13); GG_WINSOCK_SLOT_ASSERT(14);
GG_WINSOCK_SLOT_ASSERT(15); GG_WINSOCK_SLOT_ASSERT(16);
#undef GG_WINSOCK_SLOT_ASSERT
GG_STATIC_ASSERT(sizeof(WinsockInterfaceClassVtableLayout) == 0x5C);

class WinsockInterfaceClass
{
public:
    // FUNCTION: GAMEMD 0x7B19C0 (decl; reloc)
    WinsockInterfaceClass();

    struct WinsockBufferType
    {
        unsigned char Address[0x10];
        int BufferLen;
        unsigned char IsBroadcast;
        unsigned char InUse;
        unsigned char IsAllocated;
        unsigned char unknown_17;
        unsigned char unknown_18;
        unsigned char unknown_19;
        unsigned short unknown_1A;
        unsigned long Crc;
        unsigned char Payload[0x280];
    };

    // The 23 virtual declarations below preserve the binary slot sequence.
    // Signatures at methods not implemented in this bounded candidate remain
    // address-level ABI models and are not matched source claims here.
    // FUNCTION: GAMEMD 0x7B1AB0 (decl; reloc) -- ordinary virtual destructor.
    // SYNTHETIC: GAMEMD 0x7B2780 (decl; reloc) -- scalar deleting destructor, slot 0 target.
    virtual ~WinsockInterfaceClass();
    // FUNCTION: GAMEMD 0x7B1B80 (decl; reloc) -- base slot 1 target.
    virtual void vf_1();
    // FUNCTION: GAMEMD 0x7B22E0 (decl; reloc) -- base slot 2 target.
    virtual int GetPacket(void* packet, int* packetLen, void* address,
                          unsigned int* addressLen, unsigned short* unknown1A);
    // FUNCTION: GAMEMD 0x7B23B0 (decl; reloc) -- base slot 3 target.
    virtual void SendPacket(void* packet, int packetLen, void* address,
                            int addressLen, bool alternate,
                            unsigned char unknown18, unsigned short unknown1A);
    // FUNCTION: GAMEMD 0x7B24E0 (decl; reloc) -- base slot 4 target.
    virtual void Broadcast(void* packet, int packetLen, bool alternate);
    // FUNCTION: GAMEMD 0x7B1CA0 (decl; reloc) -- base slot 5.
    virtual void DiscardInBuffers();
    // FUNCTION: GAMEMD 0x7B1D10 (decl; reloc) -- base slot 6.
    virtual void DiscardOutBuffers();
    // FUNCTION: GAMEMD 0x7B1BC0 (decl; reloc) -- base slot 7.
    virtual bool StartListening();
    // FUNCTION: GAMEMD 0x7B1C50 (decl; reloc) -- base slot 8 target.
    virtual void StopListening();
    // FUNCTION: GAMEMD 0x7B25E0 (decl; reloc) -- base slot 9 target.
    virtual void vf_9(SOCKET socket);
    // FUNCTION: GAMEMD 0x7B2630 (decl; reloc) -- base slot 10 target.
    virtual bool SetSocketBuffers(SOCKET socket);
    // FUNCTION: GAMEMD 0x7B1720 (decl; reloc) -- base slot 11 target.
    virtual void AddBroadcastAddress(const char* dottedAddress,
                                     unsigned short port);
    // FUNCTION: GAMEMD 0x7B1730 (decl; reloc) -- base slot 12 target.
    virtual void ClearBroadcastAddresses();
    // FUNCTION: GAMEMD 0x7B2740 (decl; reloc) -- base slot 13 target.
    virtual int Slot13();
    // FUNCTION: GAMEMD 0x7B2750 (decl; reloc) -- base slot 14 target.
    virtual unsigned int MessageForSocket(int socket);
    // FUNCTION: GAMEMD 0x7B2760 (decl; reloc) -- base slot 15 target.
    virtual bool Init(int socketNumber);
    // FUNCTION: GAMEMD 0x7B2770 (decl; reloc) -- base slot 16 target.
    virtual int vf_16(HWND window, unsigned int message,
                               unsigned int wParam, long lParam);
    // FUNCTION: GAMEMD 0x7B26D0 (decl; reloc) -- base slot 17 target.
    virtual bool GetHostName(char* name, int nameLen);
    // FUNCTION: GAMEMD 0x7B1740 (decl; reloc) -- base slot 18 target.
    virtual int GetNumLocalAddresses();
    // FUNCTION: GAMEMD 0x7B1750 (decl; reloc) -- base slot 19 target.
    virtual unsigned char* GetLocalAddress(int index);
    // FUNCTION: GAMEMD 0x7B1760 (decl; reloc) -- base slot 20 target.
    virtual void Slot20(int value);
    // FUNCTION: GAMEMD 0x7B1FD0 (decl; reloc) -- base slot 21 target.
    virtual void ComputePacketCrc(WinsockBufferType* packet);
    // FUNCTION: GAMEMD 0x7B2050 (decl; reloc) -- base slot 22 target.
    virtual bool VerifyPacketCrc(WinsockBufferType* packet);

    // FUNCTION: GAMEMD 0x7B1B50 (decl; reloc) -- shared shutdown body.
    void ShutdownWinsock();

    // FUNCTION: GAMEMD 0x7B20E0 (decl; reloc) -- base out-buffer allocator.
    WinsockBufferType* AllocOutBuffer(bool alternate);
    // FUNCTION: GAMEMD 0x7B2240 (decl; reloc) -- IPX receive-buffer allocator.
    WinsockBufferType* AllocInBuffer();
    // FUNCTION: GAMEMD 0x7B1DE0 (decl; reloc) -- IPX startup path.
    bool StartupWinsock();

    int unknown_04;                               // +0x04, ctor stores 0x240
    DynamicVectorClass<WinsockBufferType*> InBuffers;       // +0x08
    DynamicVectorClass<WinsockBufferType*> OutBuffers;      // +0x20
    DynamicVectorClass<WinsockBufferType*> AltOutBuffers;  // +0x38
    WinsockBufferType StaticInBuffers[128];        // +0x50 .. +0x1504F
    WinsockBufferType StaticOutBuffers[128];       // +0x15050 .. +0x2A04F
    WinsockBufferType StaticAltOutBuffers[128];    // +0x2A050 .. +0x3F04F
    int StaticInBufferPos;                         // +0x3F050
    int StaticOutBufferPos;                        // +0x3F054
    int StaticAltOutBufferPos;                     // +0x3F058
    int StaticInBuffersInUse;                      // +0x3F05C
    int StaticOutBuffersInUse;                     // +0x3F060
    int StaticAltOutBuffersInUse;                  // +0x3F064
    bool WinsockInitialised;                       // +0x3F068
    unsigned char unknown_3F069[3];                // +0x3F069
    SOCKET Socket;                                 // +0x3F06C
    SOCKET unknown_3F070;                           // +0x3F070
    unsigned long ReceiveCrc;                      // +0x3F074
    unsigned char ReceiveBuffer[0x280 - 4];        // +0x3F078
    unsigned char unknown_3F2F4[4];                // +0x3F2F4
    int unknown_3F2F8;                             // +0x3F2F8
};

typedef WinsockInterfaceClass::WinsockBufferType WinsockBufferType;
typedef DynamicVectorClass<WinsockBufferType*> WinsockBufferVector;

GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, unknown_04) == 0x04);
GG_STATIC_ASSERT(sizeof(((WinsockInterfaceClass*)0)->unknown_04) == 0x04);
GG_STATIC_ASSERT(sizeof(WinsockBufferType) == 0x2A0);
GG_STATIC_ASSERT(offsetof(WinsockBufferType, unknown_1A) == 0x1A);
GG_STATIC_ASSERT(offsetof(WinsockBufferType, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(WinsockBufferType, IsBroadcast) == 0x14);
GG_STATIC_ASSERT(offsetof(WinsockBufferType, Address) == 0x00);
GG_STATIC_ASSERT(offsetof(WinsockBufferType, BufferLen) == 0x10);
GG_STATIC_ASSERT(offsetof(WinsockBufferType, InUse) == 0x15);
GG_STATIC_ASSERT(offsetof(WinsockBufferType, IsAllocated) == 0x16);
GG_STATIC_ASSERT(offsetof(WinsockBufferType, unknown_17) == 0x17);
GG_STATIC_ASSERT(offsetof(WinsockBufferType, Crc) == 0x1C);
GG_STATIC_ASSERT(offsetof(WinsockBufferType, Payload) == 0x20);
GG_STATIC_ASSERT(sizeof(WinsockBufferType*) == 4);
GG_STATIC_ASSERT(sizeof(WinsockBufferVector) == 0x18);
GG_STATIC_ASSERT(offsetof(WinsockBufferVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(WinsockBufferVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(WinsockBufferVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(WinsockBufferVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(WinsockBufferVector, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, InBuffers) == 0x08);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, OutBuffers) == 0x20);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, AltOutBuffers) == 0x38);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, StaticInBuffers) == 0x50);
GG_STATIC_ASSERT(sizeof(((WinsockInterfaceClass*)0)->StaticInBuffers) == 0x15000);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, StaticOutBuffers) == 0x15050);
GG_STATIC_ASSERT(sizeof(((WinsockInterfaceClass*)0)->StaticOutBuffers) == 0x15000);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, StaticAltOutBuffers) == 0x2A050);
GG_STATIC_ASSERT(sizeof(((WinsockInterfaceClass*)0)->StaticAltOutBuffers) == 0x15000);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, StaticInBufferPos) == 0x3F050);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, StaticOutBufferPos) == 0x3F054);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, StaticAltOutBufferPos) == 0x3F058);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, StaticInBuffersInUse) == 0x3F05C);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, StaticOutBuffersInUse) == 0x3F060);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, StaticAltOutBuffersInUse) == 0x3F064);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, Socket) == 0x3F06C);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, unknown_3F070) == 0x3F070);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, ReceiveBuffer) == 0x3F078);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, unknown_3F2F8) == 0x3F2F8);
GG_STATIC_ASSERT(sizeof(WinsockInterfaceClass) == 0x3F2FC);

#endif
