// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below. The
//   owning classes are not named by RTTI at these addresses, so each receiver
//   keeps a placeholder name derived from its address.
//
// Ordered ascending by retail address.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../renderer/surface_class.h"
#include "../_layout/color_convert.h"

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
// 0x486E30: a cell's veinhole check. The coordinate pair sits at +0x24.
struct Coord_00486E30 { short X; short Y; };
GG_STATIC_ASSERT(sizeof(Coord_00486E30) == 4);

struct Cell_00486E30;

// The veinhole monster found for a coordinate (receiver of the 0x74EF10 handler).
struct Vein_00486E30
{
    // FUNCTION: GAMEMD 0x74EF10 (decl; reloc) -- react to the cell.
    void FUN_0074EF10(Cell_00486E30* cell);
};

// The cell a map lookup returns (receiver of the 0x485590 handler).
struct CellRef_00486E30
{
    // FUNCTION: GAMEMD 0x485590 (decl; reloc) -- react to the cell.
    void FUN_00485590();
};

struct Map_00486E30
{
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) -- MapClass::GetCellAt.
    CellRef_00486E30* GetCellAt(const Coord_00486E30* coord);
};

// GLOBAL: GAMEMD 0x87F7E8 -- the map object (used by address, ECX).
extern Map_00486E30 DAT_0087F7E8_00486E30;

// FUNCTION: GAMEMD 0x74CDB0 (decl; reloc) -- the veinhole monster covering a coordinate, or 0.
Vein_00486E30* FUN_0074CDB0(const Coord_00486E30* coord);

struct Cell_00486E30
{
    char           _pad000[0x24];  // +0x0000
    Coord_00486E30 MapCoords;      // +0x0024

    int FUN_00486E30();
};
GG_STATIC_ASSERT(offsetof(Cell_00486E30, MapCoords) == 0x24);

// FUNCTION: GAMEMD 0x486E30
//
// If a veinhole monster covers this cell, hand the cell to it; otherwise let the
// map's cell record for these coordinates react. Always returns 0.
int Cell_00486E30::FUN_00486E30()
{
    Vein_00486E30* vein = FUN_0074CDB0(&MapCoords);
    if (vein) {
        vein->FUN_0074EF10(this);
        return 0;
    }
    DAT_0087F7E8_00486E30.GetCellAt(&MapCoords)->FUN_00485590();
    return 0;
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
