// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; shared address-named view (one definition for every TU that uses it).
#ifndef GG_MATCH__LAYOUT_GBL_0087F7E8_H_H
#define GG_MATCH__LAYOUT_GBL_0087F7E8_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class CellClass;
struct CellStruct;
struct Rect_4i;
struct Cell_005A7250;
struct CellStruct_005A7250;

struct Gbl_0087F7E8
{
    // FUNCTION: GAMEMD 0x4F42F0
    void FUN_004F42F0(int);
    // FUNCTION: GAMEMD 0x568BB0 (declaration)
    void FUN_00568BB0(char a1);
    // FUNCTION: GAMEMD 0x5657A0 (declaration)
    CellClass* FUN_005657A0(CellStruct const* a1);
    // FUNCTION: GAMEMD 0x56D230 (declaration) -- the zone of a cell for a movement zone.
    int FUN_0056D230(const CellStruct& cell, int movementZone, bool isBridge);
    // FUNCTION: GAMEMD 0x578290 (declaration)
    CellClass* FUN_00578290();
    // FUNCTION: GAMEMD 0x578350 (declaration)
    void FUN_00578350();
    // FUNCTION: GAMEMD 0x578460 (declaration)
    bool FUN_00578460(CellStruct const* a1, char a2);
    // FUNCTION: GAMEMD 0x578E60 (declaration)
    void FUN_00578E60(int a1, int a2);
    // FUNCTION: GAMEMD 0x588AC0
    void FUN_00588AC0();
    // FUNCTION: GAMEMD 0x5BDB90
    void FUN_005BDB90(int, int);
    // FUNCTION: GAMEMD 0x654490 (declaration)
    void FUN_00654490(Rect_4i* a1);
    // FUNCTION: GAMEMD 0x654650 (declaration)
    void FUN_00654650();
    // FUNCTION: GAMEMD 0x655990 (declaration)
    void FUN_00655990();
    // FUNCTION: GAMEMD 0x56C510 (declaration) -- the full zone rebuild.
    void FUN_0056C510();
    // FUNCTION: GAMEMD 0x581F50 (declaration)
    void FUN_00581F50();
    // FUNCTION: GAMEMD 0x657CE0 (declaration)
    void FUN_00657CE0();
    // The same entry point 0x5657A0 as the 0x5A7250 TU spelled it (by reference, its own cell view).
    Cell_005A7250* GetCell(const CellStruct_005A7250& cell);
};

#endif
