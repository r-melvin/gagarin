// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x74D490: `[EDI+0x100]` (IsDead) and `LEA
//   ESI,[EDI+0xF8]` with `MOVSX...,word [EDI+0xF8]` / `[EDI+0xFA]` (the
//   monster's CellStruct) -- both already asserted in
//   match/map/veinhole_monster_methods.h and
//   match/map/veinhole_monster_eligible_methods.h -- plus `[EDI+0xFC]`
//   (the shape/palette pointer nulled when the cell is hidden), the cell
//   members `[EAX+0x140]` (flag 0x400000), `MOVSX byte [EAX+0x11B]` (Level,
//   multiplied by 15 through `LEA EAX,[EAX+EAX*2]; LEA ESI,[EAX+EAX*4]`) and
//   `MOVSX word [EAX+0x10C]`, the globals `[0xB1D2EC]`, `[0x886FA4]`,
//   `0x886FA0`, `[0x887324]`, `[0x887314]`, `[0xA83D4C]+0x16054` and
//   `[0xB054D4]` with `[EAX+0x30C]` off the indexed house. The map instance
//   is the fixed `MOV ECX,0x87F7E8`. VeinholeMonsterClass::DrawIt is YRpp's
//   name; every offset is reconfirmed here.
#ifndef GG_MATCH_MAP_VEINHOLE_MONSTER_DRAW_METHODS_H
#define GG_MATCH_MAP_VEINHOLE_MONSTER_DRAW_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Cell_0074D490  { short X; short Y; };
struct Point_0074D490 { int X; int Y; };
struct Coord_0074D490 { int X; int Y; int Z; };
GG_STATIC_ASSERT(sizeof(Cell_0074D490)  == 4);
GG_STATIC_ASSERT(sizeof(Point_0074D490) == 8);
GG_STATIC_ASSERT(sizeof(Coord_0074D490) == 0xC);

struct CellClass_0074D490
{
    char        _pad0000[0x10C];          // +0x0000
    short       unknown_10C;              // +0x010C  handed to the blitter
    char        _pad010E[0x11B - 0x10E];  // +0x010E
    signed char Level;                    // +0x011B
    char        _pad011C[0x140 - 0x11C];  // +0x011C
    int         Flags;                    // +0x0140  0x400000 = hidden
};
GG_STATIC_ASSERT(offsetof(CellClass_0074D490, unknown_10C) == 0x10C);
GG_STATIC_ASSERT(offsetof(CellClass_0074D490, Level)       == 0x11B);
GG_STATIC_ASSERT(offsetof(CellClass_0074D490, Flags)       == 0x140);

struct Map_0074D490
{
    // FUNCTION: GAMEMD 0x565730 (decl; reloc) -- MapClass::GetTargetCell.
    CellClass_0074D490* GetCellAtCoord(const Coord_0074D490& coord);
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) -- MapClass::GetCellAt.
    CellClass_0074D490* GetCellAt(const Cell_0074D490& cell);
};

// GLOBAL: GAMEMD 0x87F7E8 -- MapClass::Instance (used by address, ECX).
extern Map_0074D490 DAT_0087F7E8;

struct Tactical_0074D490
{
    // FUNCTION: GAMEMD 0x6D2140 (decl; reloc) -- Tactical::CoordsToClient.
    bool CoordsToClient(const Coord_0074D490* coord, Point_0074D490* dest);
    // FUNCTION: GAMEMD 0x6D9EF0 (decl; reloc) -- Tactical::AddSelectable.
    bool AddSelectable(void* object, int x, int y);
};

// GLOBAL: GAMEMD 0x887324 -- Tactical::Instance (a pointer variable).
extern Tactical_0074D490* DAT_00887324;

// GLOBAL: GAMEMD 0x887314 -- the surface/blitter instance handed to 0x4AED70.
extern void* DAT_00887314;

// GLOBAL: GAMEMD 0xB1D2EC -- the veinhole shape resource.
extern void* DAT_00B1D2EC;

// GLOBAL: GAMEMD 0x886FA4 -- the tactical view's Y origin.
extern int DAT_00886FA4;

// GLOBAL: GAMEMD 0x886FA0 -- the clipping rectangle, passed by address.
extern int DAT_00886FA0;

struct House_0074D490
{
    char  _pad0000[0x30C];     // +0x0000
    void* unknown_30C;         // +0x030C  the house's remap table
};
GG_STATIC_ASSERT(offsetof(House_0074D490, unknown_30C) == 0x30C);

struct Scenario_0074D490
{
    char _pad0000[0x16054];    // +0x0000
    int  unknown_16054;          // +0x16054
};
GG_STATIC_ASSERT(offsetof(Scenario_0074D490, unknown_16054) == 0x16054);

// GLOBAL: GAMEMD 0xA83D4C -- ScenarioClass::Instance.
extern Scenario_0074D490* DAT_00A83D4C;
// GLOBAL: GAMEMD 0xB054D4 -- HouseClass::Array.Items.
extern House_0074D490** DAT_00B054D4;

// FUNCTION: GAMEMD 0x4AED70 (decl; reloc) -- the shape blitter.
void __fastcall FUN_004AED70(void* surface, void* remap, void* shape, void* palette,
                             Point_0074D490* point, void* clip, int a7, int a8,
                             int a9, int a10, int a11, int a12, int a13, int a14,
                             Point_0074D490 offset);

struct Monster_0074D490
{
    char            _pad0000[0xF8];    // +0x0000
    Cell_0074D490   Cell;              // +0x00F8
    void*           unknown_FC;        // +0x00FC
    char            IsDead;            // +0x0100

    // FUNCTION: GAMEMD 0x74D490 -- VeinholeMonsterClass::DrawIt.
    void DrawIt();
};
GG_STATIC_ASSERT(offsetof(Monster_0074D490, Cell)       == 0xF8);
GG_STATIC_ASSERT(offsetof(Monster_0074D490, unknown_FC) == 0xFC);
GG_STATIC_ASSERT(offsetof(Monster_0074D490, IsDead)     == 0x100);

#endif  // GG_MATCH_MAP_VEINHOLE_MONSTER_DRAW_METHODS_H
