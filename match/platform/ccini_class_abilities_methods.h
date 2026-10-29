// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Frame, arguments and call shapes read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x477640: the __thiscall
//   with the hidden result pointer as the first stack word (`[ESP+0x9C]`
//   after the 0x94-byte frame, returned in EAX) and `RET 0x10` for the four
//   stack words; the 0x80-byte buffer at `[ESP+0x14]` handed with the
//   section, key and the empty default 0x889F64 to `CALL 0x528A10`
//   (INIClass::ReadString, __thiscall, five arguments); the CRT strtok
//   0x7C9CC2 with the "," literal 0x817F70; the ability-name lookup 0x74FEF0
//   taking the token in ECX and answering -1 for no match; the 18-byte
//   result (`MOV byte [ESP+EAX+4],1` for a hit) copied out as four dwords and
//   a word, and the same copy from the default pointer on the empty-key path.
//   YRpp names only: CCINIClass::ReadAbilities,
//   AbilitiesStruct (18 bools), INIClass::ReadString @0x528A10.
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_ABILITIES_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_ABILITIES_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "ccini_class_methods.h"

// LIBRARY: GAMEMD 0x7C9CC2 — CRT strtok (excluded from the match target).
extern "C" char* __cdecl strtok(char* str, const char* delim);
// LIBRARY: CRT memset (inlined by cl at a constant size).
extern "C" void* __cdecl memset(void* dest, int value, size_t count);

// STRING: GAMEMD 0x889F64 — the shared empty default string.
extern const char DAT_00889F64[];
// STRING: GAMEMD 0x817F70 — ",".
extern const char DAT_00817F70[];

// FUNCTION: GAMEMD 0x74FEF0 (decl; reloc) — ability name to index, -1 if
// unknown; the string arrives in ECX.
int FUN_0074FEF0(const char* name);

// One flag per veteran/elite ability, 18 of them.
struct AbilitiesStruct
{
    bool Flags[18];   // +0x00
};
GG_STATIC_ASSERT(sizeof(AbilitiesStruct) == 0x12);


#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_ABILITIES_METHODS_H
