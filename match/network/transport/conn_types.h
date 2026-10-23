// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layouts, slots and globals read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI: ConnectionClass RTTI
//   .?AVConnectionClass@@ (type descriptor 0x81D2A0, vtable 0x7E51B4),
//   IPXConnClass (0x828190, vtable 0x7EC0CC), IPXGlobalConnClass (vtable
//   0x7EC10C), and every member offset touched by the 30 functions in
//   conn_connection.cpp / conn_ipx.cpp / conn_ipx_global.cpp. Receive_Packet
//   and Service_Send_Queue are named by the binary's own debug strings, as are
//   MaxPacketLen, NumSendAck and RetryDelta; unattested virtuals are vf_<slot>
//   and every other unproven member stays unknown_XX / FUN_XXXXXXXX.
//
// Shared declarations for the connection hierarchy (conn_*): ConnectionClass,
// IPXConnClass, IPXGlobalConnClass plus minimal models of the callee classes
// they reach. IPXAddressClass comes from the shared layout header above; the
// remaining callee classes belong to other owners and are declared only.
#ifndef GG_MATCH_NETWORK_TRANSPORT_CONN_TYPES_H
#define GG_MATCH_NETWORK_TRANSPORT_CONN_TYPES_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "../../_layout/ipx_address_class.h"

// Release-build debug printf: 0x4068E0 is a bare RET stub, cdecl/variadic.
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc)
extern "C" int __cdecl FUN_004068E0(const char* fmt, ...);

// ---------------------------------------------------------------------------
// Callee models (other owners; declared only).
// ---------------------------------------------------------------------------

// One entry of the send ring held by CommBufferClass (stride 0x24 in retail).
// Only members read by this hierarchy are named.
struct CommSendEntry
{
    unsigned int Flags;          // +0x00 bit1 = done, bit2 = overdue
    unsigned int unknown_04;     // +0x04 first-send tick
    unsigned int unknown_08;     // +0x08 last-send tick
    unsigned int unknown_0C;     // +0x0C send count
    int          unknown_10;     // +0x10 length of unknown_14
    char*        unknown_14;     // +0x14 header-prefixed packet bytes
    int          unknown_18;     // +0x18 length of unknown_1C
    void*        unknown_1C;     // +0x1C extra (address) bytes
    unsigned short unknown_20;   // +0x20
};
GG_STATIC_ASSERT(offsetof(CommSendEntry, Flags) == 0x00);
GG_STATIC_ASSERT(sizeof(CommSendEntry) == 0x24);
GG_STATIC_ASSERT(offsetof(CommSendEntry, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(CommSendEntry, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(CommSendEntry, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(CommSendEntry, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(CommSendEntry, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(CommSendEntry, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(CommSendEntry, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(CommSendEntry, unknown_20) == 0x20);

// One entry of the receive ring (stride 0x18 in retail).
struct CommReceiveEntry
{
    unsigned int Flags;          // +0x00 bit1 = consumed
    unsigned int unknown_04;     // +0x04
    int          unknown_08;     // +0x08 received length (header included)
    char*        unknown_0C;     // +0x0C received bytes (header-prefixed)
    int          unknown_10;     // +0x10
    void*        unknown_14;     // +0x14 sender address (12 bytes)
};
GG_STATIC_ASSERT(offsetof(CommReceiveEntry, Flags) == 0x00);
GG_STATIC_ASSERT(offsetof(CommReceiveEntry, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(CommReceiveEntry, unknown_10) == 0x10);
GG_STATIC_ASSERT(sizeof(CommReceiveEntry) == 0x18);
GG_STATIC_ASSERT(offsetof(CommReceiveEntry, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(CommReceiveEntry, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(CommReceiveEntry, unknown_14) == 0x14);

// The paired send/receive packet queue hanging off ConnectionClass+0x4.
// Model only: members read directly by the hierarchy are placed; the real
// allocation is 0x58 bytes (push 0x58 before operator new at 0x48BE97).
class CommBufferClass
{
public:
    // VTABLE: GAMEMD 0x7E519C (decl; retail address point, slot 0 = 0x48BB00)
    // FUNCTION: GAMEMD 0x48B1F0 (decl; reloc) -- ordinary destructor.
    // SYNTHETIC: GAMEMD 0x48BB00 (decl; reloc) -- slot-0 deleting wrapper.
    virtual ~CommBufferClass();                     // +0x00 (slot 0)

    int          unknown_04;                        // +0x04 compared with unknown_28 by IPXManagerClass::vf_2
    int          unknown_08;                        // +0x08
    char         _pad0C[0x28 - 0x0C];
    int          unknown_28;                         // +0x28
    int          unknown_2C;                        // +0x2C
    char         _pad30[0x38 - 0x30];
    int          unknown_38;                      // +0x38
    unsigned int unknown_3C;                        // +0x3C
    char         _pad40[0x58 - 0x40];

    // FUNCTION: GAMEMD 0x48B0E0 (decl; reloc)
    CommBufferClass(int sendSlots, int receiveSlots, int maxlen, int extraLength);

    // FUNCTION: GAMEMD 0x48B2A0 (decl; reloc)
    void Init();
    // FUNCTION: GAMEMD 0x48B410 (decl; reloc)
    int FUN_0048B410(void* a1, int a2, void* a3, int a4, unsigned short a5);   // a5 stored as a word (0x48B410)
    // FUNCTION: GAMEMD 0x48B570 (decl; reloc)
    int FUN_0048B570(void* a1, void* a2, int a3, void* a4, void* a5, int a6);
    // FUNCTION: GAMEMD 0x48B720 (decl; reloc)
    CommSendEntry* FUN_0048B720(int index);
    // FUNCTION: GAMEMD 0x48B750 (decl; reloc)
    int FUN_0048B750(void* a1, int a2, void* a3, int a4);
    // FUNCTION: GAMEMD 0x48B890 (decl; reloc)
    int FUN_0048B890(int a1, int a2, int a3, int a4, int a5);
    // FUNCTION: GAMEMD 0x48B9E0 (decl; reloc)
    CommReceiveEntry* FUN_0048B9E0(int index);
    // FUNCTION: GAMEMD 0x48BA10 (decl; reloc)
    void FUN_0048BA10(int a1);
    // FUNCTION: GAMEMD 0x48BA80 (decl; reloc)
    unsigned long FUN_0048BA80();
    // FUNCTION: GAMEMD 0x48BA90 (decl; reloc)
    int FUN_0048BA90();
    // FUNCTION: GAMEMD 0x48BAA0 (decl; reloc)
    void FUN_0048BAA0(bool a1);
    // FUNCTION: GAMEMD 0x48BAD0 (decl; reloc)
    void FUN_0048BAD0(int a1, int a2, int a3, int a4, int a5);
};

// The timer pair behind the global at 0x887338 (StartTime / clock object /
// TimeLeft). Same shape as the message-list timer in other modules.
struct ConnClockClass
{
    // FUNCTION: GAMEMD 0x6C8C40 (decl; reloc)
    int GetTime();
};
struct ConnTimerStruct
{
    int            StartTime;   // +0x0
    ConnClockClass Clock;       // +0x4
    int            TimeLeft;    // +0x8

    int GetValue()
    {
        int value = TimeLeft;
        if (StartTime != -1) {
            value += Clock.GetTime() - StartTime;
        }
        return value;
    }
};
GG_STATIC_ASSERT(offsetof(ConnTimerStruct, StartTime) == 0);
GG_STATIC_ASSERT(sizeof(ConnTimerStruct) == 0xC);
GG_STATIC_ASSERT(offsetof(ConnTimerStruct, Clock) == 0x4);
GG_STATIC_ASSERT(offsetof(ConnTimerStruct, TimeLeft) == 0x8);

// GLOBAL: GAMEMD 0x887338 -- the elapsed-time timer read by the queue services.
extern ConnTimerStruct ConnTimer;

// GLOBAL: GAMEMD 0xA8B238 -- the session object, shared by the conn and connman
// hierarchies; its first member is the game mode (4 selects the network-game
// address handling), and 0x69BC20 / 0x697E70 / 0x69BC60 are called on the
// object itself.
#include "../../_layout/session_class.h"
// GLOBAL: GAMEMD 0xA8DBA0 -- byte flag gating the address-stamping paths.
extern bool Flag_00A8DBA0;
// GLOBAL: GAMEMD 0xA8EA0C -- the global (broadcast) connection object.
class ConnectionClass;
extern ConnectionClass* GlobalConnection_00A8EA0C;

// Packet header: 0xE bytes (offsets +0x0 magic, +0x2 code, +0x3 byte, +0x4 id,
// +0x8 dword, +0xC word); data follows at +0xE, so the struct is packed.
#pragma pack(push, 1)
struct ConnPacketHeader
{
    unsigned short unknown_00;   // +0x00
    unsigned char  Code;          // +0x02 0 = data (ack), 1 = data (no ack), 2 = ack
    unsigned char  unknown_03;    // +0x03
    unsigned long  unknown_04;      // +0x04
    unsigned long  unknown_08;    // +0x08
    unsigned short unknown_0C;    // +0x0C
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(ConnPacketHeader, unknown_00) == 0);
GG_STATIC_ASSERT(sizeof(ConnPacketHeader) == 0xE);
GG_STATIC_ASSERT(offsetof(ConnPacketHeader, Code) == 0x2);
GG_STATIC_ASSERT(offsetof(ConnPacketHeader, unknown_03) == 0x3);
GG_STATIC_ASSERT(offsetof(ConnPacketHeader, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(ConnPacketHeader, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(ConnPacketHeader, unknown_0C) == 0xC);

// Global-connection packet header: the 0xE-byte header plus a word at +0xE.
#pragma pack(push, 1)
struct ConnGlobalPacketHeader
{
    unsigned short unknown_00;   // +0x00
    unsigned char  Code;          // +0x02
    unsigned char  unknown_03;    // +0x03
    unsigned long  unknown_04;      // +0x04
    unsigned long  unknown_08;    // +0x08
    unsigned short unknown_0C;    // +0x0C
    unsigned short unknown_0E;    // +0x0E
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(ConnGlobalPacketHeader, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(ConnGlobalPacketHeader, Code) == 0x2);
GG_STATIC_ASSERT(offsetof(ConnGlobalPacketHeader, unknown_03) == 0x3);
GG_STATIC_ASSERT(offsetof(ConnGlobalPacketHeader, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(ConnGlobalPacketHeader, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(ConnGlobalPacketHeader, unknown_0C) == 0xC);
GG_STATIC_ASSERT(sizeof(ConnGlobalPacketHeader) == 0x10);
GG_STATIC_ASSERT(offsetof(ConnGlobalPacketHeader, unknown_0E) == 0xE);

// ---------------------------------------------------------------------------
// ConnectionClass (RTTI .?AVConnectionClass@@, vtable 0x7E51B4, 10 slots).
// Packet header (0xE bytes, ConnPacketHeader): word magic +0x0, byte
// code +0x2 (0 data-needs-ack, 1 data-no-ack, 2 ack), byte +0x3, dword id +0x4.
// The constructor at 0x48BE60 and ordinary destructor at 0x48BEE0 are
// separately verified expansion rows. One ordinary destructor definition is
// shared; /Ob2 in the base TU also inlines its cleanup into 0x48C650.
// ---------------------------------------------------------------------------
class ConnectionClass
{
public:
    // FUNCTION: GAMEMD 0x48BE60 (decl; reloc)
    ConnectionClass(int sendSlots, int receiveSlots, int maxlen,
                    unsigned short magic, int retryDelay, int retryLimit,
                    int timeout, int extraLength);
    // FUNCTION: GAMEMD 0x48BEE0 (decl; reloc) -- ordinary destructor.
    virtual ~ConnectionClass();                                // slot 0  0x48C650
    virtual void Init();                                       // slot 1  0x48BF10
    virtual int vf_2(void* buf, int buflen, int needsAck,
                            unsigned char extra);              // slot 2  0x48BF40
    virtual int Receive_Packet(ConnPacketHeader* packet, int buflen); // slot 3  0x48C040
    virtual int vf_4(void* buf, int* buflen);            // slot 4  0x48C320
    virtual int Service();                                     // slot 5  0x48C3B0
    virtual int vf_6();                       // slot 6  0x48C590
    virtual int Service_Send_Queue();                          // slot 7  0x48C3E0
    virtual int vf_8();                       // slot 8  0x48C5A0
    virtual int vf_9(void* buf, int buflen, void* extra, int extraLength,
                        bool is_global, unsigned short unknown_6) = 0; // slot 9

    CommBufferClass* Queue;                // +0x04
    int              unknown_08;           // +0x08
    int              unknown_0C;           // +0x0C
    int              unknown_10;           // +0x10
    int              unknown_14;           // +0x14
    int              unknown_18;           // +0x18
    int              MaxPacketLen;         // +0x1C
    ConnPacketHeader*  unknown_20;            // +0x20
    unsigned short   unknown_24;          // +0x24
    unsigned short   unknown_26;           // +0x26 (padding)
    unsigned int     RetryDelta;           // +0x28
    unsigned int     MaxRetries;           // +0x2C
    unsigned int     Timeout;              // +0x30
    int              unknown_34;           // +0x34
    int              unknown_38;           // +0x38
    int              unknown_3C;           // +0x3C
    int              NumSendAck;           // +0x40
    unsigned int     unknown_44;           // +0x44
    unsigned int     unknown_48;           // +0x48
};

// Member offsets are pinned by the constructor and methods listed above;
// the 0x4C extent is corroborated by IPXConnClass's first derived field at +0x4C.
GG_STATIC_ASSERT(offsetof(ConnectionClass, Queue) == 0x04);
GG_STATIC_ASSERT(offsetof(ConnectionClass, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(ConnectionClass, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(ConnectionClass, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(ConnectionClass, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(ConnectionClass, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(ConnectionClass, MaxPacketLen) == 0x1C);
GG_STATIC_ASSERT(offsetof(ConnectionClass, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(ConnectionClass, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(ConnectionClass, RetryDelta) == 0x28);
GG_STATIC_ASSERT(offsetof(ConnectionClass, MaxRetries) == 0x2C);
GG_STATIC_ASSERT(offsetof(ConnectionClass, Timeout) == 0x30);
GG_STATIC_ASSERT(offsetof(ConnectionClass, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(ConnectionClass, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(ConnectionClass, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(ConnectionClass, NumSendAck) == 0x40);
GG_STATIC_ASSERT(offsetof(ConnectionClass, unknown_44) == 0x44);
GG_STATIC_ASSERT(offsetof(ConnectionClass, unknown_48) == 0x48);
GG_STATIC_ASSERT(sizeof(ConnectionClass) == 0x4C);

GG_STATIC_ASSERT(sizeof(CommBufferClass) == 0x58);
GG_STATIC_ASSERT(offsetof(CommBufferClass, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(CommBufferClass, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(CommBufferClass, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(CommBufferClass, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(CommBufferClass, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(CommBufferClass, unknown_3C) == 0x3C);

// 0x53F830 (defined in conn_ipx.cpp)
int FUN_0053F830(void* buf, int buflen);

// LIBRARY: GAMEMD 0x7CA489 (CRT wcscpy, cdecl)
extern "C" wchar_t* __cdecl wcscpy(wchar_t* dst, const wchar_t* src);

// ---------------------------------------------------------------------------
// IPXConnClass (RTTI .?AVIPXConnClass@@, type descriptor 0x828190, vtable
// 0x7EC0CC, 11 slots). sizeof 0xB8 is pinned by the allocation at 0x540DDC
// (PUSH 0xB8; operator new 0x7C8E17; constructor 0x53F430 called directly).
// ---------------------------------------------------------------------------
class IPXConnClass : public ConnectionClass
{
public:
    IPXConnClass(int sendSlots, int receiveSlots, int maxlen, unsigned short magic,
                 IPXAddressClass* address, int id, wchar_t* name,
                 int extraLength);                                // 0x53F430
    virtual ~IPXConnClass() {}                                 // slot 0  0x53F850
    virtual void Init();                                       // slot 1  0x53F4E0
    virtual int vf_9(void* buf, int buflen, void* extra, int extraLength,
                        bool is_global, unsigned short unknown_6); // slot 9  0x53F5D0
    virtual int vf_10(void* buf, int buflen, IPXAddressClass* address,
                                unsigned long* network, bool is_global,
                                unsigned short unknown_6);     // slot 10 0x53F650

    IPXAddressClass Address;            // +0x4C
    NodeAddressType unknown_58;         // +0x58
    unsigned char   _pad5E[2];          // +0x5E
    int             unknown_60;         // +0x60
    int             ID;                 // +0x64
    wchar_t         Name[40];           // +0x68 (wcscpy target; length modeled)
};
GG_STATIC_ASSERT(offsetof(IPXConnClass, Address) == 0x4C);
GG_STATIC_ASSERT(offsetof(IPXConnClass, unknown_58) == 0x58);
GG_STATIC_ASSERT(offsetof(IPXConnClass, unknown_60) == 0x60);
GG_STATIC_ASSERT(offsetof(IPXConnClass, ID) == 0x64);
GG_STATIC_ASSERT(offsetof(IPXConnClass, Name) == 0x68);
GG_STATIC_ASSERT(sizeof(IPXConnClass) == 0xB8);

// ---------------------------------------------------------------------------
// Globals and callee objects reached by IPXConnClass / IPXGlobalConnClass.
// ---------------------------------------------------------------------------
// A player record: the IPXAddressClass sits at +0x28.
#pragma pack(push, 1)
struct NetPlayerClass
{
    unsigned short  Name[0x14];         // +0x00 name-input view; capacity modeled
    IPXAddressClass Address;            // +0x28
    char            unknown_34[0x4B - 0x34];
    int             unknown_4B;
    int             unknown_4F; // 0x69B8F5/0x69B90D
    int             unknown_53; // 0x69B946/0x69B96F
    int             unknown_57; // 0x69B93D/0x69B943
    char            unknown_5B[0x6B - 0x5B];
    int             unknown_6B;         // +0x6B (unaligned; siege team 1/2, stamped by 0x5CA680)
    int             Id;                 // +0x6F (unaligned; indexes the player tables)
    int             unknown_73; // native697D2D store
    char            unknown_77[4];
    int             unknown_7B; // native697C73/697CB9 loads
    // FUNCTION: GAMEMD 0x7350C0 (decl; reloc), ECX player at 0x684565.
    const char* FUN_007350C0();
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(NetPlayerClass, Name) == 0x00);
GG_STATIC_ASSERT(offsetof(NetPlayerClass, Address) == 0x28);
GG_STATIC_ASSERT(offsetof(NetPlayerClass, unknown_4B) == 0x4B);
GG_STATIC_ASSERT(offsetof(NetPlayerClass, unknown_4F) == 0x4F);
GG_STATIC_ASSERT(offsetof(NetPlayerClass, unknown_53) == 0x53);
GG_STATIC_ASSERT(offsetof(NetPlayerClass, unknown_57) == 0x57);
GG_STATIC_ASSERT(offsetof(NetPlayerClass, unknown_6B) == 0x6B);
GG_STATIC_ASSERT(offsetof(NetPlayerClass, Id) == 0x6F);
GG_STATIC_ASSERT(offsetof(NetPlayerClass, unknown_73) == 0x73);
GG_STATIC_ASSERT(offsetof(NetPlayerClass, unknown_7B) == 0x7B);

// GLOBAL: GAMEMD 0x887628 -- the packet interface (WinsockInterfaceClass, owned by
// the winsock hierarchy; include winsock_interface_class.h to call through it).
class WinsockInterfaceClass;
extern WinsockInterfaceClass* Interface_00887628;

// The player/connection id registry at 0xB052D0 (shared by conn and connman);
// 0x663D60 maps a connection id to a byte.
struct NetIdMapRef
{
    // FUNCTION: GAMEMD 0x664610 (decl; 0x684B0A)
    void FUN_00664610(int timeout, int flag);
    // Declaration: GAMEMD 0x663B40 -- ECX receiver, no arguments, RET.
    void FUN_00663B40();
    // Declaration: GAMEMD 0x663DB0 -- pointer stack argument, boolAL, RET4.
    bool FUN_00663DB0(const unsigned char* address);
    // Declaration: GAMEMD 0x6639D0 -- result0/1, caller697E2A testsAL, RET.
    bool FUN_006639D0();
    // FUNCTION: GAMEMD 0x663D60 (decl; reloc)
    unsigned char FUN_00663D60(int id);
    // FUNCTION: GAMEMD 0x6640E0 (decl; reloc)
    void FUN_006640E0();
    // FUNCTION: GAMEMD 0x664240 (decl; reloc)
    void FUN_00664240(int id, IPXAddressClass* addr);
    // FUNCTION: GAMEMD 0x664400 (decl; reloc)
    void FUN_00664400(int id, int port);
};
// GLOBAL: GAMEMD 0xB052D0
extern NetIdMapRef IdMap_00B052D0;

// GLOBAL: GAMEMD 0xA8DBA4 -- 12-byte address, stamped into outgoing packets.
extern IPXAddressClass Address_00A8DBA4;
// GLOBAL: GAMEMD 0xA8DBB0 -- 12-byte address compared against player 0.
extern IPXAddressClass Address_00A8DBB0;
// GLOBAL: GAMEMD 0x841F3C -- dword whose low word is a port.
extern int Port_00841F3C;
// GLOBAL: GAMEMD 0xA8DBBC -- dword whose low word is a port.
extern int Port_00A8DBBC;
// GLOBAL: GAMEMD 0xA8DA78 -- player pointer array data.
extern NetPlayerClass** Players_00A8DA78;
// GLOBAL: GAMEMD 0xA8DA84 -- player count.
extern int PlayerCount_00A8DA84;

// ---------------------------------------------------------------------------
// IPXGlobalConnClass (RTTI via vtable 0x7EC10C, 18 slots). sizeof 0xDC is
// pinned by the allocations at 0x540B2B / 0x540B7A (PUSH 0xDC; operator new;
// constructor 0x53FA90 called directly).
// ---------------------------------------------------------------------------
// Packed: the dwords at +0xBA / +0xBE are not 4-byte aligned.
#pragma pack(push, 1)
class IPXGlobalConnClass : public IPXConnClass
{
public:
    IPXGlobalConnClass(int sendSlots, int receiveSlots, int maxlen,
                       unsigned short unknown_b8, unsigned short magic); // 0x53FA90
    virtual ~IPXGlobalConnClass();                                 // slot 0  0x540670
    virtual int vf_2(void* buf, int buflen, int needsAck,
                            unsigned char extra);                  // slot 2  0x540610
    virtual int Receive_Packet(ConnPacketHeader* packet, int buflen); // slot 3  0x540630
    virtual int vf_4(void* buf, int* buflen);                // slot 4  0x540650
    virtual int vf_6();                           // slot 6  0x5402D0
    virtual int vf_8();                           // slot 8  0x5400D0
    virtual int vf_9(void* buf, int buflen, void* extra, int extraLength,
                        bool is_global, unsigned short unknown_6); // slot 9  0x540050
    virtual int vf_10(void* buf, int buflen, IPXAddressClass* address,
                                unsigned long* network, bool is_global,
                                unsigned short unknown_6);         // slot 10 0x5403F0
    virtual int vf_11(void* buf, int buflen, IPXAddressClass* address,
                               int needsAck, unsigned short unknown_5, int packet_id); // slot 11 0x53FBD0
    virtual int vf_12(ConnPacketHeader* packet, int buflen,
                                    IPXAddressClass* address,
                                    unsigned short port);          // slot 12 0x53FCB0
    virtual int vf_13(void* buf, int* buflen, IPXAddressClass* address,
                                unsigned short* port);             // slot 13 0x53FF10
    virtual int vf_14(int index, void* buf, int* buflen,
                              IPXAddressClass* address, unsigned short* port,
                              unsigned long* packet_id);           // slot 14 0x53FFA0
    virtual void vf_15(int index);                         // slot 15 0x540030
    virtual int vf_16(IPXAddressClass* address,
                                    unsigned short port);          // slot 16 0x540340
    virtual void vf_17(unsigned int age);              // slot 17 0x540110
    // 0x5402B0: clears unknown_C4 while the global flag
    // 0xAA05A4 is set; the argument is popped (RET 4) but not read.
    void FUN_005402B0(int unused);

    ConnGlobalPacketHeader* GlobalHeader() { return (ConnGlobalPacketHeader*)unknown_20; }

    unsigned short  unknown_B8;         // +0xB8
    unsigned long   unknown_BA;         // +0xBA
    unsigned long   unknown_BE;         // +0xBE
    unsigned short  _padC2;             // +0xC2
    int             unknown_C4;         // +0xC4
    bool            unknown_C8;         // +0xC8
    char            _padC9[3];          // +0xC9
    IPXAddressClass* Addresses;         // +0xCC
    int*            Ids;                // +0xD0
    int             unknown_D4;         // +0xD4
    int             unknown_D8;         // +0xD8
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClass, unknown_B8) == 0xB8);
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClass, unknown_BA) == 0xBA);
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClass, unknown_BE) == 0xBE);
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClass, unknown_C4) == 0xC4);
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClass, unknown_C8) == 0xC8);
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClass, Addresses) == 0xCC);
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClass, Ids) == 0xD0);
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClass, unknown_D4) == 0xD4);
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClass, unknown_D8) == 0xD8);
GG_STATIC_ASSERT(sizeof(IPXGlobalConnClass) == 0xDC);

// GLOBAL: GAMEMD 0x887734 -- empty wide string passed as the name.
extern wchar_t EmptyName_00887734[];


// Retail slot offsets for the recorded address points. These storage views
// assert slot positions; compiler-emitted tables are checked separately.
struct CommBufferClassVtablePrefix
{
    void* deletingDestructor;
};
GG_STATIC_ASSERT(offsetof(CommBufferClassVtablePrefix, deletingDestructor) == 0);
GG_STATIC_ASSERT(sizeof(CommBufferClassVtablePrefix) == 4);

struct ConnectionClassVtableLayout
{
    void* slot_00;
    void* slot_01;
    void* slot_02;
    void* slot_03;
    void* slot_04;
    void* slot_05;
    void* slot_06;
    void* slot_07;
    void* slot_08;
    void* slot_09;
};
GG_STATIC_ASSERT(offsetof(ConnectionClassVtableLayout, slot_00) == 0x00);
GG_STATIC_ASSERT(offsetof(ConnectionClassVtableLayout, slot_01) == 0x04);
GG_STATIC_ASSERT(offsetof(ConnectionClassVtableLayout, slot_02) == 0x08);
GG_STATIC_ASSERT(offsetof(ConnectionClassVtableLayout, slot_03) == 0x0C);
GG_STATIC_ASSERT(offsetof(ConnectionClassVtableLayout, slot_04) == 0x10);
GG_STATIC_ASSERT(offsetof(ConnectionClassVtableLayout, slot_05) == 0x14);
GG_STATIC_ASSERT(offsetof(ConnectionClassVtableLayout, slot_06) == 0x18);
GG_STATIC_ASSERT(offsetof(ConnectionClassVtableLayout, slot_07) == 0x1C);
GG_STATIC_ASSERT(offsetof(ConnectionClassVtableLayout, slot_08) == 0x20);
GG_STATIC_ASSERT(offsetof(ConnectionClassVtableLayout, slot_09) == 0x24);
GG_STATIC_ASSERT(sizeof(ConnectionClassVtableLayout) == 0x28);
struct IPXConnClassVtableLayout
{
    void* slot_00;
    void* slot_01;
    void* slot_02;
    void* slot_03;
    void* slot_04;
    void* slot_05;
    void* slot_06;
    void* slot_07;
    void* slot_08;
    void* slot_09;
    void* slot_0A;
};
GG_STATIC_ASSERT(offsetof(IPXConnClassVtableLayout, slot_00) == 0x00);
GG_STATIC_ASSERT(offsetof(IPXConnClassVtableLayout, slot_01) == 0x04);
GG_STATIC_ASSERT(offsetof(IPXConnClassVtableLayout, slot_02) == 0x08);
GG_STATIC_ASSERT(offsetof(IPXConnClassVtableLayout, slot_03) == 0x0C);
GG_STATIC_ASSERT(offsetof(IPXConnClassVtableLayout, slot_04) == 0x10);
GG_STATIC_ASSERT(offsetof(IPXConnClassVtableLayout, slot_05) == 0x14);
GG_STATIC_ASSERT(offsetof(IPXConnClassVtableLayout, slot_06) == 0x18);
GG_STATIC_ASSERT(offsetof(IPXConnClassVtableLayout, slot_07) == 0x1C);
GG_STATIC_ASSERT(offsetof(IPXConnClassVtableLayout, slot_08) == 0x20);
GG_STATIC_ASSERT(offsetof(IPXConnClassVtableLayout, slot_09) == 0x24);
GG_STATIC_ASSERT(offsetof(IPXConnClassVtableLayout, slot_0A) == 0x28);
GG_STATIC_ASSERT(sizeof(IPXConnClassVtableLayout) == 0x2C);
struct IPXGlobalConnClassVtableLayout
{
    void* slot_00;
    void* slot_01;
    void* slot_02;
    void* slot_03;
    void* slot_04;
    void* slot_05;
    void* slot_06;
    void* slot_07;
    void* slot_08;
    void* slot_09;
    void* slot_0A;
    void* slot_0B;
    void* slot_0C;
    void* slot_0D;
    void* slot_0E;
    void* slot_0F;
    void* slot_10;
    void* slot_11;
};
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClassVtableLayout, slot_00) == 0x00);
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClassVtableLayout, slot_01) == 0x04);
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClassVtableLayout, slot_02) == 0x08);
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClassVtableLayout, slot_03) == 0x0C);
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClassVtableLayout, slot_04) == 0x10);
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClassVtableLayout, slot_05) == 0x14);
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClassVtableLayout, slot_06) == 0x18);
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClassVtableLayout, slot_07) == 0x1C);
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClassVtableLayout, slot_08) == 0x20);
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClassVtableLayout, slot_09) == 0x24);
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClassVtableLayout, slot_0A) == 0x28);
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClassVtableLayout, slot_0B) == 0x2C);
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClassVtableLayout, slot_0C) == 0x30);
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClassVtableLayout, slot_0D) == 0x34);
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClassVtableLayout, slot_0E) == 0x38);
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClassVtableLayout, slot_0F) == 0x3C);
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClassVtableLayout, slot_10) == 0x40);
GG_STATIC_ASSERT(offsetof(IPXGlobalConnClassVtableLayout, slot_11) == 0x44);
GG_STATIC_ASSERT(sizeof(IPXGlobalConnClassVtableLayout) == 0x48);

// Shared inline cleanup observed in scalar deleting wrapper 0x540670.
// No separate ordinary-destructor entry address is claimed.
inline IPXGlobalConnClass::~IPXGlobalConnClass()
{
    if (Ids) {
        delete Ids;
        Ids = 0;
    }
    if (Addresses) {
        delete Addresses;
        Addresses = 0;
    }
}

#endif
