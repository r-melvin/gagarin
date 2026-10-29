// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; the one lightweight view of the map object at 0x87F7E8 (MapClass, the display
// chain's MouseClass; see ui/input_controls/ui_display_chain.h for the full class). Translation units that only call
// a few of its methods and cannot take the whole display chain use this view. Every such TU must include this header
// and use DAT_0087F7E8; do not declare another view of the object.
#ifndef GG_MATCH__LAYOUT_MAP_0087F7E8_H_H
#define GG_MATCH__LAYOUT_MAP_0087F7E8_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class CellClass;
class HouseClass;
class ObjectClass;
struct CoordStruct;
struct CellStruct;
struct Triple_00747EB0;
struct Triple_005247D0;
struct MapObjCell;
struct Rect_4i;
struct Cell_005A7250;
struct CellStruct_005A7250;

struct Map_0087F7E8
{
    // FUNCTION: GAMEMD 0x4AE450 (decl; reloc)
    void FUN_004AE450();
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc)
    CellClass* FUN_005657A0(const CellStruct* cell);
    // FUNCTION: GAMEMD 0x5657E0 (decl; reloc)
    bool FUN_005657E0(const CellStruct* cell);
    // FUNCTION: GAMEMD 0x56D230 (decl; reloc) -- the zone of a cell for a movement zone.
    int FUN_0056D230(const CellStruct& cell, int movementZone, bool isBridge);
    // FUNCTION: GAMEMD 0x568300 (decl; reloc) -- is the cell coordinate on the map (terrain-object cell view).
    bool FUN_00568300(const MapObjCell* cell);
    // FUNCTION: GAMEMD 0x4F42F0
    void FUN_004F42F0(int);
    // FUNCTION: GAMEMD 0x568BB0 (declaration)
    void FUN_00568BB0(char a1);
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
    // FUNCTION: GAMEMD 0x5673A0 (decl; reloc)
    void FUN_005673A0(CoordStruct* where, int sight, HouseClass* house, int a, int b, int c, int d, int e);
    // FUNCTION: GAMEMD 0x4ACAC0 (decl; reloc)
    void FUN_004ACAC0();
    // FUNCTION: GAMEMD 0x4A8BF0 (decl; reloc)
    void FUN_004A8BF0(int a);
    // FUNCTION: GAMEMD 0x4AC8C0 (decl; reloc)
    void FUN_004AC8C0(int a);
    // FUNCTION: GAMEMD 0x4AC660 (decl; reloc)
    void FUN_004AC660(int a);
    // FUNCTION: GAMEMD 0x6938C0 (decl; reloc)
    void FUN_006938C0();
    // FUNCTION: GAMEMD 0x4F4480 (decl; reloc)
    void FUN_004F4480();
    // FUNCTION: GAMEMD 0x580BC0 (decl; reloc)
    void* FUN_00580BC0(void* a1);
    // FUNCTION: GAMEMD 0x4F4450 (decl; reloc) -- take a button off the list.
    void FUN_004F4450(void* button);
    // FUNCTION: GAMEMD 0x4F4410 (decl; reloc) -- add a button to the list.
    void FUN_004F4410(void* button);
    // FUNCTION: GAMEMD 0x6A60A0 (decl; reloc) -- repaint that sidebar tab.
    void FUN_006A60A0(unsigned int tab);
    // FUNCTION: GAMEMD 0x578AC0 (decl; reloc) -- bump the redraw counter.
    void FUN_00578AC0();
    // FUNCTION: GAMEMD 0x578AD0 (decl; reloc)
    int FUN_00578AD0(int cell, int* arg);
    // FUNCTION: GAMEMD 0x578080 (decl; reloc) -- __thiscall, one pointer argument.
    int FUN_00578080(Triple_00747EB0* value);
    // FUNCTION: GAMEMD 0x578080 (decl; reloc) -- the same entry point, second typed view.
    int FUN_00578080(Triple_005247D0* value);
    // FUNCTION: GAMEMD 0x565730 (decl; reloc) -- the cell under a coordinate.
    CellClass* FUN_00565730(const CoordStruct* coord);
    // FUNCTION: GAMEMD 0x4A9720 (decl; reloc) -- DisplayClass::Submit, put an object on the map.
    void FUN_004A9720(ObjectClass* object);
    // FUNCTION: GAMEMD 0x4A9770 (decl; reloc) -- DisplayClass::Remove, take an object off the map.
    void FUN_004A9770(ObjectClass* object);
    // FUNCTION: GAMEMD 0x4AEB10 (decl; reloc) -- the object under focus.
    ObjectClass* FUN_004AEB10();
    // FUNCTION: GAMEMD 0x4AEB30 (decl; reloc) -- set the object under focus.
    void FUN_004AEB30(ObjectClass* object);
    // FUNCTION: GAMEMD 0x5785F0 (decl; reloc) -- whether a coordinate is in the usable area.
    bool FUN_005785F0(const CoordStruct& coord);
    // FUNCTION: GAMEMD 0x574000 (decl; reloc) -- one stack argument.
    void FUN_00574000(const CellStruct* cell);
    // FUNCTION: GAMEMD 0x574C20 (decl; reloc) -- one stack argument.
    void FUN_00574C20(const CellStruct* cell);
    // FUNCTION: GAMEMD 0x5865E0 (decl; reloc) -- MapClass::IsLocationFogged, retail stub (constant false).
    bool IsLocationFogged(const CoordStruct* coords) const;
    // FUNCTION: GAMEMD 0x578080 (decl; reloc) -- the ground height at a coordinate.
    int FUN_00578080(const CoordStruct* coord);
    // FUNCTION: GAMEMD 0x6551C0 (decl; reloc) -- flag the cell's radar pixel.
    void FUN_006551C0(CellStruct const& cell);
    // FUNCTION: GAMEMD 0x586360 (decl; reloc) -- whether a coordinate is under shroud.
    bool IsLocationShrouded(const CoordStruct& coord) const;
    // FUNCTION: GAMEMD 0x578540 (decl; reloc) -- whether a cell is inside the usable area.
    bool FUN_00578540(CellClass* cell, bool flag);
};

// GLOBAL: GAMEMD 0x87F7E8 -- the map object.
extern Map_0087F7E8 DAT_0087F7E8;

#endif
