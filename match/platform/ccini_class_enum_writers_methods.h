// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Eleven CCINIClass writers that the Ghidra function list does not know
//   about. Every one of them sits in an address gap between two listed
//   functions, behind a pad of 0x90 bytes, and was found by sweeping the
//   gaps as raw bytes (`ghidra memory read` piped through `objdump -D -b
//   binary -m i386`) rather than from the function list or from the
//   private-reference seed, neither of which names any of them. They belong to the
//   same retail translation unit as the readers in
//   ccini_class_name_table_readers_methods.cpp,
//   ccini_class_armor_house_type_methods.cpp,
//   ccini_class_house_list_methods.cpp and
//   ccini_class_theater_theme_methods.cpp: each is the writer paired with
//   one of those readers, and each reuses that reader's already-confirmed
//   table.
//
//   Offsets confirmed numerically here: the house-type record's bit index
//   is the dword at +0xB8 (`MOV ECX,[EDX+0xB8]; SHL EAX,CL` at 0x475192)
//   and its inline ID text starts at +0x24 (`LEA EDI,[EDX+0x24]` at
//   0x4751D7), the same +0x24 the movie record uses at 0x4757B6.
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_ENUM_WRITERS_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_ENUM_WRITERS_METHODS_H

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

// STRING: GAMEMD 0x817474  "<none>"
extern const char STR_00817474[];
// STRING: GAMEMD 0x817F70  ","
extern const char STR_00817F70[];
// STRING: GAMEMD 0x8189B0  "%d,%d,%d"
extern const char STR_008189B0[];

// FUNCTION: GAMEMD 0x7C8EF4 (decl; reloc) — the CRT formatter, under its
// placeholder name so cl emits the ordinary call retail has.
extern "C" int __cdecl FUN_007C8EF4(char* buffer, const char* format, ...);

// A {name, value} row; see ccini_class_name_table_readers_methods.h.
struct WriterNameValuePair
{
    const char* Name;       // +0x0000
    int         Value;      // +0x0004
};
GG_STATIC_ASSERT(offsetof(WriterNameValuePair, Value) == 0x04 &&
                 sizeof(WriterNameValuePair) == 0x08);

// GLOBAL: GAMEMD 0x81B958 — the pip name table.
extern WriterNameValuePair DAT_0081B958[];
// GLOBAL: GAMEMD 0x81B9B0 — the pip-scale name table.
extern WriterNameValuePair DAT_0081B9B0[];
// GLOBAL: GAMEMD 0x81B9D8 — the foundation name table.
extern WriterNameValuePair DAT_0081B9D8[];
// GLOBAL: GAMEMD 0x81BA88 — the movement-zone names.
extern const char* DAT_0081BA88[];
// GLOBAL: GAMEMD 0x7E5210 — the armour names.
extern const char* DAT_007E5210[];

// The house-type record, as this file uses it: a bit index at +0xB8 and an
// inline ID text at +0x24.
struct HouseTypeRecord
{
    char _pad000[0x24];     // +0x0000
    char ID[0x94];          // +0x0024
    int  Index;             // +0x00B8
};
GG_STATIC_ASSERT(offsetof(HouseTypeRecord, ID) == 0x24 &&
                 offsetof(HouseTypeRecord, Index) == 0xB8);

struct HouseTypeRecordVector
{
    void*               _vtable;    // +0x0000
    HouseTypeRecord**   Items;      // +0x0004
    int                 Capacity;   // +0x0008
    int                 Count;      // +0x000C
};
GG_STATIC_ASSERT(offsetof(HouseTypeRecordVector, Items) == 0x04 &&
                 offsetof(HouseTypeRecordVector, Count) == 0x0C);

// GLOBAL: GAMEMD 0xA83C98 — the house-type registry (Items 0xA83C9C,
// Count 0xA83CA8).
extern HouseTypeRecordVector DAT_00A83C98;

// The movie record, as this file uses it: only the inline ID at +0x24.
struct MovieRecord
{
    char _pad000[0x24];     // +0x0000
    char ID[0x90];          // +0x0024
};
GG_STATIC_ASSERT(offsetof(MovieRecord, ID) == 0x24);

// GLOBAL: GAMEMD 0x8B4124 — pointer to the movie record array.
extern MovieRecord** DAT_008B4124;

// A one-dword value class. Retail returns it through a hidden buffer with
// `MOV [ECX],EAX; MOV EAX,ECX`, which is VC6's convention for a class of
// size four whether or not it declares anything.
struct IniValue
{
    int Value;      // +0x0000
};
GG_STATIC_ASSERT(sizeof(IniValue) == 0x04);

class CCINI_00474910
{
public:
    // FUNCTION: GAMEMD 0x528660 (decl; reloc) — INIClass::WriteString.
    bool     WriteString(const char* section, const char* key, const char* value);
    // FUNCTION: GAMEMD 0x528220 (decl; reloc) — a scalar INI reader whose
    // result this file wraps in a one-dword value class.
    int      ReadScalar(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x528170 (decl; reloc) — its matching writer.
    bool     WriteScalar(const char* section, const char* key, int value);

    // FUNCTION: GAMEMD 0x474910
    bool     WritePip(const char* section, const char* key, int index);
    // FUNCTION: GAMEMD 0x4749B0
    bool     WritePipScale(const char* section, const char* key, int index);
    // FUNCTION: GAMEMD 0x474A50
    IniValue FUN_00474A50(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x474A70
    bool     FUN_00474A70(const char* section, const char* key, int value);
    // FUNCTION: GAMEMD 0x474C20
    bool     FUN_00474C20(const char* section, const char* key,
                          const unsigned char* rgb);
    // FUNCTION: GAMEMD 0x474D50
    bool     FUN_00474D50(const char* section, const char* key,
                          const unsigned char* rgb);
    // FUNCTION: GAMEMD 0x474E10
    bool     WriteFoundation(const char* section, const char* key, int index);
    // FUNCTION: GAMEMD 0x474EB0
    bool     WriteMovementZone(const char* section, const char* key, int index);
    // FUNCTION: GAMEMD 0x475150
    bool     WriteHouseTypesList(const char* section, const char* key,
                                 unsigned int bits);
    // FUNCTION: GAMEMD 0x475440
    bool     WriteArmorName(const char* section, const char* key, int index);
    // FUNCTION: GAMEMD 0x4757A0
    bool     WriteMovie(const char* section, const char* key, int index);
};

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_ENUM_WRITERS_METHODS_H
