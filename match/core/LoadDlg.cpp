// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit LoadDlg.CPP. The name is the source-file string at 0x829f5c
//   in retail gamemd.exe v1.001, passed by the assert at 0x558e6f inside this object's
//   code range (0x558550-0x55a4cf). Functions are in ascending retail address order.
//
// LoadOptionsClass entries (layout and evidence: menus_load_options.h).
// LIBRARY: GAMEMD 0x7C8B3D -- operator delete; GAMEMD 0x7C8D20 -- _stricmp; GAMEMD 0x7CA489 -- _wcscpy.

#include <string.h>
#include "../ui/input_controls/menus_load_options.h"

static const char LoadDlgFile[] = "D:\\ra2mdpost\\LoadDlg.CPP";

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

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7ED2D0
extern const double DAT_007ED2D0;
// GLOBAL: GAMEMD 0xABCBE0
extern double DAT_00ABCBE0;
// GLOBAL: GAMEMD 0xABCC18
extern double DAT_00ABCC18;
// GLOBAL: GAMEMD 0xABCC20
extern int DAT_00ABCC20;
// GLOBAL: GAMEMD 0xABCC24
extern int DAT_00ABCC24;
// GLOBAL: GAMEMD 0xABCC28
extern int DAT_00ABCC28;
// GLOBAL: GAMEMD 0xABCC30
extern double DAT_00ABCC30;

// FUNCTION: GAMEMD 0x558580
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_00558580()
{
    DAT_00ABCC30 = DAT_00ABCBE0 / DAT_007ED2D0;
}

// FUNCTION: GAMEMD 0x5585A0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_005585A0()
{
    DAT_00ABCC18 = DAT_007E1718 / DAT_00ABCC30;
}

// FUNCTION: GAMEMD 0x558720
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_00558720()
{
    DAT_00ABCC28 = 0;
    DAT_00ABCC20 = 0x80;
    DAT_00ABCC24 = 0x80;
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
