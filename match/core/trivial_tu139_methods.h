// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI; every name is a placeholder
//   (FUN_/DAT_/unknown_) derived from an address or offset in that binary.
#ifndef GG_MATCH_CORE_TRIVIAL_TU139_METHODS_H
#define GG_MATCH_CORE_TRIVIAL_TU139_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_005BCC30;
struct Obj_005BCCE0;
struct Obj_005BCD70;

// GLOBAL: GAMEMD 0xABF23A
extern unsigned char DAT_00ABF23A;
// GLOBAL: GAMEMD 0xABF23C
extern int DAT_00ABF23C;

struct Obj_005BCC30
{
    char unknown_00[0x2718];
    int unknown_2718;   // +0x2718
    // FUNCTION: GAMEMD 0x5BCC30
    int FUN_005BCC30() const;
};
GG_STATIC_ASSERT(offsetof(Obj_005BCC30, unknown_2718) == 0x2718);

struct Obj_005BCCE0
{
    char unknown_00[0x2734];
    unsigned char unknown_2734;   // +0x2734
    // FUNCTION: GAMEMD 0x5BCCE0
    unsigned char FUN_005BCCE0() const;
};
GG_STATIC_ASSERT(offsetof(Obj_005BCCE0, unknown_2734) == 0x2734);

struct Obj_005BCD70
{
    char unknown_00[0x2710];
    int unknown_2710;   // +0x2710
    // FUNCTION: GAMEMD 0x5BCD70
    void FUN_005BCD70(int a1);
};
GG_STATIC_ASSERT(offsetof(Obj_005BCD70, unknown_2710) == 0x2710);


// FUNCTION: GAMEMD 0x5BC440
int __cdecl FUN_005BC440();
// FUNCTION: GAMEMD 0x5BCC20
void __cdecl FUN_005BCC20();

#endif  // GG_MATCH_CORE_TRIVIAL_TU139_METHODS_H
