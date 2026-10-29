// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
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
        Sink24->vf_1(Visible && !value);
    if (Sink28)
        Sink28->vf_1(Visible && value);
    if (Sink2C)
        Sink2C->vf_1(!Visible);
    Sprite->Func_5D26C0(&Rect);
    Sprite->Func_5D1E50();
    if (value && Part30)
        Part30->Func_5D0590();
}

// FUNCTION: GAMEMD 0x4F3720
void GraphicMenuImageItem::Slot5(bool value)
{
    if (Sink24)
        Sink24->vf_1(value && !Flag08);
    if (Sink28)
        Sink28->vf_1(value && Flag08);
    if (Sink2C)
        Sink2C->vf_1(!value);
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

// FUNCTION: GAMEMD 0x4F3600
// Frees the owned part, destroys the name member, then runs the base destructor. (The scalar deleting
// destructor 0x4F3840 is not reproduced: cl emits ??_G only beside a constructor, and the factory 0x4F3140
// expands it inline.)
GraphicMenuImageItem::~GraphicMenuImageItem()
{
    delete Part30;
}

// SYNTHETIC: GAMEMD 0x4F3840 -- GraphicMenuImageItem::`scalar deleting destructor' (compiler-generated ??_G beside the out-of-line destructor)
