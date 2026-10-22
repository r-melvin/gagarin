// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | EA-GPL-RA1-reference
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
ConnectionClass::ConnectionClass(int numsend, int numreceive, int maxlen,
                                 unsigned short magicnum, int retry_delta,
                                 int max_retries, int timeout, int extralen)
{
    MaxPacketLen = maxlen + 0xE;
    MagicNumber = magicnum;
    RetryDelta = retry_delta;
    MaxRetries = max_retries;
    Timeout = timeout;
    PacketBuf = (CommHeaderType*)new char[MaxPacketLen];
    Queue = new CommBufferClass(numsend, numreceive, MaxPacketLen, extralen);
}

// FUNCTION: GAMEMD 0x48BEE0
ConnectionClass::~ConnectionClass()
{
    delete PacketBuf;
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
int ConnectionClass::Send_Packet(void* buf, int buflen, int ack_required,
                                 unsigned char extra)
{
    PacketBuf->MagicNumber = MagicNumber;
    if (ack_required) {
        PacketBuf->Code = 0;
        PacketBuf->PacketID = NumSendAck;
        Debug_Printf("NumSendAck = %d\n", NumSendAck);
    } else {
        PacketBuf->Code = 1;
        PacketBuf->PacketID = unknown_3C;
    }
    if (Session_00A8B238.GameMode == 4 && Flag_00A8DBA0) {
        PacketBuf->unknown_03 = extra;
    }
    if (MaxPacketLen < buflen) {
        Debug_Printf("MaxPacketLen = %d\n", MaxPacketLen);
        Debug_Printf("buflen = %d\n", buflen);
        return 0;
    }
    memcpy(PacketBuf + 1, buf, buflen);
    if (Queue->FUN_0048B410(PacketBuf, buflen + 0xE, 0, 0, 0)) {
        if (ack_required) {
            NumSendAck++;
        } else {
            unknown_3C++;
        }
        return 1;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x48C040
int ConnectionClass::Receive_Packet(CommHeaderType* packet, int buflen)
{
    if (packet->MagicNumber != MagicNumber) {
        unknown_18++;
        return 0;
    }
    if (packet->Code == 2) {
        Debug_Printf("Received ACK for packet %d\n", packet->PacketID);
        for (int i = 0; i < Queue->SendCount; i++) {
            CommSendEntry* entry = Queue->FUN_0048B720(i);
            if (entry && packet->PacketID == ((CommHeaderType*)entry->unknown_14)->PacketID
                && ((CommHeaderType*)entry->unknown_14)->Code == 0) {
                entry->Flags |= 2;
                break;
            }
        }
        return 1;
    }
    if (packet->Code == 1) {
        if (Queue->unknown_08 - Queue->ReceiveCount <= 1) {
            unknown_14++;
            Debug_Printf("Error - ConnectClass::Receive_Packet Queue full on PACKET_DATA_NOACK\n");
            return 0;
        }
        if (!Queue->FUN_0048B750(packet, buflen, 0, 0)) {
            Debug_Printf("Error - unable to queue incoming packet. %s %s\n",
                         "D:\\ra2mdpost\\Connect.CPP", 332);
            unknown_14++;
            return 0;
        }
        unknown_34++;
        unknown_0C = packet->PacketID - unknown_34 + 1;
        if (packet->PacketID) {
            unknown_10 = 100 - (unknown_34 * 100) / (packet->PacketID + 1);
        }
        return 1;
    }
    if (packet->Code == 0) {
        if (packet->PacketID > unknown_44 || unknown_44 == -1) {
            for (int i = 0; i < Queue->ReceiveCount; i++) {
                CommReceiveEntry* entry = Queue->FUN_0048B9E0(i);
                if (entry && ((CommHeaderType*)entry->unknown_0C)->Code == 0
                    && ((CommHeaderType*)entry->unknown_0C)->PacketID == packet->PacketID) {
                    goto send_ack;
                }
            }
            if (Queue->unknown_08 - Queue->ReceiveCount <= 1
                && packet->PacketID != unknown_44 + 1) {
                Debug_Printf("Error - ConnectClass::Receive_Packet Queue full on PACKET_DATA_ACK\n");
                return 0;
            }
            if (!Queue->FUN_0048B750(packet, buflen, 0, 0)) {
                Debug_Printf("Error - ConnectClass::Receive_Packet Queue->Queue_Receive error\n");
                return 0;
            }
            unknown_38++;
            if (packet->PacketID == unknown_44 + 1) {
                unsigned long id = packet->PacketID;
                bool again;
                do {
                    again = false;
                    unknown_44 = id;
                    int i = 0;
                    if (Queue->ReceiveCount > 0) {
                        do {
                            CommReceiveEntry* entry = Queue->FUN_0048B9E0(i);
                            if (entry) {
                                CommHeaderType* h = (CommHeaderType*)entry->unknown_0C;
                                if (h->Code == 0 && h->PacketID == unknown_44 + 1) {
                                    id = h->PacketID;
                                    again = true;
                                    break;
                                }
                            }
                            i++;
                        } while (i < Queue->ReceiveCount);
                    }
                } while (again);
            }
        }
send_ack:
        CommHeaderType ack;
        ack.Code = 2;
        ack.PacketID = packet->PacketID;
        ack.MagicNumber = MagicNumber;
        if (Flag_00A8DBA0) {
            ack.unknown_03 = packet->unknown_03;
        } else {
            ack.unknown_03 = 0;
        }
        Debug_Printf("Sending ACK for packet %d to be forwarded to %02x\n",
                     packet->PacketID, ack.unknown_03);
        Send_To(&ack, 0xE, 0, 0, this == GlobalConnection_00A8EA0C, 0);
        return 1;
    }
    Debug_Printf("Error - ConnectClass::Receive_Packet did not understand packet->Code\n");
    return 0;
}

// FUNCTION: GAMEMD 0x48C320
int ConnectionClass::Get_Packet(void* buf, int* buflen)
{
    CommReceiveEntry* entry;
    int len;
    for (int i = 0; i < Queue->ReceiveCount; i++) {
        entry = Queue->FUN_0048B9E0(i);
        if (entry && !(entry->Flags & 2)) {
            CommHeaderType* h = (CommHeaderType*)entry->unknown_0C;
            if (h->Code == 0 && h->PacketID == unknown_48 + 1) {
                unknown_48 = h->PacketID;
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
    if (Service_Send_Queue() && Service_Receive_Queue()) {
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

    for (i = 0; i < Queue->SendCount; i++) {
        entry = Queue->FUN_0048B720(i);
        if (entry->Flags & 2) {
            if (((CommHeaderType*)entry->unknown_14)->Code == 0) {
                unsigned int now = ConnTimer.GetValue();
                Queue->FUN_0048BA10(now - entry->unknown_04);
            }
            Queue->FUN_0048B570(0, 0, i, 0, 0, 0);
            i--;
        }
    }

    int count = Queue->SendCount;
    for (i = 0; i < count; i++) {
        entry = Queue->FUN_0048B720(i);
        if (!(entry->Flags & 2)) {
            unsigned int now = ConnTimer.GetValue();
            if (now - entry->unknown_08 > RetryDelta) {
                Send_To(entry->unknown_14, entry->unknown_10, entry->unknown_1C,
                        entry->unknown_18, this == GlobalConnection_00A8EA0C,
                        entry->unknown_20);
                entry->unknown_08 = now;
                if (entry->unknown_0C == 0) {
                    entry->unknown_04 = now;
                    if (((CommHeaderType*)entry->unknown_14)->Code == 1) {
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
        Debug_Printf("ConnectionClass::Service_Send_Queue bad connection\n");
        return 0;
    }
    return 1;
}

// FUNCTION: GAMEMD 0x48C590
int ConnectionClass::Remove_Failed_Packets()
{
    return 0;
}

// FUNCTION: GAMEMD 0x48C5A0
int ConnectionClass::Service_Receive_Queue()
{
    for (int i = 0; i < Queue->ReceiveCount; i++) {
        CommReceiveEntry* entry = Queue->FUN_0048B9E0(i);
        if (entry->Flags & 2) {
            CommHeaderType* h = (CommHeaderType*)entry->unknown_0C;
            if (h->Code == 1 || h->PacketID < unknown_44) {
                Queue->FUN_0048B890(0, 0, i, 0, 0);
                i--;
            }
        }
    }
    return 1;
}

// SYNTHETIC: GAMEMD 0x48C650  ConnectionClass::`scalar deleting destructor' (inlines ~ConnectionClass)
