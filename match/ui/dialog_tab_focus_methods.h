// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | private-ref-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 at 0x600C70. The
//   three indirect calls resolve through the import table: [0x7E14EC] is
//   USER32!GetParent, [0x7E14F0] is USER32!GetNextDlgTabItem and [0x7E13CC] is
//   USER32!SetFocus, so the call sites are `__declspec(dllimport)` forms.
//
//   Convention facts: the control handle arrives in ECX and the direction flag
//   in EDX with no stack cleanup at the call sites, so this is __fastcall. The
//   `AND ESI,0xFF` ahead of the push is the flag widening to
//   GetNextDlgTabItem's `BOOL` parameter, which pins the source parameter to a
//   one-byte type. The `MOV AL,1` / `XOR AL,AL` exits pin the return to a
//   one-byte bool.
//
//   The private-reference seed files this under audio/voc_codec.cpp; that is a grouping
//   artefact. The function is a Win32 dialog keyboard-navigation helper and has
//   nothing to do with audio.
#ifndef GG_MATCH_UI_DIALOG_TAB_FOCUS_METHODS_H
#define GG_MATCH_UI_DIALOG_TAB_FOCUS_METHODS_H

typedef void* GG_HWND;

extern "C" __declspec(dllimport) GG_HWND __stdcall GetParent(GG_HWND hWnd);          // IAT 0x7E14EC
extern "C" __declspec(dllimport) GG_HWND __stdcall GetNextDlgTabItem(GG_HWND hDlg,
                                                                    GG_HWND hCtl,
                                                                    int bPrevious);  // IAT 0x7E14F0
extern "C" __declspec(dllimport) GG_HWND __stdcall SetFocus(GG_HWND hWnd);           // IAT 0x7E13CC

// FUNCTION: GAMEMD 0x600C70 (__fastcall)
bool __fastcall FUN_00600C70(GG_HWND hCtl, unsigned char bPrevious);

#endif  // GG_MATCH_UI_DIALOG_TAB_FOCUS_METHODS_H
