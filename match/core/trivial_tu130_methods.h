// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU130_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU130_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Gbl_00ABE890;
struct Obj_00597D40;
struct Obj_00597F80;
struct Obj_00597FA0;
struct Obj_00597FC0;
struct Obj_00597FE0;
struct Obj_005A9C20;

// GLOBAL: GAMEMD 0x82BA48
extern char DAT_0082BA48[];
// GLOBAL: GAMEMD 0x82BC3C
extern char DAT_0082BC3C[];
// GLOBAL: GAMEMD 0x82BC4C
extern char DAT_0082BC4C[];
// GLOBAL: GAMEMD 0x82BC5C
extern char DAT_0082BC5C[];
// GLOBAL: GAMEMD 0x82BC70
extern char DAT_0082BC70[];
// GLOBAL: GAMEMD 0xABDFD0
extern int DAT_00ABDFD0;
// GLOBAL: GAMEMD 0xABDFD4
extern int DAT_00ABDFD4;
// GLOBAL: GAMEMD 0xABDFD8
extern char DAT_00ABDFD8[];
// GLOBAL: GAMEMD 0xABE890
extern Gbl_00ABE890 DAT_00ABE890;
// GLOBAL: GAMEMD 0xABEC90
extern int DAT_00ABEC90;
// GLOBAL: GAMEMD 0xABECD0
extern int DAT_00ABECD0;

// FUNCTION: GAMEMD 0x5958E0 (declaration)
void FUN_005958E0(void*, int);
// FUNCTION: GAMEMD 0x5A9C40 (declaration)
void FUN_005A9C40(Obj_005A9C20*, int);
// FUNCTION: GAMEMD 0x734E60 (declaration)
void FUN_00734E60(void*, int, void*, int);
// FUNCTION: GAMEMD 0x7C978A (declaration)
void __cdecl FUN_007C978A(int);

struct Gbl_00ABE890
{
    // FUNCTION: GAMEMD 0x65C6D0
    void FUN_0065C6D0(int);
    // FUNCTION: GAMEMD 0x65C780 (declaration) -- the raw 32-bit draw.
    unsigned int FUN_0065C780();
};

struct Obj_00597D40
{
    // FUNCTION: GAMEMD 0x558840
    void FUN_00558840();
    // FUNCTION: GAMEMD 0x597D40
    void FUN_00597D40();
};

struct Obj_00597F80
{
    // FUNCTION: GAMEMD 0x597F80
    void FUN_00597F80();
};

struct Obj_00597FA0
{
    // FUNCTION: GAMEMD 0x597FA0
    void FUN_00597FA0();
};

struct Obj_00597FC0
{
    // FUNCTION: GAMEMD 0x597FC0
    void FUN_00597FC0();
};

struct Obj_00597FE0
{
    // FUNCTION: GAMEMD 0x597FE0
    void FUN_00597FE0();
};

struct Obj_005A9C20
{
};


// FUNCTION: GAMEMD 0x58B760
void FUN_0058B760(int a1, int a2);
// FUNCTION: GAMEMD 0x58B770
void __cdecl FUN_0058B770();
// FUNCTION: GAMEMD 0x58B7B0
void __cdecl FUN_0058B7B0();
// FUNCTION: GAMEMD 0x58B7C0
void __cdecl FUN_0058B7C0();
// FUNCTION: GAMEMD 0x58B7E0
int __cdecl FUN_0058B7E0();
// FUNCTION: GAMEMD 0x58B7F0
int __cdecl FUN_0058B7F0();
// FUNCTION: GAMEMD 0x58B800
int __cdecl FUN_0058B800();
// FUNCTION: GAMEMD 0x58B810
int __cdecl FUN_0058B810();
// FUNCTION: GAMEMD 0x58BCD0
int FUN_0058BCD0(int a1);
// FUNCTION: GAMEMD 0x58BD20
int FUN_0058BD20(int a1);
// FUNCTION: GAMEMD 0x58BD40
int FUN_0058BD40(int a1);
// FUNCTION: GAMEMD 0x58BD60
int FUN_0058BD60(int a1);
// FUNCTION: GAMEMD 0x5A9C20
void FUN_005A9C20(Obj_005A9C20* a1, int a2);

#endif  // GG_MATCH_CORE_TRIVIAL_TU130_METHODS_H
