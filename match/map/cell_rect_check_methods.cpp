// Provenance: own-binary-via-Ghidra
//   Read off retail gamemd.exe v1.001 at 0x5A7250: __fastcall with a
//   rectangle pointer in ECX ({X, Y, Width, Height} dwords at +0/+4/+8/+0xC),
//   a bool in DL and a second bool on the stack (`RET 4`). The four corners
//   are cut to 16-bit cell coordinates (MOVSX) and tested against the dwords
//   at 0xABED04 and 0xABED08; each cell comes from the map object 0x87F7E8
//   through 0x5657A0 and is classified by the cell predicates 0x4866D0,
//   0x4866F0, 0x486380, 0x486650 and 0x486670.

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Rect_005A7250
{
    int X;        // +0x00
    int Y;        // +0x04
    int Width;    // +0x08
    int Height;   // +0x0C
};
GG_STATIC_ASSERT(offsetof(Rect_005A7250, Height) == 0x0C);

struct CellStruct_005A7250
{
    short X;   // +0x00
    short Y;   // +0x02
};

struct Cell_005A7250
{
    // FUNCTION: GAMEMD 0x4866D0 (decl; reloc)
    bool FUN_004866D0();
    // FUNCTION: GAMEMD 0x4866F0 (decl; reloc)
    bool FUN_004866F0();
    // FUNCTION: GAMEMD 0x486380 (decl; reloc)
    bool FUN_00486380();
    // FUNCTION: GAMEMD 0x486650 (decl; reloc)
    bool FUN_00486650();
    // FUNCTION: GAMEMD 0x486670 (decl; reloc)
    bool FUN_00486670();
};

struct Map_005A7250
{
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc)
    Cell_005A7250* GetCell(const CellStruct_005A7250& cell);
};

// GLOBAL: GAMEMD 0x87F7E8
extern Map_005A7250 DAT_0087F7E8;
// GLOBAL: GAMEMD 0xABED04
extern int DAT_00ABED04;
// GLOBAL: GAMEMD 0xABED08
extern int DAT_00ABED08;

// The diamond test the four corners go through.
static inline bool CellInsideMap(const CellStruct_005A7250& cell)
{
    int x = cell.X;
    int y = cell.Y;
    if (x + y <= DAT_00ABED04 || x - y >= DAT_00ABED04 || y - x >= DAT_00ABED04 ||
        x + y > DAT_00ABED08) {
        return false;
    }
    return true;
}

static inline CellStruct_005A7250 InlineCell_005A7250(int x, int y)
{
    CellStruct_005A7250 cell;
    cell.X = (short)x;
    cell.Y = (short)y;
    return cell;
}

// FUNCTION: GAMEMD 0x5A7250
// True when all four corners lie on the map and every cell of the rectangle
// passes: cells of the first kind need `allow_first`, of the second kind
// `allow_second`, anything else one of the three remaining predicates.
bool __fastcall FUN_005A7250(const Rect_005A7250* rect, bool allow_first, bool allow_second)
{
    int left = rect->X;
    int top = rect->Y;
    if (!CellInsideMap(InlineCell_005A7250(left, top)) ||
        !CellInsideMap(InlineCell_005A7250(left + rect->Width - 1, top)) ||
        !CellInsideMap(InlineCell_005A7250(left, top + rect->Height - 1)) ||
        !CellInsideMap(InlineCell_005A7250(left + rect->Width - 1, top + rect->Height - 1))) {
        return false;
    }

    for (int y = top; y < rect->Y + rect->Height; y++) {
        for (int x = left; x < rect->X + rect->Width; x++) {
            Cell_005A7250* cell = DAT_0087F7E8.GetCell(InlineCell_005A7250(x, y));
            if (cell->FUN_004866D0()) {
                if (!allow_first) {
                    return false;
                }
            } else if (cell->FUN_004866F0()) {
                if (!allow_second) {
                    return false;
                }
            } else if (!cell->FUN_00486380() && !cell->FUN_00486650() && !cell->FUN_00486670()) {
                return false;
            }
        }
    }
    return true;
}
