// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 with the
//   local Ghidra CLI inside 0x483780:
//     CellClass: MapCoords [EDI+0x24] (0x483851), OverlayTypeIndex [EDI+0x44]
//       (0x48379B, 0x4837EB), FirstObject [EDI+0xE4] (0x4837E1), the byte
//       [EDI+0x11C] (0x4837BB) and OverlayData [EDI+0x11E] (0x4837AF).
//     ScenarioClass* at 0xA8B230: the byte at +0 tested with 0x80 (0x483796)
//       and the Randomizer sub-object at +0x218 (LEA at 0x483833).
//     TiberiumClass::Array.Items at 0xB0F4EC indexed by the tiberium index
//       (0x4837C5, 0x48381D); the double at [EAX+0xA0] compared against the
//       double constant at 0x7E3810 (0x4837CE).
//     The 4-byte per-direction step table at 0x89F688, X at +0 and Y at +2
//       (0x48385B, 0x48386F).
//     MapClass::Instance as the immediate 0x87F7E8 feeding GetCellAt 0x5657A0
//       (0x483886).
//   The CellClass offsets agree with the already-matched
//   match/map/cell_class_tiberium_methods.h and
//   match/map/cell_class_tiberium_germinate_methods.h (read, not edited;
//   re-derived here so this TU stands alone). Names cross-checked against YRpp.
#ifndef GG_MATCH_MAP_CELL_CLASS_SPREAD_TIBERIUM_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_SPREAD_TIBERIUM_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x5FDD20 (decl; reloc) -- overlay index -> tiberium index,
// or -1. __fastcall, the overlay index in ECX.
int OverlayTypeIndexToTiberium_00483780(int overlayIndex);

struct CellStruct_00483780
{
    short X;   // +0x00
    short Y;   // +0x02
    CellStruct_00483780() {}
};
GG_STATIC_ASSERT(sizeof(CellStruct_00483780) == 4);
GG_STATIC_ASSERT(offsetof(CellStruct_00483780, Y) == 0x02);

// GLOBAL: GAMEMD 0x89F688 -- the per-direction {dX,dY} step table.
extern CellStruct_00483780 AdjacentCell_00483780[];

inline CellStruct_00483780 operator+(CellStruct_00483780 a,
                                     const CellStruct_00483780& b)
{
    a.X = a.X + b.X;
    a.Y = b.Y + a.Y;
    return a;
}

// GLOBAL: GAMEMD 0x7E3810 -- the double the tiberium's +0xA0 is compared with.
extern const double DAT_007E3810;

struct Tiberium_00483780
{
    char   _pad000[0xA0];   // +0x0000
    double At_0A0;          // +0x00A0
};
GG_STATIC_ASSERT(offsetof(Tiberium_00483780, At_0A0) == 0xA0);

// GLOBAL: GAMEMD 0xB0F4EC -- TiberiumClass::Array.Items.
extern Tiberium_00483780** TiberiumArrayItems_00483780;



// GLOBAL: GAMEMD 0xA8B230 -- ScenarioClass::Instance.
#include "../core/scenario_class_methods.h"
extern ScenarioClass* DAT_00A8B230;

struct Cell_00483780;

struct Map_00483780
{
    char _opaque[4];
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) -- MapClass::GetCellAt.
    Cell_00483780* GetCellAt(const CellStruct_00483780* cell);
};
// GLOBAL: GAMEMD 0x87F7E8 -- the MapClass instance itself (an immediate).
extern Map_00483780 MapInstance_00483780;

struct Cell_00483780
{
    char                _pad000[0x24];        // +0x0000
    CellStruct_00483780 MapCoords;            // +0x0024
    char                _pad028[0x44 - 0x28]; // +0x0028
    int                 OverlayTypeIndex;     // +0x0044
    char                _pad048[0xE4 - 0x48]; // +0x0048
    void*               FirstObject;          // +0x00E4
    char                _pad0E8[0x11C - 0xE8];// +0x00E8
    char                At_11C;               // +0x011C
    char                _pad11D[1];           // +0x011D
    unsigned char       OverlayData;          // +0x011E

    // FUNCTION: GAMEMD 0x4838E0 (decl; reloc) -- CellClass::CanTiberiumGerminate.
    bool CanTiberiumGerminate(Tiberium_00483780* tiberium);
    // FUNCTION: GAMEMD 0x487190 (decl; reloc) -- lay the new tiberium down.
    bool FUN_00487190(int tiberiumIndex, int amount);

    // The bounds-checked neighbour lookup, expanded inline at its one call
    // site: out-of-range facings answer the cell itself.
    Cell_00483780* GetNeighbourCell(unsigned int facing)
    {
        Cell_00483780* result;
        if (facing >= 8) {
            result = this;
        } else {
            CellStruct_00483780 cell = this->MapCoords;
            cell = cell + AdjacentCell_00483780[facing & 7];
            result = MapInstance_00483780.GetCellAt(&cell);
        }
        return result;
    }

    // FUNCTION: GAMEMD 0x483780 -- CellClass::SpreadTiberium.
    bool SpreadTiberium(char forced);
};
GG_STATIC_ASSERT(offsetof(Cell_00483780, MapCoords)        == 0x24);
GG_STATIC_ASSERT(offsetof(Cell_00483780, OverlayTypeIndex) == 0x44);
GG_STATIC_ASSERT(offsetof(Cell_00483780, FirstObject)      == 0xE4);
GG_STATIC_ASSERT(offsetof(Cell_00483780, At_11C)           == 0x11C);
GG_STATIC_ASSERT(offsetof(Cell_00483780, OverlayData)      == 0x11E);

#endif  // GG_MATCH_MAP_CELL_CLASS_SPREAD_TIBERIUM_METHODS_H
