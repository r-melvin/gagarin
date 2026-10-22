// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp.
#ifndef GG_MATCH_CORE_SMALL_MISC16_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC16_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "intrusive_list_methods.h"

extern "C" void __cdecl FUN_007C8B3D(void* block);
// GLOBAL: GAMEMD 0x87DE28 — cleared once the object is gone.
extern int DAT_0087DE28;

// A dispatch table with a flag word of its own at +0x0C.
struct Obj_00402B80;
typedef void (__fastcall* Slot18)(Obj_00402B80*);
struct Table_00402B80 { char _pad[0xC]; int at0C; char _pad10[0x18 - 0x10]; };

struct Obj_00402B80
{
    char             _pad00[0xC];
    Table_00402B80*  Table;   // +0x000C

    // FUNCTION: GAMEMD 0x402B80
    void FUN_00402B80();
};
GG_STATIC_ASSERT(offsetof(Obj_00402B80, Table) == 0xC);

struct Node_00408B10 { char _pad[0x1C]; int at1C; char _pad20[0x30 - 0x20]; void* at30; };

struct Obj_00408B10
{
    int  Count;        // +0x0000
    // +0x04 is a ListNode anchor.
    char _pad04[0x10 - 0x04];
    int  unknown_10;   // +0x0010
    int  Total;        // +0x0014

    // FUNCTION: GAMEMD 0x408B10
    void __fastcall FUN_00408B10(Node_00408B10* node);
};
GG_STATIC_ASSERT(offsetof(Obj_00408B10, Total) == 0x14);

// Receiver of 0x433CF0 / 0x433ED0. 0x433ED0 never touches ECX: the receiver
// passes straight through to the helper, so both are __thiscall members.
struct Obj_00433CF0
{
    // FUNCTION: GAMEMD 0x433CF0 — callee-cleanup, four stack arguments.
    void FUN_00433CF0(int a, int* b, int c, int d);

    // FUNCTION: GAMEMD 0x433ED0 — hands the second argument to the helper both
    // by value and by address, then returns it.
    int FUN_00433ED0(int a, int b);
};

#endif  // GG_MATCH_CORE_SMALL_MISC16_METHODS_H
