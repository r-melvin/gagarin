// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Each function disassembled from the entry point of the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. File name attested by the
//   assert string "D:\ra2mdpost\MapGen.cpp" at 0x0082BA48. Every type, global
//   and function name below is a placeholder (FUN_/DAT_/Obj_/Rec_/unknown_)
//   derived from an address or offset in that binary.
#ifndef GG_MATCH_MAP_MAPGEN_H
#define GG_MATCH_MAP_MAPGEN_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/cell.h"
#include "../_layout/map_seed_class.h"
#include "iso_tile_type_class_tile_data_methods.h"
#include "../core/vector_class_operations.h"
#include "../core/trivial_tu130_methods.h"

// 8-byte value written through a pointer passed in ECX (0x58BB00).
struct Pair_8
{
    int unknown_00;
    int unknown_04;
};
GG_STATIC_ASSERT(sizeof(Pair_8) == 0x8);

// Element of the 0x50-byte record array at DAT_00ABED10 (count = DAT_0089C2DC squared).
struct Rec_50
{
    Cell unknown_00;   // returned whole (one dword copy) by 0x58C5A0
    unsigned char unknown_04[0x1C];
    double unknown_20;
    double unknown_28;
    unsigned char unknown_30[8];
    int unknown_38;
    int unknown_3C;
    int unknown_40;
    unsigned char unknown_44;
    unsigned char unknown_45;
    unsigned char unknown_46;
    unsigned char unknown_47[4];
    unsigned char unknown_4B;
    unsigned char unknown_4C[4];
};
GG_STATIC_ASSERT(offsetof(Rec_50, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(Rec_50, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(Rec_50, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(Rec_50, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(Rec_50, unknown_44) == 0x44);
GG_STATIC_ASSERT(offsetof(Rec_50, unknown_46) == 0x46);
GG_STATIC_ASSERT(offsetof(Rec_50, unknown_4B) == 0x4B);
GG_STATIC_ASSERT(sizeof(Rec_50) == 0x50);

// Returned by 0x58C800; only the byte at +0x1A is written here.
struct Rec_0058C800Ret
{
    unsigned char unknown_00[0x1A];
    unsigned char unknown_1A;
};
GG_STATIC_ASSERT(offsetof(Rec_0058C800Ret, unknown_1A) == 0x1A);


// RTTI-attested class; the canonical layout (_layout/cell_class.h) is included by MapGen.cpp.
class CellClass;

// Four ints: x, y, width, height.
struct Rect_4i
{
    int unknown_00;
    int unknown_04;
    int unknown_08;
    int unknown_0C;
};
GG_STATIC_ASSERT(sizeof(Rect_4i) == 0x10);
// Member-wise equality, as compared inline at 0x59B940.
inline bool operator==(const Rect_4i& a, const Rect_4i& b)
{
    return a.unknown_00 == b.unknown_00 && a.unknown_04 == b.unknown_04 && a.unknown_08 == b.unknown_08 &&
           a.unknown_0C == b.unknown_0C;
}
inline bool operator!=(const Rect_4i& a, const Rect_4i& b) { return !(a == b); }

// The map object at 0x87F7E8 (immediate ECX at every call): only the entry points called from here.
struct Cell_005A7250;
struct CellStruct_005A7250;

struct Gbl_0087F7E8
{
    // FUNCTION: GAMEMD 0x578290 (declaration)
    CellClass* FUN_00578290();
    // FUNCTION: GAMEMD 0x578350 (declaration)
    void FUN_00578350();
    // FUNCTION: GAMEMD 0x568BB0 (declaration)
    void FUN_00568BB0(char a1);
    // FUNCTION: GAMEMD 0x578460 (declaration)
    bool FUN_00578460(CellStruct const* a1, char a2);
    // FUNCTION: GAMEMD 0x578E60 (declaration)
    void FUN_00578E60(int a1, int a2);
    // FUNCTION: GAMEMD 0x654490 (declaration)
    void FUN_00654490(Rect_4i* a1);
    // FUNCTION: GAMEMD 0x654650 (declaration)
    void FUN_00654650();
    // FUNCTION: GAMEMD 0x5657A0 (declaration)
    CellClass* FUN_005657A0(CellStruct const* a1);
    // FUNCTION: GAMEMD 0x56D230 (declaration) -- the zone of a cell for a movement zone.
    int FUN_0056D230(const CellStruct& cell, int movementZone, bool isBridge);
    // The same entry point 0x5657A0 as the 0x5A7250 TU spelled it (by reference, its own cell view).
    Cell_005A7250* GetCell(const CellStruct_005A7250& cell);
};

typedef DynamicVectorClass<Cell> Vec_Cell;

// Element type of the RTTI-named VectorClass<TRect<int>> (vtable 0x7ED970).
#include "../_layout/geometry2d.h"

// Polymorphic object owned through MapRegionClass::unknown_00 (deleted through its scalar deleting destructor, slot 0).
class Obj_MapRegionOwned
{
public:
    virtual ~Obj_MapRegionOwned();
};

// Constructed through 0x58BF70 (operator new(0x50)); the list DAT_00ABDF90 holds RTTI .?AV?$DynamicVectorClass@PAVMapRegionClass@@
// pointers. +0x28 is a DynamicVectorClass<Cell> (vtables 0x7E3890 / 0x7E38D0).
class MapRegionClass
{
public:
    Obj_MapRegionOwned* unknown_00;
    int unknown_04;
    int unknown_08;
    int unknown_0C;
    int unknown_10;
    char unknown_14;
    unsigned char unknown_15;
    CellStruct unknown_16;
    unsigned char unknown_1A;
    unsigned char unknown_1B;
    int unknown_1C;
    int unknown_20;
    unsigned char unknown_24;
    unsigned char unknown_25[3];
    DynamicVectorClass<Cell> unknown_28;
    int unknown_40;
    int unknown_44;
    int unknown_48;
    int unknown_4C;

    // FUNCTION: GAMEMD 0x58BF70
    MapRegionClass(CellStruct a1);
    // FUNCTION: GAMEMD 0x58C070
    ~MapRegionClass();
    // FUNCTION: GAMEMD 0x58C2D0
    void FUN_0058C2D0();
    // FUNCTION: GAMEMD 0x58C320
    void FUN_0058C320(CellStruct* a1);
    // FUNCTION: GAMEMD 0x58C3B0
    void FUN_0058C3B0(CellStruct* a1);
    // FUNCTION: GAMEMD 0x58E5D0
    DynamicVectorClass<Cell>* FUN_0058E5D0();
    // FUNCTION: GAMEMD 0x594010
    bool FUN_00594010(Rect_4i* a1, int a2);
    // FUNCTION: GAMEMD 0x5942F0
    void FUN_005942F0(Rect_4i* a1);
    // FUNCTION: GAMEMD 0x58D5A0
    void FUN_0058D5A0(char a1);
};
GG_STATIC_ASSERT(offsetof(MapRegionClass, unknown_08) == 0x8);
GG_STATIC_ASSERT(offsetof(MapRegionClass, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(MapRegionClass, unknown_16) == 0x16);
GG_STATIC_ASSERT(offsetof(MapRegionClass, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(MapRegionClass, unknown_40) == 0x40);
GG_STATIC_ASSERT(sizeof(MapRegionClass) == 0x50);


// ScenarioClass::Instance (0xA8B230): only the member this file touches.
struct Gbl_00A8B230
{
    unsigned char unknown_00[0x3598];
    unsigned char unknown_3598;
};
GG_STATIC_ASSERT(offsetof(Gbl_00A8B230, unknown_3598) == 0x3598);

// The session object at 0xA8B238: only the entry point called from here.
struct Gbl_00A8B238
{
    // FUNCTION: GAMEMD 0x69AE90 (declaration)
    void FUN_0069AE90(int a1);
};

// The audio object at 0xAC4F58: only the entry point called from here.
struct Gbl_00AC4F58
{
    // FUNCTION: GAMEMD 0x643C50 (declaration)
    void FUN_00643C50(int a1, double a2, unsigned int a3, unsigned int a4);
};

// The random-number generator object at 0x886B88.
struct Gbl_00886B88
{
    // FUNCTION: GAMEMD 0x65C7E0 (declaration)
    unsigned int FUN_0065C7E0(int a1, int a2);
};

// The object at 0xABDFB8 whose method 0x5980C0 yields a double.
struct Gbl_00ABDFB8
{
    // FUNCTION: GAMEMD 0x5980C0 (declaration)
    double FUN_005980C0();
};

// Receiver of the 0x59C580 / 0x59C880 / 0x59D440 / 0x5A1E10 family: a large object with a state word at +0x3C.
class Obj_0059C580
{
public:
    unsigned char unknown_00[0x3C];
    int unknown_3C;
    unsigned char unknown_40[0xC];
    int unknown_4C;
    unsigned char unknown_50[0x130];
    int unknown_180;
    int unknown_184;
    unsigned char unknown_188[0x17C];
    int unknown_304;
    int unknown_308;
    int unknown_30C;

    // FUNCTION: GAMEMD 0x59D440
    int FUN_0059D440();
    // FUNCTION: GAMEMD 0x5A17F0 (declaration)
    void FUN_005A17F0();
    // FUNCTION: GAMEMD 0x5A19E0 (declaration)
    void FUN_005A19E0();
    // FUNCTION: GAMEMD 0x5A1E10
    void FUN_005A1E10();
};
GG_STATIC_ASSERT(offsetof(Obj_0059C580, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(Obj_0059C580, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(Obj_0059C580, unknown_180) == 0x180);
GG_STATIC_ASSERT(offsetof(Obj_0059C580, unknown_184) == 0x184);
GG_STATIC_ASSERT(offsetof(Obj_0059C580, unknown_304) == 0x304);
GG_STATIC_ASSERT(offsetof(Obj_0059C580, unknown_308) == 0x308);
GG_STATIC_ASSERT(offsetof(Obj_0059C580, unknown_30C) == 0x30C);

// GLOBAL: GAMEMD 0x82BA2C -- "TXT_RANDOM_MAP_DESCRIPTION"
extern char DAT_0082BA2C[];
// GLOBAL: GAMEMD 0x82BA48 -- "D:\ra2mdpost\MapGen.cpp"
extern char DAT_0082BA48[];
// GLOBAL: GAMEMD 0x886B88
extern Gbl_00886B88 DAT_00886B88;
// GLOBAL: GAMEMD 0xA8B238
extern Gbl_00A8B238 DAT_00A8B238;
// GLOBAL: GAMEMD 0xAC4F58
extern Gbl_00AC4F58 DAT_00AC4F58;
// GLOBAL: GAMEMD 0xABDFB8
extern Gbl_00ABDFB8 DAT_00ABDFB8;
// GLOBAL: GAMEMD 0xABE2F0
extern Rect_4i DAT_00ABE2F0;
// GLOBAL: GAMEMD 0x87F8E4
extern Rect_4i DAT_0087F8E4;
// GLOBAL: GAMEMD 0x87F8DC
extern int DAT_0087F8DC;
// GLOBAL: GAMEMD 0x7ED7F0
extern double DAT_007ED7F0;
// GLOBAL: GAMEMD 0x7ED7F8
extern double DAT_007ED7F8;
// GLOBAL: GAMEMD 0x87F7E8 -- the map object.
extern Gbl_0087F7E8 DAT_0087F7E8;
// GLOBAL: GAMEMD 0x89C2DC
extern int DAT_0089C2DC;
// GLOBAL: GAMEMD 0xA8B230 -- ScenarioClass::Instance.
extern Gbl_00A8B230* DAT_00A8B230;
// GLOBAL: GAMEMD 0x82B080
extern int DAT_0082B080[];
// GLOBAL: GAMEMD 0x82B094
extern int DAT_0082B094[];
// GLOBAL: GAMEMD 0x82B0A8
extern int DAT_0082B0A8[];
// GLOBAL: GAMEMD 0x82B0BC
extern int DAT_0082B0BC[];
// GLOBAL: GAMEMD 0x82B0D0
extern int DAT_0082B0D0[];
// GLOBAL: GAMEMD 0x82B0F8
extern int DAT_0082B0F8[];
// GLOBAL: GAMEMD 0x82B10C
extern int DAT_0082B10C[];
// GLOBAL: GAMEMD 0x82B120
extern int DAT_0082B120[];
// GLOBAL: GAMEMD 0xABED18
extern int DAT_00ABED18[];
// GLOBAL: GAMEMD 0xABED40
extern int DAT_00ABED40[];
// GLOBAL: GAMEMD 0xABE260
extern int* DAT_00ABE260;
// GLOBAL: GAMEMD 0xABE27C
extern int* DAT_00ABE27C;
// GLOBAL: GAMEMD 0x89F688 -- eight neighbour offsets.
extern CellStruct DAT_0089F688[];
// GLOBAL: GAMEMD 0xA8ED2C -- the tile table (Items of the IsometricTileTypeClass vector at 0xA8ED28).
extern IsometricTileTypeClass** DAT_00A8ED2C;
// GLOBAL: GAMEMD 0xABAD28
extern int DAT_00ABAD28;
// GLOBAL: GAMEMD 0xAA0E18
extern int DAT_00AA0E18;
// GLOBAL: GAMEMD 0xABE328
extern Pair_8 DAT_00ABE328[];
// GLOBAL: GAMEMD 0xABED0C
extern int DAT_00ABED0C;
// GLOBAL: GAMEMD 0xABED10
extern Rec_50* DAT_00ABED10;
// GLOBAL: GAMEMD 0xABED04
extern int DAT_00ABED04;
// GLOBAL: GAMEMD 0xABED08
extern int DAT_00ABED08;
// GLOBAL: GAMEMD 0xABED14
extern int DAT_00ABED14;
// GLOBAL: GAMEMD 0xABDF90
extern DynamicVectorClass<MapRegionClass*> DAT_00ABDF90;

// Inline helper expanded in 0x5942F0 and others (placeholder name): is the cell inside the playable diamond.
inline bool Inline_005942F0(CellStruct c)
{
    int x = c.X;
    int y = c.Y;
    return y + x > DAT_00ABED04 && x - y < DAT_00ABED04 && y - x < DAT_00ABED04 && y + x <= DAT_00ABED08;
}

// Region lookup by id (+0x08); out of line at 0x5943E0 and expanded in 0x594190 (placeholder name).
inline MapRegionClass* Inline_005943E0(int id)
{
    for (int i = 0; i < DAT_00ABDF90.Count; i++) {
        if (DAT_00ABDF90.Items[i]->unknown_08 == id)
            return DAT_00ABDF90.Items[i];
    }
    return 0;
}

// Inline helper expanded in 0x58C320 (placeholder name): a draw in [0, last].
inline unsigned int Inline_0058C320(unsigned int last)
{
    unsigned int idx;
    do {
        idx = (unsigned int)((double)(last + 1) * (double)DAT_00ABE890.FUN_0065C780() * 2.3283064370807974e-10);
    } while (idx > last);
    return idx;
}

// Inline helper of 0x58BCF0 (placeholder name).
inline bool Inline_0058BCF0(int a1)
{
    return a1 == 3 || a1 == 4;
}

// FUNCTION: GAMEMD 0x4068E0 (declaration) -- the debug print (format, ...), as declared elsewhere in this TU.
extern "C" int __cdecl FUN_004068E0(const char* format, ...);

// FUNCTION: GAMEMD 0x58BB00
Pair_8* FUN_0058BB00(Pair_8* a1, int a2);
// FUNCTION: GAMEMD 0x58BCF0
bool FUN_0058BCF0(int a1);
// FUNCTION: GAMEMD 0x58BD80
bool FUN_0058BD80(int a1, int a2);
// FUNCTION: GAMEMD 0x58C100
void FUN_0058C100();
// FUNCTION: GAMEMD 0x58C5A0
Cell FUN_0058C5A0(int zone, int kind);
// FUNCTION: GAMEMD 0x58CE90
void FUN_0058CE90();
// The random-map generator object at 0xABDFD8. Its constructor 0x595740
// (called from the static initialiser 0x58B740; atexit teardown 0x58B760 ->
// 0x5958E0) first runs the MapSeedClass constructor 0x595680 on +0 without
// replacing the vtable pointer, then initialises the members below. The
// 0x1C-byte blocks are vector objects whose constructors are 0x477DB0 /
// 0x477BE0 (table 0x7E4DD8) and 0x5AC900 / 0x5105A0 (table 0x7ED90C); their
// element types are not identified, so they stay opaque here. The object's
// end is not yet bounded past +0x310.
class Gbl_00ABDFD8 : public MapSeedClass
{
public:
    int unknown_178;                    // +0x178  ctor 0
    int unknown_17C;                    // +0x17C  ctor 0
    int unknown_180;                    // +0x180  ctor 0
    int unknown_184;                    // +0x184  ctor 0
    unsigned char unknown_188[0x1C];    // +0x188  vector (0x477DB0, table 0x7E4DD8)
    unsigned char unknown_1A4[0x1C];    // +0x1A4  vector (0x477DB0)
    unsigned char unknown_1C0[0x1C];    // +0x1C0  vector (0x477DB0)
    unsigned char unknown_1DC[0x1C];    // +0x1DC  vector (0x477DB0)
    unsigned char unknown_1F8[0x1C];    // +0x1F8  dynamic vector (0x477BE0, growth 10)
    unsigned char unknown_214[0x1C];    // +0x214  vector (0x477DB0)
    unsigned char unknown_230[0x1C];    // +0x230  vector (0x477DB0)
    unsigned char unknown_24C[0x1C];    // +0x24C  vector (0x477DB0)
    unsigned char unknown_268[0x1C];    // +0x268  dynamic vector (0x477BE0, growth 10)
    unsigned char unknown_284[0x1C];    // +0x284  vector (0x477DB0)
    unsigned char unknown_2A0[0x1C];    // +0x2A0  vector (0x477DB0)
    int unknown_2BC;                    // +0x2BC  ctor 0x9C4
    int unknown_2C0;                    // +0x2C0  ctor 0x157C
    unsigned char unknown_2C4[0x1C];    // +0x2C4  vector (0x5AC900, table 0x7ED90C)
    unsigned char unknown_2E0[0x1C];    // +0x2E0  dynamic vector (0x5105A0, growth 10)
    int unknown_2FC;                    // +0x2FC  ctor 0x1F4
    bool unknown_300;                   // +0x300  ctor 1
    int unknown_304;                    // +0x304  ctor 0
    int unknown_308;                    // +0x308
    int unknown_30C;                    // +0x30C  ctor 4
    bool unknown_310;                   // +0x310  ctor 0

    // FUNCTION: GAMEMD 0x595740 (decl; reloc) -- constructor
    Gbl_00ABDFD8();
    // FUNCTION: GAMEMD 0x5958E0 (decl; reloc) -- destructor
    ~Gbl_00ABDFD8();

    // FUNCTION: GAMEMD 0x5981F0 (declaration)
    void FUN_005981F0();
};
GG_STATIC_ASSERT(offsetof(Gbl_00ABDFD8, unknown_178) == 0x178);
GG_STATIC_ASSERT(offsetof(Gbl_00ABDFD8, unknown_188) == 0x188);
GG_STATIC_ASSERT(offsetof(Gbl_00ABDFD8, unknown_2A0) == 0x2A0);
GG_STATIC_ASSERT(offsetof(Gbl_00ABDFD8, unknown_2BC) == 0x2BC);
GG_STATIC_ASSERT(offsetof(Gbl_00ABDFD8, unknown_2C4) == 0x2C4);
GG_STATIC_ASSERT(offsetof(Gbl_00ABDFD8, unknown_2FC) == 0x2FC);
GG_STATIC_ASSERT(offsetof(Gbl_00ABDFD8, unknown_300) == 0x300);
GG_STATIC_ASSERT(offsetof(Gbl_00ABDFD8, unknown_304) == 0x304);
GG_STATIC_ASSERT(offsetof(Gbl_00ABDFD8, unknown_30C) == 0x30C);
GG_STATIC_ASSERT(offsetof(Gbl_00ABDFD8, unknown_310) == 0x310);
// GLOBAL: GAMEMD 0xABDFD8
extern Gbl_00ABDFD8 DAT_00ABDFD8;

// Callback run each pass of the 0x595BC0 dialog loop (CALL ESI, no arguments).
typedef void (*Callback_00595BC0)();
// Owned object at 0xABE150, deleted through its virtual deleting destructor (slot 0).
class Obj_00ABE150
{
public:
    virtual ~Obj_00ABE150();
};
class SeatNull_006406E0;
class FileClass;
// GLOBAL: GAMEMD 0x82AF14 -- callback slot; 0x48D1D0 is its resting value.
extern Callback_00595BC0 DAT_0082AF14;
// GLOBAL: GAMEMD 0xABDFEC
extern Callback_00595BC0 DAT_00ABDFEC;
// GLOBAL: GAMEMD 0xABE150
extern Obj_00ABE150* DAT_00ABE150;
// GLOBAL: GAMEMD 0xABE154 -- the preview whose first dword is its surface.
extern SeatNull_006406E0* DAT_00ABE154;
// GLOBAL: GAMEMD 0x885780 -- the palette written with the preview.
extern char DAT_00885780[];
// FUNCTION: GAMEMD 0x596300 (declaration) -- the dialog procedure of 0x595BC0.
int __stdcall FUN_00596300(void* window, unsigned int message, unsigned int wparam, long lparam);
// FUNCTION: GAMEMD 0x622650 (declaration) -- UI::BeginDialog (its header's globals clash with this TU's).
void* UI_BeginDialog(unsigned short id, int (__stdcall* proc)(void*, unsigned int, unsigned int, long), int param);
// FUNCTION: GAMEMD 0x622720 (declaration) -- UI::EndDialog.
void UI_EndDialog(void* window);
// FUNCTION: GAMEMD 0x532100 (declaration) -- __fastcall, one byte flag.
void FUN_00532100(bool flag);
// FUNCTION: GAMEMD 0x7B05C0 (declaration) -- write a surface to a PCX file:
// file in ECX, surface in EDX, palette pushed.
int FUN_007B05C0(FileClass* file, void* surface, void* palette);
class BuildingTypeClass;
// GLOBAL: GAMEMD 0xA83C6C -- BuildingTypeClass::Array items.
extern BuildingTypeClass** DAT_00A83C6C;
// FUNCTION: GAMEMD 0x45E7B0 (declaration) -- building type name to index.
int FUN_0045E7B0(const char* name);
// GLOBAL: GAMEMD 0x7ED6D8 -- 5.0
extern const double DAT_007ED6D8;
// GLOBAL: GAMEMD 0x7ED6E0 -- 15.0
extern const double DAT_007ED6E0;
// GLOBAL: GAMEMD 0x82AF18 -- one bit per neighbour of a 3x3 block (centre 0).
extern int DAT_0082AF18[9];
// FUNCTION: GAMEMD 0x5A1E50 (declaration) -- area in ECX, value in EDX, two stack arguments.
bool FUN_005A1E50(Rect_4i* area, int a2, int a3, int a4);

// Receiver of 0x590970 and 0x590FD0 (ECX); only +0x08 is read here.
class Obj_00590970
{
public:
    unsigned char unknown_00[8];
    int unknown_08;

    // FUNCTION: GAMEMD 0x590FD0
    int FUN_00590FD0(CellStruct* cell, bool* ok, int a3, float a4);
};
GG_STATIC_ASSERT(offsetof(Obj_00590970, unknown_08) == 0x8);

// FUNCTION: GAMEMD 0x4CAC40 (declaration) -- the square root of a double.
double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x59B940
float __stdcall FUN_0059B940(CellStruct* a1, CellStruct* a2, Rect_4i* area, CellStruct* a4, float a5, float a6);
// FUNCTION: GAMEMD 0x5904B0
bool __stdcall FUN_005904B0(Rect_4i* area);
// FUNCTION: GAMEMD 0x595BC0
int FUN_00595BC0(Callback_00595BC0 callback);
// FUNCTION: GAMEMD 0x5A6C10
void FUN_005A6C10(int a1, CellStruct* a2, int a3, int a4);
// FUNCTION: GAMEMD 0x5A7E90
void FUN_005A7E90(int a1, CellStruct* a2);
// FUNCTION: GAMEMD 0x5A7FA0
void FUN_005A7FA0(int a1, CellStruct* a2, char a3);
// FUNCTION: GAMEMD 0x58D010
void FUN_0058D010(char a1);
// FUNCTION: GAMEMD 0x5943E0
MapRegionClass* FUN_005943E0(int a1);
// FUNCTION: GAMEMD 0x594420 (declaration) -- grows a region from `cell`.
void FUN_00594420(CellClass* cell, int a2, int a3);
// FUNCTION: GAMEMD 0x594700
void FUN_00594700(int a1, int a2);
// FUNCTION: GAMEMD 0x594190
void __stdcall FUN_00594190(Rect_4i* area, int id);
// FUNCTION: GAMEMD 0x599530
void FUN_00599530(Obj_0059C580* a1);
// FUNCTION: GAMEMD 0x59C530
void FUN_0059C530();
// FUNCTION: GAMEMD 0x59C800
bool __stdcall FUN_0059C800(int a1);
// FUNCTION: GAMEMD 0x59E640
void __stdcall FUN_0059E640(int a1, char a2);
// FUNCTION: GAMEMD 0x59E6C0
void __stdcall FUN_0059E6C0(int a1, char a2);
// FUNCTION: GAMEMD 0x5A1270
void FUN_005A1270();
// FUNCTION: GAMEMD 0x5A12D0
void __stdcall FUN_005A12D0(char a1, int a2);
// FUNCTION: GAMEMD 0x734E60 (declaration) -- localised string lookup(label, index-out, file, line); __fastcall, RET 8.
unsigned short* FUN_00734E60(char* a1, int a2, char* a3, int a4);
// LIBRARY: GAMEMD 0x7CA489 -- CRT wcscpy (__cdecl).
extern "C" unsigned short* __cdecl FUN_007CA489(unsigned short* a1, unsigned short* a2);

// FUNCTION: GAMEMD 0x598180
double __stdcall FUN_00598180(double a1, double a2, double a3, double a4);
// FUNCTION: GAMEMD 0x59A670
void __stdcall FUN_0059A670(int a1);
// FUNCTION: GAMEMD 0x59BAB0
bool __stdcall FUN_0059BAB0(CellStruct* a1, Rect_4i* a2, char a3, double a4, double a5);
// FUNCTION: GAMEMD 0x5A6BA0
bool FUN_005A6BA0(CellStruct* a1);

// FUNCTION: GAMEMD 0x58EBC0 (declaration)
void FUN_0058EBC0();
// FUNCTION: GAMEMD 0x58EF10 (declaration)
void FUN_0058EF10();
// FUNCTION: GAMEMD 0x59B6D0
void FUN_0059B6D0();
// FUNCTION: GAMEMD 0x5A3A60
void FUN_005A3A60();

#endif  // GG_MATCH_MAP_MAPGEN_H
