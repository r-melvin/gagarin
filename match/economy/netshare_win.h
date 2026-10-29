// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Window-system declarations for the netshare.cpp block of retail .text
//   (0x5E2430..0x5EF18F). The unit's own path, "D:\ra2mdpost\netshare.cpp",
//   sits at 0x8317D8 and is pushed with its line numbers by the string-table
//   fetches in 0x5E87A0 (see netshare_slot_nodes.h). Everything declared here
//   was read off the user's retail gamemd.exe v1.001 with the local Ghidra CLI
//   at the call sites cited beside each declaration. Names are retail CRT
//   (identified by bytes), import, or address placeholders.
#ifndef GG_MATCH_ECONOMY_NETSHARE_WIN_H
#define GG_MATCH_ECONOMY_NETSHARE_WIN_H

// netshare_slot_nodes.h names a global LocalHandle (0xA8B380, the local player's
// handle); <windows.h> declares a Win32 function of that name. This unit never
// calls the Win32 one, so it is renamed for the duration of the include.
#define LocalHandle LocalHandle_Win32
#include <windows.h>
#undef LocalHandle
#include "netshare_common.h"

// FUNCTION: GAMEMD 0x775B10 (decl; reloc) -- the current dialog window.
HWND __cdecl FUN_00775B10();
// FUNCTION: GAMEMD 0x775B20 (decl; reloc) -- the current dialog's template id.
int __cdecl FUN_00775B20();
// FUNCTION: GAMEMD 0x7759B0 (decl; reloc) -- __fastcall: a window's parent dialog.
HWND FUN_007759B0(HWND window);
// FUNCTION: GAMEMD 0x775690 (decl; reloc) -- __fastcall: a control's rectangle.
void FUN_00775690(HWND window, RECT* rect);

#include "../renderer/bit_font.h"
// GLOBAL: GAMEMD 0x89C4D0
extern BitFont* DAT_0089C4D0;

// The slot-control helpers of the lobby dialog (all __fastcall; the trailing
// stacked value of the setters is popped by the callee).
// FUNCTION: GAMEMD 0x4E37D0 (decl; reloc) -- the start-position control of a slot index.
int FUN_004E37D0(int index);
// FUNCTION: GAMEMD 0x4E41D0 (decl; reloc) -- the house control of a slot index.
int FUN_004E41D0(int index);
// FUNCTION: GAMEMD 0x4E4E60 (decl; reloc) -- the colour control of a slot index.
int FUN_004E4E60(int index);
// FUNCTION: GAMEMD 0x4E5940 (decl; reloc) -- the team control of a slot index.
int FUN_004E5940(int index);
// FUNCTION: GAMEMD 0x4E3F70 (decl; reloc) -- set the start-position control, RET 4.
void FUN_004E3F70(HWND dialog, int control, int value);
// FUNCTION: GAMEMD 0x4E49A0 (decl; reloc) -- set the house control, RET 4.
void FUN_004E49A0(HWND dialog, int control, int value);
// FUNCTION: GAMEMD 0x4E5480 (decl; reloc) -- set the colour control, RET 4.
void FUN_004E5480(HWND dialog, int control, int value);
// FUNCTION: GAMEMD 0x4E5ED0 (decl; reloc) -- set the team control, RET 4.
void FUN_004E5ED0(HWND dialog, int control, int value);
// FUNCTION: GAMEMD 0x5E6520 (decl; reloc) -- __fastcall: the number of players a map supports.
int FUN_005E6520(int index);
// FUNCTION: GAMEMD 0x5E9E70, 0x5EA0D0, 0x5EA180
void FUN_005E9E70(HWND dialog, int slot, unsigned char enable);

// FUNCTION: GAMEMD 0x5E2CD0 (also declared in network/wonline.cpp).
int FUN_005E2CD0(const wchar_t* text, int buttons, void* callback, bool flag);
// FUNCTION: GAMEMD 0x5E2E40
int __stdcall FUN_005E2E40(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

// FUNCTION: GAMEMD 0x5E2670
unsigned int FUN_005E2670(Obj_007B66D0* text);
// FUNCTION: GAMEMD 0x5E2820
void FUN_005E2820(int param, const wchar_t* text, HWND window);
// FUNCTION: GAMEMD 0x5E29A0
void FUN_005E29A0(HWND window, const wchar_t* text, int length, int param);

#endif  // GG_MATCH_ECONOMY_NETSHARE_WIN_H
