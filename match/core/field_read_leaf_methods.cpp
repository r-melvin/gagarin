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

struct Obj_00426A70 {
    unsigned char unknown_00[0xA0];
    unsigned short unknown_A0;
    int FUN_00426A70();
};
GG_STATIC_ASSERT(offsetof(Obj_00426A70, unknown_A0) == 0xA0);

struct Obj_00426A80 {
    unsigned char unknown_00[0xA2];
    unsigned short unknown_A2;
    int FUN_00426A80();
};
GG_STATIC_ASSERT(offsetof(Obj_00426A80, unknown_A2) == 0xA2);

struct Rec_0046C4D0 {
    unsigned char unknown_00[0x24];
    int unknown_24;
};
GG_STATIC_ASSERT(offsetof(Rec_0046C4D0, unknown_24) == 0x24);

// FUNCTION: GAMEMD 0x00426A70
int Obj_00426A70::FUN_00426A70()
{
    return unknown_A0;
}

// FUNCTION: GAMEMD 0x00426A80
int Obj_00426A80::FUN_00426A80()
{
    return unknown_A2;
}

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
