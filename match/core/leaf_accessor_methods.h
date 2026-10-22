// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every offset below read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at the address in each annotation. None of
//   these addresses is bound by YRpp, so the types and the
//   entry points keep Ghidra placeholder names and the fields stay unknown_XX.
//
// Leaf accessors: single-field reads, writes and read-modify-writes. Each
// placeholder type is named for the start of the address cluster its methods
// sit in; where two entry points touch the same offset they are the getter and
// setter pair of one field and share a type.
//
// Conventions, read off the epilogues: a bare `RET` with the value already in
// EAX is a no-argument __thiscall getter; `MOV EAX,[ESP+4]; ...; RET 4` is a
// __thiscall setter taking one stack argument.
#ifndef GG_MATCH_CORE_LEAF_ACCESSOR_METHODS_H
#define GG_MATCH_CORE_LEAF_ACCESSOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// RulesClass singleton pointer @0x8871E0; only the field at +0x44 is read here.
struct RulesData
{
    char _pad00[0x44];   // +0x0000
    int  unknown_44;     // +0x0044
};
GG_STATIC_ASSERT(offsetof(RulesData, unknown_44) == 0x44);
extern RulesData* GameRules;   // GLOBAL: GAMEMD 0x8871E0

// GLOBAL: GAMEMD 0x87E728 / 0x87E89C — two singleton pointers returned raw.
extern void* DAT_0087E728;
extern void* DAT_0087E89C;

struct Obj_00402000
{
    char _pad000[0x1C - 0x0];
    int  unknown_1C;   // +0x001C
    // FUNCTION: GAMEMD 0x402030
    void* FUN_00402030();
};
GG_STATIC_ASSERT(offsetof(Obj_00402000, unknown_1C) == 0x1C);

struct Obj_00401F00
{
    char _pad000[0xC - 0x0];
    int  unknown_0C;   // +0x000C
    // FUNCTION: GAMEMD 0x401F80
    int FUN_00401F80();
    // FUNCTION: GAMEMD 0x401F90
    void FUN_00401F90();
};
GG_STATIC_ASSERT(offsetof(Obj_00401F00, unknown_0C) == 0xC);

struct Obj_00405200
{
    char _pad000[0x18 - 0x0];
    int  unknown_18;   // +0x0018
    // FUNCTION: GAMEMD 0x4052E0
    void FUN_004052E0();
};
GG_STATIC_ASSERT(offsetof(Obj_00405200, unknown_18) == 0x18);

struct Obj_004072B0
{
    char _pad000[0x8 - 0x0];
    int  unknown_08;   // +0x0008
    // FUNCTION: GAMEMD 0x4072B0
    unsigned int FUN_004072B0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_004072B0, unknown_08) == 0x8);

struct Obj_00408000
{
    char _pad000[0xC - 0x0];
    int  unknown_0C;   // +0x000C
    // FUNCTION: GAMEMD 0x408070
    int FUN_00408070() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00408000, unknown_0C) == 0xC);

struct Obj_00408600
{
    char _pad000[0x14 - 0x0];
    int  unknown_14;   // +0x0014
    // FUNCTION: GAMEMD 0x408600
    void FUN_00408600();
};
GG_STATIC_ASSERT(offsetof(Obj_00408600, unknown_14) == 0x14);

struct Obj_00408D00
{
    char _pad000[0x14 - 0x0];
    int  unknown_14;   // +0x0014
    char _pad018[0x4C - 0x18];
    int  unknown_4C;   // +0x004C
    int  unknown_50;   // +0x0050
    // FUNCTION: GAMEMD 0x408D40
    int FUN_00408D40();
    // FUNCTION: GAMEMD 0x408D50
    int FUN_00408D50() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00408D00, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(Obj_00408D00, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(Obj_00408D00, unknown_50) == 0x50);

struct Obj_00409300
{
    char _pad000[0x34 - 0x0];
    int  unknown_34;   // +0x0034
    int  unknown_38;   // +0x0038
    // FUNCTION: GAMEMD 0x409320
    int FUN_00409320();
};
GG_STATIC_ASSERT(offsetof(Obj_00409300, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(Obj_00409300, unknown_38) == 0x38);

struct Obj_00424C00
{
    char _pad000[0x17C - 0x0];
    int  unknown_17C;   // +0x017C
    int  unknown_180;   // +0x0180
    // FUNCTION: GAMEMD 0x424C90
    void FUN_00424C90(int value);
    // FUNCTION: GAMEMD 0x424CA0
    void FUN_00424CA0(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_00424C00, unknown_17C) == 0x17C);
GG_STATIC_ASSERT(offsetof(Obj_00424C00, unknown_180) == 0x180);

struct Obj_00425200
{
    char _pad000[0x19E - 0x0];
    unsigned char unknown_19E;   // +0x019E
    // FUNCTION: GAMEMD 0x425260
    void FUN_00425260();
    // FUNCTION: GAMEMD 0x425270
    void FUN_00425270();
};
GG_STATIC_ASSERT(offsetof(Obj_00425200, unknown_19E) == 0x19E);

struct Obj_00465D00
{
    char _pad000[0xEDC - 0x0];
    int  unknown_EDC;   // +0x0EDC
    // FUNCTION: GAMEMD 0x465D70
    int FUN_00465D70() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00465D00, unknown_EDC) == 0xEDC);

struct Obj_0046B200
{
    char _pad000[0x130 - 0x0];
    int  unknown_130;   // +0x0130
    // FUNCTION: GAMEMD 0x46B260
    void FUN_0046B260(int value);
    // FUNCTION: GAMEMD 0x46B270
    int FUN_0046B270() const;
};
GG_STATIC_ASSERT(offsetof(Obj_0046B200, unknown_130) == 0x130);

struct Obj_00473400
{
    char _pad000[0x4 - 0x0];
    int  unknown_04;   // +0x0004
    // FUNCTION: GAMEMD 0x473450
    int FUN_00473450() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00473400, unknown_04) == 0x4);

// Free leaves: two raw singleton reads and one rules-field read.
void* __cdecl FUN_00407010();   // FUNCTION: GAMEMD 0x407010
void* __cdecl FUN_0040A7A0();   // FUNCTION: GAMEMD 0x40A7A0
int   __cdecl FUN_00417FD0();   // FUNCTION: GAMEMD 0x417FD0

#endif  // GG_MATCH_CORE_LEAF_ACCESSOR_METHODS_H
