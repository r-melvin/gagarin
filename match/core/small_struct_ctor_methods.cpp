// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes compared against retail gamemd.exe v1.001 at each address below.
//
// Small value-type constructors and paired field writers, ordered ascending by
// retail address.

#include "small_struct_ctor_methods.h"
#include "../_layout/coord_struct.h"

// Both writers: retail interleaves load-store-load-store, which is what the
// volatile declarations give (the stream threads read these words; see the
// header). Plain fields would let VC6 hoist both loads ahead of both stores.
// FUNCTION: GAMEMD 0x4038A0
void Obj_00403800::FUN_004038A0(int a, int b)
{
    unknown_08 = a;
    unknown_0C = b;
}

// FUNCTION: GAMEMD 0x4038C0
void Obj_00403800::FUN_004038C0(int a, int b)
{
    unknown_20 = a;
    unknown_24 = b;
}

// FUNCTION: GAMEMD 0x41C230
Obj_0041C200::Obj_0041C200(int a, int b, int c)
{
    unknown_00 = a;
    unknown_04 = b;
    unknown_08 = c;
}

// FUNCTION: GAMEMD 0x42D470
Obj_0042D400::Obj_0042D400(short a, short b)
{
    unknown_00 = a;
    unknown_02 = b;
}

// FUNCTION: GAMEMD 0x433C70
short Obj_00433C00::FUN_00433C70(short value)
{
    short previous = unknown_24;
    unknown_24 = value;
    return previous;
}

// FUNCTION: GAMEMD 0x433C90
unsigned char Obj_00433C00::FUN_00433C90(unsigned char value)
{
    unsigned char previous = unknown_41;
    unknown_41 = value;
    return previous;
}

// FUNCTION: GAMEMD 0x4355B0
Obj_004355B0::Obj_004355B0(unsigned char a, unsigned char b, unsigned char c)
{
    unknown_00 = a;
    unknown_01 = b;
    unknown_02 = c;
}

// FUNCTION: GAMEMD 0x437090
CoordStruct* CoordStruct::FUN_00437090(int a, int b, int c)
{
    X = a;
    Y = b;
    Z = c;
    return this;
}

// FUNCTION: GAMEMD 0x43A0B0
Obj_0043A000::Obj_0043A000(int a, int b, int c)
{
    unknown_00 = a;
    unknown_04 = b;
    unknown_08 = c;
}

// FUNCTION: GAMEMD 0x46B640
Obj_0046B600::Obj_0046B600(int value)
{
    unknown_00 = CurrentFrame;
    unknown_08 = value;
}
