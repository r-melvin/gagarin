// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x657CE0.
//   The receiver is the canonical MouseClass (ui_display_chain.h): +0x121C is the DSurface and +0x1220 the
//   BSurface of the RadarClass. The two [+0x78] calls are Surface::GetRect (RET 4); the trailing arguments
//   retail pushed first stay on the stack as the arguments of the following [+0x8] call, which is
//   CopyFromPart(dest, src, srcRect, false, true) (RET 0x14); [+0x7C]/[+0x80] are GetWidth/GetHeight.

#include "ui_display_chain.h"
#include "wwlib/surface/bsurface_class.h"
#include "dsurface_class.h"

// GLOBAL: GAMEMD 0xB73550 -- non-zero while the map draws tile by tile.
extern int DAT_00B73550;

// FUNCTION: GAMEMD 0x657CE0
//
// Redraw the map. In tile mode every tile of the tile surface is drawn in
// turn; otherwise the screen is copied onto the tile surface in one piece.
void MouseClass::FUN_00657CE0()
{
    if (DAT_00B73550 == 0) {
        // The by-value local (4.7%) and by-reference helper (9.9%) forms of w39 do not match.
        // ADDRCALL: GAMEMD 0x657D18 (the source rectangle's returned address is pushed on) and 0x657D2A (the destination's)
        unknown_121C->CopyFromPart(&unknown_121C->GetRect(), unknown_1220, &unknown_1220->GetRect(), false, true);
        FUN_00656150();
        return;
    }

    int across = unknown_121C->GetWidth();
    int down = unknown_121C->GetHeight();
    for (int y = 0; y < down; y++) {
        for (int x = 0; x < across; x++) {
            Point2D tile;
            tile.X = x;
            tile.Y = y;
            FUN_00655C50(tile);
        }
    }
}
