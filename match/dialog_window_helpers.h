// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Declarations used by dialog_window_helpers.cpp: the module-scope globals and the functions it calls.
#ifndef GG_MATCH_DIALOG_WINDOW_HELPERS_H
#define GG_MATCH_DIALOG_WINDOW_HELPERS_H

#include <windows.h>
#include <commctrl.h>

// GLOBAL: GAMEMD 0xB732F0 -- the module handle.
extern HINSTANCE DAT_00B732F0;
// GLOBAL: GAMEMD 0xB72F54 / 0xB72F58 -- client extent of the reference dialog.
extern int DAT_00B72F54;
extern int DAT_00B72F58;
// GLOBAL: GAMEMD 0x849DE0 / 0x849DE4 -- target dialog extent.
extern int DAT_00849DE0;
extern int DAT_00849DE4;
// GLOBAL: GAMEMD 0xB7309C -- a tree-view drag is in progress.
extern bool DAT_00B7309C;
// GLOBAL: GAMEMD 0xB730A0 -- the tree view being dragged in.
extern HWND DAT_00B730A0;
// GLOBAL: GAMEMD 0xB730A8 -- the drag image list.
extern HIMAGELIST DAT_00B730A8;
// GLOBAL: GAMEMD 0xB73098 -- INI section the view state lives under.
extern const char* DAT_00B73098;
// STRING: GAMEMD 0x83370C -- "ComboBox"
extern const char STR_0083370C[];
// STRING: GAMEMD 0x849E34 -- "LV%d"
extern const char STR_00849E34[];
// STRING: GAMEMD 0x849E3C -- "SysListView32"
extern const char STR_00849E3C[];
// STRING: GAMEMD 0x849E4C -- "TV%d"
extern const char STR_00849E4C[];
// STRING: GAMEMD 0x849E54 -- "SysTreeView32"
extern const char STR_00849E54[];

#endif  // GG_MATCH_DIALOG_WINDOW_HELPERS_H
