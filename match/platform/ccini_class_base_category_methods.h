// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Two more CCINIClass accessors absent from the Ghidra function list,
//   found by sweeping the 0x475A3D..0x475D70 gap as raw bytes. Same retail
//   translation unit as the rest of the enumerated reader/writer run.
//
//   The four literals the 0x475A60 reader tests are "POWER" (0x81C030),
//   "FACTORY" (0x81C028), "BARRACKS" (0x81C01C) and "RADAR" (0x81C014),
//   read out of the binary; each sets one of the top four bits, and any
//   other token is looked up as a building category whose index becomes a
//   bit of its own.
#ifndef GG_MATCH_PLATFORM_CCINI_CLASS_BASE_CATEGORY_METHODS_H
#define GG_MATCH_PLATFORM_CCINI_CLASS_BASE_CATEGORY_METHODS_H

#include <stddef.h>
#include <string.h>
#include "../_rt/gg_static_assert.h"

// STRING: GAMEMD 0x889F64  ""
extern const char STR_00889F64[];
// STRING: GAMEMD 0x817F70  ","
extern const char STR_00817F70[];
// STRING: GAMEMD 0x81C014  "RADAR"
extern const char STR_0081C014[];
// STRING: GAMEMD 0x81C01C  "BARRACKS"
extern const char STR_0081C01C[];
// STRING: GAMEMD 0x81C028  "FACTORY"
extern const char STR_0081C028[];
// STRING: GAMEMD 0x81C030  "POWER"
extern const char STR_0081C030[];

// GLOBAL: GAMEMD 0x7E523C — a name table the 0x475A40 writer indexes.
extern const char* DAT_007E523C[];

// The category record: the same array the techno-type TU calls the
// UnitTypeClass items at 0xA83C6C. Only its inline ID text at +0x24 is read,
// by the 0x475B70 writer (`MOV EDI,[EBX]; ADD EDI,0x24`).
struct CategoryType_00475B70
{
    char _pad000[0x24];     // +0x0000
    char ID[4];             // +0x0024
};
GG_STATIC_ASSERT(offsetof(CategoryType_00475B70, ID) == 0x24);

// The registry the reader and the writer share. Its Items pointer is read
// from 0xA83C6C and its Count from 0xA83C78, twelve bytes apart, which puts
// the vector's own base at 0xA83C68: the tree's vector header of
// vtable / Items / Capacity / IsInitialized / IsAllocated / Count /
// CapacityIncrement.
struct CategoryTypeVector
{
    void*                           _vtable;            // +0x0000
    CategoryType_00475B70**         Items;              // +0x0004
    int                             Capacity;           // +0x0008
    bool                            IsInitialized;      // +0x000C
    bool                            IsAllocated;        // +0x000D
    int                             Count;              // +0x0010
    int                             CapacityIncrement;  // +0x0014
};
GG_STATIC_ASSERT(offsetof(CategoryTypeVector, Items) == 0x04 &&
                 offsetof(CategoryTypeVector, IsAllocated) == 0x0D &&
                 offsetof(CategoryTypeVector, Count) == 0x10 &&
                 sizeof(CategoryTypeVector) == 0x18);

// GLOBAL: GAMEMD 0xA83C68 — the category registry whose Items live at 0xA83C6C.
extern CategoryTypeVector DAT_00A83C68;

// FUNCTION: GAMEMD 0x7C9CC2 (decl; reloc) — the CRT token splitter.
extern "C" char* __cdecl FUN_007C9CC2(char* text, const char* delimiters);
// FUNCTION: GAMEMD 0x7C8D20 (decl; reloc) — the CRT case-insensitive compare.
extern "C" int __cdecl FUN_007C8D20(const char* a, const char* b);
// FUNCTION: GAMEMD 0x45E7B0 (decl; reloc) — category name -> bit number.
int FUN_0045E7B0(const char* name);

class CCINI_00475A40
{
public:
    // FUNCTION: GAMEMD 0x528A10 (decl; reloc) — INIClass::ReadString.
    int  ReadString(const char* section, const char* key, const char* defaultValue,
                    char* buffer, unsigned int size);
    // FUNCTION: GAMEMD 0x528660 (decl; reloc) — INIClass::WriteString.
    bool WriteString(const char* section, const char* key, const char* value);

    // FUNCTION: GAMEMD 0x475A40
    bool FUN_00475A40(const char* section, const char* key, int index);
    // FUNCTION: GAMEMD 0x475A60
    int  ReadCategoryList(const char* section, const char* key, int defaultValue);
    // FUNCTION: GAMEMD 0x475B70
    bool WriteCategoryList(const char* section, const char* key, int mask);
};

#endif  // GG_MATCH_PLATFORM_CCINI_CLASS_BASE_CATEGORY_METHODS_H
