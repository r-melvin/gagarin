// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly), cross-checked against YRpp
//   (every offset reconfirmed here).
//
// VersionClass — network-protocol versioning. This TU models the
// members and global table its five matched methods touch; the full class
// layout is P2 work.
//
// "Version clipping" narrows the acceptable version window while peers
// hand-shake. InitClipping reopens it to this build's full range, which
// MinVersion/MaxVersion also report — and all three carry the same immediate
// 0x00020000, so YR negotiates against exactly one protocol version.
#ifndef GG_MATCH_NETWORK_VERSION_CLASS_H
#define GG_MATCH_NETWORK_VERSION_CLASS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

// CommProtocolType — YRpp. The protocol field stored in the
// VersionProtocol table at 0x846140 (confirmed: values 0/1/2 at +4 of each
// 8-byte entry).
typedef enum CommProtocolEnum
{
    COMM_PROTOCOL_SINGLE_NO_COMP = 0,
    COMM_PROTOCOL_SINGLE_E_COMP,
    COMM_PROTOCOL_MULTI_E_COMP,
    COMM_PROTOCOL_COUNT,
    DEFAULT_COMM_PROTOCOL = COMM_PROTOCOL_MULTI_E_COMP
} CommProtocolType;

// VersionProtocolType — 8-byte entry: Version (uint) @+0, Protocol (enum) @+4.
// Confirmed numerically from 0x74FD20: loop walks the table by 8 (SUB EAX,8)
// while indexing Protocol via [ECX*8 + 0x846144] (== &VersionProtocol[0].Protocol).
struct VersionProtocolType
{
    unsigned int     Version;   // +0x00
    CommProtocolType Protocol;  // +0x04
};
GG_STATIC_ASSERT(offsetof(VersionProtocolType, Protocol) == 0x04);

// ---------------------------------------------------------------------------
// VersionClass — only MinClipVer @0x3C / MaxClipVer @0x40 are touched here
// (confirmed from 0x74FD60: MOV ...[ECX+0x3c]/[ECX+0x40]). Base padded; full
// layout (vtable, version numbers, VersionText) is P2.
// ---------------------------------------------------------------------------
// The single version constant this build both floors and ceilings at, stored by
// InitClipping (`MOV EAX,0x20000`) and returned by MinVersion / MaxVersion.
#define VERSION_CLASS_VERSION 0x20000

class VersionClass
{
public:
    char         _layout_pad_P2[0x3C];  // vtable + version fields = P2
    unsigned int MinClipVer;            // +0x3C
    unsigned int MaxClipVer;            // +0x40

    // Declared ascending by retail address.
    CommProtocolType Version_Protocol(unsigned int version);             // GAMEMD 0x74FD20 __thiscall
    void             InitClipping();                                     // GAMEMD 0x74FD50 __thiscall
    unsigned int     Clip_Version(unsigned int minver, unsigned int maxver);  // GAMEMD 0x74FD60 __thiscall
    unsigned int     MinVersion();                                       // GAMEMD 0x74FDA0 __thiscall
    unsigned int     MaxVersion();                                       // GAMEMD 0x74FDB0 __thiscall
};

GG_STATIC_ASSERT(offsetof(VersionClass, MinClipVer) == 0x3C);
GG_STATIC_ASSERT(offsetof(VersionClass, MaxClipVer) == 0x40);

#endif  // GG_MATCH_NETWORK_VERSION_CLASS_H
