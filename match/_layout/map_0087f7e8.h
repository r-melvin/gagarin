// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; the one lightweight view of the map object at 0x87F7E8 (MapClass, the display
// chain's MouseClass; see ui/input_controls/ui_display_chain.h for the full class). Translation units that only call
// a few of its methods and cannot take the whole display chain use this view. Every such TU must include this header
// and use DAT_0087F7E8; do not declare another view of the object.
#ifndef GG_MATCH__LAYOUT_MAP_0087F7E8_H_H
#define GG_MATCH__LAYOUT_MAP_0087F7E8_H_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "cell.h"   // CellStruct / Cell: the by-value NearByLocation wrapper below needs the complete type

class CellClass;
class CCINIClass;
class BufferStraw;
class HouseClass;
class ObjectClass;
class BuildingClass;
class BuildingTypeClass;
template<class T> class DynamicVectorClass;
struct Point2D;
struct CoordStruct;
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
    bool FUN_00568300(const CellStruct* cell);
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
    // FUNCTION: GAMEMD 0x579B70 (declaration) -- thiscall, one cell argument.
    unsigned int FUN_00579B70(CellClass* cell);
    // FUNCTION: GAMEMD 0x578E60 (declaration)
    void FUN_00578E60(int a1, int a2);
    // FUNCTION: GAMEMD 0x588AC0
    void FUN_00588AC0();
    // FUNCTION: GAMEMD 0x5BDA80 (decl; reloc)
    void FUN_005BDA80(int a, int b);
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
    // The same entry point taking the active foundation (a pointer) instead of the cleared value.
    void FUN_004A8BF0(void* foundation);
    // FUNCTION: GAMEMD 0x4A91B0 (decl; reloc) -- the cell under an object, by reference (an rvalue result binds).
    void FUN_004A91B0(CellStruct* out, const CellStruct& value);
    // FUNCTION: GAMEMD 0x577AB0 (decl; reloc) -- one house argument (RET 4).
    void FUN_00577AB0(HouseClass* house);
    // FUNCTION: GAMEMD 0x577D90 (decl; reloc) -- one house argument (RET 4).
    void FUN_00577D90(HouseClass* house);
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
    // The same routine taking the coordinate by reference (an rvalue result of a coordinate getter can bind to it).
    CellClass* FUN_00565730(const CoordStruct& coord);
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
    // FUNCTION: GAMEMD 0x5687F0 (decl; reloc) -- take a building's footprint off the cell map.
    void FUN_005687F0(CellStruct* cell, BuildingClass* building);
    // FUNCTION: GAMEMD 0x5683C0 (decl; reloc) -- put a building's footprint on the cell map.
    void FUN_005683C0(CellStruct* cell, BuildingClass* building);
    // FUNCTION: GAMEMD 0x5687F0 / 0x5683C0 (decl; reloc) -- the same two entries, for any placed object.
    void FUN_005687F0(CellStruct* cell, ObjectClass* object);
    void FUN_005683C0(CellStruct* cell, ObjectClass* object);
    // FUNCTION: GAMEMD 0x5678E0 (decl; reloc) -- reveal the map around a coordinate (five one-byte flags).
    void FUN_005678E0(const CoordStruct* where, int sight, HouseClass* house, char a, char b, char c, char d, char e);
    // FUNCTION: GAMEMD 0x4AA290 (decl; reloc) -- the building on a cell, with the screen point of the hit.
    BuildingClass* FUN_004AA290(CellStruct* cell, Point2D* out);
    // FUNCTION: GAMEMD 0x656580 (decl; reloc) -- the foundation point list of a building type (one stack argument).
    DynamicVectorClass<Point2D>* FUN_00656580(BuildingTypeClass* type);
    // FUNCTION: GAMEMD 0x655740 (decl; reloc) -- three stack arguments.
    void FUN_00655740(BuildingClass* building, int x, int y);
    // FUNCTION: GAMEMD 0x568350 (decl; reloc) -- is the coordinate inside the map; CoordStruct by reference.
    bool FUN_00568350(const CoordStruct& coord);
    // FUNCTION: GAMEMD 0x6562D0 (decl; reloc) -- one stack argument.
    void FUN_006562D0(Point2D* point);
    // ---- Additions for folding the private per-TU views onto this one (each entry verified against the
    // ---- binary: thiscall on 0x87F7E8, RET n = the stack words listed).
    // FUNCTION: GAMEMD 0x4A8D50 (decl; reloc) -- take the 0xC8-byte foundation record (one stack argument, RET 4; null clears).
    void FUN_004A8D50(void* foundation);
    // FUNCTION: GAMEMD 0x4A94F0 (decl; reloc) -- the extent of a foundation cell list, returned through a hidden pointer (RET 8).
    Cell FUN_004A94F0(const CellStruct* foundation);
    // FUNCTION: GAMEMD 0x4AA440 (decl; reloc) -- pick a cell on a map edge; the result comes back through the hidden pointer (RET 0x1C).
    CellStruct* FUN_004AA440(CellStruct* out, int side, CellStruct* a, CellStruct* b, int c, int d, int e);
    // FUNCTION: GAMEMD 0x4AC4F0 (decl; reloc)
    void FUN_004AC4F0();
    // FUNCTION: GAMEMD 0x4AC960 (decl; reloc) -- one stack argument.
    void FUN_004AC960(int mode);
    // FUNCTION: GAMEMD 0x4ACA10 (decl; reloc) -- infantry sub-location pick; hidden out pointer returned (RET 0xC).
    CoordStruct* FUN_004ACA10(CoordStruct* out, const CoordStruct* in, bool flag);
    // FUNCTION: GAMEMD 0x4AD7E0 (decl; reloc) -- one INI argument (RET 4).
    void FUN_004AD7E0(CCINIClass* ini);
    // FUNCTION: GAMEMD 0x4ADCD0 (decl; reloc) -- two stack arguments.
    void FUN_004ADCD0(int a, int b);
    // FUNCTION: GAMEMD 0x4ADEE0 (decl; reloc) -- two stack arguments.
    void FUN_004ADEE0(int a, int b);
    // FUNCTION: GAMEMD 0x4AE4C0 (decl; reloc) -- the cell lighting sweep.
    void FUN_004AE4C0();
    // FUNCTION: GAMEMD 0x565B00 (decl; reloc)
    void FUN_00565B00();
    // FUNCTION: GAMEMD 0x567DA0 (decl; reloc) -- four stack arguments (RET 0x10).
    void FUN_00567DA0(CoordStruct* where, int a, int b, int c);
    // FUNCTION: GAMEMD 0x56B5A0 / 0x56B780 / 0x56B8A0 / 0x56B9A0 / 0x56BAC0 (decl; reloc) -- one stream argument each (RET 4).
    void FUN_0056B5A0(BufferStraw* straw);
    void FUN_0056B780(BufferStraw* straw);
    void FUN_0056B8A0(BufferStraw* straw);
    void FUN_0056B9A0(BufferStraw* straw);
    void FUN_0056BAC0(BufferStraw* straw);
    // FUNCTION: GAMEMD 0x56BD40 (decl; reloc)
    void FUN_0056BD40();
    // FUNCTION: GAMEMD 0x56BEC0 (decl; reloc) -- cell by value, then a value (RET 8).
    bool FUN_0056BEC0(CellStruct cell, int value);
    // FUNCTION: GAMEMD 0x56D100 (decl; reloc) -- path pre-check between two cells (RET 0x18).
    bool FUN_0056D100(CellStruct* from, CellStruct* to, int a, int b, int c, int d);
    // FUNCTION: GAMEMD 0x56D230 (decl; reloc) -- the same entry point taking the cell by pointer.
    int FUN_0056D230(const CellStruct* cell, int movementZone, bool isBridge);
    // FUNCTION: GAMEMD 0x56D3F0 (decl; reloc) -- one cell argument (RET 4).
    int FUN_0056D3F0(const CellStruct& cell);
    // FUNCTION: GAMEMD 0x56D460 (decl; reloc) -- one cell argument (RET 4).
    void FUN_0056D460(const CellStruct* cell);
    // FUNCTION: GAMEMD 0x56D5A0 (decl; reloc) -- one cell argument (RET 4).
    void FUN_0056D5A0(const CellStruct* cell);
    // FUNCTION: GAMEMD 0x56D6E0 (decl; reloc)
    void FUN_0056D6E0();
    // FUNCTION: GAMEMD 0x56DC20 (decl; reloc) -- the nearby-cell search: fifteen stack words (RET 0x3C), the first the hidden out pointer.
    CellStruct* FUN_0056DC20(CellStruct* out, const CellStruct& position,
                             int speedType, int a4, int movementZone, bool alt,
                             int spaceSizeX, int spaceSizeY, bool a9, bool a10,
                             bool a11, bool ignoreOccupied,
                             const CellStruct& closeTo, bool a14, bool buildable);
    // The same entry point with every cell passed by pointer.
    CellStruct* FUN_0056DC20(CellStruct* out, const CellStruct* position,
                             int speedType, int a4, int movementZone, bool alt,
                             int spaceSizeX, int spaceSizeY, bool a9, bool a10,
                             bool a11, bool ignoreOccupied,
                             const CellStruct* closeTo, bool a14, bool buildable);
    // The by-value form (YRpp's wrapper), expanded inline at the call site: its parameters become constant-initialised
    // locals and the result is read back through the returned pointer.
    CellStruct FUN_0056DC20(const CellStruct& position, int speedType, int a4,
                            int movementZone, bool alt, int spaceSizeX,
                            int spaceSizeY, bool a9, bool a10, bool a11,
                            bool ignoreOccupied, const CellStruct& closeTo,
                            bool a14, bool buildable)
    {
        CellStruct outBuffer;
        FUN_0056DC20(&outBuffer, position, speedType, a4, movementZone, alt,
                     spaceSizeX, spaceSizeY, a9, a10, a11, ignoreOccupied,
                     closeTo, a14, buildable);
        return outBuffer;
    }
    // FUNCTION: GAMEMD 0x568300 (decl; reloc) -- the same entry point taking the cell by reference.
    bool FUN_00568300(const CellStruct& cell);
    // FUNCTION: GAMEMD 0x568350 (decl; reloc) -- the same entry point taking the coordinate by pointer.
    bool FUN_00568350(const CoordStruct* coord);
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) -- the same entry point taking the cell by reference.
    CellClass* FUN_005657A0(const CellStruct& cell);
    // FUNCTION: GAMEMD 0x578080 (decl; reloc) -- the same entry point taking the coordinate by reference.
    int FUN_00578080(const CoordStruct& coord);
    // FUNCTION: GAMEMD 0x578390 (decl; reloc) -- whether a cell-space rectangle (four ints) is inside the usable area (RET 8).
    bool FUN_00578390(const Rect_4i* rect, bool checkLevel);
    bool FUN_00578390(const Rect_4i& rect, bool checkLevel);
    // FUNCTION: GAMEMD 0x578460 (decl; reloc) -- the same entry point with the second argument as bool / int, cell by pointer or reference.
    bool FUN_00578460(const CellStruct* cell, bool useLevel);
    bool FUN_00578460(const CellStruct* cell, int flag);
    bool FUN_00578460(const CellStruct& cell, bool useLevel);
    bool FUN_00578460(const CellStruct& cell, int flag);
    // FUNCTION: GAMEMD 0x5785F0 (decl; reloc) -- the same entry point taking the coordinate by pointer.
    bool FUN_005785F0(const CoordStruct* coord);
    // FUNCTION: GAMEMD 0x57B790 (decl; reloc) -- one cell pointer (RET 4); `this` is not read.
    void FUN_0057B790(CellStruct* cell);
    // FUNCTION: GAMEMD 0x577F30 (decl; reloc) -- one house argument (RET 4).
    void FUN_00577F30(HouseClass* house);
    // FUNCTION: GAMEMD 0x584550 (decl; reloc) -- one cell argument (RET 4).
    void FUN_00584550(const CellStruct* cell);
    // FUNCTION: GAMEMD 0x5840C0 (decl; reloc) -- zone-edge collection around a cell (RET 0x10). The fourth word is the mover:
    // the decompile calls a vtable slot on it; it is kept as the int the callers pass.
    bool FUN_005840C0(CellClass* cell, int zone, DynamicVectorClass<unsigned short>* zones, int arg);
    // FUNCTION: GAMEMD 0x586BF0 (decl; reloc)
    void FUN_00586BF0();
    // FUNCTION: GAMEMD 0x588570 (decl; reloc) / 0x588750 -- cell, house, and a third object pointer (RET 0xC); `this` is not read.
    void FUN_00588570(CellStruct* cell, HouseClass* house, void* type);
    void FUN_00588750(CellStruct* cell, HouseClass* house, void* type);
    // FUNCTION: GAMEMD 0x588990 (decl; reloc)
    void FUN_00588990();
    // FUNCTION: GAMEMD 0x5865F0 (decl; reloc) -- MapClass::RevealCheck (RET 0xC); `this` is not read.
    void FUN_005865F0(CellClass* cell, HouseClass* house, bool redraw);
    // FUNCTION: GAMEMD 0x5BDAA0 (decl; reloc)
    void FUN_005BDAA0();
    // FUNCTION: GAMEMD 0x5BDC80 (decl; reloc) -- MouseClass vtable slot 19 (RET 8).
    bool FUN_005BDC80(int cursor, bool flag);
    // FUNCTION: GAMEMD 0x5BDF50 (decl; reloc)
    void FUN_005BDF50();
    // FUNCTION: GAMEMD 0x653F70 (decl; reloc) -- one coordinate pointer (RET 4).
    void FUN_00653F70(CoordStruct* where);
    // FUNCTION: GAMEMD 0x655560 (decl; reloc) -- mark one cell as occupied by the object (RET 0xC).
    void FUN_00655560(ObjectClass* object, int x, int y);
    // FUNCTION: GAMEMD 0x655B20 (decl; reloc)
    void FUN_00655B20();
    // FUNCTION: GAMEMD 0x6551C0 (decl; reloc) -- the same entry point taking the cell by pointer.
    void FUN_006551C0(const CellStruct* cell);
    // FUNCTION: GAMEMD 0x6565A0 (decl; reloc) -- redraw at a cell (RET 4).
    void FUN_006565A0(CellStruct* cell);
    // FUNCTION: GAMEMD 0x692300 (decl; reloc) -- six out parameters (stack, RET 0x18).
    void FUN_00692300(const Point2D& screen, CellStruct* cell, CoordStruct* coord,
                      ObjectClass** object, bool* flagA, bool* flagB);
    // FUNCTION: GAMEMD 0x6A4FF0 (decl; reloc) -- RET 4 stub.
    void FUN_006A4FF0(bool cameoText);
    // FUNCTION: GAMEMD 0x6A60E0 (decl; reloc) -- one stack argument.
    void FUN_006A60E0(int arg);
    // FUNCTION: GAMEMD 0x6A6300 (decl; reloc) -- two stack arguments.
    void FUN_006A6300(int kind, int index);
    // FUNCTION: GAMEMD 0x6A7590 (decl; reloc) -- one stack argument.
    void FUN_006A7590(int index);
    // FUNCTION: GAMEMD 0x6AC5F0 (decl; reloc) -- two stack arguments.
    void FUN_006AC5F0(void* item, int value);
    // FUNCTION: GAMEMD 0x6D04F0 (decl; reloc) -- one stack argument.
    void FUN_006D04F0(int value);
    // FUNCTION: GAMEMD 0x6D0F00 (decl; reloc)
    void FUN_006D0F00();
    // FUNCTION: GAMEMD 0x6D1800 (decl; reloc) -- stdcall forwarder onto 0x6AC210 (one stack argument, RET 4).
    wchar_t* FUN_006D1800(unsigned int id);
};

// GLOBAL: GAMEMD 0x87F7E8 -- the map object.
extern Map_0087F7E8 DAT_0087F7E8;

#endif
