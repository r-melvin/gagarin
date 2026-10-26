// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU100_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU100_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_005247A0;
struct Obj_005247B0;
struct Obj_005247C0;
struct Obj_00524D40;
struct Obj_00524D50;
struct Obj_00524D60;
struct Obj_00524EC0;


// FUNCTION: GAMEMD 0x711E80 (declaration)
void __cdecl FUN_00711E80();



struct Obj_005247A0
{
    // FUNCTION: GAMEMD 0x5247A0
    int FUN_005247A0() const;
};

struct Obj_005247B0
{
    // FUNCTION: GAMEMD 0x5247B0
    void FUN_005247B0();
};

struct Obj_005247C0
{
    // FUNCTION: GAMEMD 0x5247C0
    void FUN_005247C0();
    // FUNCTION: GAMEMD 0x711E90
    void FUN_00711E90();
};

struct Obj_00524D40
{
    // FUNCTION: GAMEMD 0x524D40
    int FUN_00524D40() const;
};

struct Obj_00524D50
{
    // FUNCTION: GAMEMD 0x524D50
    int FUN_00524D50() const;
};

struct Obj_00524D60
{
    char unknown_00[0xDF8];
    int unknown_DF8;   // +0x0DF8
    // FUNCTION: GAMEMD 0x524D60
    int FUN_00524D60() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00524D60, unknown_DF8) == 0xDF8);

struct Obj_00524EC0
{
    // FUNCTION: GAMEMD 0x524EC0
    Obj_00524EC0* FUN_00524EC0();
};


// FUNCTION: GAMEMD 0x523C80
void __cdecl FUN_00523C80();

#endif  // GG_MATCH_CORE_TRIVIAL_TU100_METHODS_H
