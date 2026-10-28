// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   The one MultiplayerGameMode class, read off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI. Class names are the RTTI type
//   descriptors under each table's complete object locator:
//     0x7EED60 `.?AVMultiplayerGameMode@@`  (52 slots, 0x7EED60..0x7EEE2F)
//     0x7EE6FC `.?AVMultiplayerSiege@@`     (52 slots)
//     0x7EEE34 `.?AV?$DynamicVectorClass@PAVMultiplayerTeam@@@@` (the +0x08 member)
//   The other leaf tables (MultiplayerBattle 0x7EE184, MPCooperative 0x7EE27C,
//   FreeForAll 0x7EE424, MultiplayerManBattle 0x7EE50C, Megawealth 0x7EE5F4,
//   UnholyAlliance 0x7EE814) inherit most of these bodies; their classes live
//   in mp_battle_class.h, mp_cooperative.h, free_for_all.h and
//   mp_game_mode_leaf_classes.h.
//
//   Layout, from the constructor 0x5D5B60 (RET 0x18) and the destructor
//   0x5D5D20: sizeof 0x40 (every concrete mode is allocated with PUSH 0x40).
//   +0x04 byte (0); +0x08 the team vector (vptr 0x7EEE34, CapacityIncrement
//   10); +0x20/+0x24 Obj_007B66D0 copies of arguments 1 and 2 (0x7B6720,
//   released by 0x7B6760); +0x28 argument 6; +0x2C/+0x30 Wstring copies
//   of arguments 3 and 4 (0x7B4690, released by 0x7B46F0); +0x34 the byte
//   argument 5; +0x38 the CCINIClass the constructor allocates (PUSH 0x58,
//   vptr 0x7E1AF4) and loads from the file named by +0x2C; +0x3C..+0x3F the
//   four flags read from it under the INI keys at 0x8308AC, 0x8308DC,
//   0x8308BC and 0x8308A0 (AlliesAllowed, WonlineTournamentAllowed,
//   WonlineClanTournamentAllowed, MustAlly).
//
//   Slot names: no string, RTTI or import names a slot, so they are the
//   slot-index placeholders vf_<n>; three keep the YRpp-cross-checked names
//   their matched bodies carry (PopulateTeamDropdownForPlayer 20,
//   CreateMPTeams 48, SpawnBaseUnits 50). Signatures come from each body's
//   RET n, argument reads and return use; types the bytes do not show stay
//   int / void*.
#ifndef GG_MATCH_NETWORK_MULTIPLAYER_GAME_MODE_H
#define GG_MATCH_NETWORK_MULTIPLAYER_GAME_MODE_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/vector_class.h"
#include "../core/wide_string_class.h"
#include "../core/string_class.h"
#include "../_layout/cell.h"
#include "multiplayer_team.h"

class HouseClass;
class CCINIClass;
struct MPTeam;

// The by-value vector argument of slots 21, 22 and 45. The callee owns the
// copy: each body is only the inlined destructor (free Items when
// IsAllocated, `MOV CL,[ESP+n+0xD]`). The element type is not visible.
typedef DynamicVectorClass<void*> MPGameModeArgVector;

// VTABLE: GAMEMD 0x7EED60
class MultiplayerGameMode
{
public:
    // Declaration: GAMEMD 0x5D6D80
    void FUN_005D6D80();
    // FUNCTION: GAMEMD 0x5D5B60 (decl; reloc) -- six stacked arguments, RET 0x18.
    MultiplayerGameMode(const Obj_007B66D0& name, const Obj_007B66D0& description,
                        const Wstring& unknown_3, const Wstring& unknown_4,
                        bool unknown_5, int unknown_6);
    // FUNCTION: GAMEMD 0x5D5D20 (decl; reloc) -- slot 0 through ??_G 0x5D7F20.
    virtual ~MultiplayerGameMode();
    virtual bool vf_1();                                    // 1  0x5C0E30
    virtual bool vf_2();                                    // 2  0x5C0E40
    virtual bool vf_3(int a);                               // 3  0x5C0E50
    virtual bool vf_4();                                    // 4  0x5D62C0
    virtual bool vf_5(Obj_007B66D0& message);            // 5  0x5D6310
    virtual bool vf_6();                                    // 6  0x5D6340
    virtual bool vf_7(int a);                               // 7  0x5D67A0
    virtual void vf_8();                                    // 8  0x5C0E60
    virtual void vf_9();                                    // 9  0x5C0E70
    virtual int  vf_10();                                   // 10 0x5D5DB0
    virtual int  vf_11();                                   // 11 0x5D5DC0
    virtual int  vf_12();                                   // 12 0x5D5DD0
    virtual bool vf_13(int a);                              // 13 0x5D5DE0
    virtual void vf_14(int a);                              // 14 0x5C0E80
    virtual bool vf_15();                                   // 15 0x5D6350
    virtual bool vf_16();                                   // 16 0x5D6360
    virtual int  vf_17();                                   // 17 0x5D6370
    virtual void vf_18(void* hWnd, DynamicVectorClass<int>* items, int selected); // 18 0x5D6450
    virtual void vf_19(void* hWnd, DynamicVectorClass<int>* items, int selected); // 19 0x5D64C0
    virtual void PopulateTeamDropdownForPlayer(void* hWnd, int idx);    // 20 0x5D6540
    virtual bool vf_21(int a, MPGameModeArgVector v);                   // 21 0x5C0EB0
    virtual bool vf_22(int a, MPGameModeArgVector v, int b, int c);     // 22 0x5C0E90
    virtual bool vf_23(int a, int b, int c);                // 23 0x5C0ED0
    virtual bool vf_24();                                   // 24 0x5D6320
    virtual bool vf_25();                                   // 25 0x5D6330
    virtual bool vf_26();                                   // 26 0x5C0EE0
    virtual int  vf_27();                                   // 27 0x5D6430
    virtual int  vf_28();                                   // 28 0x5D6440
    virtual void vf_29(int a, int b);                       // 29 0x5C0EF0
    virtual void vf_30(int a);                              // 30 0x5C0F00
    virtual bool vf_31();                                   // 31 0x5D6790
    virtual bool vf_32(bool a);                             // 32 0x5D6BE0
    virtual bool vf_33(bool a);                             // 33 0x5D6C70
    virtual bool vf_34();                                   // 34 0x5D74A0
    virtual bool vf_35();                                   // 35 0x5D7570
    virtual void vf_36();                                   // 36 0x5C0F10
    virtual void vf_37();                                   // 37 0x5C0F20
    virtual int  vf_38();                                   // 38 0x5C0F30
    virtual void vf_39();                                   // 39 0x5C0F40
    virtual void vf_40(int a);                              // 40 0x5C0F50
    virtual void vf_41(int a);                              // 41 0x5C0F60
    virtual bool vf_42();                                   // 42 0x5C0F70
    virtual void vf_43();                                   // 43 0x5C0F80
    virtual void vf_44();                                   // 44 0x5C0F90
    virtual bool vf_45(MPGameModeArgVector v, int a);       // 45 0x5C0FA0
    virtual int  vf_46();                                   // 46 0x5C0FC0
    virtual bool vf_47();                                   // 47 0x5C0FD0
    virtual void CreateMPTeams(DynamicVectorClass<MultiplayerTeam*>& teams); // 48 0x5D6690
    // Slot 49: the start cell for one house, returned through a hidden
    // pointer (Cell has a constructor); three stacked arguments.
    virtual Cell vf_49(int house, DynamicVectorClass<Cell>& starts, bool* taken); // 49 0x5D6890
    virtual bool SpawnBaseUnits(HouseClass* house, int unknown);        // 50 0x5D7030
    virtual bool vf_51(HouseClass* house, int* budget);                 // 51 0x5D70F0

    // MultiplayerGameMode::InitializerBase (vtable 0x7EEE74) and the six
    // Initializer<Mode> instantiations; see mp_initializer_ddtors.cpp.
    class InitializerBase
    {
    public:
        InitializerBase() {}
        virtual ~InitializerBase() {}
        // Slot 1: allocates and constructs one mode from the six stacked arguments.
        virtual MultiplayerGameMode* vf_1(const Obj_007B66D0& name, const Obj_007B66D0& description,
                                          const Wstring& unknown_3, const Wstring& unknown_4,
                                          bool unknown_5, int unknown_6) = 0;
    };

    template <class T>
    class Initializer : public InitializerBase
    {
    public:
        Initializer() {}
        virtual MultiplayerGameMode* vf_1(const Obj_007B66D0& name, const Obj_007B66D0& description,
                                          const Wstring& unknown_3, const Wstring& unknown_4,
                                          bool unknown_5, int unknown_6);
    };

    // FUNCTION: GAMEMD 0x5D6620 (decl; reloc) -- non-virtual; RET 4, returns an MPTeam.
    MPTeam* FUN_005D6620(int index);
    // FUNCTION: GAMEMD 0x5D63E0 -- non-virtual; RET 4.
    bool FUN_005D63E0(class MultiMission* entry);
    // FUNCTION: GAMEMD 0x5D6750 -- non-virtual.
    void FUN_005D6750();

    bool  unknown_04;                                 // +0x04
    DynamicVectorClass<MultiplayerTeam*> Teams;       // +0x08
    Obj_007B66D0 unknown_20;                       // +0x20
    Obj_007B66D0 unknown_24;                       // +0x24
    int   unknown_28;                                 // +0x28  the identifier Get() compares
    Wstring unknown_2C;                           // +0x2C  the INI file name
    Wstring unknown_30;                           // +0x30
    bool  unknown_34;                                 // +0x34  returned by slot 15
    CCINIClass* unknown_38;                           // +0x38  owned
    bool  AlliesAllowed;                              // +0x3C
    bool  WonlineTournamentAllowed;                   // +0x3D
    bool  WonlineClanTournamentAllowed;               // +0x3E
    bool  MustAlly;                                   // +0x3F
};
GG_STATIC_ASSERT(offsetof(MultiplayerGameMode, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(MultiplayerGameMode, Teams) == 0x08);
GG_STATIC_ASSERT(offsetof(MultiplayerGameMode, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(MultiplayerGameMode, unknown_24) == 0x24);
GG_STATIC_ASSERT(offsetof(MultiplayerGameMode, unknown_28) == 0x28);
GG_STATIC_ASSERT(offsetof(MultiplayerGameMode, unknown_2C) == 0x2C);
GG_STATIC_ASSERT(offsetof(MultiplayerGameMode, unknown_30) == 0x30);
GG_STATIC_ASSERT(offsetof(MultiplayerGameMode, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(MultiplayerGameMode, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(MultiplayerGameMode, AlliesAllowed) == 0x3C);
GG_STATIC_ASSERT(offsetof(MultiplayerGameMode, MustAlly) == 0x3F);
GG_STATIC_ASSERT(sizeof(MultiplayerGameMode) == 0x40);

// VTABLE: GAMEMD 0x7EE6FC
class MultiplayerSiege : public MultiplayerGameMode
{
public:
    // FUNCTION: GAMEMD 0x5CA630 (declaration)
    MultiplayerSiege(const Obj_007B66D0& name, const Obj_007B66D0& description,
                     const Wstring& unknown_3, const Wstring& unknown_4,
                     bool unknown_5, int unknown_6);
    // FUNCTION: GAMEMD 0x5CA670 (declaration; slot 0 through ??_G 0x5CABD0)
    virtual ~MultiplayerSiege();
    virtual bool vf_4();                                                   // 4  0x5CA680
    virtual bool vf_5(Obj_007B66D0& message);                           // 5  0x5CA6D0
    virtual bool vf_6();                                                   // 6  0x5CA7D0
    virtual bool vf_15();                                                  // 15 0x5CA7E0
    virtual bool vf_31();                                                  // 31 0x5CA7F0
    virtual bool vf_33(bool a);                                            // 33 0x5CA800
    virtual void CreateMPTeams(DynamicVectorClass<MultiplayerTeam*>& teams); // 48 0x5CA9B0
    virtual bool SpawnBaseUnits(HouseClass* house, int unknown);           // 50 0x5CAAC0
};
GG_STATIC_ASSERT(sizeof(MultiplayerSiege) == 0x40);

GG_STATIC_ASSERT(sizeof(((MultiplayerGameMode*)0)->unknown_2C) == 4);
GG_STATIC_ASSERT(sizeof(((MultiplayerGameMode*)0)->unknown_30) == 4);
#endif  // GG_MATCH_NETWORK_MULTIPLAYER_GAME_MODE_H
