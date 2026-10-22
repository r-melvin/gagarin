// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// SidebarClass slot 34 (reposition every sidebar gadget and re-register the
// tooltips); layout and evidence: sidebar_class_layout.h.

#include "sidebar_class_layout.h"
#include "../tooltip_manager_shared.h"

// GLOBAL: GAMEMD 0xB0B468 is declared in the layout header (SideShapes).
// FUNCTION: GAMEMD 0x5B40B0 (decl; reloc) -- SidebarMixRetrieve, declared in the layout header too.



// Slot 34: repositions every sidebar gadget for the current layout (including the
// 2-column cameo grid) and re-registers all tooltips.
//
// PARTIAL (98.1%, 318/323, multiset identical). The side-flag placement is two calls
// under if/else (retail pushes `bottom`, then branches to `PUSH 0` or the sum); a ternary
// argument compiled branch-free. Remaining: (1) the vertical extent `Y + Height` loads in
// the other operand order; (2) the row-count subtraction order and the strip top's
// register (retail subtracts the margin before the strip top, in EBX). Variants tried:
// the tooltip store orders (hill-climbed per block), the strip loop as pointer and int
// index, the cameo column increment in the loop header and body, the row count as five
// expression and temporary forms, the side flag as ternary / preset local, the row count reassociated five ways, the margin
// as a ternary (95.7%).
// FUNCTION: GAMEMD 0x6ABD30
void SidebarClass::vf_34()
{
    PowerClass::vf_34();
    FUN_006A5130(0);
    if (SideShapes_00B0B468[0] == 0) {
        SideShapes_00B0B468[0] = SidebarMixRetrieve("SIDEGDI1.SHP", 0);
        SideShapes_00B0B468[1] = SidebarMixRetrieve("SIDEGDI2.SHP", 0);
        SideShapes_00B0B468[2] = SidebarMixRetrieve("SIDEGDI3.SHP", 0);
    }

    ExtraButton_00B07E58.SetPosition(SidebarRect_00886F90.X + 0x10, TacticalRect_00886FA0.Y);
    ExtraButton_00B07E58.MarkRedraw();
    int bottom = ExtraGadget_00B04A10.Y + ExtraGadget_00B04A10.Height;
    if (SidebarSideFlag_00A8EB7C) {
        ExtraButton_00B07E58.SetPosition(TacticalRect_00886FA0.X + TacticalRect_00886FA0.Width, bottom);
    } else {
        ExtraButton_00B07E58.SetPosition(0, bottom);
    }
    ExtraButton_00B07E58.SetDimension(
        (SidebarSurface_00887300->*SidebarSurface_00887300->Vtbl->At_7C)(),
        (SidebarSurface_00887300->*SidebarSurface_00887300->Vtbl->At_80)() - bottom);

    RepairButton_00B0B3A0.SetPosition(RepairX_00B0B4DC, RepairY_00B0B4E0);
    RepairButton_00B0B3A0.MarkRedraw();
    RepairButton_00B0B3A0.At_44 = -SidebarRect_00886F90.X;
    SellButton_00B07DF8.SetPosition(SellOffset_00B0B4E4 + RepairButton_00B0B3A0.X,
                                    RepairButton_00B0B3A0.Y);
    SellButton_00B07DF8.MarkRedraw();
    SellButton_00B07DF8.At_44 = -SidebarRect_00886F90.X;
    for (int i = 0; i < 4; ++i) {
        TabButtons_00B07C48[i].SetPosition(TabStep_00B0B4F0 * i + TabX_00B0B4E8, TabY_00B0B4EC);
        TabButtons_00B07C48[i].MarkRedraw();
        TabButtons_00B07C48[i].At_44 = -SidebarRect_00886F90.X;
    }
    ScrollDownButton_00B0B328.SetPosition(ScrollX_00B0B508, ScrollY_00B0B50C);
    ScrollDownButton_00B0B328.MarkRedraw();
    ScrollDownButton_00B0B328.At_44 = -SidebarRect_00886F90.X;
    ScrollUpButton_00B0B408.SetPosition(ScrollUpOffset_00B0B510 + ScrollX_00B0B508, ScrollY_00B0B50C);
    ScrollUpButton_00B0B408.MarkRedraw();
    ScrollUpButton_00B0B408.At_44 = -SidebarRect_00886F90.X;

    int margin = 0x1A;
    if (Scenario_00A8B230->At_34B8) {
        margin = 0x12;
    }
    int rows = (DAT_00886F9C - margin - StripY_00B0B4F8 + DAT_00886F94 - 7) / 50;
    int slots = rows * 2;
    for (int strip = 0; strip < 4; ++strip) {
        SidebarCameoButton* cameo = &CameoButtons_00B07E80[strip * 60];
        for (int row = 0; row < rows; ++row) {
            for (int column = 0; column < 2; ++column, ++cameo) {
                (cameo->*cameo->Vtbl->At_64)(ColumnStep_00B0B4FC * column + StripX_00B0B4F4,
                                             RowStep_00B0B500 * row + StripY_00B0B4F8 + 1);
                (cameo->*cameo->Vtbl->At_48)();
            }
        }
    }

    if (ToolTipManager_Instance != 0) {
        ToolTip tip;
        tip.field_18 = false;
        for (int i = 0; i < 4; ++i) {
            tip.Bounds.X = TabButtons_00B07C48[i].X;
            tip.Bounds.Y = TabButtons_00B07C48[i].Y;
            tip.GadgetID = 0xCB + i;
            tip.Text = 0;
            tip.Bounds.Width = TabButtons_00B07C48[i].Width;
            tip.Bounds.Height = TabButtons_00B07C48[i].Height;
            ToolTipManager_Instance->Remove(tip.GadgetID);
            ToolTipManager_Instance->Add(tip);
        }
        for (int j = 0; j < 60; ++j) {
            ToolTipManager_Instance->Remove(0x3E8 + j);
        }
        for (int k = 0; k < slots; ++k) {
            tip.GadgetID = 0x3E8 + k;
            tip.Bounds.X = CameoButtons_00B07E80[k].X;
            tip.Bounds.Y = CameoButtons_00B07E80[k].Y;
            tip.Bounds.Width = CameoButtons_00B07E80[k].Width;
            tip.Text = 0;
            tip.Bounds.Height = CameoButtons_00B07E80[k].Height;
            tip.field_18 = true;
            ToolTipManager_Instance->Add(tip);
        }
        tip.Bounds.X = SellButton_00B07DF8.X;
        tip.field_18 = false;
        tip.GadgetID = 0x66;
        tip.Text = "TXT_SELL_MODE";
        tip.Bounds.Y = SellButton_00B07DF8.Y;
        tip.Bounds.Width = SellButton_00B07DF8.Width;
        tip.Bounds.Height = SellButton_00B07DF8.Height;
        ToolTipManager_Instance->Remove(tip.GadgetID);
        ToolTipManager_Instance->Add(tip);
        tip.Bounds.X = RepairButton_00B0B3A0.X;
        tip.GadgetID = 0x65;
        tip.Text = "TXT_REPAIR_MODE";
        tip.Bounds.Y = RepairButton_00B0B3A0.Y;
        tip.Bounds.Width = RepairButton_00B0B3A0.Width;
        tip.Bounds.Height = RepairButton_00B0B3A0.Height;
        ToolTipManager_Instance->Remove(tip.GadgetID);
        ToolTipManager_Instance->Add(tip);
        tip.Bounds.X = ScrollUpButton_00B0B408.X;
        tip.GadgetID = 0xC8;
        tip.Text = 0;
        tip.Bounds.Y = ScrollUpButton_00B0B408.Y;
        tip.Bounds.Width = ScrollUpButton_00B0B408.Width;
        tip.Bounds.Height = ScrollUpButton_00B0B408.Height;
        ToolTipManager_Instance->Remove(tip.GadgetID);
        ToolTipManager_Instance->Add(tip);
        tip.Bounds.X = ScrollDownButton_00B0B328.X;
        tip.GadgetID = 0xC9;
        tip.Text = 0;
        tip.Bounds.Y = ScrollDownButton_00B0B328.Y;
        tip.Bounds.Width = ScrollDownButton_00B0B328.Width;
        tip.Bounds.Height = ScrollDownButton_00B0B328.Height;
        ToolTipManager_Instance->Remove(tip.GadgetID);
        ToolTipManager_Instance->Add(tip);
    }
}
