// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// The GameDlg.CPP block of retail .text (0x4E1B10..0x4E244F): three of the
// unit's header initialisers, the game-controls dialog (runner 0x4E1D00,
// apply 0x4E1DE0, dialog procedure 0x4E1FE0), a command handler 0x4E23C0 and
// the unit's last initialiser 0x4E2440, in retail address order. The string
// 0x82280C ("GameControls: GameSpeed = %d, ...") names the dialog.
// VC6FLAGS: /nologo /c /O2 /Gr /Ob2 /DNDEBUG /Gy /MT

#include <windows.h>
#include "game_options_class_methods.h"
#include "tooltip_manager_shared.h"
#include "../network/event_queue.h"
#include "../_layout/house_class.h"
#include "../core/header_tuning_globals.h"

// ---- run-time initialised copies of the shared tuning globals -----------------------------------------------------

// GLOBAL: GAMEMD 0x8B3EB8
extern double DAT_008B3EB8;
// GLOBAL: GAMEMD 0x7E9370
const double DAT_007E9370 = 60.0;

// SYNTHETIC: GAMEMD 0x4E1B40
// GLOBAL: GAMEMD 0x8B3F08
double DAT_008B3F08 = DAT_008B3EB8 / DAT_007E9370;
// SYNTHETIC: GAMEMD 0x4E1B60
// GLOBAL: GAMEMD 0x8B3EF0
double DAT_008B3EF0 = 1.0 / DAT_008B3F08;
// SYNTHETIC: GAMEMD 0x4E1CE0
// GLOBAL: GAMEMD 0x8B3EF8
TuningCoordInit DAT_008B3EF8(128, 128, 0);

// ---- globals and helpers ------------------------------------------------------------------------------------------

// GLOBAL: GAMEMD 0xA8EB60
extern GameOptionsClass DAT_00A8EB60;
// GLOBAL: GAMEMD 0xA8E9A0
extern char DAT_00A8E9A0;
// GLOBAL: GAMEMD 0xA8B238 -- the session game mode.
extern int DAT_00A8B238;
// GLOBAL: GAMEMD 0xA8EDA0
extern int DAT_00A8EDA0;
// GLOBAL: GAMEMD 0xA83D4C -- the player's house.
extern HouseClass* DAT_00A83D4C;
// GLOBAL: GAMEMD 0x887368 -- the tool-tip manager.
extern ToolTipManager* DAT_00887368;

// GLOBAL: GAMEMD 0xA802C8 -- the outgoing event queue.
extern EventQueue<128> DAT_00A802C8;

// STRING: GAMEMD 0x82280C
// "GameControls: GameSpeed = %d, ScrollRate = %d, Detail = %d\n"

// GLOBAL: GAMEMD 0x87F7E8 -- the map; 0x4AE450 applies a new detail level.
#include "../_layout/map_0087f7e8.h"
extern Map_0087F7E8 DAT_0087F7E8;

// FUNCTION: GAMEMD 0x622650 (decl; reloc)
void* UI_BeginDialog(unsigned short id, int (__stdcall* proc)(void*, unsigned, unsigned, long), int arg);
// FUNCTION: GAMEMD 0x622720 (decl; reloc)
void UI_EndDialog(void* window);
// FUNCTION: GAMEMD 0x622800 (decl; reloc)
void UI_FocusOnWindow(HWND hWnd);
struct UI
{
    // FUNCTION: GAMEMD 0x623120 (decl; reloc)
    static bool Updated();
};
// FUNCTION: GAMEMD 0x532100 (decl; reloc) -- __fastcall, one byte flag.
void FUN_00532100(bool flag);
// FUNCTION: GAMEMD 0x70D180 (decl; reloc) -- __fastcall, one byte flag.
void FUN_0070D180(bool flag);

// FUNCTION: GAMEMD 0x622B50 (decl; reloc) -- __fastcall, the shared dialog message filter.
int FUN_00622B50(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- __fastcall string-table lookup.
wchar_t* StringTable_LoadString(const char* label, int* out, const char* file, int line);
// FUNCTION: GAMEMD 0x407000 (decl; reloc) -- the caller passes the whole EAX on.
int __cdecl FUN_00407000();
// GLOBAL: GAMEMD 0xA8EDDC
extern bool DAT_00A8EDDC;
// GLOBAL: GAMEMD 0xA8B538
extern int DAT_00A8B538;

// The slider captions: game speed, scroll rate, detail and difficulty.
// GLOBAL: GAMEMD 0x822730
extern const char* DAT_00822730[];
// GLOBAL: GAMEMD 0x82274C
extern const char* DAT_0082274C[];
// GLOBAL: GAMEMD 0x822768
extern const char* DAT_00822768[];
// GLOBAL: GAMEMD 0x822774
extern const char* DAT_00822774[];

// FUNCTION: GAMEMD 0x4E1FE0 (decl; reloc) -- the dialog procedure.
int __stdcall FUN_004E1FE0(void* window, unsigned message, unsigned wParam, long lParam);
void FUN_004E23C0(HWND window, int command, HWND control, unsigned notify);

// The game-controls dialog: its window handle.
struct Obj_004E1D00
{
    HWND Window;   // +0x00

    // FUNCTION: GAMEMD 0x4E1D00
    void FUN_004E1D00();
    // FUNCTION: GAMEMD 0x4E1DE0
    void FUN_004E1DE0();
};

// Queue an event for sending (drops it when the queue is full).
static inline void OutList_Add(const EventClass& event)
{
    if (DAT_00A802C8.Count < 128) {
        DAT_00A802C8.List[DAT_00A802C8.Head] = event;
        DAT_00A802C8.Time[DAT_00A802C8.Head] = timeGetTime();
        DAT_00A802C8.Head = (DAT_00A802C8.Head + 1) & 127;
        DAT_00A802C8.Count++;
    }
}

// FUNCTION: GAMEMD 0x4E1D00
void Obj_004E1D00::FUN_004E1D00()
{
    int result = -1;
    FUN_004068E0("GameControls: GameSpeed = %d, ScrollRate = %d, Detail = %d\n",
                 DAT_00A8EB60.GameSpeed, DAT_00A8EB60.unknown_10, DAT_00A8EB60.unknown_18);
    if (DAT_00A8E9A0 == 1) {
        Window = (HWND)UI_BeginDialog(0xBBB, FUN_004E1FE0, 0);
    } else {
        Window = (HWND)UI_BeginDialog(0xF5, FUN_004E1FE0, 0);
    }
    if (Window) {
        SetWindowLongA(Window, DWL_USER, (LONG)&result);
        UI_FocusOnWindow(Window);
        while (result == -1) {
            if (UI::Updated() == 1) {
                result = 2;
            }
            if (!DAT_00A8E9A0) {
                FUN_00532100(false);
            }
        }
        if (result == 1) {
            FUN_004E1DE0();
            DAT_00A8EB60.FUN_005FAD10();
        }
        UI_EndDialog(Window);
    }
    FUN_004068E0("GameControls: GameSpeed = %d, ScrollRate = %d, Detail = %d\n",
                 DAT_00A8EB60.GameSpeed, DAT_00A8EB60.unknown_10, DAT_00A8EB60.unknown_18);
}

// FUNCTION: GAMEMD 0x4E1DE0
void Obj_004E1D00::FUN_004E1DE0()
{
    HWND item = GetDlgItem(Window, 0x529);
    if (item) {
        int speed = 6 - SendMessageA(item, 0x400, 0, 0);
        if (DAT_00A8EB60.GameSpeed != speed) {
            if (DAT_00A8E9A0 == 1 && DAT_00A8B238 != 0 && DAT_00A8B238 != 5) {
                OutList_Add(EventClass(DAT_00A83D4C->ArrayIndex, 0xD, speed));
            } else {
                DAT_00A8EB60.GameSpeed = speed;
            }
        }
    }
    item = GetDlgItem(Window, 0x52A);
    if (item) {
        DAT_00A8EB60.unknown_10 = 6 - SendMessageA(item, 0x400, 0, 0);
    }
    item = GetDlgItem(Window, 0x52B);
    if (item) {
        int detail = SendMessageA(item, 0x400, 0, 0);
        if (DAT_00A8EB60.unknown_18 != detail) {
            DAT_00A8EB60.unknown_18 = detail;
            DAT_0087F7E8.FUN_004AE450();
        }
    }
    item = GetDlgItem(Window, 0x601);
    if (item) {
        DAT_00A8EB60.unknown_1E = SendMessageA(item, BM_GETCHECK, 0, 0) == 1;
        FUN_0070D180(DAT_00A8EB60.unknown_1E);
    }
    item = GetDlgItem(Window, 0x604);
    if (item) {
        DAT_00A8EB60.unknown_1F = SendMessageA(item, BM_GETCHECK, 0, 0) == 1;
    }
    item = GetDlgItem(Window, 0x602);
    if (item) {
        DAT_00A8EB60.unknown_20 = SendMessageA(item, BM_GETCHECK, 0, 0) == 1;
        if (DAT_00887368 && DAT_00A8E9A0 == 1) {
            DAT_00887368->SetState(DAT_00A8EB60.unknown_20);
        }
    }
    if (!DAT_00A8E9A0) {
        item = GetDlgItem(Window, 0x50F);
        if (item) {
            DAT_00A8EB60.unknown_04 = SendMessageA(item, 0x400, 0, 0);
        }
    }
}

// The scroll handler of the dialog procedure (inlined there).
static inline void Inline_004E1FE0_a(HWND window, HWND control, WPARAM wParam)
{
    if (LOWORD(wParam) != SB_THUMBTRACK) {
        return;
    }
    unsigned position = HIWORD(wParam);
    const char* label;
    HWND text;
    if (control == GetDlgItem(window, 0x529)) {
        label = DAT_00822730[position];
        text = GetDlgItem(window, 0x671);
    } else if (control == GetDlgItem(window, 0x52A)) {
        label = DAT_0082274C[position];
        text = GetDlgItem(window, 0x672);
    } else if (control == GetDlgItem(window, 0x52B)) {
        label = DAT_00822768[position];
        text = GetDlgItem(window, 0x673);
    } else {
        if (DAT_00A8E9A0) {
            return;
        }
        if (control != GetDlgItem(window, 0x50F)) {
            return;
        }
        label = DAT_00822774[position];
        text = GetDlgItem(window, 0x670);
    }
    if (text) {
        SendMessageA(text, 0x4B2, 0, (LPARAM)StringTable_LoadString(label, 0, "D:\\ra2mdpost\\GameDlg.CPP", 0x1B2));
    }
}

// Hide the game-speed slider, its frame and its caption.
static inline void Inline_004E1FE0_b(HWND window)
{
    HWND item = GetDlgItem(window, 0x529);
    ShowWindow(item, SW_HIDE);
    item = GetDlgItem(window, 0x714);
    ShowWindow(item, SW_HIDE);
    item = GetDlgItem(window, 0x671);
    ShowWindow(item, SW_HIDE);
}

// FUNCTION: GAMEMD 0x4E1FE0
int __stdcall FUN_004E1FE0(void* hwnd, unsigned message, unsigned wParam, long lParam)
{
    HWND window = (HWND)hwnd;
    int result = FUN_00622B50(window, message, wParam, lParam);
    if (result) {
        return result;
    }
    switch (message) {
    case WM_COMMAND:
        FUN_004E23C0(window, LOWORD(wParam), (HWND)lParam, HIWORD(wParam));
        break;
    case WM_HSCROLL:
        Inline_004E1FE0_a(window, (HWND)lParam, wParam);
        break;
    case 0x497: {
        HWND item = GetDlgItem(window, 0x529);
        if (DAT_00A8B238 == 0 && !DAT_00A8EDDC) {
            ShowWindow(item, SW_HIDE);
            item = GetDlgItem(window, 0x714);
            ShowWindow(item, SW_HIDE);
            item = GetDlgItem(window, 0x671);
            ShowWindow(item, SW_HIDE);
        } else if (item) {
            SendMessageA(item, 0x4AC, 0, 0);
            SendMessageA(item, 0x406, 1, 0x60000);
            SendMessageA(item, 0x405, 1, 6 - DAT_00A8EB60.GameSpeed);
        }
        if (DAT_00A8B538) {
            Inline_004E1FE0_b(window);
            if (DAT_00A8B538) {
                Inline_004E1FE0_b(window);
            }
        }
        item = GetDlgItem(window, 0x52A);
        if (item) {
            SendMessageA(item, 0x4AC, 0, 0);
            SendMessageA(item, 0x406, 1, 0x60000);
            SendMessageA(item, 0x405, 1, 6 - DAT_00A8EB60.unknown_10);
        }
        item = GetDlgItem(window, 0x52B);
        if (item) {
            SendMessageA(item, 0x4AC, 0, 0);
            SendMessageA(item, 0x406, 1, 0x20000);
            SendMessageA(item, 0x405, 1, DAT_00A8EB60.unknown_18);
        }
        item = GetDlgItem(window, 0x601);
        if (item) {
            SendMessageA(item, BM_SETCHECK, DAT_00A8EB60.unknown_1E != 0, 0);
        }
        item = GetDlgItem(window, 0x604);
        if (item) {
            SendMessageA(item, BM_SETCHECK, DAT_00A8EB60.unknown_1F != 0, 0);
        }
        item = GetDlgItem(window, 0x602);
        if (item) {
            SendMessageA(item, BM_SETCHECK, DAT_00A8EB60.unknown_20 != 0, 0);
        }
        if (DAT_00A8E9A0 == 1) {
            item = GetDlgItem(window, 0x52D);
            if (item) {
                EnableWindow(item, FUN_00407000());
            }
        } else {
            item = GetDlgItem(window, 0x50F);
            if (item) {
                SendMessageA(item, 0x4AC, 0, 0);
                SendMessageA(item, 0x406, 1, 0x20000);
                SendMessageA(item, 0x405, 1, DAT_00A8EB60.unknown_04);
            }
        }
        break;
    }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x4E23C0
// A command handler: ECX = the window, EDX = the command id, then two stack words.
void FUN_004E23C0(HWND window, int command, HWND control, unsigned notify)
{
    int* result = (int*)GetWindowLongA(window, DWL_USER);
    switch (command) {
    case 0x52C:
        if (notify == 0 && DAT_00A8E9A0 == 1) {
            DAT_00A8EDA0 = 4;
            *result = 1;
        }
        break;
    case 0x52D:
        if (notify == 0 && DAT_00A8E9A0 == 1) {
            DAT_00A8EDA0 = 6;
            *result = 1;
        }
        break;
    case 0x686:
        *result = 1;
        break;
    }
}

// SYNTHETIC: GAMEMD 0x4E2440
// GLOBAL: GAMEMD 0x8B3F14
DWORD DAT_008B3F14 = timeGetTime();

// FUNCTION: GAMEMD 0x4E2480
// Milliseconds since the start-up reading; one fewer when the timer has wrapped.
DWORD FUN_004E2480()
{
    DWORD now = timeGetTime();
    if (now <= DAT_008B3F14) {
        return now - DAT_008B3F14 - 1;
    }
    return now - DAT_008B3F14;
}
