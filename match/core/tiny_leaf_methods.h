// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp,
//   so all keep placeholder names.
//
// The remaining one- and two-instruction leaves, grouped by shape because each
// has nothing to model on its own.
//
// Conventions read off the epilogues: bare RET with a value in EDX is a
// __fastcall member (first argument in EDX); RET 4 with the value at [ESP+4] is
// a __thiscall member; bare RET with neither is a no-argument function.
#ifndef GG_MATCH_CORE_TINY_LEAF_METHODS_H
#define GG_MATCH_CORE_TINY_LEAF_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void __cdecl FUN_007C8B3D(void* block);

// Six do-nothing functions. They are real entry points - almost certainly
// virtual overrides that deliberately do nothing - not padding.
void __cdecl FUN_004068E0();   // FUNCTION: GAMEMD 0x4068E0
void __cdecl FUN_00408530();   // FUNCTION: GAMEMD 0x408530
void __cdecl FUN_0040D300();   // FUNCTION: GAMEMD 0x40D300
void __cdecl FUN_00454CE0();   // FUNCTION: GAMEMD 0x454CE0
void __cdecl FUN_0045E750();   // FUNCTION: GAMEMD 0x45E750
void __cdecl FUN_00465CB0();   // FUNCTION: GAMEMD 0x465CB0

// `MOV EAX,[ECX+0x20]; MOV EDX,[ECX+0x24]; RET` with no hidden pointer is a
// 64-bit integer return, not a two-int struct: an eight-byte struct goes back
// through a caller-supplied pointer and would show `RET 4`. The two loads are
// just a little-endian __int64 read of the pair.
struct Obj_00408100
{
    char _pad00[0x20];
    int  unknown_20;   // +0x0020
    int  unknown_24;   // +0x0024

    // FUNCTION: GAMEMD 0x408140
    __int64 FUN_00408140() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00408100, unknown_24) == 0x24);

// FUNCTION: GAMEMD 0x407510 — hands itself to the deallocator.
void __fastcall FUN_00407510(void* self);

// A three-word head closed onto itself: an empty circular list.
struct ListHead3
{
    void* a;   // +0x0000
    void* b;   // +0x0004
    void* c;   // +0x0008

    // FUNCTION: GAMEMD 0x4072C0
    void FUN_004072C0();
};

// Free-list push. The block is handed over payload-first, so the link word
// sits eight bytes below it.
struct FreeHead2 { void* First; };
void __fastcall FUN_00407530(FreeHead2* head, void* payload);   // FUNCTION: GAMEMD 0x407530

struct Obj_00406500b
{
    char _pad00[0x54];
    int  unknown_54;   // +0x0054
    int  unknown_58;   // +0x0058
    int  unknown_5C;   // +0x005C
    int  unknown_60;   // +0x0060
    int  unknown_64;   // +0x0064

    // FUNCTION: GAMEMD 0x4065F0
    void FUN_004065F0(int value);
    // FUNCTION: GAMEMD 0x406600
    void __fastcall FUN_00406600(int a, int b);
    // FUNCTION: GAMEMD 0x406610
    void __fastcall FUN_00406610(int a, int b);
};
GG_STATIC_ASSERT(offsetof(Obj_00406500b, unknown_54) == 0x54);
GG_STATIC_ASSERT(offsetof(Obj_00406500b, unknown_64) == 0x64);

struct Target_00407B00 { char _pad[0x94]; int at94; int at98; int at9C; };
struct Obj_00407B00
{
    char _pad00[0x14];
    Target_00407B00* unknown_14;   // +0x0014

    // FUNCTION: GAMEMD 0x407B40
    void __fastcall FUN_00407B40(int value);
    // FUNCTION: GAMEMD 0x407B50
    void __fastcall FUN_00407B50(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_00407B00, unknown_14) == 0x14);

struct Obj_00410200 { char _pad00[0xC]; int unknown_0C; };
int __stdcall FUN_00410220(Obj_00410200* obj);   // FUNCTION: GAMEMD 0x410220

struct Obj_00434100
{
    char _pad00[0x20];
    int  unknown_20;   // +0x0020

    // FUNCTION: GAMEMD 0x434110
    void FUN_00434110(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_00434100, unknown_20) == 0x20);

#endif  // GG_MATCH_CORE_TINY_LEAF_METHODS_H
