// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x6D6070: the coordinate is read as `[EBP]`,
//   `[EBP+4]`, `[EBP+8]` (X, Y, Z) off the single stacked argument (`RET 4`),
//   the 60x30 iso projection is inlined with the Y spill/reload through
//   `[ESP+0x14]`, the height lift comes from the __fastcall helper 0x6D20E0
//   (Z in ECX), the view offset is `[EDI+0xB0]` / `[EDI+0xB4]` (subtracted
//   and added back), the clamp helper 0x6D8640 takes the point by address
//   (`LEA EDX,[ESP+0x10]; PUSH EDX`) and answers in AL, the mode byte is
//   `[0xA8ED6B]`, and the results land in `[EDI+0xD64]`/`[EDI+0xD68]` and
//   `[EDI+0xD74]`/`[EDI+0xD78]` before the __thiscall 0x6D8B30 and the
//   `MOV byte ptr [EDI+0xD7D],1`. Method name and the mode byte's name are
//   YRpp's (names only).
#ifndef GG_MATCH_UI_TACTICAL_CLASS_POSITION_METHODS_H
#define GG_MATCH_UI_TACTICAL_CLASS_POSITION_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Point2D_006D6070
{
    int X;                    // +0x0000
    int Y;                    // +0x0004
};
GG_STATIC_ASSERT(sizeof(Point2D_006D6070) == 0x8);

struct Coord_006D6070
{
    int X;                    // +0x0000
    int Y;                    // +0x0004
    int Z;                    // +0x0008
};
GG_STATIC_ASSERT(offsetof(Coord_006D6070, Z) == 0x8);

// FUNCTION: GAMEMD 0x6D20E0 (decl; reloc) — Tactical::AdjustForZ,
// height in ECX, pixel lift in EAX.
int AdjustForZ_006D6070(int z);

// GLOBAL: GAMEMD 0xA8ED6B — Unsorted::ArmageddonMode (byte).
extern unsigned char DAT_00A8ED6B;

struct Tactical_006D6070
{
    char             _pad000[0xB0];       // +0x0000
    Point2D_006D6070 Offset_B0;           // +0x00B0  view offset (X, Y)
    char             _padB8[0xD64 - 0xB8]; // +0x00B8
    Point2D_006D6070 TacticalPos;         // +0x0D64
    char             _padD6C[0xD74 - 0xD6C]; // +0x0D6C
    Point2D_006D6070 At_D74;              // +0x0D74
    char             _padD7C;             // +0x0D7C
    unsigned char    At_D7D;              // +0x0D7D

    // FUNCTION: GAMEMD 0x6D8640 (decl; reloc) — clamp the screen point to the
    // map; true when it was moved.
    bool FUN_006D8640(Point2D_006D6070* pt);
    // FUNCTION: GAMEMD 0x6D8B30 (decl; reloc) — recompute the view after a
    // position change.
    void FUN_006D8B30();

    // FUNCTION: GAMEMD 0x6D6070 — Tactical::SetTacticalPosition.
    void SetTacticalPosition(const Coord_006D6070* pCoord);
};
GG_STATIC_ASSERT(offsetof(Tactical_006D6070, Offset_B0) == 0xB0);
GG_STATIC_ASSERT(offsetof(Tactical_006D6070, Offset_B0.Y) == 0xB4);
GG_STATIC_ASSERT(offsetof(Tactical_006D6070, TacticalPos) == 0xD64);
GG_STATIC_ASSERT(offsetof(Tactical_006D6070, TacticalPos.Y) == 0xD68);
GG_STATIC_ASSERT(offsetof(Tactical_006D6070, At_D74) == 0xD74);
GG_STATIC_ASSERT(offsetof(Tactical_006D6070, At_D74.Y) == 0xD78);
GG_STATIC_ASSERT(offsetof(Tactical_006D6070, At_D7D) == 0xD7D);

#endif  // GG_MATCH_UI_TACTICAL_CLASS_POSITION_METHODS_H
