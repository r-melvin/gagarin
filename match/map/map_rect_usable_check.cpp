// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Derived from the retail gamemd.exe v1.001 disassembly at 0x578390.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "map_class_local_radar_methods.h"

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
