// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_MOVEMENT_TRIVIAL_TU258_METHODS_H
#define GG_MATCH_MOVEMENT_TRIVIAL_TU258_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00740E50;
struct Obj_00740EE0;
struct Obj_00741490;
struct Obj_007447A0;
struct Obj_00746400;
struct Obj_00746400_6C4;
struct Obj_00746CB0;
struct Obj_00746CC0;
struct Obj_00746D00;
struct Obj_00746D00_6C4;
struct Obj_00746D60;
struct Obj_00746D80;
struct Obj_00746D90;
struct Obj_00746DD0;
struct Obj_00746E20;

// FUNCTION: GAMEMD 0x4D4DC0 (declaration)
void FUN_004D4DC0(Obj_007447A0*, int);
// FUNCTION: GAMEMD 0x707D20 (declaration)
void FUN_00707D20(Obj_00740EE0*, int);
// FUNCTION: GAMEMD 0x708C30 (declaration)
void FUN_00708C30(Obj_00740E50*, int);
// FUNCTION: GAMEMD 0x70F070 (declaration)
void FUN_0070F070(Obj_00746CB0*, int);
// FUNCTION: GAMEMD 0x70F090 (declaration)
void FUN_0070F090(Obj_00746CC0*, int);
// FUNCTION: GAMEMD 0x738680 (declaration)
void FUN_00738680(Obj_00746D60*, int);

struct Obj_00740E50
{
};

struct Obj_00740EE0
{
};

struct Obj_00741490
{
    char unknown_00[0x6C4];
    int unknown_6C4;   // +0x06C4
    // FUNCTION: GAMEMD 0x741490
    int FUN_00741490() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00741490, unknown_6C4) == 0x6C4);

struct Obj_007447A0
{
};

struct Obj_00746400
{
    char unknown_00[0x6C4];
    Obj_00746400_6C4* unknown_6C4;   // +0x06C4
    // FUNCTION: GAMEMD 0x746400
    unsigned char FUN_00746400() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00746400, unknown_6C4) == 0x6C4);

struct Obj_00746400_6C4
{
    char unknown_00[0xE1B];
    unsigned char unknown_E1B;   // +0x0E1B
};
GG_STATIC_ASSERT(offsetof(Obj_00746400_6C4, unknown_E1B) == 0xE1B);

struct Obj_00746CB0
{
};

struct Obj_00746CC0
{
};

struct Obj_00746D00
{
    char unknown_00[0x6C4];
    Obj_00746D00_6C4* unknown_6C4;   // +0x06C4
    // FUNCTION: GAMEMD 0x746D00
    unsigned char FUN_00746D00() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00746D00, unknown_6C4) == 0x6C4);

struct Obj_00746D00_6C4
{
    char unknown_00[0x6AC];
    unsigned char unknown_6AC;   // +0x06AC
};
GG_STATIC_ASSERT(offsetof(Obj_00746D00_6C4, unknown_6AC) == 0x6AC);

struct Obj_00746D60
{
    // FUNCTION: GAMEMD 0x710460
    void FUN_00710460();
};

struct Obj_00746D80
{
    char unknown_00[0x6E0];
    unsigned char unknown_6E0;   // +0x06E0
    // FUNCTION: GAMEMD 0x746D80
    unsigned char FUN_00746D80() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00746D80, unknown_6E0) == 0x6E0);

struct Obj_00746D90
{
    char unknown_00[0x6E0];
    bool unknown_6E0;   // +0x06E0
    bool unknown_6E1;   // +0x06E1
    // FUNCTION: GAMEMD 0x746D90
    int FUN_00746D90();
};
GG_STATIC_ASSERT(offsetof(Obj_00746D90, unknown_6E0) == 0x6E0);
GG_STATIC_ASSERT(offsetof(Obj_00746D90, unknown_6E1) == 0x6E1);

struct Obj_00746DD0
{
    // FUNCTION: GAMEMD 0x746DD0
    int FUN_00746DD0() const;
};

struct Obj_00746E20
{
    // FUNCTION: GAMEMD 0x746E20
    int FUN_00746E20() const;
};


// FUNCTION: GAMEMD 0x7393B0
void __cdecl FUN_007393B0();
// FUNCTION: GAMEMD 0x740E50
void FUN_00740E50(Obj_00740E50* a1, int a2);
// FUNCTION: GAMEMD 0x740EE0
void FUN_00740EE0(Obj_00740EE0* a1, int a2);
// FUNCTION: GAMEMD 0x7447A0
void FUN_007447A0(Obj_007447A0* a1, int a2);
// FUNCTION: GAMEMD 0x746CB0
void FUN_00746CB0(Obj_00746CB0* a1, int a2);
// FUNCTION: GAMEMD 0x746CC0
void FUN_00746CC0(Obj_00746CC0* a1, int a2);
// FUNCTION: GAMEMD 0x746D60
void FUN_00746D60(Obj_00746D60* a1, int a2);

#endif  // GG_MATCH_MOVEMENT_TRIVIAL_TU258_METHODS_H
