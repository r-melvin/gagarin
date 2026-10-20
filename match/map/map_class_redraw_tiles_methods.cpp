// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x657CE0.

#include "map_class_redraw_tiles_methods.h"

// FUNCTION: GAMEMD 0x657CE0
//
// Redraw the map. In tile mode every tile of the tile surface is drawn in
// turn; otherwise the screen's rectangle is mapped onto the tile surface
// and handed back in one piece.
//
// PARTIAL (64.8%, up from 14.1%; multiset now identical, 71 vs 71).
// The lever: capture the tile surface's slot-8 entry into a
// pointer-to-member-function local BEFORE the screen call that sits between
// the two uses, and take the receiver for that call from `this->Tiles` again
// rather than from the cached pointer. Retail reads the tile vtable once,
// early, and re-reads `this->Tiles` for the receiver; every spelling that
// caches only the *object* and lets cl read the vtable after the intervening
// call comes out one MOV short of retail (11.3-12.7%, 70 vs 71 instructions)
// -- measured as: vtable cached in a local (all four receiver spellings), a
// volatile lvalue read of the vptr, `tiles[0].Vptr`, a reference alias, a
// `__forceinline VptrOf()` helper, two separate `this->Tiles` locals, and the
// whole chain written as one nested expression.
//
// The residual is scheduling and colouring only: retail keeps `this` in EDI
// and the tile surface in ESI where cl 8804 takes ESI and EDI respectively,
// sinks the `PUSH 1`/`PUSH 0` pair above the two vtable loads rather than
// interleaving them, and reverses the `LEA`/`PUSH` order of the second call.
// The caveat worth recording: retail's cached value is the *vtable* and its
// call is `CALL [EBX+8]`, while this form caches the *slot* and calls
// `CALL EBX` -- the same mnemonic and the same count, so the multiset agrees
// and the score is real, but the spelling is one indirection away from
// retail's own. Declaration order of the two rectangles, a `Screen` local and
// the chained form are all byte-identical to this at 64.8%.
void Map_00657CE0::Redraw()
{
    if (DAT_00B73550 == 0) {
        Surface_00657CE0* tiles = this->Tiles;
        Fn08_00657CE0 f = tiles->Vptr->At_08;
        Rect_00657CE0 whole;
        Rect_00657CE0 mapped;
        Rect_00657CE0* r = (Screen->*Screen->Vptr->At_78a)(&whole, 0, 1);
        Rect_00657CE0* m = (tiles->*tiles->Vptr->At_78b)(&mapped, Screen, r);
        (this->Tiles->*f)(m);
        FUN_00656150();
        return;
    }

    int across = (Tiles->*Tiles->Vptr->TilesAcross)();
    int down = (Tiles->*Tiles->Vptr->TilesDown)();
    for (int y = 0; y < down; y++) {
        for (int x = 0; x < across; x++) {
            Tile_00657CE0 tile;
            tile.X = x;
            tile.Y = y;
            FUN_00655C50(tile);
        }
    }
}
