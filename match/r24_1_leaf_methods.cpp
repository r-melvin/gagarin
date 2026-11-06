// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below. The
//   owning classes are not named by RTTI at these addresses, so each receiver
//   keeps a placeholder name derived from its address.
//
// Ordered ascending by retail address.

#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "wwlib/surface/surface_class.h"
#include "_layout/color_convert.h"

// ---------------------------------------------------------------------------
// 0x42E150: a rectangle with a palette colour, drawn as an outline.
struct Box_0042E150
{
    RectangleStruct Rect;          // +0x0000
    char            _pad010[0x8];  // +0x0010
    int             ColorIndex;    // +0x0018

    void FUN_0042E150();
};
GG_STATIC_ASSERT(offsetof(Box_0042E150, ColorIndex) == 0x18);

// GLOBAL: GAMEMD 0x87F6C4 -- the palette-to-pixel lookup.
extern ColorConvert* DAT_0087F6C4;
// GLOBAL: GAMEMD 0x887314 -- DSurface::Temp.
extern Surface* DAT_00887314;

// FUNCTION: GAMEMD 0x42E150
//
// Outline the rectangle in its palette colour on the temp surface, if it has a colour.
void Box_0042E150::FUN_0042E150()
{
    if (ColorIndex != 0) {
        unsigned color = DAT_0087F6C4->Lookup(ColorIndex);
        RectangleStruct rect = Rect;
        DAT_00887314->DrawRect(&rect, color);
    }
}

// ---------------------------------------------------------------------------
// 0x488210: a toggle-style gadget press handler (the +0x2D byte is the on flag).
struct Obj_00488210
{
    char          _pad000[0x2D];   // +0x0000
    unsigned char IsOn;            // +0x002D

    // FUNCTION: GAMEMD 0x723EA0 (decl; reloc) -- turn on.
    void FUN_00723EA0();
    // FUNCTION: GAMEMD 0x723EB0 (decl; reloc) -- turn off.
    void FUN_00723EB0();
    // FUNCTION: GAMEMD 0x723EC0 (decl; reloc) -- the action handler.
    int FUN_00723EC0(unsigned flags, int key, int modifier);

    void FUN_00488210(unsigned flags, int key, int unused);
};
GG_STATIC_ASSERT(offsetof(Obj_00488210, IsOn) == 0x2D);

// FUNCTION: GAMEMD 0x488210
//
// When the press bit (4) is set, flip the on state: an object that is on is
// turned off, an off one turned on. Then run the action handler with no modifier.
void Obj_00488210::FUN_00488210(unsigned flags, int key, int unused)
{
    if (flags & 4) {
        if (IsOn) {
            FUN_00723EB0();
        } else {
            FUN_00723EA0();
        }
    }
    FUN_00723EC0(flags, key, 0);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x87F6C4
ColorConvert* DAT_0087F6C4;
// END defined globals
