// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob1
#include <string.h>
#include "conn_types.h"
#include "winsock_interface_class.h"

// VTABLE: GAMEMD 0x7EC10C  IPXGlobalConnClass (18 slots)

// Retail literals referenced by this translation unit.
// STRING: GAMEMD 0x8281D4
// STRING: GAMEMD 0x8281F4
// STRING: GAMEMD 0x82821C
// STRING: GAMEMD 0x82824C
// STRING: GAMEMD 0x828270
// STRING: GAMEMD 0x8282A0
// STRING: GAMEMD 0x8282D4
// STRING: GAMEMD 0x8282E8
// STRING: GAMEMD 0x8282F0

// FUNCTION: GAMEMD 0x53FA90
IPXGlobalConnClass::IPXGlobalConnClass(int sendSlots, int receiveSlots, int maxlen,
                                       unsigned short unknown_b8,
                                       unsigned short magic)
    : IPXConnClass(sendSlots, receiveSlots, maxlen + 2, magic, 0, 0,
                   EmptyName_00887734, 0xC)
{
    unknown_B8 = unknown_b8;
    unknown_C4 = 0;
    unknown_C8 = true;
    unknown_D4 = receiveSlots;
    Ids = new int[receiveSlots];
    Addresses = new IPXAddressClass[unknown_D4];
    for (int i = 0; i < unknown_D4; i++) {
        Ids[i] = -1;
    }
    unknown_D8 = 0;
}

// FUNCTION: GAMEMD 0x53FBD0
int IPXGlobalConnClass::vf_11(void* buf, int buflen,
                                       IPXAddressClass* address, int needsAck,
                                       int unknown_5, int packet_id)
{
    IPXAddressClass local;
    GlobalHeader()->unknown_08 = 0;
    GlobalHeader()->unknown_0C = 0;
    GlobalHeader()->unknown_00 = unknown_24;
    if (needsAck && address) {
        GlobalHeader()->Code = 0;
    } else {
        GlobalHeader()->Code = 1;
    }
    GlobalHeader()->unknown_04 = Queue->unknown_2C;
    if (packet_id) {
        GlobalHeader()->unknown_04 = packet_id;
    }
    GlobalHeader()->unknown_0E = unknown_B8;
    GlobalHeader()->unknown_03 = 0;
    if (address) {
        local = *address;
    }
    memcpy((char*)unknown_20 + 0x10, buf, buflen);
    return Queue->FUN_0048B410(unknown_20, buflen + 0x10, &local, 0xC, unknown_5);
}

// FUNCTION: GAMEMD 0x53FCB0
// CAP: multiset delta retail-only {je}, compiled-only {pop x2, jne}; retail defers the
// EBX/EDI pushes past the magic test (we push all four up front). Variants: early
// return vs if-wrapped switch, case-scope braces.
int IPXGlobalConnClass::vf_12(ConnPacketHeader* packet, int buflen,
                                            IPXAddressClass* address,
                                            unsigned short port)
{
    if (packet->unknown_00 != unknown_24) {
        return 0;
    }
    switch (packet->Code) {
    case 2: {
        for (int j = 0; j < Queue->unknown_28; j++) {
            CommSendEntry* entry = Queue->FUN_0048B720(j);
            if (packet->unknown_04 == ((ConnPacketHeader*)entry->unknown_14)->unknown_04
                && ((ConnPacketHeader*)entry->unknown_14)->Code == 0) {
                entry->Flags |= 2;
                return 1;
            }
        }
        return 1;
    }
    case 1: {
        IPXAddressClass local = *address;
        if (port) {
            local.FUN_0053F200(port);
        }
        Queue->FUN_0048B750(packet, buflen, &local, 0xC);
        return 1;
    }
    case 0: {
        IPXAddressClass local = *address;
        if (port) {
            local.FUN_0053F200(port);
        }
        int i;
        for (i = 0; i < unknown_D4; i++) {
            if (i >= Queue->unknown_3C) {
                break;
            }
            if (local.Equals_EE70(Addresses[i]) && packet->unknown_04 == Ids[i]) {
                goto ack;
            }
        }
        if (!Queue->FUN_0048B750(packet, buflen, &local, 0xC)) {
            FUN_004068E0("Failed to queue incoming packet. Ack not sent\n");
            return 1;
        }
        Addresses[unknown_D8] = local;
        Ids[unknown_D8] = packet->unknown_04;
        unknown_D8++;
        if (unknown_D8 >= unknown_D4) {
            unknown_D8 = 0;
        }
    ack:
        ConnGlobalPacketHeader ack;
        ack.unknown_00 = unknown_24;
        ack.Code = 2;
        ack.unknown_04 = packet->unknown_04;
        FUN_004068E0("Sending global ack packet to port %d\n", port);
        ack.unknown_0E = unknown_B8;
        ack.unknown_03 = 0;
        if (!vf_9(&ack, 0x10, address, 0xC, this == GlobalConnection_00A8EA0C, port)) {
            FUN_004068E0("Failed to ack global packet\n");
        }
        return 1;
    }
    }
    return 1;
}

// FUNCTION: GAMEMD 0x53FF10
int IPXGlobalConnClass::vf_13(void* buf, int* buflen,
                                        IPXAddressClass* address,
                                        unsigned short* port)
{
    if (Queue->unknown_38) {
        CommReceiveEntry* entry = Queue->FUN_0048B9E0(0);
        if (entry && !(entry->Flags & 2)) {
            entry->Flags |= 2;
            int len = entry->unknown_08 - 0x10;
            char* data = entry->unknown_0C;
            if (len > 0) {
                memcpy(buf, data + 0x10, len);
            }
            *buflen = len;
            *port = ((ConnGlobalPacketHeader*)data)->unknown_0E;
            *address = *(IPXAddressClass*)entry->unknown_14;
            return 1;
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x53FFA0
int IPXGlobalConnClass::vf_14(int index, void* buf, int* buflen,
                                      IPXAddressClass* address,
                                      unsigned short* port,
                                      unsigned long* packet_id)
{
    if (Queue->unknown_38 >= index) {
        CommReceiveEntry* entry = Queue->FUN_0048B9E0(index);
        if (entry && !(entry->Flags & 2)) {
            char* data = entry->unknown_0C;
            int len = entry->unknown_08 - 0x10;
            if (len > 0) {
                memcpy(buf, data + 0x10, len);
            }
            *buflen = len;
            *port = ((ConnGlobalPacketHeader*)data)->unknown_0E;
            *address = *(IPXAddressClass*)entry->unknown_14;
            if (packet_id) {
                *packet_id = ((ConnGlobalPacketHeader*)data)->unknown_04;
            }
            return 1;
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x540030
void IPXGlobalConnClass::vf_15(int index)
{
    if (index < Queue->unknown_38) {
        Queue->FUN_0048B9E0(index)->Flags |= 2;
    }
}

// FUNCTION: GAMEMD 0x540050
// CAP 36.2%: multiset delta retail-only {lea [esi+0xba]} (dead address-of); register/
// layout order differs. Variants: single-call if/else, early returns, &unknown_BA local.
int IPXGlobalConnClass::vf_9(void* buf, int buflen, void* extra, int extraLength,
                                bool is_global, unsigned short unknown_6)
{
    if (((IPXAddressClass*)extra)->IsBroadcast()) {
        return FUN_0053F830(buf, buflen);
    }
    if (Session_00A8B238.GameMode == 3 && unknown_C4
        && *(unsigned long*)extra == unknown_BA) {
        return vf_10(buf, buflen, (IPXAddressClass*)extra,
                               &unknown_BE, is_global, 0);
    } else {
        return vf_10(buf, buflen, (IPXAddressClass*)extra, 0,
                               is_global, unknown_6);
    }
}

// FUNCTION: GAMEMD 0x5400D0
int IPXGlobalConnClass::vf_8()
{
    for (int i = 0; i < Queue->unknown_38; i++) {
        if (Queue->FUN_0048B9E0(i)->Flags & 2) {
            Queue->FUN_0048B890(0, 0, i, 0, 0);
            i--;
        }
    }
    return 1;
}

// FUNCTION: GAMEMD 0x540110
// CAP 98.5%: multiset identical; two loads (entry->unknown_04 / age) swap order in the
// age compare. Variants: operand order, int casts, reversed compare.
void IPXGlobalConnClass::vf_17(unsigned int age)
{
    FUN_004068E0("Stripping queue entries older than %d seconds. Num receive = %d\n",
                 age / 60, Queue->unknown_38);
    for (int i = 0; i < Queue->unknown_38; i++) {
        CommReceiveEntry* entry = Queue->FUN_0048B9E0(i);
        FUN_004068E0("i = %d\n", i);
        if (entry) {
            FUN_004068E0("Checking packet %d\n", i);
            int now = ConnTimer.GetValue();
            if ((int)entry->unknown_04 + (int)age < now) {
                FUN_004068E0("Stripping global packet due to age of %d seconds\n",
                             (int)(ConnTimer.GetValue() - entry->unknown_04) / 60);
                int id = ((ConnPacketHeader*)entry->unknown_0C)->unknown_04;
                for (int j = 0; j < unknown_D4; j++) {
                    if (Ids[j] == id) {
                        Ids[j] = -1;
                        break;
                    }
                }
                Queue->FUN_0048B890(0, 0, i, 0, 0);
                i--;
            } else {
                FUN_004068E0("Leaving global packet due to age of %d seconds\n",
                             (int)(ConnTimer.GetValue() - entry->unknown_04) / 60);
            }
        }
    }
    FUN_004068E0("Done stripping. Num receive = %d\n", Queue->unknown_38);
}

// FUNCTION: GAMEMD 0x5402D0
int IPXGlobalConnClass::vf_6()
{
    char buf[0x400];
    int count = 0;
    for (int i = 0; i < Queue->unknown_28; i++) {
        unsigned int flags = Queue->FUN_0048B720(i)->Flags;
        if ((flags & 4) && !(flags & 2)) {
            IPXAddressClass address;
            int len;
            int addrlen = 0xC;
            Queue->FUN_0048B570(buf, &len, i, &address, &addrlen, 0);
            i--;
            count++;
        }
    }
    return count;
}

// FUNCTION: GAMEMD 0x540340
int IPXGlobalConnClass::vf_16(IPXAddressClass* address,
                                            unsigned short port)
{
    char buf[0x400];
    int count = 0;
    for (int i = 0; i < Queue->unknown_28; i++) {
        CommSendEntry* entry = Queue->FUN_0048B720(i);
        if (!(entry->Flags & 2) && entry->unknown_18
            && ((IPXAddressClass*)entry->unknown_1C)->Equals_EF30(*address)
            && entry->unknown_20 == port) {
            IPXAddressClass removed;
            int len;
            int addrlen = 0xC;
            Queue->FUN_0048B570(buf, &len, i, &removed, &addrlen, 0);
            i--;
            count++;
        }
    }
    return count;
}

// FUNCTION: GAMEMD 0x5403F0
// PARTIAL 1.3% positional (was 0.0%; section 0x1F0 against retail 0x213). The network
// override and the player lookup share one net/node pair, as retail's single 8-byte pair
// (frame 0x28) does. Prologue differs: ours keeps a zero in EBX, retail uses TEST. Retail
// clears the header dword at hdr+8 through a separate LEA (the shape of an intrinsic 4-byte
// memset); not reproduced until the field's type has independent evidence.
int IPXGlobalConnClass::vf_10(void* buf, int buflen,
                                        IPXAddressClass* address,
                                        unsigned long* network, bool is_global,
                                        unsigned short unknown_6)
{
    IPXAddressClass local;
    NetworkNumberType net;
    NodeAddressType node;
    local = *address;
    if (network) {
        address->FUN_0053EDA0(net, node);
        net.Number = *network;
        local.FUN_0053ED20(net, node, 0);
    }

    unsigned short port;
    ConnPacketHeader* hdr;
    if (Session_00A8B238.GameMode == 4 && !is_global && Flag_00A8DBA0 && unknown_C8) {
        hdr = (ConnPacketHeader*)buf;
        if (hdr->unknown_03 == 0) {
            IPXAddressClass copy = local;
            copy.FUN_0053EDA0(net, node);
            copy.FUN_0053ED20(net, node, unknown_6);
            int player_id = -1;
            for (int i = 0; i < PlayerCount_00A8DA84; i++) {
                if (Players_00A8DA78[i]->Address.Equals_EE70(copy)) {
                    player_id = Players_00A8DA78[i]->Id;
                    break;
                }
            }
            unsigned char id = IdMap_00B052D0.FUN_00663D60(player_id);
            if (!id) {
                id = 1;
            }
            hdr->unknown_03 = id;
        }
        local = Address_00A8DBA4;
        port = Port_00841F3C;
        if (Address_00A8DBB0.Equals_EE70(Players_00A8DA78[0]->Address)
            && local.Equals_EF30(Players_00A8DA78[0]->Address)) {
            hdr->unknown_0C = 0;
            hdr->unknown_08 = 0;
        } else {
            hdr->unknown_0C = (unsigned short)Port_00841F3C;
            port = Port_00A8DBBC;
            hdr->unknown_08 = 0;
        }
    } else {
        hdr = (ConnPacketHeader*)buf;
        port = unknown_6;
        hdr->unknown_0C = 0;
        hdr->unknown_08 = 0;
    }

    if (Interface_00887628) {
        Interface_00887628->SendPacket(hdr, buflen, &local, 0xC, is_global, !unknown_C8, port);
    }
    return 1;
}

// FUNCTION: GAMEMD 0x540610
int IPXGlobalConnClass::vf_2(void* buf, int buflen, int needsAck,
                                    unsigned char extra)
{
    return ConnectionClass::vf_2(buf, buflen, needsAck, extra);
}

// FUNCTION: GAMEMD 0x540630
int IPXGlobalConnClass::Receive_Packet(ConnPacketHeader* packet, int buflen)
{
    return ConnectionClass::Receive_Packet(packet, buflen);
}

// FUNCTION: GAMEMD 0x540650
int IPXGlobalConnClass::vf_4(void* buf, int* buflen)
{
    return ConnectionClass::vf_4(buf, buflen);
}

// SYNTHETIC: GAMEMD 0x540670  IPXGlobalConnClass::`scalar deleting destructor'
