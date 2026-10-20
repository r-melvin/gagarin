// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x602AE0.
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x601360  FUN_00601360 (__fastcall)
//   FUNCTION: GAMEMD 0x602AE0  FUN_00602AE0 (__fastcall)

#include "control_id_predicate_methods.h"

// FUNCTION: GAMEMD 0x601360  FUN_00601360 (__fastcall)
// The wider membership test of the same family: 58 identifiers, again written
// in retail's comparison order because that order is the source order. This one
// answers a one-byte bool (`MOV AL,1` / `XOR AL,AL`) where its 0x602AE0 sibling
// answers a full dword, and its accepted set is a strict superset of that one's
// except for 0x109 and 0x113, which only this test accepts.
bool __fastcall FUN_00601360(int nID)
{
    if (
        nID == 0x10C || nID == 0x94 || nID == 0xB6 || nID == 0xA3 ||
        nID == 0x73 || nID == 0xD8 || nID == 0xBBB || nID == 0xF5 ||
        nID == 0x105 || nID == 0xE2 || nID == 0xD5 || nID == 0x2B5 ||
        nID == 0xB7 || nID == 0x2B4 || nID == 0x101 || nID == 0x129 ||
        nID == 0xBC7 || nID == 0xBC6 || nID == 0xD7 || nID == 0x108 ||
        nID == 0xBC || nID == 0xBD || nID == 0xBB || nID == 0xB5 ||
        nID == 0xBBA || nID == 0xFF || nID == 0xEA || nID == 0x6B ||
        nID == 0x100 || nID == 0x102 || nID == 0xB8 || nID == 0xD6 ||
        nID == 0x103 || nID == 0x11F || nID == 0x125 || nID == 0x115 ||
        nID == 0x122 || nID == 0x112 || nID == 0xE7 || nID == 0x116 ||
        nID == 0xC2 || nID == 0xC9 || nID == 0x11D || nID == 0x11C ||
        nID == 0x113 || nID == 0xFE || nID == 0x109 || nID == 0x10F ||
        nID == 0x117 || nID == 0x114 || nID == 0xC3 || nID == 0x124 ||
        nID == 0xE6 || nID == 0xF3 || nID == 0xF4 || nID == 0x2BC ||
        nID == 0x11B || nID == 0x10E)
    {
        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x602AE0  FUN_00602AE0 (__fastcall)
// Membership test over a fixed set of eighteen identifiers. The terms are
// written in retail's own comparison order because that order is the source
// order: cl lays a disjunction of equality tests out verbatim, so any
// re-sorting (or a switch, which would bring a jump table) loses the match.
int __fastcall FUN_00602AE0(int nID)
{
    if (nID == 0x125 || nID == 0xE7 || nID == 0x116 || nID == 0xC2 ||
        nID == 0xC9 || nID == 0x11D || nID == 0x11C || nID == 0x114 ||
        nID == 0x2BC || nID == 0x113 || nID == 0x109 || nID == 0x10F ||
        nID == 0x117 || nID == 0xE6 || nID == 0xF3 || nID == 0xF4 ||
        nID == 0x10E || nID == 0x112)
    {
        return 1;
    }

    return 0;
}
