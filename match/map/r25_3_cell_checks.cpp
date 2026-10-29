// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob2
// Provenance: own-binary-via-Ghidra
//   Evidence: retail gamemd.exe v1.001 disassembly at each address below.
//
// Address index: 0x6B2520

#include "../_layout/cell_class.h"

// GLOBAL: GAMEMD 0xABED04 / 0xABED08 -- the playable diamond limits.
extern int DAT_00ABED04;
extern int DAT_00ABED08;
// GLOBAL: GAMEMD 0xA8ED38 -- the tile type table's count.
extern int DAT_00A8ED38;

// A tile type as seen by this check: only the flag at +0x2E0 is read.
struct IsoTileView_006B2520
{
    char unknown_000[0x2E0];
    bool unknown_2E0;      // +0x2E0
};
GG_STATIC_ASSERT(offsetof(IsoTileView_006B2520, unknown_2E0) == 0x2E0);
// GLOBAL: GAMEMD 0xA8ED2C -- the tile type table's items.
extern IsoTileView_006B2520** DAT_00A8ED2C;

// One 0x50-byte record of the map grid: only the flag at +0x45 is read.
struct GridRec_006B2520
{
    char unknown_00[0x45];
    unsigned char unknown_45;   // +0x45
};
// FUNCTION: GAMEMD 0x58C2A0 (decl; reloc) -- the grid record of a cell (pointer to its coordinates in ECX).
GridRec_006B2520* __fastcall FUN_0058C2A0(const CellStruct* cell);

// Inline expanded here: is the cell inside the playable diamond.
inline bool InDiamond_006B2520(CellStruct c)
{
    int x = c.X;
    int y = c.Y;
    return y + x > DAT_00ABED04 && x - y < DAT_00ABED04 && y - x < DAT_00ABED04 && y + x <= DAT_00ABED08;
}

inline GridRec_006B2520* RecAt_006B2520(CellStruct c)
{
    return FUN_0058C2A0(&c);
}

// FUNCTION: GAMEMD 0x6B2520
// True when this cell is empty ground inside the playable diamond with a clear grid record and a
// tile type that allows it (or no tile type).
bool CellClass::FUN_006B2520()
{
    if (InDiamond_006B2520(MapCoords) && OverlayTypeIndex == -1 && FirstObject == 0) {
        if (RecAt_006B2520(MapCoords)->unknown_45 == 0) {
            int tile = IsoTileTypeIndex;
            if (tile < DAT_00A8ED38 && tile != 0xFFFF) {
                return DAT_00A8ED2C[tile]->unknown_2E0;
            }
            return true;
        }
    }
    return false;
}
