// Provenance: own-binary-via-Ghidra
//   Bytes read off the user's retail gamemd.exe v1.001 via the local Ghidra
//   CLI at 0x7BB920: a non-virtual __thiscall (`RET 0x20`: three ints, a
//   by-value RectangleStruct and a colour) that only calls DrawLineEx
//   (slot +0x2C).
#include "surface_class.h"

// FUNCTION: GAMEMD 0x7BB920
//
// Bresenham/midpoint filled circle: for each octant step draw the four
// horizontal spans mirrored about the centre, clipped to `clip`.
void XSurface::FUN_007BB920(int cx, int cy, int radius, RectangleStruct clip,
                           unsigned int color)
{
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    do {
        Point2D a, b, c, e, f, g, h, k;

        b.X = cx + y;
        b.Y = cy + x;
        a.X = cx - y;
        a.Y = cy + x;
        DrawLineEx(&clip, &a, &b, color);

        e.X = cx + x;
        e.Y = cy + y;
        c.X = cx - x;
        c.Y = cy + y;
        DrawLineEx(&clip, &c, &e, color);

        g.X = cx + y;
        g.Y = cy - x;
        f.X = cx - y;
        f.Y = cy - x;
        DrawLineEx(&clip, &f, &g, color);

        k.X = cx + x;
        k.Y = cy - y;
        h.X = cx - x;
        h.Y = cy - y;
        DrawLineEx(&clip, &h, &k, color);

        if (d < 0) {
            d += 4 * x + 6;
        } else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    } while (y >= x);
}
