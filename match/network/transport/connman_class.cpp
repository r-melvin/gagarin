// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob1
#include <string.h>
#include "connman_class.h"
#include "winsock_interface_class.h"

extern "C" int __cdecl FUN_007C8D20(const char* a, const char* b);   // CRT _strcmpi

// GLOBAL: GAMEMD 0xA8B550 -- shared packet scheduling lead limit.
extern int MaxAhead;

// External game objects reached by Service (other owners; declared only). The
// session (0xA8B238), id registry (0xB052D0), player table (0xA8DA78/0xA8DA84),
// packet interface (0x887628), flag 0xA8DBA0 and the address/port globals at
// 0xA8DBA4 / 0xA8DBBC are declared once in conn_types.h.
// GLOBAL: GAMEMD 0xA8E2C8, 0xA8D60E, 0xA8E2D0 -- byte flags.
// GLOBAL: GAMEMD 0xA8E2C8
extern bool Flag_00A8E2C8;
// GLOBAL: GAMEMD 0xA8D60E
extern bool Flag_00A8D60E;
// GLOBAL: GAMEMD 0xA8E2D0
extern bool Flag_00A8E2D0;
// GLOBAL: GAMEMD 0xA8E7AC (int flag), 0xA8ED84 (frame counter), 0xA80238 (house count).
// GLOBAL: GAMEMD 0xA8E7AC
extern int Flag_00A8E7AC;
// GLOBAL: GAMEMD 0xA8ED84
extern int Frame_00A8ED84;
// GLOBAL: GAMEMD 0xA80238
extern int HouseCount_00A80238;
// GLOBAL: GAMEMD 0xA8DA90 -- eight slot player pointers.
extern NetPlayerClass* SlotPlayers_00A8DA90[8];
// GLOBAL: GAMEMD 0xA8E2B2 -- per-player port words.
extern unsigned short Ports_00A8E2B2[];
// GLOBAL: GAMEMD 0xA8BB1C -- last router address copy (0xA8DBA4 / 0xA8DBBC: conn_types.h).
extern IPXAddressClass Address_00A8BB1C;

// External helper at 0x7350C0 (not an assigned entry): narrow a UTF-16 name into a
// static ring buffer; ECX = source: __fastcall with one register argument.
// Retail literals referenced by this translation unit.
// STRING: GAMEMD 0x828398
// STRING: GAMEMD 0x8283A8
// STRING: GAMEMD 0x828488
// STRING: GAMEMD 0x8284AC
// STRING: GAMEMD 0x8284CC
// STRING: GAMEMD 0x8284F8
// STRING: GAMEMD 0x828524
// STRING: GAMEMD 0x828540
// STRING: GAMEMD 0x82855C
// STRING: GAMEMD 0x828598
// STRING: GAMEMD 0x8285D8
// STRING: GAMEMD 0x828610
// STRING: GAMEMD 0x828648
// STRING: GAMEMD 0x828684
// STRING: GAMEMD 0x8286AC
// STRING: GAMEMD 0x8286DC

// FUNCTION: GAMEMD 0x7350C0 (decl; reloc)
extern const char* __fastcall NarrowName_007350C0(const unsigned short* name);

// One row of the per-connection statistics table at 0xA8B574 (stride 0x68).
struct ConnStat
{
    char            Name[0x40];     // +0x00 name-output view; capacity modeled
    int             PeakMs;         // +0x40
    int             unknown_44;     // +0x44
    int             unknown_48;     // +0x48
    int             unknown_4C;     // +0x4C
    int             AvgMs;          // +0x50
    char            unknown_54[0x5C - 0x54];
    IPXAddressClass Address;        // +0x5C
};
GG_STATIC_ASSERT(offsetof(ConnStat, Name) == 0x00);
GG_STATIC_ASSERT(offsetof(ConnStat, PeakMs)  == 0x40);
GG_STATIC_ASSERT(offsetof(ConnStat, unknown_44) == 0x44);
GG_STATIC_ASSERT(offsetof(ConnStat, unknown_48) == 0x48);
GG_STATIC_ASSERT(offsetof(ConnStat, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(ConnStat, AvgMs)   == 0x50);
GG_STATIC_ASSERT(offsetof(ConnStat, Address) == 0x5C);
GG_STATIC_ASSERT(sizeof(ConnStat)            == 0x68);

// GLOBAL: GAMEMD 0xA8B574 -- per-connection statistics rows.
extern ConnStat ConnStats_00A8B574[];
// GLOBAL: GAMEMD 0xA8022C -- table of per-player objects indexed by connection id.
extern void** PlayerTable_00A8022C;
// GLOBAL: GAMEMD 0xA83D4C -- one distinguished entry skipped by the statistics pass.
extern void* PlayerSkipped_00A83D4C;

// External helper at 0x735090 (not an assigned entry): narrow a UTF-16 string.
// Register-argument convention (ECX = dest, EDX = src, one stack word,
// callee pops): __fastcall.
// FUNCTION: GAMEMD 0x735090 (decl; reloc)
extern void __fastcall WideToNarrow_00735090(char* dest, const unsigned short* src, int max);

// FUNCTION: GAMEMD 0x540C60
void IPXManagerClass::SetTiming(int retrydelta, int maxretries, int timeout, bool setglobal)
{
    this->RetryDelta = retrydelta;
    this->MaxRetries = maxretries;
    this->Timeout    = timeout;

    FUN_004068E0("IPX Manager: RetryDelta = %d\n", retrydelta);
    FUN_004068E0("MaxAhead is %d\n", MaxAhead);

    if (setglobal) {
        this->vf_14(this->RetryDelta, this->MaxRetries, this->Timeout);
    }

    for (int i = 0; i < this->ConnectionCount; ++i) {
        this->Connection[i]->RetryDelta = this->RetryDelta;
        this->Connection[i]->MaxRetries = this->MaxRetries;
        this->Connection[i]->Timeout    = this->Timeout;
    }

    if (this->MulticastChannel != 0) {
        this->MulticastChannel->RetryDelta = this->RetryDelta;
        this->MulticastChannel->MaxRetries = this->MaxRetries;
        this->MulticastChannel->Timeout    = this->Timeout;
    }
}

// FUNCTION: GAMEMD 0x540D10
void IPXManagerClass::vf_14(int retrydelta, int maxretries, int timeout)
{
    if (GlobalChannel != 0) {
        GlobalChannel->RetryDelta = retrydelta;
        GlobalChannel->MaxRetries = maxretries;
        GlobalChannel->Timeout    = timeout;
    }
}

// FUNCTION: GAMEMD 0x540D40
void IPXManagerClass::SaveGlobalTiming()
{
    if (GlobalChannel != 0) {
        SavedRetryDelta = GlobalChannel->RetryDelta;
        SavedMaxRetries = GlobalChannel->MaxRetries;
        SavedTimeout    = GlobalChannel->Timeout;
    }
}

// FUNCTION: GAMEMD 0x540D60
void IPXManagerClass::RestoreGlobalTiming()
{
    if (GlobalChannel != 0) {
        GlobalChannel->RetryDelta = SavedRetryDelta;
        GlobalChannel->MaxRetries = SavedMaxRetries;
        GlobalChannel->Timeout    = SavedTimeout;
    }
}

// FUNCTION: GAMEMD 0x540D80
void IPXManagerClass::SetRouterTiming(int retrydelta, int maxretries, int timeout)
{
    if (RouterChannel != 0) {
        RouterChannel->RetryDelta = retrydelta;
        RouterChannel->MaxRetries = maxretries;
        RouterChannel->Timeout    = timeout;
    }
    if (MulticastChannel != 0) {
        MulticastChannel->RetryDelta = retrydelta;
        MulticastChannel->MaxRetries = maxretries;
        MulticastChannel->Timeout    = timeout;
    }
}

// FUNCTION: GAMEMD 0x540F90
int IPXManagerClass::vf_4()
{
    return ConnectionCount;
}

// FUNCTION: GAMEMD 0x540FA0
int IPXManagerClass::vf_5(int index)
{
    if (index >= 0 && index < ConnectionCount) {
        return Connection[index]->ID;
    }
    return -1;
}

// FUNCTION: GAMEMD 0x541040
int IPXManagerClass::vf_6(int id)
{
    for (int i = 0; i < ConnectionCount; ++i) {
        if (Connection[i]->ID == id) {
            return i;
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x541070
int IPXManagerClass::ConnectionIndexOf(ConnectionClass* conn)
{
    for (int i = 0; i < ConnectionCount; ++i) {
        if (Connection[i] == conn) {
            return i;
        }
    }
    if (conn == MulticastChannel) {
        return -4;
    }
    if (conn == RouterChannel) {
        return -3;
    }
    return (conn == GlobalChannel) ? -2 : -1;
}

// FUNCTION: GAMEMD 0x5414C0
int IPXManagerClass::vf_2(void* buf, int buflen, int needsAck, int id)
{
    if (unknown_04 && Active && ConnectionCount) {
        if (id == -1) {
            if (Session_00A8B238.GameMode == 4 && Flag_00A8DBA0) {
                CommBufferClass* queue = MulticastChannel->Queue;
                if (queue->unknown_28 < queue->unknown_04) {
                    return MulticastChannel->vf_2(buf, buflen, needsAck, 0xff);
                }
            } else {
                int i;
                for (i = 0; i < ConnectionCount; ++i) {
                    CommBufferClass* queue = Connection[i]->Queue;
                    if (queue->unknown_28 == queue->unknown_04) {
                        ++unknown_A0;
                        return 0;
                    }
                }
                for (i = 0; i < ConnectionCount; ++i) {
                    Connection[i]->vf_2(buf, buflen, needsAck, 0);
                }
                return 1;
            }
        } else {
            int index = vf_6(id);
            if (index != -1) {
                ConnectionClass* conn = Connection[index];
                CommBufferClass* queue = conn->Queue;
                if (queue->unknown_28 != queue->unknown_04) {
                    conn->vf_2(buf, buflen, needsAck, 0);
                    return 1;
                }
            }
        }
        ++unknown_A0;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x5415F0
int IPXManagerClass::vf_3(void* buf, int* buflen, int* id)
{
    if (unknown_04 && Active && ConnectionCount != 0) {
        if (CurConnection >= ConnectionCount) {
            CurConnection = 0;
        }
        for (int i = 0; i < ConnectionCount; ++i) {
            int received = Connection[CurConnection]->vf_4(buf, buflen);
            int connid = Connection[CurConnection]->ID;
            if (++CurConnection >= ConnectionCount) {
                CurConnection = 0;
            }
            if (received) {
                *id = connid;
                return 1;
            }
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x541820
// PARTIAL, 3.6% by position (28/783) but structurally closer than the previous 6.0%:
// retail calls CRT _strcmpi (0x7C8D20) for the two name compares, not an inlined strcmp
// (previous source used strcmp, which also had the wrong case sensitivity); with the call
// the frame is the retail 0x4B8 (was 0x4BC), the instruction count falls 814 -> 783 against
// retail 760, and the `ok = 1` initialiser now precedes the IPXAddressClass constructor as
// in retail. The positional score drops only because the earlier alignment was accidental.
// Residual: retail does not rotate the packet loop (bottom is `test ebx,ebx; jz exit;
// jmp top`, top reloads [0x887628]); cl here duplicates the GetPacket head at the loop
// bottom (one extra call and its argument setup, ~23 instructions) and, in the for(;;)
// spelling, also hoists a zero register (EDI) over the whole function, which retail only
// creates (EBP) for the tail. Tried: for(;;) with `next_packet: if (size == 0) break;`.
int IPXManagerClass::Service()
{
    IPXPacket packet;
    char from[0x80];
    char name[0x16];
    int fromlen;
    int buflen;
    int ok = 1;
    unsigned int size;
    IPXAddressClass addr;
    unsigned short port;
    int i;
    int j;

    if (Interface_00887628) {
        do {
            buflen = 0x400;
            fromlen = 0x80;
            port = 0;
            size = Interface_00887628->GetPacket(&packet, &buflen, &from, (unsigned int*)&fromlen, &port);
            if (size == 0) {
                break;
            }
            addr = *(IPXAddressClass*)from;
            CurrentPacket = &packet;

            if (packet.Magic == GlobalChannel->unknown_24) {
                if (FUN_00541680(&packet, &packet, size, &from, port)) {
                    continue;
                }
                if (!GlobalChannel->vf_12((ConnPacketHeader*)&packet, size, &addr, port)) {
                    FUN_004068E0("GlobalChannel recive buffer overflow %d\n", ++unknown_A4);
                    break;
                }
                if (Session_00A8B238.GameMode != 4 || !Flag_00A8E2C8) {
                    continue;
                }
                for (i = 0; i < PlayerCount_00A8DA84; ++i) {
                    if (Players_00A8DA78[i]->Address.FUN_0053EF30(&addr) && Ports_00A8E2B2[i] == port) {
                        goto next_packet;
                    }
                }
                if (PlayerCount_00A8DA84 == 0) {
                    continue;
                }
                FUN_004068E0("NAT Alert - port number fiddling detected!\n");
                if (size < 0x10 || packet.Code == 2 || size < 0x3f) {
                    continue;
                }
                if (CurrentPacket->Type != 0x27 && CurrentPacket->Type != 0x29 && CurrentPacket->Type != 0xd) {
                    continue;
                }
                memset(name, 0, sizeof(name));
                strncpy(name, CurrentPacket->Name, 0x14);
                for (i = 0; i < PlayerCount_00A8DA84; ++i) {
                    if (FUN_007C8D20(NarrowName_007350C0(Players_00A8DA78[i]->Name), name) == 0) {
                        goto found_player;
                    }
                }
                continue;
            found_player:
                if (Players_00A8DA78[i]->Address.FUN_0053EF30(&addr) && Players_00A8DA78[i]->Address.Port == port) {
                    continue;
                }
                {
                    unsigned short oldport = Ports_00A8E2B2[i];
                    FUN_004068E0("Player %s is having his port translated to %d\n", name, port);
                    Ports_00A8E2B2[i] = port;
                    IdMap_00B052D0.FUN_00664400(Players_00A8DA78[i]->Id, port);
                    GlobalChannel->vf_16(&addr, oldport);
                    GlobalChannel->vf_16(&addr, Players_00A8DA78[i]->Address.Port);
                    Players_00A8DA78[i]->Address = addr;
                    Players_00A8DA78[i]->Address.FUN_0053F200(port);
                    IdMap_00B052D0.FUN_00664240(Players_00A8DA78[i]->Id, &Players_00A8DA78[i]->Address);
                    SlotPlayers_00A8DA90[Session_00A8B238.FUN_0069BC60(i)]->Address = addr;
                    SlotPlayers_00A8DA90[Session_00A8B238.FUN_0069BC60(i)]->Address.FUN_0053F200(port);
                }
                for (j = 0; j < ConnectionCount; ++j) {
                    if (FUN_007C8D20(NarrowName_007350C0(Connection[j]->Name), name) == 0) {
                        Connection[j]->Address = addr;
                        Connection[j]->Address.FUN_0053F200(port);
                        FUN_004068E0("Set address for connection %d to %s\n", j, Connection[j]->Address.FUN_0053F0E0(0));
                        break;
                    }
                }
                if (Flag_00A8D60E || ConnectionCount == 0) {
                    continue;
                }
                if (HouseCount_00A80238 <= Players_00A8DA78[i]->Id) {
                    continue;
                }
                if (!Session_00A8B238.FUN_00697E70(PlayerTable_00A8022C[Players_00A8DA78[i]->Id])) {
                    continue;
                }
                FUN_004068E0("Frame %d, Router apparently changed address from %s to %s\n",
                             Frame_00A8ED84, MulticastChannel->Address.FUN_0053F0E0(0), addr.FUN_0053F0E0(0));
                MulticastChannel->Address = addr;
                MulticastChannel->Address.FUN_0053F200(port);
                Address_00A8BB1C = addr;
                Address_00A8BB1C.FUN_0053F200(port);
                Address_00A8DBA4 = addr;
                Address_00A8DBA4.FUN_0053F200(port);
                *(unsigned short*)&Port_00A8DBBC = port;
            } else if (packet.Magic == RouterChannel->unknown_24) {
                if (!Flag_00A8DBA0) {
                    continue;
                }
                if (!RouterChannel->vf_12((ConnPacketHeader*)&packet, size, &addr, 0)) {
                    FUN_004068E0("RouterChannel recive buffer overflow %d\n", ++unknown_A4);
                    break;
                }
            } else if (packet.Magic == unknown_20) {
                if (FUN_00541680(&packet, &packet, size, &from, port)) {
                    continue;
                }
                if (Flag_00A8DBA0 && packet.Flag == 0xff) {
                    if (packet.Code == 2) {
                        MulticastChannel->Receive_Packet((ConnPacketHeader*)&packet, size);
                    } else if (ConnectionCount > 0) {
                        switch (packet.Code) {
                        case 0:
                            FUN_004068E0("Adding DATA_ACK packet %d from %s ; %d to multicast queue\n",
                                         packet.Id, addr.FUN_0053F0E0(0), port);
                            break;
                        case 1:
                            FUN_004068E0("Adding DATA_NOACK packet %d from %s ; %d to multicast queue\n",
                                         packet.Id, addr.FUN_0053F0E0(0), port);
                            break;
                        case 2:
                            FUN_004068E0("Adding ACK packet %d from %s ; %d to multicast queue\n",
                                         packet.Id, addr.FUN_0053F0E0(0), port);
                            break;
                        default:
                            FUN_004068E0("Adding ??? packet %d from %s ; %d to multicast queue\n",
                                         packet.Id, addr.FUN_0053F0E0(0), port);
                            break;
                        }
                        if (!Connection[0]->Receive_Packet((ConnPacketHeader*)&packet, size)) {
                            size = 0;
                            FUN_004068E0("Receive buffer overflow %d\n", ++unknown_A4);
                        }
                    }
                } else {
                    for (j = 0; j < ConnectionCount; ++j) {
                        if (Flag_00A8DBA0 && IdMap_00B052D0.FUN_00663D60(Connection[j]->ID) == packet.Flag) {
                            goto found_connection;
                        }
                        if (!Flag_00A8DBA0 && Connection[j]->Address.FUN_0053EE70(&addr)) {
                            goto found_connection;
                        }
                    }
                    if (Session_00A8B238.GameMode == 4 && !Flag_00A8E7AC && Frame_00A8ED84 > 8
                        && !Flag_00A8DBA0 && size > 0xf && packet.Code == 1 && packet.Kind == 0x19) {
                        int id = (signed char)packet.Type;
                        for (i = 1; i < PlayerCount_00A8DA84; ++i) {
                            if (Players_00A8DA78[i]->Id == id) {
                                Players_00A8DA78[i]->Address = addr;
                                if (vf_6(id) != -1) {
                                    Connection[vf_6(id)]->Address = addr;
                                }
                                break;
                            }
                        }
                    }
                    continue;
                found_connection:
                    if (!Connection[j]->Receive_Packet((ConnPacketHeader*)&packet, size)) {
                        size = 0;
                        FUN_004068E0("Reecive buffer overflow %d\n", ++unknown_A4);
                    }
                }
                if (Session_00A8B238.GameMode == 4 && Flag_00A8DBA0 && addr.FUN_0053EF60(&MulticastChannel->Address)) {
                    for (i = 1; i < PlayerCount_00A8DA84; ++i) {
                        if (Players_00A8DA78[i]->Address.FUN_0053EF30(&MulticastChannel->Address)
                            && Session_00A8B238.FUN_00697E70(PlayerTable_00A8022C[Players_00A8DA78[i]->Id])) {
                            FUN_004068E0("Frame %d, Router apparently changed address from %s to %s\n",
                                         Frame_00A8ED84, MulticastChannel->Address.FUN_0053F0E0(0), addr.FUN_0053F0E0(0));
                            Players_00A8DA78[i]->Address = addr;
                            MulticastChannel->Address = addr;
                            Address_00A8BB1C = addr;
                            Address_00A8DBA4 = addr;
                            IdMap_00B052D0.FUN_00664240(Players_00A8DA78[i]->Id, &addr);
                        }
                    }
                }
            }
        next_packet:;
        } while (size != 0);
    }

    if (GlobalChannel && Interface_00887628) {
        if (!GlobalChannel->Service()) {
            GlobalChannel->vf_6();
            ok = 0;
        }
    }
    if (Flag_00A8DBA0) {
        if (RouterChannel) {
            if (!RouterChannel->Service()) {
                RouterChannel->vf_6();
                ok = 0;
            }
            if (!Flag_00A8E2D0) {
                IdMap_00B052D0.FUN_006640E0();
            }
        }
    }
    if (Flag_00A8DBA0) {
        if (MulticastChannel) {
            if (!MulticastChannel->Service()) {
                FUN_004068E0("Multicast channel has gone bad\n");
                ok = 0;
            }
        }
    }
    if (Interface_00887628 && ConnectionCount > 0) {
        for (i = 0; i < ConnectionCount; ++i) {
            if (!Connection[i]->Service()) {
                ok = 0;
                FailedId = Connection[i]->ID;
                FUN_004068E0("Error - Connection %d has gone bad\n", FailedId);
            }
        }
    }
    if (ok) {
        FailedId = -1;
    }
    return ok;
}

// FUNCTION: GAMEMD 0x5422D0
int IPXManagerClass::vf_7()
{
    if (unknown_04 && Active) {
        return GlobalChannel->Queue->unknown_28;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x5422F0
int IPXManagerClass::vf_8()
{
    if (unknown_04 && Active) {
        return GlobalChannel->Queue->unknown_38;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x542310
int IPXManagerClass::vf_20()
{
    if (unknown_04 && Active && RouterChannel) {
        return RouterChannel->Queue->unknown_28;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x542330
int IPXManagerClass::vf_21()
{
    if (unknown_04 && Active && RouterChannel) {
        return RouterChannel->Queue->unknown_38;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x542350
int IPXManagerClass::vf_9(int id)
{
    if (unknown_04 && Active && ConnectionCount) {
        if (id != -1) {
            int index = vf_6(id);
            if (index != -1) {
                return Connection[index]->Queue->unknown_28;
            }
        } else {
            int most = 0;
            for (int i = 0; i < ConnectionCount; ++i) {
                int n = Connection[i]->Queue->unknown_28;
                if (n > most) {
                    most = n;
                }
            }
            return most;
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x5423C0
int IPXManagerClass::vf_10(int id)
{
    if (unknown_04 && Active && ConnectionCount) {
        if (id != -1) {
            int index = vf_6(id);
            if (index != -1) {
                return Connection[index]->Queue->unknown_38;
            }
        } else {
            int most = 0;
            for (int i = 0; i < ConnectionCount; ++i) {
                int n = Connection[i]->Queue->unknown_38;
                if (n > most) {
                    most = n;
                }
            }
            return most;
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x542450
int IPXManagerClass::ResponseTime()
{
    unsigned int maxv = 0;

    for (int i = 0; i < this->ConnectionCount; ++i) {
        unsigned int v = this->Connection[i]->Queue->FUN_0048BA80();
        if (v > maxv) {
            maxv = v;
        }
    }

    unsigned int result;
    if (this->MulticastChannel == 0 ||
        (result = this->MulticastChannel->Queue->FUN_0048BA80()) <= maxv) {
        result = maxv;
    }
    return (int)result;
}

// FUNCTION: GAMEMD 0x5424A0
int IPXManagerClass::ResponseTimeOf(int index)
{
    return Connection[index]->Queue->FUN_0048BA80();
}

// FUNCTION: GAMEMD 0x542520
void IPXManagerClass::UpdateStats()
{
    for (int i = 0; i < ConnectionCount; ++i) {
        void* player = PlayerTable_00A8022C[Connection[i]->ID];
        if (player != 0 && player != PlayerSkipped_00A83D4C) {
            ConnStat* stat = &ConnStats_00A8B574[i];
            if (stat->Name[0] == 0) {
                WideToNarrow_00735090(stat->Name, Connection[i]->Name, -1);
                stat->Address = Connection[i]->Address;
            }
            int peak = (Connection[i]->Queue->FUN_0048BA90() * 1000) / 60;
            stat->PeakMs = (stat->PeakMs > peak) ? stat->PeakMs : peak;
            int avg = (Connection[i]->Queue->FUN_0048BA80() * 1000) / 60;
            stat->AvgMs = (avg > stat->AvgMs) ? avg : stat->AvgMs;
            stat->unknown_44 = Connection[i]->unknown_08;
            stat->unknown_48 = Connection[i]->unknown_0C;
            stat->unknown_4C = Connection[i]->unknown_10;
        }
    }
}

// FUNCTION: GAMEMD 0x542EC0
void IPXManagerClass::vf_11(bool a1)
{
    for (int i = 0; i < ConnectionCount; ++i) {
        Connection[i]->Queue->FUN_0048BAA0(a1);
    }
    if (GlobalChannel) {
        GlobalChannel->Queue->FUN_0048BAA0(true);
    }
    if (RouterChannel) {
        RouterChannel->Queue->FUN_0048BAA0(true);
    }
    if (MulticastChannel) {
        MulticastChannel->Queue->FUN_0048BAA0(true);
    }
}

// FUNCTION: GAMEMD 0x542FE0
void IPXManagerClass::vf_15(int index, int a2, int a3, int a4, int a5, int a6)
{
    if (index == -1) {
        GlobalChannel->Queue->FUN_0048BAD0(a2, a3, a4, a5, a6);
    } else if (Connection[index] != 0) {
        Connection[index]->Queue->FUN_0048BAD0(a2, a3, a4, a5, a6);
    }
}

// FUNCTION: GAMEMD 0x543040
void IPXManagerClass::Slot24(int, int)
{
}
