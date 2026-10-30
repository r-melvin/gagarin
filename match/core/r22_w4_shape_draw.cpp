// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Shape draw into a clipped rectangle, read off the user's retail gamemd.exe v1.001 with the local
//   Ghidra CLI. Sibling of the shape draws at 0x72E860..0x72EA70 (views named after the address).
//   Address index: 0x72E730.

struct Point_0072E730 {
    int x;
    int y;
};
struct Rect_0072E730 {
    int x;
    int y;
    int w;
    int h;
};
struct Surface_0072E730;
struct Convert_0072E730;
struct Shape_0072E730;

// GLOBAL: GAMEMD 0xB0FC1C -- draw position.
extern Point_0072E730* DAT_00B0FC1C;
// GLOBAL: GAMEMD 0x8A00A4 - screen width.
extern int DAT_008A00A4;

// FUNCTION: GAMEMD 0x4AED70 (decl; reloc) -- shape draw, __fastcall: surface in ECX, convert in EDX, fourteen stack words.
void __fastcall FUN_004AED70(Surface_0072E730* surface, Convert_0072E730* convert, Shape_0072E730* shape,
                             int frame, Point_0072E730* position, Rect_0072E730* clip, int flags,
                             int a6, int a7, int a8, int zAdjust, int a10, int a11, int a12,
                             Point_0072E730 offset);

// FUNCTION: GAMEMD 0x72E730
// Draws the shape for the current screen width (640 wide or other) clipped to a copy of `rect`,
// halving anything past 800x600 from that edge.
void __fastcall FUN_0072E730(Surface_0072E730* surface, const Rect_0072E730* rect, Convert_0072E730* convert,
                             Shape_0072E730* shape640, Shape_0072E730* shapeOther)
{
    Point_0072E730 position = {0, 0};
    Rect_0072E730 clip;
    clip.x = rect->x;
    clip.y = rect->y;
    clip.w = rect->w;
    clip.h = rect->h;
    if (clip.w > 800) {
        clip.w = (clip.w - 800) / 2 + 800;
    }
    if (clip.h > 600) {
        clip.h = (clip.h - 600) / 2 + 600;
    }
    position = *DAT_00B0FC1C;
    if (DAT_008A00A4 == 640) {
        Point_0072E730 offset = {0, 0};
        FUN_004AED70(surface, convert, shape640, 0, &position, &clip, 0x400, 0, 0, 0, 1000, 0, 0, 0, offset);
        return;
    }
    Point_0072E730 offset = {0, 0};
    FUN_004AED70(surface, convert, shapeOther, 0, &position, &clip, 0x400, 0, 0, 0, 1000, 0, 0, 0, offset);
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x8A00A4
int DAT_008A00A4;
// GLOBAL: GAMEMD 0xB0FC1C
Point_0072E730* DAT_00B0FC1C;
// END defined globals
