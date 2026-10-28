// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// GraphicMenuItem base-class entries (layout and evidence: menus_graphic_menu.h).
// The destructor body 0x4F3A70 is defined first so the scalar deleting destructor at 0x4F3B20 expands
// it inline, as retail does; the derived classes' destructors (other translation units) call it.
// LIBRARY: GAMEMD 0x7C8B3D -- operator delete.

#include "menus_graphic_menu.h"

// GAMEMD 0x4F3A70 (the out-of-line body) is outside this cluster's address list and is not claimed here.
inline GraphicMenuItem::~GraphicMenuItem()
{
    delete Part;
}

// FUNCTION: GAMEMD 0x4F3A50
GraphicMenuItem::GraphicMenuItem(int id)
    : Id(id), Flag08(false), Visible(true), Part(0)
{
}

// FUNCTION: GAMEMD 0x4F3AF0
bool GraphicMenuItem::Slot2(const Point2D*)
{
    return false;
}

// FUNCTION: GAMEMD 0x4F3B00
bool GraphicMenuItem::Slot1(unsigned)
{
    return false;
}

// FUNCTION: GAMEMD 0x4F3B10
void GraphicMenuItem::Slot3(MenusItemHost*)
{
    if (Part)
        Part->Func_5D0590();
}

// SYNTHETIC: GAMEMD 0x4F3B20
// GraphicMenuItem::scalar deleting destructor (compiler-generated ??_G; scored from the harness, see menus.rows.tsv)
