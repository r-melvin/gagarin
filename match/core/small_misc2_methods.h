// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp,
//   so all keep placeholder names.
#ifndef GG_MATCH_CORE_SMALL_MISC2_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC2_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "guarded_forward_methods.h"

// GLOBAL: GAMEMD 0x87E8A0 — an interface pointer released through slot 0x48.
extern IFace* DAT_0087E8A0;
// GLOBAL: GAMEMD 0x87E294 — installed into a fresh record by 0x405BE0.
extern char DAT_0087E294[];
// STRING: GAMEMD 0x817474 — "<none>", the out-of-range answer for 0x473960.
extern const char STR_00817474b[];
// GLOBAL: GAMEMD 0x81B7CC — an eleven-entry table with an eight-byte stride.
struct TableEntry8 { const char* Name; int unknown_04; };
extern TableEntry8 DAT_0081B7CC[];

// FUNCTION: GAMEMD 0x40A940 — release the global interface if it is set.
void __cdecl FUN_0040A940b();

// FUNCTION: GAMEMD 0x473960 — bounds-checked table read; the compare is
// unsigned (`JNC`), so a negative index takes the out-of-range path too.
const char* FUN_00473960(unsigned int index);

#include "flag_object_00407100.h"

struct Voice_00405D40;

struct Obj_004072D0
{
    void* a;   // +0x0000
    void* b;   // +0x0004
    int   c;   // +0x0008

    // FUNCTION: GAMEMD 0x4072D0
    void FUN_004072D0();
};

struct Obj_00405B00
{
    Voice_00405D40* unknown_00;  // +0x0000
    int   unknown_04;  // +0x0004
    void* unknown_08;  // +0x0008
    char* unknown_0C;  // +0x000C

    // FUNCTION: GAMEMD 0x405BE0
    void FUN_00405BE0();
    // FUNCTION: GAMEMD 0x405C00
    void FUN_00405C00();
};
GG_STATIC_ASSERT(offsetof(Obj_00405B00, unknown_00) == 0x0);
GG_STATIC_ASSERT(offsetof(Obj_00405B00, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Obj_00405B00, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(Obj_00405B00, unknown_0C) == 0xC);
GG_STATIC_ASSERT(sizeof(Obj_00405B00) == 0x10);

// Callee-cleanup: no `ADD ESP` after the call, so __stdcall.
void __stdcall FUN_00432E40(int a, int b, int c);

struct Obj_00433000
{
    char _pad00[0xC];
    int  unknown_0C;   // +0x000C
    int  unknown_10;   // +0x0010
    int  unknown_14;   // +0x0014

    // FUNCTION: GAMEMD 0x433040
    void FUN_00433040();
};
GG_STATIC_ASSERT(offsetof(Obj_00433000, unknown_14) == 0x14);

struct Obj_00406600b
{
    char _pad00[0x10];
    int  Flags;        // +0x0010
    char _pad14[0x4C - 0x14];
    int  unknown_4C;   // +0x004C

    // FUNCTION: GAMEMD 0x406650
    int FUN_00406650() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00406600b, unknown_4C) == 0x4C);

#endif  // GG_MATCH_CORE_SMALL_MISC2_METHODS_H
