// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Table bases, extents and the element stride are read numerically off the
//   user's retail gamemd.exe v1.001 via the local Ghidra CLI at 0x40DCE0 and
//   0x45DD50. Neither entry point is bound by YRpp or the seed map.
//
// Two case-insensitive name lookups over static {name, value} tables. Both walk
// a pointer by 8 while keeping a separate index, and the index is what the hit
// path uses (`MOV EAX,[EDI*8 + <table>+4]`) - so the element is two 4-byte
// fields and the value is the second.
//
// Extents come from the loop bounds: 0x816EE0..0x817130 is 0x250 bytes, i.e.
// 74 entries, and 0x819288..0x8192B8 is 0x30, i.e. 6.
#ifndef GG_MATCH_CORE_NAME_VALUE_LOOKUP_METHODS_H
#define GG_MATCH_CORE_NAME_VALUE_LOOKUP_METHODS_H

// The CRT-adjacent case-insensitive compare, __cdecl: retail pushes the needle
// first and the table entry second, then adjusts ESP by 8 itself.
extern "C" int __cdecl FUN_007C8D20(const char* a, const char* b);

struct NameValue
{
    const char* Name;    // +0x0000
    int         Value;   // +0x0004
};

// GLOBAL: GAMEMD 0x816EE0 — 74 entries, ends at 0x817130.
extern NameValue DAT_00816EE0[74];
// GLOBAL: GAMEMD 0x819288 — 6 entries, ends at 0x8192B8.
extern NameValue DAT_00819288[6];

// FUNCTION: GAMEMD 0x40DCE0
int __fastcall FUN_0040DCE0(const char* name);
// FUNCTION: GAMEMD 0x45DD50
int __fastcall FUN_0045DD50(const char* name);

#endif  // GG_MATCH_CORE_NAME_VALUE_LOOKUP_METHODS_H
