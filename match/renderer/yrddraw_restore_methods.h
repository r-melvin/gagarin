// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, globals and imports read off the user's retail gamemd.exe v1.001
//   via the local Ghidra CLI at 0x4A44F0: the DirectDraw object pointer at
//   0x8A0094 with its COM slots +0x4C (RestoreDisplayMode) and +0x08
//   (Release), the error callback at 0x8A00B0 (ECX = HRESULT), the three
//   dwords cleared at 0x8A00A4/A8/AC, the main window at 0xB73550, the CRT
//   sprintf at 0x7C8EF4 and the MessageBoxA import 0x7E1460 loaded once and
//   called through ESI. YRpp (consult-only, no LICENSE) names Restore.
#ifndef GG_MATCH_RENDERER_YRDDRAW_RESTORE_METHODS_H
#define GG_MATCH_RENDERER_YRDDRAW_RESTORE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "direct_draw_interface_view.h"

// GLOBAL: GAMEMD 0x8A00A4 / 0x8A00A8 / 0x8A00AC — display mode width, height, depth.
extern int DAT_008A00A4;
extern int DAT_008A00A8;
extern int DAT_008A00AC;
// GLOBAL: GAMEMD 0x8A00B0 — the DirectDraw error callback.
extern void (__fastcall* DAT_008A00B0)(long hr);
// GLOBAL: GAMEMD 0xB73550 — the main window.
extern void* DAT_00B73550;

// STRING: GAMEMD 0x81FC7C / 0x81FC70 — the two message-box strings.

// FUNCTION: GAMEMD 0x4A44F0 — YRDDraw::Restore.
void YRDDraw_Restore();

#endif  // GG_MATCH_RENDERER_YRDDRAW_RESTORE_METHODS_H
