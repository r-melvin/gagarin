// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI: TypeDescriptor 0x0081FF08 `.?AVDial8Class@@`; class hierarchy descriptor 0x007FFA98.
//   Bases in RTTI (declaration) order: ControlClass +0x0.
//   vtable 0x7E5E3C (34 slots) (VTABLE marker already carried by match/ui/direction_dial_ctor_methods.cpp)
//   Virtual slots are named vf_<slot>; the binary attests no names. Argument counts come from each target's RET n;
//   return types are not recovered (void placeholder). Member offsets come from constructor stores only.
#ifndef GG_MATCH_LAYOUT_DIAL8_CLASS_H
#define GG_MATCH_LAYOUT_DIAL8_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../ui/control_class.h"

class Dial8Class : public ControlClass
{
public:
    virtual ~Dial8Class();                                      // 0  0x4A59A0: deleting destructor override
    virtual int Draw(int);                                      // 27  0x4A57B0: override of ControlClass
    virtual int Action(unsigned int, unsigned int *, int);      // 31  0x4A5660: override of ControlClass
    int unknown_2C;  // +0x2C store at 0x4A53EF
    int unknown_30;  // +0x30 store at 0x4A53FF
    int unknown_34;  // +0x34 store at 0x4A5436
    int unknown_38;  // +0x38 store at 0x4A546B
    int unknown_3C;  // +0x3C store at 0x4A548D
    int unknown_40;  // +0x40 store at 0x4A54CC
    int unknown_44;  // +0x44 store at 0x4A54F4
    int unknown_48;  // +0x48 store at 0x4A5497
    int unknown_4C;  // +0x4C store at 0x4A5502
    int unknown_50;  // +0x50 store at 0x4A550F
    int unknown_54;  // +0x54 store at 0x4A549C
    int unknown_58;  // +0x58 store at 0x4A5519
    int unknown_5C;  // +0x5C store at 0x4A5528
    int unknown_60;  // +0x60 store at 0x4A552B
    int unknown_64;  // +0x64 store at 0x4A553A
    int unknown_68;  // +0x68 store at 0x4A54A5
    int unknown_6C;  // +0x6C store at 0x4A5549
    int unknown_70;  // +0x70 store at 0x4A5541
    int unknown_74;  // +0x74 store at 0x4A54B8
    int unknown_78;  // +0x78 store at 0x4A556C
    int unknown_7C;  // +0x7C store at 0x4A55AE
    int unknown_80;  // +0x80 store at 0x4A55E8
    int unknown_84;  // +0x84 store at 0x4A560C
    int unknown_88;  // +0x88 store at 0x4A5596
    int unknown_8C;  // +0x8C store at 0x4A5618
    int unknown_90;  // +0x90 store at 0x4A562B
    int unknown_94;  // +0x94 store at 0x4A5580
    int unknown_98;  // +0x98 store at 0x4A5631
    int unknown_9C;  // +0x9C store at 0x4A564B
    int unknown_A0;  // +0xA0 store at 0x4A563F
    int unknown_A4;  // +0xA4 store at 0x4A5645
    int unknown_A8;  // +0xA8 store at 0x4A55A1
    int unknown_AC;  // +0xAC store at 0x4A5651
    int unknown_B0;  // +0xB0 store at 0x4A55FE
    int unknown_B4;  // +0xB4 store at 0x4A5408
    int unknown_B8;  // +0xB8 store at 0x4A5420
    int unknown_BC;  // +0xBC store at 0x4A5426
};
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_44) == 0x44);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_48) == 0x48);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_50) == 0x50);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_54) == 0x54);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_58) == 0x58);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_5C) == 0x5C);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_60) == 0x60);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_64) == 0x64);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_68) == 0x68);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_6C) == 0x6C);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_70) == 0x70);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_74) == 0x74);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_78) == 0x78);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_7C) == 0x7C);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_80) == 0x80);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_84) == 0x84);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_88) == 0x88);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_8C) == 0x8C);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_90) == 0x90);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_94) == 0x94);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_98) == 0x98);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_9C) == 0x9C);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_A0) == 0xA0);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_A4) == 0xA4);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_A8) == 0xA8);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_AC) == 0xAC);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_B0) == 0xB0);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_B4) == 0xB4);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_B8) == 0xB8);
GG_STATIC_ASSERT(offsetof(Dial8Class, unknown_BC) == 0xBC);

#endif  // GG_MATCH_LAYOUT_DIAL8_CLASS_H
