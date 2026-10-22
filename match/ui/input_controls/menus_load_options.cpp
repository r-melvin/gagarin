// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//
// LoadOptionsClass entries (layout and evidence: menus_load_options.h).
// LIBRARY: GAMEMD 0x7C8B3D -- operator delete; GAMEMD 0x7C8D20 -- _stricmp; GAMEMD 0x7CA489 -- _wcscpy.

#include <string.h>
#include "menus_load_options.h"

static const char LoadDlgFile[] = "D:\\ra2mdpost\\LoadDlg.CPP";

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
                out->ScenarioNumber = header.GetScenarioNumber();
                out->Campaign = header.GetCampaign();
                out->GameType = header.GetGameType();
                strcpy(out->Name, entry->FileName);
                wcscpy(out->House, header.GetPlayerHouse());
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

// SYNTHETIC: GAMEMD 0x55A0D0
// LoadOptionsClass::scalar deleting destructor (compiler-generated ??_G; scored from the harness, see menus.rows.tsv)
// CAPPED at 95.5% (42 of 44 instructions; multiset identical). Retail stores the vtable (`MOV [EDI],0x7ED2E4`)
// before it loads the entry count (`MOV EAX,[EDI+0x30]`); cl loads the count first. Six loop spellings
// (for, while, loop variable outside, element copied to a local, `if (Count > 0) do/while`, `Count > i`) all
// give the same two-instruction swap or worse. The destructor is inline in menus_load_options.h.
