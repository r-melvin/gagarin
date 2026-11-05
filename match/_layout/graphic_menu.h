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
#include "../vector_class.h"
#include "../string_class.h"
#include "ms_engine.h"

class GraphicMenuItem;

class GraphicMenu
{
public:
    virtual ~GraphicMenu();                                     // 0  0x4F2830: scalar deleting destructor shape
    GraphicMenu();                                              // 0x4F2140 (0x4F1CA0 is the allocating factory)
    MSEngine Engine;               // +0x04 constructed by 0x5D1AA0 (ctor callers place the next member at +0x4C)
    Wstring Background;            // +0x4C 'Title.PCX' via 0x7B4630 at 0x4F2153
    Wstring Name;                  // +0x50 'Intro' via 0x7B4630 at 0x4F2160
    int unknown_54;  // +0x54 store at 0x4F2167
    DynamicVectorClass<GraphicMenuItem*> Items;  // +0x58 vtable 0x7EA604 (RTTI DynamicVectorClass<GraphicMenuItem*>)
};
GG_STATIC_ASSERT(offsetof(GraphicMenu, unknown_54) == 0x54);
GG_STATIC_ASSERT(offsetof(GraphicMenu, Engine) == 0x04);
GG_STATIC_ASSERT(offsetof(GraphicMenu, Background) == 0x4C);
GG_STATIC_ASSERT(offsetof(GraphicMenu, Name) == 0x50);
GG_STATIC_ASSERT(offsetof(GraphicMenu, Items) == 0x58);
GG_STATIC_ASSERT(sizeof(GraphicMenu) == 0x70);

#endif  // GG_MATCH_LAYOUT_GRAPHIC_MENU_H
