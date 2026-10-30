#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Obj_00558810;

// GLOBAL: GAMEMD 0xA8B230
extern int DAT_00A8B230;


// Retail PAVFileEntryClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

#include "../core/vector_class_operations.h"

class FileEntryClass;

// VTABLE: GAMEMD 0x7ED32C -- VectorClass<FileEntryClass*>.
template class VectorClass<FileEntryClass*>;
typedef VectorClass<FileEntryClass*> GgFileEntryClassVectorClass;
GG_STATIC_ASSERT(offsetof(GgFileEntryClassVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgFileEntryClassVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgFileEntryClassVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgFileEntryClassVectorClass, IsAllocated) == 0x0D);

// VTABLE: GAMEMD 0x7ED30C -- DynamicVectorClass<FileEntryClass*>.
template class DynamicVectorClass<FileEntryClass*>;
typedef DynamicVectorClass<FileEntryClass*> GgFileEntryClassDynamicVectorClass;
GG_STATIC_ASSERT(offsetof(GgFileEntryClassDynamicVectorClass, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgFileEntryClassDynamicVectorClass, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgFileEntryClassDynamicVectorClass, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgFileEntryClassDynamicVectorClass, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgFileEntryClassDynamicVectorClass, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgFileEntryClassDynamicVectorClass, CapacityIncrement) == 0x14);

GG_STATIC_ASSERT(sizeof(FileEntryClass*) == 4);

// FUNCTION: GAMEMD 0x558DD0 (decl; reloc)
int FUN_00558DD0(Obj_00558810*, int);

struct Obj_00558810
{
    char unknown_00[0x4];
    int unknown_04;   // +0x0004
    char unknown_08[0x4];
    int unknown_0C;   // +0x000C
};
GG_STATIC_ASSERT(offsetof(Obj_00558810, unknown_04) == 0x4);
GG_STATIC_ASSERT(offsetof(Obj_00558810, unknown_0C) == 0xC);


// FUNCTION: GAMEMD 0x558810
int FUN_00558810(Obj_00558810* a1, int a2, int a3);

// FUNCTION: GAMEMD 0x558810
// Branching.
int FUN_00558810(Obj_00558810* a1, int a2, int a3)
{
    a1->unknown_04 = 2;
    if (a3 == 0)
    {
        a1->unknown_0C = DAT_00A8B230 + 0x1360;
        return FUN_00558DD0(a1, a2);
    }
    a1->unknown_0C = a3;
    return FUN_00558DD0(a1, a2);
}

// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit LoadDlg.CPP. The name is the source-file string at 0x829f5c
//   in retail gamemd.exe v1.001, passed by the assert at 0x558e6f inside this object's
//   code range (0x558550-0x55a4cf). Functions are in ascending retail address order.
//
// LoadOptionsClass entries (layout and evidence: menus_load_options.h).
// LIBRARY: GAMEMD 0x7C8B3D -- operator delete; GAMEMD 0x7C8D20 -- _stricmp; GAMEMD 0x7CA489 -- _wcscpy.

#include <string.h>
#include "input_controls/menus_load_options.h"

static const char LoadDlgFile[] = "D:\\ra2mdpost\\LoadDlg.CPP";

// FUNCTION: GAMEMD 0x558740
// Start with no mission mode or description, the "SAV" extension and a 0x800 field, and an empty
// entry list (cleared through its vtable, as the constructor leaves it).
LoadOptionsClass::LoadOptionsClass()
{
    Mode = 0;
    Description = 0;
    Field14 = 0;
    Extension = "SAV";
    Field10 = 0x800;
    Entries.Clear();
}

// FUNCTION: GAMEMD 0x558790
// PARTIAL: 94.9% -- same instructions as retail; cl stores the vtable pointer after loading the entry count,
// where retail stores it first (ten loop spellings tried, including the earlier six on the deleting copy).
// Release every list entry, then clear the vector (its base destructor then runs inline).
LoadOptionsClass::~LoadOptionsClass()
{
    for (int i = 0; i < Entries.Count; ++i)
        delete Entries.Items[i];
    Entries.Clear();
}

// SYNTHETIC: GAMEMD 0x55A0D0
// LoadOptionsClass::scalar deleting destructor (compiler-generated ??_G; scored from the harness, see menus.rows.tsv)
// CAPPED at 95.5% (42 of 44 instructions; multiset identical). Retail stores the vtable (`MOV [EDI],0x7ED2E4`)
// before it loads the entry count (`MOV EAX,[EDI+0x30]`); cl loads the count first. Six loop spellings
// (for, while, loop variable outside, element copied to a local, `if (Count > 0) do/while`, `Count > i`) all
// give the same two-instruction swap or worse. The destructor is inline in menus_load_options.h.

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7ED2D0
extern const double DAT_007ED2D0;
// GLOBAL: GAMEMD 0xABCBE0
extern double DAT_00ABCBE0;
// GLOBAL: GAMEMD 0xABCC20
extern int DAT_00ABCC20;
// GLOBAL: GAMEMD 0xABCC24
extern int DAT_00ABCC24;
// GLOBAL: GAMEMD 0xABCC28
extern int DAT_00ABCC28;

// dynamic initializer for DAT_00ABCC30
// GLOBAL: GAMEMD 0x00ABCC30
extern double DAT_00ABCC30;

// dynamic initializer for DAT_00ABCC18
// GLOBAL: GAMEMD 0x00ABCC18
extern double DAT_00ABCC18;

GG_STATIC_ASSERT(sizeof(DAT_00ABCC30) == 8);
GG_STATIC_ASSERT(sizeof(DAT_00ABCC18) == 8);

// FUNCTION: GAMEMD 0x559D60
// Runs the loading dialog around the game load: the cursor count is saved, the dialog shown, and the
// count restored afterwards.
bool LoadOptionsClass::Slot1(const char* fileName)
{
    int cursorCount = DAT_00887640->GetCursorCount();
    void* dialog = MenusShowDialog(MenusGetText("TXT_LOADING", 0, LoadDlgFile, 0x41C), 0, 0);
    DAT_00887640->HideCursor();
    if (dialog)
        MenusFocusOnWindow(dialog);
    MenusLoadFlagA = false;
    MenusLoadFlagB = false;
    MenusSessionInstance.Func_69BB40();
    bool ok = MenusLoadGame(fileName);
    while (DAT_00887640->GetCursorCount() < cursorCount)
        DAT_00887640->ShowCursor();
    while (DAT_00887640->GetCursorCount() > cursorCount)
        DAT_00887640->HideCursor();
    if (dialog)
        MenusEndDialog(dialog);
    return ok;
}

// FUNCTION: GAMEMD 0x559E40
bool LoadOptionsClass::Slot2(const char* fileName, const wchar_t* description)
{
    void* dialog = MenusShowDialog(MenusGetText("TXT_SAVING_GAME", 0, LoadDlgFile, 0x453), 0, 0);
    DAT_00887640->HideCursor();
    if (dialog)
        MenusFocusOnWindow(dialog);
    bool ok = MenusSaveGame(fileName, description, 0);
    DAT_00887640->ShowCursor();
    if (dialog)
        MenusEndDialog(dialog);
    return ok;
}

// FUNCTION: GAMEMD 0x559ED0
// Fills a list record from a save-game file entry; false for the network save or an unreadable header.
bool LoadOptionsClass::Slot4(MenusSaveListInfo* out, FileEntryClass* entry)
{
    if (out != 0 || entry != 0) {
        if (stricmp(entry->FileName, "SAVEGAME.NET") != 0) {
            MenusSaveHeader header;
            bool ok = MenusReadFromFile(entry->FileName, &header);
            if (ok) {
                if (header.GetPad0() != MenusDefaultHeaderPad) {
                    wcscpy(out->Description, header.GetDescription());
                    out->NotDefault = true;
                } else {
                    wcscpy(out->Description, header.GetDescription());
                    out->NotDefault = false;
                }
                out->ReadOk = ok;
                out->ScenarioNumber = header.FUN_00681140();
                out->Campaign = header.GetCampaign();
                out->GameType = header.GetGameType();
                strcpy(out->Name, entry->FileName);
                wcscpy(out->House, header.FUN_00681100());
                if (strlen(out->Name) == 0)
                    strcpy(out->Name, entry->AltName);
                out->Field1B0 = entry->Field18;
                out->Field1AC = entry->Field14;
                return true;
            }
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x55A050
const wchar_t* LoadOptionsClass::Slot5()
{
    return MenusGetText("GUI:LoadMissionMenu", 0, LoadDlgFile, 0x4C0);
}

// FUNCTION: GAMEMD 0x55A070
const wchar_t* LoadOptionsClass::Slot6()
{
    return MenusGetText("GUI:SaveMissionMenu", 0, LoadDlgFile, 0x4C6);
}

// FUNCTION: GAMEMD 0x55A090
const wchar_t* LoadOptionsClass::Slot7()
{
    return MenusGetText("GUI:DeleteMissionMenu", 0, LoadDlgFile, 0x4CC);
}

// FUNCTION: GAMEMD 0x55A0B0
const wchar_t* LoadOptionsClass::Slot8()
{
    return MenusGetText("TXT_GAME_WAS_SAVED", 0, LoadDlgFile, 0x4D2);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x55A150
// DynamicVectorClass<FileEntryClass*>::Clear

// FUNCTION: GAMEMD 0x55A180
// DynamicVectorClass<FileEntryClass*>::Slot5

// FUNCTION: GAMEMD 0x55A1A0
// VectorClass<FileEntryClass*>::Slot6

// FUNCTION: GAMEMD 0x55A1B0
// VectorClass<FileEntryClass*>::operator==

// FUNCTION: GAMEMD 0x55A1F0
// VectorClass<FileEntryClass*>::SetCapacity

// FUNCTION: GAMEMD 0x55A2A0
// VectorClass<FileEntryClass*>::Clear

// FUNCTION: GAMEMD 0x55A2D0
// VectorClass<FileEntryClass*>::FindItemIndex

// FUNCTION: GAMEMD 0x55A310
// VectorClass<FileEntryClass*>::Slot5

// FUNCTION: GAMEMD 0x55A330
// DynamicVectorClass<FileEntryClass*>::SetCapacity

// FUNCTION: GAMEMD 0x55A3E0
// DynamicVectorClass<FileEntryClass*>::FindItemIndex

// SYNTHETIC: GAMEMD 0x55A410
// VectorClass<FileEntryClass*>::scalar deleting destructor

// SYNTHETIC: GAMEMD 0x55A460
// DynamicVectorClass<FileEntryClass*>::scalar deleting destructor

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0xA8ED5C
bool MenusLoadFlagA;
// GLOBAL: GAMEMD 0xA8E378
bool MenusLoadFlagB;
// END defined globals
