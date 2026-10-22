// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Globals and name offsets extracted individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI, one disassembly per entry
//   point. None of these addresses is bound by YRpp.
//
// Find-by-name over a global array. Walk the array comparing each item's inline
// name against the caller's string and return the index, or -1.
//
// Two things the bytes decide. The count global is re-read on every iteration
// rather than hoisted, so the loop bound comes off the global directly. And the
// name offset is not fixed across instances - 0x45E760 and 0x45E7B0 walk the
// *same* array but compare at +0x64 and +0x24, so they are two different name
// fields on one item type, not a copy-paste of one function.
#ifndef GG_MATCH_CORE_FIND_BY_NAME_METHODS_H
#define GG_MATCH_CORE_FIND_BY_NAME_METHODS_H

extern "C" int __cdecl FUN_007C8D20(const char* a, const char* b);   // strcmp

extern char** DAT_008B4154;  // GLOBAL: GAMEMD 0x8B4154  item array
extern char** DAT_00A83C6C;  // GLOBAL: GAMEMD 0xA83C6C  item array
extern char** DAT_00A8B21C;  // GLOBAL: GAMEMD 0xA8B21C  item array
extern int   DAT_008B4160;   // GLOBAL: GAMEMD 0x8B4160  item count
extern int   DAT_00A83C78;   // GLOBAL: GAMEMD 0xA83C78  item count
extern int   DAT_00A8B228;   // GLOBAL: GAMEMD 0xA8B228  item count

int __fastcall FUN_0041CAA0(const char* name);   // FUNCTION: GAMEMD 0x41CAA0
int __fastcall FUN_00427CB0(const char* name);   // FUNCTION: GAMEMD 0x427CB0
int __fastcall FUN_0045E760(const char* name);   // FUNCTION: GAMEMD 0x45E760
int __fastcall FUN_0045E7B0(const char* name);   // FUNCTION: GAMEMD 0x45E7B0

#endif  // GG_MATCH_CORE_FIND_BY_NAME_METHODS_H
