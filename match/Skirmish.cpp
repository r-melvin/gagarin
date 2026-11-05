// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit Skirmish.cpp. The name is the source-file string at 0x83fc4c
//   in retail gamemd.exe v1.001, passed by the assert at 0x6acc2a inside this object's
//   code range (0x6ac970-0x6aef0f). Functions are in ascending retail address order.

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "mathtbl_init_shapes.h"
#include "_rt/gg_static_assert.h"
#include "multiplayer_game_mode.h"
#include "netshare_win.h"
#include "_layout/session_class.h"
#include "_layout/house_type_class.h"
#include "_layout/rules_class.h"
#include "session_entry.h"
#include "wide_string_class.h"
#include "_layout/query_00603f00.h"
#include "ui_updated_methods.h"
#include "vtable_seating_ctor_family_methods.h"

// GLOBAL: GAMEMD 0x7F3138
extern const double DAT_007F3138;
// GLOBAL: GAMEMD 0xB0B540
extern double DAT_00B0B540;
// GLOBAL: GAMEMD 0xB0B578
extern double DAT_00B0B578;
// GLOBAL: GAMEMD 0xB0B590
extern double DAT_00B0B590;

// SYNTHETIC: GAMEMD 0x006AC9A0
// dynamic initializer for DAT_00B0B590

// GLOBAL: GAMEMD 0x00B0B590
double DAT_00B0B590 = DAT_00B0B540 / DAT_007F3138;

// SYNTHETIC: GAMEMD 0x006AC9C0
// dynamic initializer for DAT_00B0B578

// GLOBAL: GAMEMD 0x00B0B578
double DAT_00B0B578 = 1.0 / DAT_00B0B590;

// SYNTHETIC: GAMEMD 0x006ACB40
// GLOBAL: GAMEMD 0x00B0B580
MathTblCoord DAT_00B0B580;

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x7F3138
extern const double DAT_007F3138 = 60.0;
// END defined globals

// GLOBAL: GAMEMD 0xA8B23C
extern MultiplayerGameMode* DAT_00A8B23C;

// GLOBAL: GAMEMD 0xB0B59C -- the lobby dialog while it runs.
extern HWND DAT_00B0B59C;

// FUNCTION: GAMEMD 0x775940 (decl; reloc) -- __fastcall (id): a dialog handle, or null.
HWND FUN_00775940(int id);

// The combo control of a seat (seat 0 is slot 1), or -1.
static inline int Seat_Combo(int seat)
{
    if (seat == 0)
        return 0x50B;
    if (seat == 1)
        return 0x50E;
    if (seat == 2)
        return 0x516;
    if (seat == 3)
        return 0x51A;
    if (seat == 4)
        return 0x51B;
    if (seat == 5)
        return 0x51C;
    return seat == 6 ? 0x51D : -1;
}

// FUNCTION: GAMEMD 0x4E3320 (decl; reloc) -- the name control of a slot index.
int FUN_004E3320(int index);

// FUNCTION: GAMEMD 0x6ACCA0
bool __fastcall FUN_006ACCA0(int count)
{
    HWND dialog = DAT_00B0B59C;
    if (count < 8) {
        int slot = count;
        do {
            int combo = Seat_Combo(slot - 1);
            int selected = SendDlgItemMessageA(dialog, combo, 0x147, 0, 0);
            int kind = SendDlgItemMessageA(dialog, combo, 0x150, selected, 0);
            if (kind == 0 || kind == 1 || kind == 2) {
                return true;
            }
            slot++;
        } while (slot < 8);
    }
    return false;
}

// FUNCTION: GAMEMD 0x6ACD60
void __fastcall FUN_006ACD60(HWND dialog)
{
    if (dialog == 0) {
        dialog = FUN_00775940(0x102);
    }
    bool allies = false;
    if (DAT_00A8B23C) {
        allies = DAT_00A8B23C->AlliesAllowed;
    }
    HWND item = GetDlgItem(dialog, 0x76D);
    if (item) {
        if (allies)
            EnableWindow(item, 1);
        else
            EnableWindow(item, 0);
        for (int slot = 1; slot < 8; slot++) {
            int combo = Seat_Combo(slot - 1);
            int selected = SendDlgItemMessageA(dialog, combo, 0x147, 0, 0);
            int kind = SendDlgItemMessageA(dialog, combo, 0x150, selected, 0);
            int control = FUN_004E5940(slot);
            if (control >= 0) {
                item = GetDlgItem(dialog, control);
                if (item) {
                    if (kind == -1)
                        EnableWindow(item, 0);
                    else if (!allies)
                        EnableWindow(item, 0);
                    else
                        EnableWindow(item, 1);
                }
            }
        }
    }
}

// FUNCTION: GAMEMD 0x6ACE80
void __fastcall FUN_006ACE80(HWND dialog, int count)
{
    if (dialog && DAT_00A8B23C) {
        int first = 1;
        int last = 8;
        if (count > 0 && count < last) {
            first = count;
            last = count + 1;
        }
        for (int i = first; i < last; i++) {
            int control = FUN_004E5940(i);
            if (DAT_00A8B23C && DAT_00A8B23C->AlliesAllowed)
                FUN_004E5ED0(dialog, control, 3);
            else
                FUN_004E5ED0(dialog, control, -2);
        }
    }
}

// FUNCTION: GAMEMD 0x6ADC20 (decl; reloc) -- refresh one seat's controls from its combo selection.
void __fastcall FUN_006ADC20(HWND dialog, int combo);

void __fastcall FUN_006ADF00(HWND dialog, int first, int count);
void __fastcall FUN_006AE080(HWND dialog, int first);

// FUNCTION: GAMEMD 0x6ADDF0
void __fastcall FUN_006ADDF0(HWND dialog, int from, int to)
{
    int fromCount;
    if (from == -1) {
        fromCount = 8;
    } else {
        fromCount = FUN_005E6520(from);
    }
    int toCount = FUN_005E6520(to);
    int delta = toCount - fromCount;
    if (from >= 0 && to >= 0 && from < Session_00A8B238.unknown_690.Count && to < Session_00A8B238.unknown_690.Count) {
        bool fromRandom = Session_00A8B238.unknown_690.Items[from]->FUN_0069ADF0();
        bool toRandom = Session_00A8B238.unknown_690.Items[to]->FUN_0069ADF0();
        if (fromRandom && toRandom) {
            FUN_006AE080(dialog, 1);
            FUN_006ADF00(dialog, 1, toCount - 1);
        }
    }
    if (delta > 0) {
        FUN_006ADF00(dialog, fromCount, delta);
    } else if (delta < 0) {
        FUN_006AE080(dialog, toCount);
    }
    FUN_006ACE80(dialog, 0);
}

// FUNCTION: GAMEMD 0x6ADF00
void __fastcall FUN_006ADF00(HWND dialog, int first, int count)
{
    int last = first + count;
    for (int slot = first; slot < last; slot++) {
        int combo = Seat_Combo(slot - 1);
        int name = FUN_004E3320(slot);
        int house = FUN_004E41D0(slot);
        int start = FUN_004E37D0(slot);
        int colour = FUN_004E4E60(slot);
        int team = FUN_004E5940(slot);
        HWND comboItem = GetDlgItem(dialog, combo);
        HWND nameItem = GetDlgItem(dialog, name);
        HWND houseItem = GetDlgItem(dialog, house);
        HWND startItem = GetDlgItem(dialog, start);
        HWND colourItem = GetDlgItem(dialog, colour);
        HWND teamItem = GetDlgItem(dialog, team);
        ShowWindow(comboItem, 5);
        ShowWindow(nameItem, 5);
        ShowWindow(houseItem, 5);
        ShowWindow(startItem, 5);
        ShowWindow(colourItem, 5);
        ShowWindow(teamItem, 5);
        FUN_006ADC20(dialog, combo);
    }
}

// FUNCTION: GAMEMD 0x6AE080
void __fastcall FUN_006AE080(HWND dialog, int first)
{
    int slot;
    for (slot = first; slot < 8; slot++) {
        int combo = Seat_Combo(slot - 1);
        int count = SendDlgItemMessageA(dialog, combo, 0x146, 0, 0);
        for (int i = 0; i < count; i++) {
            if (SendDlgItemMessageA(dialog, combo, 0x150, i, 0) == -1) {
                SendDlgItemMessageA(dialog, combo, 0x14E, i, 0);
                break;
            }
        }
        FUN_006ADC20(dialog, combo);
    }
    for (slot = first; slot < 8; slot++) {
        int combo = Seat_Combo(slot - 1);
        int name = FUN_004E3320(slot);
        int start = FUN_004E37D0(slot);
        int house = FUN_004E41D0(slot);
        int colour = FUN_004E4E60(slot);
        int team = FUN_004E5940(slot);
        HWND comboItem = GetDlgItem(dialog, combo);
        HWND nameItem = GetDlgItem(dialog, name);
        HWND startItem = GetDlgItem(dialog, start);
        HWND houseItem = GetDlgItem(dialog, house);
        HWND colourItem = GetDlgItem(dialog, colour);
        HWND teamItem = GetDlgItem(dialog, team);
        ShowWindow(comboItem, 0);
        ShowWindow(nameItem, 0);
        ShowWindow(startItem, 0);
        ShowWindow(houseItem, 0);
        ShowWindow(colourItem, 0);
        ShowWindow(teamItem, 0);
    }
}

// STRING: GAMEMD 0x83FC3C "STT:PlayerNone"
// STRING: GAMEMD 0x831D0C "STT:PlayerDumbAI"
// STRING: GAMEMD 0x831CF8 "STT:PlayerSmartAI"
// STRING: GAMEMD 0x831CE4 "STT:PlayerGeniusAI"

// GLOBAL: GAMEMD 0x83FC4C -- this unit's build path, handed to the label lookup.
extern const char DAT_0083FC4C[];

// GLOBAL: GAMEMD 0xA83C98 -- HouseTypeClass::Array.
extern DynamicVectorClass<HouseTypeClass*> DAT_00A83C98;
// GLOBAL: GAMEMD 0x887048 -- the CCINI the rules were read from.
extern CCINIClass* DAT_00887048;
// GLOBAL: GAMEMD 0x8871E0 -- RulesClass::Instance.
extern RulesClass* DAT_008871E0;
// GLOBAL: GAMEMD 0xAC1154 -- the lobby's map preview.
extern SeatNull_006406E0* DAT_00AC1154;

// FUNCTION: GAMEMD 0x622650 (decl; reloc) -- UI::BeginDialog.
void* UI_BeginDialog(unsigned short id, int (__stdcall* proc)(void*, unsigned, unsigned, long), int arg);
// FUNCTION: GAMEMD 0x622720 (decl; reloc) -- UI::EndDialog.
void UI_EndDialog(void* window);
// FUNCTION: GAMEMD 0x622800 (decl; reloc) -- UI::FocusOnWindow.
void UI_FocusOnWindow(HWND window);
// FUNCTION: GAMEMD 0x532100 (decl; reloc) -- __fastcall, one byte flag.
void FUN_00532100(bool flag);
struct CaptureSurface;
// FUNCTION: GAMEMD 0x52FEC0 (decl; reloc)
void __fastcall FUN_0052FEC0(CaptureSurface* surface, unsigned char repaint);
// FUNCTION: GAMEMD 0x72CF40 (decl; reloc)
void FUN_0072CF40();
// FUNCTION: GAMEMD 0x72CF90 (decl; reloc)
void FUN_0072CF90();
// FUNCTION: GAMEMD 0x622B50 (decl; reloc) -- __fastcall, the shared dialog message filter.
int FUN_00622B50(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
// FUNCTION: GAMEMD 0x6067A0 (decl; reloc) -- __fastcall: a control's flag.
bool FUN_006067A0(int key);
// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- __fastcall string-table lookup.
const wchar_t* FUN_00734E60(const char* label, int* index, const char* file, int line);
// FUNCTION: GAMEMD 0x4E3830 (decl; reloc) -- __fastcall: the slot a start-position control belongs to.
int FUN_004E3830(int control);
// FUNCTION: GAMEMD 0x4E4170 (decl; reloc) -- __fastcall: the start-position control's value, RET 4.
int FUN_004E4170(HWND dialog, int control, int fallback);
// FUNCTION: GAMEMD 0x4E38A0 (decl; reloc) -- the caption of a start position.
const wchar_t* FUN_004E38A0(int index);
// FUNCTION: GAMEMD 0x4E4230 (decl; reloc) -- __fastcall: the slot a house control belongs to.
int FUN_004E4230(int control);
// FUNCTION: GAMEMD 0x4E4E20 (decl; reloc) -- __fastcall: the house control's value, RET 4.
int FUN_004E4E20(HWND dialog, int control, int fallback);
// FUNCTION: GAMEMD 0x4E42A0 (decl; reloc) -- the caption of a house.
const wchar_t* FUN_004E42A0(int index);
// FUNCTION: GAMEMD 0x4E4EC0 (decl; reloc) -- __fastcall: the slot a colour control belongs to.
int FUN_004E4EC0(int control);
// FUNCTION: GAMEMD 0x4E5900 (decl; reloc) -- __fastcall: the colour control's value, RET 4.
int FUN_004E5900(HWND dialog, int control, int fallback);
// FUNCTION: GAMEMD 0x4E4F30 (decl; reloc) -- the caption of a colour.
const wchar_t* FUN_004E4F30(int index);
// FUNCTION: GAMEMD 0x6ACEE0 (decl; reloc) -- the lobby command handler: dialog, control, notifying window, code; RET 8.
void FUN_006ACEE0(HWND dialog, int control, long window, unsigned notify);
// FUNCTION: GAMEMD 0x6AE6E0 (decl; reloc) -- the lobby's custom-message handler; RET 4.
int FUN_006AE6E0(HWND dialog, unsigned wparam, long lparam);

// The lobby dialog procedure, defined below.
int __stdcall FUN_006AE3F0(void* hwnd, unsigned message, unsigned wParam, long lParam);

// FUNCTION: GAMEMD 0x6AE2C0
bool FUN_006AE2C0()
{
    int result = -1;
    DAT_008871E0->Read_Countries(DAT_00887048);
    DAT_008871E0->FUN_00672440(DAT_00887048);
    for (int i = 0; i < DAT_00A83C98.Count; i++) {
        DAT_00A83C98.Items[i]->vf_25(DAT_00887048);
    }
    FUN_0072CF40();
    HWND dialog = (HWND)UI_BeginDialog(0x102, FUN_006AE3F0, 0);
    if (dialog) {
        DAT_00B0B59C = dialog;
        SetWindowLongA(dialog, DWL_USER, (LONG)&result);
        UI_FocusOnWindow(dialog);
        while (result != 0x617 && result != 0x5C0) {
            if (UI::Updated() == 1) {
                break;
            }
            FUN_00532100(false);
        }
        UI_EndDialog(dialog);
        DAT_00B0B59C = 0;
    }
    if (DAT_00AC1154) {
        delete DAT_00AC1154;
        DAT_00AC1154 = 0;
    }
    FUN_0072CF90();
    Session_00A8B238.FUN_006990A0();
    if (result == 0x5C0) {
        FUN_0052FEC0(0, 1);
    }
    if (result == 0x617)
        return true;
    return false;
}

// FUNCTION: GAMEMD 0x6AE3F0 (partial 94.5%: the final else-arm null assignment is xor eax,eax; push eax in retail, push 0 here)
int __stdcall FUN_006AE3F0(void* hwnd, unsigned message, unsigned wParam, long lParam)
{
    HWND window = (HWND)hwnd;
    int result = FUN_00622B50(window, message, wParam, lParam);
    if (result) {
        return result;
    }
    switch (message) {
    case WM_COMMAND:
        FUN_006ACEE0(window, LOWORD(wParam), lParam, HIWORD(wParam));
        return 1;
    case WM_PAINT:
        if (DAT_00AC1154) {
            HWND item = GetDlgItem(window, 0x468);
            if (!FUN_006067A0((int)item)) {
                DAT_00AC1154->FUN_00640710(window);
            }
        }
        ValidateRect(window, 0);
        return 0;
    case 0x497:
        return FUN_006AE6E0(window, wParam, lParam);
    case 0x4E9: {
        Query_00603F00* query = (Query_00603F00*)lParam;
        query->unknown_08 = 0;
        if (query->unknown_00 && query->unknown_04 != -1) {
            int id = GetDlgCtrlID((HWND)query->unknown_00);
            if (id == 0x50B || id == 0x50E || id == 0x516 || id == 0x51A || id == 0x51B || id == 0x51C || id == 0x51D) {
                int selected = query->unknown_04;
                if (selected == -1) {
                    selected = SendDlgItemMessageA(window, id, 0x147, 0, 0);
                }
                int kind = SendDlgItemMessageA(window, id, 0x150, selected, 0);
                if (kind == -1) {
                    query->unknown_08 = FUN_00734E60("STT:PlayerNone", 0, DAT_0083FC4C, 0x87);
                } else if (kind == 2) {
                    query->unknown_08 = FUN_00734E60("STT:PlayerDumbAI", 0, DAT_0083FC4C, 0x89);
                } else if (kind == 1) {
                    query->unknown_08 = FUN_00734E60("STT:PlayerSmartAI", 0, DAT_0083FC4C, 0x8B);
                } else if (kind == 0) {
                    query->unknown_08 = FUN_00734E60("STT:PlayerGeniusAI", 0, DAT_0083FC4C, 0x8D);
                } else {
                    query->unknown_08 = 0;
                }
                return 1;
            }
            if (FUN_004E3830(id) == -1) {
                if (FUN_004E4230(id) == -1) {
                    if (FUN_004E4EC0(id) != -1) {
                        int colour = FUN_004E5900(window, id, query->unknown_04);
                        query->unknown_08 = FUN_004E4F30(colour);
                    }
                } else {
                    int house = FUN_004E4E20(window, id, query->unknown_04);
                    query->unknown_08 = FUN_004E42A0(house);
                }
            } else {
                int start = FUN_004E4170(window, id, query->unknown_04);
                if (start != -1) {
                    query->unknown_08 = FUN_004E38A0(start);
                }
            }
        }
        return 1;
    }
    }
    return 0;
}
