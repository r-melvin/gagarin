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
#include "../map/iso_tile_type_class_tile_data_methods.h"
#include "vector_class_operations.h"
#include "trivial_tu130_methods.h"

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
    CellStruct unknown_00;
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

// Local view of CellClass (RTTI-attested class; MapCoords at +0x24): only the members this file touches.
class CellClass
{
public:
    unsigned char unknown_00[0x24];
    CellStruct unknown_24;
    unsigned char unknown_28[0x10];
    int unknown_38;
    unsigned char unknown_3C[0xDE];
    unsigned char unknown_11A;
    signed char unknown_11B;

    // FUNCTION: GAMEMD 0x481810 (declaration)
    CellClass* FUN_00481810(int a1);
    // FUNCTION: GAMEMD 0x4863D0 (declaration)
    bool FUN_004863D0();
    // FUNCTION: GAMEMD 0x486380 (declaration)
    bool FUN_00486380();
    // FUNCTION: GAMEMD 0x4865B0 (declaration)
    bool FUN_004865B0();
    // FUNCTION: GAMEMD 0x4865D0 (declaration)
    char FUN_004865D0();
    // FUNCTION: GAMEMD 0x58C800 (declaration)
    Rec_0058C800Ret* FUN_0058C800();
};
GG_STATIC_ASSERT(offsetof(CellClass, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(CellClass, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(CellClass, unknown_11A) == 0x11A);
GG_STATIC_ASSERT(offsetof(CellClass, unknown_11B) == 0x11B);

// Four ints: x, y, width, height.
struct Rect_4i
{
    int unknown_00;
    int unknown_04;
    int unknown_08;
    int unknown_0C;
};
GG_STATIC_ASSERT(sizeof(Rect_4i) == 0x10);

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
    // The same entry point 0x5657A0 as the 0x5A7250 TU spelled it (by reference, its own cell view).
    Cell_005A7250* GetCell(const CellStruct_005A7250& cell);
};

typedef DynamicVectorClass<Cell> Vec_Cell;

// Element type of the RTTI-named VectorClass<TRect<int>> (vtable 0x7ED970): four ints.
template<class T> class TRect
{
public:
    T unknown_00;
    T unknown_04;
    T unknown_08;
    T unknown_0C;
    TRect() {}
    bool operator==(const TRect<T>& o) const
    {
        return unknown_00 == o.unknown_00 && unknown_04 == o.unknown_04 && unknown_08 == o.unknown_08 &&
               unknown_0C == o.unknown_0C;
    }
    bool operator!=(const TRect<T>& o) const { return !(*this == o); }
};

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
Pair_8* __fastcall FUN_0058BB00(Pair_8* a1, int a2);
// FUNCTION: GAMEMD 0x58BCF0
bool __fastcall FUN_0058BCF0(int a1);
// FUNCTION: GAMEMD 0x58BD80
bool __fastcall FUN_0058BD80(int a1, int a2);
// FUNCTION: GAMEMD 0x58C100
void __fastcall FUN_0058C100();
// FUNCTION: GAMEMD 0x58CE90
void __fastcall FUN_0058CE90();
// FUNCTION: GAMEMD 0x5A7FA0
void __fastcall FUN_005A7FA0(int a1, CellStruct* a2, char a3);
// FUNCTION: GAMEMD 0x58D010
void __fastcall FUN_0058D010(char a1);
// FUNCTION: GAMEMD 0x5943E0
MapRegionClass* __fastcall FUN_005943E0(int a1);
// FUNCTION: GAMEMD 0x599530
void __fastcall FUN_00599530(Obj_0059C580* a1);
// FUNCTION: GAMEMD 0x59C530
void __fastcall FUN_0059C530();
// FUNCTION: GAMEMD 0x59C800
bool __stdcall FUN_0059C800(int a1);
// FUNCTION: GAMEMD 0x59E640
void __stdcall FUN_0059E640(int a1, char a2);
// FUNCTION: GAMEMD 0x59E6C0
void __stdcall FUN_0059E6C0(int a1, char a2);
// FUNCTION: GAMEMD 0x5A1270
void __fastcall FUN_005A1270();
// FUNCTION: GAMEMD 0x5A12D0
void __stdcall FUN_005A12D0(char a1, int a2);
// FUNCTION: GAMEMD 0x734E60 (declaration) -- localised string lookup(label, index-out, file, line); __fastcall, RET 8.
unsigned short* __fastcall FUN_00734E60(char* a1, int a2, char* a3, int a4);
// LIBRARY: GAMEMD 0x7CA489 -- CRT wcscpy (__cdecl).
extern "C" unsigned short* __cdecl FUN_007CA489(unsigned short* a1, unsigned short* a2);

// FUNCTION: GAMEMD 0x598180
double __stdcall FUN_00598180(double a1, double a2, double a3, double a4);
// FUNCTION: GAMEMD 0x59A670
void __stdcall FUN_0059A670(int a1);
// FUNCTION: GAMEMD 0x59BAB0
bool __stdcall FUN_0059BAB0(CellStruct* a1, Rect_4i* a2, char a3, double a4, double a5);
// FUNCTION: GAMEMD 0x5A6BA0
bool __fastcall FUN_005A6BA0(CellStruct* a1);

// FUNCTION: GAMEMD 0x58EBC0 (declaration)
void __fastcall FUN_0058EBC0();
// FUNCTION: GAMEMD 0x58EF10 (declaration)
void __fastcall FUN_0058EF10();
// FUNCTION: GAMEMD 0x59B6D0
void __fastcall FUN_0059B6D0();
// FUNCTION: GAMEMD 0x5A3A60
void __fastcall FUN_005A3A60();

#endif  // GG_MATCH_MAP_MAPGEN_H
