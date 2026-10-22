// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp.
#ifndef GG_MATCH_CORE_SMALL_MISC21_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC21_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "guarded_forward_methods.h"

// GLOBAL: GAMEMD 0x87E728
extern void* DAT_0087E728c;
bool __cdecl    FUN_0053BAD0();                        // GAMEMD 0x53BAD0
void __fastcall FUN_00403770b(void* self, int arg);    // GAMEMD 0x403770
void __cdecl    FUN_00404FD0b();                       // GAMEMD 0x404FD0
void __cdecl    FUN_00751040b();                       // GAMEMD 0x751040
void __cdecl    FUN_007535B0();                        // GAMEMD 0x7535B0
void __cdecl    FUN_00753500();                        // GAMEMD 0x753500

// FUNCTION: GAMEMD 0x406F00 — the shutdown path. The probe gates the first
// three steps only.
void __cdecl FUN_00406F00();

// Twelve bytes, so returned through a caller-supplied pointer whatever the
// special members are.
struct Triple3ib
{
    int a, b, c;

    // FUNCTION: GAMEMD 0x437160
    Triple3ib FUN_00437160(const Triple3ib* other) const;
};

struct Holder_0040A610 { char _pad[0x64]; IFace* at64; };
struct Obj_0040A610;
typedef void (__fastcall* NotifyFn)(Obj_0040A610*);

struct Obj_0040A610
{
    char                _pad000[0xA4];
    int                 Flags;        // +0x00A4
    char                _padA8[0x158 - 0xA8];
    Holder_0040A610*    unknown_158;  // +0x0158
    char                _pad15C[0x164 - 0x15C];
    NotifyFn            unknown_164;  // +0x0164

    // FUNCTION: GAMEMD 0x40A610
    int FUN_0040A610();
};
GG_STATIC_ASSERT(offsetof(Obj_0040A610, Flags) == 0xA4);
GG_STATIC_ASSERT(offsetof(Obj_0040A610, unknown_164) == 0x164);

#endif  // GG_MATCH_CORE_SMALL_MISC21_METHODS_H
