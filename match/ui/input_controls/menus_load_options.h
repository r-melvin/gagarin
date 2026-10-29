// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Menus cluster view of LoadOptionsClass (UI input/controls module). Read from the retail gamemd.exe
//   v1.001: RTTI .?AVLoadOptionsClass@@ (vtable 0x7ED2E4, no base), the constructor 0x558740 (the
//   +0x04/+0x08/+0x0C/+0x10/+0x14 stores and the DynamicVectorClass<FileEntryClass*> at +0x20, vtable
//   0x7ED30C), the destructor body 0x55A0D0 and the method bodies in menus_load_options.cpp.
//
//   LoadOptionsClass itself, FileEntryClass and MenusSaveListInfo now live in the canonical
//   match/_layout/load_options_class.h; this header keeps the cluster's save-header record and helpers.
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
#include "../../_layout/load_options_class.h"

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

#endif  // GG_MATCH_UI_INPUT_CONTROLS_MENUS_LOAD_OPTIONS_H
