// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit MPScore.cpp. The name is the source-file string at 0x82fe24
//   in retail gamemd.exe v1.001, passed by the assert at 0x5c982a inside this object's
//   code range (0x5c9510-0x5ca41f). Functions are in ascending retail address order.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /Ob2 /MT
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The MPScore.cpp block of retail .text (0x5C9510..0x5CA41F; the unit's own
// path at 0x82FE24 names it): three of the unit's run-time initialisers, the
// score-screen object's constructor and run method, the duration formatter,
// the number-to-dialog-item helper, the per-house score table builder and its
// sort, in retail address order.
//
// STRING: GAMEMD 0x81B2EC "TXT_TIME_FORMAT_HOURS"
// STRING: GAMEMD 0x81B3D0 L"%d"
// STRING: GAMEMD 0x81B41C "Loser"
// STRING: GAMEMD 0x81B424 "Winner"
// STRING: GAMEMD 0x82FE84 "GUI:MultiplayerScore"
// STRING: GAMEMD 0x82FE9C "GUI:SkirmishScore"
// STRING: GAMEMD 0x82FEB0 "TXT_GAME"
// STRING: GAMEMD 0x82FEBC "SCORE"
// STRING: GAMEMD 0x82FE40 "%hs: %s\n Scheme: %d\n Lost = %d\n Kills = %d\n Built = %d\n Score = %d\n"

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "mp_score.h"
#include "../_layout/theme_class.h"
#include "../_layout/house_class.h"
#include "../_layout/house_type_class.h"
#include "../core/header_tuning_globals.h"
#include "../core/vector_class.h"
#include "../renderer/pcx_get_surface_methods.h"

// ---- run-time initialised copies of the shared tuning globals -----------------------------------------------------

// GLOBAL: GAMEMD 0xABF998
extern double DAT_00ABF998;
// GLOBAL: GAMEMD 0x7EE6D8
const double DAT_007EE6D8 = 60.0;

// ---- what the unit reaches outside itself --------------------------------------------------------------------------

// GLOBAL: GAMEMD 0x82FE24 -- this unit's build path, handed to the label lookup.
extern const char DAT_0082FE24[];

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- resolve a label to its localised
// text; __fastcall with the file and line on the stack, RET 8.
const wchar_t* FUN_00734E60(const char* label, int flags, const char* file, int line);

// GLOBAL: GAMEMD 0xA80228 -- the house registry (Items +0x04 = 0xA8022C, Count +0x10 = 0xA80238).
extern DynamicVectorClass<HouseClass*> DAT_00A80228;

// GLOBAL: GAMEMD 0xAC1198 -- the observer's house.
extern HouseClass* DAT_00AC1198;

// The scenario object; +0x218 is its random-number generator and +0x34B8 the
// side index the multiplayer screen palette is loaded for.
struct Random_0065C7E0
{
    // FUNCTION: GAMEMD 0x65C7E0 (decl; reloc) -- a number in [low, high], RET 8.
    int FUN_0065C7E0(int low, int high);
};
// The clock inside a count-up timer; its reader ignores `this`.
#include "../_layout/clock_006c8c40.h"
// A count-up timer: the start tick (-1 while stopped), the clock and the ticks
// accumulated so far; read inline by 0x5C9B10 with the timer's address in EBP.
struct Timer_005C9B10
{
    int            unknown_00;   // +0x00 start tick, -1 == stopped
    Clock_006C8C40 unknown_04;   // +0x04
    int            unknown_08;   // +0x08 accumulated ticks

    int Elapsed()
    {
        int total = unknown_08;
        if (unknown_00 != -1) {
            total += unknown_04.FUN_006C8C40() - unknown_00;
        }
        return total;
    }
};
struct Scenario_00A8B230
{
    char            _pad0000[0x218];               // +0x0000
    Random_0065C7E0 unknown_218;                   // +0x0218
    char            _pad0219[0x614 - 0x219];       // +0x0219
    Timer_005C9B10  unknown_614;                   // +0x0614 the elapsed game time
    char            _pad0620[0x34B8 - 0x620];      // +0x0620
    int             unknown_34B8;                  // +0x34B8
};
GG_STATIC_ASSERT(offsetof(Scenario_00A8B230, unknown_218) == 0x218);
GG_STATIC_ASSERT(offsetof(Scenario_00A8B230, unknown_614) == 0x614);
GG_STATIC_ASSERT(offsetof(Scenario_00A8B230, unknown_34B8) == 0x34B8);
// GLOBAL: GAMEMD 0xA8B230
extern Scenario_00A8B230* DAT_00A8B230;

// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- the debug log sink (a bare RET in retail).
extern "C" void __cdecl FUN_004068E0(const char* format, ...);

// The screen rectangle handed to the blank-fill; four dwords.
struct Rect_005C9720
{
    int X;        // +0x00
    int Y;        // +0x04
    int Width;    // +0x08
    int Height;   // +0x0C
};
GG_STATIC_ASSERT(sizeof(Rect_005C9720) == 0x10);
struct Surface_0088730C;
// GLOBAL: GAMEMD 0x88730C -- the primary drawing surface.
extern Surface_0088730C* DAT_0088730C;
// GLOBAL: GAMEMD 0x8A00A4 -- the screen width.
extern int DAT_008A00A4;
// GLOBAL: GAMEMD 0x8A00A8 -- the screen height.
extern int DAT_008A00A8;

// FUNCTION: GAMEMD 0x72D730 (decl; reloc)
void EnsureMpScreenPalette(int sideIndex);

// FUNCTION: GAMEMD 0x72D780 (decl; reloc)
void __cdecl FreeMpScreenPalette();

// FUNCTION: GAMEMD 0x72EAD0 (decl; reloc) -- __fastcall: surface in ECX, rectangle in EDX.
void FUN_0072EAD0(Surface_0088730C* surface, Rect_005C9720* rect);

// FUNCTION: GAMEMD 0x4F4780 (decl; reloc) -- __fastcall: bool in CL, surface in EDX, one stacked int.
void FUN_004F4780(bool flag, Surface_0088730C* surface, int arg);

// FUNCTION: GAMEMD 0x60D380 (decl; reloc) -- __fastcall: dialog resource id in ECX,
// dialog procedure in EDX, one stacked dword; runs the dialog.
int FUN_0060D380(int resource, int (__stdcall* procedure)(HWND, UINT, WPARAM, LPARAM), int arg);

// GLOBAL: GAMEMD 0xAC4848 -- the loaded-PCX table.
extern PCX DAT_00AC4848;
// GLOBAL: GAMEMD 0x844B24 -- the ten bar image names for side 0 ("mpascrnlbar01.pcx"...).
extern const char* DAT_00844B24[10];
// GLOBAL: GAMEMD 0x844B4C -- the ten for side 1 ("mpsscrnlbar01.pcx"...).
extern const char* DAT_00844B4C[10];
// GLOBAL: GAMEMD 0x844B74 -- the ten for side 2 ("mpyscrnlbar01.pcx"...).
extern const char* DAT_00844B74[10];

// FUNCTION: GAMEMD 0x622B50 (decl; reloc) -- __fastcall, the shared dialog message filter.
int FUN_00622B50(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

// FUNCTION: GAMEMD 0x775690 (decl; reloc) -- __fastcall: a control's rectangle.
void FUN_00775690(HWND window, RECT* rect);

// FUNCTION: GAMEMD 0x72AA10 (decl; reloc) -- __fastcall: the rectangle, two offsets.
void FUN_0072AA10(Rect_005C9720* rect, int dx, int dy);

// FUNCTION: GAMEMD 0x621B80 (decl; reloc) -- __fastcall: rectangle, surface, two dwords.
void FUN_00621B80(Rect_005C9720* rect, Surface_0088730C* surface, int unknown_3, int unknown_4);

// FUNCTION: GAMEMD 0x603D30 (decl; reloc) -- __fastcall: put a surface on a control.
void FUN_00603D30(HWND control, void* surface);

// GLOBAL: GAMEMD 0x887310
extern Surface_0088730C* DAT_00887310;

// The theme (music) player at 0xA83D10: canonical ThemeClass.
// GLOBAL: GAMEMD 0xA83D10
extern ThemeClass DAT_00A83D10;

// A colour scheme: its +0x308 member hands back a colour by value.
struct ColorValue_00517440
{
    ColorValue_00517440() {}
    unsigned char R;   // +0x00
    unsigned char G;   // +0x01
    unsigned char B;   // +0x02
};
GG_STATIC_ASSERT(sizeof(ColorValue_00517440) == 3);
struct SchemeColor_00517440
{
    // FUNCTION: GAMEMD 0x517440 (decl; reloc) -- the colour through a hidden pointer.
    ColorValue_00517440 FUN_00517440() const;
};
struct ColorScheme_00B054D0
{
    char                 _pad000[0x308];   // +0x000
    SchemeColor_00517440 unknown_308;      // +0x308
};
GG_STATIC_ASSERT(offsetof(ColorScheme_00B054D0, unknown_308) == 0x308);
// GLOBAL: GAMEMD 0xB054D0 -- the colour-scheme registry (Items at 0xB054D4).
extern DynamicVectorClass<ColorScheme_00B054D0*> DAT_00B054D0;

// GLOBAL: GAMEMD 0xB779D4
extern int DAT_00B779D4;
// GLOBAL: GAMEMD 0x82FD5C -- each score row's five control ids (name, kills,
// losses, production, score).
extern const int DAT_0082FD5C[8][5];
// GLOBAL: GAMEMD 0x82FDFC -- the two header bar controls.
extern const int DAT_0082FDFC[2];
// GLOBAL: GAMEMD 0x82FE04 -- each row's bar control.
extern const int DAT_0082FE04[8];

// ---- the score screen ----------------------------------------------------------------------------------------------

// GLOBAL: GAMEMD 0xABF9E8
extern double DAT_00ABF9E8;

// GLOBAL: GAMEMD 0xABF9D0
extern double DAT_00ABF9D0;

// GLOBAL: GAMEMD 0xABF9D8
extern TuningCoordInit DAT_00ABF9D8;

// FUNCTION: GAMEMD 0x5C9700
//
// Clears the sorted-entry table and the two dwords beside it; the object
// itself holds no data (the callers 0x685884 and 0x685FCE pass one stack byte).
Obj_005C9700::Obj_005C9700()
{
    DAT_00ABF9F4 = 0;
    DAT_00ABF9F8 = 0;
    memset(DAT_00ABF958, 0, sizeof(DAT_00ABF958));
}

// FUNCTION: GAMEMD 0x5C9720
//
// Blank the screen, run the score dialog (resource 0x108, procedure 0x5C9B10),
// blank again and release the palette.
void Obj_005C9700::FUN_005C9720()
{
    EnsureMpScreenPalette(DAT_00A8B230->unknown_34B8);
    Rect_005C9720 rect;
    rect.X = 0;
    rect.Y = 0;
    rect.Width = DAT_008A00A4;
    rect.Height = DAT_008A00A8;
    FUN_0072EAD0(DAT_0088730C, &rect);
    FUN_004F4780(true, DAT_0088730C, 0);
    FUN_0060D380(0x108, FUN_005C9B10, 0);
    FUN_0072EAD0(DAT_0088730C, &rect);
    FUN_004F4780(true, DAT_0088730C, 0);
    FreeMpScreenPalette();
}

// FUNCTION: GAMEMD 0x5C97B0
//
// Format a duration in seconds as hours, minutes and seconds, capped at
// 99:59:59. The same formatter as 0x46D360 and 0x470C90, written out again in
// this unit (its own file path and line 0xD9).
void FUN_005C97B0(wchar_t* buffer, int seconds)
{
    if (buffer == 0) {
        return;
    }

    if (seconds / 3600 > 99) {
        seconds = 359999;
    }

    int hours = seconds / 3600;
    seconds -= hours * 3600;

    int minutes = seconds / 60;
    seconds -= minutes * 60;

    swprintf(buffer, FUN_00734E60("TXT_TIME_FORMAT_HOURS", 0, DAT_0082FE24, 0xD9), hours, minutes, seconds);
}

// FUNCTION: GAMEMD 0x5C9850
//
// Print a number into a dialog item (message 0x4B2 sets its text).
void FUN_005C9850(HWND dialog, int item, int value)
{
    wchar_t buffer[0x20];
    swprintf(buffer, L"%d", value);
    HWND control = GetDlgItem(dialog, item);
    SendMessageA(control, 0x4B2, 0, (LPARAM)buffer);
}

// FUNCTION: GAMEMD 0x5C98A0
//
// Fill one score entry per house that is present, not multiplay-passive and
// not the observer: its name and colour scheme, a winner count, losses, kills,
// production and the score (a survivor's score gains a random bonus between
// half and all of it). Each entry is traced to the debug log.
void __cdecl FUN_005C98A0()
{
    Session_00A8B238.ScoreCount = 0;
    int count = DAT_00A80228.Count;
    for (int i = 0; i < count; i++) {
        HouseClass* house = DAT_00A80228.Items[i];
        if (house == 0 || ((HouseTypeClass*)house->Type)->MultiplayPassive == true || house == DAT_00AC1198) {
            continue;
        }

        int index = Session_00A8B238.ScoreCount++;
        Session_00A8B238.ScoreEntries[index].unknown_2C = 0;
        wcscpy(Session_00A8B238.ScoreEntries[index].Name, house->UIName);
        Session_00A8B238.ScoreEntries[index].unknown_30[0] = 0;
        Session_00A8B238.ScoreEntries[index].unknown_40[0] = 0;
        Session_00A8B238.ScoreEntries[index].unknown_50[0] = 0;
        Session_00A8B238.ScoreEntries[index].unknown_60[0] = 0;
        Session_00A8B238.ScoreEntries[index].unknown_28 = house->ColorSchemeIndex;
        if (!house->Defeated) {
            ++Session_00A8B238.ScoreEntries[index].unknown_2C;
            Session_00A8B238.ScoreSurvivor = index;
        }

        int kills = 0;
        int k;
        for (k = 0; k < 20; k++) {
            kills += house->KilledUnitsOfHouses[k];
        }
        for (k = 0; k < 20; k++) {
            kills += house->KilledBuildingsOfHouses[k];
        }
        Session_00A8B238.ScoreEntries[index].unknown_40[0] = kills;
        Session_00A8B238.ScoreEntries[index].unknown_30[0] = house->TotalKilledBuildings + house->TotalKilledUnits;
        int built = house->FactoryProducedBuildingTypes.FUN_0049FB60();
        built += house->FactoryProducedUnitTypes.FUN_0049FB60();
        built += house->FactoryProducedInfantryTypes.FUN_0049FB60();
        built += house->FactoryProducedAircraftTypes.FUN_0049FB60();
        Session_00A8B238.ScoreEntries[index].unknown_50[0] = built;
        if (house->PointTotal > 0) {
            Session_00A8B238.ScoreEntries[index].unknown_60[0] += house->PointTotal;
        }
        if (!house->Defeated) {
            int score = Session_00A8B238.ScoreEntries[index].unknown_60[0];
            Session_00A8B238.ScoreEntries[index].unknown_60[0] = DAT_00A8B230->unknown_218.FUN_0065C7E0(score / 2, score) + score / 2 + score;
        }

        FUN_004068E0("%hs: %s\n Scheme: %d\n Lost = %d\n Kills = %d\n Built = %d\n Score = %d\n",
                     Session_00A8B238.ScoreEntries[index].Name, Session_00A8B238.ScoreEntries[index].unknown_2C > 0 ? "Winner" : "Loser",
                     Session_00A8B238.ScoreEntries[index].unknown_28, Session_00A8B238.ScoreEntries[index].unknown_30[0],
                     Session_00A8B238.ScoreEntries[index].unknown_40[0], Session_00A8B238.ScoreEntries[index].unknown_50[0],
                     Session_00A8B238.ScoreEntries[index].unknown_60[0]);
    }
}

// FUNCTION: GAMEMD 0x5C9AA0
//
// Point the sort table at the filled entries and order them by score.
void __cdecl FUN_005C9AA0()
{
    int count = Session_00A8B238.ScoreCount;
    for (int i = 0; i < count; i++) {
        DAT_00ABF958[i] = &Session_00A8B238.ScoreEntries[i];
    }
    if (count > 1) {
        qsort(DAT_00ABF958, count, sizeof(ScoreEntry_00A8D1FC*), FUN_005C9AE0);
    }
}

// FUNCTION: GAMEMD 0x5C9AE0
//
// qsort comparison: higher score first.
int __cdecl FUN_005C9AE0(const void* a, const void* b)
{
    const ScoreEntry_00A8D1FC* first = *(ScoreEntry_00A8D1FC* const*)a;
    const ScoreEntry_00A8D1FC* second = *(ScoreEntry_00A8D1FC* const*)b;
    if (first->unknown_60[0] == second->unknown_60[0]) {
        return 0;
    }
    return first->unknown_60[0] > second->unknown_60[0] ? -1 : 1;
}

// FUNCTION: GAMEMD 0x5C9B10
//
// The score dialog's procedure. 0x497 fills it: the score theme, the game
// title and number, the elapsed time, the side's header bars, then one row per
// entry in score order (bar image, name, kills, losses, production and score,
// each text in the entry's colour). 0x111 from the continue button (0x6D1)
// sets the dialog's done flag; 0xF redraws the frame around the rows. The
// number cells reuse 0x5C9850 (inlined here) before setting their colour.
//
// PARTIAL (37.9% positional, 85.7% aligned). Three residues: retail's frame is
// four bytes larger (0x18C) and pushes EBP straight after the filter test, so
// every stack offset is shifted by four; the four number buffers sit in a
// different stack order (retail: losses, production, kills, score); and the
// sort-table walk keeps the count in EBP rather than EDX. Tried: if/else vs a
// switch (the switch gives retail's block order: 4.4% -> 6.5%), each control
// handle taken into a local before the send (-> 37.9%), all 24 declaration
// orders of the four buffers and swapping their names (no change), and the
// number cells as calls to 0x5C9850 (no change, kept as the plainer form).
int __stdcall FUN_005C9B10(HWND dialog, UINT message, WPARAM wParam, LPARAM lParam)
{
    int result = FUN_00622B50(dialog, message, wParam, lParam);
    if (result != 0) {
        return result;
    }

    int* done = (int*)GetWindowLongA(dialog, 8);
    HWND control;
    switch (message) {
    case 0x497:
    {
        DAT_00A83D10.PlaySong(DAT_00A83D10.FindIndex("SCORE"));

        wchar_t text[0x20];
        if (Session_00A8B238.GameMode == 4) {
            swprintf(text, FUN_00734E60("TXT_GAME", 0, DAT_0082FE24, 0x174), DAT_00B779D4);
        } else {
            swprintf(text, FUN_00734E60("TXT_GAME", 0, DAT_0082FE24, 0x176), Session_00A8B238.unknown_2344);
        }
        const wchar_t* title;
        if (Session_00A8B238.GameMode == 5) {
            title = FUN_00734E60("GUI:SkirmishScore", 0, DAT_0082FE24, 0x17A);
        } else {
            title = FUN_00734E60("GUI:MultiplayerScore", 0, DAT_0082FE24, 0x17C);
        }
        control = GetDlgItem(dialog, 0x694);
        SendMessageA(control, 0x4B2, 0, (LPARAM)title);
        control = GetDlgItem(dialog, 0x6D2);
        SendMessageA(control, 0x4B2, 0, (LPARAM)text);

        FUN_005C97B0(text, DAT_00A8B230->unknown_614.Elapsed() / 60);
        control = GetDlgItem(dialog, 0x3EA);
        SendMessageA(control, 0x4B2, 0, (LPARAM)text);

        FUN_005C98A0();
        FUN_005C9AA0();

        int i;
        for (i = 0; i < 2; i++) {
            HWND bar = GetDlgItem(dialog, DAT_0082FDFC[i]);
            void* image = FUN_005CA110(i);
            if (bar != 0 && image != 0) {
                FUN_00603D30(bar, image);
            }
        }

        for (i = 0; i < Session_00A8B238.ScoreCount; i++) {
            ColorValue_00517440 color = DAT_00B054D0.Items[DAT_00ABF958[i]->unknown_28]->unknown_308.FUN_00517440();
            COLORREF rgb = RGB(color.R, color.G, color.B);

            HWND bar = GetDlgItem(dialog, DAT_0082FE04[i]);
            void* image = FUN_005CA110(i + 2);
            if (bar != 0 && image != 0) {
                FUN_00603D30(bar, image);
            }

            int item = DAT_0082FD5C[i][0];
            control = GetDlgItem(dialog, item);
            SendMessageA(control, 0x4B2, 0, (LPARAM)DAT_00ABF958[i]->Name);
            control = GetDlgItem(dialog, item);
            SendMessageA(control, 0x498, 0, rgb);
            item = DAT_0082FD5C[i][1];
            FUN_005C9850(dialog, item, DAT_00ABF958[i]->unknown_40[0]);
            control = GetDlgItem(dialog, item);
            SendMessageA(control, 0x498, 0, rgb);
            item = DAT_0082FD5C[i][2];
            FUN_005C9850(dialog, item, DAT_00ABF958[i]->unknown_30[0]);
            control = GetDlgItem(dialog, item);
            SendMessageA(control, 0x498, 0, rgb);
            item = DAT_0082FD5C[i][3];
            FUN_005C9850(dialog, item, DAT_00ABF958[i]->unknown_50[0]);
            control = GetDlgItem(dialog, item);
            SendMessageA(control, 0x498, 0, rgb);
            item = DAT_0082FD5C[i][4];
            FUN_005C9850(dialog, item, DAT_00ABF958[i]->unknown_60[0]);
            control = GetDlgItem(dialog, item);
            SendMessageA(control, 0x498, 0, rgb);
        }
        return 0;
    }
    case 0x111:
        if (LOWORD(wParam) == 0x6D1) {
            *done = 1;
            return 0;
        }
        break;
    case 0xF:
    {
        RECT first;
        RECT last;
        FUN_00775690(GetDlgItem(dialog, 0x6D2), &first);
        FUN_00775690(GetDlgItem(dialog, DAT_0082FD5C[Session_00A8B238.ScoreCount - 1][4]), &last);
        Rect_005C9720 frame;
        frame.X = first.left;
        frame.Y = first.top;
        frame.Width = last.right - first.left;
        frame.Height = last.bottom - first.top;
        FUN_0072AA10(&frame, -4, -8);
        FUN_00621B80(&frame, DAT_00887310, 0, 0x9F);
        break;
    }
    }
    return 0;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5CA110
//
// The score screen's side-specific bar image for one row: side 0, 1 and 2 of
// the multiplayer screen each have ten names (0x844B24, 0x844B4C, 0x844B74);
// anything else gives no surface.
void* FUN_005CA110(int index)
{
    int side = DAT_00A8B230->unknown_34B8;
    if (side == 0) {
        if (index == 0) {
            return DAT_00AC4848.GetSurface(DAT_00844B24[0], 0);
        }
        if (index == 1) {
            return DAT_00AC4848.GetSurface(DAT_00844B24[1], 0);
        }
        if (index == 2) {
            return DAT_00AC4848.GetSurface(DAT_00844B24[2], 0);
        }
        if (index == 3) {
            return DAT_00AC4848.GetSurface(DAT_00844B24[3], 0);
        }
        if (index == 4) {
            return DAT_00AC4848.GetSurface(DAT_00844B24[4], 0);
        }
        if (index == 5) {
            return DAT_00AC4848.GetSurface(DAT_00844B24[5], 0);
        }
        if (index == 6) {
            return DAT_00AC4848.GetSurface(DAT_00844B24[6], 0);
        }
        if (index == 7) {
            return DAT_00AC4848.GetSurface(DAT_00844B24[7], 0);
        }
        if (index == 8) {
            return DAT_00AC4848.GetSurface(DAT_00844B24[8], 0);
        }
        if (index == 9) {
            return DAT_00AC4848.GetSurface(DAT_00844B24[9], 0);
        }
    } else if (side == 1) {
        if (index == 0) {
            return DAT_00AC4848.GetSurface(DAT_00844B4C[0], 0);
        }
        if (index == 1) {
            return DAT_00AC4848.GetSurface(DAT_00844B4C[1], 0);
        }
        if (index == 2) {
            return DAT_00AC4848.GetSurface(DAT_00844B4C[2], 0);
        }
        if (index == 3) {
            return DAT_00AC4848.GetSurface(DAT_00844B4C[3], 0);
        }
        if (index == 4) {
            return DAT_00AC4848.GetSurface(DAT_00844B4C[4], 0);
        }
        if (index == 5) {
            return DAT_00AC4848.GetSurface(DAT_00844B4C[5], 0);
        }
        if (index == 6) {
            return DAT_00AC4848.GetSurface(DAT_00844B4C[6], 0);
        }
        if (index == 7) {
            return DAT_00AC4848.GetSurface(DAT_00844B4C[7], 0);
        }
        if (index == 8) {
            return DAT_00AC4848.GetSurface(DAT_00844B4C[8], 0);
        }
        if (index == 9) {
            return DAT_00AC4848.GetSurface(DAT_00844B4C[9], 0);
        }
    } else if (side == 2) {
        if (index == 0) {
            return DAT_00AC4848.GetSurface(DAT_00844B74[0], 0);
        }
        if (index == 1) {
            return DAT_00AC4848.GetSurface(DAT_00844B74[1], 0);
        }
        if (index == 2) {
            return DAT_00AC4848.GetSurface(DAT_00844B74[2], 0);
        }
        if (index == 3) {
            return DAT_00AC4848.GetSurface(DAT_00844B74[3], 0);
        }
        if (index == 4) {
            return DAT_00AC4848.GetSurface(DAT_00844B74[4], 0);
        }
        if (index == 5) {
            return DAT_00AC4848.GetSurface(DAT_00844B74[5], 0);
        }
        if (index == 6) {
            return DAT_00AC4848.GetSurface(DAT_00844B74[6], 0);
        }
        if (index == 7) {
            return DAT_00AC4848.GetSurface(DAT_00844B74[7], 0);
        }
        if (index == 8) {
            return DAT_00AC4848.GetSurface(DAT_00844B74[8], 0);
        }
        if (index == 9) {
            return DAT_00AC4848.GetSurface(DAT_00844B74[9], 0);
        }
    }
    return 0;
}
