// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x4CB8B0-0x4CB978), cross-checked
//   against YRpp (FieldClass) (reconfirmed here).
//
// FieldClass — one network packet field: a 4-byte ID, a 16-bit data-type tag,
// a 16-bit size, and a pointer to the field's data. HostToNet / NetToHost
// byte-swap the type/size and, for short/long-typed fields, the data payload.
// (The two byte-swap methods live in the file named for PacketClass, the
//  packet that owns a linked list of these fields.)
#ifndef GG_MATCH_NETWORK_PACKET_CLASS_H
#define GG_MATCH_NETWORK_PACKET_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FieldClass data-type tags (confirmed from the HostToNet/NetToHost jump
// tables: `add eax,-3; cmp eax,3; ja default`, i.e. cases 3..6). Tags 3/4
// (SHORT/USHORT) swap a 16-bit payload; 5/6 (LONG/ULONG) swap a 32-bit one.
class FieldClass
{
public:
    void HostToNet();   // GAMEMD 0x4CB8B0 __thiscall
    void NetToHost();   // GAMEMD 0x4CB920 __thiscall

    // Properties
    char           ID[4];     // +0x00
    unsigned short DataType;  // +0x04
    unsigned short Size;      // +0x06
    void*          Data;      // +0x08
    FieldClass*    Next;      // +0x0C
};

GG_STATIC_ASSERT(offsetof(FieldClass, DataType) == 0x04);
GG_STATIC_ASSERT(offsetof(FieldClass, Size)     == 0x06);
GG_STATIC_ASSERT(offsetof(FieldClass, Data)     == 0x08);

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(FieldClass, Next)     == 0x0C);
GG_STATIC_ASSERT(sizeof(FieldClass)             == 0x10);
#endif

// Winsock ntohs, reached through the thunk at 0x7C8974.
extern "C" unsigned short __stdcall ntohs(unsigned short netshort);

// PacketClass -- a received packet: its total size and ID in host order and
// the singly linked list of its fields, newest first. Offsets from the parse
// constructor at 0x625AF0 (`MOV [EDI],AX`, `MOV [EDI+2],AX`, `MOV [EDI+4],0`).
class PacketClass
{
public:
    PacketClass(char* pBuffer);   // GAMEMD 0x625AF0 __thiscall

    unsigned short Size;          // +0x00
    unsigned short ID;            // +0x02
    FieldClass*    Head;          // +0x04
};

GG_STATIC_ASSERT(offsetof(PacketClass, ID)   == 0x02);
GG_STATIC_ASSERT(offsetof(PacketClass, Head) == 0x04);

#endif  // GG_MATCH_NETWORK_PACKET_CLASS_H
