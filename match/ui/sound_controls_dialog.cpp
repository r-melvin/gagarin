// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The sound-controls dialog runner at 0x6B6230 of retail gamemd.exe v1.001; the string 0x840030
//   ("SoundControls: GameSpeed = %d, ...") names the dialog. Same shape as the game-controls
//   runner in game_controls_dialog.cpp.
//
// Address index: 0x6B6230
#include <windows.h>
#include "ui_updated_methods.h"
#include "game_options_class_methods.h"

// GLOBAL: GAMEMD 0xA8EB60
extern GameOptionsClass DAT_00A8EB60;
// GLOBAL: GAMEMD 0xA8E9A0
extern char DAT_00A8E9A0;
// GLOBAL: GAMEMD 0xB0B800
extern char DAT_00B0B800;

// FUNCTION: GAMEMD 0x622650 (decl; reloc) -- UI::BeginDialog.
HWND __fastcall UI_BeginDialog(unsigned short id, int (__stdcall* proc)(HWND, unsigned int, unsigned int, long),
                               int param);
// FUNCTION: GAMEMD 0x622800 (decl; reloc) -- UI::FocusOnWindow.
void __fastcall UI_FocusOnWindow(HWND window);
// FUNCTION: GAMEMD 0x6B6300 (decl; reloc) -- the dialog procedure.
int __stdcall FUN_006B6300(HWND window, unsigned int message, unsigned int wParam, long lParam);
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- debug log printf.
void FUN_004068E0(const char* format, ...);
// FUNCTION: GAMEMD 0x532100 (decl; reloc)
void __fastcall FUN_00532100(bool flag);
// FUNCTION: GAMEMD 0x622720 (decl; reloc)
void __fastcall FUN_00622720(HWND window);

// STRING: GAMEMD 0x840030
// FUNCTION: GAMEMD 0x6B6230
// PARTIAL: 91.8% -- retail pushes the proc and the zero before it loads the dialog id (the same
// instruction multiset; only the position of the id load differs).
// Run the sound-controls dialog: log the option values, open the dialog, pump
// until the dialog procedure stores a result (or the host asks to leave), then close it.
void FUN_006B6230()
{
    int result = -1;
    FUN_004068E0("SoundControls: GameSpeed = %d, ScrollRate = %d, Detail = %d\n",
                 DAT_00A8EB60.GameSpeed, DAT_00A8EB60.ScrollRate, DAT_00A8EB60.DetailLevel);
    DAT_00B0B800 = 0;
    unsigned short id = 0xD6;
    if (DAT_00A8E9A0) {
        id = 0xB8;
    }
    HWND window = UI_BeginDialog(id, FUN_006B6300, 0);
    if (window) {
        SetWindowLongA(window, DWL_USER, (LONG)&result);
        UI_FocusOnWindow(window);
        while (result == -1) {
            if (UI::Updated() == 1) {
                result = 2;
            }
            if (!DAT_00A8E9A0) {
                FUN_00532100(false);
            }
        }
        FUN_00622720(window);
    }
    FUN_004068E0("SoundControls: GameSpeed = %d, ScrollRate = %d, Detail = %d\n",
                 DAT_00A8EB60.GameSpeed, DAT_00A8EB60.ScrollRate, DAT_00A8EB60.DetailLevel);
}
