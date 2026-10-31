#include "../FUNCTION.H"
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Retail PAVFileEntryClass RTTI establishes the pointer element type and zero-offset
// DynamicVectorClass -> VectorClass base chain. Complete entry-origin spans
// establish the bound methods. GX emits a short derived deleting wrapper;
// no GX reproduces its full retail body. No TypeList or constructor is bound;
// original TU boundaries, final link and complete object sizes are unknown.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

#include "../core/vector_class_operations.h"
#include "../platform/window_moving_methods.h"

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
#include "../core/scenario_class.h"
#include "../_layout/scenario_ptr_00a8b230.h"

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

// The Win32 file-delete import. Retail calls it indirectly through the IAT
// (`call dword ptr [__imp__DeleteFileA@4]`); declaring it dllimport makes our
// cl emit the identical `ff 15` form (reloc-normalised by the differ).
extern "C" __declspec(dllimport) int __stdcall DeleteFileA(const char* lpFileName);

// FUNCTION: GAMEMD 0x5587F0  (__thiscall)
// Open the savegame browser in Load mode: set Mode=Load, clear the Save
// Description, then tail-call the shared dialog worker (0x558DD0), whose bool
// result becomes ours.
bool LoadOptionsClass::LoadDialog()
{
    this->Mode = LOM_Load;
    this->Description = 0;
    return this->ProcessDialog();
}

// FUNCTION: GAMEMD 0x558810
// Load dialog entry: mode 2 with the given description, or the current scenario's name when none is given.
char LoadOptionsClass::FUN_00558810(const wchar_t* a1)
{
    Mode = 2;
    if (a1 == 0)
        a1 = DAT_00A8B230->unknown_1360;
    Description = a1;
    return ProcessDialog();
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
#include "../_layout/load_options_class.h"
#include <windows.h>

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

struct SavedGameEntry_00559D30 {
    char unknown_00[0x1AC];
    FILETIME LastWrite;   // +0x1AC
};
GG_STATIC_ASSERT(offsetof(SavedGameEntry_00559D30, LastWrite) == 0x1AC);

// FUNCTION: GAMEMD 0x622B50 (decl; reloc) -- the shared dialog handler.
int __fastcall FUN_00622B50(HWND h, UINT msg, WPARAM w, LPARAM l);
// FUNCTION: GAMEMD 0x607FD0 (decl; reloc)
void FUN_00607FD0(HWND h);

// FUNCTION: GAMEMD 0x558A30
// PARTIAL: 81.2% -- same instruction multiset except two je/jne pairs: retail tests the three
// command ids with forward je branches and bodies out of line; an if-chain nests them
// (a switch on the id adds two register copies, 7.9%).
// Dialog procedure: after the shared handler, repaint, clamp the window while
// it is being moved, record the chosen command and prime the list control.
int __stdcall FUN_00558A30(HWND h, UINT msg, WPARAM w, LPARAM l)
{
    int r = FUN_00622B50(h, msg, w, l);
    if (r == 0) {
        switch (msg) {
        case 0x111: {
            unsigned int notify = w >> 16;
            int id = w & 0xFFFF;
            int* data = (int*)GetWindowLongA(h, 8);
            if (id == 0x40F) {
                if (notify == 0) {
                    data[6] = 0x40F;
                    return 0;
                }
            } else if (id == 0x525) {
                if (notify == 2) {
                    LRESULT count = SendMessageA((HWND)l, 0x18B, 0, 0);
                    if (count > 0) {
                        data[6] = 0x40F;
                        return 0;
                    }
                }
            } else if (id == 0x686) {
                data[6] = 2;
                return 0;
            }
            break;
        }
        case 0xF:
            FUN_00607FD0(h);
            return 1;
        case 0x216:
            return OnWindowMoving(h, w, (Rect_00776D80*)l);
        case 0x497:
            SendDlgItemMessageA(h, 0x525, 0x4A6, 0xF9, 2);
            SendDlgItemMessageA(h, 0x525, 0x4A6, 0x38, 0xFF);
            SendDlgItemMessageA(h, 0x525, 0x4A6, 0, 0x13B);
            break;
        }
        r = 0;
    }
    return r;
}

// FUNCTION: GAMEMD 0x5588E0 (decl; reloc)
void FUN_005588E0(HWND h, unsigned int id, LPARAM control, unsigned int notify);

// FUNCTION: GAMEMD 0x558B90
// Dialog procedure: repaint, clamp the window while it is being moved,
// forward commands, prime both list controls and latch the result code.
int __stdcall FUN_00558B90(HWND h, UINT msg, WPARAM w, LPARAM l)
{
    int r = FUN_00622B50(h, msg, w, l);
    if (r == 0) {
        switch (msg) {
        case 0x111:
            FUN_005588E0(h, w & 0xFFFF, l, w >> 16);
            return 0;
        case 0xF:
            FUN_00607FD0(h);
            return 1;
        case 0x216:
            return OnWindowMoving(h, w, (Rect_00776D80*)l);
        case 0x497: {
            SendMessageA(GetDlgItem(h, 0x526), 0xC5, 0x4F, 0);
            SendDlgItemMessageA(h, 0x527, 0x4A6, 0xF9, 2);
            SendDlgItemMessageA(h, 0x527, 0x4A6, 0x38, 0xFF);
            SendDlgItemMessageA(h, 0x527, 0x4A6, 0, 0x13B);
            break;
        }
        case 0x4DA: {
            int* data = (int*)GetWindowLongA(h, 8);
            data[6] = 1;
            return 0;
        }
        }
        r = 0;
    }
    return r;
}


// FUNCTION: GAMEMD 0x558CB0
// Dialog procedure: after the shared handler, clamp the window while it is
// being moved, repaint, set the result code for two buttons and prime the
// list control's three settings.
int __stdcall FUN_00558CB0(HWND h, UINT msg, WPARAM w, LPARAM l)
{
    int r = FUN_00622B50(h, msg, w, l);
    if (r == 0) {
        switch (msg) {
        case 0x111: {
            unsigned int notify = w >> 16;
            int* data = (int*)GetWindowLongA(h, 8);
            switch (w & 0xFFFF) {
            case 0x686:
                if (notify == 0) {
                    data[6] = 2;
                    return 0;
                }
                break;
            case 0x6C8:
                if (notify == 0) {
                    data[6] = 1;
                    return 0;
                }
                break;
            }
            break;
        }
        case 0xF:
            FUN_00607FD0(h);
            return 1;
        case 0x216:
            return OnWindowMoving(h, w, (Rect_00776D80*)l);
        case 0x497:
            SendDlgItemMessageA(h, 0x528, 0x4A6, 0xF9, 2);
            SendDlgItemMessageA(h, 0x528, 0x4A6, 0x38, 0xFF);
            SendDlgItemMessageA(h, 0x528, 0x4A6, 0, 0x13B);
            break;
        }
        r = 0;
    }
    return r;
}

// FUNCTION: GAMEMD 0x559D30
int __cdecl FUN_00559D30(SavedGameEntry_00559D30** a, SavedGameEntry_00559D30** b)
{
    const FILETIME* left = &(*a)->LastWrite;
    const FILETIME* right = &(*b)->LastWrite;
    return -CompareFileTime(left, right);
}

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

// FUNCTION: GAMEMD 0x559EB0  (__thiscall, vtable slot 3; ECX unused)
// Delete one savegame file; report success only when DeleteFileA returns
// exactly 1 (TRUE).
bool LoadOptionsClass::DeleteMission(const char* pFilename)
{
    // Bind the comparison to a bool local so cl emits the lean `cmp eax,1;
    // sete al` tail (retail's exact form) instead of the branchless
    // dec/neg/sbb/inc equality idiom it picks when `== 1` is returned inline.
    bool succeeded = (DeleteFileA(pFilename) == 1);
    return succeeded;
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
