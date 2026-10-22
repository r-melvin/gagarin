// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 with the local
//   Ghidra CLI at 0x67B500 and its four siblings. The frame is a 0x80-byte
//   stack buffer (`SUB ESP,0x80`, `LEA EAX,[ESP]`) handed to the INI string
//   reader at 0x528A10 together with the empty-string default at 0x889F64
//   (confirmed as sixteen zero bytes by `ghidra memory read 0x889F64 32`) and
//   the buffer length 0x80. The reader is __thiscall and no `MOV ECX` precedes
//   the call, which pins the enclosing function's convention: its first
//   parameter is already in ECX and its second is in EDX, i.e. __fastcall.
//   The success path calls a per-instance parser __thiscall on the buffer
//   (`LEA ECX,[ESP]; CALL`) and returns its result; the failure path returns
//   the caller's fallback, read from the second stack parameter.
//
//   All five members are byte-identical apart from the two call relocations,
//   so one body serves the family; only the parser differs per instance.
//   These entry points carry no name in the binary or in the YRpp map and keep
//   their placeholder names.
#ifndef GG_MATCH_PLATFORM_INI_LOOKUP_PARSE_FAMILY_METHODS_H
#define GG_MATCH_PLATFORM_INI_LOOKUP_PARSE_FAMILY_METHODS_H

#include "../_rt/gg_static_assert.h"

// STRING: GAMEMD 0x889F64 — the empty-string default handed to the reader.
extern char const GgEmptyDefault[];

struct GgIniReader
{
    // FUNCTION: GAMEMD 0x528A10 (decl; reloc) — the INI string reader:
    // ReadString(section, entry, defaultValue, buffer, bufferSize).
    int ReadString(char const* section, char const* entry,
                   char const* defaultValue, char* buffer, unsigned size);

    // The five forwarders are members of this same reader, not free functions
    // taking it: retail leaves the reader in ECX for the nested __thiscall
    // ReadString with no `MOV ECX` in between, and the section pointer arrives
    // in EDX — that is `__fastcall` on a member (this in ECX, the first
    // explicit argument in EDX, the rest on the stack, `RET 8`). A plain
    // __thiscall member would push the section too and return `RET 0xC`.
    // Declared ascending by retail address.
    // FUNCTION: GAMEMD 0x67B500
    int __fastcall FUN_0067B500(char const* section, char const* entry, int fallback);
    // FUNCTION: GAMEMD 0x67BAC0
    int __fastcall FUN_0067BAC0(char const* section, char const* entry, int fallback);
    // FUNCTION: GAMEMD 0x67BCE0
    int __fastcall FUN_0067BCE0(char const* section, char const* entry, int fallback);
    // FUNCTION: GAMEMD 0x67BD30
    int __fastcall FUN_0067BD30(char const* section, char const* entry, int fallback);
    // FUNCTION: GAMEMD 0x67BD80
    int __fastcall FUN_0067BD80(char const* section, char const* entry, int fallback);
};

// FUNCTION: GAMEMD 0x75E3B0 (decl; reloc)
int GgParse_0067B500(char* text);
// FUNCTION: GAMEMD 0x524CB0 (decl; reloc)
int GgParse_0067BAC0(char* text);
// FUNCTION: GAMEMD 0x4653C0 (decl; reloc)
int GgParse_0067BCE0(char* text);
// FUNCTION: GAMEMD 0x41CEF0 (decl; reloc)
int GgParse_0067BD30(char* text);
// FUNCTION: GAMEMD 0x71E2A0 (decl; reloc)
int GgParse_0067BD80(char* text);

// Read one INI entry into a 0x80-byte stack buffer and hand it to this
// instance's parser; on a miss, give the caller its fallback back.
#define GG_INI_LOOKUP_PARSE_BODY(TAG)                                     \
int __fastcall GgIniReader::FUN_##TAG(char const* section,                \
                                      char const* entry, int fallback)    \
{                                                                         \
    char buffer[0x80];                                                    \
    if (this->ReadString(section, entry, GgEmptyDefault, buffer,          \
                         sizeof(buffer)) != 0) {                          \
        return GgParse_##TAG(buffer);                                     \
    }                                                                     \
    return fallback;                                                      \
}

#endif  // GG_MATCH_PLATFORM_INI_LOOKUP_PARSE_FAMILY_METHODS_H
