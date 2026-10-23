// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-REA | own-binary-via-Ghidra
// Command-specific packet layouts shared by their sender/receiver consumers.
// Existing receive and taunt buffers retain their established extents. These
// are separate command variants: byte2F in the taunt is not the progress int.
// 69AE90 zeroes250/455 bytes and sends250/51 respectively; no narrowed local.
#ifndef GG_MATCH_NETWORK_COMMAND_PACKET_LAYOUTS_H
#define GG_MATCH_NETWORK_COMMAND_PACKET_LAYOUTS_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"
// One message popped off the queue: only the kind, the sender byte and the
// payload int are read, and the payload sits one byte into the sender word,
// so the record is packed.
#pragma pack(push, 1)
struct Message_0048D080
{
    int  Kind;                 // +0x0000
    char _pad004[0x18 - 0x04]; // +0x0004
    union
    {
        int SenderWord;        // +0x0018  low byte is the sender
        struct
        {
            char Sender;       // +0x0018
            int  Payload;      // +0x0019  unaligned
        } Packed;
    };
    char _pad01D[0xFC - 0x1D]; // +0x001D
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(Message_0048D080, SenderWord) == 0x18);
GG_STATIC_ASSERT(sizeof(Message_0048D080) == 0xFC);


// The taunt packet: 0x1C7 bytes sent (PUSH 0x1C7), command 0x1D at +0, the
// sender's name copied to +4, then byte, packed-nibble and two dword fields at
// odd offsets (+0x2F, +0x30, +0x31, +0x35).
#pragma pack(push, 1)
struct CommandTauntPacket
{
    int Command;                         // +0x00
    char Name[0x2B];                     // +0x04
    bool unknown_2F;                     // +0x2F
    unsigned char Taunt : 4;             // +0x30 low nibble
    unsigned char Colour : 4;            // +0x30 high nibble
    int unknown_31;                      // +0x31
    int unknown_35;                      // +0x35
    char unknown_39[0x1C7 - 0x39];       // +0x39
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(CommandTauntPacket, unknown_2F) == 0x2F);
GG_STATIC_ASSERT(offsetof(CommandTauntPacket, unknown_31) == 0x31);
GG_STATIC_ASSERT(offsetof(CommandTauntPacket, unknown_35) == 0x35);
GG_STATIC_ASSERT(sizeof(CommandTauntPacket) == 0x1C7);


// 0x64ABDF/0x64AC0D/0x64AC1F, followed by the 455-byte send0x64AC4D.
// ev_f0992f314e4faa58347216093b1b6eb19b21c8184a79afb69519601a1e420b09.
#pragma pack(push, 1)
struct QueuePacket_0064AAE0
{
    int unknown_00;
    char unknown_04[20];
    char unknown_18[0x2F - 0x18];
    int unknown_2F;
    int unknown_33;
    char unknown_37[0x1C7 - 0x37];
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(QueuePacket_0064AAE0, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(QueuePacket_0064AAE0, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(QueuePacket_0064AAE0, unknown_2F) == 0x2F);
GG_STATIC_ASSERT(offsetof(QueuePacket_0064AAE0, unknown_33) == 0x33);
GG_STATIC_ASSERT(sizeof(QueuePacket_0064AAE0) == 0x1C7);
#pragma pack(push, 1)
struct Payload_0069B08C
{
    int unknown_00; // 69B0A2: command0x6C
    unsigned char unknown_04[0x18 - 4];
    unsigned char unknown_18; // 69B0D5: sender byte fromA8DB30
    int unknown_19; // 69B0C0: truncated progress percentage
    unsigned char unknown_1D[0xFA - 0x1D];
};
struct Payload_0069AF45
{
    int unknown_00; // 69AF5C: command0x0F
    char unknown_04[0x2F - 4]; // strcpy destination; logical string limit unproven
    int unknown_2F; // 69AF7A: progress, NOT the taunt packet's bool atthisoffset
    unsigned char unknown_33[0x1C7 - 0x33];
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(Payload_0069B08C, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(Payload_0069B08C, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(Payload_0069B08C, unknown_19) == 0x19);
GG_STATIC_ASSERT(sizeof(Payload_0069B08C) == 0xFA);
GG_STATIC_ASSERT(offsetof(Payload_0069AF45, unknown_00) == 0);
GG_STATIC_ASSERT(offsetof(Payload_0069AF45, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(Payload_0069AF45, unknown_2F) == 0x2F);
GG_STATIC_ASSERT(sizeof(Payload_0069AF45) == 0x1C7);

GG_STATIC_ASSERT(sizeof(((Payload_0069B08C*)0)->unknown_00) == 4);
GG_STATIC_ASSERT(sizeof(((Payload_0069B08C*)0)->unknown_18) == 1);
GG_STATIC_ASSERT(sizeof(((Payload_0069B08C*)0)->unknown_19) == 4);
GG_STATIC_ASSERT(sizeof(((Payload_0069AF45*)0)->unknown_00) == 4);
GG_STATIC_ASSERT(sizeof(((Payload_0069AF45*)0)->unknown_2F) == 4);
#endif
