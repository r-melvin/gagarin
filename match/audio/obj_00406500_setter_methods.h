// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x406520 / 0x406530 / 0x406540 / 0x4065C0 / 0x4065D0 /
//   0x4065E0 / 0x406640. No YRpp or seed-map binding covers any of them.
//
// A family of one-instruction field setters clustered at 0x4065xx, all on the
// same object. Nothing names the type, so both it and the seven entry points
// keep Ghidra placeholder names and the fields are `unknown_XX` — a legitimate
// layout primitive here, not a gap to be filled by guesswork.
//
// Calling convention: `MOV [ECX+off],EDX; RET` with no stack adjustment. The
// value arrives in EDX, which __thiscall never does — that is __fastcall, with
// the object in ECX and the value in EDX.
#ifndef GG_MATCH_AUDIO_OBJ_00406500_SETTER_METHODS_H
#define GG_MATCH_AUDIO_OBJ_00406500_SETTER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00406500
{
    char _pad000[0x14];        // +0x0000
    int  unknown_14;           // +0x0014
    char _pad018[0x40 - 0x18]; // +0x0018
    int  unknown_40;           // +0x0040
    char _pad044[0x48 - 0x44]; // +0x0044
    int  unknown_48;           // +0x0048
    int  unknown_4C;           // +0x004C
    int  unknown_50;           // +0x0050
    char _pad054[0x138 - 0x54];// +0x0054
    int  unknown_138;          // +0x0138
    int  unknown_13C;          // +0x013C

    // The setters are members, not free functions taking the object: retail
    // puts the object in ECX and the value in EDX, which is `__fastcall` on a
    // member. A plain __thiscall member would push the value and return
    // `RET 4`, so the convention is kept. Declared ascending by retail address.
    // FUNCTION: GAMEMD 0x406520
    void __fastcall FUN_00406520(int value);
    // FUNCTION: GAMEMD 0x406530
    void __fastcall FUN_00406530(int value);
    // FUNCTION: GAMEMD 0x406540
    void __fastcall FUN_00406540(int value);
    // FUNCTION: GAMEMD 0x4065C0
    void __fastcall FUN_004065C0(int value);
    // FUNCTION: GAMEMD 0x4065D0
    void __fastcall FUN_004065D0(int value);
    // FUNCTION: GAMEMD 0x4065E0
    void __fastcall FUN_004065E0(int value);
    // FUNCTION: GAMEMD 0x406640
    void __fastcall FUN_00406640(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_00406500, unknown_14)  == 0x14);
GG_STATIC_ASSERT(offsetof(Obj_00406500, unknown_40)  == 0x40);
GG_STATIC_ASSERT(offsetof(Obj_00406500, unknown_48)  == 0x48);
GG_STATIC_ASSERT(offsetof(Obj_00406500, unknown_4C)  == 0x4C);
GG_STATIC_ASSERT(offsetof(Obj_00406500, unknown_50)  == 0x50);
GG_STATIC_ASSERT(offsetof(Obj_00406500, unknown_138) == 0x138);
GG_STATIC_ASSERT(offsetof(Obj_00406500, unknown_13C) == 0x13C);


#endif  // GG_MATCH_AUDIO_OBJ_00406500_SETTER_METHODS_H
