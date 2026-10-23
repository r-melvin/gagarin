// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit TU108 of retail gamemd.exe v1.001; its source-file name is
//   not attested by the binary, so the file keeps a placeholder name. Code range 0x5406e0-0x54311f,
//   segmented from retail evidence (link-ordered static-initialiser table, RTTI class
//   ownership, neighbouring object bounds). Functions are in ascending retail address order.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
//
// The IPXManagerClass unit of retail .text (0x540710..0x5430DF), the parts not
// already in connman_class.cpp: the unit's header-global initialisers, the
// constructor, Init and the non-virtual connection helpers, in retail address
// order. IPXManagerClass is declared in connman_class.h.

#include <string.h>
#include "transport/connman_class.h"
#include "transport/ipx_interface_class.h"
#include "../core/vector_class.h"

// ---- run-time initialised copies of the shared tuning globals -------------

// GLOBAL: GAMEMD 0xAA0650
extern double DAT_00AA0650;
// GLOBAL: GAMEMD 0x7EC158
const double DAT_007EC158 = 60.0;

// GLOBAL: GAMEMD 0xAA06A0
double DAT_00AA06A0 = DAT_00AA0650 / DAT_007EC158;

// GLOBAL: GAMEMD 0xAA0688
double DAT_00AA0688 = 1.0 / DAT_00AA06A0;

struct TuningCoordInit_540
{
    int X;
    int Y;
    int Z;
    TuningCoordInit_540(int x, int y, int z) { X = x; Y = y; Z = z; }
};

// GLOBAL: GAMEMD 0xAA0690
TuningCoordInit_540 DAT_00AA0690(128, 128, 0);

// The 12-byte address block the forwarding step sends to; only the dword at +4
// is set at run time (the loopback IP).
struct LoopbackAddress_00AA06AC
{
    unsigned long unknown_00;   // +0x00
    unsigned long Address;      // +0x04
    unsigned long unknown_08;   // +0x08
};
GG_STATIC_ASSERT(offsetof(LoopbackAddress_00AA06AC, Address) == 4);
GG_STATIC_ASSERT(sizeof(LoopbackAddress_00AA06AC) == 0xC);

// ---- external functions ----------------------------------------------------

// FUNCTION: GAMEMD 0x53F4F0 (decl; reloc) -- stores its seven arguments in
// the 0xAA05xx block; ECX/EDX + five stack words, RET 0x14.
void FUN_0053F4F0(unsigned short a1, int a2, int a3, int a4, int a5, int a6, int a7);

// FUNCTION: GAMEMD 0x53F540 (decl; reloc)
int __cdecl FUN_0053F540();

// FUNCTION: GAMEMD 0x53F5B0 (decl; reloc)
void __cdecl FUN_0053F5B0();

// FUNCTION: GAMEMD 0x735120 (decl; reloc) -- widen a narrow string; ECX = text.
wchar_t* FUN_00735120(const char* text);

// GLOBAL: GAMEMD 0xA8DA74 -- the player vector (Items 0xA8DA78, Count 0xA8DA84).
extern DynamicVectorClass<NetPlayerClass*> Players_00A8DA74;

// LIBRARY: GAMEMD 0x7DD0F8 _wcsicmp
extern "C" int __cdecl _wcsicmp(const wchar_t* a, const wchar_t* b);

// LIBRARY: GAMEMD 0x7C8962 -- WSOCK32 ordinal 8 (htonl) import thunk.
extern "C" unsigned long __stdcall htonl(unsigned long hostlong);

// GLOBAL: GAMEMD 0xB052EC
extern int DAT_00B052EC;

// GLOBAL: GAMEMD 0xA8E2B2 -- per-player port words.
extern unsigned short Ports_00A8E2B2[];

// SYNTHETIC: GAMEMD 0x540710

// SYNTHETIC: GAMEMD 0x540730

// SYNTHETIC: GAMEMD 0x5408B0

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5408F0
IPXManagerClass::IPXManagerClass(int a1, int a2, int a3, int a4, unsigned short a5,
                                 unsigned short a6)
{
    if (Interface_00887628) {
        delete Interface_00887628;
        Interface_00887628 = 0;
    }
    Interface_00887628 = new IPXInterfaceClass;
    if (Interface_00887628->StartupWinsock()) {
        unknown_04 = 1;
    } else {
        unknown_04 = 0;
    }
    if (Interface_00887628) {
        delete Interface_00887628;
    }
    Interface_00887628 = 0;

    Active = 0;
    unknown_08 = a1;
    unknown_0C = a3;
    unknown_10 = a2;
    unknown_14 = a4;
    unknown_18 = a1;
    unknown_1C = a4;
    unknown_20 = a6;
    unknown_22 = (unsigned short)((a5 >> 8) | (a5 << 8));
    unknown_24 = 0;
    ConnectionCount = 0;
    CurConnection = 0;
    for (int i = 0; i < 7; ++i) {
        Connection[i] = 0;
    }
    GlobalChannel = 0;
    RouterChannel = 0;
    MulticastChannel = 0;
    unknown_A0 = 0;
    unknown_A4 = 0;
    FailedId = -1;
    RetryDelta = 2;
    MaxRetries = -1;
    Timeout = 60;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x540A80  IPXManagerClass::Init
// Named by its own trace string "**** IPXManagerClass::Init ***".
int IPXManagerClass::Init()
{
    FUN_004068E0("**** IPXManagerClass::Init ***\n");
    if (Interface_00887628) {
        Interface_00887628->DiscardInBuffers();
        Interface_00887628->DiscardOutBuffers();
    }
    if (Session_00A8B238.GameMode != 4) {
        if (!unknown_04) {
            return 0;
        }
        if (Active) {
            FUN_0053F5B0();
            Active = 0;
        }
    } else {
        unknown_04 = 1;
    }
    if (GlobalChannel) {
        delete GlobalChannel;
        GlobalChannel = 0;
    }
    if (RouterChannel) {
        delete RouterChannel;
        RouterChannel = 0;
    }
    if (MulticastChannel) {
        delete MulticastChannel;
        MulticastChannel = 0;
    }
    for (int i = 0; i < ConnectionCount; ++i) {
        delete Connection[i];
        Connection[i] = 0;
    }
    ConnectionCount = 0;

    GlobalChannel = new IPXGlobalConnClass(unknown_0C, unknown_0C * 2, unknown_08, unknown_20, 0x1236);
    if (!GlobalChannel) {
        return 0;
    }
    GlobalChannel->Init();
    GlobalChannel->RetryDelta = RetryDelta;
    GlobalChannel->MaxRetries = MaxRetries;
    GlobalChannel->Timeout = Timeout;

    RouterChannel = new IPXGlobalConnClass(unknown_1C, unknown_1C * 2, unknown_18, unknown_20, 0xCDEF);
    if (!RouterChannel) {
        return 0;
    }
    RouterChannel->Init();
    RouterChannel->RetryDelta = RetryDelta;
    RouterChannel->MaxRetries = MaxRetries;
    RouterChannel->Timeout = Timeout;

    FUN_0053F4F0(unknown_22, unknown_24, unknown_7C, unknown_94, unknown_80, unknown_98, unknown_74);
    if (!Interface_00887628) {
        return 0;
    }
    if (Session_00A8B238.GameMode != 4 && !FUN_0053F540()) {
        return 0;
    }
    Active = 1;
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x540C50
int IPXManagerClass::FUN_00540C50()
{
    return unknown_04;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x540DC0
int IPXManagerClass::FUN_00540DC0(int id, wchar_t* name, IPXAddressClass* address)
{
    if (!unknown_04) {
        return 0;
    }
    if (ConnectionCount == 7) {
        return 0;
    }
    Connection[ConnectionCount] = new IPXConnClass(unknown_14, unknown_14, unknown_10, unknown_20,
                                                   address, id, name, 0);
    if (!Connection[ConnectionCount]) {
        return 0;
    }
    Connection[ConnectionCount]->Init();
    Connection[ConnectionCount]->RetryDelta = RetryDelta;
    Connection[ConnectionCount]->MaxRetries = MaxRetries;
    Connection[ConnectionCount]->Timeout = Timeout;
    ConnectionCount++;
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x540E70
int IPXManagerClass::FUN_00540E70()
{
    if (!unknown_04) {
        return 0;
    }
    MulticastChannel = new IPXConnClass(unknown_14, unknown_14, unknown_10, unknown_20,
                                        &Players_00A8DA74[0]->Address, -1,
                                        FUN_00735120("Multicast"), 0);
    if (!MulticastChannel) {
        return 0;
    }
    MulticastChannel->Init();
    MulticastChannel->RetryDelta = RetryDelta;
    MulticastChannel->MaxRetries = MaxRetries;
    MulticastChannel->Timeout = Timeout;
    return 1;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x540F00
int IPXManagerClass::FUN_00540F00(int id)
{
    if (!unknown_04 || !ConnectionCount) {
        return 0;
    }
    for (int i = 0; i < ConnectionCount; ++i) {
        if (Connection[i]->ID == id) {
            delete Connection[i];
            for (int j = i; j < ConnectionCount - 1; ++j) {
                Connection[j] = Connection[j + 1];
            }
            ConnectionCount--;
            if (CurConnection >= ConnectionCount) {
                CurConnection = 0;
            }
            return 1;
        }
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x540FC0
wchar_t* IPXManagerClass::FUN_00540FC0(int id)
{
    for (int i = 0; i < ConnectionCount; ++i) {
        if (Connection[i]->ID == id) {
            return Connection[i]->Name;
        }
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x541000
IPXAddressClass* IPXManagerClass::FUN_00541000(int id)
{
    for (int i = 0; i < ConnectionCount; ++i) {
        if (Connection[i]->ID == id) {
            return &Connection[i]->Address;
        }
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5410C0
void IPXManagerClass::FUN_005410C0(int index, int id, wchar_t* name)
{
    if (index < ConnectionCount) {
        Connection[index]->ID = id;
        wcscpy(Connection[index]->Name, name);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5410F0
int IPXManagerClass::FUN_005410F0(void* buf, int buflen, int needsAck, IPXAddressClass* address,
                                  unsigned short port, int packet_id)
{
    if (!unknown_04 || !Active) {
        return 0;
    }
    if (needsAck && (!address || address->IsBroadcast())) {
        needsAck = 0;
    }
    int result = GlobalChannel->vf_11(buf, buflen, address, needsAck, port, packet_id);
    if (!result) {
        FUN_004068E0("Send overflow %d\n", ++unknown_A0);
    }
    return result;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x541170
// PARTIAL (84.1%; mnemonic multiset identical). Retail holds the player count
// in ECX and this in ESI; VC6 picks EDX and EDI here and schedules the count
// load first. The sibling 0x541260 with the same shape matches. Tried: count
// test `> 0`, a while loop, the address declared at the top (5.6%).
int IPXManagerClass::FUN_00541170(void* buf, int buflen, int needsAck, int id)
{
    if (Players_00A8DA74.Count && Players_00A8DA74[0]->Id == id) {
        return 0;
    }
    for (int i = 1; i < Players_00A8DA74.Count; ++i) {
        if (Players_00A8DA74[i]->Id == id) {
            IPXAddressClass address = Players_00A8DA74[i]->Address;
            return FUN_005410F0(buf, buflen, needsAck, &address, Ports_00A8E2B2[i], 0);
        }
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x541260
int IPXManagerClass::FUN_00541260(void* buf, int buflen, int needsAck, const wchar_t* name)
{
    if (Players_00A8DA74.Count && _wcsicmp(Players_00A8DA74[0]->Name, name) == 0) {
        return 0;
    }
    for (int i = 1; i < Players_00A8DA74.Count; ++i) {
        if (_wcsicmp(Players_00A8DA74[i]->Name, name) == 0) {
            IPXAddressClass address = Players_00A8DA74[i]->Address;
            return FUN_005410F0(buf, buflen, needsAck, &address, Ports_00A8E2B2[i], 0);
        }
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x541370
int IPXManagerClass::FUN_00541370(void* buf, int* buflen, IPXAddressClass* address,
                                  unsigned short* port)
{
    if (!unknown_04 || !Active) {
        return 0;
    }
    return GlobalChannel->vf_13(buf, buflen, address, port);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5413B0
int IPXManagerClass::FUN_005413B0(int index, void* buf, int* buflen, IPXAddressClass* address,
                                  unsigned short* port, unsigned long* packet_id)
{
    if (!unknown_04 || !Active) {
        return 0;
    }
    return GlobalChannel->vf_14(index, buf, buflen, address, port, packet_id);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5413F0
void IPXManagerClass::FUN_005413F0(int index)
{
    if (unknown_04 && Active) {
        GlobalChannel->vf_15(index);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x541410
int IPXManagerClass::FUN_00541410(void* buf, int buflen, unsigned char needsAck)
{
    if (!unknown_04 || !Active || !RouterChannel) {
        return 0;
    }
    int result = RouterChannel->vf_11(buf, buflen, &RouterChannel->Address, needsAck, 0, 0);
    if (!result) {
        FUN_004068E0("Send overflow %d\n", ++unknown_A0);
    }
    return result;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x541480
int IPXManagerClass::FUN_00541480(void* buf, int* buflen, IPXAddressClass* address,
                                  unsigned short* port)
{
    if (!unknown_04 || !Active) {
        return 0;
    }
    return RouterChannel->vf_13(buf, buflen, address, port);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x541680
// PARTIAL (32.3%). Retail keeps the address of the header's +0x08 dword in
// EBX across the remote branch (the +0x08 dword and +0x0C word read as one
// six-byte node), and its pops follow a different epilogue order. Tried:
// flat else-if, early returns in the remote branch; a node-typed header view
// would need Service's call site changed and is left for that function.
// The forwarding step of Service: in game mode 4 with forwarding on, a packet
// that carries the forwarder port is sent on to the loopback forwarder, and one
// that names a remote node is re-addressed and sent there. Returns true when the
// packet was forwarded.
bool IPXManagerClass::FUN_00541680(IPXPacket* header, IPXPacket* packet, unsigned int size,
                                   void* from, unsigned short port)
{
    // GLOBAL: GAMEMD 0xAA06AC -- the loopback address block (dword +4 = 0xAA06B0).
    static LoopbackAddress_00AA06AC loopback = { 0, htonl(0x7F000001), 0 };

    if (Session_00A8B238.GameMode == 4 && Flag_00A8DBA0 && DAT_00B052EC) {
        if (header->unknown_0C == Port_00841F3C) {
            header->unknown_0C = port;
            header->unknown_08 = *(unsigned long*)((IPXAddressClass*)from)->NodeAddress;
            FUN_004068E0("Forwarding packet from %s ; %d to forwarder\n",
                         ((IPXAddressClass*)from)->FUN_0053F0E0(0), port);
            Interface_00887628->SendPacket(packet, size, &loopback, 0xC, false, 1,
                                           (unsigned short)Port_00841F3C);
            return true;
        }
        if (header->unknown_0C) {
            NodeAddressType node;
            Players_00A8DA74[0]->Address.FUN_0053EDC0(&node);
            if (*(unsigned long*)node.Node == (unsigned long)header->unknown_08
                && Ports_00A8E2B2[0] == header->unknown_0C) {
                FUN_004068E0("Packet is supposed to be forwarded to us - just adding it to our queue\n");
            } else if (header->unknown_08) {
                unsigned short to_port = header->unknown_0C;
                IPXAddressClass address;
                NodeAddressType to_node;
                *(unsigned long*)to_node.Node = header->unknown_08;
                address.FUN_0053EDE0(&to_node);
                address.FUN_0053F200(to_port);
                header->unknown_0C = 0;
                header->unknown_08 = 0;
                FUN_004068E0("Forwarding packet from router to %s\n", address.FUN_0053F0E0(0));
                Interface_00887628->SendPacket(packet, size, &address, 0xC, false, 1, to_port);
                return true;
            }
        }
    }
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x542280
void IPXManagerClass::FUN_00542280(int id, IPXAddressClass* address)
{
    int index = vf_6(id);
    if (index != -1 && index < ConnectionCount) {
        Connection[index]->Address = *address;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5422C0
int IPXManagerClass::FUN_005422C0()
{
    return FailedId;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x542430
void IPXManagerClass::FUN_00542430(unsigned short port)
{
    unknown_22 = (unsigned short)((port >> 8) | (port << 8));
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5424C0
unsigned long IPXManagerClass::FUN_005424C0()
{
    if (GlobalChannel) {
        return GlobalChannel->Queue->FUN_0048BA80();
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5424E0
unsigned long IPXManagerClass::FUN_005424E0()
{
    if (RouterChannel) {
        return RouterChannel->Queue->FUN_0048BA80();
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x542500
unsigned long IPXManagerClass::FUN_00542500()
{
    if (MulticastChannel) {
        return MulticastChannel->Queue->FUN_0048BA80();
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x542F30
// The packet bytes of the oldest unacknowledged send across the connections.
char* IPXManagerClass::FUN_00542F30()
{
    unsigned int oldest = 0xFFFFFFFF;
    char* result = 0;
    for (int i = 0; i < ConnectionCount; ++i) {
        CommSendEntry* entry = 0;
        for (int j = 0; j < Connection[i]->Queue->unknown_28; ++j) {
            entry = Connection[i]->Queue->FUN_0048B720(j);
            if (entry) {
                if (!entry->unknown_14[2] && !(entry->Flags & 2)) {
                    break;
                }
                entry = 0;
            }
        }
        if (entry && entry->unknown_04 < oldest) {
            oldest = entry->unknown_04;
            result = entry->unknown_14;
        }
    }
    return result;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x543050
void IPXManagerClass::FUN_00543050(IPXAddressClass* address)
{
    if (RouterChannel) {
        RouterChannel->Address = *address;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x543080
void IPXManagerClass::FUN_00543080()
{
    if (GlobalChannel) {
        GlobalChannel->unknown_C8 = 0;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x543090
void IPXManagerClass::FUN_00543090()
{
    if (GlobalChannel) {
        GlobalChannel->unknown_C8 = 1;
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5430A0
void IPXManagerClass::FUN_005430A0(IPXAddressClass* address, unsigned short port)
{
    if (GlobalChannel) {
        GlobalChannel->vf_16(address, port);
    }
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5430C0
void IPXManagerClass::FUN_005430C0(unsigned int age)
{
    if (GlobalChannel) {
        GlobalChannel->vf_17(age);
    }
}
