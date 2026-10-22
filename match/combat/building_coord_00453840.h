// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail instructions at 0x453840 establish the BuildingClass receiver,
//   offsets +0x520 / +0x69C, type-data offsets below, and vtable slots +0xAC
//   / +0x408. RTTI bytes identify the table as BuildingClass: COL 0x7FC360
//   points to TD 0x818D60 (".?AVBuildingClass@@"); its table begins at
//   0x7E3EBC and contains 0x453840 at 0x7E3F6C (slot 44).
#ifndef GG_MATCH_COMBAT_BUILDING_COORD_00453840_H
#define GG_MATCH_COMBAT_BUILDING_COORD_00453840_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Coord_00453840
{
    int X;
    int Y;
    int Z;

    Coord_00453840* Set(int x, int y, int z)
    {
        X = x;
        Y = y;
        Z = z;
        return this;
    }
};
GG_STATIC_ASSERT(sizeof(Coord_00453840) == 0xC);
GG_STATIC_ASSERT(offsetof(Coord_00453840, X) == 0x0);
GG_STATIC_ASSERT(offsetof(Coord_00453840, Y) == 0x4);
GG_STATIC_ASSERT(offsetof(Coord_00453840, Z) == 0x8);

struct Point_00453840
{
    int X;
    int Y;
};
GG_STATIC_ASSERT(sizeof(Point_00453840) == 8);
GG_STATIC_ASSERT(offsetof(Point_00453840, X) == 0x0);
GG_STATIC_ASSERT(offsetof(Point_00453840, Y) == 0x4);

struct TypeView_00453840
{
    char unknown_000[0xE44];
    int At_E44;
    int At_E48;
    char unknown_E4C[0x394];
    int At_11E0;
    int At_11E4;
    char unknown_11E8[0x393];
    unsigned char At_157B;
    char unknown_157C[0xC];
    Point_00453840 At_1588;
    char unknown_1590[0x135];
    unsigned char At_16C5;
    unsigned char At_16C6;
    char unknown_16C7[0x9D];
    unsigned char At_1764;
};
GG_STATIC_ASSERT(offsetof(TypeView_00453840, At_E44) == 0xE44);
GG_STATIC_ASSERT(offsetof(TypeView_00453840, At_E48) == 0xE48);
GG_STATIC_ASSERT(offsetof(TypeView_00453840, At_11E0) == 0x11E0);
GG_STATIC_ASSERT(offsetof(TypeView_00453840, At_11E4) == 0x11E4);
GG_STATIC_ASSERT(offsetof(TypeView_00453840, At_157B) == 0x157B);
GG_STATIC_ASSERT(offsetof(TypeView_00453840, At_1588) == 0x1588);
GG_STATIC_ASSERT(offsetof(TypeView_00453840, At_16C5) == 0x16C5);
GG_STATIC_ASSERT(offsetof(TypeView_00453840, At_16C6) == 0x16C6);
GG_STATIC_ASSERT(offsetof(TypeView_00453840, At_1764) == 0x1764);
GG_STATIC_ASSERT(sizeof(TypeView_00453840) == 0x1768);

struct BuildingClassVtbl_00453840;
struct BuildingClass_00453840
{
    BuildingClassVtbl_00453840* Vtbl;
    char unknown_004[0x51C];
    TypeView_00453840* At_520;
    char unknown_524[0x178];
    int At_69C;

    // FUNCTION: GAMEMD 0x453840
    Coord_00453840* FUN_00453840(Coord_00453840* out, int mode,
                                  int unused2, int unused3, int unused4);
    // FUNCTION: GAMEMD 0x6F3AD0 (direct __thiscall target; RET 0x14)
    Coord_00453840* FUN_006F3AD0(Coord_00453840* out, int mode,
                                 Coord_00453840 coord);
    // FUNCTION: GAMEMD 0x453BF0 (direct __thiscall target; RET 0x0C)
    Coord_00453840* FUN_00453BF0(Coord_00453840* coord, int mode, int flag);
};
GG_STATIC_ASSERT(offsetof(BuildingClass_00453840, Vtbl) == 0x000);
GG_STATIC_ASSERT(offsetof(BuildingClass_00453840, At_520) == 0x520);
GG_STATIC_ASSERT(offsetof(BuildingClass_00453840, At_69C) == 0x69C);
GG_STATIC_ASSERT(sizeof(BuildingClass_00453840) == 0x6A0);

typedef int (BuildingClass_00453840::*Fn408_00453840)();
typedef Coord_00453840* (BuildingClass_00453840::*FnAC_00453840)(Coord_00453840*);
struct BuildingClassVtbl_00453840
{
    char unknown_000[0xAC];
    FnAC_00453840 At_AC;
    char unknown_B0[0x358];
    Fn408_00453840 At_408;
};
GG_STATIC_ASSERT(offsetof(BuildingClassVtbl_00453840, At_AC) == 0xAC);
GG_STATIC_ASSERT(offsetof(BuildingClassVtbl_00453840, At_408) == 0x408);
GG_STATIC_ASSERT(sizeof(FnAC_00453840) == 4);
GG_STATIC_ASSERT(sizeof(Fn408_00453840) == 4);
GG_STATIC_ASSERT(sizeof(BuildingClassVtbl_00453840) == 0x40C);

struct Projector_00453840
{
    Point_00453840* CoordsToClient(Point_00453840* out, const int* in);
};
// GLOBAL: GAMEMD 0x887324
extern Projector_00453840* DAT_00887324;

#endif  // GG_MATCH_COMBAT_BUILDING_COORD_00453840_H
