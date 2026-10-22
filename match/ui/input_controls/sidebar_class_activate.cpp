// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// SidebarClass slot 54 (show / hide the sidebar); layout and evidence:
// sidebar_class_layout.h.

#include "sidebar_class_layout.h"

// GLOBAL: GAMEMD 0xA8D5F8 -- bit 1 set while the game is in a restricted mode.
extern unsigned char DAT_00A8D5F8;
// GLOBAL: GAMEMD 0xA8B238 -- session game mode.
extern int GameMode_00A8B238;
// FUNCTION: GAMEMD 0x5BF450 (decl; reloc) -- releases the pump list.
void FUN_005BF450();

// Slot 54: shows or hides the sidebar (-1 toggles); registers or removes every gadget
// and rebuilds the visible cameo buttons.
//
// PARTIAL (86.0%, 197/229). Same instruction multiset as retail. Two differences:
// (1) retail pushes EBP and EDI only after the `changed` test (`JE 0x6A8078` skips the
// pops), cl pushes them together with EBX before it; (2) retail loads the scenario flag
// into EAX before `MOV EAX,0x1A`, cl hoists the constant above the flag load.
// Variants tried: the changed flag as a nested `if`, as an early `return changed`
// (worse: separate epilogue), as an int, recomputed at the end, `== true`; the margin
// as local flag, if/else both ways, negated test.
// FUNCTION: GAMEMD 0x6A7D70
bool SidebarClass::vf_54(int control)
{
    bool old = At_53A5;
    if (DAT_00A8D5F8 & 2) {
        if (GameMode_00A8B238 != 0 && GameMode_00A8B238 != 5) {
            return old;
        }
    }
    if (control != -1) {
        At_53A5 = (control == 1);
    } else {
        At_53A5 = (old == 0);
    }
    bool changed = At_53A5 != old;
    if (changed) {
        FUN_00652E50(At_53A5);
        if (At_53A5) {
            vf_34();
            At_53A6 = 1;
            SellButton_00B07DF8.Zap();
            AddButton(&SellButton_00B07DF8);
            RepairButton_00B0B3A0.Zap();
            AddButton(&RepairButton_00B0B3A0);
            for (int i = 0; i < 4; ++i) {
                TabButtons_00B07C48[i].Zap();
                TabButtons_00B07C48[i].At_2C = 0;
                AddButton(&TabButtons_00B07C48[i]);
            }
            ScrollDownButton_00B0B328.Zap();
            Map_0087F7E8.AddButton(&ScrollDownButton_00B0B328);
            ScrollUpButton_00B0B408.Zap();
            Map_0087F7E8.AddButton(&ScrollUpButton_00B0B408);
            ExtraButton_00B07E58.Zap();
            AddButton(&ExtraButton_00B07E58);
            ExtraGadget_00B04A10.Zap();
            AddButton(&ExtraGadget_00B04A10);
            for (int j = 0; j < 4; ++j) {
                Strips[j].TopRowIndex = 0;
                if (Strips[j].CameoCount > 0) {
                    TabButtons_00B07C48[j].Enable();
                }
            }
            TabButtons_00B07C48[unknown_539C].TurnOn();
            StripClass* strip = &Strips[unknown_539C];
            strip->At_1C = 1;
            int margin = 0x1A;
            if (Scenario_00A8B230->At_34B8) {
                margin = 0x12;
            }
            int rows = (DAT_00886F9C - StripY_00B0B4F8 - margin + DAT_00886F94 - 7) / 50 * 2;
            for (int k = 0; k < rows; ++k) {
                CameoButtons_00B07E80[strip->RowBase * 60 + k].Zap();
                MapInstance_0087F7E8.AddButton(&CameoButtons_00B07E80[strip->RowBase * 60 + k]);
            }
            SidebarNeedsRedraw_00884B8F = 1;
            FUN_006A6610();
            FlagToRedraw(2);
        } else {
            FUN_005BF450();
            vf_13(&SellButton_00B07DF8);
            vf_13(&RepairButton_00B0B3A0);
            vf_13(&ExtraButton_00B07E58);
            for (int i = 0; i < 4; ++i) {
                vf_13(&TabButtons_00B07C48[i]);
            }
            vf_13(&ScrollDownButton_00B0B328);
            vf_13(&ScrollUpButton_00B0B408);
            StripClass* strip = &Strips[unknown_539C];
            for (int k = 0; k < 60; ++k) {
                MapInstance_0087F7E8.FUN_004F4450(&CameoButtons_00B07E80[strip->RowBase * 60 + k]);
            }
            vf_13(&ExtraGadget_00B04A10);
            FlagToRedraw(2);
        }
    }
    return changed;
}
