// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | RTTI
// IPXInterfaceClass RTTI type descriptor at 0x84D8F8 and class locator at
// 0x80EA60 identify a zero-offset WinsockInterfaceClass base. The retail
// address point 0x7F794C has 23 entries; four derived overrides are observed at
// slots 13 through 16. Allocation call sites in the retail image request
// 0x3F310 bytes before invoking the IPX constructor; that is an allocation
// extent observation, not evidence for constructor ownership in this file.
#ifndef GG_MATCH_NETWORK_TRANSPORT_IPX_INTERFACE_CLASS_H
#define GG_MATCH_NETWORK_TRANSPORT_IPX_INTERFACE_CLASS_H

#include <stddef.h>
#include "winsock_interface_class.h"
#include <wsipx.h>
#include "../../_rt/gg_static_assert.h"

// Stack address layout used by IPX Init/vf_16. Retail uses a 16-byte
// SOCKADDR length for bind and a 14-byte SOCKADDR_IPX length for data calls.
GG_STATIC_ASSERT(sizeof(SOCKADDR) == 0x10);
GG_STATIC_ASSERT(sizeof(SOCKADDR_IPX) == 0x0E);
GG_STATIC_ASSERT(offsetof(SOCKADDR_IPX, sa_family) == 0x00);
GG_STATIC_ASSERT(offsetof(SOCKADDR_IPX, sa_netnum) == 0x02);
GG_STATIC_ASSERT(offsetof(SOCKADDR_IPX, sa_nodenum) == 0x06);
GG_STATIC_ASSERT(offsetof(SOCKADDR_IPX, sa_socket) == 0x0C);

typedef WinsockInterfaceClass::WinsockBufferType WinsockBufferType;

// VTABLE: GAMEMD 0x7F794C -- retail address-point binding read from PE.
// Slot target order: 7B1790,7B1B80,7B22E0,7B23B0,7B24E0,7B1CA0,
// 7B1D10,7B1BC0,7B1C50,7B25E0,7B2630,7B1720,7B1730,7B1770,
// 7B1780,7B10C0,7B13D0,7B26D0,7B1740,7B1750,7B1760,7B1FD0,7B2050.
// This layout declaration alone does not prove compiler emission or final link.
struct IPXInterfaceClassVtableLayout
{
    void* slot_00; void* slot_01; void* slot_02; void* slot_03;
    void* slot_04; void* slot_05; void* slot_06; void* slot_07;
    void* slot_08; void* slot_09; void* slot_0A; void* slot_0B;
    void* slot_0C; void* slot_0D; void* slot_0E; void* slot_0F;
    void* slot_10; void* slot_11; void* slot_12; void* slot_13;
    void* slot_14; void* slot_15; void* slot_16;
};
#define GG_IPX_SLOT_ASSERT(n) \
    GG_STATIC_ASSERT(offsetof(IPXInterfaceClassVtableLayout, slot_##n) == 4 * 0x##n)
GG_IPX_SLOT_ASSERT(00); GG_IPX_SLOT_ASSERT(01); GG_IPX_SLOT_ASSERT(02);
GG_IPX_SLOT_ASSERT(03); GG_IPX_SLOT_ASSERT(04); GG_IPX_SLOT_ASSERT(05);
GG_IPX_SLOT_ASSERT(06); GG_IPX_SLOT_ASSERT(07); GG_IPX_SLOT_ASSERT(08);
GG_IPX_SLOT_ASSERT(09); GG_IPX_SLOT_ASSERT(0A); GG_IPX_SLOT_ASSERT(0B);
GG_IPX_SLOT_ASSERT(0C); GG_IPX_SLOT_ASSERT(0D); GG_IPX_SLOT_ASSERT(0E);
GG_IPX_SLOT_ASSERT(0F); GG_IPX_SLOT_ASSERT(10); GG_IPX_SLOT_ASSERT(11);
GG_IPX_SLOT_ASSERT(12); GG_IPX_SLOT_ASSERT(13); GG_IPX_SLOT_ASSERT(14);
GG_IPX_SLOT_ASSERT(15); GG_IPX_SLOT_ASSERT(16);
#undef GG_IPX_SLOT_ASSERT
GG_STATIC_ASSERT(sizeof(IPXInterfaceClassVtableLayout) == 0x5C);

class IPXInterfaceClass : public WinsockInterfaceClass
{
public:
    // Type declaration for slot 0; the existing 0x7B1790 deleting entry and
    // any ordinary destructor body remain outside this candidate.
    virtual ~IPXInterfaceClass();
    // FUNCTION: GAMEMD 0x7B1770 (decl; reloc) -- retail slot 13.
    virtual int Slot13();
    // FUNCTION: GAMEMD 0x7B1780 (decl; reloc) -- retail slot 14.
    virtual unsigned int MessageForSocket(int socket);
    // FUNCTION: GAMEMD 0x7B10C0 (decl; reloc) -- retail slot 15.
    virtual bool Init(int socketNumber);
    // FUNCTION: GAMEMD 0x7B13D0 (decl; reloc) -- retail slot 16.
    virtual int vf_16(HWND window, unsigned int message,
                               unsigned int wParam, long lParam);

    // FUNCTION: GAMEMD 0x7B0DD0 (decl; reloc) -- excluded capped query body.
    int FUN_007B0DD0(int protocol, SOCKADDR_IPX* address);
    // FUNCTION: GAMEMD 0x7B0F50 (decl; reloc)
    int GetAdapterAddressString(int adapter, char* buffer, int bufferLen);

    unsigned char LocalNetwork[4];       // +0x3F2FC, copied from IPX address
    unsigned char BroadcastNode[6];      // +0x3F300, all-FF broadcast node
    unsigned char LocalNode[6];          // +0x3F306, local node from address query
    unsigned long SocketNumber;          // +0x3F30C
};

GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, WinsockInitialised) == 0x3F068);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, Socket) == 0x3F06C);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, ReceiveCrc) == 0x3F074);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, ReceiveBuffer) == 0x3F078);
GG_STATIC_ASSERT(offsetof(WinsockInterfaceClass, unknown_3F2F8) == 0x3F2F8);
GG_STATIC_ASSERT(offsetof(IPXInterfaceClass, LocalNetwork) == 0x3F2FC);
GG_STATIC_ASSERT(offsetof(IPXInterfaceClass, BroadcastNode) == 0x3F300);
GG_STATIC_ASSERT(offsetof(IPXInterfaceClass, LocalNode) == 0x3F306);
GG_STATIC_ASSERT(offsetof(IPXInterfaceClass, SocketNumber) == 0x3F30C);
// The final observed field reaches the allocation request boundary. This
// pins the modeled prefix without claiming an independently proven full size.
GG_STATIC_ASSERT(offsetof(IPXInterfaceClass, SocketNumber) + sizeof(unsigned long) == 0x3F310);

#endif
