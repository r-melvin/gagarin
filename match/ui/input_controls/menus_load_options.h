// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Menus cluster view of LoadOptionsClass (UI input/controls module). Read from the retail gamemd.exe
//   v1.001: RTTI .?AVLoadOptionsClass@@ (vtable 0x7ED2E4, no base), the constructor 0x558740 (the
//   +0x04/+0x08/+0x0C/+0x10/+0x14 stores and the DynamicVectorClass<FileEntryClass*> at +0x20, vtable
//   0x7ED30C), the destructor body 0x55A0D0 and the method bodies in menus_load_options.cpp.
//
//   Address-scoped view: the class name is the true name, but this header is NOT to be included together
//   with match/ui/load_options_class_methods.h (it adds the vtable and the members that the existing view
//   models as a bare pointer). The integrator consolidates. The class has no allocation site in this
//   cluster, so its size is not asserted (offsets only).
//
//   Calling conventions: the census labelled the 0x559xxx slots __stdcall, but the bodies never touch
//   `this`: slot 1 takes one stack argument (RET 4), slots 2 and 4 take two (RET 8) and each loads the
//   arguments from the first stack slots, so they are __thiscall with unused ECX (the existing exact
//   0x559EB0 DeleteMission, RET 4 with the file name at [ESP+4], sits in slot 3 the same way).
#ifndef GG_MATCH_UI_INPUT_CONTROLS_MENUS_LOAD_OPTIONS_H
#define GG_MATCH_UI_INPUT_CONTROLS_MENUS_LOAD_OPTIONS_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "../../core/vector_class.h"
#include "ui_common.h"

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

// The savegame header record read by 0x67FD20. Constructed by 0x680FF0; the getters are the exact
// 0x681090 / 0x6810C0 / 0x681100 / 0x681120 / 0x681140 / 0x6812D0 methods.
struct MenusSaveHeader
{
    MenusSaveHeader();                         // 0x680FF0
    void* GetPad0() const;                     // 0x681090
    const wchar_t* GetDescription() const;     // 0x6810C0
    const wchar_t* FUN_00681100() const;     // 0x681100
    int GetCampaign() const;                   // 0x681120
    int FUN_00681140() const;             // 0x681140
    int GetGameType() const;                   // 0x6812D0
    char _pad[0x3F4];
};

// SessionClass::Instance (0xA8B238).
struct MenusSession
{
    void Func_69BB40();
};

// GLOBAL: GAMEMD 0xA8B238 -- SessionClass::Instance.
extern MenusSession MenusSessionInstance;
// GLOBAL: GAMEMD 0xA8ED5C / 0xA8E378 -- two flag bytes cleared before a load.
extern bool MenusLoadFlagA;
extern bool MenusLoadFlagB;
// GLOBAL: GAMEMD 0x83D560 -- compared with the header's pad word.
extern void* MenusDefaultHeaderPad;

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- __fastcall(label ECX, index-out EDX, file, line), RET 8.
const wchar_t* MenusGetText(const char* label, int* index, const char* file, int line);
// FUNCTION: GAMEMD 0x623230 (decl; reloc) -- __fastcall(text ECX, EDX, one stack word), RET 4; returns the
// dialog handle. Every caller here passes zero for both.
void* MenusShowDialog(const wchar_t* text, int a, int b);
// FUNCTION: GAMEMD 0x622800 (decl; reloc) -- the existing exact UI::FocusOnWindow, __fastcall(handle).
void MenusFocusOnWindow(void* handle);
// FUNCTION: GAMEMD 0x622720 (decl; reloc) -- the existing exact UI::EndDialog, __fastcall(handle).
void MenusEndDialog(void* handle);
// FUNCTION: GAMEMD 0x67E440 (decl; reloc) -- __fastcall(file name ECX), returns the load result.
bool MenusLoadGame(const char* fileName);
// FUNCTION: GAMEMD 0x67CEF0 (decl; reloc) -- __fastcall(file name ECX, description EDX, 0), RET 4.
bool MenusSaveGame(const char* fileName, const wchar_t* description, int zero);
// FUNCTION: GAMEMD 0x67FD20 (decl; reloc) -- the existing exact ReadFromFile, __fastcall(file name, header).
bool MenusReadFromFile(const char* fileName, MenusSaveHeader* header);

// VTABLE: GAMEMD 0x7ED2E4
class LoadOptionsClass
{
public:
    virtual ~LoadOptionsClass()
    {
        for (int i = 0; i < Entries.Count; ++i)
            delete Entries.Items[i];
        Entries.Clear();
    }
    virtual bool Slot1(const char* fileName);                               // 0x559D60
    virtual bool Slot2(const char* fileName, const wchar_t* description);   // 0x559E40
    virtual bool DeleteMission(const char* fileName);                       // 0x559EB0 (existing exact, static __stdcall view)
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
};
GG_STATIC_ASSERT(offsetof(LoadOptionsClass, Mode) == 0x04);
GG_STATIC_ASSERT(offsetof(LoadOptionsClass, Extension) == 0x08);
GG_STATIC_ASSERT(offsetof(LoadOptionsClass, Description) == 0x0C);
GG_STATIC_ASSERT(offsetof(LoadOptionsClass, Field10) == 0x10);
GG_STATIC_ASSERT(offsetof(LoadOptionsClass, Entries) == 0x20);

#endif  // GG_MATCH_UI_INPUT_CONTROLS_MENUS_LOAD_OPTIONS_H
