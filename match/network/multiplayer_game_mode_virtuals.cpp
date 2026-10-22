// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against the user's retail gamemd.exe v1.001. Multiplayer.cpp
//   (the unit that also holds MultiplayerGameMode::Get 0x5D5F30 and the
//   Initializer<T> family 0x5D7FD0..): the base-class slot bodies of table
//   0x7EED60 that live here, the destructor and its deleting wrapper.
//   Globals are views of what each body reads; their owners' classes are
//   not modelled here.


#include <windows.h>
#include "multiplayer_game_mode.h"
#include "../_layout/house_class.h"
#include "../_layout/house_type_class.h"
#include "../platform/ccini_class_methods.h"
#include "../platform/ccfile_class.h"
#include "../core/vector_class_operations.h"
#include "../_rt/gg_vslot.h"

// GLOBAL: GAMEMD 0xA80228 -- the house array (Items 0xA8022C, Count 0xA80238).
extern DynamicVectorClass<HouseClass*> HouseArray_00A80228;

struct Random_005D6890
{
    // FUNCTION: GAMEMD 0x65C7E0 (decl; reloc) -- a value in [low, high].
    int FUN_0065C7E0(int low, int high);
};

struct Scenario_005D6790
{
    unsigned int unknown_0000;     // +0x0000  bit 10 cleared by slot +0x7C, bit 9 tested by +0xCC
    char _pad0004[0x218 - 4];
    Random_005D6890 unknown_0218;  // +0x0218
    char _pad0219[0x1180 - 0x219];
    int  unknown_1180[16];         // +0x1180  house index per start slot
};
GG_STATIC_ASSERT(offsetof(Scenario_005D6790, unknown_0218) == 0x218);
GG_STATIC_ASSERT(offsetof(Scenario_005D6790, unknown_1180) == 0x1180);

// GLOBAL: GAMEMD 0xA8B230 -- ScenarioClass::Instance.
extern Scenario_005D6790* ScenarioInstance_00A8B230;

// One entry of the list at 0xA8B8C8.
struct Entry_00A8B8C8
{
    char _pad000[0x17C];
    bool unknown_17C;              // +0x17C

    // FUNCTION: GAMEMD 0x69ADF0 (decl; reloc) -- name at +0x58 is "RandMap_Sed".
    bool FUN_0069ADF0();
    // FUNCTION: GAMEMD 0x69AE10 (decl; reloc)
    bool FUN_0069AE10(Obj_007B4620* mode);
};
GG_STATIC_ASSERT(offsetof(Entry_00A8B8C8, unknown_17C) == 0x17C);

// GLOBAL: GAMEMD 0xA8B8C8 (Items 0xA8B8CC, Count 0xA8B8D8).
extern DynamicVectorClass<Entry_00A8B8C8*> DAT_00A8B8C8;

struct Session_005D6430
{
    // FUNCTION: GAMEMD 0x69B670 (decl; reloc)
    int FUN_0069B670();
};

// GLOBAL: GAMEMD 0xA8B238 -- SessionClass::Instance.
extern Session_005D6430 SessionInstance_00A8B238;

// One node of the player list at 0xA8DA74: the name first, a dword at the
// odd offset +0x6B (-1 marks an observer here), hence packed.
#pragma pack(push, 1)
struct PlayerNode_005D6890
{
    wchar_t Name[0x14];            // +0x00
    char _pad28[0x6B - 0x28];
    int  unknown_6B;               // +0x6B

    // Retail tests this through a bool (`SETZ AL; TEST AL,AL`).
    bool IsObserver() const { return unknown_6B == -1; }
};
#pragma pack(pop)
GG_STATIC_ASSERT(offsetof(PlayerNode_005D6890, unknown_6B) == 0x6B);

// GLOBAL: GAMEMD 0xA8DA74 (Items 0xA8DA78, Count 0xA8DA84).
extern DynamicVectorClass<PlayerNode_005D6890*> PlayerList_00A8DA74;

// GLOBAL: GAMEMD 0xA8B548 -- the number of teams slot 48 adds after the observers.
extern int DAT_00A8B548;
// FUNCTION: GAMEMD 0x5C1030 (decl; reloc) -- a new MultiplayerBattleTeam for an index.
MultiplayerTeam* __fastcall FUN_005C1030(int index);

// GLOBAL: GAMEMD 0xABFDD4
static bool DAT_00ABFDD4;
// GLOBAL: GAMEMD 0xABFDD5
static bool DAT_00ABFDD5;

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- sqrt(double).
extern "C" double __cdecl FUN_004CAC40(double value);
// FUNCTION: GAMEMD 0x7CA5D3 (decl; reloc) -- CRT wcscmp.
extern "C" int __cdecl wcscmp(const wchar_t* a, const wchar_t* b);

// --- Views for slot +0xCC (0x5D70F0) -------------------------------------

struct Vtbl_TechnoType_005D70F0;
struct TechnoType_005D70F0
{
    Vtbl_TechnoType_005D70F0* Vtbl;      // +0x000
    char _pad004[0x634 - 4];
    int  unknown_634;                     // +0x634  compared with the house's +0x1D4
    char _pad638[0x6CC - 0x638];
    unsigned int unknown_6CC;             // +0x6CC  per-country bit mask
    char _pad6D0[0x6D5 - 0x6D0];
    bool unknown_6D5;                     // +0x6D5
};
GG_STATIC_ASSERT(offsetof(TechnoType_005D70F0, unknown_634) == 0x634);
GG_STATIC_ASSERT(offsetof(TechnoType_005D70F0, unknown_6CC) == 0x6CC);
GG_STATIC_ASSERT(offsetof(TechnoType_005D70F0, unknown_6D5) == 0x6D5);
typedef void* (TechnoType_005D70F0::*Fn8C_005D70F0)(HouseClass* house);
typedef int (TechnoType_005D70F0::*FnAC_005D70F0)();
struct Vtbl_TechnoType_005D70F0
{
    char _pad000[0x8C];
    Fn8C_005D70F0 vt_8C;                  // +0x8C  make an object for the house
    char _pad090[0xAC - 0x90];
    FnAC_005D70F0 vt_AC;                  // +0xAC  its cost
};
GG_STATIC_ASSERT(offsetof(Vtbl_TechnoType_005D70F0, vt_8C) == 0x8C);
GG_STATIC_ASSERT(offsetof(Vtbl_TechnoType_005D70F0, vt_AC) == 0xAC);

// The element classes are the RTTI ones of the two local vectors' tables
// (DynamicVectorClass<UnitType_005D70F0*> 0x7EA2A4, <InfantryType_005D70F0*> 0x7EA324).
class UnitType_005D70F0 : public TechnoType_005D70F0 {};
class InfantryType_005D70F0 : public TechnoType_005D70F0 {};

// GLOBAL: GAMEMD 0xA83CE0 (Items 0xA83CE4, Count 0xA83CF0).
extern DynamicVectorClass<UnitType_005D70F0*> UnitTypeArray_00A83CE0;
// GLOBAL: GAMEMD 0xA8E348 (Items 0xA8E34C, Count 0xA8E358).
extern DynamicVectorClass<InfantryType_005D70F0*> InfantryTypeArray_00A8E348;

struct Rules_005D70F0
{
    char _pad000[0xB20];
    DynamicVectorClass<TechnoType_005D70F0*> unknown_B20;   // +0xB20  types never handed out
};
GG_STATIC_ASSERT(offsetof(Rules_005D70F0, unknown_B20) == 0xB20);
// GLOBAL: GAMEMD 0x8871E0 -- RulesClass::Instance.
extern Rules_005D70F0* RulesInstance_008871E0;

struct FloatSel_007500B0
{
    // FUNCTION: GAMEMD 0x7500B0 (decl; reloc)
    void Select(bool on);
};

struct Vtbl_Techno_005D70F0;
struct Techno_005D70F0
{
    Vtbl_Techno_005D70F0* Vtbl;           // +0x000
    char _pad004[0x150 - 4];
    FloatSel_007500B0 unknown_150;        // +0x150
};
GG_STATIC_ASSERT(offsetof(Techno_005D70F0, unknown_150) == 0x150);
typedef void (Techno_005D70F0::*Fn20_005D70F0)(int a);
typedef void (Techno_005D70F0::*Fn1F0_005D70F0)(int mission);
struct Vtbl_Techno_005D70F0
{
    char _pad000[0x20];
    Fn20_005D70F0 vt_20;                  // +0x020
    char _pad024[0x1F0 - 0x24];
    Fn1F0_005D70F0 vt_1F0;                // +0x1F0
};
GG_STATIC_ASSERT(offsetof(Vtbl_Techno_005D70F0, vt_20) == 0x20);
GG_STATIC_ASSERT(offsetof(Vtbl_Techno_005D70F0, vt_1F0) == 0x1F0);

// FUNCTION: GAMEMD 0x7CAAE4 (decl; reloc) -- the CRT's __RTDynamicCast.
extern "C" void* __cdecl FUN_007CAAE4(void* object, long vfDelta, void* srcType,
                                      void* dstType, int isReference);
// GLOBAL: GAMEMD 0x817AF8   .?AVObjectClass@@
extern char TypeDesc_ObjectClass[];
// GLOBAL: GAMEMD 0x817B58   .?AVTechnoClass@@
extern char TypeDesc_TechnoClass[];

// FUNCTION: GAMEMD 0x688ED0 (decl; reloc) -- place a techno near a cell.
int FUN_00688ED0(Techno_005D70F0* techno, const Cell& cell, int a);

// FUNCTION: GAMEMD 0x77D940 (decl; reloc)
bool FUN_0077D940();
// FUNCTION: GAMEMD 0x623840 (decl; reloc) -- empty the combo box.
int FUN_00623840(HWND hWnd);
// FUNCTION: GAMEMD 0x688380 (decl; reloc) -- the start cells.
DynamicVectorClass<Cell> FUN_00688380(bool flag);
// FUNCTION: GAMEMD 0x4068E0 (decl; reloc) -- the debug trace (no-op in retail).
void FUN_004068E0(const char* format, ...);

// GLOBAL: GAMEMD 0x7EED18 -- the section name, "MultiplayerDialog..." (0x83079C).
extern const char* DAT_007EED18;

// FUNCTION: GAMEMD 0x5D5B60
// Copy the four strings and the two scalars, build the mode's CCINIClass,
// load it from the file named by +0x2C when that file exists and read the
// four flags from section DAT_007EED18; MustAlly needs AlliesAllowed. It is
// what emits the vtable 0x7EED60 and the deleting destructor 0x5D7F20.
//
// PARTIAL (64.4%). Exact from the entry through the file teardown (0x5D5B60-0x5D5C7D);
// retail then tests the section lookup as a bool (`SETNZ AL; CMP AL,BL`),
// which cl 8804 folds into the branch, and every later instruction shifts.
// Tried: the plain pointer test (64.4), an inline bool helper on INIClass
// (63.0) and a bool local (64.4).
MultiplayerGameMode::MultiplayerGameMode(const Obj_007B66D0& name,
                                         const Obj_007B66D0& description,
                                         const Obj_007B4620& unknown_3,
                                         const Obj_007B4620& unknown_4,
                                         bool unknown_5, int unknown_6)
    : unknown_20(name),
      unknown_24(description),
      unknown_28(unknown_6),
      unknown_2C(unknown_3),
      unknown_30(unknown_4),
      unknown_34(unknown_5),
      unknown_38(0)
{
    unknown_04 = false;
    WonlineTournamentAllowed = true;
    WonlineClanTournamentAllowed = true;
    AlliesAllowed = true;
    MustAlly = false;

    unknown_38 = new CCINIClass;
    {
        CCFileClass file(unknown_2C);
        if (file.CCFileClass::Exists(false)) {
            unknown_38->ReadCCFile(&file, false, false);
        }
    }

    if (unknown_38 != 0 && unknown_38->GetSection(DAT_007EED18) != 0) {
        WonlineTournamentAllowed = unknown_38->FUN_005295F0(DAT_007EED18, "WonlineTournamentAllowed", WonlineTournamentAllowed);
        WonlineClanTournamentAllowed = unknown_38->FUN_005295F0(DAT_007EED18, "WonlineClanTournamentAllowed", WonlineClanTournamentAllowed);
        AlliesAllowed = unknown_38->FUN_005295F0(DAT_007EED18, "AlliesAllowed", AlliesAllowed);
        MustAlly = unknown_38->FUN_005295F0(DAT_007EED18, "MustAlly", MustAlly);
        if (MustAlly && !AlliesAllowed) {
            MustAlly = false;
        }
    }
}

// SYNTHETIC: GAMEMD 0x5D7F20
// MultiplayerGameMode scalar deleting destructor, emitted with the vtable by
// the constructor 0x5D5B60, with the destructor body inlined. The body is
// `inline` in this unit so that the wrapper carries it as retail's does: a
// plain definition, with or without /Ob2, leaves ??_G calling it (3.3%).
// The out-of-line copy 0x5D5D20, which the leaf destructors call, is
// therefore not emitted here and stays a declaration.
// The count is read through GetCount(): read directly, cl 8804 hoists the
// load above the vptr store. Obj_007B4620 declares no destructor, so the two
// copies are released through Destruct (0x7B46F0) in member order.
inline MultiplayerGameMode::~MultiplayerGameMode()
{
    for (int i = 0; i < Teams.GetCount(); i++) {
        if (Teams.Items[i] != 0) {
            delete Teams.Items[i];
        }
    }
    Teams.Clear();
    if (unknown_38 != 0) {
        delete unknown_38;
    }
    unknown_30.Destruct();
    unknown_2C.Destruct();
}

// FUNCTION: GAMEMD 0x5D5DB0
int MultiplayerGameMode::vf_10()
{
    return -2;
}

// FUNCTION: GAMEMD 0x5D5DC0
int MultiplayerGameMode::vf_11()
{
    return MustAlly ? 0 : -2;
}

// FUNCTION: GAMEMD 0x5D5DD0
int MultiplayerGameMode::vf_12()
{
    return AlliesAllowed ? 3 : -2;
}

// FUNCTION: GAMEMD 0x5D5DE0
bool MultiplayerGameMode::vf_13(int a)
{
    if (MustAlly && a == -2) {
        return false;
    }
    return a >= 0 && a <= 3;
}

// FUNCTION: GAMEMD 0x5D6320
bool MultiplayerGameMode::vf_24()
{
    return true;
}

// FUNCTION: GAMEMD 0x5D6330
bool MultiplayerGameMode::vf_25()
{
    return true;
}

// FUNCTION: GAMEMD 0x5D6350
bool MultiplayerGameMode::vf_15()
{
    return unknown_34;
}

// FUNCTION: GAMEMD 0x5D6360
bool MultiplayerGameMode::vf_16()
{
    return false;
}

// FUNCTION: GAMEMD 0x5D6370
// The first entry this mode accepts, or -1.
int MultiplayerGameMode::vf_17()
{
    int count = DAT_00A8B8C8.Count;
    for (int i = 0; i < count; i++) {
        Entry_00A8B8C8* entry = DAT_00A8B8C8.Items[i];
        bool ok;
        if (entry->FUN_0069ADF0()) {
            ok = vf_15();
        } else {
            if (!entry->unknown_17C && FUN_0077D940()) {
                continue;
            }
            ok = entry->FUN_0069AE10(&unknown_30);
        }
        if (ok) {
            return i;
        }
    }
    return -1;
}

// FUNCTION: GAMEMD 0x5D6430
int MultiplayerGameMode::vf_27()
{
    return SessionInstance_00A8B238.FUN_0069B670();
}

// FUNCTION: GAMEMD 0x5D6440
int MultiplayerGameMode::vf_28()
{
    return vf_27();
}

// FUNCTION: GAMEMD 0x5D6450
// Fill a combo box (CB_ADDSTRING, CB_SETCURSEL, CB_SETITEMDATA).
void MultiplayerGameMode::vf_18(void* hWnd, DynamicVectorClass<int>* items, int selected)
{
    FUN_00623840((HWND)hWnd);
    for (int i = 0; i < items->Count; i++) {
        int item = items->Items[i];
        LRESULT index = SendMessageA((HWND)hWnd, CB_ADDSTRING, 0, item);
        if (item == selected) {
            SendMessageA((HWND)hWnd, CB_SETCURSEL, index, 0);
        }
        SendMessageA((HWND)hWnd, CB_SETITEMDATA, index, item);
    }
}

// FUNCTION: GAMEMD 0x5D64C0
// The list-box form (LB_RESETCONTENT, 0x4CD, LB_SETCURSEL, LB_SETITEMDATA).
void MultiplayerGameMode::vf_19(void* hWnd, DynamicVectorClass<int>* items, int selected)
{
    SendMessageA((HWND)hWnd, LB_RESETCONTENT, 0, 0);
    for (int i = 0; i < items->Count; i++) {
        int item = items->Items[i];
        LRESULT index = SendMessageA((HWND)hWnd, 0x4CD, 0, item);
        if (item == selected) {
            SendMessageA((HWND)hWnd, LB_SETCURSEL, index, 0);
        }
        SendMessageA((HWND)hWnd, LB_SETITEMDATA, index, item);
    }
}

// FUNCTION: GAMEMD 0x5D6540
// Rebuild the team combo: empty it, delete and clear the old team list, ask
// slot 48 for a fresh one, then add every team's title (CB_ADDSTRING),
// preselect the one whose index is the chosen player's team value
// (CB_SETCURSEL) and attach the team to its item (CB_SETITEMDATA).
void MultiplayerGameMode::PopulateTeamDropdownForPlayer(void* hWnd, int idx)
{
    FUN_00623840((HWND)hWnd);

    for (int i = 0; i < Teams.Count; ++i) {
        MultiplayerTeam* team = Teams.Items[i];
        if (team != 0)
            delete team;
    }
    Teams.Clear();
    CreateMPTeams(Teams);

    if (idx >= 0 && idx < PlayerList_00A8DA74.Count) {
        int mode = PlayerList_00A8DA74.Items[idx]->unknown_6B;
        for (int i = 0; i < Teams.Count; ++i) {
            MultiplayerTeam* team = Teams.Items[i];
            WPARAM item = SendMessageA((HWND)hWnd, CB_ADDSTRING, 0,
                                       (LPARAM)team->unknown_04.FUN_007B7140());
            if (team->unknown_08 == mode)
                SendMessageA((HWND)hWnd, CB_SETCURSEL, item, 0);
            SendMessageA((HWND)hWnd, CB_SETITEMDATA, item, (LPARAM)team);
        }
    }
}

// FUNCTION: GAMEMD 0x5D6690
// The base team list: the observers first, then one team per index.
void MultiplayerGameMode::CreateMPTeams(DynamicVectorClass<MultiplayerTeam*>& teams)
{
    teams.AddItem(new MultiplayerObserverTeam);
    for (int i = 1; i <= DAT_00A8B548; ++i)
        teams.AddItem(FUN_005C1030(i));
}

// FUNCTION: GAMEMD 0x5D6790
bool MultiplayerGameMode::vf_31()
{
    ScenarioInstance_00A8B230->unknown_0000 &= ~0x400;
    return true;
}

// FUNCTION: GAMEMD 0x5D67A0
bool MultiplayerGameMode::vf_7(int)
{
    return true;
}

// FUNCTION: GAMEMD 0x5D6BE0
// Put every house with a start slot on its start cell and record which house
// took each slot.
bool MultiplayerGameMode::vf_32(bool a)
{
    DynamicVectorClass<Cell> starts = FUN_00688380(a);
    for (int i = 0; i < HouseArray_00A80228.Count; i++) {
        HouseClass* house = HouseArray_00A80228.Items[i];
        if (!((HouseTypeClass*)house->Type)->MultiplayPassive) {
            int slot = house->StartingPoint;
            if (slot != -2) {
                house->FUN_0050E000(starts.Items[slot]);
                ScenarioInstance_00A8B230->unknown_1180[slot] = i;
            }
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x5D6C70
// Houses that already own a start slot go there; the others ask slot +0xC4.
bool MultiplayerGameMode::vf_33(bool a)
{
    bool taken[16];
    DynamicVectorClass<Cell> starts = FUN_00688380(a);
    int i;

    for (i = 0; i < 16; i++) {
        if (ScenarioInstance_00A8B230->unknown_1180[i] == -1) {
            taken[i] = false;
        } else {
            taken[i] = true;
        }
    }
    for (i = 0; i < HouseArray_00A80228.Count; i++) {
        HouseClass* house = HouseArray_00A80228.Items[i];
        if (!((HouseTypeClass*)house->Type)->MultiplayPassive) {
            bool found = false;
            int slot = -1;
            for (int j = 0; j < 16; j++) {
                if (ScenarioInstance_00A8B230->unknown_1180[j] == i) {
                    found = true;
                    slot = j;
                }
            }
            if (!found) {
                FUN_004068E0("Assigning Starting Points for house %d (%s)\n", i, ((HouseTypeClass*)house->Type)->ID);
                Cell cell = vf_49(i, starts, taken);
                house->FUN_0050E000(cell);
            } else {
                house->FUN_0050E000(starts.Items[slot]);
            }
        }
    }
    return true;
}

// Whether the house is a human player whose node in the player list is an
// observer. Inline: both copies sit in 0x5D6890.
static inline bool IsObserverHouse(int house)
{
    HouseClass* h = HouseArray_00A80228.Items[house];
    if (h != 0) {
        for (int j = 0; j < PlayerList_00A8DA74.Count; j++) {
            if (h->FUN_0050B730()
                && wcscmp(h->UIName, PlayerList_00A8DA74.Items[j]->Name) == 0) {
                return PlayerList_00A8DA74.Items[j]->IsObserver();
            }
        }
    }
    return false;
}

// FUNCTION: GAMEMD 0x5D6890
// Pick a start cell for a house. The first house (no slot taken yet) gets a
// random cell; an observer gets a random cell, or the first taken one; every
// other house gets the free cell farthest in sum from the taken ones.
//
// PARTIAL (20.5% positional, 80.2% aligned: 219/273). CAPPED after three
// variants: (1) the observer search written out twice in place (20.9/82.1,
// but it folds retail's `SETZ AL; TEST AL,AL` away); (2) the search as one
// inline helper returning the node's observer test (kept: it reproduces the
// SETZ); (3) the distance through a Cell difference read as two ints.
// Remaining: the random-index argument order (count before the scenario
// pointer), the local slot of the house pointer (+0x14 vs +0x10) and retail's
// separate epilogue on the first-house path, which cl 8804 tail-merges.
Cell MultiplayerGameMode::vf_49(int house, DynamicVectorClass<Cell>& starts, bool* taken)
{
    int i;
    for (i = 0; i < starts.Count; i++) {
        if (ScenarioInstance_00A8B230->unknown_1180[i] != -1) {
            break;
        }
    }

    if (i == starts.Count) {
        DAT_00ABFDD4 = false;
        DAT_00ABFDD5 = false;
        if (IsObserverHouse(house)) {
            int slot = ScenarioInstance_00A8B230->unknown_0218.FUN_0065C7E0(0, starts.Count - 1);
            taken[slot] = true;
            ScenarioInstance_00A8B230->unknown_1180[slot] = house;
            DAT_00ABFDD4 = true;
            FUN_004068E0("Observer observing random cell: %d (%d,%d)\n",
                         slot, starts.Items[slot].X, starts.Items[slot].Y);
            return starts.Items[slot];
        }
        int slot = ScenarioInstance_00A8B230->unknown_0218.FUN_0065C7E0(0, starts.Count - 1);
        FUN_004068E0("First cell taken: %d (%d,%d)\n",
                     slot, starts.Items[slot].X, starts.Items[slot].Y);
        taken[slot] = true;
        ScenarioInstance_00A8B230->unknown_1180[slot] = house;
        return starts.Items[slot];
    }

    if (DAT_00ABFDD4 && !DAT_00ABFDD5) {
        DAT_00ABFDD5 = true;
        ScenarioInstance_00A8B230->unknown_1180[i] = house;
        return starts.Items[i];
    }

    if (IsObserverHouse(house)) {
        DAT_00ABFDD5 = true;
        DAT_00ABFDD4 = true;
        FUN_004068E0("Observer Observing cell: %d (%d,%d)\n",
                     i, starts.Items[i].X, starts.Items[i].Y);
        return starts.Items[i];
    }

    int best = -1;
    int bestDistance = -1;
    for (int k = 0; k < starts.Count; k++) {
        if (!taken[k]) {
            int distance = 0;
            for (int m = 0; m < starts.Count; m++) {
                if (taken[m]) {
                    Cell d;
                    d.X = starts.Items[k].X - starts.Items[m].X;
                    d.Y = starts.Items[k].Y - starts.Items[m].Y;
                    int x = d.X;
                    int y = d.Y;
                    distance += (short)FUN_004CAC40((double)x * x + (double)y * y);
                }
            }
            if (distance > bestDistance) {
                bestDistance = distance;
                best = k;
            }
        }
    }
    taken[best] = true;
    ScenarioInstance_00A8B230->unknown_1180[best] = house;
    FUN_004068E0("Starting cell taken: %d (%d,%d)\n",
                 best, starts.Items[best].X, starts.Items[best].Y);
    return starts.Items[best];
}

// FUNCTION: GAMEMD 0x5D70F0
// Spend the house's start budget on random start units: unit types first while
// more than a third of the budget is left, infantry after. Twenty failed
// placements end it early. False when no type qualifies.
//
// PARTIAL (5.0% positional, 63.5% aligned: 190/299). One draft, capped:
// retail calls the VectorClass base constructors out of line (0x5D8950,
// 0x5D89A0) where cl 8804 expands the canonical template constructor in
// place, which shifts the whole frame set-up; the same out-of-line/inline
// split already caps MultiplayerGameMode::Get (0x5D5F30).
bool MultiplayerGameMode::vf_51(HouseClass* house, int* budget)
{
    if (*budget <= 0) {
        return true;
    }

    int initial = *budget;
    DynamicVectorClass<UnitType_005D70F0*> units;
    DynamicVectorClass<InfantryType_005D70F0*> infantry;
    unsigned int mask = 1 << ((HouseTypeClass*)house->Type)->ArrayIndex;
    int i;

    for (i = 0; i < UnitTypeArray_00A83CE0.Count; i++) {
        UnitType_005D70F0* type = UnitTypeArray_00A83CE0.Items[i];
        if (type->unknown_6D5 && (type->unknown_6CC & mask)
            && type->unknown_634 <= house->TechLevel) {
            int k;
            for (k = 0; k < RulesInstance_008871E0->unknown_B20.Count; k++) {
                if (RulesInstance_008871E0->unknown_B20.Items[k] == type) {
                    break;
                }
            }
            if (k == RulesInstance_008871E0->unknown_B20.Count) {
                units.AddItem(type);
            }
        }
    }
    for (i = 0; i < InfantryTypeArray_00A8E348.Count; i++) {
        InfantryType_005D70F0* type = InfantryTypeArray_00A8E348.Items[i];
        if (type->unknown_6D5 && (type->unknown_6CC & mask)
            && type->unknown_634 <= house->TechLevel) {
            infantry.AddItem(type);
        }
    }

    if (units.Count == 0 && infantry.Count == 0) {
        return false;
    }

    int tries = 20;
    while (*budget > 0 && tries > 0) {
        TechnoType_005D70F0* type;
        if (*budget > initial / 3 && units.Count != 0) {
            type = units.Items[ScenarioInstance_00A8B230->unknown_0218.FUN_0065C7E0(0, units.Count - 1)];
        } else {
            type = infantry.Items[ScenarioInstance_00A8B230->unknown_0218.FUN_0065C7E0(0, infantry.Count - 1)];
        }
        Techno_005D70F0* techno = (Techno_005D70F0*)FUN_007CAAE4(
            (type->*type->Vtbl->vt_8C)(house), 0, TypeDesc_ObjectClass, TypeDesc_TechnoClass, 0);
        if (FUN_00688ED0(techno, house->FUN_0050DEF0(), 4) == 0) {
            if (techno != 0) {
                (techno->*techno->Vtbl->vt_20)(1);
            }
            tries--;
        } else {
            *budget -= (type->*type->Vtbl->vt_AC)();
            if (ScenarioInstance_00A8B230->unknown_0000 & 0x200) {
                techno->unknown_150.Select(true);
            }
            if (house->FUN_0050B730()) {
                (techno->*techno->Vtbl->vt_1F0)(5);
            } else {
                (techno->*techno->Vtbl->vt_1F0)(11);
            }
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x5D74A0
// Ally every pair of houses that share a team.
//
// PARTIAL (18.5%). CAPPED after three variants: an inline team accessor,
// `continue`-style guards and a cached team local all leave it at 18.5%.
// Retail keeps the count in EDX, copies the house to ECX before each team
// read (`MOV ECX,EBX; MOV ECX,[ECX+0x1605C]`) and compares the passive flag
// in memory; cl 8804 keeps the count in ESI.
bool MultiplayerGameMode::vf_34()
{
    for (int i = 0; i < HouseArray_00A80228.Count; i++) {
        HouseClass* house = HouseArray_00A80228.Items[i];
        if (!((HouseTypeClass*)house->Type)->MultiplayPassive
            && house->StartingAllies != -2 && house->StartingAllies != -1) {
            for (int j = i + 1; j < HouseArray_00A80228.Count; j++) {
                HouseClass* other = HouseArray_00A80228.Items[j];
                if (!((HouseTypeClass*)other->Type)->MultiplayPassive
                    && HouseArray_00A80228.Items[i]->StartingAllies == other->StartingAllies) {
                    house->FUN_004F9B70(other, false);
                    other->FUN_004F9B70(house, false);
                }
            }
        }
    }
    return true;
}
