// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit MainOpt.cpp. The name is the source-file string at 0x82a2a8
//   in retail gamemd.exe v1.001, passed by the assert at 0x55f9c4 inside this object's
//   code range (0x55f780-0x56170f). Functions are in ascending retail address order.

#include "game_options_class_methods.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include <windows.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7ED3B0
extern const double DAT_007ED3B0;
// GLOBAL: GAMEMD 0xABCE40
extern double DAT_00ABCE40;
// GLOBAL: GAMEMD 0xABCF30
extern double DAT_00ABCF30;
// GLOBAL: GAMEMD 0xABCF38
extern int DAT_00ABCF38;
// GLOBAL: GAMEMD 0xABCF3C
extern int DAT_00ABCF3C;
// GLOBAL: GAMEMD 0xABCF40
extern int DAT_00ABCF40;
// GLOBAL: GAMEMD 0xABCF48
extern double DAT_00ABCF48;

// dynamic initializer for DAT_00ABCF48

// GLOBAL: GAMEMD 0x00ABCF48
extern double DAT_00ABCF48;

// dynamic initializer for DAT_00ABCF30

// GLOBAL: GAMEMD 0x00ABCF30
extern double DAT_00ABCF30;

// SYNTHETIC: GAMEMD 0x55F970 -- initialiser: constructs DAT_00ABCE70 (GameOptionsClass::GameOptionsClass, 0x5FA350).
// GLOBAL: GAMEMD 0xABCE70
GameOptionsClass DAT_00ABCE70;

// GLOBAL: GAMEMD 0x82A2A8 -- "D:\\ra2mdpost\\MainOpt.cpp", the build path handed to the label lookup.
extern const char DAT_0082A2A8[];

// FUNCTION: GAMEMD 0x622B50 (decl; reloc) -- the shared dialog message handler.
int __fastcall FUN_00622B50(HWND h, UINT msg, WPARAM w, LPARAM l);

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- resolve a label to its localised
// text; __fastcall with the file and line on the stack, RET 8.
const wchar_t* FUN_00734E60(const char* label, int flags, const char* file, int line);

// FUNCTION: GAMEMD 0x55F980
// Dialog procedure of the "about to try mode" confirmation: after the shared
// handler declines, control 0x5C1 stores 1 and 0x6CA stores 2 in the result slot
// kept in the window's user data; on init message 0x497 the prompt text is
// set on control 0x5DB.
int __stdcall FUN_0055F980(HWND h, UINT msg, WPARAM w, LPARAM l)
{
    int handled = FUN_00622B50(h, msg, w, l);
    if (handled != 0) {
        return handled;
    }
    int* pResult = (int*)GetWindowLongA(h, 8);
    switch (msg) {
    case 0x497: {
        const wchar_t* text = FUN_00734E60("TXT_ABOUT_TO_TRY_MODE", 0, DAT_0082A2A8, 0xA2);
        HWND item = GetDlgItem(h, 0x5DB);
        SendMessageA(item, 0x4B2, 0, (LPARAM)text);
        return 0;
    }
    case 0x111:
        switch (w & 0xFFFF) {
        case 0x5C1:
            *pResult = 1;
            break;
        case 0x6CA:
            *pResult = 2;
            return 0;
        }
        break;
    }
    return 0;
}

// FUNCTION: GAMEMD 0x561350
// Dialog procedure of the mode-change confirmation; same shape as 0x55F980 with
// the "GUI:ConfirmModeChange" prompt.
int __stdcall FUN_00561350(HWND h, UINT msg, WPARAM w, LPARAM l)
{
    int handled = FUN_00622B50(h, msg, w, l);
    if (handled != 0) {
        return handled;
    }
    int* pResult = (int*)GetWindowLongA(h, 8);
    switch (msg) {
    case 0x497: {
        const wchar_t* text = FUN_00734E60("GUI:ConfirmModeChange", 0, DAT_0082A2A8, 0x5DD);
        HWND item = GetDlgItem(h, 0x5DB);
        SendMessageA(item, 0x4B2, 0, (LPARAM)text);
        return 0;
    }
    case 0x111:
        switch (w & 0xFFFF) {
        case 0x5C1:
            *pResult = 1;
            break;
        case 0x6CA:
            *pResult = 2;
            return 0;
        }
        break;
    }
    return 0;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x82A2A8
extern const char DAT_0082A2A8[] = "D:\\ra2mdpost\\MainOpt.cpp";
// END defined globals
