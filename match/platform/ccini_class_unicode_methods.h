// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, literals and the frame read off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x528E00: the CRT calls 0x7CA405
//   (wcslen, result `SHL 3; INC` for the allocation), 0x7C8E17 (operator
//   new), 0x7D468C (_itoa: the zero-extended wchar, the cursor and 0x10
//   pushed, `ADD ESP,0xC`) and 0x7C8B3D (free); the separator string at
//   0x817F70 (","), appended by the inlined strcat (`REPNE SCASB` twice,
//   `REP MOVSD` / `REP MOVSB`) and the cursor re-derived by an inlined
//   strlen off the buffer start; the forward to 0x528660 (WriteString,
//   __thiscall, three pushed pointers). No member of `this` is touched: it is
//   spilled to the frame at entry and reloaded into ECX for the forward.
//   Method names from YRpp (names only).
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_UNICODE_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_UNICODE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// LIBRARY: GAMEMD 0x7CA405 (decl; reloc) — CRT wcslen.
extern "C" unsigned int __cdecl wcslen(const wchar_t* s);
// LIBRARY: GAMEMD 0x7D468C (decl; reloc) — CRT _itoa.
extern "C" char* __cdecl _itoa(int value, char* buffer, int radix);
// LIBRARY: GAMEMD 0x7C8E17 (decl; reloc) — operator new.
extern "C" void* __cdecl FUN_007C8E17(unsigned int size);
// LIBRARY: GAMEMD 0x7C8B3D (decl; reloc) — CRT free.
extern "C" void __cdecl FUN_007C8B3D(void* block);
// CRT intrinsics expanded inline by /O2.
extern "C" char* __cdecl strcat(char* dest, const char* src);
extern "C" unsigned int __cdecl strlen(const char* s);

// STRING: GAMEMD 0x817F70  ","
extern const char STR_00817F70[];

struct CCINI_00528E00
{
    // FUNCTION: GAMEMD 0x528660 (decl; reloc) — INIClass::WriteString.
    bool WriteString(const char* section, const char* key, const char* value);

    // FUNCTION: GAMEMD 0x528E00 — CCINIClass::WriteUnicodeString.
    bool WriteUnicodeString(const char* section, const char* key,
                            const wchar_t* string);
};

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_UNICODE_METHODS_H
