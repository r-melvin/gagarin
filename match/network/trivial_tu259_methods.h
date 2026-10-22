// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_NETWORK_TRIVIAL_TU259_METHODS_H
#define GG_MATCH_NETWORK_TRIVIAL_TU259_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Gptr_008871E0;
struct Obj_007473C0;
struct Obj_007473D0;
struct Obj_00747F20;
struct Obj_00748160;
struct Obj_00748170;
struct Obj_00748180;

// GLOBAL: GAMEMD 0x8871E0
extern Gptr_008871E0* DAT_008871E0;

// FUNCTION: GAMEMD 0x711E80 (declaration)
void __cdecl FUN_00711E80();

struct Gptr_008871E0
{
    char unknown_00[0x16CC];
    int unknown_16CC;   // +0x16CC
};
GG_STATIC_ASSERT(offsetof(Gptr_008871E0, unknown_16CC) == 0x16CC);

struct Obj_007473C0
{
    // FUNCTION: GAMEMD 0x7473C0
    void FUN_007473C0();
};

struct Obj_007473D0
{
    // FUNCTION: GAMEMD 0x711E90
    void FUN_00711E90();
    // FUNCTION: GAMEMD 0x7473D0
    void FUN_007473D0();
};

struct Obj_00747F20
{
    // FUNCTION: GAMEMD 0x747F20
    int FUN_00747F20() const;
};

struct Obj_00748160
{
    // FUNCTION: GAMEMD 0x748160
    int FUN_00748160() const;
};

struct Obj_00748170
{
    // FUNCTION: GAMEMD 0x748170
    int FUN_00748170() const;
};

struct Obj_00748180
{
    char unknown_00[0xDF8];
    int unknown_DF8;   // +0x0DF8
    // FUNCTION: GAMEMD 0x748180
    int FUN_00748180() const;
};
GG_STATIC_ASSERT(offsetof(Obj_00748180, unknown_DF8) == 0xDF8);



#endif  // GG_MATCH_NETWORK_TRIVIAL_TU259_METHODS_H
