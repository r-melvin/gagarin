// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit CampScor.cpp. The name is the source-file string at 0x81b304
//   in retail gamemd.exe v1.001, passed by the assert at 0x46d3da inside this object's
//   code range (0x46d120-0x47153f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// STRING: GAMEMD 0x81B2EC  "TXT_TIME_FORMAT_HOURS"
//
// Campaign score classes: constructors, empty destructors and the compiler-emitted
// scalar deleting destructors (0x471500, 0x471520).

// FUNCTION.H brings in <windows.h>, whose Win32 LocalHandle clashes with the global of that name in
// netshare_slot_nodes.h (0xA8B380). This unit never calls the Win32 one.
#define LocalHandle LocalHandle_Win32
#include "FUNCTION.H"
#undef LocalHandle
#include "house_index_lookup_methods.h"
#include "mathtbl_init_shapes.h"
#include <math.h>
#include "header_init_shapes.h"

#include "small_misc5_methods.h"

#include "small_misc7_methods.h"

#include "trivial_tu043_methods.h"

#include "dialog_enable_methods.h"

#include "format_duration_methods.h"
#include "pcx_get_surface_methods.h"
#include "netshare_slot_nodes.h"
#include "_layout/session_class.h"
#include "connman_class.h"
#include "multiplayer_game_mode.h"
#include "netshare_common.h"
#include "command_packet_layouts.h"
#include <string.h>
#include "scenario_session_globals.h"
#include "_layout/house_class.h"
#include "vector_class.h"
#include "scenario_class.h"
#include "_layout/scenario_ptr_00a8b230.h"
#include "_layout/house_type_class.h"

// VTABLE: GAMEMD 0x7E4AAC
// Campaign score screen state (retail slot 1 is 0x46FC00, not matched).
class CampaignScoreClass
{
public:
    CampaignScoreClass();                 // 0x46D330
    virtual ~CampaignScoreClass();        // 0x46D350 body, 0x471500 scalar deleting
    virtual void Slot1();                 // 0x46FC00

    int Unknown04;                        // +0x04
};
GG_STATIC_ASSERT(offsetof(CampaignScoreClass, Unknown04) == 0x04);

struct MPlayerScoreType;

// VTABLE: GAMEMD 0x7E4AB8
// Campaign end score screen state (retail slot 1 is 0x471420, not matched).
class CampaignEndScoreClass
{
public:
    CampaignEndScoreClass();              // 0x470C00
    virtual ~CampaignEndScoreClass();     // 0x470C30 body, 0x471520 scalar deleting
    virtual void Slot1(DynamicVectorClass<MPlayerScoreType*> scores, int scratch, int posted, int number, const wchar_t* record);  // 0x471420
};

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).

// GLOBAL: GAMEMD 0x7E4A98
extern const double DAT_007E4A98;
// GLOBAL: GAMEMD 0x89DFA8
extern double DAT_0089DFA8;

// GLOBAL: GAMEMD 0x7E1708
const double DAT_007E1708 = 2.0;
// GLOBAL: GAMEMD 0x7E1710
const double DAT_007E1710 = 256.0;
// GLOBAL: GAMEMD 0x7E4AA0 -- degrees to radians
const double DAT_007E4AA0 = 0.017453292519943295;
// FUNCTION: GAMEMD 0x4CAD50 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAD50(double value);
// FUNCTION: GAMEMD 0x4CADE0 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CADE0(double value);
// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- __cdecl, double in and out.
double __cdecl FUN_004CAC40(double value);

// SYNTHETIC: GAMEMD 0x46D120
// GLOBAL: GAMEMD 0x89DFA8
double DAT_0089DFA8 = FUN_004CAC40(pow(DAT_007E1710, DAT_007E1708) * 2);

// SYNTHETIC: GAMEMD 0x0046D150
// dynamic initializer for DAT_0089E040
// GLOBAL: GAMEMD 0x0089E040
double DAT_0089E040 = DAT_0089DFA8 / DAT_007E4A98;

// SYNTHETIC: GAMEMD 0x0046D170
// dynamic initializer for DAT_0089E018
// GLOBAL: GAMEMD 0x0089E018
double DAT_0089E018 = 1.0 / DAT_0089E040;

GG_STATIC_ASSERT(sizeof(DAT_0089E040) == 8);
GG_STATIC_ASSERT(sizeof(DAT_0089E018) == 8);

// SYNTHETIC: GAMEMD 0x46D190
// GLOBAL: GAMEMD 0x89E010
double DAT_0089E010 = DAT_007E4AA0 * 45.0;

// SYNTHETIC: GAMEMD 0x46D1B0
// GLOBAL: GAMEMD 0x89DFB0
double DAT_0089DFB0 = DAT_007E4AA0 * 60.0;

// SYNTHETIC: GAMEMD 0x46D1D0
// GLOBAL: GAMEMD 0x89DF68
double DAT_0089DF68 = DAT_007E4AA0 * 90.0;

// SYNTHETIC: GAMEMD 0x46D1F0
// GLOBAL: GAMEMD 0x89E048
int DAT_0089E048 = (int)(FUN_004CAD50(DAT_0089DF68 - DAT_0089DFB0) * DAT_0089DFA8 * 0.5);

// SYNTHETIC: GAMEMD 0x46D230
// GLOBAL: GAMEMD 0x89DFB8
double DAT_0089DFB8 = FUN_004CADE0(DAT_0089E048 * 0.00390625);

// SYNTHETIC: GAMEMD 0x46D260
// GLOBAL: GAMEMD 0x89DFD8
double DAT_0089DFD8 = FUN_004CADE0((DAT_0089E048 * 2) / DAT_0089DFA8);

// SYNTHETIC: GAMEMD 0x46D290
// GLOBAL: GAMEMD 0x89E034
int DAT_0089E034 = (int)(DAT_0089E048 * 4 + 0.5);

// SYNTHETIC: GAMEMD 0x46D2C0
// GLOBAL: GAMEMD 0x89DFA0
HeaderCellInit DAT_0089DFA0(0, 0);

// SYNTHETIC: GAMEMD 0x46D2D0
// GLOBAL: GAMEMD 0x89DFC8
HeaderCoordInit DAT_0089DFC8(0, 0, 0);

// SYNTHETIC: GAMEMD 0x0046D2F0
// GLOBAL: GAMEMD 0x0089E028
MathTblCoord DAT_0089E028;

// FUNCTION: GAMEMD 0x46D330
CampaignScoreClass::CampaignScoreClass()
{
    Unknown04 = 0;

    DAT_0089E050 = 0;
    DAT_0081B1E8 = -1;
}

// FUNCTION: GAMEMD 0x46D350
// Empty destructor (stores only the vtable).
CampaignScoreClass::~CampaignScoreClass()
{
}

// SYNTHETIC: GAMEMD 0x471500 -- CampaignScoreClass::`scalar deleting destructor'

// FUNCTION: GAMEMD 0x46D360
//
// Format a duration in seconds as hours, minutes and seconds into the caller's
// buffer, capped at 99:59:59.
//
// The hour count is computed twice — once to test the cap and again after it —
// rather than being clamped in place. Retail emits both divisions (0x46D373 and
// 0x46D390), so the source tests `seconds / 3600` and then recomputes it.
void FUN_0046D360(gg_wchar* buffer, int seconds)
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

    FUN_007CA564(buffer,
                 FUN_00734E60("TXT_TIME_FORMAT_HOURS", 0, DAT_0081B304, 0xA9),
                 hours, minutes, seconds);
}

// FUNCTION: GAMEMD 0x46D480
// Stores its argument in a member.
void FUN_0046D480(Obj_0046D480* a1, int a2)
{
    a1->unknown_89E000 = a2;
}

// FUNCTION: GAMEMD 0x46D490
// Member getter (byte).
unsigned char Obj_0046D490::FUN_0046D490() const
{
    return unknown_89E000;
}

// FUNCTION: GAMEMD 0x46D810
void FUN_0046D810()
{
    Payload_0046D810 packet;
    packet.unknown_00 = 0x33;
    strcpy(packet.unknown_04, LocalHandle);
    packet.unknown_2F = Players_00A8DA78[0]->FUN_00696F50();
    packet.unknown_33 = Players_00A8DA78[0]->FUN_00696F10();
    packet.unknown_37 = Players_00A8DA78[0]->FUN_00696F20();
    if (Session_00A8B238.unknown_2858[0]) {
        Manager_00A8E9C0.FUN_00541260(&packet, 0x1C7, 1, Session_00A8B238.unknown_2858[0]->Name);
        Manager_00A8E9C0.Service();
    }
}

// FUNCTION: GAMEMD 0x46DA70 (partial 97.6%: identical instruction multiset; the last two adds of the production sum pair units+built+buildings in a different order and use ecx where retail uses edx)
//
// Fill one score entry per human house that is present and not multiplay-passive: its name and colour
// scheme, a winner count, losses, kills, production and the score. Each entry is traced to the debug log.
void __cdecl FUN_0046DA70()
{
    Session_00A8B238.ScoreCount = 0;
    int count = HouseClass_Array.Count;
    for (int i = 0; i < count; i++) {
        HouseClass* house = HouseClass_Array.Items[i];
        if (house == 0 || ((HouseTypeClass*)house->Type)->MultiplayPassive == true || !house->IsControlledByHuman()) {
            continue;
        }

        int index = Session_00A8B238.ScoreCount++;
        Session_00A8B238.ScoreEntries[index].unknown_2C = 0;
        wcscpy((wchar_t*)Session_00A8B238.ScoreEntries[index].Name, (wchar_t*)house->UIName);
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
        Session_00A8B238.ScoreEntries[index].unknown_30[0] = house->TotalKilledUnits + house->TotalKilledBuildings;
        int built = house->ActiveBuildingTypes.FUN_0049FB60();
        built += house->ActiveUnitTypes.FUN_0049FB60();
        built += house->ActiveInfantryTypes.FUN_0049FB60();
        built += house->ActiveAircraftTypes.FUN_0049FB60();
        Session_00A8B238.ScoreEntries[index].unknown_50[0] = house->TotalKilledUnits + built + house->TotalKilledBuildings;
        if (house->PointTotal > 0) {
            Session_00A8B238.ScoreEntries[index].unknown_60[0] += house->PointTotal;
        }

        FUN_004068E0("%hs: %s\n Scheme: %d\n Lost = %d\n Kills = %d\n Built = %d\n Score = %d\n",
                     Session_00A8B238.ScoreEntries[index].Name, Session_00A8B238.ScoreEntries[index].unknown_2C > 0 ? "Winner" : "Loser",
                     Session_00A8B238.ScoreEntries[index].unknown_28, Session_00A8B238.ScoreEntries[index].unknown_30[0],
                     Session_00A8B238.ScoreEntries[index].unknown_40[0], Session_00A8B238.ScoreEntries[index].unknown_50[0],
                     Session_00A8B238.ScoreEntries[index].unknown_60[0]);
    }
}

struct Entry_0046DC50
{
    char unknown_00[0x60];
    int unknown_60;           // +0x60  the score the table is ordered by
    char unknown_64[0x0C];
};
GG_STATIC_ASSERT(offsetof(Entry_0046DC50, unknown_60) == 0x60);
GG_STATIC_ASSERT(sizeof(Entry_0046DC50) == 0x70);

// Score ordering comparator for qsort (defined after its user).
int __cdecl FUN_0046DC90(const void* a, const void* b);

// GLOBAL: GAMEMD 0xA8D1FC
extern Entry_0046DC50 DAT_00A8D1FC[];
// GLOBAL: GAMEMD 0x89DF80
extern Entry_0046DC50* DAT_0089DF80[];

// FUNCTION: GAMEMD 0x46DC50
//
// Point the sort table at the filled score entries and order them.
void __cdecl FUN_0046DC50()
{
    int count = DAT_00A8D580;
    for (int i = 0; i < count; i++) {
        DAT_0089DF80[i] = &DAT_00A8D1FC[i];
    }
    if (count > 1) {
        qsort(DAT_0089DF80, count, sizeof(Entry_0046DC50*), FUN_0046DC90);
    }
}

// FUNCTION: GAMEMD 0x46DC90
//
// qsort comparison: higher score first.
int __cdecl FUN_0046DC90(const void* a, const void* b)
{
    const Entry_0046DC50* first = *(Entry_0046DC50* const*)a;
    const Entry_0046DC50* second = *(Entry_0046DC50* const*)b;
    if (first->unknown_60 == second->unknown_60) {
        return 0;
    }
    return first->unknown_60 > second->unknown_60 ? -1 : 1;
}

// FUNCTION: GAMEMD 0x4E41D0 (decl; reloc) -- the house control of a slot index.
int FUN_004E41D0(int index);
// FUNCTION: GAMEMD 0x4E49A0 (decl; reloc) -- set the house control, RET 4.
void FUN_004E49A0(HWND_ dialog, int control, int value);
// FUNCTION: GAMEMD 0x4E4E60 (decl; reloc) -- the colour control of a slot index.
int FUN_004E4E60(int index);
// FUNCTION: GAMEMD 0x4E5480 (decl; reloc) -- set the colour control, RET 4.
void FUN_004E5480(HWND_ dialog, int control, int value);
// GLOBAL: GAMEMD 0xA8DA8C -- the seat the local player holds.
extern int DAT_00A8DA8C;

// FUNCTION: GAMEMD 0x4E37D0 (decl; reloc) -- the start-position control of a slot index.
int FUN_004E37D0(int index);

// FUNCTION: GAMEMD 0x46DCC0
void FUN_0046DCC0(HWND_ dialog, unsigned char enable)
{
    for (int i = 0; i < 8; i++) {
        NodeNameType* node = Session_00A8B238.unknown_2858[i];
        if (node->FUN_005E93F0() && i != DAT_00A8DA8C) {
            int id;
            if (i == 0)
                id = 0x411;
            else if (i == 1)
                id = 0x412;
            else
                id = -1;
            HWND_ item = GetDlgItem(dialog, id);
            EnableWindow(item, enable);
            item = GetDlgItem(dialog, FUN_004E37D0(i));
            EnableWindow(item, enable);
            item = GetDlgItem(dialog, FUN_004E41D0(i));
            EnableWindow(item, enable);
            item = GetDlgItem(dialog, FUN_004E4E60(i));
            EnableWindow(item, enable);
        }
    }
}

// USER32 imports used by the dialog fills below.
extern "C" __declspec(dllimport) int __stdcall ShowWindow(HWND_ wnd, int command);
extern "C" __declspec(dllimport) long __stdcall SendDlgItemMessageA(HWND_ dialog, int id, unsigned message, unsigned wparam, long lparam);
// IAT 0x7E14A4: USER32!SendMessageA.
extern "C" __declspec(dllimport) long __stdcall SendMessageA(HWND_ hWnd, unsigned uMsg, unsigned wParam, long lParam);

// FUNCTION: GAMEMD 0x46DE20
//
// Show or hide the lobby dialog's controls together (the first is also invalidated); the last
// control takes the opposite state.
void __fastcall FUN_0046DE20(HWND_ dialog, int show)
{
    HWND_ item = GetDlgItem(dialog, 0x732);
    if (item) {
        ShowWindow(item, show);
        InvalidateRect(item, 0, 0);
    }
    item = GetDlgItem(dialog, 0x72f);
    if (item)
        ShowWindow(item, show);
    item = GetDlgItem(dialog, 0x798);
    if (item)
        ShowWindow(item, show);
    item = GetDlgItem(dialog, 0x799);
    if (item)
        ShowWindow(item, show);
    item = GetDlgItem(dialog, 0x79a);
    if (item)
        ShowWindow(item, show);
    item = GetDlgItem(dialog, 0x79b);
    if (item)
        ShowWindow(item, show);
    item = GetDlgItem(dialog, 0x77e);
    if (item)
        ShowWindow(item, show);
    item = GetDlgItem(dialog, 0x6d2);
    if (item)
        ShowWindow(item, show);
    item = GetDlgItem(dialog, 0x6d3);
    if (item)
        ShowWindow(item, show);
    item = GetDlgItem(dialog, 0x411);
    if (item)
        ShowWindow(item, show);
    item = GetDlgItem(dialog, 0x412);
    if (item)
        ShowWindow(item, show);
    item = GetDlgItem(dialog, 0x6da);
    if (item)
        ShowWindow(item, show);
    item = GetDlgItem(dialog, 0x6db);
    if (item)
        ShowWindow(item, show);
    item = GetDlgItem(dialog, 0x6a1);
    if (item)
        ShowWindow(item, show);
    item = GetDlgItem(dialog, 0x510);
    if (item)
        ShowWindow(item, show);
    item = GetDlgItem(dialog, 0x6a2);
    if (item)
        ShowWindow(item, show);
    item = GetDlgItem(dialog, 0x522);
    if (item)
        ShowWindow(item, show);
    item = GetDlgItem(dialog, 0x6a3);
    if (item)
        ShowWindow(item, show);
    item = GetDlgItem(dialog, 0x6a4);
    if (item)
        ShowWindow(item, show);
    item = GetDlgItem(dialog, 0x6d1);
    if (item)
        ShowWindow(item, show);
    item = GetDlgItem(dialog, 0x5a8);
    if (item)
        ShowWindow(item, show);
    item = GetDlgItem(dialog, 0x71c);
    if (item) {
        if (!show)
            ShowWindow(item, 1);
        else
            ShowWindow(item, 0);
    }
    item = GetDlgItem(dialog, 0x468);
    if (item)
        ShowWindow(item, show);
}

// FUNCTION: GAMEMD 0x46F600
void FUN_0046F600(HWND_ dialog)
{
    for (int i = 0; i < 8; i++) {
        int id;
        if (i == 0)
            id = 0x411;
        else if (i == 1)
            id = 0x412;
        else
            continue;
        HWND_ first = GetDlgItem(dialog, id);
        if (ShowWindow(first, 0)) {
            if (id != -1) {
                HWND_ combo = GetDlgItem(dialog, id);
                NodeNameType* node = Session_00A8B238.unknown_2858[i];
                if (node == 0)
                    continue;
                SendDlgItemMessageA(dialog, id, 0x14B, 0, 0);
                int index = SendMessageA(combo, 0x4C2, 0, (long)node);
                SendMessageA(combo, 0x151, index, (long)node);
                SendMessageA(combo, 0x14E, index, 0);
            }
            ShowWindow(first, 5);
        }
    }
}

// FUNCTION: GAMEMD 0x4E3F70 (decl; reloc) -- set the start-position control, RET 4.
void FUN_004E3F70(HWND_ dialog, int control, int value);

// FUNCTION: GAMEMD 0x46F6D0
void FUN_0046F6D0(HWND_ dialog)
{
    for (int i = 0; i < 8; i++) {
        int control = FUN_004E37D0(i);
        HWND_ item = GetDlgItem(dialog, control);
        if (ShowWindow(item, 0)) {
            NodeNameType* node = Session_00A8B238.unknown_2858[i];
            int position = -2;
            MultiplayerGameMode* mode = Session_00A8B238.unknown_04;
            if (mode != 0 && (Session_00A8B238.GameMode == 3 || Session_00A8B238.GameMode == 4)) {
                position = mode->vf_10();
            }
            int value;
            if (node->FUN_005E9440()) {
                value = Session_00A8B238.unknown_18.unknown_4C[i];
            } else if (node == OpenNode) {
                value = position;
            } else if (node == ClosedNode) {
                value = position;
            } else if (node == WaitingNode) {
                value = position;
            } else if (node == ObserverNode) {
                value = -3;
            } else {
                value = node->FUN_00696F10();
            }
            if (Session_00A8B238.unknown_04 != 0 && !Session_00A8B238.unknown_04->vf_7(value)) {
                value = position;
                if (node->FUN_005E9440()) {
                    Session_00A8B238.unknown_18.unknown_4C[i] = position;
                } else if (node->FUN_005E93F0()) {
                    Session_00A8B238.unknown_2858[i]->FUN_00696F90(position);
                }
            }
            FUN_004E3F70(dialog, control, value);
            ShowWindow(item, 5);
        }
    }
}

// FUNCTION: GAMEMD 0x46F810
//
// Each of the four rejections gets its own `POP EDI; MOV EAX,-2; POP ESI; RET`
// in retail - four separate epilogues, so four separate `return -2` statements
// rather than one `||` chain, which would share a tail.
int FUN_0046F810(int index)
{
    Entry_0046F810* entry = DAT_00A8DA90[index];

    if (entry->FUN_005E9440()) {
        return DAT_00A8B2BC[index];
    }

    if (entry == DAT_00AC119C) {
        return -2;
    }

    if (entry == DAT_00AC11A0) {
        return -2;
    }

    if (entry == DAT_00AC11B0) {
        return -2;
    }

    if (entry == DAT_00AC11B4) {
        return -2;
    }

    return entry->FUN_00696F20();
}

// FUNCTION: GAMEMD 0x46F880
//
// The same lookup against the second parallel table. Written out rather than
// shared.
int FUN_0046F880(int index)
{
    Entry_0046F810* entry = DAT_00A8DA90[index];

    if (entry->FUN_005E9440()) {
        return DAT_00A8B2DC[index];
    }

    if (entry == DAT_00AC119C) {
        return -2;
    }

    if (entry == DAT_00AC11A0) {
        return -2;
    }

    if (entry == DAT_00AC11B0) {
        return -2;
    }

    if (entry == DAT_00AC11B4) {
        return -2;
    }

    return entry->FUN_00696F50();
}

// FUNCTION: GAMEMD 0x46F8F0
void FUN_0046F8F0(HWND_ dialog)
{
    int local = DAT_00A8DA8C;
    if (local != -1) {
        int control = FUN_004E41D0(local);
        NodeNameType* node = Session_00A8B238.unknown_2858[local];
        int value;
        if (node->FUN_005E9440()) {
            value = Session_00A8B238.unknown_18.unknown_6C[local];
        } else if (node == OpenNode) {
            value = -2;
        } else if (node == ClosedNode) {
            value = -2;
        } else if (node == WaitingNode) {
            value = -2;
        } else if (node == ObserverNode) {
            value = -2;
        } else {
            value = node->FUN_00696F20();
        }
        FUN_004E49A0(dialog, control, value);
    }
    for (int i = 0; i < 8; i++) {
        if (i != local) {
            int control = FUN_004E41D0(i);
            NodeNameType* node = Session_00A8B238.unknown_2858[i];
            int value;
            if (node->FUN_005E9440()) {
                value = Session_00A8B238.unknown_18.unknown_6C[i];
            } else if (node == OpenNode) {
                value = -2;
            } else if (node == ClosedNode) {
                value = -2;
            } else if (node == WaitingNode) {
                value = -2;
            } else if (node == ObserverNode) {
                value = -2;
            } else {
                value = node->FUN_00696F20();
            }
            FUN_004E49A0(dialog, control, value);
        }
    }
}

// GLOBAL: GAMEMD 0xAC4848 -- the cache of loaded PCX pictures.
extern PCX DAT_00AC4848;
// GLOBAL: GAMEMD 0x81B1E0 -- the picture shown for the first player.
extern const char* DAT_0081B1E0;
// GLOBAL: GAMEMD 0x81B1E4 -- the picture shown for the second player.
extern const char* DAT_0081B1E4;
// FUNCTION: GAMEMD 0x603D30 (decl; reloc) -- put a picture on a control.
void FUN_00603D30(HWND_ control, void* surface);

// FUNCTION: GAMEMD 0x46FA20
//
// Put the picture of each of the two seat colours on the seat-one and seat-two controls of the dialog,
// or none when that seat has no player.
void FUN_0046FA20(HWND_ dialog)
{
    void* first = DAT_00AC4848.GetSurface(DAT_0081B1E0, 0);
    void* second = DAT_00AC4848.GetSurface(DAT_0081B1E4, 0);
    for (int i = 0; i < 8; i++) {
        Entry_0046F810* entry = DAT_00A8DA90[i];
        if (entry && entry->FUN_005E93F0()) {
            int id;
            if (i == 0)
                id = 0x6d2;
            else if (i == 1)
                id = 0x6d3;
            else
                continue;
            HWND_ item = GetDlgItem(dialog, id);
            if (item != 0) {
                if (DAT_0089E000[i]) {
                    if (i == 0)
                        FUN_00603D30(item, first);
                    else
                        FUN_00603D30(item, second);
                } else {
                    FUN_00603D30(item, 0);
                }
            }
        }
    }
}

// FUNCTION: GAMEMD 0x46FAC0
void FUN_0046FAC0(HWND_ dialog)
{
    for (int i = 0; i < 8; i++) {
        int control = FUN_004E4E60(i);
        NodeNameType* node = Session_00A8B238.unknown_2858[i];
        int value;
        if (node->FUN_005E9440()) {
            value = Session_00A8B238.unknown_18.unknown_8C[i];
        } else if (node == OpenNode) {
            value = -2;
        } else if (node == ClosedNode) {
            value = -2;
        } else if (node == WaitingNode) {
            value = -2;
        } else if (node == ObserverNode) {
            value = -2;
        } else {
            value = node->FUN_00696F50();
        }
        FUN_004E5480(dialog, control, value);
    }
}

// FUNCTION: GAMEMD 0x46FB50
//
// Enable or disable two dialog controls according to how full the list is.
// Below capacity, the first control is disabled and the second enabled; at
// capacity, only the first is touched and its state comes from the current
// slot's own flag.
//
// Both controls are fetched before either is tested, so the second lookup
// happens even on the path that never uses it.
void FUN_0046FB50(HWND_ dlg)
{
    HWND_ first = GetDlgItem(dlg, 0x6D1);
    HWND_ second = GetDlgItem(dlg, 0x5C0);

    if (first == 0) {
        return;
    }

    if (DAT_00A8DA84 < DAT_00A8D580) {
        EnableWindow(first, 0);
        if (second == 0) {
            return;
        }
        EnableWindow(second, 1);
        return;
    }

    if (DAT_0089E000[SelectedSlotIndex]) {
        EnableWindow(first, 0);
        return;
    }

    EnableWindow(first, 1);
}


struct Obj_0046FBD0;


// FUNCTION: GAMEMD 0x48D080 (decl; reloc)
void FUN_0048D080(Obj_0046FBD0*, int);
// FUNCTION: GAMEMD 0x5DAF20 (decl; reloc)
bool FUN_005DAF20(Obj_0046FBD0*, int);
// FUNCTION: GAMEMD 0x77F900 (decl; reloc)
bool FUN_0077F900(Obj_0046FBD0*, int);

struct Obj_0046FBD0
{
};


// FUNCTION: GAMEMD 0x46FBD0
unsigned char FUN_0046FBD0(Obj_0046FBD0* a1, int a2);

// FUNCTION: GAMEMD 0x46FBD0
// Branching.
unsigned char FUN_0046FBD0(Obj_0046FBD0* a1, int a2)
{
    if (Session_00A8B238.GameMode == 3)
    {
        return FUN_005DAF20(a1, a2);
    }
    if (Session_00A8B238.GameMode == 4)
    {
        return FUN_0077F900(a1, a2);
    }
    FUN_0048D080(a1, a2);
    return 0;
}

// FUNCTION: GAMEMD 0x470C00
CampaignEndScoreClass::CampaignEndScoreClass()
{
    DAT_0089E008 = -1;
    DAT_0089E020 = 0;
    DAT_0089DFD4 = 0;
}

// FUNCTION: GAMEMD 0x470C30
// Empty destructor (stores only the vtable).
CampaignEndScoreClass::~CampaignEndScoreClass()
{
}

// SYNTHETIC: GAMEMD 0x471520 -- CampaignEndScoreClass::`scalar deleting destructor'

// 0x7CA564: the CRT swprintf (cdecl, varargs).
extern "C" int __cdecl swprintf(wchar_t* pszBuffer, const wchar_t* pszFormat, ...);

// Formats a number as text and posts it to a dialog control (custom message 0x4B2).
// FUNCTION: GAMEMD 0x00470C40
void FUN_00470C40(HWND_ dialog, int controlId, int value)
{
    wchar_t text[32];
    swprintf(text, L"%d", value);
    HWND_ item = GetDlgItem(dialog, controlId);
    SendMessageA(item, 0x4B2, 0, (long)text);
}

// FUNCTION: GAMEMD 0x470C90
//
// A second copy of the same formatter. The two differ in exactly one constant:
// the line number handed to the label lookup, 0x6EA here against 0xA9 at
// 0x46D360. Same file path in both, so this is the same helper written out twice
// in one source file, at lines 169 and 1770 — which is itself the evidence that
// it was duplicated by hand rather than shared. Written out longhand rather than
// shared: the family rule in the methodology exists because look-alike siblings
// have been caught diverging, and confirming these two are identical is a check,
// not an assumption.
void FUN_00470C90(gg_wchar* buffer, int seconds)
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

    FUN_007CA564(buffer,
                 FUN_00734E60("TXT_TIME_FORMAT_HOURS", 0, DAT_0081B304, 0x6EA),
                 hours, minutes, seconds);
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x471400
// Branching.
void __cdecl FUN_00471400()
{
    if (DAT_0089E020 > 1)
    {
        FUN_007C8B48(DAT_0089DFE0, DAT_0089E020, 4, 0x46DC90);
    }
}

// GLOBAL: GAMEMD 0x89E0A4 -- the end-score caption.
extern wchar_t DAT_0089E0A4[];
// GLOBAL: GAMEMD 0x89DFC0
extern int DAT_0089DFC0;
struct CaptureSurface;
// FUNCTION: GAMEMD 0x72D300 (decl; reloc) -- load the side-dependent multiplayer screen.
void FUN_0072D300(int sideIndex);
// FUNCTION: GAMEMD 0x72D350 (decl; reloc)
void FUN_0072D350();
// FUNCTION: GAMEMD 0x72D730 (decl; reloc)
void EnsureMpScreenPalette(int sideIndex);
// FUNCTION: GAMEMD 0x72D780 (decl; reloc)
void __cdecl FreeMpScreenPalette();
// FUNCTION: GAMEMD 0x52FEC0 (decl; reloc)
void __fastcall FUN_0052FEC0(CaptureSurface* surface, unsigned char repaint);
// FUNCTION: GAMEMD 0x60D380 (decl; reloc) -- run a modal dialog, RET 4.
int FUN_0060D380(unsigned short dialogId, int (__stdcall* procedure)(void*, unsigned int, unsigned int, long), char banner);
// FUNCTION: GAMEMD 0x470D30 (decl; reloc) -- the end-score dialog procedure.
int __stdcall FUN_00470D30(void* dialog, unsigned int message, unsigned int wparam, long lparam);

// FUNCTION: GAMEMD 0x471420
void CampaignEndScoreClass::Slot1(DynamicVectorClass<MPlayerScoreType*> scores, int scratch, int posted, int number, const wchar_t* record)
{
    DAT_0089E020 = scores.Count;
    wcscpy(DAT_0089E0A4, record);
    for (int i = 0; i < DAT_0089E020; i++) {
        DAT_0089DFE0[i] = scores.Items[i];
    }
    if (DAT_0089E020 > 1) {
        qsort(DAT_0089DFE0, DAT_0089E020, sizeof(MPlayerScoreType*), FUN_0046DC90);
    }
    DAT_0089DFC0 = number;
    DAT_0089E008 = posted;
    DAT_0089DFD4 = scratch;
    int side = DAT_00A8B230->unknown_34B8;
    FUN_0072D300(side);
    EnsureMpScreenPalette(side);
    FUN_0052FEC0(0, 1);
    FUN_0060D380(0xBC7, FUN_00470D30, 0);
    FreeMpScreenPalette();
    FUN_0072D350();
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x89DFD4
int DAT_0089DFD4;
// GLOBAL: GAMEMD 0x89E008
int DAT_0089E008;
// GLOBAL: GAMEMD 0x89E020
int DAT_0089E020;
// GLOBAL: GAMEMD 0x89E050
int DAT_0089E050;
// GLOBAL: GAMEMD 0xA8D580
int DAT_00A8D580;
// GLOBAL: GAMEMD 0x81B1E8
int DAT_0081B1E8 = -1;
// GLOBAL: GAMEMD 0x7E4A98
extern const double DAT_007E4A98 = 60.0;
// GLOBAL: GAMEMD 0x81B304
extern const char DAT_0081B304[] = "D:\\ra2mdpost\\CampScor.cpp";
// GLOBAL: GAMEMD 0xAC119C
Entry_0046F810* DAT_00AC119C;
// GLOBAL: GAMEMD 0xAC11A0
Entry_0046F810* DAT_00AC11A0;
// GLOBAL: GAMEMD 0xAC11B0
Entry_0046F810* DAT_00AC11B0;
// GLOBAL: GAMEMD 0xAC11B4
Entry_0046F810* DAT_00AC11B4;
// END defined globals
