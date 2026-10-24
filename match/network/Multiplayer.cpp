// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Original translation unit Multiplayer.cpp. The name is the source-file string at 0x8309f4
//   in retail gamemd.exe v1.001, passed by the assert at 0x5d7744 inside this object's
//   code range (0x5d58b0-0x5d8a5f). Functions are in ascending retail address order.
//   Obj_/Gbl_ views below are per-function placeholder receivers. Replacing
//   them with the canonical class re-mangles their symbols, so that is left to
//   a separate rename-only change.
//
// The trivial leaves the big shape sweeps left behind: four loads of a
// container's +0x10 field, five loads of its +0x04 storage pointer, five
// constant-true returns with no arguments, three with one argument, three
// one-argument no-ops, and three stores of the ECX argument into a fixed
// global. Ordered ascending by retail address.
//
// Retail RTTI type descriptors name VectorClass<MultiplayerGameMode*> and
// DynamicVectorClass<MultiplayerGameMode*>; each address below is the vtable slot body
// of that specialization (slot owner read from the retail vtables).
// Pointer/scalar/enum element: no element layout is claimed.
//
// Paired flag probes: /GX shortens the dynamic deleting entry to 0x20
// bytes; no-GX matches its full 0x49-byte span. Other 11 bodies match both.
// Retail RTTI TypeDescriptors 0x00830830 and 0x00830868 identify
// VectorClass<MultiplayerTeam*> and DynamicVectorClass<MultiplayerTeam*>; COLs
// 0x00807020 and 0x00806FF0 point at them, and the dynamic hierarchy (CHD
// 0x00806FE0, two base classes, base array 0x00806FD0) records the vector as
// its zero-offset base.
// VectorClass<T> address point 0x007EEE54 and DynamicVectorClass<T> address
// point 0x007EEE34 are each seven-slot tables whose COL is at address-4.
// Complete function spans (control-flow closure from each entry, not the
// first RET) were checked against the pinned retail PE. This TU recovers the
// vector specialization only; it makes no constructor, original-TU, or
// complete MultiplayerTeam layout claim.
//
// 10 remaining four-byte-element resize bodies retain address-scoped
// views until their actual template classes are integrated. Recovered entries
// are bound in their native specialization implementations.
// Entry-origin spans are 0xB0 bytes. Instructions confirm Items+4, Capacity+8,
// initialization flag+C, ownership flag+D, live count+10 and Clear slot+C.
// Original source ownership and TU grouping are not established by this sweep.
//
// The source keeps the base resize as an inline call and clamps the count only
// on success. The capacity-zero branch dispatches Clear; allocation failure
// returns false. The ownership expression retains the verified short-circuit
// term so VC6 schedules SETZ and the pointer/capacity stores as retail does.
// These views remain verified under /O2 /DNDEBUG /Gy /GX.
//
// MultiplayerGameMode::InitializerBase and its Initializer<Mode> template.
// RTTI names the base ".?AVInitializerBase@MultiplayerGameMode@@" (vtable
// 0x7EEE74) and six instantiations, one per game mode. Every scalar deleting
// destructor stores the base vtable, frees the object when bit 0 of the flag
// is set, and returns `this`: the destructor is the base's empty virtual one.
// The bodies here are compiler output: the explicit instantiations below
// compile each Initializer<Mode> constructor, which emits the vtables and with
// them the `??_G` wrappers. Neither class touches a member in these bodies, so
// no layout is reconstructed.
//
//   Bytes matched against the user's retail gamemd.exe v1.001. Multiplayer.cpp
//   (the unit that also holds MultiplayerGameMode::Get 0x5D5F30 and the
//   Initializer<T> family 0x5D7FD0..): the base-class slot bodies of table
//   0x7EED60 that live here, the destructor and its deleting wrapper.
//   Globals are views of what each body reads; their owners' classes are
//   not modelled here.

#include "../core/leftover_trivial_leaf_sweep.h"

#include "../core/trivial_tu156_methods.h"

#include "../core/vector_class_operations.h"

class MultiplayerGameMode;

template class DynamicVectorClass<MultiplayerGameMode*>;

GG_STATIC_ASSERT(sizeof(MultiplayerGameMode*) == 4);
GG_STATIC_ASSERT(sizeof(VectorClass<MultiplayerGameMode* >) == 0x10);
GG_STATIC_ASSERT(sizeof(DynamicVectorClass<MultiplayerGameMode* >) == 0x18);

#include "../core/vector_class_operations.h"

class MultiplayerTeam;

// LIBRARY: GAMEMD 0x7C8B3D -- operator delete(void*), ??3@YAXPAX@Z.
// LIBRARY: GAMEMD 0x7C8E17 -- operator new(size_t), ??2@YAPAXI@Z.

template class DynamicVectorClass<MultiplayerTeam*>;

// VTABLE: GAMEMD 0x007EEE54 -- VectorClass<MultiplayerTeam*>.
// VTABLE: GAMEMD 0x007EEE34 -- DynamicVectorClass<MultiplayerTeam*>.

typedef VectorClass<MultiplayerTeam*> GgMultiplayerTeamVector;
typedef DynamicVectorClass<MultiplayerTeam*> GgMultiplayerTeamDynamicVector;
GG_STATIC_ASSERT(sizeof(MultiplayerTeam*) == 4);
GG_STATIC_ASSERT(sizeof(GgMultiplayerTeamVector) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMultiplayerTeamVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMultiplayerTeamVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMultiplayerTeamVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMultiplayerTeamVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMultiplayerTeamVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(sizeof(GgMultiplayerTeamDynamicVector) == 0x18);
GG_STATIC_ASSERT(offsetof(GgMultiplayerTeamDynamicVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(GgMultiplayerTeamDynamicVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(GgMultiplayerTeamDynamicVector, IsInitialized) == 0x0C);
GG_STATIC_ASSERT(offsetof(GgMultiplayerTeamDynamicVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(GgMultiplayerTeamDynamicVector, unknown_0E) == 0x0E);
GG_STATIC_ASSERT(offsetof(GgMultiplayerTeamDynamicVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(GgMultiplayerTeamDynamicVector, CapacityIncrement) == 0x14);

#include "../core/vector_resize_family_methods.h"

// No /GX: retail inlines the DynamicVectorClass constructor around the
// static guard with no EH frame; under /GX cl calls the whole constructor.
#include "mp_game_mode_class_get_methods.h"

// GLOBAL: GAMEMD 0xABFDA0 — the game-mode vector, a function-local static
// behind the guard byte at 0xABFD70. Each inline expansion of the accessor
// carries its own copy of the guard, which is why retail constructs the same
// object at two sites inside the loop (and again in 0x5D6130).
static inline ModeVector_005D5F30& Modes_005D5F30()
{
    static ModeVector_005D5F30 modes;
    return modes;
}

// SYNTHETIC: GAMEMD 0x5D5B20 -- exit-time destructor stub of the function-local static above
#include "mp_game_mode_class_methods.h"

#include "mp_game_mode_class_spawn_methods.h"

#include "multiplayer_game_mode.h"

#include "mp_battle_class.h"
#include "mp_game_mode_leaf_classes.h"
#include "free_for_all.h"
#include "mp_cooperative.h"

// RTTI ".?AVUnholyAlliance@@" (table 0x7EE814); only its constructor
// (0x5CB3A0) is referenced here.
class UnholyAlliance : public MultiplayerGameMode
{
public:
    UnholyAlliance(const Obj_007B66D0& a, const Obj_007B66D0& b, const Wstring& c, const Wstring& d, bool e, int f);
};

// MultiplayerGameMode::InitializerBase and Initializer<T> are declared in the
// canonical class (multiplayer_game_mode.h).

// Slot 1 of each Initializer<Mode> table (0x7EEEBC, 0x7EEEB0, 0x7EEEA4,
// 0x7EEE98, 0x7EEE8C): operator new(0x40) and the mode constructor.
// FUNCTION: GAMEMD 0x5D8170
// Initializer<MultiplayerBattle>::vf_1
// FUNCTION: GAMEMD 0x5D81B0
// Initializer<MultiplayerManBattle>::vf_1
// FUNCTION: GAMEMD 0x5D81F0
// Initializer<MultiplayerSiege>::vf_1
// FUNCTION: GAMEMD 0x5D8230
// Initializer<UnholyAlliance>::vf_1
// FUNCTION: GAMEMD 0x5D8270
// Initializer<FreeForAll>::vf_1
// FUNCTION: GAMEMD 0x5D82B0
// Initializer<MPCooperative>::vf_1
template <class T>
MultiplayerGameMode* MultiplayerGameMode::Initializer<T>::vf_1(const Obj_007B66D0& name, const Obj_007B66D0& description,
                                                               const Wstring& unknown_3, const Wstring& unknown_4,
                                                               bool unknown_5, int unknown_6)
{
    return new T(name, description, unknown_3, unknown_4, unknown_5, unknown_6);
}

template class MultiplayerGameMode::Initializer<MultiplayerManBattle>;
template class MultiplayerGameMode::Initializer<MultiplayerSiege>;
template class MultiplayerGameMode::Initializer<UnholyAlliance>;
template class MultiplayerGameMode::Initializer<FreeForAll>;
template class MultiplayerGameMode::Initializer<MPCooperative>;

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

#include "session_entry.h"

// GLOBAL: GAMEMD 0xA8B8C8 (Items 0xA8B8CC, Count 0xA8B8D8).
extern DynamicVectorClass<MultiMission*> DAT_00A8B8C8;

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
MultiplayerTeam* FUN_005C1030(int index);

// GLOBAL: GAMEMD 0xABFDD4
static bool DAT_00ABFDD4;
// GLOBAL: GAMEMD 0xABFDD5
static bool DAT_00ABFDD5;

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) -- sqrt(double).
extern "C" double __cdecl FUN_004CAC40(double value);

// LIBRARY: GAMEMD 0x7CA5D3 (decl; reloc) -- CRT wcscmp.
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

// LIBRARY: GAMEMD 0x7CAAE4 (decl; reloc) -- the CRT's __RTDynamicCast.
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

// Globals written by this TU's static initialisers (placeholder names; no
// canonical header declares them yet).
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x7E1718
extern const double DAT_007E1718;
// GLOBAL: GAMEMD 0x7EED08
extern const double DAT_007EED08;
// GLOBAL: GAMEMD 0xABFD58
extern double DAT_00ABFD58;
// GLOBAL: GAMEMD 0xABFD98
extern double DAT_00ABFD98;
// GLOBAL: GAMEMD 0xABFDB8
extern int DAT_00ABFDB8;
// GLOBAL: GAMEMD 0xABFDBC
extern int DAT_00ABFDBC;
// GLOBAL: GAMEMD 0xABFDC0
extern int DAT_00ABFDC0;
// GLOBAL: GAMEMD 0xABFDC8
extern double DAT_00ABFDC8;

// FUNCTION: GAMEMD 0x5D58E0
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_005D58E0()
{
    DAT_00ABFDC8 = DAT_00ABFD58 / DAT_007EED08;
}

// FUNCTION: GAMEMD 0x5D5900
// Static-initialiser shape: stores a floating-point expression of globals.
void __cdecl FUN_005D5900()
{
    DAT_00ABFD98 = DAT_007E1718 / DAT_00ABFDC8;
}

// FUNCTION: GAMEMD 0x5D5A80
// Static-initialiser shape: stores constants to adjacent globals.
void __cdecl FUN_005D5A80()
{
    DAT_00ABFDC0 = 0;
    DAT_00ABFDB8 = 0x80;
    DAT_00ABFDBC = 0x80;
}

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
                                         const Wstring& unknown_3,
                                         const Wstring& unknown_4,
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

// FUNCTION: GAMEMD 0x5D5F30
//
// Find the game mode whose identifier matches, or null. The loop reads the
// static through the accessor twice per pass — once for the count in the
// condition, once for the item — so the guard is expanded twice and the loop
// is not rotated (retail's `JMP` back to the guard at the head).
//
// PARTIAL (79.3%, 46/58). Retail's first guard copy calls the VectorClass
// base ctor out of line (`PUSH EBX; PUSH EBX; MOV ECX,0xABFDA0; CALL
// 0x5D89F0`) while its second copy has it inlined with size folded to zero;
// cl 8804 makes one decision for both expansions (both inline here). The
// canonical DynamicVectorClass template gives the same 79.3% as the earlier
// hand-written vector; see the history of this file for the variants tried.
// Also 79.3%, so no lever on that decision: the count through GetCount() (kept
// here), the count through a second inline accessor wrapping Modes, and the
// item through an inline operator[] together with GetCount().
MultiplayerGameMode* MultiplayerGameMode_Get(int index)
{
    int i;

    for (i = 0; i < Modes_005D5F30().GetCount(); i++) {
        MultiplayerGameMode* mode = Modes_005D5F30().Items[i];
        if (mode->unknown_28 == index) {
            return mode;
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x5D62C0  MultiplayerGameMode::vf_4 (__thiscall)
// Number every entry in the global array with its own index, except the ones
// the 0x696F10 classifier reports as -3, which get -1 instead. Retail reloads
// both the Items base and the Count on every iteration — the classifier call
// can mutate the vector, so neither can be cached — and always reports success.
//
// `this` is unused. Slot 4 (byte offset 0x10, which YRpp calls vt_entry_10).
bool MultiplayerGameMode::vf_4()
{
    for (int i = 0; i < MPGameModeArray.Count; i++) {
        if (((MPGameModeEntry**)MPGameModeArray.Items)[i]->Classify() == -3) {
            ((MPGameModeEntry**)MPGameModeArray.Items)[i]->unknown_6B = -1;
        } else {
            ((MPGameModeEntry**)MPGameModeArray.Items)[i]->unknown_6B = i;
        }
    }
    return true;
}

// FUNCTION: GAMEMD 0x5D6310
bool __stdcall FUN_005D6310(int)
{
    return true;
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

// FUNCTION: GAMEMD 0x5D6340
bool __cdecl FUN_005D6340()
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
        MultiMission* entry = DAT_00A8B8C8.Items[i];
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

// FUNCTION: GAMEMD 0x5D7030  MultiplayerGameMode::SpawnBaseUnits
//
// With bases switched off there is nothing to do. Otherwise pick the house's
// base unit type, build one, and try to place it at the house's base
// coordinate; failing that, scatter it near the base cell. A unit that could
// be placed neither way is deleted again.
bool MultiplayerGameMode::SpawnBaseUnits(HouseClass* house, int unused)
{
    if (DAT_00A8B258 == 0)
        return true;
    UnitTypeClass* type = house->FUN_00505310(RulesInstance->unknown_B20);
    if (type == 0)
        return false;
    UnitClass* unit = new UnitClass(type, house);
    if (unit == 0)
        return false;
    if (unit->vf_54(house->FUN_0050DF30(), 0))
        return true;
    if (FUN_00688ED0(unit, house->FUN_0050DEF0(), 1))
        return true;
    delete unit;
    return false;
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

// FUNCTION: GAMEMD 0x5D7570
bool MultiplayerGameMode::vf_35()
{
    return true;
}

// FUNCTION: GAMEMD 0x5D7580
// Stores its argument in a member.
Obj_005D7580* Obj_005D7580::FUN_005D7580()
{
    unknown_00 = 0x7EEE74;
    return this;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5D7CD0
// Stores its argument in a member.
void Obj_005D7CD0::FUN_005D7CD0()
{
    unknown_00 = 0x7EEE74;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x5D7F20
// MultiplayerGameMode scalar deleting destructor, emitted with the vtable by
// the constructor 0x5D5B60, with the destructor body inlined. The body is
// `inline` in this unit so that the wrapper carries it as retail's does: a
// plain definition, with or without /Ob2, leaves ??_G calling it (3.3%).
// The out-of-line copy 0x5D5D20, which the leaf destructors call, is
// therefore not emitted here and stays a declaration.
// The count is read through GetCount(): read directly, cl 8804 hoists the
// load above the vptr store. Native 0x5D7F63..0x5D7F7E releases the two
// Wstring members in reverse declaration order before the wide strings;
// automatic member destruction supplies these calls.
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
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// SYNTHETIC: GAMEMD 0x5D7FD0
// MultiplayerGameMode::InitializerBase scalar deleting destructor
// SYNTHETIC: GAMEMD 0x5D7FF0
// Initializer<MultiplayerBattle> (vtable 0x7EEEBC)
// SYNTHETIC: GAMEMD 0x5D8010
// Initializer<MultiplayerManBattle> (vtable 0x7EEEB0)
// SYNTHETIC: GAMEMD 0x5D8030
// Initializer<MultiplayerSiege> (vtable 0x7EEEA4)
// SYNTHETIC: GAMEMD 0x5D8050
// Initializer<UnholyAlliance> (vtable 0x7EEE98)
// SYNTHETIC: GAMEMD 0x5D8070
// Initializer<FreeForAll> (vtable 0x7EEE8C)
// SYNTHETIC: GAMEMD 0x5D8090
// Initializer<MPCooperative> (vtable 0x7EEE80)
template class MultiplayerGameMode::Initializer<MultiplayerBattle>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x005D80B0
// FUNCTION: GAMEMD 0x005D80E0
// FUNCTION: GAMEMD 0x005D8100
// FUNCTION: GAMEMD 0x005D82F0
// FUNCTION: GAMEMD 0x005D8330
// FUNCTION: GAMEMD 0x005D83E0
// FUNCTION: GAMEMD 0x005D8410
// FUNCTION: GAMEMD 0x005D8450
// FUNCTION: GAMEMD 0x005D8470
// FUNCTION: GAMEMD 0x005D8520
// FUNCTION: GAMEMD 0x005D8810
// FUNCTION: GAMEMD 0x005D8860
template class VectorClass<MultiplayerTeam*>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// TEMPLATE: GAMEMD 0x5D8140
// DynamicVectorClass<MultiplayerGameMode*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x5D8160
// VectorClass<MultiplayerGameMode*>::Slot6 (slot 6)
// TEMPLATE: GAMEMD 0x5D8550
// VectorClass<MultiplayerGameMode*>::operator== (slot 1)
// TEMPLATE: GAMEMD 0x5D8590
// VectorClass<MultiplayerGameMode*>::SetCapacity (slot 2)
// TEMPLATE: GAMEMD 0x5D8670
// VectorClass<MultiplayerGameMode*>::FindItemIndex (slot 4)
// TEMPLATE: GAMEMD 0x5D86B0
// VectorClass<MultiplayerGameMode*>::Slot5 (slot 5)
// TEMPLATE: GAMEMD 0x5D87E0
// DynamicVectorClass<MultiplayerGameMode*>::FindItemIndex (slot 4)
template class VectorClass<MultiplayerGameMode*>;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x5D8730
bool VectorResizeFamily::FUN_5D8730(int newsize, void** array)
{
    if (ResizeBase(newsize, array)) {
        if (Length < Count) {
            Count = Length;
        }
        return true;
    }

    return false;
}
