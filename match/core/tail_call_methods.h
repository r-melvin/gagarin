// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp or the
//   seed map.
//
// Forwarders that end in JMP rather than CALL/RET.
//
// CORRECTION: these were previously left aside on the claim that VC6 does not
// emit tail-call jumps from ordinary source. That was asserted, not measured,
// and it is false — at /O2 a call in tail position whose result is discarded
// (or passed straight through) becomes a JMP, including after adjusting ECX.
// A three-line probe reproduced `ADD ECX,8; JMP` and
// `MOV ECX,[ECX+0x14]; XOR EDX,EDX; ADD ECX,0x10; JMP` exactly.
#ifndef GG_MATCH_CORE_TAIL_CALL_METHODS_H
#define GG_MATCH_CORE_TAIL_CALL_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Declared-only callees.
void  __fastcall FUN_00407170(void* self, int arg);   // GAMEMD 0x407170
void* __fastcall FUN_00407470(void* self);            // GAMEMD 0x407470
void  __fastcall FUN_004072C0b(void* self);           // GAMEMD 0x4072C0

// A dispatch table of __thiscall slots hung off +0xD4.
struct Obj_00402600;
typedef void (__fastcall* Slot)(Obj_00402600*);
struct Obj_00402600
{
    char  _pad000[0xD4];
    char* Dispatch;   // +0x00D4

    // FUNCTION: GAMEMD 0x4026A0
    void FUN_004026A0();
    // FUNCTION: GAMEMD 0x4026B0
    void FUN_004026B0();
};
GG_STATIC_ASSERT(offsetof(Obj_00402600, Dispatch) == 0xD4);

// A function pointer stored directly in the object at +0x10C.
struct Obj_00403800b;
typedef void (__fastcall* SelfFn)(Obj_00403800b*);
struct Obj_00403800b
{
    char   _pad000[0x10C];
    SelfFn Handler;   // +0x010C

    // FUNCTION: GAMEMD 0x403810
    void FUN_00403810();
};
GG_STATIC_ASSERT(offsetof(Obj_00403800b, Handler) == 0x10C);

// FUNCTION: GAMEMD 0x407070
void __fastcall FUN_00407070(void* self);

struct Obj_00408000b
{
    char  _pad00[0x14];
    char* unknown_14;   // +0x0014

    // FUNCTION: GAMEMD 0x4080C0
    void FUN_004080C0();
};
GG_STATIC_ASSERT(offsetof(Obj_00408000b, unknown_14) == 0x14);

struct Obj_00408500b
{
    int  unknown_00;   // +0x0000
    int  unknown_04;   // +0x0004
    char _pad08[0x14 - 0x08];
    int  unknown_14;   // +0x0014
    int  unknown_18;   // +0x0018

    // FUNCTION: GAMEMD 0x408520
    void FUN_00408520();
    // FUNCTION: GAMEMD 0x4084E0
    void FUN_004084E0();
};
GG_STATIC_ASSERT(offsetof(Obj_00408500b, unknown_18) == 0x18);

#endif  // GG_MATCH_CORE_TAIL_CALL_METHODS_H
