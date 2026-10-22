// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Derived from the retail gamemd.exe v1.001 disassembly at 0x578390.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct CellPos_00578390
{
    short X;   // +0x0000
    short Y;   // +0x0002

    CellPos_00578390(int x, int y) : X((short)x), Y((short)y) {}
};

struct Rect_00578390
{
    int X;        // +0x0000
    int Y;        // +0x0004
    int Width;    // +0x0008
    int Height;   // +0x000C
};
GG_STATIC_ASSERT(offsetof(Rect_00578390, Y) == 0x4);
GG_STATIC_ASSERT(offsetof(Rect_00578390, Width) == 0x8);
GG_STATIC_ASSERT(offsetof(Rect_00578390, Height) == 0xC);

class Map_00578390
{
public:
    // FUNCTION: GAMEMD 0x578460 (decl) - is the cell inside the usable area.
    bool IsWithinUsableArea(const CellPos_00578390& cell, bool checkLevel);

    int IsRectWithinUsableArea(const Rect_00578390& rect, bool checkLevel);
};

// FUNCTION: GAMEMD 0x578390
// True when all four corner cells of the rectangle are in the usable area.
int Map_00578390::IsRectWithinUsableArea(const Rect_00578390& rect, bool checkLevel)
{
    CellPos_00578390 topLeft(rect.X, rect.Y);
    if (IsWithinUsableArea(topLeft, checkLevel)) {
        CellPos_00578390 topRight(rect.X + rect.Width - 1, rect.Y);
        if (IsWithinUsableArea(topRight, checkLevel)) {
            CellPos_00578390 bottomLeft(rect.X, rect.Y + rect.Height - 1);
            if (IsWithinUsableArea(bottomLeft, checkLevel)) {
                CellPos_00578390 bottomRight(rect.X + rect.Width - 1, rect.Y + rect.Height - 1);
                if (IsWithinUsableArea(bottomRight, checkLevel)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
