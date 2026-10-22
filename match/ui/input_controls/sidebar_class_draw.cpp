// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// SidebarClass slot 16 (draw); layout and evidence: sidebar_class_layout.h.

#include "sidebar_class_layout.h"
#include "../tooltip_manager_shared.h"

// GLOBAL: GAMEMD 0x8809F4 -- clip rectangle, copied from the object at 0xB07DC8.
struct SidebarClipRect
{
    int X;
    int Y;
    int Width;
    int Height;
};
extern SidebarClipRect ClipRect_008809F4;
// GLOBAL: GAMEMD 0xB07DC8 -- source of the clip rectangle.
extern SidebarClipRect BackdropRect_00B07DC8;
// GLOBAL: GAMEMD 0xB0B518 -- accumulated "something was redrawn" flag.
// (SidebarTouched_00B0B518 in the layout header.)

// Number of cameo rows that fit in the sidebar (expanded inline by 0x6A6C30).
inline int SidebarRowCount()
{
    int margin = 0x1A;
    if (Scenario_00A8B230->At_34B8) {
        margin = 0x12;
    }
    return (DAT_00886F9C - StripY_00B0B4F8 - margin + DAT_00886F94 - 7) / 50;
}

// FUNCTION: GAMEMD 0x4AED70 (decl; reloc) -- draw a shape: surface in ECX, convert
// in EDX, fourteen stack arguments (RET 0x38).
void __fastcall SidebarDrawShape(SidebarSurfaceView* surface, SidebarConvert* convert,
                                 SidebarShapeFile* shape, int frame, Point2D* position,
                                 SidebarAreaRect* bounds, int flags, int a6, int a7, int a8,
                                 int zAdjust, int a10, int a11, int a12, int a13, int a14);

// One 0x400-flag shape draw at (0, y) on the sidebar surface; expanded inline by 0x6A6C30.
inline void DrawSidebarShape(int shape, int frame, int y, SidebarAreaRect* bounds)
{
    Point2D position;
    position.X = 0;
    position.Y = y;
    SidebarDrawShape(SidebarSurface_00887300, ConvertA_0087F6CC, SideShapes_00B0B468[shape], frame,
                     &position, bounds, 0x400, 0, 0, 0, 0x3E8, 0, 0, 0, 0, 0);
}

// Slot 16: draws the sidebar: backdrop shapes, the buttons, the open/close animation
// frames and the current strip, then folds the buttons' redraw flags into one.
//
// CAPPED at 5.6% (20/355; LCS 256/355 = 72.1%, up from 223 = 62.8%). Retail loads the
// backdrop rectangle after the callee-saved pushes, ours before; retail pushes the
// thirteenth shape-draw argument through a fresh `xor eax,eax` while the others use the
// zero register EBX (a zero-valued local for that argument is folded by cl, no change).
// The shape draws are expanded from an inline helper (attempt 2), which moved LCS from 62.8%
// to 72.1% but lowered the positional score from 9.3% to 5.6%. Attempts: (1) open-coded
// draws, 9.3%; (2) inline helper `DrawSidebarShape`, 5.6% (kept); (3) a zero local for the
// thirteenth argument, no change. Remaining multiset delta: retail has 2 `xor`, a top-tested
// row loop with the row count recomputed per iteration (ours matches), and the prologue
// ordering above.
// FUNCTION: GAMEMD 0x6A6C30
void SidebarClass::vf_16(bool forced)
{
    ClipRect_008809F4 = BackdropRect_00B07DC8;
    SidebarSurfaceView* previous = CurrentSurface_00887314;
    CurrentSurface_00887314 = SidebarSurface_00887300;
    bool drewBackground = false;
    SidebarAreaRect bounds;
    bounds.Height = (SidebarSurface_00887300->*SidebarSurface_00887300->Vtbl->At_80)();
    bounds.Width = (SidebarSurface_00887300->*SidebarSurface_00887300->Vtbl->At_7C)();
    bounds.X = 0;
    bounds.Y = 0;
    if (forced || At_53A6 || At_53A7) {
        forced = true;
    } else {
        forced = false;
    }
    if (At_53A5 && forced && !DAT_00A8ED6B) {
        if (At_53A7) {
            drewBackground = true;
            DrawSidebarShape(0, 0, DAT_00886F94, &bounds);
            int y = StripY_00B0B4F8;
            for (int i = 0; i < SidebarRowCount(); ++i) {
                DrawSidebarShape(1, 0, y, &bounds);
                y += SideShapes_00B0B468[1]->Height;
            }
            DrawSidebarShape(2, 0, y, &bounds);
            DrawSidebarShape(3, 0, SideShapes_00B0B468[2]->Height + y, &bounds);
        }
        SellButton_00B07DF8.Draw(drewBackground);
        RepairButton_00B0B3A0.Draw(drewBackground);
        for (int j = 0; j < 4; ++j) {
            TabButtons_00B07C48[j].Draw(1);
        }
        ScrollDownButton_00B0B328.Draw(drewBackground);
        ScrollUpButton_00B0B408.Draw(drewBackground);
        if (unknown_5398 != 0) {
            DrawSidebarShape(4, unknown_5394, StripY_00B0B4F8, &bounds);
            DrawSidebarShape(5, unknown_5394, StripY_00B0B4F8, &bounds);
            DrawSidebarShape(6, unknown_5394, StripY_00B0B4F8, &bounds);
        }
        SidebarTouched_00B0B518 = 1;
    }
    Strips[ActiveTab].FUN_006A9540(At_53A7);
    PowerClass::vf_16(forced || drewBackground);
    if (SellButton_00B07DF8.At_54) {
        SellButton_00B07DF8.At_54 = false;
        SidebarTouched_00B0B518 = 1;
    }
    if (RepairButton_00B0B3A0.At_54) {
        RepairButton_00B0B3A0.At_54 = false;
        SidebarTouched_00B0B518 = 1;
    }
    for (int k = 0; k < 4; ++k) {
        if (TabButtons_00B07C48[k].At_54) {
            TabButtons_00B07C48[k].At_54 = false;
            SidebarTouched_00B0B518 = 1;
        }
    }
    if (ScrollDownButton_00B0B328.At_54) {
        ScrollDownButton_00B0B328.At_54 = false;
        SidebarTouched_00B0B518 = 1;
    }
    if (ScrollUpButton_00B0B408.At_54) {
        ScrollUpButton_00B0B408.At_54 = false;
        SidebarTouched_00B0B518 = 1;
    }
    if (ToolTipManager_Instance) {
        ToolTipManager_Instance->Draw(true);
    }
    FUN_006A70E0(SidebarTouched_00B0B518 || At_53A7);
    At_53A6 = false;
    At_53A7 = false;
    CurrentSurface_00887314 = previous;
}
