// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Retail entry 0x4155F0, extent 0x1CD. AircraftClass vtable 0x7E22A4
//   slot +0x26C points here (0x7E2510); RTTI locator 0x7FB4C0 names
//   AircraftClass via type descriptor 0x817B90. All accessed prefixes below
//   come from this entry's instructions; unknown full extents stay unmodeled.
#ifndef GG_AIRCRAFT_MISSION_004155F0_H
#define GG_AIRCRAFT_MISSION_004155F0_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "_rt/gg_vslot.h"
#include "_layout/cell_class.h"
#include "core/cell_step_tables.h"

struct Coord_004155F0 { int X, Y, Z; };
GG_STATIC_ASSERT(offsetof(Coord_004155F0, X) == 0);
GG_STATIC_ASSERT(offsetof(Coord_004155F0, Y) == 4);
GG_STATIC_ASSERT(offsetof(Coord_004155F0, Z) == 8);
GG_STATIC_ASSERT(sizeof(Coord_004155F0) == 12);
struct Cell_004155F0
{
    short X, Y;
    // Inlined value comparison at retail 0x41574E / 0x415760.
    bool operator!=(const Cell_004155F0& other) const
    {
        return X != other.X || Y != other.Y;
    }
    // CellStruct::operator+ written out: the sum of two cells.
    Cell_004155F0 operator+(const CellStruct& offset) const
    {
        Cell_004155F0 sum;
        sum.X = X + offset.X;
        sum.Y = Y + offset.Y;
        return sum;
    }
};
GG_STATIC_ASSERT(offsetof(Cell_004155F0, X) == 0);
GG_STATIC_ASSERT(offsetof(Cell_004155F0, Y) == 2);
GG_STATIC_ASSERT(sizeof(Cell_004155F0) == 4);

struct House_004155F0
{
    char unknown_00[0x1E0];
    int At_1E0;
    // FUNCTION: GAMEMD 0x50DAC0 — ECX receiver, no stack arguments.
    int FUN_0050DAC0();
    // FUNCTION: GAMEMD 0x50DA80 (decl; reloc) — ECX receiver, no stack arguments.
    int FUN_0050DA80();
};
GG_STATIC_ASSERT(offsetof(House_004155F0, At_1E0) == 0x1E0);
struct Rules_004155F0
{
    char unknown_00[0x280];
    int Sound;
    char unknown_284[0xC];
    int At_290;
};
GG_STATIC_ASSERT(offsetof(Rules_004155F0, Sound) == 0x280);
GG_STATIC_ASSERT(offsetof(Rules_004155F0, At_290) == 0x290);

// GLOBAL: GAMEMD 0x8871E0
extern Rules_004155F0* RulesInstance_004155F0;

struct WeaponType_004155F0
{
    char unknown_00[0xA4];
    int Damage;
    char unknown_A8[0xC];
    int Range;
};
GG_STATIC_ASSERT(offsetof(WeaponType_004155F0, Damage) == 0xA4);
GG_STATIC_ASSERT(offsetof(WeaponType_004155F0, Range) == 0xB4);
struct Weapon_004155F0 { WeaponType_004155F0* Type; };
GG_STATIC_ASSERT(offsetof(Weapon_004155F0, Type) == 0);

struct AircraftType_004155F0;
struct Vtbl_004155F0;
struct Aircraft_004155F0
{
    Vtbl_004155F0* Vptr;
    char unknown_04[0x9C - 4];
    Coord_004155F0 Location;
    char unknown_A8[0x21C - 0xA8];
    House_004155F0* Owner;
    char unknown_220[0x260 - 0x220];
    int LastSightRange;
    char unknown_264[0x2B4 - 0x264];
    void* Target;
    char unknown_2B8[0x2FC - 0x2B8];
    void* At_2FC;
    char unknown_300[0x5A4 - 0x300];
    void* Destination;
    char unknown_5A8[0x5D4 - 0x5A8];
    void* At_5D4;
    char unknown_5D8[0x6C4 - 0x5D8];
    AircraftType_004155F0* Type;
    char unknown_6C8[0x6D2 - 0x6C8];
    unsigned char IsLocked;

    // FUNCTION: GAMEMD 0x4155F0
    int FUN_004155F0();
    // FUNCTION: GAMEMD 0x4157C0
    int FUN_004157C0();
    // FUNCTION: GAMEMD 0x415A50
    int FUN_00415A50();
    // FUNCTION: GAMEMD 0x4195A0
    int FUN_004195A0(Aircraft_004155F0* other, Cell_004155F0* out);
    // FUNCTION: GAMEMD 0x41A940
    int FUN_0041A940();
    // FUNCTION: GAMEMD 0x65AE30 (decl; reloc) -- ECX receiver, no stack arguments.
    bool FUN_0065AE30();
    // FUNCTION: GAMEMD 0x4D6AA0 (decl; reloc) -- ECX receiver, no stack arguments.
    int FUN_004D6AA0();
    // FUNCTION: GAMEMD 0x5F6440 — __thiscall, one pushed target.
    int FUN_005F6440(void* target);
};
GG_STATIC_ASSERT(offsetof(Aircraft_004155F0, Vptr) == 0);
GG_STATIC_ASSERT(offsetof(Aircraft_004155F0, Location) == 0x9C);
GG_STATIC_ASSERT(offsetof(Aircraft_004155F0, Owner) == 0x21C);
GG_STATIC_ASSERT(offsetof(Aircraft_004155F0, LastSightRange) == 0x260);
GG_STATIC_ASSERT(offsetof(Aircraft_004155F0, Target) == 0x2B4);
GG_STATIC_ASSERT(offsetof(Aircraft_004155F0, At_2FC) == 0x2FC);
GG_STATIC_ASSERT(offsetof(Aircraft_004155F0, Destination) == 0x5A4);
GG_STATIC_ASSERT(offsetof(Aircraft_004155F0, At_5D4) == 0x5D4);
GG_STATIC_ASSERT(offsetof(Aircraft_004155F0, Type) == 0x6C4);
GG_STATIC_ASSERT(offsetof(Aircraft_004155F0, IsLocked) == 0x6D2);

struct AircraftTypeVtbl_004155F0;
struct AircraftType_004155F0
{
    AircraftTypeVtbl_004155F0* Vptr;
};
typedef int (AircraftType_004155F0::*FnBC_004155F0)();
struct AircraftTypeVtbl_004155F0
{
    char unknown_00[0xBC];
    FnBC_004155F0 At_BC;
};
GG_STATIC_ASSERT(offsetof(AircraftTypeVtbl_004155F0, At_BC) == 0xBC);
typedef void (Aircraft_004155F0::*Fn1E8_004155F0)(int, int);
typedef Weapon_004155F0* (Aircraft_004155F0::*Fn3F8_004155F0)(int);
typedef Coord_004155F0* (Aircraft_004155F0::*Fn48_004155F0)(Coord_004155F0*);
typedef void* (Aircraft_004155F0::*Fn1BC_004155F0)();
typedef int (Aircraft_004155F0::*Fn1C8_004155F0)();
typedef char (Aircraft_004155F0::*Fn2AC_004155F0)();
typedef void (Aircraft_004155F0::*Fn480_004155F0)(void*, int);
typedef void (Aircraft_004155F0::*Fn484_004155F0)(int, int);
typedef void (Aircraft_004155F0::*Fn488_004155F0)(int, int, int, int, int);
typedef void (Aircraft_004155F0::*Fn48C_004155F0)(int, int, int, int);
GG_STATIC_ASSERT(sizeof(Fn1E8_004155F0) == 4);
GG_STATIC_ASSERT(sizeof(Fn3F8_004155F0) == 4);
GG_STATIC_ASSERT(sizeof(Fn48_004155F0) == 4);
GG_STATIC_ASSERT(sizeof(Fn1BC_004155F0) == 4);
GG_STATIC_ASSERT(sizeof(Fn1C8_004155F0) == 4);
GG_STATIC_ASSERT(sizeof(Fn2AC_004155F0) == 4);
GG_STATIC_ASSERT(sizeof(Fn484_004155F0) == 4);
GG_STATIC_ASSERT(sizeof(Fn480_004155F0) == 4);
GG_STATIC_ASSERT(sizeof(Fn488_004155F0) == 4);
GG_STATIC_ASSERT(sizeof(Fn48C_004155F0) == 4);
// Retail entries: +0x1E8 = 0x41BA90 (RET 8), +0x3F8 = 0x70E140 (RET 4),
// +0x480 = 0x41AA80 (RET 8), +0x488 = 0x70AF50 (RET 0x14),
// +0x48C = 0x70B1D0 (RET 0x10), re-read from vtable 0x7E22A4.
struct Vtbl_004155F0
{
    char unknown_00[0x48];
    Fn48_004155F0 GetCoords;
    char unknown_4C[0x1BC - 0x4C];
    Fn1BC_004155F0 At_1BC;
    char unknown_1C0[0x1C8 - 0x1C0];
    Fn1C8_004155F0 At_1C8;
    char unknown_1CC[0x1E8 - 0x1CC];
    Fn1E8_004155F0 QueueMission;
    char unknown_1EC[0x2AC - 0x1EC];
    Fn2AC_004155F0 At_2AC;
    char unknown_2B0[0x3F8 - 0x2B0];
    Fn3F8_004155F0 GetWeapon;
    char unknown_3FC[0x480 - 0x3FC];
    Fn480_004155F0 SetDestination;
    Fn484_004155F0 At_484;
    Fn488_004155F0 At_488;
    Fn48C_004155F0 At_48C;
};
GG_STATIC_ASSERT(offsetof(Vtbl_004155F0, QueueMission) == 0x1E8);
GG_STATIC_ASSERT(offsetof(Vtbl_004155F0, GetCoords) == 0x48);
GG_STATIC_ASSERT(offsetof(Vtbl_004155F0, At_1BC) == 0x1BC);
GG_STATIC_ASSERT(offsetof(Vtbl_004155F0, At_1C8) == 0x1C8);
GG_STATIC_ASSERT(offsetof(Vtbl_004155F0, At_2AC) == 0x2AC);
GG_STATIC_ASSERT(offsetof(Vtbl_004155F0, GetWeapon) == 0x3F8);
GG_STATIC_ASSERT(offsetof(Vtbl_004155F0, At_484) == 0x484);
GG_STATIC_ASSERT(offsetof(Vtbl_004155F0, SetDestination) == 0x480);
GG_STATIC_ASSERT(offsetof(Vtbl_004155F0, At_488) == 0x488);
GG_STATIC_ASSERT(offsetof(Vtbl_004155F0, At_48C) == 0x48C);

struct Map_004155F0
{
    // FUNCTION: GAMEMD 0x4AA440 — seven pushed words, RET 0x1C.
    Cell_004155F0* FUN_004AA440(Cell_004155F0* out, int side,
        const Cell_004155F0* a, const Cell_004155F0* b, int c, int d, int e);
    // FUNCTION: GAMEMD 0x5657A0 — one pushed cell pointer, RET 4.
    void* FUN_005657A0(const Cell_004155F0& cell);
    // FUNCTION: GAMEMD 0x567DA0 — four pushed words, RET 0x10.
    void FUN_00567DA0(const Coord_004155F0* location, int a, int range, int b);
    // FUNCTION: GAMEMD 0x568300 (decl; reloc) -- whether a cell coordinate is on the map (RET 4).
    bool FUN_00568300(const Cell_004155F0* cell);
};
// GLOBAL: GAMEMD 0x87F7E8
extern Map_004155F0 DAT_0087F7E8;
// GLOBAL: GAMEMD 0x889E68 — the two-word sentinel read by the final comparison.
extern Cell_004155F0 DAT_00889E68;
// FUNCTION: GAMEMD 0x7509E0 — index in ECX, coordinates in EDX, RET 4.
void* FUN_007509E0(int index, const Coord_004155F0* location, void* controller);

#endif // GG_AIRCRAFT_MISSION_004155F0_H
