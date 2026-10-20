// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x6D2420: the coordinate is read as `[EBP]`,
//   `[EBP+4]`, `[EBP+8]` (X, Y, Z) off the first stacked argument and the
//   second indexes the float table at 0x8428EC (`[EAX*4+0x8428EC]`, stored
//   to `[ESI+0xD8]`); `[ESI+0xDC]` is zeroed; the 60x30 iso projection is
//   inlined with the Y spill/reload through `[ESP+0x14]` and AdjustForZ
//   (0x6D20E0) inlined with its bias in the dead second parameter slot
//   (`FMUL [0xB0CD48]`, `FADD [0x7E1738]`, CRT __ftol 0x7C5F00); the view
//   offset is `[ESI+0xB0]` / `[ESI+0xB4]` (subtracted and added back); the
//   results land in `[ESI+0xD0]` / `[ESI+0xD4]` and the current position
//   `[ESI+0xD64]` / `[ESI+0xD68]` is copied to `[ESI+0xC8]` / `[ESI+0xCC]`.
//   Method name from YRpp TacticalClass.h (consult-only; name only).
#ifndef GG_MATCH_UI_TACTICAL_CLASS_FOCUS_METHODS_H
#define GG_MATCH_UI_TACTICAL_CLASS_FOCUS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Point2D_006D2420
{
    int X;                    // +0x0000
    int Y;                    // +0x0004
};
GG_STATIC_ASSERT(sizeof(Point2D_006D2420) == 0x8);

struct Coord_006D2420
{
    int X;                    // +0x0000
    int Y;                    // +0x0004
    int Z;                    // +0x0008
};
GG_STATIC_ASSERT(offsetof(Coord_006D2420, Z) == 0x8);

// GLOBAL: GAMEMD 0xB0CD48 — the height-to-pixel scale (runtime-initialised
// double; zero in the image).
extern double DAT_00B0CD48;

// GLOBAL: GAMEMD 0x8428EC — per-speed scroll step table (float; 0.0015,
// 0.003, 0.0075, 0.03, ...).
extern float DAT_008428EC[];

struct Tactical_006D2420
{
    char             _pad000[0xB0];          // +0x0000
    Point2D_006D2420 Offset_B0;              // +0x00B0  view offset (X, Y)
    char             _padB8[0xC8 - 0xB8];    // +0x00B8
    Point2D_006D2420 FocusStart;             // +0x00C8  position the focus move starts from
    Point2D_006D2420 FocusTarget;            // +0x00D0  screen point to reach
    float            FocusStep;              // +0x00D8
    int              At_DC;                  // +0x00DC  progress, reset to 0
    char             _padE0[0xD64 - 0xE0];   // +0x00E0
    Point2D_006D2420 TacticalPos;            // +0x0D64

    // FUNCTION: GAMEMD 0x6D2420 — TacticalClass::FocusOn.
    void FocusOn(const Coord_006D2420* pCoord, int speed);
};
GG_STATIC_ASSERT(offsetof(Tactical_006D2420, Offset_B0) == 0xB0);
GG_STATIC_ASSERT(offsetof(Tactical_006D2420, Offset_B0.Y) == 0xB4);
GG_STATIC_ASSERT(offsetof(Tactical_006D2420, FocusStart) == 0xC8);
GG_STATIC_ASSERT(offsetof(Tactical_006D2420, FocusStart.Y) == 0xCC);
GG_STATIC_ASSERT(offsetof(Tactical_006D2420, FocusTarget) == 0xD0);
GG_STATIC_ASSERT(offsetof(Tactical_006D2420, FocusTarget.Y) == 0xD4);
GG_STATIC_ASSERT(offsetof(Tactical_006D2420, FocusStep) == 0xD8);
GG_STATIC_ASSERT(offsetof(Tactical_006D2420, At_DC) == 0xDC);
GG_STATIC_ASSERT(offsetof(Tactical_006D2420, TacticalPos) == 0xD64);
GG_STATIC_ASSERT(offsetof(Tactical_006D2420, TacticalPos.Y) == 0xD68);

#endif  // GG_MATCH_UI_TACTICAL_CLASS_FOCUS_METHODS_H
