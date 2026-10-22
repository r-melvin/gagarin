// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// CCToolTip slots 1..5 (layout and evidence: sidebar_cctooltip.h).

#include "sidebar_cctooltip.h"

// Slot 1: positions the tooltip text box next to the gadget it belongs to, flipping
// it to the other side of the area's midline, clamping it to the area and growing
// the box to the measured text size.
//
// PARTIAL (99.0%, 189/191). Same instruction multiset as retail; the only two
// positional differences are the load order of `area->X` and `area->Width` in the
// horizontal overflow sum (retail loads X into EDX then Width into EBP, cl loads Width
// first and X second; the vertical sum matches). Variants tried: the expression in all
// 24 operand orders (cl canonicalises them, identical output), stepwise `over -= ..`
// statements, and named locals for `fx`, `ax`, `aw` loaded in either order.
// FUNCTION: GAMEMD 0x478BA0
bool CCToolTip::Update(ToolTipManagerData& from)
{
    if (WWMouseClassInstance->GetHideCount() >= 0) {
    TipFont_00478BA0* font = FontInstance_0089C4D0;
    const TipRect_00478BA0* area;
    if (SidebarSideFlag_00A8EB7C == 1) {
        if (from.X > TacticalRect_00886FA0.X + TacticalRect_00886FA0.Width) {
            area = &SidebarRect_00886F90;
            TipTouchedSidebar_00884B8E = 1;
        } else {
            area = &TacticalRect_00886FA0;
        }
    } else {
        if (from.X <= SidebarRect_00886F90.X + SidebarRect_00886F90.Width) {
            area = &SidebarRect_00886F90;
            TipTouchedSidebar_00884B8E = 1;
        } else {
            area = &TacticalRect_00886FA0;
        }
    }
    if (area) {
        int w;
        int h;
        font->FUN_00433CF0(from.HelpText, &w, &h, area->Width);
        w += 4;
        h += 3;
        from.Width = w > from.Width ? w : from.Width;
        from.Height = h > from.Height ? h : from.Height;
        if (from.Width >= area->Width) {
            font->FUN_00433CF0(from.HelpText, &w, &h, area->Width - 4);
            w += 4;
            h += 3;
            from.Width = w > from.Width ? w : from.Width;
            from.Height = h > from.Height ? h : from.Height;
        }
        const ToolTip* tip = CurrentToolTip;
        if (tip && tip->field_18) {
            const ToolTipBounds b = tip->Bounds;
            if (b.X < area->X + area->Width / 2) {
                from.X = b.X + b.Width - 5;
            } else {
                from.X = b.X - w + 5;
            }
            from.X = area->X > from.X ? area->X : from.X;
            if (b.Y < area->Y + area->Height / 2) {
                from.Y = b.Y + b.Height - 5;
            } else {
                from.Y = b.Y - h + 5;
            }
            from.Y = area->Y > from.Y ? area->Y : from.Y;
        } else {
            int over = from.X - area->X - area->Width + from.Width;
            if (over > 0) {
                from.X -= over;
            }
            from.Y += 16;
            over = from.Y - area->Y - area->Height + from.Height;
            if (over > 0) {
                from.Y = from.Y - from.Height - 16;
            }
        }
    }
    return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x478DB0
void CCToolTip::MarkToRedraw(ToolTipManagerData& from)
{
    if (SidebarSideFlag_00A8EB7C == 1) {
        if (from.X >= TacticalRect_00886FA0.X + TacticalRect_00886FA0.Width) {
            TipTouchedSidebar_00884B8E = 1;
            SidebarNeedsRedraw_00884B8F = 1;
        }
    } else {
        if (from.X <= SidebarRect_00886F90.X + SidebarRect_00886F90.Width) {
            TipTouchedSidebar_00884B8E = 1;
            SidebarNeedsRedraw_00884B8F = 1;
        }
    }
    MapInstance_0087F7E8.FlagToRedraw(0);
    ToolTipManager::MarkToRedraw(from);
}

// FUNCTION: GAMEMD 0x478E10
void CCToolTip::Draw(bool onSidebar)
{
    OnSidebar = onSidebar;
    ToolTipManager::Draw(!onSidebar);
}

// The display's pixel packer, expanded inline (see sidebar_cctooltip.h).
inline unsigned int PackColor(const TipRGB_00478E30& c)
{
    unsigned int blue = (c.B >> BlueRight_008A0DDC) << BlueLeft_008A0DD8;
    unsigned int green = (c.G >> GreenRight_008A0DE4) << GreenLeft_008A0DE0;
    unsigned int red = (c.R >> RedRight_008A0DD4) << RedLeft_008A0DD0;
    return blue | green | red;
}

// Slot 4: draws the tooltip: picks the composite or sidebar surface from the side
// flag and the box position, measures the text, clamps the box to the surface,
// fills it with the packed tooltip colour and prints the text inside it.
//
// CAPPED at 2.9% positional (5/175; LCS 119/175 = 68%). Multiset delta: retail has 2
// `mov` that cl does not (everything else is identical). Retail loads the side flag
// byte into BL (`MOV BL,[0xA8EB7C]` ... `CMP BL,1`) between loading `from.X` (EAX) and
// `from.Y` (EDI); cl folds it into `CMP BYTE PTR [flag],1` and so hands EBX to the
// y local, which shifts every later register and the whole positional score. Variants
// tried: the flag as an unsigned char local declared first / between x and y / as a
// bool; the global typed unsigned char / char / bool / int; the two arms as `switch`
// (worse, 3.4% positional, LCS 68%); x and y as locals vs. direct field reads; the
// colour pack as a by-value copy, a const reference with locals declared B/G/R and
// every other declaration order (the by-reference inline reproduces retail's word load
// of G,B). Retail's frame (0x2C) and the `EBP` save around the print call match.
// FUNCTION: GAMEMD 0x478E30
void CCToolTip::DrawText(ToolTipManagerData& from)
{
    TipSurface_00478E30* surface;
    unsigned char side = SidebarSideFlag_00A8EB7C;
    int x = from.X;
    int y = from.Y;
    if (side == 1) {
        int limit = TacticalRect_00886FA0.X + TacticalRect_00886FA0.Width;
        if (from.X + from.Width <= limit) {
            surface = CompositeSurface_0088731C;
        } else {
            if (OnSidebar != 1 || from.X < limit) return;
            surface = SidebarSurface_00887300;
            x = from.X - limit;
            SidebarSurfaceUsed_00B0B518 = 1;
        }
    } else {
        int limit = SidebarRect_00886F90.X + SidebarRect_00886F90.Width;
        if (from.X >= limit) {
            surface = CompositeSurface_0088731C;
            x = from.X - limit;
        } else {
            if (OnSidebar != 1 || from.X + from.Width >= limit) return;
            surface = SidebarSurface_00887300;
            SidebarSurfaceUsed_00B0B518 = 1;
        }
    }
    if (!surface) return;

    const wchar_t* text = from.HelpText;
    TipFont_00478BA0* font = FontInstance_0089C4D0;
    TipRectLTRB_00478E30 box;
    box.Top = y;
    box.Bottom = y;
    box.Left = x;
    box.Right = x;
    int w;
    int h;
    font->FUN_00433CF0(text, &w, &h, (surface->*surface->Vtbl->At_7C)());
    box.Bottom = box.Top + h;
    box.Right = box.Left + w;
    int boxH = box.Bottom - box.Top + 4;
    int boxW = box.Right - box.Left + 8;
    if (box.Left + boxW > (surface->*surface->Vtbl->At_7C)()) {
        box.Left = (surface->*surface->Vtbl->At_7C)() - boxW;
    }
    box.Right = box.Left + boxW;
    box.Bottom = box.Top + boxH;
    unsigned int color = PackColor(TipColor_00B0FA1C);
    TipRect_00478BA0 fill;
    fill.X = box.Left;
    fill.Y = box.Top;
    fill.Width = boxW;
    fill.Height = boxH;
    (surface->*surface->Vtbl->At_14)(&fill, 0);
    (surface->*surface->Vtbl->At_58)(&fill, color);
    font->FUN_00433C90(1);
    font->FUN_00433CA0(&box);
    font->FUN_00433C70((unsigned short)color);
    PrinterInstance_0089C4B8->FUN_00434CD0(font, surface, text, box.Left + 4, box.Top + 2,
                                           box.Right - box.Left, box.Bottom - box.Top, 0, 0, 0);
}

// FUNCTION: GAMEMD 0x479050
wchar_t* CCToolTip::GetToolTipText(unsigned int id)
{
    if (WWMouseClassInstance->GetHideCount() < 0) {
        return 0;
    }
    return MapInstance_0087F7E8.FUN_006D1800(id);
}
