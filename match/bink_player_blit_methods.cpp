// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at the addresses annotated
//   below. Kept apart from the callers so that they emit a call to these bodies
//   instead of expanding them.
//
// Functions are ordered ascending by retail address.

#include "bink_player_teardown_methods.h"

// FUNCTION: GAMEMD 0x433270
// Paint the helper's back buffer onto the surface, centred horizontally and
// bottom-aligned inside the player's area.
void MSBinkPlayer::FUN_00433270(Surface* surface)
{
    BinkHelper_00433270* helper = Helper;
    if (helper && helper->Active) {
        RectangleStruct* src = &helper->SourceRect;
        if (src->Width > 0 && src->Height > 0) {
            Surface* buffer = helper->Buffer;
            RectangleStruct buf = buffer->GetRect();
            RectangleStruct dest = *src;
            dest.X = dest.X + (Area.Width - buf.Width) / 2;
            dest.Y = dest.Y + (Area.Height - buf.Height);
            dest.X += Area.X;
            dest.Y += Area.Y;
            surface->CopyFromPart(&dest, buffer, src, true, true);
        }
    }
}

// FUNCTION: GAMEMD 0x433330
// Clear the rectangle the helper last painted.
void MSBinkPlayer::FUN_00433330(Surface* surface)
{
    BinkHelper_00433270* helper = Helper;
    if (helper && helper->Active) {
        RectangleStruct clear = helper->ClearRect;
        if (clear.Width > 0 && clear.Height > 0) {
            RectangleStruct buf = helper->Buffer->GetRect();
            clear.X = clear.X + (Area.Width - buf.Width) / 2;
            clear.Y = clear.Y + (Area.Height - buf.Height);
            clear.X += Area.X;
            clear.Y += Area.Y;
            surface->FillRect(&clear, 0);
        }
    }
}
