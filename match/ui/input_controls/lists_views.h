// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Lists cluster declarations (UI input/controls module) that only this cluster uses: the CRT routines
//   it calls, the modifier key codes read by GadgetClass::Input and the edit cursor string. The gadget
//   classes themselves (Gadget, Control, List, CheckList, ColorList, Edit, DropList and the embedded
//   ShapeButton/Slider) are in ui_gadget.h; the surface, mouse, keyboard, colour and font views in
//   ui_common.h.
#ifndef GG_MATCH_UI_INPUT_CONTROLS_LISTS_VIEWS_H
#define GG_MATCH_UI_INPUT_CONTROLS_LISTS_VIEWS_H

#include "ui_gadget.h"

// LIBRARY: GAMEMD 0x7CA564 _swprintf
extern "C" int __cdecl _swprintf(wchar_t* dest, const wchar_t* format, ...);
// LIBRARY: GAMEMD 0x7CA405 wcslen
extern "C" unsigned __cdecl wcslen(const wchar_t* s);
// LIBRARY: GAMEMD 0x7C9A8D isgraph
extern "C" int __cdecl isgraph(int c);
// LIBRARY: GAMEMD 0x7C990E isalpha
extern "C" int __cdecl isalpha(int c);
// LIBRARY: GAMEMD 0x7C998C isdigit
extern "C" int __cdecl isdigit(int c);
// LIBRARY: GAMEMD 0x7C9A31 isalnum
extern "C" int __cdecl isalnum(int c);
// LIBRARY: GAMEMD 0x7C97D3 toupper
extern "C" int __cdecl toupper(int c);

// Modifier key codes, read by GadgetClass::Input in pairs (first/second key of each modifier).
// GLOBAL: GAMEMD 0xA8EC08 .. 0xA8EBFC — six key codes read in pairs: 0xA8EC08/0xA8EC0C, 0xA8EC00/0xA8EC04 and
// 0xA8EBF8/0xA8EBFC set modifier bits 1, 2 and 4.
extern int DAT_00A8EC08;
extern int DAT_00A8EC0C;
extern int DAT_00A8EC00;
extern int DAT_00A8EC04;
extern int DAT_00A8EBF8;
extern int DAT_00A8EBFC;

// The cursor string drawn after the text while editing.
// GLOBAL: GAMEMD 0x82076C — the cursor string.
extern wchar_t DAT_0082076C[];

#endif  // GG_MATCH_UI_INPUT_CONTROLS_LISTS_VIEWS_H
