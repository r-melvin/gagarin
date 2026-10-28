// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_MAP_TRIVIAL_TU050_METHODS_H
#define GG_MATCH_MAP_TRIVIAL_TU050_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Arg1_00484A80;
struct Arg1_00484A90;
struct Obj_00483610;
struct Obj_00486380;
struct Obj_004865B0;
struct Obj_00486650;
struct Obj_00486670;
struct Obj_004866D0;
struct Obj_004866F0;
struct Obj_00486710;
struct Obj_00486730;
struct Obj_00486900;
struct Obj_00487E60;
struct Obj_00487E70;

// GLOBAL: GAMEMD 0xA8E9A0
extern unsigned char DAT_00A8E9A0;
// GLOBAL: GAMEMD 0xAA0738
extern int DAT_00AA0738;
// GLOBAL: GAMEMD 0xAA0E20
extern int DAT_00AA0E20;
// GLOBAL: GAMEMD 0xAA1094
extern int DAT_00AA1094;
// GLOBAL: GAMEMD 0xAA10A4
extern int DAT_00AA10A4;
// GLOBAL: GAMEMD 0xABAD28
extern int DAT_00ABAD28;
// GLOBAL: GAMEMD 0xABBEC4
extern int DAT_00ABBEC4;
// GLOBAL: GAMEMD 0xABBEC8
extern int DAT_00ABBEC8;
// GLOBAL: GAMEMD 0xABC2B0
extern int DAT_00ABC2B0;
// GLOBAL: GAMEMD 0xABC2C8
extern int DAT_00ABC2C8;

struct Arg1_00484A80
{
    char unknown_00[0x194];
    int unknown_194;   // +0x0194
};
GG_STATIC_ASSERT(offsetof(Arg1_00484A80, unknown_194) == 0x194);

struct Arg1_00484A90
{
    char unknown_00[0x194];
    int unknown_194;   // +0x0194
};
GG_STATIC_ASSERT(offsetof(Arg1_00484A90, unknown_194) == 0x194);

struct Obj_00483610
{
    char unknown_00[0x140];
    unsigned int unknown_140;   // +0x0140
    // FUNCTION: GAMEMD 0x483610
    int FUN_00483610() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00483610, unknown_140) == 0x140);

struct Obj_00486380
{
    char unknown_00[0x38];
    int unknown_38;   // +0x0038
    // FUNCTION: GAMEMD 0x486380
    bool FUN_00486380();
};
GG_STATIC_ASSERT(offsetof(Obj_00486380, unknown_38) == 0x38);

struct Obj_004865B0
{
    char unknown_00[0x38];
    int unknown_38;   // +0x0038
    // FUNCTION: GAMEMD 0x4865B0
    bool FUN_004865B0();
};
GG_STATIC_ASSERT(offsetof(Obj_004865B0, unknown_38) == 0x38);

struct Obj_00486650
{
    char unknown_00[0x38];
    int unknown_38;   // +0x0038
    // FUNCTION: GAMEMD 0x486650
    bool FUN_00486650();
};
GG_STATIC_ASSERT(offsetof(Obj_00486650, unknown_38) == 0x38);

struct Obj_00486670
{
    char unknown_00[0x38];
    int unknown_38;   // +0x0038
    // FUNCTION: GAMEMD 0x486670
    bool FUN_00486670();
};
GG_STATIC_ASSERT(offsetof(Obj_00486670, unknown_38) == 0x38);

struct Obj_004866D0
{
    char unknown_00[0x38];
    int unknown_38;   // +0x0038
    // FUNCTION: GAMEMD 0x4866D0
    bool FUN_004866D0();
};
GG_STATIC_ASSERT(offsetof(Obj_004866D0, unknown_38) == 0x38);

struct Obj_004866F0
{
    char unknown_00[0x38];
    int unknown_38;   // +0x0038
    // FUNCTION: GAMEMD 0x4866F0
    bool FUN_004866F0();
};
GG_STATIC_ASSERT(offsetof(Obj_004866F0, unknown_38) == 0x38);

struct Obj_00486710
{
    char unknown_00[0x38];
    int unknown_38;   // +0x0038
    // FUNCTION: GAMEMD 0x486710
    bool FUN_00486710();
};
GG_STATIC_ASSERT(offsetof(Obj_00486710, unknown_38) == 0x38);

struct Obj_00486730
{
    char unknown_00[0x38];
    int unknown_38;   // +0x0038
    // FUNCTION: GAMEMD 0x486730
    bool FUN_00486730();
};
GG_STATIC_ASSERT(offsetof(Obj_00486730, unknown_38) == 0x38);

struct Obj_00486900
{
    char unknown_00[0x38];
    int unknown_38;   // +0x0038
    // FUNCTION: GAMEMD 0x486900
    unsigned char FUN_00486900();
};
GG_STATIC_ASSERT(offsetof(Obj_00486900, unknown_38) == 0x38);

struct Obj_00487E60
{
    // FUNCTION: GAMEMD 0x487E60
    int FUN_00487E60() const;
};

struct Obj_00487E70
{
    // FUNCTION: GAMEMD 0x487E70
    int FUN_00487E70() const;
};


// FUNCTION: GAMEMD 0x484A80
void __stdcall FUN_00484A80(Arg1_00484A80* a1);
// FUNCTION: GAMEMD 0x484A90
void __stdcall FUN_00484A90(Arg1_00484A90* a1);

#endif  // GG_MATCH_MAP_TRIVIAL_TU050_METHODS_H
