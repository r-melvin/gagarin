// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp or the
//   seed map.
#ifndef GG_MATCH_CORE_SMALL_MISC5_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC5_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x87E728 — the subsystem object these entry points drive.
extern void* DAT_0087E728;
// GLOBAL: GAMEMD 0x89E050 / 0x81B1E8 — reset alongside the record at 0x46D330.
extern int   DAT_0089E050;
extern int   DAT_0081B1E8;
// VTABLE: GAMEMD 0x7E4AAC
extern char  VT_007E4AAC[];

// Declared-only callees.
void __fastcall FUN_004071C0(void* self);                 // GAMEMD 0x4071C0
void __fastcall FUN_00403730(void* self, int arg);        // GAMEMD 0x403730
void __fastcall FUN_00403770(void* self, int arg);        // GAMEMD 0x403770
void __fastcall FUN_004037C0(void* self, int arg);        // GAMEMD 0x4037C0
void __cdecl    FUN_00404E70();                           // GAMEMD 0x404E70
void __cdecl    FUN_00404FD0();                           // GAMEMD 0x404FD0
void __cdecl    FUN_00405040();                           // GAMEMD 0x405040
void __cdecl    FUN_004081A0();                           // GAMEMD 0x4081A0
void __cdecl    FUN_00751040();                           // GAMEMD 0x751040
void __cdecl    FUN_00751080();                           // GAMEMD 0x751080

struct Obj_00401080
{
    // Three sub-objects at +0x00, +0x28 and +0x50, each initialised the same way.
    // FUNCTION: GAMEMD 0x401080
    void FUN_00401080();
};

// FUNCTION: GAMEMD 0x406E80
void __cdecl FUN_00406E80();
// FUNCTION: GAMEMD 0x406EA0
void __cdecl FUN_00406EA0();
// FUNCTION: GAMEMD 0x406EC0
void __cdecl FUN_00406EC0();
// FUNCTION: GAMEMD 0x406EE0
void __cdecl FUN_00406EE0();

struct Inner_00432C50 { char _pad[0x8]; unsigned int at8; unsigned int atC; };
struct Obj_00432C50
{
    char               _pad00[0x4];
    Inner_00432C50*    unknown_04;   // +0x0004
    char               _pad08[0x30 - 0x08];
    unsigned int       unknown_30;   // +0x0030

    // FUNCTION: GAMEMD 0x432C50
    int FUN_00432C50() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00432C50, unknown_30) == 0x30);

struct Obj_0046D330
{
    char* _vtable;      // +0x0000
    int   unknown_04;   // +0x0004

    // FUNCTION: GAMEMD 0x46D330
    Obj_0046D330* FUN_0046D330();
};

#endif  // GG_MATCH_CORE_SMALL_MISC5_METHODS_H
