// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: retail gamemd.exe v1.001 RTTI and entry-origin member accesses;
// shared Winsock/connection declarations are existing repository ABI views.
#ifndef GG_MATCH_NETWORK_TRANSPORT_UDP_INTERFACE_CLASS_H
#define GG_MATCH_NETWORK_TRANSPORT_UDP_INTERFACE_CLASS_H

#include <stddef.h>
#include "winsock_interface_class.h"
#include "../../_layout/ipx_address_class.h"
#include "../../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x00841F30 -- 32-bit default port value read by UDP methods.
extern int DAT_00841F30;
// GLOBAL: GAMEMD 0x00841F38 -- 16-bit alternate/listen port read by Init.
extern unsigned short DAT_00841F38;

typedef DynamicVectorClass<unsigned char*> UDPAddressVector;

// VTABLE: GAMEMD 0x7F7A6C -- retail binding; this declaration does not
// establish emitted-table or final-link selection.
class UDPInterfaceClass : public WinsockInterfaceClass
{
public:
    virtual void SendPacket(void*, int, void*, int, bool, unsigned char, unsigned short);
    virtual void Broadcast(void*, int, bool);
    virtual bool StartListening();
    virtual void StopListening();
    virtual void AddBroadcastAddress(const char*, unsigned short);
    virtual void ClearBroadcastAddresses();
    virtual int Slot13();
    virtual unsigned int MessageForSocket(int);
    virtual bool Init(int);
    // FUNCTION: GAMEMD 0x7B3AA0 (decl; reloc) -- capped body outside this batch.
    virtual int MessageHandler(HWND, unsigned int, unsigned int, long);
    virtual int GetNumLocalAddresses();
    virtual unsigned char* GetLocalAddress(int);
    virtual bool OpenPrimarySocket(unsigned short);
    virtual unsigned short GetPrimaryPort();
    virtual bool StartupWinsockInit();
    virtual bool OpenSpareSocket(unsigned short);
    virtual void CloseSpareSocket(unsigned short);
    virtual void CloseAllSpareSockets();
    virtual void SelectSpareSocket(unsigned short);
    virtual void MarkAddressUnreachable(unsigned char*, unsigned short);

    unsigned short PrimaryPort;                     // +0x3F2FC
    unsigned char unknown_3F2FE[2];                 // +0x3F2FE
    SOCKET SpareSockets[8];                          // +0x3F300, storage view; count bound unproven here
    unsigned short SparePorts[8];                    // +0x3F320, storage view; count bound unproven here
    int SpareSocketCount;                            // +0x3F330
    SOCKET CurrentSpareSocket;                       // +0x3F334
    UDPAddressVector BroadcastAddresses;             // +0x3F338
    unsigned short BroadcastPorts[0x100];            // +0x3F350, modeled 0x200-byte storage region
    UDPAddressVector LocalAddresses;                  // +0x3F550
    int UnreachableCount;                            // +0x3F568
    unsigned long UnreachableAddresses[16];          // +0x3F56C (loop bound is 16)
    unsigned short UnreachablePorts[16];             // +0x3F5AC (loop bound is 16)
};

GG_STATIC_ASSERT(sizeof(UDPAddressVector) == 0x18);
GG_STATIC_ASSERT(sizeof(unsigned short) == 0x02);
GG_STATIC_ASSERT(offsetof(UDPAddressVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(UDPAddressVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(UDPAddressVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(UDPAddressVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(UDPAddressVector, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClass, PrimaryPort) == sizeof(WinsockInterfaceClass));
GG_STATIC_ASSERT(offsetof(UDPInterfaceClass, PrimaryPort) == 0x3F2FC);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClass, unknown_3F2FE) == 0x3F2FE);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClass, PrimaryPort) + sizeof(((UDPInterfaceClass*)0)->PrimaryPort) +
                 sizeof(((UDPInterfaceClass*)0)->unknown_3F2FE) == offsetof(UDPInterfaceClass, SpareSockets));
GG_STATIC_ASSERT(offsetof(UDPInterfaceClass, SpareSockets) == 0x3F300);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClass, SparePorts) == 0x3F320);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClass, SpareSockets) + sizeof(((UDPInterfaceClass*)0)->SpareSockets) ==
                 offsetof(UDPInterfaceClass, SparePorts));
GG_STATIC_ASSERT(offsetof(UDPInterfaceClass, SparePorts) + sizeof(((UDPInterfaceClass*)0)->SparePorts) ==
                 offsetof(UDPInterfaceClass, SpareSocketCount));
GG_STATIC_ASSERT(offsetof(UDPInterfaceClass, SpareSocketCount) == 0x3F330);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClass, CurrentSpareSocket) == 0x3F334);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClass, BroadcastAddresses) == 0x3F338);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClass, BroadcastPorts) == 0x3F350);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClass, LocalAddresses) == 0x3F550);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClass, BroadcastAddresses) + sizeof(((UDPInterfaceClass*)0)->BroadcastAddresses) ==
                 offsetof(UDPInterfaceClass, BroadcastPorts));
GG_STATIC_ASSERT(offsetof(UDPInterfaceClass, BroadcastPorts) + sizeof(((UDPInterfaceClass*)0)->BroadcastPorts) ==
                 offsetof(UDPInterfaceClass, LocalAddresses));
GG_STATIC_ASSERT(offsetof(UDPInterfaceClass, LocalAddresses) + sizeof(((UDPInterfaceClass*)0)->LocalAddresses) ==
                 offsetof(UDPInterfaceClass, UnreachableCount));
GG_STATIC_ASSERT(offsetof(UDPInterfaceClass, UnreachableCount) == 0x3F568);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClass, UnreachableAddresses) == 0x3F56C);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClass, UnreachablePorts) == 0x3F5AC);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClass, UnreachableAddresses) + sizeof(((UDPInterfaceClass*)0)->UnreachableAddresses) ==
                 offsetof(UDPInterfaceClass, UnreachablePorts));

// Windows ABI storage used by the stack-local network records in these methods.
GG_STATIC_ASSERT(sizeof(SOCKET) == 0x04);
GG_STATIC_ASSERT(sizeof(SOCKADDR_IN) == 0x10);
GG_STATIC_ASSERT(offsetof(SOCKADDR_IN, sin_family) == 0x00);
GG_STATIC_ASSERT(offsetof(SOCKADDR_IN, sin_port) == 0x02);
GG_STATIC_ASSERT(offsetof(SOCKADDR_IN, sin_addr) == 0x04);
GG_STATIC_ASSERT(sizeof(IN_ADDR) == 0x04);
GG_STATIC_ASSERT(offsetof(IN_ADDR, S_un) == 0x00);
GG_STATIC_ASSERT(offsetof(SOCKADDR_IN, sin_addr) + offsetof(IN_ADDR, S_un) == 0x04);
GG_STATIC_ASSERT(offsetof(HOSTENT, h_addr_list) == 0x0C);
GG_STATIC_ASSERT(offsetof(LINGER, l_onoff) == 0x00);
GG_STATIC_ASSERT(offsetof(LINGER, l_linger) == 0x02);
GG_STATIC_ASSERT(sizeof(LINGER) == 0x04);

// The allocation request at 0x52F443 is 0x3F5CC bytes; this view reaches
// that boundary, but does not prove a complete original class sizeof.
GG_STATIC_ASSERT(offsetof(UDPInterfaceClass, UnreachablePorts) +
                 sizeof(((UDPInterfaceClass*)0)->UnreachablePorts) == 0x3F5CC);

// Slot positions are pinned separately from the retail target bindings.
struct UDPInterfaceClassVtableLayout
{
    void* slot_00; // retail 0x007B4170
    void* slot_01; // retail 0x007B1B80
    void* slot_02; // retail 0x007B22E0
    void* slot_03; // retail 0x007B36C0
    void* slot_04; // retail 0x007B3720
    void* slot_05; // retail 0x007B1CA0
    void* slot_06; // retail 0x007B1D10
    void* slot_07; // retail 0x007B3890
    void* slot_08; // retail 0x007B3900
    void* slot_09; // retail 0x007B25E0
    void* slot_0A; // retail 0x007B2630
    void* slot_0B; // retail 0x007B2FF0
    void* slot_0C; // retail 0x007B2F90
    void* slot_0D; // retail 0x007B40F0
    void* slot_0E; // retail 0x007B4100
    void* slot_0F; // retail 0x007B3450
    void* slot_10; // retail 0x007B3AA0
    void* slot_11; // retail 0x007B26D0
    void* slot_12; // retail 0x007B4140
    void* slot_13; // retail 0x007B4150
    void* slot_14; // retail 0x007B1760
    void* slot_15; // retail 0x007B1FD0
    void* slot_16; // retail 0x007B2050
    void* slot_17; // retail 0x007B30B0
    void* slot_18; // retail 0x007B4160
    void* slot_19; // retail 0x007B3430
    void* slot_1A; // retail 0x007B31E0
    void* slot_1B; // retail 0x007B3310
    void* slot_1C; // retail 0x007B3A20
    void* slot_1D; // retail 0x007B33D0
    void* slot_1E; // retail 0x007B3920
};
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_00) == 0x00);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_01) == 0x04);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_02) == 0x08);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_03) == 0x0C);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_04) == 0x10);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_05) == 0x14);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_06) == 0x18);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_07) == 0x1C);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_08) == 0x20);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_09) == 0x24);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_0A) == 0x28);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_0B) == 0x2C);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_0C) == 0x30);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_0D) == 0x34);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_0E) == 0x38);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_0F) == 0x3C);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_10) == 0x40);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_11) == 0x44);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_12) == 0x48);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_13) == 0x4C);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_14) == 0x50);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_15) == 0x54);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_16) == 0x58);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_17) == 0x5C);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_18) == 0x60);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_19) == 0x64);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_1A) == 0x68);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_1B) == 0x6C);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_1C) == 0x70);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_1D) == 0x74);
GG_STATIC_ASSERT(offsetof(UDPInterfaceClassVtableLayout, slot_1E) == 0x78);
GG_STATIC_ASSERT(sizeof(UDPInterfaceClassVtableLayout) == 0x7C);

#endif
