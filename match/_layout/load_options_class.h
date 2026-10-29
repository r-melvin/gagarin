// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Canonical LoadOptionsClass (the load/save/delete savegame dialog driver). Read from the retail
//   gamemd.exe v1.001:
//   RTTI .?AVLoadOptionsClass@@, vtable 0x7ED2E4 (9 slots, no base). Constructor 0x558740: stores the
//   DynamicVectorClass<FileEntryClass*> head at +0x20 (vtable 0x7ED30C, Count 0, capacity increment 10,
//   IsInitialized 1), then Mode(+0x04)=0, Description(+0x0C)=0, +0x14=0, vptr, Extension(+0x08)="SAV"
//   (0x829EA0), +0x10=0x800, and clears the entries through the vector's slot 3.
//   Destructor 0x558790 (out of line; the scalar deleting destructor 0x55A0D0 has the same body inlined):
//   stores the vptr, deletes each of the Count entries, clears the vector through its slot 3 and runs the
//   inlined VectorClass destructor (vtable 0x7ED32C). A stack instance in 0x52D640 is 0x38 bytes
//   (frame 0x38), so sizeof(LoadOptionsClass) == 0x38; MapSeedClass (0x178 bytes) derives from it.
//
//   Calling conventions: the census labelled the 0x559xxx slots __stdcall, but the bodies never touch
//   `this`: slot 1 takes one stack argument (RET 4), slots 2 and 4 take two (RET 8) and each loads the
//   arguments from the first stack slots, so they are __thiscall with unused ECX (the existing exact
//   0x559EB0 DeleteMission, RET 4 with the file name at [ESP+4], sits in slot 3 the same way).
#ifndef GG_MATCH_LAYOUT_LOAD_OPTIONS_CLASS_H
#define GG_MATCH_LAYOUT_LOAD_OPTIONS_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/vector_class.h"

// LoadOptionsMode (YRpp, reconfirmed from the disasm:
// LoadDialog stores 1 into Mode@+4, SaveDialog stores 2, DeleteDialog stores 3).
enum LoadOptionsMode
{
    LOM_None   = 0,
    LOM_Load   = 1,
    LOM_Save   = 2,
    LOM_Delete = 3
};

// One save-game list entry (the element of LoadOptionsClass::Entries). Only the touched fields are named.
class FileEntryClass
{
public:
    char _pad000[0x14];
    int  Field14;          // +0x14
    int  Field18;          // +0x18
    char _pad01C[0x10];
    char FileName[0x104];  // +0x2C
    char AltName[0x40];    // +0x130
};
GG_STATIC_ASSERT(offsetof(FileEntryClass, Field14) == 0x14);
GG_STATIC_ASSERT(offsetof(FileEntryClass, Field18) == 0x18);
GG_STATIC_ASSERT(offsetof(FileEntryClass, FileName) == 0x2C);
GG_STATIC_ASSERT(offsetof(FileEntryClass, AltName) == 0x130);

// The record slot 4 fills for the dialog list.
struct MenusSaveListInfo
{
    wchar_t Description[0x80];  // +0x000
    char    Name[0x20];         // +0x100
    int     ScenarioNumber;     // +0x120
    char    _pad124[4];
    wchar_t House[0x30];        // +0x128
    char    _pad188[0x20];
    int     Campaign;           // +0x1A8
    int     Field1AC;           // +0x1AC
    int     Field1B0;           // +0x1B0
    bool    ReadOk;             // +0x1B4
    bool    NotDefault;         // +0x1B5
    char    _pad1B6[2];
    int     GameType;           // +0x1B8
};
GG_STATIC_ASSERT(offsetof(MenusSaveListInfo, Name) == 0x100);
GG_STATIC_ASSERT(offsetof(MenusSaveListInfo, ScenarioNumber) == 0x120);
GG_STATIC_ASSERT(offsetof(MenusSaveListInfo, House) == 0x128);
GG_STATIC_ASSERT(offsetof(MenusSaveListInfo, Campaign) == 0x1A8);
GG_STATIC_ASSERT(offsetof(MenusSaveListInfo, Field1AC) == 0x1AC);
GG_STATIC_ASSERT(offsetof(MenusSaveListInfo, Field1B0) == 0x1B0);
GG_STATIC_ASSERT(offsetof(MenusSaveListInfo, ReadOk) == 0x1B4);
GG_STATIC_ASSERT(offsetof(MenusSaveListInfo, NotDefault) == 0x1B5);
GG_STATIC_ASSERT(offsetof(MenusSaveListInfo, GameType) == 0x1B8);

// VTABLE: GAMEMD 0x7ED2E4
class LoadOptionsClass
{
public:
    virtual ~LoadOptionsClass();                                            // 0x55A0D0 (scalar deleting); body 0x558790
    virtual bool Slot1(const char* fileName);                               // 0x559D60
    virtual bool Slot2(const char* fileName, const wchar_t* description);   // 0x559E40
    virtual bool DeleteMission(const char* fileName);                       // 0x559EB0
    virtual bool Slot4(MenusSaveListInfo* out, FileEntryClass* entry);      // 0x559ED0
    virtual const wchar_t* Slot5();                                         // 0x55A050
    virtual const wchar_t* Slot6();                                         // 0x55A070
    virtual const wchar_t* Slot7();                                         // 0x55A090
    virtual const wchar_t* Slot8();                                         // 0x55A0B0

    int            Mode;         // +0x04
    const char*    Extension;    // +0x08
    const wchar_t* Description;  // +0x0C
    int            Field10;      // +0x10
    int            Field14;      // +0x14
    char           _pad018[8];
    DynamicVectorClass<FileEntryClass*> Entries;  // +0x20

    // FUNCTION: GAMEMD 0x558740 (native constructor)
    LoadOptionsClass();

    bool LoadDialog();                  // GAMEMD 0x5587F0 __thiscall
    bool ProcessDialog();               // GAMEMD 0x558DD0 (worker, declared)
    // FUNCTION: GAMEMD 0x558810 (declaration)
    char FUN_00558810(const wchar_t* a1);
    // FUNCTION: GAMEMD 0x559C20 (decl; reloc) -- scans the save directory for this->Extension; bool result.
    bool FUN_00559C20();
};
GG_STATIC_ASSERT(offsetof(LoadOptionsClass, Mode) == 0x04);
GG_STATIC_ASSERT(offsetof(LoadOptionsClass, Extension) == 0x08);
GG_STATIC_ASSERT(offsetof(LoadOptionsClass, Description) == 0x0C);
GG_STATIC_ASSERT(offsetof(LoadOptionsClass, Field10) == 0x10);
GG_STATIC_ASSERT(offsetof(LoadOptionsClass, Field14) == 0x14);
GG_STATIC_ASSERT(offsetof(LoadOptionsClass, Entries) == 0x20);
GG_STATIC_ASSERT(sizeof(LoadOptionsClass) == 0x38);

#endif  // GG_MATCH_LAYOUT_LOAD_OPTIONS_CLASS_H
