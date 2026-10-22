// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Retail vtable 0x7F45C4 slots +0x64/+0x68 point to 0x6E6080/0x6E6160.
//   Its locator 0x80BCF0 identifies .?AVTagTypeClass@@ at 0x842CB0.
//   The reader is unlisted; raw bytes at its entry end with RET 4 at 0x6E615A.
#ifndef GG_MATCH_AI_TAG_TYPE_CLASS_INI_METHODS_H
#define GG_MATCH_AI_TAG_TYPE_CLASS_INI_METHODS_H

#include "tag_type_class_flag_methods.h"

// Opaque receiver: only direct method calls are made on the INI object.
struct TagINI_006E6080
{
    // FUNCTION: GAMEMD 0x526B00
    void Reset();
    // FUNCTION: GAMEMD 0x528660
    bool WriteString(const char* section, const char* key, const char* value);
    // FUNCTION: GAMEMD 0x528A10
    int ReadString(const char* section, const char* key, const char* def,
                   char* buffer, int length);
};

// GLOBAL: GAMEMD 0x7F4550 — points to "Tags" at 0x842C3C.
extern const char* DAT_007F4550;
// STRING: GAMEMD 0x817F70 — comma.
extern const char STR_00817F70[];
// STRING: GAMEMD 0x842CCC — "%d,%s,%s".
extern const char STR_00842CCC[];
// STRING: GAMEMD 0x842CD8 — "%s,<none>".
extern const char STR_00842CD8[];
// STRING: GAMEMD 0x889F64 — empty default.
extern const char STR_00889F64[];

// LIBRARY: GAMEMD 0x7C91D0 — strncpy.
extern "C" char* __cdecl strncpy(char*, const char*, unsigned int);
// LIBRARY: GAMEMD 0x7C9BFD — decimal parser.
extern "C" int __cdecl FUN_007C9BFD(const char*);
// LIBRARY: GAMEMD 0x7C9CC2 — strtok.
extern "C" char* __cdecl strtok(char*, const char*);
// IAT at 0x7E14B0: wsprintfA, a cdecl variadic WinAPI import.
extern "C" __declspec(dllimport) int __cdecl wsprintfA(char*, const char*, ...);

// The shared TriggerTypeClass declares the native factory at 0x727AA0.

// Retail copies twelve dwords and a final byte to Name at +0x64.
struct TagName_006E6080 { char Text[0x31]; };
GG_STATIC_ASSERT(offsetof(TagName_006E6080, Text) == 0);
GG_STATIC_ASSERT(sizeof(((AbstractTypeClass*)0)->Name) == sizeof(TagName_006E6080));
GG_STATIC_ASSERT(sizeof(TagName_006E6080) == 0x31);

#endif // GG_MATCH_AI_TAG_TYPE_CLASS_INI_METHODS_H
