// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Every offset and argument slot read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at the address in each
//   annotation. None is bound by YRpp or the seed map, so the types and entry
//   points keep Ghidra placeholder names and the fields stay unknown_XX.
//
// Small value-type constructors and paired field writers.
//
// Three of these (0x41C230, 0x437090, 0x43A0B0) are byte-identical three-int
// constructors on three different types. They are written out longhand rather
// than shared or macro-generated - the family rule in the methodology exists
// because sibling functions that looked interchangeable have already been
// caught diverging.
//
// Argument widths come off the loads, not the RET: a `short` parameter still
// occupies four bytes of stack, so `MOV DX,[ESP+4]` with `RET 4` is one short
// argument, not two.
#ifndef GG_MATCH_CORE_SMALL_STRUCT_CTOR_METHODS_H
#define GG_MATCH_CORE_SMALL_STRUCT_CTOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0xA8ED84 — the engine frame counter.
extern int CurrentFrame;

// Two-int writers on one object, +0x08/+0x0C and +0x20/+0x24.
struct Obj_00403800
{
    char _pad00[0x8];
    int  unknown_08;    // +0x0008
    int  unknown_0C;    // +0x000C
    char _pad10[0x20 - 0x10];
    int  unknown_20;    // +0x0020
    int  unknown_24;    // +0x0024

    // FUNCTION: GAMEMD 0x4038A0
    void FUN_004038A0(int a, int b);
    // FUNCTION: GAMEMD 0x4038C0
    void FUN_004038C0(int a, int b);
};
GG_STATIC_ASSERT(offsetof(Obj_00403800, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(Obj_00403800, unknown_24) == 0x24);

// A pair of shorts, constructed in place.
struct Obj_0042D400
{
    short unknown_00;   // +0x0000
    short unknown_02;   // +0x0002

    // FUNCTION: GAMEMD 0x42D470
    Obj_0042D400(short a, short b);
};
GG_STATIC_ASSERT(offsetof(Obj_0042D400, unknown_02) == 0x02);

// Swap-setters: store the new value, hand back the old one.
struct Obj_00433C00
{
    char          _pad00[0x24];
    short         unknown_24;   // +0x0024
    char          _pad26[0x41 - 0x26];
    unsigned char unknown_41;   // +0x0041

    // FUNCTION: GAMEMD 0x433C70
    short FUN_00433C70(short value);
    // FUNCTION: GAMEMD 0x433C90
    unsigned char FUN_00433C90(unsigned char value);
};
GG_STATIC_ASSERT(offsetof(Obj_00433C00, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(Obj_00433C00, unknown_41) == 0x41);

// Three bytes, constructed in place.
struct Obj_004355B0
{
    unsigned char unknown_00;   // +0x0000
    unsigned char unknown_01;   // +0x0001
    unsigned char unknown_02;   // +0x0002

    // FUNCTION: GAMEMD 0x4355B0
    Obj_004355B0(unsigned char a, unsigned char b, unsigned char c);
};

// Three-int value types. Byte-identical constructors, distinct types.
struct Obj_0041C200
{
    int unknown_00, unknown_04, unknown_08;
    // FUNCTION: GAMEMD 0x41C230
    Obj_0041C200(int a, int b, int c);
};
struct Obj_00437000
{
    int unknown_00, unknown_04, unknown_08;
    // FUNCTION: GAMEMD 0x437090
    Obj_00437000(int a, int b, int c);
};
struct Obj_0043A000
{
    int unknown_00, unknown_04, unknown_08;
    // FUNCTION: GAMEMD 0x43A0B0
    Obj_0043A000(int a, int b, int c);
};

// Stamps the current frame alongside a caller-supplied value.
struct Obj_0046B600
{
    int  unknown_00;   // +0x0000  (frame counter at construction)
    char _pad04[0x4];
    int  unknown_08;   // +0x0008

    // FUNCTION: GAMEMD 0x46B640
    Obj_0046B600(int value);
};
GG_STATIC_ASSERT(offsetof(Obj_0046B600, unknown_08) == 0x08);

#endif  // GG_MATCH_CORE_SMALL_STRUCT_CTOR_METHODS_H
