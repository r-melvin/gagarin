// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2
#include <string.h>
#include "conn_types.h"

// VTABLE: GAMEMD 0x7E51B4  ConnectionClass (10 slots, slot 9 = _purecall 0x4C9150)
// Expansion rows outside the M1 30-row table: the standalone constructor at
// 0x48BE60 and destructor at 0x48BEE0, both preserved from accepted arrangement 3.

// Retail literals referenced by this translation unit.
// STRING: GAMEMD 0x81D2C0
// STRING: GAMEMD 0x81D2D0
// STRING: GAMEMD 0x81D2E4
// STRING: GAMEMD 0x81D2F8
// STRING: GAMEMD 0x81D340
// STRING: GAMEMD 0x81D374
// STRING: GAMEMD 0x81D3B8
// STRING: GAMEMD 0x81D3FC
// STRING: GAMEMD 0x81D42C
// STRING: GAMEMD 0x81D448
// STRING: GAMEMD 0x81D490
// STRING: GAMEMD 0x81D4AC

// FUNCTION: GAMEMD 0x48BE60
ConnectionClass::ConnectionClass(int sendSlots, int receiveSlots, int maxlen,
                                 unsigned short magic, int retryDelay,
                                 int retryLimit, int timeout, int extraLength)
{
    MaxPacketLen = maxlen + 0xE;
    unknown_24 = magic;
    RetryDelta = retryDelay;
    MaxRetries = retryLimit;
    Timeout = timeout;
    unknown_20 = (ConnPacketHeader*)new char[MaxPacketLen];
    Queue = new CommBufferClass(sendSlots, receiveSlots, MaxPacketLen, extraLength);
}

// FUNCTION: GAMEMD 0x48BEE0
ConnectionClass::~ConnectionClass()
{
    delete unknown_20;
    if (Queue) {
        delete Queue;
    }
}

// FUNCTION: GAMEMD 0x48BF10
void ConnectionClass::Init()
{
    unknown_34 = 0;
    unknown_38 = 0;
    unknown_3C = 0;
    NumSendAck = 0;
    unknown_08 = 0;
    unknown_0C = 0;
    unknown_10 = 0;
    unknown_14 = 0;
    unknown_18 = 0;
    unknown_44 = -1;
    unknown_48 = -1;
    Queue->Init();
}

// FUNCTION: GAMEMD 0x48BF40
int ConnectionClass::vf_2(void* buf, int buflen, int needsAck,
                                 unsigned char extra)
{
    unknown_20->unknown_00 = unknown_24;
    if (needsAck) {
        unknown_20->Code = 0;
        unknown_20->unknown_04 = NumSendAck;
        FUN_004068E0("NumSendAck = %d\n", NumSendAck);
    } else {
        unknown_20->Code = 1;
        unknown_20->unknown_04 = unknown_3C;
    }
    if (Session_00A8B238.GameMode == 4 && Flag_00A8DBA0) {
        unknown_20->unknown_03 = extra;
    }
    if (MaxPacketLen < buflen) {
        FUN_004068E0("MaxPacketLen = %d\n", MaxPacketLen);
        FUN_004068E0("buflen = %d\n", buflen);
        return 0;
    }
    memcpy(unknown_20 + 1, buf, buflen);
    if (Queue->FUN_0048B410(unknown_20, buflen + 0xE, 0, 0, 0)) {
        if (needsAck) {
            NumSendAck++;
        } else {
            unknown_3C++;
        }
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x48C040
int ConnectionClass::Receive_Packet(ConnPacketHeader* packet, int buflen)
{
    if (packet->unknown_00 != unknown_24) {
        unknown_18++;
        return 0;
    }
    if (packet->Code == 2) {
        FUN_004068E0("Received ACK for packet %d\n", packet->unknown_04);
        for (int i = 0; i < Queue->unknown_28; i++) {
            CommSendEntry* entry = Queue->FUN_0048B720(i);
            if (entry && packet->unknown_04 == ((ConnPacketHeader*)entry->unknown_14)->unknown_04
                && ((ConnPacketHeader*)entry->unknown_14)->Code == 0) {
                entry->Flags |= 2;
                break;
            }
        }
        return 1;
    }
    if (packet->Code == 1) {
        if (Queue->unknown_08 - Queue->unknown_38 <= 1) {
            unknown_14++;
            FUN_004068E0("Error - ConnectClass::Receive_Packet Queue full on PACKET_DATA_NOACK\n");
            return 0;
        }
        if (!Queue->FUN_0048B750(packet, buflen, 0, 0)) {
            FUN_004068E0("Error - unable to queue incoming packet. %s %s\n",
                         "D:\\ra2mdpost\\Connect.CPP", 332);
            unknown_14++;
            return 0;
        }
        unknown_34++;
        unknown_0C = packet->unknown_04 - unknown_34 + 1;
        if (packet->unknown_04) {
            unknown_10 = 100 - (unknown_34 * 100) / (packet->unknown_04 + 1);
        }
        return 1;
    }
    if (packet->Code == 0) {
        if (packet->unknown_04 > unknown_44 || unknown_44 == -1) {
            for (int i = 0; i < Queue->unknown_38; i++) {
                CommReceiveEntry* entry = Queue->FUN_0048B9E0(i);
                if (entry && ((ConnPacketHeader*)entry->unknown_0C)->Code == 0
                    && ((ConnPacketHeader*)entry->unknown_0C)->unknown_04 == packet->unknown_04) {
                    goto send_ack;
                }
            }
            if (Queue->unknown_08 - Queue->unknown_38 <= 1
                && packet->unknown_04 != unknown_44 + 1) {
                FUN_004068E0("Error - ConnectClass::Receive_Packet Queue full on PACKET_DATA_ACK\n");
                return 0;
            }
            if (!Queue->FUN_0048B750(packet, buflen, 0, 0)) {
                FUN_004068E0("Error - ConnectClass::Receive_Packet Queue->Queue_Receive error\n");
                return 0;
            }
            unknown_38++;
            if (packet->unknown_04 == unknown_44 + 1) {
                unsigned long id = packet->unknown_04;
                bool again;
                do {
                    again = false;
                    unknown_44 = id;
                    int i = 0;
                    if (Queue->unknown_38 > 0) {
                        do {
                            CommReceiveEntry* entry = Queue->FUN_0048B9E0(i);
                            if (entry) {
                                ConnPacketHeader* h = (ConnPacketHeader*)entry->unknown_0C;
                                if (h->Code == 0 && h->unknown_04 == unknown_44 + 1) {
                                    id = h->unknown_04;
                                    again = true;
                                    break;
                                }
                            }
                            i++;
                        } while (i < Queue->unknown_38);
                    }
                } while (again);
            }
        }
send_ack:
        ConnPacketHeader ack;
        ack.Code = 2;
        ack.unknown_04 = packet->unknown_04;
        ack.unknown_00 = unknown_24;
        if (Flag_00A8DBA0) {
            ack.unknown_03 = packet->unknown_03;
        } else {
            ack.unknown_03 = 0;
        }
        FUN_004068E0("Sending ACK for packet %d to be forwarded to %02x\n",
                     packet->unknown_04, ack.unknown_03);
        vf_9(&ack, 0xE, 0, 0, this == GlobalConnection_00A8EA0C, 0);
        return 1;
    }
    FUN_004068E0("Error - ConnectClass::Receive_Packet did not understand packet->Code\n");
    return 0;
}

// FUNCTION: GAMEMD 0x48C320
int ConnectionClass::vf_4(void* buf, int* buflen)
{
    CommReceiveEntry* entry;
    int len;
    for (int i = 0; i < Queue->unknown_38; i++) {
        entry = Queue->FUN_0048B9E0(i);
        if (entry && !(entry->Flags & 2)) {
            ConnPacketHeader* h = (ConnPacketHeader*)entry->unknown_0C;
            if (h->Code == 0 && h->unknown_04 == unknown_48 + 1) {
                unknown_48 = h->unknown_04;
                goto found;
            }
            if (h->Code == 1) {
                goto found;
            }
        }
    }
    return 0;
found:
    entry->Flags |= 2;
    len = entry->unknown_08 - 0xE;
    if (len > 0) {
        memcpy(buf, entry->unknown_0C + 0xE, len);
    }
    *buflen = len;
    return 1;
}

// FUNCTION: GAMEMD 0x48C3B0
int ConnectionClass::Service()
{
    if (Service_Send_Queue() && vf_8()) {
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x48C3E0
int ConnectionClass::Service_Send_Queue()
{
    int failed = 0;
    int i;
    CommSendEntry* entry;

    for (i = 0; i < Queue->unknown_28; i++) {
        entry = Queue->FUN_0048B720(i);
        if (entry->Flags & 2) {
            if (((ConnPacketHeader*)entry->unknown_14)->Code == 0) {
                unsigned int now = ConnTimer.GetValue();
                Queue->FUN_0048BA10(now - entry->unknown_04);
            }
            Queue->FUN_0048B570(0, 0, i, 0, 0, 0);
            i--;
        }
    }

    int count = Queue->unknown_28;
    for (i = 0; i < count; i++) {
        entry = Queue->FUN_0048B720(i);
        if (!(entry->Flags & 2)) {
            unsigned int now = ConnTimer.GetValue();
            if (now - entry->unknown_08 > RetryDelta) {
                vf_9(entry->unknown_14, entry->unknown_10, entry->unknown_1C,
                        entry->unknown_18, this == GlobalConnection_00A8EA0C,
                        entry->unknown_20);
                entry->unknown_08 = now;
                if (entry->unknown_0C == 0) {
                    entry->unknown_04 = now;
                    if (((ConnPacketHeader*)entry->unknown_14)->Code == 1) {
                        entry->Flags |= 2;
                    }
                } else {
                    unknown_08++;
                }
                entry->unknown_0C++;
                if (MaxRetries != -1 && entry->unknown_0C > MaxRetries) {
                    entry->Flags |= 4;
                    failed = 1;
                }
                if (Timeout != -1 && entry->unknown_08 - entry->unknown_04 > Timeout) {
                    entry->Flags |= 4;
                    failed = 1;
                }
            }
        }
    }

    if (failed) {
        FUN_004068E0("ConnectionClass::Service_Send_Queue bad connection\n");
        return 0;
    }
    return 1;
}

// FUNCTION: GAMEMD 0x48C590
int ConnectionClass::vf_6()
{
    return 0;
}

// FUNCTION: GAMEMD 0x48C5A0
int ConnectionClass::vf_8()
{
    for (int i = 0; i < Queue->unknown_38; i++) {
        CommReceiveEntry* entry = Queue->FUN_0048B9E0(i);
        if (entry->Flags & 2) {
            ConnPacketHeader* h = (ConnPacketHeader*)entry->unknown_0C;
            if (h->Code == 1 || h->unknown_04 < unknown_44) {
                Queue->FUN_0048B890(0, 0, i, 0, 0);
                i--;
            }
        }
    }
    return 1;
}

// SYNTHETIC: GAMEMD 0x48C650  ConnectionClass::`scalar deleting destructor' (inlines ~ConnectionClass)
