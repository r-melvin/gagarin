// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, slots and conventions read numerically off the user's retail gamemd.exe v1.001 via the local Ghidra
//   CLI and REA (entry disassembly at 0x6922E0, 0x693060, 0x693840, 0x693880, 0x6938C0, 0x6938F0) and the RTTI
//   vtable .?AVScrollClass@@ at 0x7F1094 (55 slots, vtable_slots.json census).
//
// Layout evidence for the ScrollClass entries (the classes themselves are in ui_display_chain.h):
//   * 0x6938F0 destroys the 75 cameos (0x34 bytes, empty destructor 0x40D260) of each of the four 0xF94-byte strips
//     at +0x1544 (cameos at strip +0x58, so the walk starts at +0x159C), then calls the RadarClass destructor body
//     0x652C00;
//   * 0x692290 calls the TabClass constructor 0x6CFE20, initialises +0x5548 .. +0x555A and stores both vptrs (0x7F1094
//     at +0, 0x7F108C on the INoticeSink sub-object at +0x5518);
//   * +0x555A, +0x5558, +0x5550, +0x5554 are read or written by the slots below.
#ifndef GG_MATCH_UI_INPUT_CONTROLS_DISPLAY_SCROLL_H
#define GG_MATCH_UI_INPUT_CONTROLS_DISPLAY_SCROLL_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "display_class.h"

extern "C" __declspec(dllimport) void* __stdcall GetCapture(void);
extern "C" __declspec(dllimport) int __stdcall ReleaseCapture(void);

// GLOBAL: GAMEMD 0xB73550 -- the window handle the capture is compared with.
extern void* DisplayCaptureWindow_00B73550;
// GLOBAL: GAMEMD 0xA8ED9C
extern bool DisplayFlag_00A8ED9C;
// GLOBAL: GAMEMD 0x884D44
extern bool DisplayFlag_00884D44;

// RadarClass, PowerClass, SidebarClass, TabClass (with INoticeSink) and ScrollClass are declared in
// ui_display_chain.h.

#endif  // GG_MATCH_UI_INPUT_CONTROLS_DISPLAY_SCROLL_H
