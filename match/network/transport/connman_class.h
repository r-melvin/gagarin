// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout, offsets, RTTI and vtable slots read from the user's retail
//   gamemd.exe v1.001 through the local Ghidra CLI (member-access disassembly
//   of every function in connman_class.cpp, RTTI locators 0x8049B8 and
//   0x804988, vtables 0x7EC1D4 and 0x7EC16C). Service, SetTiming,
//   ResponseTime, Connection, CurConnection and the timing members are
//   YRpp-cross-checked names confirmed by these bodies; GlobalChannel and
//   RouterChannel are named by the binary's debug strings. Unattested slots
//   are vf_<slot>; names marked "behavioural" describe what the body does.
//
// Network transport, hierarchy "connman": ConnManClass -> IPXManagerClass.
//
// DEPENDENCIES on the other transport hierarchies (shared declarations, each type
// is defined once): conn_types.h owns ConnectionClass / IPXConnClass /
// IPXGlobalConnClass / CommBufferClass and the shared globals; IPXAddressClass
// is owned by the shared _layout header.
// winsock_interface_class.h owns WinsockInterfaceClass.
#ifndef GG_MATCH_NETWORK_TRANSPORT_CONNMAN_CLASS_H
#define GG_MATCH_NETWORK_TRANSPORT_CONNMAN_CLASS_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "conn_types.h"

// Wire packet as read by IPXManagerClass::Service (offsets from the receive
// buffer). Modelled size 0x400 (the receive length passed to the interface).
struct IPXPacket
{
    unsigned short Magic;         // +0x00 compared with the channel magic numbers
    unsigned char  Code;          // +0x02 0 data-needs-ack, 1 data-no-ack, 2 ack
    unsigned char  Flag;          // +0x03
    int            Id;            // +0x04
    int            unknown_08;    // +0x08
    unsigned short unknown_0C;    // +0x0C
    unsigned char  Kind;          // +0x0E (0x19 tested)
    unsigned char  unknown_0F;
    int            Type;          // +0x10 (0x27, 0x29, 0x0D tested; low byte also read as a signed id)
    char           Name[0x14];    // +0x14
    char           unknown_28[0x400 - 0x28];
};
GG_STATIC_ASSERT(offsetof(IPXPacket, Magic) == 0x00);
GG_STATIC_ASSERT(offsetof(IPXPacket, Code)  == 0x02);
GG_STATIC_ASSERT(offsetof(IPXPacket, Flag)  == 0x03);
GG_STATIC_ASSERT(offsetof(IPXPacket, Id)    == 0x04);
GG_STATIC_ASSERT(offsetof(IPXPacket, Kind)  == 0x0E);
GG_STATIC_ASSERT(offsetof(IPXPacket, Type)  == 0x10);
GG_STATIC_ASSERT(offsetof(IPXPacket, Name)  == 0x14);
GG_STATIC_ASSERT(sizeof(IPXPacket)          == 0x400);

// ---------------------------------------------------------------------------
// ConnManClass: abstract connection manager (RTTI .?AVConnManClass@@, locator
// 0x8049B8, one base chain entry). Retail table 0x7EC1D4 has scalar deleting
// destructor target 0x543100 at slot 0 and _purecall (0x4C9150) at slots 1..15,
// followed by zero words. Its empty native destructor naturally emits the
// scalar deleting body at 0x543100 when the derived destructor is compiled.
// IPXManagerClass members start at +0x04 in this prefix view.
// ---------------------------------------------------------------------------
// VTABLE: GAMEMD 0x7EC1D4 -- 16 observed retail slots.
class ConnManClass
{
public:
    // SYNTHETIC: GAMEMD 0x543100 -- compiler-generated scalar deleting entry.
    virtual ~ConnManClass() {}                                             // slot 0
    virtual int  Service() = 0;                                            // slot 1
    virtual int  vf_2(void* buf, int buflen, int needsAck, int id) = 0;         // slot 2
    virtual int  vf_3(void* buf, int* buflen, int* id) = 0;             // slot 3
    virtual int  vf_4() = 0;                                     // slot 4
    virtual int  vf_5(int index) = 0;                              // slot 5
    virtual int  vf_6(int id) = 0;                              // slot 6
    virtual int  vf_7() = 0;                                      // slot 7
    virtual int  vf_8() = 0;                                   // slot 8
    virtual int  vf_9(int id) = 0;                                      // slot 9
    virtual int  vf_10(int id) = 0;                                   // slot 10
    virtual void vf_11(bool a1) = 0;                           // slot 11
    virtual int  ResponseTime() = 0;                                       // slot 12
    virtual void SetTiming(int retrydelta, int maxretries, int timeout, bool setglobal) = 0; // slot 13
    virtual void vf_14(int retrydelta, int maxretries, int timeout) = 0;           // slot 14
    virtual void vf_15(int index, int a2, int a3, int a4, int a5, int a6) = 0;      // slot 15
};

// ---------------------------------------------------------------------------
// IPXManagerClass (RTTI .?AVIPXManagerClass@@, locator 0x804988, chain
// IPXManagerClass -> ConnManClass). Retail vtable address point 0x7EC16C, 25
// observed slots followed by the ConnManClass locator pointer 0x8049B8 at
// 0x7EC1D0. This bounded TU models touched member offsets only.
// ---------------------------------------------------------------------------
// VTABLE: GAMEMD 0x7EC16C -- 25 observed retail slots.
class IPXManagerClass : public ConnManClass
{
public:
    // FUNCTION: GAMEMD 0x5408F0 (declaration) -- constructor; RET 0x18.
    IPXManagerClass(int a1, int a2, int a3, int a4, unsigned short a5,
                    unsigned short a6);
    // FUNCTION: GAMEMD 0x5409F0 (decl; reloc) -- ordinary destructor.
    // SYNTHETIC: GAMEMD 0x5430E0 (decl; reloc) -- scalar deleting entry.
    virtual ~IPXManagerClass();                                            // slot 0
    virtual int  Service();                                                // slot 1
    virtual int  vf_2(void* buf, int buflen, int needsAck, int id);             // slot 2
    virtual int  vf_3(void* buf, int* buflen, int* id);                 // slot 3
    virtual int  vf_4();                                         // slot 4
    virtual int  vf_5(int index);                                  // slot 5
    virtual int  vf_6(int id);                                  // slot 6
    virtual int  vf_7();                                          // slot 7
    virtual int  vf_8();                                       // slot 8
    virtual int  vf_9(int id);                                          // slot 9
    virtual int  vf_10(int id);                                       // slot 10
    virtual void vf_11(bool a1);                               // slot 11
    virtual int  ResponseTime();                                           // slot 12
    virtual void SetTiming(int retrydelta, int maxretries, int timeout, bool setglobal); // slot 13
    virtual void vf_14(int retrydelta, int maxretries, int timeout);           // slot 14
    virtual void vf_15(int index, int a2, int a3, int a4, int a5, int a6);      // slot 15
    virtual void SaveGlobalTiming();                                       // slot 16 (behavioural)
    virtual void RestoreGlobalTiming();                                    // slot 17 (behavioural)
    virtual void SetRouterTiming(int retrydelta, int maxretries, int timeout);          // slot 18 (behavioural; sets the router and multicast channels)
    virtual int  ConnectionIndexOf(ConnectionClass* conn);                 // slot 19 (behavioural)
    virtual int  vf_20();                                         // slot 20
    virtual int  vf_21();                                      // slot 21
    virtual int  ResponseTimeOf(int index);                                // slot 22 (behavioural)
    virtual void vf_23();                                            // slot 23 (behavioural)
    virtual void Slot24(int a1, int a2);                                   // slot 24 (empty body 0x543040)

    // FUNCTION: GAMEMD 0x540A80 (decl; reloc) -- direct caller 0x5DA6C0.
    // Named by its own trace string "**** IPXManagerClass::Init ***".
    int Init();
    // FUNCTION: GAMEMD 0x540C50 (declaration)
    int FUN_00540C50();
    // FUNCTION: GAMEMD 0x540DC0 (declaration)
    int FUN_00540DC0(int id, wchar_t* name, IPXAddressClass* address);
    // FUNCTION: GAMEMD 0x540E70 (declaration)
    int FUN_00540E70();
    // FUNCTION: GAMEMD 0x540F00 (declaration)
    int FUN_00540F00(int id);
    // FUNCTION: GAMEMD 0x540FC0 (declaration)
    wchar_t* FUN_00540FC0(int id);
    // FUNCTION: GAMEMD 0x541000 (declaration)
    IPXAddressClass* FUN_00541000(int id);
    // FUNCTION: GAMEMD 0x5410C0 (declaration)
    void FUN_005410C0(int index, int id, wchar_t* name);
    // FUNCTION: GAMEMD 0x5410F0 (declaration)
    int FUN_005410F0(void* buf, int buflen, int needsAck, IPXAddressClass* address,
                     unsigned short port, int packet_id);
    // FUNCTION: GAMEMD 0x541170 (declaration)
    int FUN_00541170(void* buf, int buflen, int needsAck, int id);
    // FUNCTION: GAMEMD 0x541260 (declaration)
    int FUN_00541260(void* buf, int buflen, int needsAck, const wchar_t* name);
    // FUNCTION: GAMEMD 0x541370 (declaration)
    int FUN_00541370(void* buf, int* buflen, IPXAddressClass* address, unsigned short* port);
    // FUNCTION: GAMEMD 0x5413B0 (declaration)
    int FUN_005413B0(int index, void* buf, int* buflen, IPXAddressClass* address,
                     unsigned short* port, unsigned long* packet_id);
    // FUNCTION: GAMEMD 0x5413F0 (declaration)
    void FUN_005413F0(int index);
    // FUNCTION: GAMEMD 0x541410 (declaration)
    int FUN_00541410(void* buf, int buflen, unsigned char needsAck);
    // FUNCTION: GAMEMD 0x541480 (declaration)
    int FUN_00541480(void* buf, int* buflen, IPXAddressClass* address, unsigned short* port);
    // FUNCTION: GAMEMD 0x542280 (declaration)
    void FUN_00542280(int id, IPXAddressClass* address);
    // FUNCTION: GAMEMD 0x5422C0 (declaration)
    int FUN_005422C0();
    // FUNCTION: GAMEMD 0x542430 (declaration)
    void FUN_00542430(unsigned short port);
    // FUNCTION: GAMEMD 0x5424C0 (declaration)
    unsigned long FUN_005424C0();
    // FUNCTION: GAMEMD 0x5424E0 (declaration)
    unsigned long FUN_005424E0();
    // FUNCTION: GAMEMD 0x542500 (declaration)
    unsigned long FUN_00542500();
    // FUNCTION: GAMEMD 0x542F30 (declaration)
    char* FUN_00542F30();
    // FUNCTION: GAMEMD 0x543050 (declaration)
    void FUN_00543050(IPXAddressClass* address);
    // FUNCTION: GAMEMD 0x543080 (declaration)
    void FUN_00543080();
    // FUNCTION: GAMEMD 0x543090 (declaration)
    void FUN_00543090();
    // FUNCTION: GAMEMD 0x5430A0 (declaration)
    void FUN_005430A0(IPXAddressClass* address, unsigned short port);
    // FUNCTION: GAMEMD 0x5430C0 (declaration)
    void FUN_005430C0(unsigned int age);
    // FUNCTION: GAMEMD 0x542FC0 (decl; reloc) -- direct caller 0x5DA6C0.
    void FUN_00542FC0(int* value);

    // FUNCTION: GAMEMD 0x541680 (decl; reloc)
    // Service calls this helper; its body is deferred to a later batch.
    bool FUN_00541680(IPXPacket* header, IPXPacket* packet, unsigned int size,
                      void* from, unsigned short port);

    unsigned char    unknown_04;               // +0x04 (ctor stores the interface-open result)
    unsigned char    Active;                  // +0x05
    char             unknown_06[0x08 - 0x06];
    int              unknown_08;              // +0x08 ctor a1 (global channel max length)
    int              unknown_0C;              // +0x0C ctor a3 (global channel send count)
    int              unknown_10;              // +0x10 ctor a2
    int              unknown_14;              // +0x14 ctor a4
    int              unknown_18;              // +0x18 ctor a1 (router channel max length)
    int              unknown_1C;              // +0x1C ctor a4 (router channel send count)
    unsigned short   unknown_20;             // +0x20
    unsigned short   unknown_22;              // +0x22 ctor a5, byte-swapped
    int              unknown_24;              // +0x24
    IPXConnClass*    Connection[7];           // +0x28
    int              ConnectionCount;                 // +0x44
    IPXGlobalConnClass* GlobalChannel;        // +0x48
    IPXGlobalConnClass* RouterChannel;        // +0x4C (vslot 12 / 16 calls exist only on IPXGlobalConnClass)
    IPXConnClass*    MulticastChannel;        // +0x50
    int              CurConnection;           // +0x54
    int              RetryDelta;              // +0x58
    int              MaxRetries;              // +0x5C
    int              Timeout;                 // +0x60
    int              SavedRetryDelta;         // +0x64
    int              SavedMaxRetries;         // +0x68
    int              SavedTimeout;            // +0x6C
    int              unknown_70;              // +0x70
    int              unknown_74;              // +0x74 (Init passes it to 0x53F4F0)
    int              unknown_78;              // +0x78
    int              unknown_7C;              // +0x7C (Init passes it to 0x53F4F0)
    int              unknown_80;              // +0x80 (Init passes it to 0x53F4F0)
    char             unknown_84[0x8C - 0x84];
    IPXPacket*       unknown_8C;           // +0x8C
    int              unknown_90;              // +0x90
    int              unknown_94;              // +0x94 (Init passes it to 0x53F4F0)
    int              unknown_98;              // +0x98 (Init passes it to 0x53F4F0)
    int              unknown_9C;              // +0x9C
    int              unknown_A0;              // +0xA0
    int              unknown_A4;              // +0xA4
    int              FailedId;                // +0xA8
};

GG_STATIC_ASSERT(offsetof(IPXManagerClass, unknown_04)       == 0x04);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, Active)          == 0x05);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, unknown_08)      == 0x08);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, unknown_0C)      == 0x0C);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, unknown_10)      == 0x10);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, unknown_14)      == 0x14);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, unknown_18)      == 0x18);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, unknown_1C)      == 0x1C);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, unknown_20)     == 0x20);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, unknown_22)      == 0x22);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, unknown_24)      == 0x24);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, Connection)      == 0x28);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, ConnectionCount)         == 0x44);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, GlobalChannel)   == 0x48);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, RouterChannel)  == 0x4C);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, MulticastChannel)       == 0x50);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, CurConnection)   == 0x54);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, RetryDelta)      == 0x58);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, MaxRetries)      == 0x5C);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, Timeout)         == 0x60);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, SavedRetryDelta) == 0x64);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, SavedMaxRetries) == 0x68);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, SavedTimeout)    == 0x6C);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, unknown_74)      == 0x74);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, unknown_7C)      == 0x7C);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, unknown_80)      == 0x80);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, unknown_8C)   == 0x8C);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, unknown_94)      == 0x94);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, unknown_98)      == 0x98);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, unknown_A0)      == 0xA0);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, unknown_A4)      == 0xA4);
GG_STATIC_ASSERT(offsetof(IPXManagerClass, FailedId)        == 0xA8);

// GLOBAL: GAMEMD 0xA8E9C0 -- the manager instance (constructed at 0x4E80A0). The
// conn hierarchy reaches 0x541070 / 0x540F90 / 0x540FA0 on it by direct (class
// qualified) calls.
extern IPXManagerClass Manager_00A8E9C0;


// Retail slot offsets for the recorded address points. These storage views
// assert slot positions; compiler-emitted tables are checked separately.
struct ConnManClassVtableLayout
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
};
GG_STATIC_ASSERT(offsetof(ConnManClassVtableLayout, slot_00) == 0x00);
GG_STATIC_ASSERT(offsetof(ConnManClassVtableLayout, slot_01) == 0x04);
GG_STATIC_ASSERT(offsetof(ConnManClassVtableLayout, slot_02) == 0x08);
GG_STATIC_ASSERT(offsetof(ConnManClassVtableLayout, slot_03) == 0x0C);
GG_STATIC_ASSERT(offsetof(ConnManClassVtableLayout, slot_04) == 0x10);
GG_STATIC_ASSERT(offsetof(ConnManClassVtableLayout, slot_05) == 0x14);
GG_STATIC_ASSERT(offsetof(ConnManClassVtableLayout, slot_06) == 0x18);
GG_STATIC_ASSERT(offsetof(ConnManClassVtableLayout, slot_07) == 0x1C);
GG_STATIC_ASSERT(offsetof(ConnManClassVtableLayout, slot_08) == 0x20);
GG_STATIC_ASSERT(offsetof(ConnManClassVtableLayout, slot_09) == 0x24);
GG_STATIC_ASSERT(offsetof(ConnManClassVtableLayout, slot_0A) == 0x28);
GG_STATIC_ASSERT(offsetof(ConnManClassVtableLayout, slot_0B) == 0x2C);
GG_STATIC_ASSERT(offsetof(ConnManClassVtableLayout, slot_0C) == 0x30);
GG_STATIC_ASSERT(offsetof(ConnManClassVtableLayout, slot_0D) == 0x34);
GG_STATIC_ASSERT(offsetof(ConnManClassVtableLayout, slot_0E) == 0x38);
GG_STATIC_ASSERT(offsetof(ConnManClassVtableLayout, slot_0F) == 0x3C);
GG_STATIC_ASSERT(sizeof(ConnManClassVtableLayout) == 0x40);
struct IPXManagerClassVtableLayout
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
    void* slot_12;
    void* slot_13;
    void* slot_14;
    void* slot_15;
    void* slot_16;
    void* slot_17;
    void* slot_18;
};
GG_STATIC_ASSERT(offsetof(IPXManagerClassVtableLayout, slot_00) == 0x00);
GG_STATIC_ASSERT(offsetof(IPXManagerClassVtableLayout, slot_01) == 0x04);
GG_STATIC_ASSERT(offsetof(IPXManagerClassVtableLayout, slot_02) == 0x08);
GG_STATIC_ASSERT(offsetof(IPXManagerClassVtableLayout, slot_03) == 0x0C);
GG_STATIC_ASSERT(offsetof(IPXManagerClassVtableLayout, slot_04) == 0x10);
GG_STATIC_ASSERT(offsetof(IPXManagerClassVtableLayout, slot_05) == 0x14);
GG_STATIC_ASSERT(offsetof(IPXManagerClassVtableLayout, slot_06) == 0x18);
GG_STATIC_ASSERT(offsetof(IPXManagerClassVtableLayout, slot_07) == 0x1C);
GG_STATIC_ASSERT(offsetof(IPXManagerClassVtableLayout, slot_08) == 0x20);
GG_STATIC_ASSERT(offsetof(IPXManagerClassVtableLayout, slot_09) == 0x24);
GG_STATIC_ASSERT(offsetof(IPXManagerClassVtableLayout, slot_0A) == 0x28);
GG_STATIC_ASSERT(offsetof(IPXManagerClassVtableLayout, slot_0B) == 0x2C);
GG_STATIC_ASSERT(offsetof(IPXManagerClassVtableLayout, slot_0C) == 0x30);
GG_STATIC_ASSERT(offsetof(IPXManagerClassVtableLayout, slot_0D) == 0x34);
GG_STATIC_ASSERT(offsetof(IPXManagerClassVtableLayout, slot_0E) == 0x38);
GG_STATIC_ASSERT(offsetof(IPXManagerClassVtableLayout, slot_0F) == 0x3C);
GG_STATIC_ASSERT(offsetof(IPXManagerClassVtableLayout, slot_10) == 0x40);
GG_STATIC_ASSERT(offsetof(IPXManagerClassVtableLayout, slot_11) == 0x44);
GG_STATIC_ASSERT(offsetof(IPXManagerClassVtableLayout, slot_12) == 0x48);
GG_STATIC_ASSERT(offsetof(IPXManagerClassVtableLayout, slot_13) == 0x4C);
GG_STATIC_ASSERT(offsetof(IPXManagerClassVtableLayout, slot_14) == 0x50);
GG_STATIC_ASSERT(offsetof(IPXManagerClassVtableLayout, slot_15) == 0x54);
GG_STATIC_ASSERT(offsetof(IPXManagerClassVtableLayout, slot_16) == 0x58);
GG_STATIC_ASSERT(offsetof(IPXManagerClassVtableLayout, slot_17) == 0x5C);
GG_STATIC_ASSERT(offsetof(IPXManagerClassVtableLayout, slot_18) == 0x60);
GG_STATIC_ASSERT(sizeof(IPXManagerClassVtableLayout) == 0x64);

#endif  // GG_MATCH_NETWORK_TRANSPORT_CONNMAN_CLASS_H
