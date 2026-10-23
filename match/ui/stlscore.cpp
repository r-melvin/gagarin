// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit stlscore.cpp. The name is the source-file string at 0x842178
//   in retail gamemd.exe v1.001, passed by the assert at 0x6c9254 inside this object's
//   code range (0x6c8c80-0x6c93ef). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.

#include "../core/trivial_tu223_methods.h"

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
// GLOBAL: GAMEMD 0xB0BF40
extern double DAT_00B0BF40;
// GLOBAL: GAMEMD 0xB0BF48
extern int DAT_00B0BF48;
// GLOBAL: GAMEMD 0xB0BF4C
extern int DAT_00B0BF4C;
// GLOBAL: GAMEMD 0xB0BF50
extern int DAT_00B0BF50;
// GLOBAL: GAMEMD 0xB0BF58
extern double DAT_00B0BF58;

// FUNCTION: GAMEMD 0x6C8CB0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_006C8CB0()
{
    DAT_00B0BF58 = DAT_00B0BEF0 / DAT_007F3F48;
}

// FUNCTION: GAMEMD 0x6C8CD0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_006C8CD0()
{
    DAT_00B0BF40 = DAT_007E1718 / DAT_00B0BF58;
}

// FUNCTION: GAMEMD 0x6C8E50
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_006C8E50()
{
    DAT_00B0BF50 = 0;
    DAT_00B0BF48 = 0x80;
    DAT_00B0BF4C = 0x80;
}

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

// Formats a number as text and posts it to a dialog control (custom message 0x4B2).
// FUNCTION: GAMEMD 0x006C8FA0
void FUN_006C8FA0(GG_HWND dialog, int controlId, int value)
{
    wchar_t text[32];
    swprintf(text, L"%d", value);
    GG_HWND item = GetDlgItem(dialog, controlId);
    SendMessageA(item, 0x4B2, 0, (long)text);
}
