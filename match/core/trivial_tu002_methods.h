// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU002_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU002_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Gbl_0087E8A8;
struct Obj_00407060;
struct Obj_00407090;
struct Obj_00407F80;
struct Obj_004080A0;
struct Obj_00408EB0;
struct Obj_00408EC0;
struct Obj_00408ED0;
struct Obj_004090F0;
struct Obj_00409330;

// GLOBAL: GAMEMD 0x87E728
extern int DAT_0087E728;
// GLOBAL: GAMEMD 0x87E8A8
extern Gbl_0087E8A8 DAT_0087E8A8;

// FUNCTION: GAMEMD 0x4033C0 (declaration)
void FUN_004033C0(int, int);
// FUNCTION: GAMEMD 0x407170 (declaration)
void FUN_00407170(Obj_00407060*, int);

struct Gbl_0087E8A8
{
    // FUNCTION: GAMEMD 0x420130
    void FUN_00420130();
};

struct Obj_00407060
{
    // FUNCTION: GAMEMD 0x407060
    void FUN_00407060();
};

struct Obj_00407090
{
    char unknown_00[0x4];
    int unknown_04;   // +0x0004
    int unknown_08;   // +0x0008
    // FUNCTION: GAMEMD 0x407090
    int FUN_00407090() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00407090, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Obj_00407090, unknown_08) == 0x8);

struct Obj_00407F80
{
    char unknown_00[0x88];
    int unknown_88;   // +0x0088
    // FUNCTION: GAMEMD 0x407F80
    int FUN_00407F80();
};
GG_STATIC_ASSERT(offsetof(Obj_00407F80, unknown_88) == 0x88);

struct Obj_004080A0
{
    char unknown_00[0xA4];
    int unknown_A4;   // +0x00A4
    // FUNCTION: GAMEMD 0x4080A0
    int* FUN_004080A0();
};
GG_STATIC_ASSERT(offsetof(Obj_004080A0, unknown_A4) == 0xA4);

struct Obj_00408EB0
{
    char unknown_00[0x18];
    int unknown_18;   // +0x0018
};
GG_STATIC_ASSERT(offsetof(Obj_00408EB0, unknown_18) == 0x18);

struct Obj_00408EC0
{
    char unknown_00[0x18];
    int unknown_18;   // +0x0018
    // FUNCTION: GAMEMD 0x408EC0
    int FUN_00408EC0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00408EC0, unknown_18) == 0x18);

struct Obj_00408ED0
{
    char unknown_00[0x14];
    int unknown_14;   // +0x0014
    // FUNCTION: GAMEMD 0x408ED0
    int FUN_00408ED0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00408ED0, unknown_14) == 0x14);

struct Obj_004090F0
{
    char unknown_00[0x24];
    int unknown_24;   // +0x0024
    // FUNCTION: GAMEMD 0x4090F0
    int FUN_004090F0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_004090F0, unknown_24) == 0x24);

struct Obj_00409330
{
    char unknown_00[0x30];
    int unknown_30;   // +0x0030
    // FUNCTION: GAMEMD 0x409330
    int FUN_00409330() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00409330, unknown_30) == 0x30);


// FUNCTION: GAMEMD 0x406E60
void FUN_00406E60(int a1, int a2);
// FUNCTION: GAMEMD 0x408EB0
int FUN_00408EB0(Obj_00408EB0* a1, int a2);
// FUNCTION: GAMEMD 0x40AD80
void __cdecl FUN_0040AD80();

#endif  // GG_MATCH_CORE_TRIVIAL_TU002_METHODS_H
