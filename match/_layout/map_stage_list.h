// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native 5CEDD0/5CEE60 establish the three vector and string lifetimes.
// Entry construction 5CEEF0 allocates MapStage as 0x6C and both MS entries
// as 0x10; 5D0380/5D0470 establish their leading string and scalar offsets.
// Vector element identities come from RTTI at 8301A0/830200/830268.
#ifndef GG_MATCH_LAYOUT_MAP_STAGE_LIST_H
#define GG_MATCH_LAYOUT_MAP_STAGE_LIST_H
#include "../core/string_class.h"
#include "../core/vector_class_operations.h"

class MSAnimEntry {
public:
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

class MapStage {
public:
    Wstring Name;                    // +0, copy receiver 5CF6F0
    Wstring Title;                   // +4, copy receiver 5CF799
    unsigned char unknown_08[0x64];
    // Declaration: GAMEMD 0x5D0070 -- ordinary destructor, external here.
    ~MapStage();
};
GG_STATIC_ASSERT(offsetof(MapStage, Name) == 0);
GG_STATIC_ASSERT(offsetof(MapStage, Title) == 4);
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
