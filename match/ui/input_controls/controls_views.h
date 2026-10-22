// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Controls cluster declarations (UI input/controls module) that only this cluster uses: the rules sound
//   index, the sound player, the region save/restore helpers and the CRT/winmm imports. Every offset and
//   argument layout is read off a retail gamemd.exe v1.001 instruction in one of the controls_*.cpp entries.
//   The gadget classes (Gauge, TriColorGauge, Slider, StaticButton, TextButton, ShapeButton, TextLabel,
//   Toggle) are in ui_gadget.h; the surface, mouse, colour and font views in ui_common.h.
#ifndef GG_MATCH_UI_INPUT_CONTROLS_CONTROLS_VIEWS_H
#define GG_MATCH_UI_INPUT_CONTROLS_CONTROLS_VIEWS_H

#include "ui_gadget.h"

// 0x750920 (VocClass::PlayGlobal): plays a sound by index; bound by address here.
void* __fastcall ControlsPlaySound(int index, unsigned pan, float volume, void* controller);
// The rules object behind [0x8871E0]; +0x6C4 holds a sound index.
struct ControlsRules
{
    char unknown_000[0x6C4];
    int TextSound;   // +0x6C4
};
GG_STATIC_ASSERT(offsetof(ControlsRules, TextSound) == 0x6C4);
// GLOBAL: GAMEMD 0x8871E0 -- the rules object.
extern ControlsRules* ControlsRulesInstance;
// IMPORT: GAMEMD 0x7E1530 (winmm timeGetTime)
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
// 0x4371D0 and 0x437290: capture the surface region to a buffer, and put it back
// (surface in ECX, rectangle in EDX, buffer on the stack, RET 4).
void __fastcall FUN_004371D0(Surface* surface, Rect* area, MemoryBuffer* buffer);
void __fastcall FUN_00437290(Surface* surface, Rect* area, MemoryBuffer* buffer);

#endif
