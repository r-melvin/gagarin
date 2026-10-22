// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and global addresses read off the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI at 0x4A80D0 / 0x6C8C40 / 0x732D00. Names cross-checked
//   against YRpp.
//
// Three unrelated global query leaves that share only their shape: a constant,
// a scaled system clock, and a global flag read.
#ifndef GG_MATCH_PLATFORM_SYSTEM_QUERY_METHODS_H
#define GG_MATCH_PLATFORM_SYSTEM_QUERY_METHODS_H

// GLOBAL: GAMEMD 0x00B0FE65 — the "player is type-selecting" flag (a double
// click selects every unit of the same type on screen).
extern bool IsTypeSelectingFlag;

// CD number the engine reports for the currently required disc. Retail is the
// constant 2 (`MOV EAX,0x2; RET`) — YR ships a single disc, so the multi-disc
// query is hard-wired.
int __fastcall CD_GetCDNumber();          // GAMEMD 0x4A80D0

// The engine's coarse game clock: the multimedia timer in milliseconds scaled
// down by 16 (`SHR EAX,4`), giving roughly a 1/60 s tick.
int __fastcall Timer_GetTime();           // GAMEMD 0x6C8C40

bool __fastcall Unsorted_IsTypeSelecting(); // GAMEMD 0x732D00

#endif  // GG_MATCH_PLATFORM_SYSTEM_QUERY_METHODS_H
