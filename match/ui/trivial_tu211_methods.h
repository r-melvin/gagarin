// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_UI_TRIVIAL_TU211_METHODS_H
#define GG_MATCH_UI_TRIVIAL_TU211_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_006A8B10;
struct Obj_006ABA20;
struct Obj_006ABAC0;

// GLOBAL: GAMEMD 0x83F92C
extern char DAT_0083F92C[];
// GLOBAL: GAMEMD 0x87F7E8
extern char DAT_0087F7E8[];
// GLOBAL: GAMEMD 0xA8B238
extern int DAT_00A8B238;
// GLOBAL: GAMEMD 0xA8ED9C
extern bool DAT_00A8ED9C;
// GLOBAL: GAMEMD 0xA8EDA0
extern int DAT_00A8EDA0;
// GLOBAL: GAMEMD 0xB07BC0
extern int DAT_00B07BC0;

// FUNCTION: GAMEMD 0x4F42F0 (declaration)
void FUN_004F42F0(void*, int, int);
// FUNCTION: GAMEMD 0x5B40B0 (declaration)
int FUN_005B40B0(void*, unsigned char);

struct Obj_006A8B10
{
    char unknown_00[0x3C];
    unsigned char unknown_3C;   // +0x003C
};
GG_STATIC_ASSERT(offsetof(Obj_006A8B10, unknown_3C) == 0x3C);

struct Obj_006ABA20
{
    char unknown_00[0x34];
    bool unknown_34;   // +0x0034
    // FUNCTION: GAMEMD 0x6ABA20
    int FUN_006ABA20();
};
GG_STATIC_ASSERT(offsetof(Obj_006ABA20, unknown_34) == 0x34);

struct Obj_006ABAC0
{
    char unknown_00[0x54];
    int unknown_54;   // +0x0054
    // FUNCTION: GAMEMD 0x6ABAC0
    bool FUN_006ABAC0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_006ABAC0, unknown_54) == 0x54);


// FUNCTION: GAMEMD 0x6A8160
int __stdcall FUN_006A8160(int a1);
// FUNCTION: GAMEMD 0x6A8B10
void FUN_006A8B10(Obj_006A8B10* a1, int a2);
// FUNCTION: GAMEMD 0x6ABC40
int __cdecl FUN_006ABC40();

#endif  // GG_MATCH_UI_TRIVIAL_TU211_METHODS_H
