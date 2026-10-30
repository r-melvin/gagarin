// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Field reads and bounded record lookups whose body repeats at two or more
// retail addresses. Each address is compiled and checked on its own; the
// copies differ in the field offset or in the global table they index. Owners
// that are not modelled elsewhere are placeholders `Obj_<ADDR>` / `Rec_<ADDR>`
// declaring only what the body touches, with offset asserts.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/rec_0046c4d0.h"

extern int DAT_00889F64;
extern Rec_0046C4D0** DAT_008B4154;
extern unsigned int DAT_008B4160;
// FUNCTION: GAMEMD 0x00427C90
int* FUN_00427C90(unsigned int index)
{
    if (index > DAT_008B4160)
        return &DAT_00889F64;
    return &DAT_008B4154[index]->unknown_24;
}

extern Rec_0046C4D0** DAT_00A83D9C;
extern unsigned int DAT_00A83DA8;

extern Rec_0046C4D0** DAT_00A8EB2C;
extern unsigned int DAT_00A8EB38;
// FUNCTION: GAMEMD 0x0074B620
int* FUN_0074B620(unsigned int index)
{
    if (index > DAT_00A8EB38)
        return &DAT_00889F64;
    return &DAT_00A8EB2C[index]->unknown_24;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x889F64
int DAT_00889F64;
// GLOBAL: GAMEMD 0x8B4154
Rec_0046C4D0** DAT_008B4154;
// GLOBAL: GAMEMD 0x8B4160
unsigned int DAT_008B4160;
// GLOBAL: GAMEMD 0xA8EB2C
Rec_0046C4D0** DAT_00A8EB2C;
// GLOBAL: GAMEMD 0xA8EB38
unsigned int DAT_00A8EB38;
// END defined globals
