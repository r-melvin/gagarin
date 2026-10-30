// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at each address below.
//
//   Ordered ascending by retail address.

#include "trivial_tu127_methods.h"
#include "../_layout/cell_class.h"
#include "../_layout/cell.h"
#include "../_layout/cell_offset.h"
// SYNTHETIC: GAMEMD 0x561900 -- dynamic initialiser for DAT_00ABD490: tail-jumps to the aggregate fill at 0x561910
// SYNTHETIC: GAMEMD 0x561910 -- aggregate fill of the offset table
// GLOBAL: GAMEMD 0xABD490
// Cell offsets sorted by growing radius, 369 entries.
CellOffset DAT_00ABD490[369] = {
    CellOffset(0, 0), CellOffset(1, -1), CellOffset(0, -1), CellOffset(-1, -1), CellOffset(-1, 0),
    CellOffset(1, 0), CellOffset(-1, 1), CellOffset(0, 1), CellOffset(1, 1), CellOffset(-1, -2),
    CellOffset(0, -2), CellOffset(1, -2), CellOffset(-2, -1), CellOffset(2, -1), CellOffset(-2, 0),
    CellOffset(2, 0), CellOffset(-2, 1), CellOffset(2, 1), CellOffset(-1, 2), CellOffset(0, 2),
    CellOffset(1, 2), CellOffset(-1, -3), CellOffset(0, -3), CellOffset(1, -3), CellOffset(-2, -2),
    CellOffset(2, -2), CellOffset(-3, -1), CellOffset(3, -1), CellOffset(-3, 0), CellOffset(3, 0),
    CellOffset(-3, 1), CellOffset(3, 1), CellOffset(-2, 2), CellOffset(2, 2), CellOffset(-1, 3),
    CellOffset(0, 3), CellOffset(1, 3), CellOffset(-1, -4), CellOffset(0, -4), CellOffset(1, -4),
    CellOffset(-3, -3), CellOffset(-2, -3), CellOffset(2, -3), CellOffset(3, -3), CellOffset(-3, -2),
    CellOffset(3, -2), CellOffset(-4, -1), CellOffset(4, -1), CellOffset(-4, 0), CellOffset(4, 0),
    CellOffset(-4, 1), CellOffset(4, 1), CellOffset(-3, 2), CellOffset(3, 2), CellOffset(-3, 3),
    CellOffset(-2, 3), CellOffset(2, 3), CellOffset(3, 3), CellOffset(-1, 4), CellOffset(0, 4),
    CellOffset(1, 4), CellOffset(-1, -5), CellOffset(0, -5), CellOffset(1, -5), CellOffset(-3, -4),
    CellOffset(-2, -4), CellOffset(2, -4), CellOffset(3, -4), CellOffset(-4, -3), CellOffset(4, -3),
    CellOffset(-4, -2), CellOffset(4, -2), CellOffset(-5, -1), CellOffset(5, -1), CellOffset(-5, 0),
    CellOffset(5, 0), CellOffset(-5, 1), CellOffset(5, 1), CellOffset(-4, 2), CellOffset(4, 2),
    CellOffset(-4, 3), CellOffset(4, 3), CellOffset(-3, 4), CellOffset(-2, 4), CellOffset(2, 4),
    CellOffset(3, 4), CellOffset(-1, 5), CellOffset(0, 5), CellOffset(1, 5), CellOffset(-1, -6),
    CellOffset(0, -6), CellOffset(1, -6), CellOffset(-3, -5), CellOffset(-2, -5), CellOffset(2, -5),
    CellOffset(3, -5), CellOffset(-4, -4), CellOffset(4, -4), CellOffset(-5, -3), CellOffset(5, -3),
    CellOffset(-5, -2), CellOffset(5, -2), CellOffset(-6, -1), CellOffset(6, -1), CellOffset(-6, 0),
    CellOffset(6, 0), CellOffset(-6, 1), CellOffset(6, 1), CellOffset(-5, 2), CellOffset(5, 2),
    CellOffset(-5, 3), CellOffset(5, 3), CellOffset(-4, 4), CellOffset(4, 4), CellOffset(-3, 5),
    CellOffset(-2, 5), CellOffset(2, 5), CellOffset(3, 5), CellOffset(-1, 6), CellOffset(0, 6),
    CellOffset(1, 6), CellOffset(-1, -7), CellOffset(0, -7), CellOffset(1, -7), CellOffset(-3, -6),
    CellOffset(-2, -6), CellOffset(2, -6), CellOffset(3, -6), CellOffset(-5, -5), CellOffset(-4, -5),
    CellOffset(4, -5), CellOffset(5, -5), CellOffset(-5, -4), CellOffset(5, -4), CellOffset(-6, -3),
    CellOffset(6, -3), CellOffset(-6, -2), CellOffset(6, -2), CellOffset(-7, -1), CellOffset(7, -1),
    CellOffset(-7, 0), CellOffset(7, 0), CellOffset(-7, 1), CellOffset(7, 1), CellOffset(-6, 2),
    CellOffset(6, 2), CellOffset(-6, 3), CellOffset(6, 3), CellOffset(-5, 4), CellOffset(5, 4),
    CellOffset(-5, 5), CellOffset(-4, 5), CellOffset(4, 5), CellOffset(5, 5), CellOffset(-3, 6),
    CellOffset(-2, 6), CellOffset(2, 6), CellOffset(3, 6), CellOffset(-1, 7), CellOffset(0, 7),
    CellOffset(1, 7), CellOffset(-1, -8), CellOffset(0, -8), CellOffset(1, -8), CellOffset(-3, -7),
    CellOffset(-2, -7), CellOffset(2, -7), CellOffset(3, -7), CellOffset(-5, -6), CellOffset(-4, -6),
    CellOffset(4, -6), CellOffset(5, -6), CellOffset(-6, -5), CellOffset(6, -5), CellOffset(-6, -4),
    CellOffset(6, -4), CellOffset(-7, -3), CellOffset(7, -3), CellOffset(-7, -2), CellOffset(7, -2),
    CellOffset(-8, -1), CellOffset(8, -1), CellOffset(-8, 0), CellOffset(8, 0), CellOffset(-8, 1),
    CellOffset(8, 1), CellOffset(-7, 2), CellOffset(7, 2), CellOffset(-7, 3), CellOffset(7, 3),
    CellOffset(-6, 4), CellOffset(6, 4), CellOffset(-6, 5), CellOffset(6, 5), CellOffset(-5, 6),
    CellOffset(-4, 6), CellOffset(4, 6), CellOffset(5, 6), CellOffset(-3, 7), CellOffset(-2, 7),
    CellOffset(2, 7), CellOffset(3, 7), CellOffset(-1, 8), CellOffset(0, 8), CellOffset(1, 8),
    CellOffset(-1, -9), CellOffset(0, -9), CellOffset(1, -9), CellOffset(-3, -8), CellOffset(-2, -8),
    CellOffset(2, -8), CellOffset(3, -8), CellOffset(-5, -7), CellOffset(-4, -7), CellOffset(4, -7),
    CellOffset(5, -7), CellOffset(-6, -6), CellOffset(6, -6), CellOffset(-7, -5), CellOffset(7, -5),
    CellOffset(-7, -4), CellOffset(7, -4), CellOffset(-8, -3), CellOffset(8, -3), CellOffset(-8, -2),
    CellOffset(8, -2), CellOffset(-9, -1), CellOffset(9, -1), CellOffset(-9, 0), CellOffset(9, 0),
    CellOffset(-9, 1), CellOffset(9, 1), CellOffset(-8, 2), CellOffset(8, 2), CellOffset(-8, 3),
    CellOffset(8, 3), CellOffset(-7, 4), CellOffset(7, 4), CellOffset(-7, 5), CellOffset(7, 5),
    CellOffset(-6, 6), CellOffset(6, 6), CellOffset(-5, 7), CellOffset(-4, 7), CellOffset(4, 7),
    CellOffset(5, 7), CellOffset(-3, 8), CellOffset(-2, 8), CellOffset(2, 8), CellOffset(3, 8),
    CellOffset(-1, 9), CellOffset(0, 9), CellOffset(1, 9), CellOffset(-1, -10), CellOffset(0, -10),
    CellOffset(1, -10), CellOffset(-3, -9), CellOffset(-2, -9), CellOffset(2, -9), CellOffset(3, -9),
    CellOffset(-5, -8), CellOffset(-4, -8), CellOffset(4, -8), CellOffset(5, -8), CellOffset(-7, -7),
    CellOffset(-6, -7), CellOffset(6, -7), CellOffset(7, -7), CellOffset(-7, -6), CellOffset(7, -6),
    CellOffset(-8, -5), CellOffset(8, -5), CellOffset(-8, -4), CellOffset(8, -4), CellOffset(-9, -3),
    CellOffset(9, -3), CellOffset(-9, -2), CellOffset(9, -2), CellOffset(-10, -1), CellOffset(10, -1),
    CellOffset(-10, 0), CellOffset(10, 0), CellOffset(-10, 1), CellOffset(10, 1), CellOffset(-9, 2),
    CellOffset(9, 2), CellOffset(-9, 3), CellOffset(9, 3), CellOffset(-8, 4), CellOffset(8, 4),
    CellOffset(-8, 5), CellOffset(8, 5), CellOffset(-7, 6), CellOffset(7, 6), CellOffset(-7, 7),
    CellOffset(-6, 7), CellOffset(6, 7), CellOffset(7, 7), CellOffset(-5, 8), CellOffset(-4, 8),
    CellOffset(4, 8), CellOffset(5, 8), CellOffset(-3, 9), CellOffset(-2, 9), CellOffset(2, 9),
    CellOffset(3, 9), CellOffset(-1, 10), CellOffset(0, 10), CellOffset(1, 10), CellOffset(0, 11),
    CellOffset(0, -11), CellOffset(-1, 11), CellOffset(1, 11), CellOffset(-1, -11), CellOffset(1, -11),
    CellOffset(-2, 11), CellOffset(2, 11), CellOffset(-2, -11), CellOffset(2, -11), CellOffset(-3, 11),
    CellOffset(3, 11), CellOffset(-3, -11), CellOffset(-3, 11), CellOffset(-4, 9), CellOffset(4, 9),
    CellOffset(-4, -9), CellOffset(4, -9), CellOffset(-5, 9), CellOffset(5, 9), CellOffset(-5, -9),
    CellOffset(5, -9), CellOffset(-6, 8), CellOffset(6, 8), CellOffset(-6, -8), CellOffset(6, -8),
    CellOffset(-7, 8), CellOffset(7, 8), CellOffset(-7, -8), CellOffset(7, -8), CellOffset(-8, 7),
    CellOffset(8, 7), CellOffset(-8, -7), CellOffset(8, -7), CellOffset(-8, 6), CellOffset(8, 6),
    CellOffset(-8, -6), CellOffset(8, -6), CellOffset(-9, 5), CellOffset(9, 5), CellOffset(-9, -5),
    CellOffset(9, -5), CellOffset(-9, 4), CellOffset(9, 4), CellOffset(-9, -4), CellOffset(9, -4),
    CellOffset(-10, 3), CellOffset(10, 3), CellOffset(-10, -3), CellOffset(10, -3), CellOffset(-10, 2),
    CellOffset(10, 2), CellOffset(-10, -2), CellOffset(10, -2), CellOffset(-11, 1), CellOffset(11, 1),
    CellOffset(-11, -1), CellOffset(11, -1), CellOffset(11, 0), CellOffset(-11, 0)
};

// SYNTHETIC: GAMEMD 0x5638C0 -- initialiser entry: tail-jumps to the aggregate fill at 0x5638D0
// SYNTHETIC: GAMEMD 0x5638D0 -- aggregate fill of the offset table
// GLOBAL: GAMEMD 0xABCF60
// Cell offsets, 309 entries.
CellOffset DAT_00ABCF60[309] = {
    CellOffset(0, 0), CellOffset(-1, 1), CellOffset(0, 1), CellOffset(1, 1), CellOffset(1, 0),
    CellOffset(-1, 0), CellOffset(1, -1), CellOffset(0, -1), CellOffset(-1, -1), CellOffset(1, 1),
    CellOffset(0, 1), CellOffset(-1, 1), CellOffset(1, 1), CellOffset(-1, 1), CellOffset(1, 0),
    CellOffset(-1, 0), CellOffset(1, -1), CellOffset(-1, -1), CellOffset(1, -1), CellOffset(0, -1),
    CellOffset(-1, -1), CellOffset(0, 1), CellOffset(0, 1), CellOffset(0, 1), CellOffset(1, 1),
    CellOffset(-1, 1), CellOffset(1, 0), CellOffset(-1, 0), CellOffset(1, 0), CellOffset(-1, 0),
    CellOffset(1, 0), CellOffset(-1, 0), CellOffset(1, -1), CellOffset(-1, -1), CellOffset(0, -1),
    CellOffset(0, -1), CellOffset(0, -1), CellOffset(0, 1), CellOffset(0, 1), CellOffset(0, 1),
    CellOffset(1, 1), CellOffset(1, 1), CellOffset(-1, 1), CellOffset(-1, 1), CellOffset(1, 1),
    CellOffset(-1, 1), CellOffset(1, 0), CellOffset(-1, 0), CellOffset(1, 0), CellOffset(-1, 0),
    CellOffset(1, 0), CellOffset(-1, 0), CellOffset(1, -1), CellOffset(-1, -1), CellOffset(1, -1),
    CellOffset(1, -1), CellOffset(-1, -1), CellOffset(-1, -1), CellOffset(0, -1), CellOffset(0, -1),
    CellOffset(0, -1), CellOffset(0, 1), CellOffset(0, 1), CellOffset(0, 1), CellOffset(1, 1),
    CellOffset(1, 1), CellOffset(-1, 1), CellOffset(-1, 1), CellOffset(1, 1), CellOffset(-1, 1),
    CellOffset(1, 1), CellOffset(-1, 1), CellOffset(1, 0), CellOffset(-1, 0), CellOffset(1, 0),
    CellOffset(-1, 0), CellOffset(1, 0), CellOffset(-1, 0), CellOffset(1, -1), CellOffset(-1, -1),
    CellOffset(1, -1), CellOffset(-1, -1), CellOffset(1, -1), CellOffset(1, -1), CellOffset(-1, -1),
    CellOffset(-1, -1), CellOffset(0, -1), CellOffset(0, -1), CellOffset(0, -1), CellOffset(0, 1),
    CellOffset(0, 1), CellOffset(0, 1), CellOffset(1, 1), CellOffset(0, 1), CellOffset(0, 1),
    CellOffset(-1, 1), CellOffset(1, 1), CellOffset(-1, 1), CellOffset(1, 1), CellOffset(-1, 1),
    CellOffset(1, 0), CellOffset(1, 0), CellOffset(1, 0), CellOffset(-1, 0), CellOffset(1, 0),
    CellOffset(-1, 0), CellOffset(1, 0), CellOffset(-1, 0), CellOffset(1, 0), CellOffset(-1, 0),
    CellOffset(1, -1), CellOffset(-1, -1), CellOffset(1, -1), CellOffset(-1, -1), CellOffset(1, -1),
    CellOffset(0, -1), CellOffset(0, -1), CellOffset(-1, -1), CellOffset(0, -1), CellOffset(0, -1),
    CellOffset(0, -1), CellOffset(0, 1), CellOffset(0, 1), CellOffset(0, 1), CellOffset(1, 1),
    CellOffset(0, 1), CellOffset(0, 1), CellOffset(-1, 1), CellOffset(1, 1), CellOffset(1, 1),
    CellOffset(-1, 1), CellOffset(-1, 1), CellOffset(1, 1), CellOffset(-1, 1), CellOffset(1, 1),
    CellOffset(-1, 1), CellOffset(1, 0), CellOffset(-1, 0), CellOffset(1, 0), CellOffset(-1, 0),
    CellOffset(1, 0), CellOffset(-1, 0), CellOffset(1, 0), CellOffset(-1, 0), CellOffset(1, 0),
    CellOffset(-1, 0), CellOffset(1, -1), CellOffset(-1, -1), CellOffset(1, -1), CellOffset(-1, -1),
    CellOffset(1, -1), CellOffset(1, -1), CellOffset(-1, -1), CellOffset(-1, -1), CellOffset(1, -1),
    CellOffset(0, -1), CellOffset(0, -1), CellOffset(-1, -1), CellOffset(0, -1), CellOffset(0, -1),
    CellOffset(0, -1), CellOffset(0, 1), CellOffset(0, 1), CellOffset(0, 1), CellOffset(0, 1),
    CellOffset(0, 1), CellOffset(0, 1), CellOffset(0, 1), CellOffset(1, 1), CellOffset(1, 1),
    CellOffset(-1, 1), CellOffset(-1, 1), CellOffset(1, 1), CellOffset(-1, 1), CellOffset(1, 1),
    CellOffset(-1, 1), CellOffset(1, 0), CellOffset(-1, 0), CellOffset(1, 0), CellOffset(-1, 0),
    CellOffset(1, 0), CellOffset(-1, 0), CellOffset(1, 0), CellOffset(-1, 0), CellOffset(1, 0),
    CellOffset(-1, 0), CellOffset(1, 0), CellOffset(-1, 0), CellOffset(1, 0), CellOffset(-1, 0),
    CellOffset(1, -1), CellOffset(-1, -1), CellOffset(1, -1), CellOffset(-1, -1), CellOffset(1, -1),
    CellOffset(1, -1), CellOffset(-1, -1), CellOffset(-1, -1), CellOffset(0, -1), CellOffset(0, -1),
    CellOffset(0, -1), CellOffset(0, -1), CellOffset(0, -1), CellOffset(0, -1), CellOffset(0, -1),
    CellOffset(0, 1), CellOffset(0, 1), CellOffset(0, 1), CellOffset(0, 1), CellOffset(0, 1),
    CellOffset(0, 1), CellOffset(0, 1), CellOffset(1, 1), CellOffset(1, 1), CellOffset(-1, 1),
    CellOffset(-1, 1), CellOffset(1, 1), CellOffset(-1, 1), CellOffset(1, 1), CellOffset(-1, 1),
    CellOffset(1, 1), CellOffset(-1, 1), CellOffset(1, 0), CellOffset(-1, 0), CellOffset(1, 0),
    CellOffset(-1, 0), CellOffset(1, 0), CellOffset(-1, 0), CellOffset(1, 0), CellOffset(-1, 0),
    CellOffset(1, 0), CellOffset(-1, 0), CellOffset(1, 0), CellOffset(-1, 0), CellOffset(1, 0),
    CellOffset(-1, 0), CellOffset(1, -1), CellOffset(-1, -1), CellOffset(1, -1), CellOffset(-1, -1),
    CellOffset(1, -1), CellOffset(-1, -1), CellOffset(1, -1), CellOffset(1, -1), CellOffset(-1, -1),
    CellOffset(-1, -1), CellOffset(0, -1), CellOffset(0, -1), CellOffset(0, -1), CellOffset(0, -1),
    CellOffset(0, -1), CellOffset(0, -1), CellOffset(0, -1), CellOffset(0, 1), CellOffset(0, 1),
    CellOffset(0, 1), CellOffset(0, 1), CellOffset(0, 1), CellOffset(0, 1), CellOffset(0, 1),
    CellOffset(1, 1), CellOffset(1, 1), CellOffset(-1, 1), CellOffset(-1, 1), CellOffset(1, 1),
    CellOffset(1, 1), CellOffset(-1, 1), CellOffset(-1, 1), CellOffset(1, 1), CellOffset(-1, 1),
    CellOffset(1, 1), CellOffset(-1, 1), CellOffset(1, 1), CellOffset(-1, 1), CellOffset(1, 0),
    CellOffset(-1, 0), CellOffset(1, 0), CellOffset(-1, 0), CellOffset(1, 0), CellOffset(-1, 0),
    CellOffset(1, 0), CellOffset(-1, 0), CellOffset(1, 0), CellOffset(-1, 0), CellOffset(1, 0),
    CellOffset(-1, 0), CellOffset(1, 0), CellOffset(-1, 0), CellOffset(1, -1), CellOffset(-1, -1),
    CellOffset(1, -1), CellOffset(-1, -1), CellOffset(1, -1), CellOffset(-1, -1), CellOffset(1, -1),
    CellOffset(1, -1), CellOffset(-1, -1), CellOffset(-1, -1), CellOffset(1, -1), CellOffset(1, -1),
    CellOffset(-1, -1), CellOffset(-1, -1), CellOffset(0, -1), CellOffset(0, -1), CellOffset(0, -1),
    CellOffset(0, -1), CellOffset(0, -1), CellOffset(0, -1), CellOffset(0, -1)
};

// SYNTHETIC: GAMEMD 0x565060 -- CellClass constructor + atexit registration
// SYNTHETIC: GAMEMD 0x565080 -- exit-time stub: tail-jumps to ~CellClass
// GLOBAL: GAMEMD 0xABDC50
// The map's "invalid cell" sentinel.
CellClass InvalidCell;

// Includes for the method bodies below come after the table initialisers so that the
// translation unit's _$E initialiser numbering is unchanged.
#include "../_layout/session_class.h"
#include "../ui/input_controls/ui_display_chain.h"
#include <stdlib.h>
#include "../core/lcw_pipe.h"
#include "../_layout/house_class.h"
#include "../_layout/house_type_class.h"
#include "../combat/veinhole_monster_deleteall_methods.h"
#include "../_layout/tiberium_class.h"
#include "map_class_location_shrouded_methods.h"
#include "crate_class.h"
#include "../core/unsorted_callback_methods.h"
#include "../renderer/zbuffer_class_methods.h"
#include "../renderer/drawing.h"

// GLOBAL: GAMEMD 0xABD480 -- the "no cell" coordinate.
extern CellStruct DAT_00ABD480;
// GLOBAL: GAMEMD 0xABDC10 -- the "no coordinate" sentinel.
extern CoordStruct DAT_00ABDC10;
// GLOBAL: GAMEMD 0xA8022C -- HouseClass::Array items.
extern HouseClass** HouseArrayItems;
// GLOBAL: GAMEMD 0xA80238 -- HouseClass::Array count.
extern int HouseArrayCount;
// GLOBAL: GAMEMD 0xA8B261
extern bool DAT_00A8B261;

// FUNCTION: GAMEMD 0x5659F0
// Clears the depth and alpha buffers and every crate slot.
void MapClass::vf_07()
{
    FUN_004068E0("MapClass::Init_Clear entry\n");
    Unsorted_CallBack();
    ZBuffer_00887644->Fill(0xFFFF);
    ABuffer_0087E8A4->Fill(0x7F);
    Unsorted_CallBack();
    FUN_004F42D0();
    Unsorted_CallBack();
    for (int i = 0; i < 0x100; ++i) {
        CrateClass* crate = &Crates[i];
        crate->Location = DAT_00ABD480;
        if (crate->Timer.StartTime != -1) {
            crate->Timer.TimeLeft = crate->Timer.GetTimeLeft();
            crate->Timer.StartTime = -1;
        }
    }
    unknown_148 = 13;
    unknown_1158[0] = 0;
    FUN_004068E0("MapClass::Init_Clear done\n");
}

// FUNCTION: GAMEMD 0x56AE40
int MapClass::FUN_0056AE40(Pipe* chain) const
{
    int total = 0;
    int i;
    LCWPipe pipe(LCWPipe::COMPRESS, 0x2000);
    pipe.SetChainTo(chain);
    for (i = 0; i < Owned.Capacity; i++) {
        CellClass* cell = Owned.Items[i];
        total += pipe.FUN_00631D10((int)(cell ? &cell->IsoTileTypeIndex : &InvalidCell.IsoTileTypeIndex), 2);
    }
    for (i = 0; i < Owned.Capacity; i++) {
        CellClass* cell = Owned.Items[i];
        total += pipe.FUN_00631D10((int)(cell ? &cell->Height : &InvalidCell.Height), 1);
    }
    for (i = 0; i < Owned.Capacity; i++) {
        CellClass* cell = Owned.Items[i];
        total += pipe.FUN_00631D10((int)(cell ? &cell->Level : &InvalidCell.Level), 1);
    }
    return total;
}

// FUNCTION: GAMEMD 0x56BBE0
// Walks every crate slot and retires the ones whose timer has run out.
void MapClass::vf_27()
{
    if (Session_00A8B238.GameMode != 0 && DAT_00A8B261) {
        for (int i = 0; i < 0x100; ++i) {
            CrateClass* crate = &Crates[i];
            if (crate->Location.X != DAT_00ABD480.X || crate->Location.Y != DAT_00ABD480.Y) {
                if (crate->Timer.GetTimeLeft() == 0) {
                    crate->FUN_004A1750();
                    FUN_0056BD40();
                }
            }
        }
    }
}

// FUNCTION: GAMEMD 0x56C200
// Returns a constant.
int __cdecl FUN_0056C200()
{
    return 1;
}

// FUNCTION: GAMEMD 0x56C500
// Empty function.
void __cdecl FUN_0056C500()
{
}

// Component-wise equality, expanded inline at 0x56E8A5-0x56E945.
static inline bool CoordsEqual(const CoordStruct& a, const CoordStruct& b)
{
    return a.X == b.X && a.Y == b.Y && a.Z == b.Z;
}

// FUNCTION: GAMEMD 0x56E890
bool MapClass::FUN_0056E890(const CellStruct* cell, int* houseTypeValue, int* sector) const
{
    if (cell->X == DAT_00ABD480.X && cell->Y == DAT_00ABD480.Y) {
        return false;
    }
    int w = MapRect.Width;
    int x = cell->X;
    int y = cell->Y;
    if (x + y <= w || x - y >= w || y - x >= w || x + y > w + MapRect.Height * 2) {
        return false;
    }
    for (int i = 0; i < HouseArrayCount; i++) {
        HouseClass* house = HouseArrayItems[i];
        if (house && !house->Defeated) {
            if (!CoordsEqual(house->FUN_0050DF30(), DAT_00ABDC10)) {
                *sector = house->SectorOfCell((CellStruct*)cell);
                if (*sector != -1) {
                    *houseTypeValue = house->Type->ArrayIndex2;
                    return true;
                }
            }
        }
    }
    return false;
}

// Unclaimed (below partial bar): GAMEMD 0x578290 MapClass::FUN_00578290, the next cell of the iteration over
// the owned-cell table (best 68.6%).

// FUNCTION: GAMEMD 0x581090
void MapClass::FUN_00581090()
{
    int i;
    for (i = 0; i < 13; i++) {
        if (Buffers[i]) {
            delete Buffers[i];
            Buffers[i] = 0;
        }
    }
    MapBucketTable<MapBucketA>* bucketsA = BucketsA;
    if (bucketsA) {
        if (bucketsA->Items)
            delete[] bucketsA->Items;
        delete bucketsA;
        BucketsA = 0;
    }
    for (i = 0; i < 3; i++) {
        Rings[i].Clear();
        MapBucketTable<MapBucketB>* buckets = BucketsB[i];
        if (buckets) {
            if (buckets->Items)
                delete[] buckets->Items;
            delete buckets;
            BucketsB[i] = 0;
        }
    }
    VeinholeMonsterClass::DeleteAll();
    VeinholeMonsterClass::DeleteVeinholeGrowthData();
    TiberiumClass::FreeSpreadLogicAll();
    TiberiumClass::FreeGrowthLogicAll();
}

// FUNCTION: GAMEMD 0x5864A0
// The same level-shifted cell lookup as IsLocationShrouded (0x586360), testing the +0x13C count instead of the shroud bit.
static inline CellClass* CellAtLevel_005864A0(const CoordStruct* coords, int level)
{
    CellStruct cell;
    cell.X = (short)(coords->X / 256);
    cell.Y = (short)(coords->Y / 256);

    CellStruct adjusted;
    adjusted.X = cell.X - level;
    adjusted.Y = cell.Y - level;

    int index = adjusted.Y * 512 + adjusted.X;
    if (index >= 0 && index < 0x40000) {
        CellClass* p = Cells_00586360[index];
        if (p != 0) {
            return p;
        }
    }
    InvalidCell_00586360.MapCoords = adjusted;
    return &InvalidCell_00586360;
}

bool MapClass::FUN_005864A0(const CoordStruct* coords) const
{
    int z = coords->Z / LevelHeight_00586360;
    CellClass* pCell;

    if (z & 1) {
        pCell = CellAtLevel_005864A0(coords, z / 2 + 1);
        if (pCell->unknown_13C <= 0) {
            return false;
        }
        if (pCell->GetNeighbourCell(3)->unknown_13C > 0) {
            return true;
        }
    } else {
        pCell = CellAtLevel_005864A0(coords, z / 2);
        if (pCell->unknown_13C > 0) {
            return true;
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x586AC0
// Pulls a cell back inside the local map rectangle: the cell is taken through the inverse isometric
// projection, moved onto the nearer edge of the rectangle, and projected back.
CellStruct* MapClass::FUN_00586AC0(CellStruct* out, const CellStruct* cell, bool flag) const
{
    int f = MapRect.Width;
    int cx = cell->X;
    int cy = cell->Y;
    int d = (f & 1) ? cx - cy + 1 : cx - cy;
    Point2D p;
    p.X = (d >> 1) + f / 2 - LocalRect.X;
    p.Y = cx + cy - f - LocalRect.Y;
    int halfW = LocalRect.Width / 2;
    int halfH = LocalRect.Height / 2;
    int x;
    int y;
    if (abs(p.X - halfW) < abs(p.Y - halfH)) {
        y = p.Y;
        if (p.X < halfW) {
            x = flag != 0;
        } else {
            x = flag ? LocalRect.Width - 1 : LocalRect.Width;
        }
    } else {
        x = p.X;
        if (p.Y < halfH) {
            y = flag != 0;
        } else {
            y = LocalRect.Height;
            if (flag) {
                --y;
            }
        }
    }
    int ax = x + LocalRect.X;
    int ay = y + LocalRect.Y;
    CellStruct r;
    r.X = (short)(ax + ((ay + 1) >> 1));
    r.Y = (short)(f + (ay >> 1) - ax);
    *out = r;
    return out;
}

// GLOBAL: GAMEMD 0x82A594 -- the movement zone compatibility table, eight entries per zone.
extern int DAT_0082A594[13][8];

// FUNCTION: GAMEMD 0x5889F0
// Picks the zone whose row fits both given zones best (-1 when none does).
int FUN_005889F0(int value, int running)
{
    int bestZone = -1;
    int bestCount = 0;
    for (int zone = 0; zone < 13; zone++) {
        bool fits = true;
        int count = 0;
        for (int j = 0; j < 8; j++) {
            int a = DAT_0082A594[value][j];
            int b = DAT_0082A594[running][j];
            int c = DAT_0082A594[zone][j];
            if ((a == 2 || b == 2) && c == 1) {
                fits = false;
            }
            if (a == c && b == c && c == 1) {
                count++;
            }
        }
        if (fits && count > bestCount) {
            bestCount = count;
            bestZone = zone;
        }
    }
    return bestZone;
}
