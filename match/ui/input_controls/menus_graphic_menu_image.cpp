// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// GraphicMenuImageItem entries (layout and evidence: menus_graphic_menu.h).
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t); GAMEMD 0x7C8B3D -- operator delete.

#include "menus_graphic_menu.h"

// FUNCTION: GAMEMD 0x4F3640
bool GraphicMenuImageItem::Slot2(const Point2D* point)
{
    return Visible
        && point->X >= Rect.X && point->X < Rect.X + Rect.Width
        && point->Y >= Rect.Y && point->Y < Rect.Y + Rect.Height;
}

// FUNCTION: GAMEMD 0x4F3690
void GraphicMenuImageItem::Slot4(bool value)
{
    if (Sink24)
        Sink24->SetFlag(Visible && !value);
    if (Sink28)
        Sink28->SetFlag(Visible && value);
    if (Sink2C)
        Sink2C->SetFlag(!Visible);
    Sprite->Func_5D26C0(&Rect);
    Sprite->Func_5D1E50();
    if (value && Part30)
        Part30->Func_5D0590();
}

// FUNCTION: GAMEMD 0x4F3720
void GraphicMenuImageItem::Slot5(bool value)
{
    if (Sink24)
        Sink24->SetFlag(value && !Flag08);
    if (Sink28)
        Sink28->SetFlag(value && Flag08);
    if (Sink2C)
        Sink2C->SetFlag(!value);
    Sprite->Func_5D26C0(&Rect);
    Sprite->Func_5D1E50();
}

// FUNCTION: GAMEMD 0x4F37A0
// If the image file named by the item exists, builds its surface sprite and hands it to the host.
void GraphicMenuImageItem::Slot3(MenusItemHost* host)
{
    GraphicMenuItem::Slot3(host);
    if (MenusCCFile(&Name).Exists(0)) {
        MenusSurfaceSprite* sprite = new MenusSurfaceSprite(&Name, MenusScreenSurface, &host->Anchor, 1);
        if (sprite)
            host->Func_5D1DF0(sprite, 0x493E0);
    }
}

// SYNTHETIC: GAMEMD 0x4F3840
// GraphicMenuImageItem::scalar deleting destructor (compiler-generated ??_G; scored from the harness, see menus.rows.tsv)

