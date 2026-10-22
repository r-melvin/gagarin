// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, globals, the two out-parameter helpers and the vtable slots read
//   off the user's retail gamemd.exe v1.001 via the local Ghidra CLI at
//   0x5D7030. YRpp supplies the names
//   `MPGameModeClass::SpawnBaseUnits` (retail class name: MultiplayerGameMode),
//   Unsorted::Bases (0xA8B258) and the
//   UnitClass(UnitTypeClass*, HouseClass*) constructor at 0x7353C0; every
//   offset is reconfirmed here from the disassembly.
#ifndef GG_MATCH_NETWORK_MP_GAME_MODE_CLASS_SPAWN_METHODS_H
#define GG_MATCH_NETWORK_MP_GAME_MODE_CLASS_SPAWN_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// GLOBAL: GAMEMD 0xA8B258 — Unsorted::Bases (bases enabled for this game).
extern char DAT_00A8B258;

struct Coord_005D7030 { int X; int Y; int Z; };
GG_STATIC_ASSERT(sizeof(Coord_005D7030) == 0x0C);

struct Cell_005D7030 { short X; short Y; };
GG_STATIC_ASSERT(sizeof(Cell_005D7030) == 0x04);

struct UnitType_005D7030;
struct Vtbl_005D7030;

// The unit that gets built; only its vtable is touched here.
struct Unit_005D7030
{
    Vtbl_005D7030* Vptr;    // +0x0000

    // FUNCTION: GAMEMD 0x7353C0 (decl; reloc) — UnitClass::UnitClass.
    Unit_005D7030* Construct(UnitType_005D7030* type, struct House_005D7030* owner);
};

typedef bool (Unit_005D7030::*FnD8_005D7030)(Coord_005D7030* coords, int facing);
typedef void (Unit_005D7030::*Fn20_005D7030)(int flags);

struct Vtbl_005D7030
{
    char _pad000[0x20];          // +0x0000
    Fn20_005D7030 At_20;         // +0x0020  scalar-deleting destructor
    char _pad024[0xD8 - 0x24];   // +0x0024
    FnD8_005D7030 At_D8;         // +0x00D8  place on the map at a coordinate
};
GG_STATIC_ASSERT(offsetof(Vtbl_005D7030, At_20) == 0x20);
GG_STATIC_ASSERT(offsetof(Vtbl_005D7030, At_D8) == 0xD8);

// The base-unit type list inside the rules; opaque here, only its address is
// taken (`ADD EAX,0xB20`).
struct RulesUnitList_005D7030 { int At_00; };

struct Rules_005D7030
{
    char _pad0000[0xB20];                 // +0x0000
    RulesUnitList_005D7030 At_B20;        // +0x0B20  the base-unit type list
};
GG_STATIC_ASSERT(offsetof(Rules_005D7030, At_B20) == 0xB20);

// GLOBAL: GAMEMD 0x8871E0 — RulesClass::Instance.
extern Rules_005D7030* DAT_008871E0;

struct House_005D7030
{
    // FUNCTION: GAMEMD 0x505310 (decl; reloc) — pick the buildable type out of a list.
    UnitType_005D7030* FUN_00505310(RulesUnitList_005D7030* list);
    // FUNCTION: GAMEMD 0x50DEF0 (decl; reloc) — the house's base cell.
    Cell_005D7030* FUN_0050DEF0(Cell_005D7030* out);
    // FUNCTION: GAMEMD 0x50DF30 (decl; reloc) — the house's base coordinate.
    Coord_005D7030* FUN_0050DF30(Coord_005D7030* out);
};

// FUNCTION: GAMEMD 0x688ED0 (decl; reloc) — scatter-place a unit near a cell.
int __fastcall FUN_00688ED0(Unit_005D7030* unit, Cell_005D7030* cell, int flag);

struct MultiplayerGameMode_005D7030
{
    // FUNCTION: GAMEMD 0x5D7030 — MultiplayerGameMode::SpawnBaseUnits (virtual;
    // `this` is never read, so a plain member reproduces the body bytes).
    bool SpawnBaseUnits(House_005D7030* house, unsigned long unused);
};

#endif  // GG_MATCH_NETWORK_MP_GAME_MODE_CLASS_SPAWN_METHODS_H
