// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   The comma-separated-list and percentage corner of the CCINIClass
//   enumerated reader run, read numerically off the user's retail
//   gamemd.exe v1.001 with the local Ghidra CLI. Same contiguous
//   0x474810..0x475A3D block as ccini_class_small_readers_methods.cpp,
//   whose confirmed INI conventions are reused.
//
//   Layout evidence, all from the disassembly: the house instance array is
//   reached as a pointer at 0xA8022C with its count twelve bytes later at
//   0xA80238; the record's bit index is the dword at +0x30 (`MOV ECX,
//   [EDX+0x30]; SHL EAX,CL` at 0x475322) and its inline name text starts at
//   +0x15FF4 (`LEA EDI,[EDX+0x15FF4]` at 0x475364), which is consistent
//   with the record being one of the engine's very large house objects
//   rather than a house *type*.
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_HOUSE_LIST_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_HOUSE_LIST_METHODS_H

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

// STRING: GAMEMD 0x889F64  ""
extern const char STR_00889F64[];
// STRING: GAMEMD 0x817F70  ","
extern const char STR_00817F70[];

// FUNCTION: GAMEMD 0x7C9CC2 (decl; reloc) — the CRT token splitter, under
// its placeholder name so cl cannot substitute anything for the call.
extern "C" char* __cdecl FUN_007C9CC2(char* text, const char* delimiters);

// FUNCTION: GAMEMD 0x48DEB0 (decl; reloc) — house-type name -> bit mask.
int __fastcall FUN_0048DEB0(const char* name);
// FUNCTION: GAMEMD 0x50C170 (decl; reloc) — house name -> bit number.
int __fastcall FUN_0050C170(const char* name);

// One house record. Only its bit index and its inline name are touched.
struct House_004752E0
{
    char _pad000[0x30];         // +0x0000
    int  Index;                 // +0x0030
    char _pad034[0x15FC0];      // +0x0034
    char Name[0x18];            // +0x15FF4
};
GG_STATIC_ASSERT(offsetof(House_004752E0, Index) == 0x30 &&
                 offsetof(House_004752E0, Name) == 0x15FF4);

// The house registry: Items at 0xA8022C, Count at 0xA80238.
// Partial registry view through Count; intermediate bytes remain unknown.
struct HouseVector
{
    void*               _vtable;    // +0x0000
    House_004752E0**    Items;      // +0x0004
    int                 Capacity;   // +0x0008
    char unknown_0C[4];                 // +0x000C
    int                 Count;      // +0x0010
};
GG_STATIC_ASSERT(offsetof(HouseVector, Items) == 0x04 &&
                 offsetof(HouseVector, Count) == 0x10 &&
                 sizeof(HouseVector) == 0x14);

// GLOBAL: GAMEMD 0xA80228 — the house registry.
extern HouseVector DAT_00A80228;

class CCINI_00474810
{
public:
    // FUNCTION: GAMEMD 0x5276D0 (decl; reloc) — INIClass::ReadInteger.
    int  ReadInteger(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x528A10 (decl; reloc) — INIClass::ReadString.
    int  ReadString(const char* section, const char* key, const char* defaultValue,
                    char* buffer, unsigned int size);
    // FUNCTION: GAMEMD 0x528660 (decl; reloc) — INIClass::WriteString.
    bool WriteString(const char* section, const char* key, const char* value);

    // FUNCTION: GAMEMD 0x474810
    int  ReadPercentAsByte(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x4750D0
    int  ReadHouseTypesList(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x475260
    int  ReadHousesList(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x4752E0
    bool WriteHousesList(const char* section, const char* key, unsigned int bits);
};

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_HOUSE_LIST_METHODS_H
