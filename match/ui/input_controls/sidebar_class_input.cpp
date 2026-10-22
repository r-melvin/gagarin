// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// SidebarClass slot 10 (per-frame input handling); layout and evidence:
// sidebar_class_layout.h.

#include "sidebar_class_layout.h"

// Number of cameo rows that fit in the sidebar (expanded inline by 0x6A7780,
// twice in one path).
inline int SidebarRowCount()
{
    int margin = 0x1A;
    if (Scenario_00A8B230->At_34B8) {
        margin = 0x12;
    }
    return (DAT_00886F9C - margin - StripY_00B0B4F8 + DAT_00886F94 - 7) / 50;
}

// Slot 10: per-frame sidebar input: scrolls the open/close animation, toggles the
// observer panel state, handles the hotkeys for sell/repair/tab/scroll and ticks the
// buttons.
//
// CAPPED at 35.9% (143/398; LCS 228/394 = 57.9%). Multiset delta: retail has `sub` 1, `dec` 1,
// `jmp` 1, `jge` 2; ours `mov` 2, `test` 2, `cmp` 1, `setne`/`sete` 1+1, `setl` 2. Attempts:
//  1. first pass (as kept).
//  2. the observer toggle as if/else storing 1 or 0: cl folds it back into `sete`
//     (11.0% positional, LCS 54.1%).
//  3. the toggle as a `switch (control)` with `case 1`: LCS 59.4% but 11.0% positional (the
//     code length shifts everything after it); kept out because the score is lower.
//  4. the key dispatch as a `switch (code)`: cl builds a jump table (462 instructions,
//     26.3%), retail uses a compare chain whose last arms (scroll down/up) are laid after the
//     function epilogue; not reproduced.
//  5. `SidebarPlayGlobal` declared as a void-returning fastcall with a signed second
//     argument: no change. Retail places `MOV EDX,0x2000` between the two pushes; ours
//     emits both pushes first.
// FUNCTION: GAMEMD 0x6A7780
void SidebarClass::vf_10(int* key, Point2D* mouse)
{
    Point2D relative;
    relative.X = mouse->X - SidebarRect_00886F90.X;
    relative.Y = mouse->Y;
    if (DAT_00A8ED6B == 0) {
        vf_54(1);
        for (int i = 0; i < 4; ++i) {
            Strips[i].FUN_006A8B30(key, &relative);
        }
    }
    if (At_53A5) {
        if (unknown_5398 == 1) {
            unknown_5394 = unknown_5394 + 1;
            if (unknown_5394 > SideShapes_00B0B468[4]->Frames) {
                unknown_5398 = 0;
                unknown_5394 = 0;
            }
        } else if (unknown_5398 == -1) {
            unknown_5394 = unknown_5394 - 1;
            if (unknown_5394 < 0) {
                unknown_5398 = 0;
                unknown_5394 = 0;
            }
        }
        int control = CurrentPlayer_00A83D4C->At_2F0 > 0;
        bool old = At_5514;
        if (control == -1) {
            control = (old == 0);
        }
        At_5514 = (control == 1);
        if (old != At_5514) {
            FlagToRedraw(0);
            At_53A6 = 1;
            if (!At_5514) {
                vf_18(0, 0);
            }
        }
        int code = *key;
        if (code == 0x8066) {
            SidebarPlayGlobal(Rules_008871E0->Sound188, 0x2000, 1.0f, 0);
            SetSellMode_004AC660(-1);
        } else if (code == 0x8065) {
            SidebarPlayGlobal(Rules_008871E0->Sound188, 0x2000, 1.0f, 0);
            SetRepairMode_004AC8C0(-1);
        } else if (code >= 0x80CB && code < 0x80CF) {
            int tab = code - 0x80CB;
            if (tab != unknown_539C) {
                TabButtons_00B07C48[unknown_539C].TurnOff();
                StripClass* previous = &Strips[unknown_539C];
                previous->At_1C = 0;
                for (int i = 0; i < 60; ++i) {
                    MapInstance_0087F7E8.FUN_004F4450(
                        &CameoButtons_00B07E80[previous->RowBase * 60 + i]);
                }
                unknown_539C = tab;
                TabButtons_00B07C48[tab].TurnOn();
                StripClass* strip = &Strips[unknown_539C];
                strip->At_1C = 1;
                int rows = SidebarRowCount() * 2;
                for (int j = 0; j < rows; ++j) {
                    CameoButtons_00B07E80[strip->RowBase * 60 + j].Zap();
                    MapInstance_0087F7E8.AddButton(&CameoButtons_00B07E80[strip->RowBase * 60 + j]);
                }
                SidebarNeedsRedraw_00884B8F = 1;
                FUN_006A6610();
                At_53A7 = 1;
            }
            SidebarPlayGlobal(Rules_008871E0->Sound190, 0x2000, 1.0f, 0);
        } else if ((code & ~0x4000) == (ScrollDownButton_00B0B328.ID | 0x8000)) {
            ScrollDownButton_00B0B328.At_2C = 0;
            StripClass* strip = &Strips[unknown_539C];
            int step = SidebarRowCount();
            if (CurrentPlayer_00A83D4C == Observer_00AC1198) {
                step = 1;
            }
            int rows = SidebarRowCount();
            bool scrolls;
            if (CurrentPlayer_00A83D4C == Observer_00AC1198) {
                scrolls = strip->TopRowIndex + rows / 2 < ObserverRowLimit_00884CF8;
            } else {
                scrolls = (strip->TopRowIndex + rows) * 2 < strip->CameoCount;
            }
            if (scrolls) {
                strip->At_48 = strip->At_48 + step;
                SidebarPlayGlobal(Rules_008871E0->Sound190, 0x2000, 1.0f, 0);
            } else {
                SidebarPlayGlobal(Rules_008871E0->Sound700, 0x2000, 1.0f, 0);
            }
        } else if (code == (ScrollUpButton_00B0B408.ID | 0x8000)) {
            ScrollUpButton_00B0B408.At_2C = 0;
            StripClass* strip = &Strips[unknown_539C];
            int rows = SidebarRowCount();
            if (CurrentPlayer_00A83D4C == Observer_00AC1198) {
                rows = 1;
            }
            if (strip->TopRowIndex != 0) {
                strip->At_48 = strip->At_48 - rows;
                SidebarPlayGlobal(Rules_008871E0->Sound190, 0x2000, 1.0f, 0);
            } else {
                SidebarPlayGlobal(Rules_008871E0->Sound700, 0x2000, 1.0f, 0);
            }
        }
        bool redraw = false;
        for (int k = 0; k < 4; ++k) {
            if (TabButtons_00B07C48[k].AI()) {
                redraw = true;
            }
        }
        if (redraw) {
            At_53A6 = 1;
            SidebarTouched_00B0B518 = 1;
            SidebarNeedsRedraw_00884B8F = 1;
            FlagToRedraw(0);
        }
    }
    if (!SellMode) {
        if (SellButton_00B07DF8.IsOn) {
            SellButton_00B07DF8.TurnOff();
        }
    }
    if (!RepairMode) {
        if (RepairButton_00B0B3A0.IsOn) {
            RepairButton_00B0B3A0.TurnOff();
        }
    }
    PowerClass::vf_10(key, mouse);
}
