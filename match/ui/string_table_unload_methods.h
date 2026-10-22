// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Globals and call shapes read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x734D30: the two singly
//   linked lists whose heads live at `[0xB1CF8C]` and `[0xB1CF88]` (next
//   pointer at +0 of each node, `MOV ECX,[EAX]` / `MOV ESI,[EAX]`); the two
//   pointer arrays `[0xB1CF78]` and `[0xB1CF7C]` walked with `[ECX+ESI*4]`
//   against the count `[0xB1CF70]`; the single buffer `[0xB1CF74]`; the
//   dword store `MOV [0xB1CF80],EDI` (a 4-byte flag); and the CRT free at
//   0x7C8B3D (`PUSH p; CALL; ADD ESP,4`). YRpp names only
//  : StringTable::Unload (static), ValueCount
//   @0xB1CF70, Labels @0xB1CF74, Values @0xB1CF78, ExtraValues @0xB1CF7C,
//   IsLoaded @0xB1CF80, LastLoadedString @0xB1CF88; 0xB1CF8C is unnamed there.
#ifndef GG_MATCH_UI_STRING_TABLE_UNLOAD_METHODS_H
#define GG_MATCH_UI_STRING_TABLE_UNLOAD_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// LIBRARY: GAMEMD 0x7C8B3D — CRT free (push ptr; call; add esp,4); excluded
// from the match target.
extern "C" void __cdecl FUN_007C8B3D(void* block);

// A node of either singly linked string list; only the link at +0 is read.
struct StringNode_00734D30
{
    StringNode_00734D30* Next;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(StringNode_00734D30, Next) == 0x0);

// GLOBAL: GAMEMD 0xB1CF70 — StringTable::ValueCount.
extern int DAT_00B1CF70;
// GLOBAL: GAMEMD 0xB1CF74 — StringTable::Labels (one block).
extern void* DAT_00B1CF74;
// GLOBAL: GAMEMD 0xB1CF78 — StringTable::Values (ValueCount owned strings).
extern void** DAT_00B1CF78;
// GLOBAL: GAMEMD 0xB1CF7C — StringTable::ExtraValues (ValueCount owned strings).
extern void** DAT_00B1CF7C;
// GLOBAL: GAMEMD 0xB1CF80 — StringTable::IsLoaded (stored as a dword).
extern int DAT_00B1CF80;
// GLOBAL: GAMEMD 0xB1CF88 — StringTable::LastLoadedString list head.
extern StringNode_00734D30* DAT_00B1CF88;
// GLOBAL: GAMEMD 0xB1CF8C — a second owned string list head.
extern StringNode_00734D30* DAT_00B1CF8C;

struct StringTable
{
    // FUNCTION: GAMEMD 0x734D30
    static void Unload();
};

#endif  // GG_MATCH_UI_STRING_TABLE_UNLOAD_METHODS_H
