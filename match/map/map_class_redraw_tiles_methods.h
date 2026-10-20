// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x657CE0: the two surface pointers `[EDI+0x121C]` and
//   `[EDI+0x1220]`, the mode flag 0xB73550, the surface slots `[EDX+0x78]`
//   (a rectangle returned through a hidden pointer), `[EDX+0x7C]` and
//   `[EAX+0x80]` (the tile counts) and `[EBX+0x8]`, and the two helpers
//   0x655C50 (draw one tile, taking the tile position by address) and
//   0x656150 (the whole-surface path).
#ifndef GG_MATCH_MAP_MAP_CLASS_REDRAW_TILES_METHODS_H
#define GG_MATCH_MAP_MAP_CLASS_REDRAW_TILES_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// A tile position handed to the per-tile draw by address.
struct Tile_00657CE0
{
    int X;   // +0x0000
    int Y;   // +0x0004
};
GG_STATIC_ASSERT(sizeof(Tile_00657CE0) == 8);

// The rectangle the surface slots return through a hidden pointer; the
// user-declared constructor is what selects that convention.
struct Rect_00657CE0
{
    int X;      // +0x0000
    int Y;      // +0x0004
    int Width;  // +0x0008
    int Height; // +0x000C
};
GG_STATIC_ASSERT(sizeof(Rect_00657CE0) == 0x10);

struct SurfaceVtbl_00657CE0;

struct Surface_00657CE0
{
    SurfaceVtbl_00657CE0* Vptr;   // +0x0000
};
typedef void           (Surface_00657CE0::*Fn08_00657CE0)(Rect_00657CE0* rect);
// Slot 0x78 is reached with two different argument lists, one per surface
// kind; retail hands the rectangle back through an explicit out pointer and
// returns that pointer, so neither form is a C++ struct return.
typedef Rect_00657CE0* (Surface_00657CE0::*Fn78a_00657CE0)(Rect_00657CE0* out,
                                                           int a, int b);
typedef Rect_00657CE0* (Surface_00657CE0::*Fn78b_00657CE0)(Rect_00657CE0* out,
                                                           Surface_00657CE0* other,
                                                           Rect_00657CE0* rect);
typedef int           (Surface_00657CE0::*Fn7C_00657CE0)();
typedef int           (Surface_00657CE0::*Fn80_00657CE0)();

struct SurfaceVtbl_00657CE0
{
    char            _pad000[0x08];          // +0x0000
    Fn08_00657CE0   At_08;                  // +0x0008
    char            _pad00C[0x78 - 0x0C];   // +0x000C
    union
    {
        Fn78a_00657CE0 At_78a;              // +0x0078
        Fn78b_00657CE0 At_78b;
    };
    Fn7C_00657CE0   TilesAcross;            // +0x007C
    Fn80_00657CE0   TilesDown;              // +0x0080
};
GG_STATIC_ASSERT(offsetof(SurfaceVtbl_00657CE0, At_08)       == 0x08);
GG_STATIC_ASSERT(offsetof(SurfaceVtbl_00657CE0, At_78a)      == 0x78);
GG_STATIC_ASSERT(offsetof(SurfaceVtbl_00657CE0, TilesAcross) == 0x7C);
GG_STATIC_ASSERT(offsetof(SurfaceVtbl_00657CE0, TilesDown)   == 0x80);

// GLOBAL: GAMEMD 0xB73550 — non-zero while the map draws tile by tile.
extern int DAT_00B73550;

struct Map_00657CE0
{
    char               _pad0000[0x121C];   // +0x0000
    Surface_00657CE0*  Tiles;              // +0x121C
    Surface_00657CE0*  Screen;             // +0x1220

    // FUNCTION: GAMEMD 0x655C50 (decl; reloc) — draw one tile.
    void FUN_00655C50(const Tile_00657CE0& tile);
    // FUNCTION: GAMEMD 0x656150 (decl; reloc) — finish the whole-surface path.
    void FUN_00656150();

    // FUNCTION: GAMEMD 0x657CE0 — the map's redraw dispatch.
    void Redraw();
};
GG_STATIC_ASSERT(offsetof(Map_00657CE0, Tiles)  == 0x121C);
GG_STATIC_ASSERT(offsetof(Map_00657CE0, Screen) == 0x1220);

#endif  // GG_MATCH_MAP_MAP_CLASS_REDRAW_TILES_METHODS_H
