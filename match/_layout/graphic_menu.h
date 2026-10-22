// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI: TypeDescriptor 0x00824170 `.?AVGraphicMenu@@`; class hierarchy descriptor 0x008025B0.
//   Bases in RTTI (declaration) order: none.
// VTABLE: GAMEMD 0x7EA5FC (1 slots)
//   Allocation: operator new (0x7C8E17) of 0x70 bytes at 0x4F1CDB.
//   Virtual slots are named vf_<slot>; the binary attests no names. Argument counts come from each target's RET n;
//   return types are not recovered (void placeholder). Member offsets come from constructor stores only.
#ifndef GG_MATCH_LAYOUT_GRAPHIC_MENU_H
#define GG_MATCH_LAYOUT_GRAPHIC_MENU_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class GraphicMenu
{
public:
    virtual ~GraphicMenu();                                     // 0  0x4F2830: scalar deleting destructor shape
    unsigned char unknown_04[80];  // +0x4
    int unknown_54;  // +0x54 store at 0x4F2167
    int unknown_58;  // +0x58 vptr store at 0x4F2177
    int unknown_5C;  // +0x5C store at 0x4F216A
    int unknown_60;  // +0x60 store at 0x4F216D
    unsigned char unknown_64;  // +0x64 store at 0x4F2170
    unsigned char unknown_65;  // +0x65 store at 0x4F2174
    unsigned char unknown_66[2];  // +0x66
    int unknown_68;  // +0x68 store at 0x4F2185
    int unknown_6C;  // +0x6C store at 0x4F217E
};
GG_STATIC_ASSERT(offsetof(GraphicMenu, unknown_54) == 0x54);
GG_STATIC_ASSERT(offsetof(GraphicMenu, unknown_58) == 0x58);
GG_STATIC_ASSERT(offsetof(GraphicMenu, unknown_5C) == 0x5C);
GG_STATIC_ASSERT(offsetof(GraphicMenu, unknown_60) == 0x60);
GG_STATIC_ASSERT(offsetof(GraphicMenu, unknown_64) == 0x64);
GG_STATIC_ASSERT(offsetof(GraphicMenu, unknown_65) == 0x65);
GG_STATIC_ASSERT(offsetof(GraphicMenu, unknown_68) == 0x68);
GG_STATIC_ASSERT(offsetof(GraphicMenu, unknown_6C) == 0x6C);
GG_STATIC_ASSERT(sizeof(GraphicMenu) == 0x70);

#endif  // GG_MATCH_LAYOUT_GRAPHIC_MENU_H
