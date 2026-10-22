// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   RTTI: TypeDescriptor 0x0081FF08 `.?AVDial8Class@@`; class hierarchy descriptor 0x007FFA98.
//   Bases in RTTI (declaration) order: ControlClass +0x0.
// VTABLE: GAMEMD 0x7E5E3C (34 slots)
//   Virtual slots are named vf_<slot>; the binary attests no names. Argument counts come from each target's RET n;
//   return types are not recovered (void placeholder). Member offsets come from the constructor 0x4A53B0: the
//   face centre (+0x2C/+0x30), two rings of eight compass points (+0x34, +0x74), the direction and its facing.
#ifndef GG_MATCH_LAYOUT_DIAL8_CLASS_H
#define GG_MATCH_LAYOUT_DIAL8_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../ui/control_class.h"

struct DialPoint
{
    int X;   // +0x0
    int Y;   // +0x4
};

class Dial8Class : public ControlClass
{
public:
    Dial8Class(int id, int x, int y, int width, int height, int direction);

    // 0  0x4A59A0: deleting destructor; no destructor of its own is attested (calls the base destructor 0x4E1390 directly)
    virtual int Draw(int forced);                               // 27  0x4A57B0: override of ControlClass
    virtual int Action(unsigned flags, unsigned* key, int modifier);// 31  0x4A5660: override of ControlClass

    int       unknown_2C;      // +0x2C store at 0x4A53EF
    int       unknown_30;      // +0x30 store at 0x4A53FF
    DialPoint OuterPoint[8];   // +0x34 first point stored at 0x4A5436
    DialPoint InnerPoint[8];   // +0x74 first point stored at 0x4A54B8
    int       Direction;       // +0xB4 store at 0x4A5408
    int       Facing;          // +0xB8 store at 0x4A5420
    int       unknown_BC;      // +0xBC store at 0x4A5426
};
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(Dial8Class, OuterPoint) == 0x34);
GG_STATIC_ASSERT(offsetof(Dial8Class, InnerPoint) == 0x74);
GG_STATIC_ASSERT(offsetof(Dial8Class, Direction) == 0xB4);
GG_STATIC_ASSERT(offsetof(Dial8Class, Facing) == 0xB8);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_BC) == 0xBC);

#endif  // GG_MATCH_LAYOUT_DIAL8_CLASS_H
