// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   The display chain as one class hierarchy, read from the user's retail gamemd.exe v1.001 via the local Ghidra CLI.
//   RTTI (class hierarchy descriptors) gives the chain
//     GScreenClass > MapClass > DisplayClass > RadarClass > PowerClass > SidebarClass > TabClass > ScrollClass
//     > MouseClass,
//   with TabClass's second base INoticeSink at +0x5518 (RTTI base offset 21784). Primary vtables (slot counts from the
//   RTTI vtable census): GScreenClass 0x7EA6FC (22), MapClass 0x7ED404 (30), DisplayClass 0x7E6114 (50), RadarClass
//   0x7F0344 (54), PowerClass 0x7EFF54 (54), SidebarClass 0x7F3058 (55), TabClass 0x7EDFB4 (55), ScrollClass
//   0x7F1094 (55), MouseClass 0x7E1964 (55); the INoticeSink tables are 0x7E1FBC (INoticeSink), 0x7EDFAC (TabClass),
//   0x7F108C (ScrollClass) and 0x7E195C (MouseClass), one slot each (0x6D1770 in the three derived tables).
//   Each class below declares exactly the slots its retail table changes (override or new slot); the slot numbers in
//   the comments are retail indices, the address is the function that retail table holds.
//   Member offsets come from the constructor stores: GScreenClass 0x4F4220, DisplayClass 0x4A8730 (stores
//   +0x1174..+0x11E0), RadarClass 0x652960 (first store +0x11E8), PowerClass 0x63F6B0 (+0x150C..+0x1540),
//   SidebarClass 0x6A4E60 (strips from +0x1544, +0x539C..+0x5515), TabClass 0x6CFE20 (INoticeSink vptr at +0x5518,
//   sub-object constructor 0x4A2350 on +0x551C, +0x552C..+0x5546), ScrollClass 0x692290 (+0x5548..+0x555A), and from
//   the members the module entries touch. MouseClass's size 0x556C is the byte count its Save writes (0x5BE715).
//   Names are kept only where the binary confirms the role (YRpp-cross-check); everything else is unknown_XX or FUN_ placeholders.
//
// Where a member or parameter type is a module-local view of a class outside this chain (a house, a cell, an INI
// reader), it is forward-declared here under the view's name and defined in the module header that dereferences it.
//
// StripClass origin (+0x1544, not +0x154C). The SidebarClass constructor 0x6A4E60 loads ESI = this+0x1544 and writes
// the strip's first members there ([ESI] dword, [ESI+4] byte, [ESI+8] the frame counter, [ESI+0x10..0x18]), builds the
// 75-entry cameo array at ESI+0x58 (vector constructor 0x4068F0, 0x34-byte entries, constructor 0x6AC7C0), steps
// ESI by 0xF94, and then calls the strip method 0x6A80A0 with ECX = this+0x1544. So the strip begins at +0x1544 and
// its cameos at +0x58. The MouseClass destructor 0x40D290 reads as if the strip began at +0x154C because it calls the
// empty out-of-line destructor 0x40D300 with ECX = strip+8: that is the destructor of the timer member at strip+8,
// not of a strip base, and the cameos it tears down at ESI+0x50 are the same bytes (strip+0x58).
#ifndef GG_MATCH_UI_INPUT_CONTROLS_UI_DISPLAY_CHAIN_H
#define GG_MATCH_UI_INPUT_CONTROLS_UI_DISPLAY_CHAIN_H

#include <stddef.h>
#include <objidl.h>   // IUnknown (VC98 SDK, LIBRARY)
#include "../../_rt/gg_static_assert.h"
#include "../../_layout/geometry2d.h"
#include "../../_layout/abstract_class.h"
#include "../../core/dynamic_vector_ctor_methods.h"
#include "../../core/vector_class_operations.h"
#include "../../core/pair_vector_ctor_family_methods.h"
#include "../../core/zone_connection_class.h"
#include "../../core/small_misc2_methods.h"
#include "../../_layout/elapsed_timer.h"

GG_STATIC_ASSERT(sizeof(DynamicVectorClass<Point2D>) == 0x18);

// ---- shared value types ------------------------------------------------------------------------------------------

// GLOBAL: GAMEMD 0xA8ED84 -- current frame read by the StripClass and cameo constructors.
extern int CurrentFrame_00A8ED84;

// A packed map cell (two 16-bit coordinates).
#include "../../_layout/cell.h"
#include "../../map/crate_class.h"
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

#include "../../_layout/components.h"

// The 16-byte interface id GScreenClass::QueryInterface compares (IID layout).
struct DisplayGuid { char Bytes[16]; };
GG_STATIC_ASSERT(sizeof(DisplayGuid) == 16);

// The "do not initialise" tag the load path passes to the placement constructor.
struct Obj_005BDF70 { };

struct IStream;

// Views defined by the module headers that dereference them.
class DisplayHouse;           // display_reveal.h  (HouseClass)
class HouseClass;
class ObjectClass;
class DisplayCell;            // display_reveal.h  (CellClass)
struct DisplayScCellObject;   // display_scenario.h (CellClass)
struct DisplayScIni;          // display_scenario.h (CCINIClass)
class DisplayCmdAbstract;     // display_command.h (AbstractClass-shaped target)
class DisplayCmdObject;       // display_command.h (ObjectClass)
class DisplayCmdPendType;     // display_command.h (the pending placement's type)
struct DisplayCmdVec3;        // display_command.h (CoordStruct)
struct MapSavedObject;        // mouse_mouse_class.h (an IPersistStream object on a cell)

// GadgetClass as the screen's button list sees it (kept as a local view until the module's gadget headers are
// consolidated). The sidebar's button views derive from it. Only the slots 0x4F4320..0x4F4450 dispatch through are typed;
// the others keep their slot position.
class DisplayGadget
{
public:
    virtual void vf_00();                              // 0x00
    virtual void vf_01();                              // 0x04
    virtual void vf_02();                              // 0x08
    virtual void vf_03();                              // 0x0C
    virtual void AppendTo(DisplayGadget* head);        // 0x10  attach after the list head
    virtual void vf_05();                              // 0x14
    virtual DisplayGadget* GetHead();                  // 0x18
    virtual void vf_07();                              // 0x1C
    virtual void vf_08();                              // 0x20
    virtual DisplayGadget* Unlink();                   // 0x24  returns the new head
    virtual int Input();                               // 0x28  returns the pressed key
    virtual void vf_11();                              // 0x2C
    virtual void vf_12();                              // 0x30
    virtual void vf_13();                              // 0x34
    virtual void vf_14();                              // 0x38
    virtual void vf_15();                              // 0x3C
    virtual void vf_16();                              // 0x40
    virtual void vf_17();                              // 0x44
    virtual void vf_18();                              // 0x48
    virtual void vf_19();                              // 0x4C
    virtual void vf_20();                              // 0x50
    virtual void vf_21();                              // 0x54
    virtual void vf_22();                              // 0x58
    virtual int IsActive();                            // 0x5C
};

// ---- MapClass containers -----------------------------------------------------------------------------------------

// The SaveItems vector element type is declared canonically in zone_connection_class.h.
struct SubzoneTrackingStruct
{
    DynamicVectorClass<SubzoneConnectionStruct> unknown_00; // +0x00
    unsigned short unknown_18;                              // +0x18
    unsigned char unknown_1A[2];                            // +0x1A
    int unknown_1C;                                         // +0x1C
    int unknown_20;                                         // +0x20

    // FUNCTION: GAMEMD 0x589BD0
    SubzoneTrackingStruct();
    // Member-wise copy that leaves the two bytes at +0x1A alone (inlined into VectorClass<T>::Slot6, 0x588E10).
    SubzoneTrackingStruct(const SubzoneTrackingStruct& o)
        : unknown_00(o.unknown_00), unknown_18(o.unknown_18), unknown_1C(o.unknown_1C), unknown_20(o.unknown_20) {}
    bool operator==(const SubzoneTrackingStruct& o) const
    {
        return unknown_18 == o.unknown_18 && unknown_1C == o.unknown_1C;
    }
    bool operator!=(const SubzoneTrackingStruct& o) const { return !(*this == o); }
    // FUNCTION: GAMEMD 0x58A500
    SubzoneTrackingStruct& operator=(const SubzoneTrackingStruct& o);
};
GG_STATIC_ASSERT(offsetof(SubzoneTrackingStruct, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(SubzoneTrackingStruct, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(SubzoneTrackingStruct, unknown_1A) == 0x1A);
GG_STATIC_ASSERT(offsetof(SubzoneTrackingStruct, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(SubzoneTrackingStruct, unknown_20) == 0x20);
GG_STATIC_ASSERT(sizeof(SubzoneTrackingStruct) == 0x24);

// Vector-shaped buckets (0x18 bytes, vptr first); both kinds are built by an out-of-line two-argument constructor
// and carry their growth increment at +0x14.
class MapBucketA
{
public:
    // FUNCTION: GAMEMD 0x5BEA30 (decl; reloc) - constructor (capacity, items), RET 8.
    MapBucketA(int capacity = 0, int items = 0);
    virtual ~MapBucketA();       // vector-deleting destructor reached through slot 0 with flag 3
    char unknown_04[0x14 - 4];   // +0x04
    int  Growth;                 // +0x14
};
GG_STATIC_ASSERT(offsetof(MapBucketA, Growth) == 0x14);
GG_STATIC_ASSERT(sizeof(MapBucketA) == 0x18);

class MapBucketBBase
{
public:
    // FUNCTION: GAMEMD 0x58B070 (decl; reloc) - constructor (capacity, items), RET 8.
    MapBucketBBase(int capacity, int items);
    virtual ~MapBucketBBase();
    char unknown_04[0x10 - 4];   // +0x04
    int  Count;                  // +0x10
    int  Growth;                 // +0x14
};

// The derived bucket sets its own vtable (0x7ED520), the count 0 and the increment 10 after the base constructor.
class MapBucketB : public MapBucketBBase
{
public:
    MapBucketB() : MapBucketBBase(0, 0)
    {
        Growth = 10;
        Count = 0;
    }
    virtual ~MapBucketB();
};
GG_STATIC_ASSERT(sizeof(MapBucketB) == 0x18);

// FUNCTION: GAMEMD 0x56CB80 (decl; reloc) - stored in the table header by the inline constructor below.
void __cdecl MapBucketCallback();

// A 0x10-byte table of 0x100 buckets (header: items, callback, count, increment), allocated inline by Load.
template <class Bucket>
struct MapBucketTable
{
    Bucket* Items;                 // +0x00
    void (__cdecl* Callback)();    // +0x04
    int     Count;                 // +0x08
    int     Increment_;            // +0x0C
    MapBucketTable()
    {
        Callback = MapBucketCallback;
        Count = 0x100;
        Increment_ = 0x14;
        Items = new Bucket[0x100];
        for (int i = 0; i < Count; i++)
            Items[i].Growth = 0x14;
    }
};

// A four-byte record of the word table (two bytes set by the inline constructor).
struct MapWordEntry
{
    unsigned char a;
    unsigned char b;
    unsigned char unknown_02[2];
    MapWordEntry() : a(7), b(0) {}
};
GG_STATIC_ASSERT(sizeof(MapWordEntry) == 4);


// ---- GScreenClass ------------------------------------------------------------------------------------------------

// IGameMap: the retail hierarchy descriptor of GScreenClass names a struct IGameMap with one base, IUnknown, between
// GScreenClass and IUnknown (RTTI ".?AUIGameMap@@"). It adds no members of its own.
struct __declspec(novtable) IGameMap : public IUnknown
{
};
GG_STATIC_ASSERT(sizeof(IGameMap) == 4);

// VTABLE: GAMEMD 0x7EA6FC (22 slots; COM-shaped: QueryInterface / AddRef / Release first)
class GScreenClass : public IGameMap
{
public:
    virtual HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);            // 0   0x4F4240
    virtual ULONG __stdcall AddRef();                                             // 1   0x40D230
    virtual ULONG __stdcall Release();                                            // 2   0x40D240
    virtual void vf_03();                                                         // 3   0x4C9150 (__purecall)
    // FUNCTION: GAMEMD 0x4F4C00 (scalar deleting destructor; ??_G)
    virtual ~GScreenClass() {}                                                    // 4   0x4F4C00
    virtual void vf_05();                                                         // 5   0x4F42A0
    virtual void vf_06(int unused);                                               // 6   0x4F42B0
    virtual void vf_07();                                                         // 7   0x4F42D0
    virtual void vf_08();                                                         // 8   0x4F42E0
    virtual void Input(int* key, int* x, int* y);                                 // 9   0x4F4320
    virtual void vf_10(int* key, Point2D* where);                                 // 10  0x4F4BB0
    virtual bool IsButtonListHead(DisplayGadget* gadget);                         // 11  0x4F43F0
    virtual bool AddButton(DisplayGadget* gadget);                                // 12  0x4F4410
    virtual bool vf_13(DisplayGadget* gadget);                             // 13  0x4F4450
    virtual void FlagToRedraw(int mode);                                          // 14  0x4F42F0 (redraw request)
    virtual void vf_15();                                                         // 15  0x4F4480
    virtual void vf_16(bool forced);                                              // 16  0x4AEBD0 (draw)
    virtual void vf_17();                                                         // 17  0x4F45B0
    virtual void vf_18(int cursor, bool flag);                                    // 18  0x4C9150 (__purecall)
    virtual bool vf_19(int cursor, bool flag);                                    // 19  0x4C9150 (__purecall)
    virtual void vf_20();                                                         // 20  0x4C9150 (__purecall)
    virtual void vf_21(bool flag);                                                // 21  0x4C9150 (__purecall)

    // FUNCTION: GAMEMD 0x4F4220
    GScreenClass();

    int unknown_04;   // +0x04
    int unknown_08;   // +0x08
    int RedrawFlag;   // +0x0C
};
GG_STATIC_ASSERT(offsetof(GScreenClass, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(GScreenClass, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(GScreenClass, RedrawFlag) == 0x0C);
GG_STATIC_ASSERT(sizeof(GScreenClass) == 0x10);

// ---- MapClass ----------------------------------------------------------------------------------------------------

// VTABLE: GAMEMD 0x7ED404 (30 slots)
class CellClass;
struct SubzoneConnectionStruct;
struct CoordStruct;
class DSurface;
class BSurface;
template<class Key, class Value> struct HashObject;
struct RadarTrackingStruct;
class TechnoClass;
// Address-scoped holder shape established by Radar constructor 0x652960.
struct RadarArrayHolder
{
    // Native element table 0x7F042C and constructor 0x658DE0 identify this array.
    DynamicVectorClass<HashObject<RadarTrackingStruct, TechnoClass*> >* items;
    void* unknown_04;          // +0x04
    int unknown_08;            // +0x08
    int unknown_0C;            // +0x0C
};
GG_STATIC_ASSERT(offsetof(RadarArrayHolder, items) == 0x00);
GG_STATIC_ASSERT(offsetof(RadarArrayHolder, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(RadarArrayHolder, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(RadarArrayHolder, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(sizeof(RadarArrayHolder) == 0x10);
struct Cell_00578540;           // map_class_usable_area_methods.cpp
struct WarheadType_00489180;    // map_class_total_damage_methods.cpp
struct Cell_0050DEF0;   // radar_class.h
struct RadarDiamond;    // Radar.cpp
class Pipe;
class MapClass : public GScreenClass
{
public:
    // FUNCTION: GAMEMD 0x565090 (decl; reloc) -- ordinary MapClass constructor, called by DisplayClass 0x4A8730.
    MapClass();
    // FUNCTION: GAMEMD 0x565190 (decl; reloc) -- no-init MapClass constructor, called by DisplayClass 0x6AC840.
    MapClass(const Obj_005BDF70& noInit);

    // FUNCTION: GAMEMD 0x5673A0 (declaration only; no body provider yet)
    // Native passes a coordinate pointer; reference source spelling is provisional.
    void FUN_005673A0(const CoordStruct& where, int sight, HouseClass* house, int a, int b, int c, int d, int e);
    // FUNCTION: GAMEMD 0x5678E0 (decl; reloc) -- reveal the map around a coordinate; the pointer is the coordinate.
    void FUN_005678E0(const CoordStruct& where, int sight, HouseClass* house, int a, int b, int c, int d, int e);
    // FUNCTION: GAMEMD 0x00565730 (decl; reloc)
    CellClass* FUN_00565730(const CoordStruct& coord);
    // FUNCTION: GAMEMD 0x5865E0 (decl; reloc), __thiscall, RET 4.
    bool IsLocationFogged(const CoordStruct* coord) const;
    // FUNCTION: GAMEMD 0x568350 (decl; reloc), CoordStruct by reference.
    bool FUN_00568350(const CoordStruct& coord);
    // FUNCTION: GAMEMD 0x5880A0 (decl; hidden CoordStruct result, RET 16).
    CoordStruct FUN_005880A0(const CoordStruct& from,
                             const CoordStruct& to, HouseClass* house);
public:
    virtual void vf_03();                    // 3   0x5656D0
    // FUNCTION: GAMEMD 0x5652C0 (body); scalar deleting wrapper 0x588BF0.
    virtual ~MapClass();                     // 4   0x588BF0 (??_G)
    virtual void vf_05();                    // 5   0x565800
    virtual void vf_07();                    // 7   0x5659F0

    virtual void vf_22();                    // 22  0x565AA0
    virtual void vf_23();                    // 23  0x565B00
    virtual void vf_24();                    // 24  0x565BC0
    virtual void vf_25();                    // 25  0x577920
    virtual bool vf_26();                    // 26  0x4AEBE0
    virtual void vf_27();                    // 27  0x56BBE0
    virtual void vf_28(RectangleStruct* rect, int a, int b, int c);   // 28  0x565C10
    virtual void vf_29(RectangleStruct* rect);   // 29  0x567230

    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) -- the cell at a coordinate. Two typed views of the one retail function
    // (by reference and by pointer, same ABI) until the module CellClass views are consolidated.
    DisplayCell* GetCellAt_005657A0(CellStruct const& cell);
    DisplayScCellObject* FUN_005657A0(const CellStruct* cell);
    // FUNCTION: GAMEMD 0x56D230 (decl; reloc) -- Queue0x64D427/64D51B,
    // coordinate pointer, MovementZone, bridge flag; RET12.
    int FUN_0056D230(const CellStruct& cell, int movementZone, bool bridge);
    // FUNCTION: GAMEMD 0x578460 (decl; reloc) -- Queue0x64D4E9,
    // coordinate pointer and boundary flag; RET8.
    bool FUN_00578460(const CellStruct& cell, bool checkLevel);
    // FUNCTION: GAMEMD 0x5657E0 (decl; reloc) -- RET 4.
    bool FUN_005657E0(const CellStruct& cell);
    // FUNCTION: GAMEMD 0x577F30 (decl; reloc) -- RET 4; takes a house (null at 0x5C9430).
    void FUN_00577F30(void* house);
    // FUNCTION: GAMEMD 0x578290 (decl; reloc) -- the next cell of the iteration, or null. Two typed views again (the
    // display_scenario.h and mouse_mouse_class.h CellClass views).
    CellClass* FUN_00578290();
    MapSavedObject* NextSavedObject_00578290();
    // FUNCTION: GAMEMD 0x578350 (decl; reloc) -- rewind the cell-object iteration.
    void FUN_00578350();
    // FUNCTION: GAMEMD 0x4AE450 -- reset every cell's light after a detail-level change, then request a redraw.
    void FUN_004AE450();

    // Methods defined by the matched map/ TUs (formerly per-TU partial views of this class).
    // FUNCTION: GAMEMD 0x588960 / 0x588990 -- clamp the capped count at +0x148.
    void FUN_00588960(int limit);
    int FUN_00588990();
    // FUNCTION: GAMEMD 0x565470 / 0x5654A0 / 0x5654E0 / 0x565520 / 0x565610 -- isometric projection helpers.
    Point2D FUN_00565470(const Point2D& in) const;
    Point2D FUN_005654A0(const Point2D& in) const;
    Point2D FUN_005654E0(const Point2D& in) const;
    Point2D FUN_00565520(const Point2D& in) const;
    CellStruct* FUN_00565580(CellStruct* out, const CellStruct* in) const;
    CellStruct* FUN_005655C0(CellStruct* out, const CellStruct* in) const;
    CellStruct* FUN_00565610(CellStruct* out, const CellStruct* in) const;
    CellStruct* FUN_00565660(CellStruct* out, const CellStruct* in) const;
    // FUNCTION: GAMEMD 0x56D3A0 -- the word lookup for a cell.
    unsigned int FUN_0056D3A0(const CellStruct* cell) const;
    // FUNCTION: GAMEMD 0x578460 (decl; reloc), const view / 0x5785F0 / 0x578540 -- usable-area tests.
    bool IsWithinUsableArea(const CellStruct& cell, bool checkLevel) const;
    bool IsWithinUsableArea(const CoordStruct& coords) const;
    bool IsWithinUsableArea(Cell_00578540* pCell, bool checkLevel) const;
    // FUNCTION: GAMEMD 0x578080 -- the floor height at a coordinate (second name for FUN_00578080).
    int GetZPos(CoordStruct* coords);
    // FUNCTION: GAMEMD 0x581090 -- frees the map's tables, then the veinhole and tiberium logic.
    void FUN_00581090();
    // FUNCTION: GAMEMD 0x5864A0 -- whether the cell under a coordinate (or its facing-3 neighbour on odd levels) has a positive +0x13C.
    bool FUN_005864A0(const CoordStruct* coords) const;
    // FUNCTION: GAMEMD 0x586AC0 -- pulls a cell back inside the local map rectangle.
    CellStruct* FUN_00586AC0(CellStruct* out, const CellStruct* cell, bool flag) const;
    // FUNCTION: GAMEMD 0x56E890 -- finds the house whose base covers a cell: its sector and its type's +0xB8 value.
    bool FUN_0056E890(const CellStruct* cell, int* houseTypeValue, int* sector) const;
    // FUNCTION: GAMEMD 0x56AE40 -- sums the bytes of the owned cells' tile, height and level fed through an LCW pipe.
    int FUN_0056AE40(Pipe* chain) const;
    // FUNCTION: GAMEMD 0x56BD40 -- crate bookkeeping, called by slot 27 for each expired crate.
    void FUN_0056BD40();
    // FUNCTION: GAMEMD 0x4F42D0 / 0x568300.
    void FUN_004F42D0();
    bool CoordinatesLegal(const CellStruct& cell) const;
    // FUNCTION: GAMEMD 0x565730 (decl; reloc) / 0x4ACA10 -- cell under a coordinate; infantry sub-location pick.
    CellClass* GetCellAt(const CoordStruct& coords);
    CoordStruct PickInfantrySublocation(const CoordStruct& coords, bool ignoreContents);
    // FUNCTION: GAMEMD 0x565730 -- the cell under a cell-space point.
    CellClass* GetTargetCell(Point2D& location);
    // FUNCTION: GAMEMD 0x586360 -- IsLocationShrouded.
    bool IsLocationShrouded(CoordStruct const& coords) const;
    // FUNCTION: GAMEMD 0x56BCD0 -- threat posed at a cell to a house.
    int GetThreatPosed(const CellStruct& cell, HouseClass* pHouse) const;
    // FUNCTION: GAMEMD 0x489180 -- the damage after armour and distance.
    static int GetTotalDamage(int damage, WarheadType_00489180* warhead, int armor, int distance);

    char  unknown_10[0x14 - 0x10];                   // +0x0010
    MapBucketTable<MapBucketA>* BucketsA;            // +0x0014
    void* Buffers[13];                               // +0x0018 13 tables of BufferShorts 16-bit entries
    int   BufferShorts;                              // +0x004C
    DynamicVectorClass<ZoneConnectionClass> SaveItems; // +0x0050
    MapWordEntry* Words;                             // +0x0068
    int   WordCount;                                 // +0x006C
    char* Records;                                   // +0x0070 ten bytes per word
    char  unknown_74[0x80 - 0x74];                   // +0x0074
    MapBucketTable<MapBucketB>* BucketsB[3];         // +0x0080
    DynamicVectorClass<SubzoneTrackingStruct> Rings[3]; // +0x008C stride 0x18
    DynamicVectorClass<Cell> ListA; // +0x00D4
    RectangleStruct MapRect;                         // +0x00EC [Map] Size (its address is the first argument of slot 28)
    RectangleStruct LocalRect;                       // +0x00FC [Map] LocalSize
    int   unknown_10C;                               // +0x010C cell iterator, see 0x578290
    int   unknown_110;                               // +0x0110
    int   unknown_114;                               // +0x0114
    CellClass** unknown_118;                         // +0x0118 cursor into the owned-cell table
    int   unknown_11C;                               // +0x011C
    int   unknown_120;                               // +0x0120
    char  unknown_124[0x134 - 0x124];                // +0x0124
    int   unknown_134;                               // +0x0134 cleared by slot 24 0x565BC0
    VectorClass<CellClass*> Owned; // +0x0138
    int unknown_148; // +0x0148
    int unknown_14C; // +0x014C
    int unknown_150; // +0x0150
    int unknown_154; // +0x0154
    CrateClass Crates[0x100]; // +0x0158
    char unknown_1158[4]; // +0x1158
    DynamicVectorClass<Cell> CellTags; // +0x115C
};
GG_STATIC_ASSERT(offsetof(MapClass, BucketsA) == 0x14);
GG_STATIC_ASSERT(offsetof(MapClass, Buffers) == 0x18);
GG_STATIC_ASSERT(offsetof(MapClass, BufferShorts) == 0x4C);
GG_STATIC_ASSERT(offsetof(MapClass, SaveItems) == 0x50);
GG_STATIC_ASSERT(offsetof(MapClass, Words) == 0x68);
GG_STATIC_ASSERT(offsetof(MapClass, WordCount) == 0x6C);
GG_STATIC_ASSERT(offsetof(MapClass, Records) == 0x70);
GG_STATIC_ASSERT(offsetof(MapClass, BucketsB) == 0x80);
GG_STATIC_ASSERT(offsetof(MapClass, Rings) == 0x8C);
GG_STATIC_ASSERT(offsetof(MapClass, ListA) == 0xD4);
GG_STATIC_ASSERT(offsetof(MapClass, MapRect) == 0xEC);
GG_STATIC_ASSERT(offsetof(MapClass, LocalRect) == 0xFC);
GG_STATIC_ASSERT(offsetof(MapClass, unknown_10C) == 0x10C);
GG_STATIC_ASSERT(offsetof(MapClass, unknown_110) == 0x110);
GG_STATIC_ASSERT(offsetof(MapClass, unknown_114) == 0x114);
GG_STATIC_ASSERT(offsetof(MapClass, unknown_118) == 0x118);
GG_STATIC_ASSERT(offsetof(MapClass, unknown_11C) == 0x11C);
GG_STATIC_ASSERT(offsetof(MapClass, unknown_120) == 0x120);
GG_STATIC_ASSERT(offsetof(MapClass, unknown_134) == 0x134);
GG_STATIC_ASSERT(offsetof(MapClass, Owned) == 0x138);
GG_STATIC_ASSERT(offsetof(MapClass, unknown_148) == 0x148);
GG_STATIC_ASSERT(offsetof(MapClass, unknown_14C) == 0x14C);
GG_STATIC_ASSERT(offsetof(MapClass, unknown_150) == 0x150);
GG_STATIC_ASSERT(offsetof(MapClass, unknown_154) == 0x154);
GG_STATIC_ASSERT(offsetof(MapClass, Crates) == 0x158);
GG_STATIC_ASSERT(offsetof(MapClass, Crates) + offsetof(CrateClass, Location) == 0x164);
GG_STATIC_ASSERT(sizeof(((MapClass*)0)->Crates) == 0x1000);
GG_STATIC_ASSERT(offsetof(MapClass, unknown_1158) == 0x1158);
GG_STATIC_ASSERT(offsetof(MapClass, CellTags) == 0x115C);
GG_STATIC_ASSERT(sizeof(VectorClass<CellClass*>) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<ZoneConnectionClass>) == 0x18);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<SubzoneTrackingStruct>) == 0x18);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<Cell>) == 0x18);
GG_STATIC_ASSERT(sizeof(MapClass) == 0x1174);

// ---- DisplayClass ------------------------------------------------------------------------------------------------

// VTABLE: GAMEMD 0x7E6114 (50 slots)
class DisplayClass : public MapClass
{
public:
    // FUNCTION: GAMEMD 0x4A8730 (decl; reloc) -- ordinary constructor; member offsets are established here.
    DisplayClass();
    // FUNCTION: GAMEMD 0x6AC840 -- tagged load constructor; forwards noInit to MapClass and clears SavedColor.
    DisplayClass(const Obj_005BDF70& noInit);

    // FUNCTION: GAMEMD 0x4A9720 / 0x4A9770 (decl; reloc).
    void Submit(ObjectClass* object);
    void Remove(ObjectClass* object);

    // FUNCTION: GAMEMD 0x4A94F0 / 0x4A95A0 (decl; reloc).
    CellStruct FoundationBoundsSize(CellStruct const* foundation) const;
    void MarkFoundation(CellStruct const* baseCell, bool mark);

    virtual void vf_05();                                // 5   0x4A8850
    virtual void vf_07();                                // 7   0x4A88C0
    virtual void vf_08();                                // 8   0x4A8930
    virtual void vf_10(int* key, Point2D* where);        // 10  0x4A9700

    virtual long vf_30(IStream* stream);                 // 30  0x4AE6F0 (load)
    virtual long vf_31(IStream* stream);                 // 31  0x4AE720 (save)
    virtual void vf_32(DisplayScIni* ini);               // 32  0x4ACE70 (read the scenario INI)
    virtual const wchar_t* vf_33(int id);                // 33  0x4AE4F0 (tooltip text)
    virtual void vf_34();                                // 34  0x4AE6B0
    virtual void vf_35();                                // 35  0x4AEAD0
    virtual bool vf_36(CellStruct* cell, DisplayHouse* house);                  // 36  0x4A9890
    virtual bool vf_37(CellStruct* cell, DisplayHouse* house, bool increase);   // 37  0x4A9CA0
    virtual bool vf_38(CellStruct* cell, DisplayHouse* house);                  // 38  0x4A9DD0
    virtual bool vf_39(CellStruct* cell, DisplayHouse* house);                  // 39  0x4AA050
    virtual int  vf_40();                                // 40  0x4C9150 (__purecall)
    virtual bool vf_41(int a, int* b, bool c);           // 41  0x4A9840
    virtual void vf_42(const RectangleStruct* rect);     // 42  0x4A8960 (set the view dimensions)
    virtual void vf_43(int a1);                          // 43  0x40D250: bare RET 4
    virtual void vf_44(const Point2D* where);            // 44  0x4AAD20
    virtual void vf_45(const Point2D* where);            // 45  0x4AC310
    virtual void vf_46(CellStruct* cell, int a2, DisplayCmdAbstract* target, int a4, bool a5);            // 46  0x4AAE90
    virtual void vf_47(const Point2D* where);            // 47  0x4AC380
    virtual void vf_48(int unused, CellStruct* cell, DisplayCmdObject* target, int action, bool a5);      // 48  0x4AB9B0
    virtual void vf_49(int unused);                      // 49  0x4AAD30

    // FUNCTION: GAMEMD 0x4A8BF0 (decl; reloc)
    void SetActiveFoundation_004A8BF0(void* foundation);
    // FUNCTION: GAMEMD 0x4A8EB0 (decl; reloc)
    bool FUN_004A8EB0(DisplayCmdPendType* type, int field, void* foundation, const CellStruct& at);
    // FUNCTION: GAMEMD 0x4AC660 (decl; reloc) -- set the sell mode; RET 4.
    void SetSellMode_004AC660(int mode);
    // FUNCTION: GAMEMD 0x4AC700 (decl; reloc)
    void SetWaypointMode_004AC700(int mode, int arg);
    // FUNCTION: GAMEMD 0x4AC820 (decl; reloc)
    void SetPowerMode_004AC820(int mode);
    // FUNCTION: GAMEMD 0x4AC8C0 (decl; reloc) -- set the repair mode; RET 4.
    void SetRepairMode_004AC8C0(int mode);
    // FUNCTION: GAMEMD 0x4AC960 (decl; reloc)
    void SetBeaconMode_004AC960(int mode);
    // FUNCTION: GAMEMD 0x4AE750 (decl; reloc)
    void FUN_004AE750(DisplayCmdObject* target, CellStruct cell, int action);
    // FUNCTION: GAMEMD 0x4A91B0 (decl; reloc) -- RET 8.
    void FUN_004A91B0(CellStruct* out, void* arg);
    // FUNCTION: GAMEMD 0x4A9650 (decl; reloc) -- RET 8; set or clear flag 4 (+0x12C) on every cell of the saved foundation.
    void FUN_004A9650(const CellStruct* cell, bool set);
    // FUNCTION: GAMEMD 0x4AA2B0 (decl; reloc) -- RET 4; the object after the one given.
    DisplayCmdObject* FUN_004AA2B0(DisplayCmdObject* from);
    // FUNCTION: GAMEMD 0x4AA380 (decl; reloc) -- RET 4; the object before the one given.
    DisplayCmdObject* FUN_004AA380(DisplayCmdObject* from);
    // FUNCTION: GAMEMD 0x4ACAC0 (decl; reloc) -- ECX only; walk the 512x512 cells and settle the lit ones.
    void FUN_004ACAC0();
    // FUNCTION: GAMEMD 0x4ACBC0 (decl; reloc) -- ECX only; re-derive the shroud of every cell that was lit.
    void FUN_004ACBC0();
    // FUNCTION: GAMEMD 0x4ACC50 (decl; reloc) -- RET 4; forget what is known of a cell and re-derive its neighbours.
    void FUN_004ACC50(const CellStruct* cell);
    // FUNCTION: GAMEMD 0x4ACDA0 (decl; reloc) -- RET 4; put a lit cell's neighbours back to the unlit state.
    void FUN_004ACDA0(const CellStruct* cell);
    // FUNCTION: GAMEMD 0x4ADEE0 (decl; reloc) -- RET 8; reveal around, or run the gap generator of, every techno.
    void FUN_004ADEE0(bool skipBuildings, int arg);
    // FUNCTION: GAMEMD 0x4ADFF0 (decl; reloc) -- RET 8; reveal around the techno objects of draw layer 2.
    void FUN_004ADFF0(bool skipBuildings, int arg);
    // FUNCTION: GAMEMD 0x4AE290 (decl; reloc)
    void FUN_004AE290();
    // FUNCTION: GAMEMD 0x4AEB10 (decl; reloc)
    int FUN_004AEB10();
    // FUNCTION: GAMEMD 0x4AEB30 (decl; reloc) -- RET 4.
    void FUN_004AEB30(DisplayCmdObject* object);

    CellStruct unknown_1174;              // +0x1174 (the constructor copies the default cell 0x8A03F8)
    CellStruct FoundationOffset;          // +0x1178
    void* CurrentFoundation;              // +0x117C
    bool CanPlace;                        // +0x1180
    bool unknown_1181;                    // +0x1181
    CellStruct SavedCell;                 // +0x1182
    CellStruct SavedOffset;               // +0x1186
    char unknown_118A[2];                 // +0x118A
    void* SavedFoundation;                // +0x118C
    DisplayCmdObject* SavedPending;       // +0x1190
    DisplayCmdPendType* SavedType;        // +0x1194
    int  SavedField;                      // +0x1198
    bool unknown_119C;                    // +0x119C
    char unknown_119D[3];                 // +0x119D
    void* unknown_11A0;                   // +0x11A0 (swizzled after a load)
    DisplayCmdObject* Pending;            // +0x11A4 (swizzled after a load)
    DisplayCmdPendType* unknown_11A8;     // +0x11A8 (swizzled after a load)
    int  unknown_11AC;                    // +0x11AC (-1 = none)
    bool RepairMode;                      // +0x11B0
    bool SellMode;                        // +0x11B1
    bool PowerMode;                       // +0x11B2
    bool WaypointMode;                    // +0x11B3
    bool BeaconMode;                      // +0x11B4
    char unknown_11B5[3];                 // +0x11B5
    int  unknown_11B8;                    // +0x11B8 (-1 = none)
    DisplayCmdVec3* WaypointCoord;        // +0x11BC (cleared at the end of a load)
    char unknown_11C0[0x11CC - 0x11C0];   // +0x11C0
    ColorStruct SavedColor;               // +0x11CC (the palette entry the highlight animation restores)
    bool unknown_11CF;                    // +0x11CF
    bool unknown_11D0;                    // +0x11D0
    char unknown_11D1[3];                 // +0x11D1
    Point2D DragStart;                    // +0x11D4
    Point2D DragCurrent;                  // +0x11DC
};
GG_STATIC_ASSERT(offsetof(DisplayClass, unknown_1174) == 0x1174);
GG_STATIC_ASSERT(offsetof(DisplayClass, FoundationOffset) == 0x1178);
GG_STATIC_ASSERT(offsetof(DisplayClass, CurrentFoundation) == 0x117C);
GG_STATIC_ASSERT(offsetof(DisplayClass, CanPlace) == 0x1180);
GG_STATIC_ASSERT(offsetof(DisplayClass, SavedCell) == 0x1182);
GG_STATIC_ASSERT(offsetof(DisplayClass, SavedOffset) == 0x1186);
GG_STATIC_ASSERT(offsetof(DisplayClass, SavedFoundation) == 0x118C);
GG_STATIC_ASSERT(offsetof(DisplayClass, SavedPending) == 0x1190);
GG_STATIC_ASSERT(offsetof(DisplayClass, SavedType) == 0x1194);
GG_STATIC_ASSERT(offsetof(DisplayClass, SavedField) == 0x1198);
GG_STATIC_ASSERT(offsetof(DisplayClass, unknown_119C) == 0x119C);
GG_STATIC_ASSERT(offsetof(DisplayClass, unknown_11A0) == 0x11A0);
GG_STATIC_ASSERT(offsetof(DisplayClass, Pending) == 0x11A4);
GG_STATIC_ASSERT(offsetof(DisplayClass, unknown_11A8) == 0x11A8);
GG_STATIC_ASSERT(offsetof(DisplayClass, unknown_11AC) == 0x11AC);
GG_STATIC_ASSERT(offsetof(DisplayClass, RepairMode) == 0x11B0);
GG_STATIC_ASSERT(offsetof(DisplayClass, SellMode) == 0x11B1);
GG_STATIC_ASSERT(offsetof(DisplayClass, PowerMode) == 0x11B2);
GG_STATIC_ASSERT(offsetof(DisplayClass, WaypointMode) == 0x11B3);
GG_STATIC_ASSERT(offsetof(DisplayClass, BeaconMode) == 0x11B4);
GG_STATIC_ASSERT(offsetof(DisplayClass, unknown_11B8) == 0x11B8);
GG_STATIC_ASSERT(offsetof(DisplayClass, WaypointCoord) == 0x11BC);
GG_STATIC_ASSERT(offsetof(DisplayClass, SavedColor) == 0x11CC);
GG_STATIC_ASSERT(offsetof(DisplayClass, unknown_11CF) == 0x11CF);
GG_STATIC_ASSERT(offsetof(DisplayClass, unknown_11D0) == 0x11D0);
GG_STATIC_ASSERT(offsetof(DisplayClass, DragStart) == 0x11D4);
GG_STATIC_ASSERT(offsetof(DisplayClass, DragCurrent) == 0x11DC);
GG_STATIC_ASSERT(sizeof(DisplayClass) == 0x11E4);

// ---- RadarClass --------------------------------------------------------------------------------------------------

// VTABLE: GAMEMD 0x7F0344 (54 slots)
class RadarClass : public DisplayClass
{
public:
    // RTTI .?AVRTacticalClass@RadarClass@@ (type 0x839298, vtable 0x7F02BC): the radar's static tactical gadget,
    // defined in match/ui/radar_button_statics.cpp.
    class RTacticalClass;
    // FUNCTION: GAMEMD 0x652960 (decl; reloc) -- ordinary constructor.
    RadarClass();
    // FUNCTION: GAMEMD 0x6A4F20 (decl; partial) -- tagged load constructor, RET 4.
    RadarClass(const Obj_005BDF70& noInit)
        : DisplayClass(noInit), unknown_1224(0, 0), unknown_125C(0, 0), unknown_1500(0)
    {
        unknown_14C0.FUN_00405BE0();
    }
    // FUNCTION: GAMEMD 0x652C00 (decl; reloc) -- the RadarClass destructor body (called by every derived ??_G).
    virtual ~RadarClass();                               // 4   0x6587A0 (??_G)
    virtual void vf_05();                                // 5   0x652CF0
    virtual void vf_07();                                // 7   0x652DE0
    virtual void vf_08();                                // 8   0x653010
    virtual void vf_10(int* key, Point2D* where);        // 10  0x653850
    virtual void vf_16(bool forced);                     // 16  0x653100
    virtual void vf_28(RectangleStruct* rect, int a, int b, int c);   // 28  0x653F50
    virtual void vf_29(RectangleStruct* rect);           // 29  0x654490 (forwards the rectangle to 0x567230)
    virtual long vf_30(IStream* stream);                 // 30  0x6568A0
    virtual long vf_31(IStream* stream);                 // 31  0x656AC0
    virtual const wchar_t* vf_33(int id);                // 33  0x658770
    virtual void vf_34();                                // 34  0x654320
    virtual bool vf_36(CellStruct* cell, DisplayHouse* house);                  // 36  0x653810
    virtual bool vf_37(CellStruct* cell, DisplayHouse* house, bool increase);   // 37  0x653830

    virtual void vf_50();                                // 50  0x652D90 (free the art)
    virtual void vf_51();                                // 51  0x653760
    virtual void vf_52(const CoordStruct* where);        // 52  0x653F70
    virtual void vf_53();                                // 53  0x652E90 (load the art)

    // FUNCTION: GAMEMD 0x654650 (decl; reloc) -- helper uses ECX=this, RET.
    void FUN_00654650();
    // FUNCTION: GAMEMD 0x6547C0 (decl; reloc) -- aggregate result, two rectangle pointers, bool.
    RectangleStruct FUN_006547C0(const RectangleStruct* source, RectangleStruct* output, bool flag);
    // FUNCTION: GAMEMD 0x6558D0
    void FUN_006558D0();
    // FUNCTION: GAMEMD 0x655990
    void FUN_00655990();
    // FUNCTION: GAMEMD 0x655B20
    void FUN_00655B20();
    // FUNCTION: GAMEMD 0x6563B0 (decl; reloc) -- helper uses ECX=this, RET.
    void FUN_006563B0();

    // FUNCTION: GAMEMD 0x656EC0 (decl; reloc)
    void FUN_00656EC0();
    // FUNCTION: GAMEMD 0x655A90
    void FUN_00655A90();
    // FUNCTION: GAMEMD 0x653FA0 (decl; reloc)
    void FUN_00653FA0();
    // FUNCTION: GAMEMD 0x6579E0 (decl; reloc)
    void FUN_006579E0();
    // FUNCTION: GAMEMD 0x656CB0 (decl; reloc)
    void FUN_00656CB0(int, int);
    // FUNCTION: GAMEMD 0x6578F0 (decl; reloc)
    void FUN_006578F0();

    // FUNCTION: GAMEMD 0x652E50 (decl; reloc) -- RET 4.
    void FUN_00652E50(bool on);
    // FUNCTION: GAMEMD 0x655050 -- cell to radar-space record {x, y, mode, 1}; RET 8.
    struct RadarDiamond FUN_00655050(const Cell_0050DEF0& cell);
    // FUNCTION: GAMEMD 0x655150 -- radar-space point to cell; hidden result, RET 8.
    Cell_0050DEF0 FUN_00655150(const Point2D* point);
    // FUNCTION: GAMEMD 0x6550C0 -- map cell to radar screen position; RET 4.
    struct RadarDiamond FUN_006550C0(const Cell_0050DEF0* cell);
    // FUNCTION: GAMEMD 0x6551C0 -- queue a cell for redraw once; RET 4.
    void FUN_006551C0(const Cell* cell);
    // FUNCTION: GAMEMD 0x6557F0 -- map point to radar pixel position, optionally clamped; RET 0xC.
    Point2D* FUN_006557F0(Point2D* out, const Point2D* point, bool clamp);
    // FUNCTION: GAMEMD 0x656BE0 (decl; reloc) -- RET 8.
    void FUN_00656BE0(bool on, int flag);
    // FUNCTION: GAMEMD 0x656DF0 -- switch the tactical map on or off; RET 4.
    void FUN_00656DF0(bool on);
    // FUNCTION: GAMEMD 0x656E90 -- latch the forced flag; RET 4.
    void FUN_00656E90(bool force);

    // Retail constructor 0x6A4F20: vector members at +0x1224/+0x125C/+0x1278,
    // followed by the timer at +0x1500. Other bytes remain unclassified.
    int unknown_11E4;
    int unknown_11E8;
    int unknown_11EC;
    int unknown_11F0;
    int unknown_11F4;
    int unknown_11F8;
    int unknown_11FC;
    int unknown_1200;
    int unknown_1204;
    int unknown_1208;
    int unknown_120C;
    int unknown_1210;
    int unknown_1214;
    int unknown_1218;
    DSurface* unknown_121C;                         // +0x121C RTTI .?AVDSurface@@, primary base at 0
    BSurface* unknown_1220;                         // +0x1220 RTTI .?AVBSurface@@, primary base at 0
    DynamicVectorClass<Cell> unknown_1224;
    void* unknown_123C;                             // +0x123C operator-delete allocation
    int unknown_1240;
    int unknown_1244;
    int unknown_1248;
    int unknown_124C;
    int unknown_1250;
    int unknown_1254;
    RadarArrayHolder* unknown_1258;                 // +0x1258 holder for the 256-vector allocation
    DynamicVectorClass<Point2D> unknown_125C;
    void* unknown_1274;                             // +0x1274 operator-delete allocation
    DynamicVectorClass<Point2D> unknown_1278[0x16];
    int unknown_1488;
    int unknown_148C;
    int unknown_1490;                         // +0x1490 [Radar] SetVisibleRect state
    int unknown_1494;                         // +0x1494 [Radar] SetVisibleRect state
    int unknown_1498;                         // +0x1498 [Radar] tracking sentinel
    RectangleStruct RadarBounds;             // +0x149C [Radar] visible-cell bounds
    int unknown_14AC;
    int unknown_14B0;
    int unknown_14B4;
    int unknown_14B8;
    char unknown_14BC;
    unsigned char unknown_14BD;
    char unknown_14BE[2];
    AudioController unknown_14C0;   // +0x14C0 (0x14; its Unused word is +0x14D0)
    int unknown_14D4;
    unsigned char unknown_14D8;
    unsigned char unknown_14D9;
    unsigned char unknown_14DA;
    char unknown_14DB;
    int unknown_14DC;
    int unknown_14E0;
    int unknown_14E4;
    int unknown_14E8;
    char unknown_14EC[0x14FC - 0x14EC];
    int unknown_14FC;
    ScenarioElapsedTimer unknown_1500;
};
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_11E4) == 0x11E4);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_11E8) == 0x11E8);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_11EC) == 0x11EC);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_11F0) == 0x11F0);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_11F4) == 0x11F4);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_11F8) == 0x11F8);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_11FC) == 0x11FC);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1200) == 0x1200);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1204) == 0x1204);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1208) == 0x1208);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_120C) == 0x120C);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1210) == 0x1210);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1214) == 0x1214);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1218) == 0x1218);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_121C) == 0x121C);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1220) == 0x1220);
GG_STATIC_ASSERT(sizeof(DSurface*) == 4);
GG_STATIC_ASSERT(sizeof(BSurface*) == 4);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1224) == 0x1224);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_123C) == 0x123C);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1240) == 0x1240);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1244) == 0x1244);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1248) == 0x1248);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_124C) == 0x124C);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1250) == 0x1250);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1254) == 0x1254);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1258) == 0x1258);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_125C) == 0x125C);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1274) == 0x1274);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1278) == 0x1278);
GG_STATIC_ASSERT(sizeof(((RadarClass*)0)->unknown_1278) / sizeof(DynamicVectorClass<Point2D>) == 0x16);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_14C0) == 0x14C0);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1490) == 0x1490);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1488) == 0x1488);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_148C) == 0x148C);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1494) == 0x1494);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1498) == 0x1498);
GG_STATIC_ASSERT(offsetof(RadarClass, RadarBounds) == 0x149C);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_14AC) == 0x14AC);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_14B0) == 0x14B0);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_14B4) == 0x14B4);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_14B8) == 0x14B8);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_14BC) == 0x14BC);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_14BD) == 0x14BD);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_14D4) == 0x14D4);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_14D8) == 0x14D8);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_14D9) == 0x14D9);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_14DA) == 0x14DA);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_14DB) == 0x14DB);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_14DC) == 0x14DC);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_14E0) == 0x14E0);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_14E4) == 0x14E4);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_14E8) == 0x14E8);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_14EC) == 0x14EC);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_14FC) == 0x14FC);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1500) == 0x1500);
GG_STATIC_ASSERT(sizeof(RadarClass) == 0x150C);

// ---- PowerClass --------------------------------------------------------------------------------------------------

// VTABLE: GAMEMD 0x7EFF54 (54 slots). The destructor is implicit (0x6404B0 is its ??_G).
class PowerClass : public RadarClass
{
public:
    // FUNCTION: GAMEMD 0x63F6B0 (decl; reloc) -- ordinary constructor.
    PowerClass();
    // FUNCTION: GAMEMD 0x6A4F20 (decl; partial) -- tagged load constructor, RET 4.
    PowerClass(const Obj_005BDF70& noInit)
        : RadarClass(noInit), unknown_1510(AbstractNoInit()), unknown_1520(0)
    {
    }
    virtual void vf_05();                                // 5   0x63F7B0
    virtual void vf_07();                                // 7   0x63F730
    virtual void vf_10(int* key, Point2D* where);        // 10  0x63FEA0
    virtual void vf_16(bool forced);                     // 16  0x63FB20
    virtual const wchar_t* vf_33(int id);                // 33  0x640450
    virtual void vf_34();                                // 34  0x6403A0
    virtual void vf_50();                                // 50  0x63F7E0
    virtual void vf_53();                                // 53  0x63F7C0

    // FUNCTION: GAMEMD 0x63F810 -- restart the +0x1510 timer at 3 and set +0x151C to 10.
    void FUN_0063F810();
    // FUNCTION: GAMEMD 0x63F850 (decl; reloc)
    int FUN_0063F850();
    // FUNCTION: GAMEMD 0x63F8F0 -- scaled share of the three bar counters.
    int FUN_0063F8F0();
    // FUNCTION: GAMEMD 0x63F960 (decl; reloc) -- three out limits, RET 12.
    void FUN_0063F960(int* limit152C, int* limit1530, int* limit1534);
    // FUNCTION: GAMEMD 0x63FDC0 -- shrink the first counter that exceeds its limit.
    void FUN_0063FDC0();
    // FUNCTION: GAMEMD 0x63FE30 -- grow the first counter below its limit.
    void FUN_0063FE30();

    // +0x150C..+0x1543: stores of the constructor 0x63F6B0.
    bool unknown_150C;                  // +0x150C ctor 0
    char unknown_150D[3];
    ScenarioElapsedTimer unknown_1510;  // +0x1510
    int unknown_151C;                   // +0x151C ctor 0
    ScenarioElapsedTimer unknown_1520;
    int unknown_152C;                   // +0x152C ctor 0
    int unknown_1530;                   // +0x1530 ctor 0
    int unknown_1534;                   // +0x1534 ctor 0
    bool unknown_1538;                  // +0x1538 ctor 0
    char unknown_1539[3];
    int unknown_153C;                   // +0x153C ctor -1
    int unknown_1540;                   // +0x1540 ctor -1
};
// SidebarClass's constructor writes its first member (the first strip) at +0x1544.
GG_STATIC_ASSERT(offsetof(PowerClass, unknown_150C) == 0x150C);
GG_STATIC_ASSERT(offsetof(PowerClass, unknown_1510) == 0x1510);
GG_STATIC_ASSERT(offsetof(PowerClass, unknown_151C) == 0x151C);
GG_STATIC_ASSERT(offsetof(PowerClass, unknown_1520) == 0x1520);
GG_STATIC_ASSERT(offsetof(PowerClass, unknown_152C) == 0x152C);
GG_STATIC_ASSERT(offsetof(PowerClass, unknown_1530) == 0x1530);
GG_STATIC_ASSERT(offsetof(PowerClass, unknown_1534) == 0x1534);
GG_STATIC_ASSERT(offsetof(PowerClass, unknown_1538) == 0x1538);
GG_STATIC_ASSERT(offsetof(PowerClass, unknown_153C) == 0x153C);
GG_STATIC_ASSERT(offsetof(PowerClass, unknown_1540) == 0x1540);
GG_STATIC_ASSERT(sizeof(PowerClass) == 0x1544);

// ---- SidebarClass ------------------------------------------------------------------------------------------------

union SidebarCameoUnknown04
{
    int Word;
    unsigned char Bytes[4];
};
GG_STATIC_ASSERT(sizeof(SidebarCameoUnknown04) == 4);

struct SidebarCameoUnknown18Bytes
{
    unsigned char Low;
    char unknown_19[3];
};
union SidebarCameoUnknown18
{
    int Word;
    SidebarCameoUnknown18Bytes Bytes;
};
GG_STATIC_ASSERT(sizeof(SidebarCameoUnknown18) == 4);

// One of the 75 per-strip cameo entries (0x34 bytes). Its destructor is the empty function 0x40D260 (a lone RET);
// retail passes its address to the vector-destructor helper (0x40AFD0).
struct SidebarCameo
{
    // FUNCTION: GAMEMD 0x6AC7C0 (decl; partial) -- array element initializer, RET 4.
    SidebarCameo();
    int   unknown_00;                     // +0x00 (cleared by StripClass initializer)
    SidebarCameoUnknown04 unknown_04;      // +0x04 (initializer writes byte 0; strip reset clears the four bytes; lookups compare it as an int)
    int   unknown_08;                     // +0x08
    void* Pointer;                        // +0x0C (registered with the swizzle manager after a load)
    int   unknown_10;                     // +0x10
    int   unknown_14;                     // +0x14
    SidebarCameoUnknown18 unknown_18;     // +0x18 (word store by 0x6AC870; low-byte store by 0x6A80A0)
    int   unknown_1C;                     // +0x1C
    int   unknown_20;                     // +0x20
    int   unknown_24;                     // +0x24
    int   unknown_28;                     // +0x28
    int   unknown_2C;                     // +0x2C
    int   unknown_30;                     // +0x30
    // FUNCTION: GAMEMD 0x40D260 -- empty destructor.
    ~SidebarCameo() {}
};
GG_STATIC_ASSERT(offsetof(SidebarCameo, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(SidebarCameo, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(SidebarCameo, unknown_08) == 0x08);
GG_STATIC_ASSERT(offsetof(SidebarCameo, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(SidebarCameo, Pointer) == 0x0C);
GG_STATIC_ASSERT(offsetof(SidebarCameo, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(SidebarCameo, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(SidebarCameoUnknown18Bytes, Low) == 0x00);
GG_STATIC_ASSERT(offsetof(SidebarCameo, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(SidebarCameo, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(SidebarCameo, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(SidebarCameo, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(SidebarCameo, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(SidebarCameo, unknown_30) == 0x30);
GG_STATIC_ASSERT(sizeof(SidebarCameo) == 0x34);

// The timer at strip +0x08 (start frame at +0, the countdown at +8; 0x6A4E60 stores the current frame and zero).
// Retail's MouseClass destructor calls an empty out-of-line destructor (0x40D300) on it; the SidebarClass, TabClass
// and ScrollClass destructors do not (it was inlined away in their units). One type cannot carry both, so it is
// modelled with the implicit destructor that the three matched destructors need.
struct StripTimer
{
    StripTimer() {}
    StripTimer(int startFrame, int timeLeft)
        : StartFrame(startFrame), TimeLeft(timeLeft) {}
    int StartFrame;                       // +0x00
    int unknown_04;                       // +0x04
    int TimeLeft;                         // +0x08
};
GG_STATIC_ASSERT(sizeof(StripTimer) == 0x0C);
GG_STATIC_ASSERT(offsetof(StripTimer, StartFrame) == 0x00);
GG_STATIC_ASSERT(offsetof(StripTimer, TimeLeft) == 0x08);

// StripClass: one build column. sizeof 0xF94 (stride of the strip array); origin +0x1544, see the file header.
struct StripClass
{
    StripClass()
        : unknown_00(0), unknown_04(false), Timer(CurrentFrame_00A8ED84, 0),
          unknown_14(0), unknown_18(1)
    {
    }

    int  unknown_00;                      // +0x0000 (zeroed by the constructor)
    bool unknown_04;                      // +0x0004 (zeroed by the constructor)
    char unknown_05[3];                   // +0x0005
    StripTimer Timer;                     // +0x0008
    int  unknown_14;                      // +0x0014
    int  unknown_18;                      // +0x0018 (set to 1 by the constructor)
    unsigned char At_1C;                  // +0x001C
    char unknown_1D[3];                   // +0x001D
    int  At_20;                           // +0x0020
    int  At_24;                           // +0x0024
    RectangleStruct Rect;                 // +0x0028
    int  RowBase;                         // +0x0038
    unsigned char At_3C;                  // +0x003C (written by 0x6A5ED0 / 0x6A60E0)
    unsigned char unknown_3D;             // +0x003D
    unsigned char unknown_3E;             // +0x003E
    unsigned char unknown_3F;             // +0x003F
    int  unknown_40;                      // +0x0040
    int  TopRowIndex;                     // +0x0044
    int  At_48;                           // +0x0048
    int  unknown_4C;                      // +0x004C
    int  unknown_50;                      // +0x0050
    int  CameoCount;                      // +0x0054
    SidebarCameo Cameos[75];              // +0x0058

    // FUNCTION: GAMEMD 0x6A80A0 (decl; reloc) -- strip initializer; returns this, RET 4.
    StripClass* FUN_006A80A0(void* unknown_00);
    // FUNCTION: GAMEMD 0x6A81B0 (decl; reloc) -- strip reset.
    void FUN_006A81B0();
    // FUNCTION: GAMEMD 0x6A8220 (decl; reloc) -- strip init(index); RET 4.
    void FUN_006A8220(int index);
    // FUNCTION: GAMEMD 0x6A8B30 (decl; reloc) -- strip input (key, point); RET 8.
    bool FUN_006A8B30(int* key, Point2D* point);
    // FUNCTION: GAMEMD 0x6A92E0 (decl; reloc) -- text of the cameo at a row; RET 4.
    wchar_t* FUN_006A92E0(int row);
    // FUNCTION: GAMEMD 0x6A9540 (decl; reloc) -- draw the strip; RET 4.
    void FUN_006A9540(bool full);
    // FUNCTION: GAMEMD 0x6ABAC0 (decl; reloc)
    bool FUN_006ABAC0();
    // FUNCTION: GAMEMD 0x6ABA60
    bool FUN_006ABA60(void* value, int type, int id);
    // FUNCTION: GAMEMD 0x6AA600 (decl; reloc)
    bool FUN_006AA600();
    // FUNCTION: GAMEMD 0x6A87F0
    bool FUN_006A87F0(int type, int id);
    // FUNCTION: GAMEMD 0x6A8710 (decl; reloc)
    void FUN_006A8710(int type, int id);
};
GG_STATIC_ASSERT(offsetof(StripClass, Timer) == 0x08);
GG_STATIC_ASSERT(offsetof(StripClass, unknown_00) == 0x00);
GG_STATIC_ASSERT(offsetof(StripClass, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(StripClass, unknown_14) == 0x14);
GG_STATIC_ASSERT(offsetof(StripClass, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(StripClass, At_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(StripClass, At_20) == 0x20);
GG_STATIC_ASSERT(offsetof(StripClass, At_24) == 0x24);
GG_STATIC_ASSERT(offsetof(StripClass, Rect) == 0x28);
GG_STATIC_ASSERT(offsetof(StripClass, RowBase) == 0x38);
GG_STATIC_ASSERT(offsetof(StripClass, At_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(StripClass, unknown_3D) == 0x3D);
GG_STATIC_ASSERT(offsetof(StripClass, unknown_3E) == 0x3E);
GG_STATIC_ASSERT(offsetof(StripClass, unknown_3F) == 0x3F);
GG_STATIC_ASSERT(offsetof(StripClass, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(StripClass, TopRowIndex) == 0x44);
GG_STATIC_ASSERT(offsetof(StripClass, At_48) == 0x48);
GG_STATIC_ASSERT(offsetof(StripClass, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(StripClass, unknown_50) == 0x50);
GG_STATIC_ASSERT(offsetof(StripClass, CameoCount) == 0x54);
GG_STATIC_ASSERT(offsetof(StripClass, Cameos) == 0x58);
GG_STATIC_ASSERT(sizeof(StripClass) == 0xF94);

struct SidebarHouse;   // sidebar_class_layout.h (HouseClass)

// VTABLE: GAMEMD 0x7F3058 (55 slots). The destructor is implicit: retail's ??_G (0x6AC7F0) tears the strip array
// down inline and calls the RadarClass destructor body.
class SidebarClass : public PowerClass
{
public:
    SidebarClass();
    // FUNCTION: GAMEMD 0x6A4F20 (decl; partial) -- tagged load constructor, RET 4.
    SidebarClass(const Obj_005BDF70& noInit);

    virtual void vf_05();                                // 5   0x6A5000 (one-time init)
    virtual void vf_07();                                // 7   0x6A5030
    virtual void vf_08();                                // 8   0x6A5310 (init IO)
    virtual void vf_10(int* key, Point2D* where);        // 10  0x6A7780 (AI)
    virtual void vf_16(bool forced);                     // 16  0x6A6C30 (draw)
    virtual long vf_30(IStream* stream);                 // 30  0x6AC5D0
    virtual long vf_31(IStream* stream);                 // 31  0x6AC5E0
    virtual const wchar_t* vf_33(int id);                // 33  0x6AC210 (tooltip text)
    virtual void vf_34();                                // 34  0x6ABD30 (reposition)
    virtual void vf_50();                                // 50  0x6A5BF0 (free the art)
    virtual void vf_53();                                // 53  0x6A5840 (load the art)
    virtual bool vf_54(int control);                     // 54  0x6A7D70 (activate) -- new slot

    // FUNCTION: GAMEMD 0x6A5090 (decl; reloc)
    void FUN_006A5090();
    // FUNCTION: GAMEMD 0x6A5130 (decl; reloc) -- RET 4.
    void FUN_006A5130(int arg);
    // FUNCTION: GAMEMD 0x6A5ED0 (decl; partial).
    void FUN_006A5ED0();
    // FUNCTION: GAMEMD 0x6A60E0 (decl; partial) -- RET 4.
    void FUN_006A60E0(int tab);
    // FUNCTION: GAMEMD 0x6A6220 (decl) -- set (1), clear (anything else) or flip (-1) the byte at +0x5515; RET 4.
    unsigned char FUN_006A6220(int mode);
    // FUNCTION: GAMEMD 0x6A6290 (decl) -- the same body on the byte at +0x5514; RET 4.
    unsigned char FUN_006A6290(int mode);
    // FUNCTION: GAMEMD 0x6A6610 (decl; reloc) -- rebuild the strip contents.
    void FUN_006A6610();
    // FUNCTION: GAMEMD 0x6A70E0 (decl; reloc) -- RET 4.
    void FUN_006A70E0(bool flag);
    // FUNCTION: GAMEMD 0x6A6A00 (decl; reloc) -- RET 8.
    bool Scroll(bool up, int amount);
    // FUNCTION: GAMEMD 0x6A60A0 (decl; reloc).
    void RepaintSidebar(int tab);
    // FUNCTION: GAMEMD 0x6ABC60 / 0x6ABCD0 (decl; reloc; static __fastcall).
    static int FUN_006ABC60(int abs, int idxType, int unused);
    static int GetObjectTabIdx(int abs, int buildCat, int isNaval);
    // FUNCTION: GAMEMD 0x6A7590 (decl; reloc) -- RET 4.
    void SetTab(int tab);
    // FUNCTION: GAMEMD 0x6A7D20
    void FUN_006A7D20();
    // FUNCTION: GAMEMD 0x6A67A0
    void FUN_006A67A0(int tab);

    StripClass Strips[4];                 // +0x1544
    int unknown_5394;                     // +0x5394
    int unknown_5398;                     // +0x5398
    int unknown_539C;                        // +0x539C
    int At_53A0;                          // +0x53A0
    bool unknown_53A4;                    // +0x53A4
    bool At_53A5;                         // +0x53A5
    bool At_53A6;                         // +0x53A6
    bool At_53A7;                         // +0x53A7
    char unknown_53A8[0x53AC - 0x53A8];   // +0x53A8
    SidebarHouse* Houses[8];              // +0x53AC
    int Totals[8];                        // +0x53CC
    int Values[8];                        // +0x53EC
    int At_540C[8];                       // +0x540C
    void* Colors[8];                      // +0x542C
    int At_544C[8];                       // +0x544C
    int At_546C[8];                       // +0x546C
    int At_548C[8];                       // +0x548C
    int At_54AC[8];                       // +0x54AC
    int At_54CC[8];                       // +0x54CC
    int At_54EC[8];                       // +0x54EC
    unsigned char At_550C;                // +0x550C
    char unknown_550D[3];                 // +0x550D
    int Count;                            // +0x5510
    unsigned char At_5514;                // +0x5514
    unsigned char At_5515;                // +0x5515
    char unknown_5516[2];                 // +0x5516
};
GG_STATIC_ASSERT(offsetof(SidebarClass, Strips) == 0x1544);
GG_STATIC_ASSERT(offsetof(SidebarClass, unknown_539C) == 0x539C);
GG_STATIC_ASSERT(offsetof(SidebarClass, At_53A0) == 0x53A0);
GG_STATIC_ASSERT(offsetof(SidebarClass, unknown_53A4) == 0x53A4);
GG_STATIC_ASSERT(offsetof(SidebarClass, At_53A5) == 0x53A5);
GG_STATIC_ASSERT(offsetof(SidebarClass, At_53A6) == 0x53A6);
GG_STATIC_ASSERT(offsetof(SidebarClass, unknown_53A8) == 0x53A8);
GG_STATIC_ASSERT(offsetof(SidebarClass, Houses) == 0x53AC);
GG_STATIC_ASSERT(offsetof(SidebarClass, Totals) == 0x53CC);
GG_STATIC_ASSERT(offsetof(SidebarClass, Values) == 0x53EC);
GG_STATIC_ASSERT(offsetof(SidebarClass, At_540C) == 0x540C);
GG_STATIC_ASSERT(offsetof(SidebarClass, Colors) == 0x542C);
GG_STATIC_ASSERT(offsetof(SidebarClass, At_544C) == 0x544C);
GG_STATIC_ASSERT(offsetof(SidebarClass, At_546C) == 0x546C);
GG_STATIC_ASSERT(offsetof(SidebarClass, At_548C) == 0x548C);
GG_STATIC_ASSERT(offsetof(SidebarClass, At_54AC) == 0x54AC);
GG_STATIC_ASSERT(offsetof(SidebarClass, At_54CC) == 0x54CC);
GG_STATIC_ASSERT(offsetof(SidebarClass, At_54EC) == 0x54EC);
GG_STATIC_ASSERT(offsetof(SidebarClass, At_550C) == 0x550C);
GG_STATIC_ASSERT(offsetof(SidebarClass, Count) == 0x5510);
GG_STATIC_ASSERT(offsetof(SidebarClass, At_5514) == 0x5514);
GG_STATIC_ASSERT(offsetof(SidebarClass, At_5515) == 0x5515);
// TabClass's INoticeSink sub-object sits at +0x5518 (RTTI base offset 21784).
GG_STATIC_ASSERT(sizeof(SidebarClass) == 0x5518);

// ---- TabClass ----------------------------------------------------------------------------------------------------

#include "../../_layout/notice_sink.h"

// The sub-object at TabClass +0x551C (constructed by 0x4A2350).
struct TabNoticeData
{
    char unknown_00[4];
    // FUNCTION: GAMEMD 0x4A2370 (decl; reloc) -- one bool argument; RET 4.
    void FUN_004A2370(bool arg);
    // FUNCTION: GAMEMD 0x4A2600 (decl; reloc) -- one int argument; RET 4.
    void FUN_004A2600(int arg);
};

// VTABLE: GAMEMD 0x7EDFB4 (55 slots; INoticeSink table 0x7EDFAC at +0x5518)
class TabClass : public SidebarClass, public INoticeSink
{
public:
    // FUNCTION: GAMEMD 0x6CFE20 (decl; reloc)
    TabClass();
    TabClass(const Obj_005BDF70& noInit);

    virtual void vf_05();                                // 5   0x6D0260
    virtual void vf_08();                                // 8   0x6D03A0
    virtual void vf_10(int* key, Point2D* where);        // 10  0x6D0680
    virtual void vf_16(bool forced);                     // 16  0x6D0A20 (draw)
    virtual const wchar_t* vf_33(int id);                // 33  0x6D1800
    virtual void vf_50();                                // 50  0x6D0270
    virtual void vf_53();                                // 53  0x6D02B0
    virtual bool vf_54(int control);                     // 54  0x6D04F0

    // INoticeSink slot 0 (0x6D1770): entered with ECX = the sub-object at +0x5518, which the body does not use.
    virtual bool Notice(int id, int arg);

    // FUNCTION: GAMEMD 0x6D04D0 (decl; reloc)
    void FUN_006D04D0();
    // FUNCTION: GAMEMD 0x6D0FD0 (decl; reloc)
    void FUN_006D0FD0();
    // FUNCTION: GAMEMD 0x6D1200 (decl; reloc)
    void FUN_006D1200();

    TabNoticeData unknown_551C;           // +0x551C
    int At_5520;                          // +0x5520
    char unknown_5524[0x5538 - 0x5524];   // +0x5524 (the constructor stores the frame counter at +0x552C)
    int At_5538;                          // +0x5538
    char unknown_553C[4];                 // +0x553C
    int At_5540;                          // +0x5540
    bool At_5544;                         // +0x5544
    bool At_5545;                         // +0x5545
    bool At_5546;                         // +0x5546
    char unknown_5547[1];                 // +0x5547
};
GG_STATIC_ASSERT(offsetof(TabClass, unknown_551C) == 0x551C);
GG_STATIC_ASSERT(offsetof(TabClass, At_5520) == 0x5520);
GG_STATIC_ASSERT(offsetof(TabClass, At_5538) == 0x5538);
GG_STATIC_ASSERT(offsetof(TabClass, At_5540) == 0x5540);
GG_STATIC_ASSERT(offsetof(TabClass, At_5544) == 0x5544);
GG_STATIC_ASSERT(offsetof(TabClass, At_5545) == 0x5545);
GG_STATIC_ASSERT(offsetof(TabClass, At_5546) == 0x5546);
GG_STATIC_ASSERT(sizeof(TabClass) == 0x5548);

// ---- ScrollClass -------------------------------------------------------------------------------------------------

// VTABLE: GAMEMD 0x7F1094 (55 slots; INoticeSink table 0x7F108C at +0x5518). The destructor is implicit (0x6938F0).
class ScrollClass : public TabClass
{
public:
    // FUNCTION: GAMEMD 0x692290
    ScrollClass();
    // FUNCTION: GAMEMD 0x5BE9B0 (decl; reloc) -- the "no initialisation" constructor the load path runs; RET 4.
    ScrollClass(const Obj_005BDF70& noInit);

    virtual void vf_08();                                // 8   0x40D270
    virtual void vf_10(int* key, Point2D* where);        // 10  0x6922E0
    virtual bool vf_26();                                // 26  0x693060
    virtual void vf_35();                                // 35  0x6938C0
    virtual void vf_44(const Point2D* where);            // 44  0x693880
    virtual void vf_49(int unused);                      // 49  0x693840

    // FUNCTION: GAMEMD 0x692300 (decl; reloc) -- RET 0x18.
    bool FUN_00692300(const Point2D* where, CellStruct* cell, DisplayCmdVec3* coord, DisplayCmdAbstract** target,
                      bool* a5, bool* a6);
    // FUNCTION: GAMEMD 0x692610 (decl; reloc) -- RET 0xC.
    int FUN_00692610(CellStruct* cell, DisplayCmdAbstract* target, bool a3);
    // FUNCTION: GAMEMD 0x692B60 (decl; reloc) -- RET 4.
    void FUN_00692B60(const Point2D* where);
    // FUNCTION: GAMEMD 0x692F30
    void FUN_00692F30();
    // FUNCTION: GAMEMD 0x693440 (decl; reloc) -- RET 4.
    void FUN_00693440(const Point2D* where);

    int  unknown_5548;                    // +0x5548
    bool unknown_554C;                    // +0x554C
    char unknown_554D[3];                 // +0x554D
    int  unknown_5550;                    // +0x5550  X of the saved position (vf_44)
    int  unknown_5554;                    // +0x5554  Y of the saved position (vf_44)
    bool unknown_5558;                    // +0x5558
    bool unknown_5559;                    // +0x5559  set to 1 by the constructor
    bool unknown_555A;                    // +0x555A
    char unknown_555B[1];                 // +0x555B
};
GG_STATIC_ASSERT(offsetof(ScrollClass, unknown_5548) == 0x5548);
GG_STATIC_ASSERT(offsetof(ScrollClass, unknown_554C) == 0x554C);
GG_STATIC_ASSERT(offsetof(ScrollClass, unknown_5550) == 0x5550);
GG_STATIC_ASSERT(offsetof(ScrollClass, unknown_5554) == 0x5554);
GG_STATIC_ASSERT(offsetof(ScrollClass, unknown_5558) == 0x5558);
GG_STATIC_ASSERT(offsetof(ScrollClass, unknown_5559) == 0x5559);
GG_STATIC_ASSERT(offsetof(ScrollClass, unknown_555A) == 0x555A);
GG_STATIC_ASSERT(sizeof(ScrollClass) == 0x555C);

// ---- MouseClass --------------------------------------------------------------------------------------------------

// VTABLE: GAMEMD 0x7E1964 (55 slots; INoticeSink table 0x7E195C at +0x5518)
class MouseClass : public ScrollClass
{
public:
    // The "no initialisation" constructor Load re-runs over the freshly read object: the out-of-line base part
    // (0x5BE9B0) then the two vptr stores.
    MouseClass(const Obj_005BDF70& noInit) : ScrollClass(noInit) {}
    // FUNCTION: GAMEMD 0x40D290 (scalar deleting destructor) -- see mouse_mouse_class.h for its state.
    virtual ~MouseClass() {}                             // 4   0x40D290

    virtual void vf_05();                                // 5   0x5BDF30 loads MOUSE.SHA
    virtual void vf_07();                                // 7   0x5BDF50 reset
    virtual void vf_10(int* key, Point2D* where);        // 10  0x5BDDC0 per-frame update
    virtual void vf_18(int cursor, bool flag);           // 18  0x5BDA80
    virtual bool vf_19(int cursor, bool flag);           // 19  0x5BDC80 apply a cursor row
    virtual void vf_20();                                // 20  0x5BDAA0 re-apply the requested cursor
    virtual void vf_21(bool flag);                       // 21  0x5BDAB0 switch the alternate-frame flag
    virtual long vf_30(IStream* stream);                 // 30  0x5BDF70 Load
    virtual long vf_31(IStream* stream);                 // 31  0x5BE6D0 Save
    virtual int  vf_40();                                // 40  0x40D280

    // Shared inline step of vf_19 / vf_21 (mouse_mouse_class_methods.cpp).
    void ApplyCursorRow(int index, bool flag);

    bool CursorFlag;                      // +0x555C the "alternate frames" flag of the applied cursor
    int  CursorIndex;                     // +0x5560 the applied row of the cursor table
    int  RequestedCursor;                 // +0x5564 the last cursor id requested through slot 18
    int  CursorFrame;                     // +0x5568 animation frame within the applied row

    // FUNCTION: GAMEMD 0x5BDA40 (native constructor)
    MouseClass();

    // FUNCTION: GAMEMD 0x5BDB90 (decl; reloc) -- RET 8, ECX (the map object) unused: a cursor-table row lookup.
    int FUN_005BDB90(int index, bool alternate);
};
GG_STATIC_ASSERT(offsetof(MouseClass, CursorFlag) == 0x555C);
GG_STATIC_ASSERT(offsetof(MouseClass, CursorIndex) == 0x5560);
GG_STATIC_ASSERT(offsetof(MouseClass, RequestedCursor) == 0x5564);
GG_STATIC_ASSERT(offsetof(MouseClass, CursorFrame) == 0x5568);
// sizeof from Save: `PUSH 0x556C` is the byte count written for the whole object (0x5BE715).
GG_STATIC_ASSERT(sizeof(MouseClass) == 0x556C);

// GLOBAL: GAMEMD 0x87F7E8 -- the map object (a static MouseClass; MOV ECX,0x87F7E8 at every call through it). Calls
// made on the object itself are direct calls to the slot body the MouseClass table holds.
extern MouseClass Map_0087F7E8;

#endif  // GG_MATCH_UI_INPUT_CONTROLS_UI_DISPLAY_CHAIN_H
