// SPDX-License-Identifier: GPL-3.0-or-later
//   /Ob2: retail's __xc entries point straight at the initialiser bodies (no
//   out-of-line _$E thunk behind a jump).
// Provenance: own-binary-via-Ghidra
//   Original translation unit stlscore.cpp. The name is the source-file string at 0x842178
//   in retail gamemd.exe v1.001, passed by the assert at 0x6c9254 inside this object's
//   code range (0x6c8c80-0x6c93ef). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.

#include "../core/trivial_tu223_methods.h"
#include "../core/mathtbl_init_shapes.h"

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7F3F48
extern const double DAT_007F3F48;
// GLOBAL: GAMEMD 0xB0BEF0
extern double DAT_00B0BEF0;

// SYNTHETIC: GAMEMD 0x006C8CB0
// GLOBAL: GAMEMD 0x00B0BF58
double DAT_00B0BF58 = DAT_00B0BEF0 / DAT_007F3F48;

// SYNTHETIC: GAMEMD 0x006C8CD0
// GLOBAL: GAMEMD 0x00B0BF40
double DAT_00B0BF40 = DAT_007E1718 / DAT_00B0BF58;

// SYNTHETIC: GAMEMD 0x006C8E50
// GLOBAL: GAMEMD 0x00B0BF48
MathTblCoord DAT_00B0BF48;

// FUNCTION: GAMEMD 0x6C8E70
// Returns its receiver.
Obj_006C8E70* Obj_006C8E70::FUN_006C8E70()
{
    return this;
}

typedef void* GG_HWND;
// IAT 0x7E14A4: USER32!SendMessageA.
extern "C" __declspec(dllimport) long __stdcall SendMessageA(GG_HWND hWnd, unsigned uMsg, unsigned wParam, long lParam);
// IAT 0x7E14A8: USER32!GetDlgItem.
extern "C" __declspec(dllimport) GG_HWND __stdcall GetDlgItem(GG_HWND hDlg, int nID);
// 0x7CA564: the CRT swprintf (cdecl, varargs).
extern "C" int __cdecl swprintf(wchar_t* pszBuffer, const wchar_t* pszFormat, ...);

// Formats a number of seconds as hours, minutes and seconds and posts the text to a
// dialog control (custom message 0x4B2).
// FUNCTION: GAMEMD 0x006C8F10
void __fastcall FUN_006C8F10(GG_HWND dialog, int controlId, int seconds)
{
    wchar_t text[32];
    int minutes = seconds / 60;
    int hours = minutes / 60;
    // STRING: GAMEMD 0x842158 L"%02d:%02d:%02d"
    swprintf(text, L"%02d:%02d:%02d", hours, minutes - hours * 60, seconds - minutes * 60);
    GG_HWND item = GetDlgItem(dialog, controlId);
    SendMessageA(item, 0x4B2, 0, (long)text);
}

// Formats a number as text and posts it to a dialog control (custom message 0x4B2).
// FUNCTION: GAMEMD 0x006C8FA0
void FUN_006C8FA0(GG_HWND dialog, int controlId, int value)
{
    wchar_t text[32];
    swprintf(text, L"%d", value);
    GG_HWND item = GetDlgItem(dialog, controlId);
    SendMessageA(item, 0x4B2, 0, (long)text);
}
