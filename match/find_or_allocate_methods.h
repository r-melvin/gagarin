// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Strings, globals, allocation sizes and constructor targets extracted
//   individually from the user's retail gamemd.exe v1.001 via the local Ghidra
//   CLI, one disassembly per entry point. None is bound by YRpp.
//
// FindOrAllocate. Reject the two "no type" spellings, look the name up in the
// global array, and construct a new item when it is absent.
//
// The two rejected names are the same strings in all three instances - "<none>"
// at 0x817474 and "none" at 0x817694 - but everything else differs: array
// globals, allocation size and constructor target are per type. The allocation
// sizes are the giveaway that these are three distinct item types sharing one
// lookup shape: 0xE10, 0x110 and 0x1798.
#ifndef GG_MATCH_CORE_FIND_OR_ALLOCATE_METHODS_H
#define GG_MATCH_CORE_FIND_OR_ALLOCATE_METHODS_H

extern "C" int   __cdecl FUN_007C8D20(const char* a, const char* b);   // strcmp
extern "C" void* __cdecl FUN_007C8E17(unsigned int size);              // operator new

// STRING: GAMEMD 0x817474  "<none>"
extern const char STR_00817474[];
// STRING: GAMEMD 0x817694  "none"
extern const char STR_00817694[];

extern char** DAT_00A83C6C;   // GLOBAL: GAMEMD 0xA83C6C  item array
extern char** DAT_00A8B204;   // GLOBAL: GAMEMD 0xA8B204  item array
extern char** DAT_00A8B21C;   // GLOBAL: GAMEMD 0xA8B21C  item array
extern int    DAT_00A83C78;   // GLOBAL: GAMEMD 0xA83C78  item count
extern int    DAT_00A8B210;   // GLOBAL: GAMEMD 0xA8B210  item count
extern int    DAT_00A8B228;   // GLOBAL: GAMEMD 0xA8B228  item count

// Item constructors. __thiscall, not __fastcall: retail pushes the name and
// leaves only `this` in ECX, so a second register argument puts it in EDX and
// the call site stops matching.
struct Item
{
    char* FUN_0041C8B0(const char* name);   // GAMEMD 0x41C8B0
    char* FUN_0041E350(const char* name);   // GAMEMD 0x41E350
    char* FUN_0045DD90(const char* name);   // GAMEMD 0x45DD90
};

char* FUN_0041CEF0(const char* name);   // FUNCTION: GAMEMD 0x41CEF0
char* FUN_0041FCA0(const char* name);   // FUNCTION: GAMEMD 0x41FCA0
char* FUN_004653C0(const char* name);   // FUNCTION: GAMEMD 0x4653C0

#endif  // GG_MATCH_CORE_FIND_OR_ALLOCATE_METHODS_H
