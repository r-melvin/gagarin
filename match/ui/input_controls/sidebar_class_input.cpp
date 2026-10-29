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
    if (DAT_00A8B230->unknown_34B8) {
        margin = 0x12;
    }
    return (DAT_00886F9C - margin - StripY_00B0B4F8 + DAT_00886F94 - 7) / 50;
}

// Slot 10: per-frame sidebar input: scrolls the open/close animation, toggles the
// observer panel state, handles the hotkeys for sell/repair/tab/scroll and ticks the
// buttons.
//
// PARTIAL 46.6% (multiset: retail-only `sub`, `jmp`, `jge`; ours `mov` 3, `jl`). The
// observer toggle is a `switch (control)` with `case 1` (retail's `dec eax; jz`), the old
// state is kept as the field's own byte type (no `setne`), and the scroll-down test is
// one condition so cl branches on each compare instead of materialising a flag (`setl`).
// The PlayGlobal pan is declared after the volume. Remaining: retail shares one
// PlayGlobal(Sound190) tail between the tab and scroll-down paths and lays the scroll arms
// after the epilogue. Earlier attempts: the toggle as if/else of 1/0 (folded to `sete`),
// the key dispatch as a `switch (code)` (jump table, 26.3%).
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
        unsigned char old = At_5514;
        if (control == -1) {
            control = (old == 0);
        }
        switch (control) {
        case 1:
            At_5514 = true;
            break;
        default:
            At_5514 = false;
            break;
        }
        if (old != At_5514) {
            FlagToRedraw(0);
            At_53A6 = 1;
            if (!At_5514) {
                vf_18(0, 0);
            }
        }
        int code = *key;
        if (code == 0x8066) {
            VocClass::PlayGlobal(Rules_008871E0->Sound188, 1.0f, 0x2000, 0);
            SetSellMode_004AC660(-1);
        } else if (code == 0x8065) {
            VocClass::PlayGlobal(Rules_008871E0->Sound188, 1.0f, 0x2000, 0);
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
            VocClass::PlayGlobal(Rules_008871E0->Sound190, 1.0f, 0x2000, 0);
        } else if ((code & ~0x4000) == (ScrollDownButton_00B0B328.ID | 0x8000)) {
            ScrollDownButton_00B0B328.At_2C = 0;
            StripClass* strip = &Strips[unknown_539C];
            int step = SidebarRowCount();
            if (CurrentPlayer_00A83D4C == Observer_00AC1198) {
                step = 1;
            }
            int rows = SidebarRowCount();
            if ((CurrentPlayer_00A83D4C == Observer_00AC1198
                    && strip->TopRowIndex + rows / 2 < ObserverRowLimit_00884CF8)
                || (CurrentPlayer_00A83D4C != Observer_00AC1198
                    && (strip->TopRowIndex + rows) * 2 < strip->CameoCount)) {
                strip->At_48 = strip->At_48 + step;
                VocClass::PlayGlobal(Rules_008871E0->Sound190, 1.0f, 0x2000, 0);
            } else {
                VocClass::PlayGlobal(Rules_008871E0->Sound700, 1.0f, 0x2000, 0);
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
                VocClass::PlayGlobal(Rules_008871E0->Sound190, 1.0f, 0x2000, 0);
            } else {
                VocClass::PlayGlobal(Rules_008871E0->Sound700, 1.0f, 0x2000, 0);
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
