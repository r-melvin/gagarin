// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Original translation unit MPCoop.cpp. The name is the source-file string at 0x82dc4c
//   in retail gamemd.exe v1.001, passed by the assert at 0x5c2272 inside this object's
//   code range (0x5c10f0-0x5c5aef). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The remaining address-scoped scalar deleting destructors of the 30-byte family,
// by retail address. Each runs its class's real destructor, then frees the
// object when bit 0 of the flag argument is set, and returns `this`.
//
// The header initialiser group at 0x5C1120, 0x5C1140 and 0x5C12C0
// (header_init_shapes.h): two derived doubles and a {128, 128, 0} coordinate,
// in __xc order. The divisor at 0x7EE268 reads 60.0 (ghidra memory read).
//
//   MPCoop.cpp (0x5C10F0..0x5C5AEF).

#include "deleting_dtor_sweep.h"
#include "../network/transport/winsock_interface_class.h"
#include "../_layout/pipe.h"
#include "../_layout/straw.h"

#include "header_init_shapes.h"

// GLOBAL: GAMEMD 0xABF420
extern double DAT_00ABF420;
// GLOBAL: GAMEMD 0x7EE268
const double DAT_007EE268 = 60.0;

#include "trivial_tu144_methods.h"

#include <windows.h>
#include "../network/mp_cooperative.h"
#include "vector_class_operations.h"
#include "../network/mp_game_mode_class_methods.h"
#include "../economy/house_class_accessor_methods.h"

#include <string.h>

// LIBRARY: GAMEMD 0x7CD680 -- CRT _strnicmp (cdecl, locale-flag fast path).
extern "C" int __cdecl _strnicmp(const char* a, const char* b, size_t n);

// A record handed out by the 0x89F518 list: three 0x104-byte names behind +0x0C.
// Its +0x10 vector holds DynamicVectorClass-shaped string lists (Items +0x04,
// Count +0x10).
struct Rec_0049E3B0
{
    char  unknown_00[0x0C];   // +0x00
    char (*Names)[0x104];     // +0x0C three MAX_PATH-sized strings
    DynamicVectorClassLayout Lists;   // +0x10 (Items +0x14, Count +0x20)
};
GG_STATIC_ASSERT(offsetof(Rec_0049E3B0, Names) == 0x0C);
GG_STATIC_ASSERT(offsetof(Rec_0049E3B0, Lists) == 0x10);

// FUNCTION: GAMEMD 0x49D9F0 (decl; reloc) -- look a name up; an index or -1.
int __fastcall FUN_0049D9F0(const char* name);

// FUNCTION: GAMEMD 0x734E60 (decl; reloc) -- StringTable::LoadString.
wchar_t* __fastcall StringTable_LoadString(const char* label, int* out,
                                           const char* file, int line);

// STRING: GAMEMD 0x82DC78 -- "GUI:Random".
extern const char STR_0082DC78[];
// STRING: GAMEMD 0x82DC4C -- this module's __FILE__ ("D:\\ra2mdpost\\MPCoop.cpp").
extern const char STR_0082DC4C[];

// FUNCTION: GAMEMD 0x5EBC00 (decl; reloc) -- __fastcall (dialog, mode).
void __fastcall FUN_005EBC00(HWND dialog, int mode);

// FUNCTION: GAMEMD 0x5E8760 (decl; reloc) -- the caller tests AL, so the
// result is a bool here (the matched body is typed int in netshare_slot_nodes).
bool __fastcall FUN_005E8760();

// LIBRARY: GAMEMD 0x7C8EF4 -- CRT sprintf.
extern "C" int __cdecl sprintf(char* buffer, const char* format, ...);
// STRING: GAMEMD 0x82DC64 -- "NAME:COOPDESC%d%d".
extern const char STR_0082DC64[];
// GLOBAL: GAMEMD 0xA8EB68 -- the value posted with message 0x405.
extern LPARAM DAT_00A8EB68;

// FUNCTION: GAMEMD 0x4E37D0 (decl; reloc) -- the control id for slot `index`.
int __fastcall FUN_004E37D0(int index);

// FUNCTION: GAMEMD 0x4E3F70 (decl; reloc) -- __fastcall (dialog, id) + one stack word.
void __fastcall FUN_004E3F70(HWND dialog, int id, int value);

// FUNCTION: GAMEMD 0x5E26C0 (decl; reloc) -- a dialog handle, or null.
HWND __fastcall FUN_005E26C0();

// GLOBAL: GAMEMD 0xA8BB0C -- the session's player limit.
extern int DAT_00A8BB0C;
// GLOBAL: GAMEMD 0xA8DA90 -- the eight lobby slots.
extern MPGameModeEntry* DAT_00A8DA90[8];

// An entry of the 0xA83C98 vector; +0x60 is handed to the combo as item text.
struct Entry_00A83C9C
{
    char   unknown_00[0x60];  // +0x00
    const wchar_t* unknown_60; // +0x60 item text
};
// GLOBAL: GAMEMD 0xA83C9C -- that vector's Items.
extern Entry_00A83C9C** DAT_00A83C9C;
// GLOBAL: GAMEMD 0xA83CA8 -- that vector's Count.
extern int DAT_00A83CA8;
struct List_0089F518
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x49E3B0 (decl; reloc) -- fetch record `index` into *out; RET 8.
    void FUN_0049E3B0(int index, Rec_0049E3B0** out);
    // FUNCTION: GAMEMD 0x49E4F0 (decl; reloc) -- the record count into *out; RET 4.
    void FUN_0049E4F0(int* out);
};
// GLOBAL: GAMEMD 0x89F518
extern List_0089F518 DAT_0089F518;
// GLOBAL: GAMEMD 0x89F574 -- the record count.
extern int DAT_0089F574;
// An entry of the 0xA8B8C8 vector; its name starts at +0x58.
struct Entry_00A8B8CC
{
    char unknown_00[0x58];    // +0x00
    char Name[1];             // +0x58
};
// GLOBAL: GAMEMD 0xA8B8CC -- that vector's Items.
extern Entry_00A8B8CC** DAT_00A8B8CC;
// GLOBAL: GAMEMD 0xA8B254 -- the selected entry index (0 = none).
extern int DAT_00A8B254;

// GLOBAL: GAMEMD 0xABF460 -- eight per-entry values (`MOV ECX,8; REP STOSD`).
int DAT_00ABF460[8];

// SYNTHETIC: GAMEMD 0x5C1120
// GLOBAL: GAMEMD 0xABF490
double DAT_00ABF490 = DAT_00ABF420 / DAT_007EE268;

// SYNTHETIC: GAMEMD 0x5C1140
// GLOBAL: GAMEMD 0xABF458
double DAT_00ABF458 = 1.0 / DAT_00ABF490;

// SYNTHETIC: GAMEMD 0x5C12C0
// GLOBAL: GAMEMD 0xABF480
HeaderCoordInit DAT_00ABF480(128, 128, 0);

// FUNCTION: GAMEMD 0x5C1470
// The base gets `false` for its fifth argument. Then empty the campaign list
// (keeping its capacity) and refill it with one campaign per record of the
// 0x89F518 list.
//
// PARTIAL (56.6%). Everything up to the +0x324 member matches; retail then
// calls the out-of-line VectorClass<CoopCampaignClass*> constructor 0x5C5A80
// while cl expands it inline (it keeps the VectorClass<int> calls out of line),
// shifting the rest. Declaring the instantiation `extern template` reaches
// 91.8% but also un-inlines the destructor's vector teardown (0x5C1640 drops
// to 41.3%), so it is not kept; the decision is cl's inliner, not the source.
MPCooperative::MPCooperative(const Obj_007B66D0& a, const Obj_007B66D0& b, const Obj_007B4620& c, const Obj_007B4620& d, bool e, int f)
    : MultiplayerGameMode(a, b, c, d, false, f)
{
    unknown_40 = 0;
    unknown_44 = 0;
    unknown_33C = 0;
    unknown_50 = 0;
    unknown_04 = false;
    unknown_48 = false;
    unknown_49 = false;
    unknown_4C = 0;
    unknown_340 = true;

    for (int i = Campaigns.Count - 1; i >= 0; i--) {
        delete Campaigns.Items[i];
    }
    int capacity = Campaigns.Capacity;
    Campaigns.Clear();
    Campaigns.SetCapacity(capacity, 0);

    int count;
    DAT_0089F518.FUN_0049E4F0(&count);
    for (int n = 0; n < count; n++) {
        CoopCampaignClass* campaign = new CoopCampaignClass;
        campaign->FUN_0049CAF0(n);
        Campaigns.AddItem(campaign);
    }
}

// FUNCTION: GAMEMD 0x5C1640
MPCooperative::~MPCooperative()
{
    if (unknown_40 != 0) {
        delete unknown_40;
        unknown_40 = 0;
    }
    int i;
    for (i = Campaigns.Count - 1; i >= 0; i--) {
        delete Campaigns.Items[i];
    }
    Campaigns.Clear();
    for (i = Nodes.Count - 1; i >= 0; i--) {
        operator delete(Nodes.Items[i]);
    }
    int capacity = Nodes.Capacity;
    Nodes.Clear();
    Nodes.SetCapacity(capacity, 0);
    if (unknown_50 != 0) {
        delete unknown_50;
        unknown_50 = 0;
    }
    unknown_04 = false;
}

// FUNCTION: GAMEMD 0x5C1980
// The last record one of whose three names prefixes-matches (case-blind, for
// the name's own length) the selected entry's name, or -1.
//
// PARTIAL (11.9%). Same blocks and calls; retail keeps the result in a stack
// slot (`SUB ESP,8`, record index in EBP, name offset in EBX) where cl gives
// the result a register, so every instruction shifts. Tried a nested if with a
// name local (10.2%), one && condition (11.9%) and the names as char[][0x104]
// (11.9%).
int FUN_005C1980()
{
    int found = -1;
    for (int i = 0; i < DAT_0089F574; i++) {
        Rec_0049E3B0* rec;
        DAT_0089F518.FUN_0049E3B0(i, &rec);
        for (int j = 0; j < 3; j++) {
            if (DAT_00A8B254 != 0
                && _strnicmp(DAT_00A8B8CC[DAT_00A8B254]->Name, rec->Names[j],
                             strlen(rec->Names[j])) == 0) {
                found = i;
            }
        }
    }
    return found;
}

// FUNCTION: GAMEMD 0x5C1CB0
// Stores its argument in a member. Vtable slot 9 of MPCooperative (RTTI).
void Obj_005C1CB0::FUN_005C1CB0()
{
    unknown_340 = 1;
}

// FUNCTION: GAMEMD 0x5C21D0
// Show or hide the co-op description and the four related controls. The
// description text comes from "NAME:COOPDESC<a+1><b+1>" when the campaign at
// +0x40 reports both of its values.
//
// PARTIAL (3.4%). Same blocks, calls and constants; register allocation
// differs from the first instruction: retail keeps the `ok` flag in BL and
// re-reads `show` from its stack slot, cl keeps `show` in BL and spills `ok`.
// Tried: `ok` declared in the inner block (2.8%), at the top (3.4%), and the
// the flag as an int (2.8%).
void MPCooperative::FUN_005C21D0(HWND dialog, bool show)
{
    bool ok = true;
    if (show) {
        FUN_005EBC00(dialog, 2);
    }
    if (unknown_40 != 0) {
        int a;
        int b;
        if (!unknown_40->FUN_0049BC80(&a)) {
            ok = false;
        }
        if (unknown_40->FUN_0049BCC0(&b) && ok) {
            char label[0x40];
            sprintf(label, STR_0082DC64, a + 1, b + 1);
            HWND text = GetDlgItem(dialog, 0x72F);
            if (text == 0) {
                return;
            }
            SendMessageA(text, 0x4B2, 0,
                (LPARAM)StringTable_LoadString(label, 0, STR_0082DC4C, 0x281));
            if (show) {
                ShowWindow(text, SW_SHOW);
                InvalidateRect(text, 0, FALSE);
            } else {
                ShowWindow(text, SW_HIDE);
                InvalidateRect(text, 0, FALSE);
            }
        }
    }

    HWND control = GetDlgItem(dialog, 0x732);
    if (control != 0) {
        PostMessageA(control, 0x4AC, 0, 0);
        PostMessageA(control, 0x406, 1, 0x20000);
        PostMessageA(control, 0x405, 1, DAT_00A8EB68);
        ShowWindow(control, show ? SW_SHOW : SW_HIDE);
        EnableWindow(control, FUN_005E8760() ? TRUE : FALSE);
        InvalidateRect(control, 0, TRUE);
    }
    control = GetDlgItem(dialog, 0x78E);
    if (control != 0) {
        ShowWindow(control, show ? SW_SHOW : SW_HIDE);
    }
    control = GetDlgItem(dialog, 0x78D);
    if (control != 0) {
        ShowWindow(control, show ? SW_SHOW : SW_HIDE);
    }
    control = GetDlgItem(dialog, 0x78C);
    if (control != 0) {
        ShowWindow(control, show ? SW_SHOW : SW_HIDE);
    }
}

// FUNCTION: GAMEMD 0x5C23B0
// Refill one combo with the choices of the current campaign record: a
// "GUI:Random" item (data -2) when there is more than one, then every listed
// name that resolves to a valid entry, tagged with that entry's index.
//
// PARTIAL (98.3%): the entry's +0x60 text is loaded into EDX where retail
// uses EAX (multiset identical). Typing the field LPARAM or wchar_t* gives
// the same; only a redundant `text` local reaches 100%, which the no-steering
// rule excludes.
void MPCooperative::FUN_005C23B0(HWND dialog, int id)
{
    int count = DAT_00A83CA8;
    if (count == 0) {
        return;
    }
    HWND combo = GetDlgItem(dialog, id);
    ShowWindow(combo, SW_HIDE);
    SendMessageA(combo, CB_RESETCONTENT, 0, 0);

    Rec_0049E3B0* rec;
    int index = 0;
    DAT_0089F518.FUN_0049E3B0(unknown_33C, &rec);
    if (rec == 0 || rec->Lists.Count == 0) {
        return;
    }
    if (unknown_40 == 0 || !unknown_40->FUN_0049BCC0(&index)) {
        index = 0;
    }
    if (index >= rec->Lists.Count) {
        return;
    }
    int n = ((DynamicVectorClassLayout**)rec->Lists.Items)[index]->Count;
    if (n > 1) {
        LRESULT item = SendMessageA(combo, 0x4C2, 0,
            (LPARAM)StringTable_LoadString(STR_0082DC78, 0, STR_0082DC4C, 0x2ED));
        SendMessageA(combo, CB_SETITEMDATA, item, -2);
    }
    for (int i = 0; i < n; i++) {
        int entry = FUN_0049D9F0(((char**)((DynamicVectorClassLayout**)rec->Lists.Items)[index]->Items)[i]);
        if (entry >= 0 && entry < count) {
            LRESULT item = SendMessageA(combo, 0x4C2, 0, (LPARAM)DAT_00A83C9C[entry]->unknown_60);
            SendMessageA(combo, CB_SETITEMDATA, item, entry);
        }
    }
    SendMessageA(combo, CB_SETCURSEL, 0, 0);
    ShowWindow(combo, SW_SHOW);
}

// FUNCTION: GAMEMD 0x5C2500
// For every slot up to the player limit: refill its combo, then select the
// random item (-2) when the campaign record lists several choices, else the
// one listed name's entry; mirror the choice into the slot. Then show the
// co-op controls on the dialog 0x5E26C0 reports.
void MPCooperative::FUN_005C2500(HWND dialog)
{
    if (dialog == 0) {
        return;
    }
    int limit = DAT_00A8BB0C;
    Rec_0049E3B0* rec;
    int index = 0;
    DAT_0089F518.FUN_0049E3B0(unknown_33C, &rec);
    if (rec == 0 || rec->Lists.Count == 0) {
        return;
    }
    if (unknown_40 != 0) {
        if (!unknown_40->FUN_0049BCC0(&index)) {
            index = 0;
        }
    } else {
        index = 0;
    }
    if (index >= rec->Lists.Count) {
        return;
    }
    int n = ((DynamicVectorClassLayout**)rec->Lists.Items)[index]->Count;
    for (int i = 0; i < limit; i++) {
        int id = FUN_004E37D0(i);
        FUN_005C23B0(dialog, id);
        if (n > 1) {
            FUN_004E3F70(dialog, id, -2);
            DAT_00A8DA90[i]->FUN_00696F90(-2);
        } else {
            int entry = FUN_0049D9F0(((char**)((DynamicVectorClassLayout**)rec->Lists.Items)[index]->Items)[0]);
            FUN_004E3F70(dialog, id, entry);
            DAT_00A8DA90[i]->FUN_00696F90(entry);
        }
    }
    FUN_005EBC00(dialog, limit);
    HWND shown = FUN_005E26C0();
    if (shown != 0) {
        FUN_005C21D0(shown, true);
    }
}

// FUNCTION: GAMEMD 0x5C26D0
// Reset the table to -2, then fill one slot per game-mode array entry from
// the entry's 0x696F30.
void FUN_005C26D0()
{
    int i;

    for (i = 0; i < 8; i++) {
        DAT_00ABF460[i] = -2;
    }
    int count = MPGameModeArray.Count;
    for (i = 0; i < count; i++) {
        DAT_00ABF460[i] = ((MPGameModeEntry**)MPGameModeArray.Items)[i]->FUN_00696F30();
    }
}

// FUNCTION: GAMEMD 0x5C2D00
// Give `house` a start spot. While fewer spots are taken than there are human
// houses, pick a random co-op spot and walk forward (wrapping) to a free one;
// otherwise take the first free spot from the co-op count onwards. Mark it
// taken and record the house on the scenario.
//
// PARTIAL (56.0%). cl loads the scenario pointer once before the branch;
// retail loads it inside each arm (`MOV ECX,[0xA8B230]; MOV EAX,[ECX+0x11E4];
// ADD ECX,0x218`). Swapping the arms gives 45.3%. Caching the spot count in a
// local first reaches 90.7% (only the LEA/ADD colouring left) but is a value
// copy with no semantic role, so it is not kept.
void MPCooperative::FUN_005C2D00(int house, DynamicVectorClassLayout* spots, bool* taken)
{
    int used = 0;
    int i;
    for (i = 0; i < spots->Count; i++) {
        if (taken[i]) {
            used++;
        }
    }

    int humans = 0;
    for (i = 0; i < HouseClassArray.Count; i++) {
        HouseClass* h = ((HouseClass**)HouseClassArray.Items)[i];
        if (h != 0 && h->IsControlledByHuman()) {
            humans++;
        }
    }

    int spot;
    if (used < humans) {
        spot = MPCoopScenario_00A8B230->Random.FUN_0065C7E0(
            0, MPCoopScenario_00A8B230->NumCoopHumanStartSpots - 1);
        while (taken[spot]) {
            spot = (spot + 1) % MPCoopScenario_00A8B230->NumCoopHumanStartSpots;
        }
    } else {
        spot = MPCoopScenario_00A8B230->NumCoopHumanStartSpots;
        while (taken[spot] && spot < spots->Count) {
            spot++;
        }
    }
    taken[spot] = true;
    MPCoopScenario_00A8B230->StartHouse[spot] = house;
}

// FUNCTION: GAMEMD 0x5C36F0
// Tail-forwards to another function. Vtable slot 35 of MPCooperative (RTTI).
void Obj_005C36F0::FUN_005C36F0()
{
    FUN_005D7570();
}

// FUNCTION: GAMEMD 0x5C3700
// Returns a constant boolean. Vtable slot 15 of MPCooperative (RTTI).
bool Obj_005C3700::FUN_005C3700() const
{
    return false;
}

// FUNCTION: GAMEMD 0x5C3EC0
// Replace the helper at +0x40 with a fresh one, run its 0x49CAF0(0), and with
// exactly two entries in the game-mode array hand both to 0x49B760. True when
// the helper exists.
bool MPCooperative::FUN_005C3EC0()
{
    if (unknown_40 != 0) {
        delete unknown_40;
    }
    unknown_40 = 0;
    unknown_40 = new CoopCampaignClass;
    unknown_40->FUN_0049CAF0(0);
    if (MPGameModeArray.Count == 2) {
        unknown_40->FUN_0049B760(((void**)MPGameModeArray.Items)[0],
                                 ((void**)MPGameModeArray.Items)[1]);
    }
    return unknown_40 ? true : false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5C42C0
// Returns a constant. Vtable slot 38 of MPCooperative (RTTI).
int Obj_005C42C0::FUN_005C42C0() const
{
    return 2;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5C4EE0
// Returns a constant boolean. Vtable slot 1 of MPCooperative (RTTI).
bool Obj_005C4EE0::FUN_005C4EE0() const
{
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5C4EF0
// Returns a constant boolean. Vtable slot 2 of MPCooperative (RTTI).
bool Obj_005C4EF0::FUN_005C4EF0() const
{
    return true;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5C4F00
// Returns a constant boolean. Vtable slot 47 of MPCooperative (RTTI).
bool Obj_005C4F00::FUN_005C4F00() const
{
    return false;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5C4F10
void* Obj_5C4F10::FUN_5C4F10(unsigned int flags)
{
    FUN_005C1640(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}
