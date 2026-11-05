// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native 5CEDD0/5CEE60 establish the three vector and string lifetimes.
// Entry construction 5CEEF0 allocates MapStage as 0x6C and both MS entries
// as 0x10; 5D0380/5D0470 establish their leading string and scalar offsets.
// Vector element identities come from RTTI at 8301A0/830200/830268.
#ifndef GG_MATCH_LAYOUT_MAP_STAGE_LIST_H
#define GG_MATCH_LAYOUT_MAP_STAGE_LIST_H
#include "../string_class.h"
#include "../wide_string_class.h"
#include "../vector_class_operations.h"
#include "geometry2d.h"

class MSAnimEntry {
public:
    // FUNCTION: GAMEMD 0x5D0380 -- reads up to four comma-separated fields of `text`.
    MSAnimEntry(Wstring* text);
    Wstring Name;                    // +0, 5D0380 string construction
    int unknown_04;
    int unknown_08;
    int unknown_0C;
};
GG_STATIC_ASSERT(offsetof(MSAnimEntry, Name) == 0);
GG_STATIC_ASSERT(offsetof(MSAnimEntry, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(MSAnimEntry, unknown_08) == 8);
GG_STATIC_ASSERT(offsetof(MSAnimEntry, unknown_0C) == 0xC);
GG_STATIC_ASSERT(sizeof(MSAnimEntry) == 0x10);

class MSSfxEntry {
public:
    // FUNCTION: GAMEMD 0x5D0470 -- `name` is the default text; `fields` is the comma-separated list read.
    MSSfxEntry(Wstring* name, Wstring* fields);
    // FUNCTION: GAMEMD 0x5D0590 (decl; reloc) -- an empty method (a single RET).
    void FUN_005D0590();

    Wstring Name;                    // +0, 5D0470 string construction
    unsigned char unknown_04;
    unsigned char unknown_05[3];
    int unknown_08;
    int unknown_0C;
};
GG_STATIC_ASSERT(offsetof(MSSfxEntry, Name) == 0);
GG_STATIC_ASSERT(offsetof(MSSfxEntry, unknown_04) == 4);
GG_STATIC_ASSERT(offsetof(MSSfxEntry, unknown_08) == 8);
GG_STATIC_ASSERT(offsetof(MSSfxEntry, unknown_0C) == 0xC);
GG_STATIC_ASSERT(sizeof(MSSfxEntry) == 0x10);

// RTTI VectorClass<MSTextEntry*> (0x7EEB94): the element built by 0x5D0290 from a wide comma-separated list.
class MSTextEntry {
public:
    // FUNCTION: GAMEMD 0x5D0290
    MSTextEntry(const Obj_007B66D0* fields);

    int unknown_00;
    int unknown_04;
    int unknown_08;
    Obj_007B66D0 unknown_0C;         // +0xC wide string, built first by 5D0290 and released by 5D0070
};
GG_STATIC_ASSERT(offsetof(MSTextEntry, unknown_0C) == 0xC);
GG_STATIC_ASSERT(sizeof(MSTextEntry) == 0x10);

// RTTI VectorClass<MapSelection*> (0x7EEBB4): 5D0070 releases each element's leading Wstring and frees it;
// 5D0190 and 5D0240 read the name and a flag byte at +0x04. Only those two members are attested.
class MapSelection {
public:
    Wstring Name;                    // +0
    unsigned char unknown_04;        // +4
};
GG_STATIC_ASSERT(offsetof(MapSelection, unknown_04) == 4);

class MapStage {
public:
    Wstring Name;                    // +0, copy receiver 5CF6F0
    Wstring Title;                   // +4, copy receiver 5CF799
    Wstring unknown_08;              // +0x08 released by 5D0070
    Wstring unknown_0C;              // +0x0C released by 5D0070
    Obj_007B66D0 unknown_10;         // +0x10 wide string released by 5D0070
    int unknown_14;                  // +0x14 not touched by the destructor
    Wstring unknown_18[2];           // +0x18 two strings, released as an array
    Wstring unknown_20;              // +0x20
    DynamicVectorClass<Point2D> unknown_24;          // +0x24 (vtable 0x7EEB54), released by 5D0070
    DynamicVectorClass<MSTextEntry*> unknown_3C;     // +0x3C (vtable 0x7EEB34), elements deleted by 5D0070
    DynamicVectorClass<MapSelection*> unknown_54;    // +0x54 (vtable 0x7EEB14): Items +0x58 and Count +0x64
    // FUNCTION: GAMEMD 0x5D0070
    ~MapStage();
    MapSelection* FUN_005D0190(const char* key);   // 5D0190: the entry whose upper-cased name equals the key, or null
    Wstring FUN_005D0240(unsigned char flag);      // 5D0240: a copy of the name of the first entry with this flag byte
};
GG_STATIC_ASSERT(offsetof(MapStage, Name) == 0);
GG_STATIC_ASSERT(offsetof(MapStage, Title) == 4);
GG_STATIC_ASSERT(offsetof(MapStage, unknown_10) == 0x10);
GG_STATIC_ASSERT(offsetof(MapStage, unknown_18) == 0x18);
GG_STATIC_ASSERT(offsetof(MapStage, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(MapStage, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(MapStage, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(MapStage, unknown_54) == 0x54);
GG_STATIC_ASSERT(sizeof(MapStage) == 0x6C);

// Declaration: GAMEMD 0x407000 -- the call at 5CF84C tests full EAX.
int SessionExists();

class MapStageList {
public:
    DynamicVectorClass<MapStage*> Stages;
    int BoundsX;
    int BoundsY;
    int BoundsW;
    int BoundsH;
    Wstring Name;
    DynamicVectorClass<MSAnimEntry*> Strings;
    DynamicVectorClass<MSSfxEntry*> Titles;

    MapStageList();                         // 5CEDD0
    ~MapStageList();                        // 5CEE60
    void ClearAll();                        // 5CF5F0
    MapStage* FindByName(Wstring* key);       // 5CF6B0
    MapStage* FindByTitle(Wstring* key);      // 5CF760
    MapStage* GetAt(unsigned short index);   // 5CF810
    int FUN_005CF830(MapStage* stage);       // virtual FindItemIndex, not append
    Wstring* FindTitle(Wstring* key);        // 5CF840
};
GG_STATIC_ASSERT(offsetof(MapStageList, Stages) == 0);
GG_STATIC_ASSERT(offsetof(MapStageList, BoundsX) == 0x18);
GG_STATIC_ASSERT(offsetof(MapStageList, BoundsY) == 0x1C);
GG_STATIC_ASSERT(offsetof(MapStageList, BoundsW) == 0x20);
GG_STATIC_ASSERT(offsetof(MapStageList, BoundsH) == 0x24);
GG_STATIC_ASSERT(offsetof(MapStageList, Name) == 0x28);
GG_STATIC_ASSERT(offsetof(MapStageList, Strings) == 0x2C);
GG_STATIC_ASSERT(offsetof(MapStageList, Titles) == 0x44);
GG_STATIC_ASSERT(sizeof(MapStageList) == 0x5C);
#endif
