// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x452360: on the building the bytes `[ESI+0x660]`
//   (cleared) and `[ESI+0x80]` (set), the owner at `[ESI+0x21C]` and the type
//   at `[ESI+0x520]`; on the type `[EAX+0xEE4]` (int, compared > 0), the
//   bytes `[EAX+0x1573]` and `[EAX+0xCCE]`, and `[EAX+0xEB8]` (int, pushed);
//   on the owner the bytes `[ECX+0x5778]`, `[EDX+0x5779]` and `[ECX+0x1FC]`.
//   Callees: 0x452480 (BuildingClass::DisableStuff, __thiscall), 0x50B6F0
//   (HouseClass::IsControlledByCurrentPlayer, __thiscall, byte result),
//   0x752700 (VoxClass::Play, __fastcall: ECX=name, EDX=-1, pushed -1) and
//   0x509140 (HouseClass::Update_FactoriesQueues, __thiscall, three pushed
//   args). Names cross-checked against YRpp BuildingClass::GoOffline /
//   and the committed spines
//   match/_layout/object_class.h (NeedsRedraw @0x80), techno_class.h (Owner
//   @0x21C), techno_type_class.h (Naval @0xCCE), building_type_class_layout.h
//   (Factory @0xEB8, PowerDrain @0xEE4) and match/economy/
//   house_class_power_methods.h (the two @0x5778/@0x5779 bytes) — re-derived.
#ifndef GG_MATCH_COMBAT_BUILDING_CLASS_OFFLINE_METHODS_H
#define GG_MATCH_COMBAT_BUILDING_CLASS_OFFLINE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct HouseClass_00452360
{
    char _pad0000[0x1FC];             // +0x0000
    char RecheckTechTree;                // +0x01FC
    char _pad01FD[0x5778 - 0x1FD];    // +0x01FD
    char PowerBlackoutWasActivated;   // +0x5778
    char RadarBlackoutWasActivated;   // +0x5779

    // FUNCTION: GAMEMD 0x509140 (decl; reloc) — HouseClass::Update_FactoriesQueues.
    void Update_FactoriesQueues(int factoryOf, bool isNaval, int buildCat);
    // FUNCTION: GAMEMD 0x50B6F0 (decl; reloc) — HouseClass::IsControlledByCurrentPlayer.
    bool IsControlledByCurrentPlayer();
};
GG_STATIC_ASSERT(offsetof(HouseClass_00452360, RecheckTechTree) == 0x1FC);
GG_STATIC_ASSERT(offsetof(HouseClass_00452360, PowerBlackoutWasActivated) == 0x5778);
GG_STATIC_ASSERT(offsetof(HouseClass_00452360, RadarBlackoutWasActivated) == 0x5779);

struct Type_00452360
{
    char _pad0000[0xCCE];             // +0x0000
    bool Naval;                       // +0x0CCE
    char _pad0CCF[0xEB8 - 0xCCF];     // +0x0CCF
    int  Factory;                     // +0x0EB8  AbstractType produced, 0 = none
    char _pad0EBC[0xEE4 - 0xEBC];     // +0x0EBC
    int  PowerDrain;                  // +0x0EE4
    char _pad0EE8[0x1573 - 0xEE8];    // +0x0EE8
    char Powered;                     // +0x1573
};
GG_STATIC_ASSERT(offsetof(Type_00452360, Naval) == 0xCCE);
GG_STATIC_ASSERT(offsetof(Type_00452360, Factory) == 0xEB8);
GG_STATIC_ASSERT(offsetof(Type_00452360, PowerDrain) == 0xEE4);
GG_STATIC_ASSERT(offsetof(Type_00452360, Powered) == 0x1573);

struct VoxClass_00452360
{
    // FUNCTION: GAMEMD 0x752700 (decl; reloc) — VoxClass::Play.
    static void Play(const char* name, int a, int b);
};

// STRING: GAMEMD 0x819108 — "EVA_BuildingOffLine".
extern const char EvaBuildingOffLine[];

struct BuildingClass_00452360
{
    char                  _pad0000[0x80];            // +0x0000
    char                  NeedsRedraw;               // +0x0080
    char                  _pad0081[0x21C - 0x81];    // +0x0081
    HouseClass_00452360*  Owner;                     // +0x021C
    char                  _pad0220[0x520 - 0x220];   // +0x0220
    Type_00452360*        Type;                      // +0x0520
    char                  _pad0524[0x660 - 0x524];   // +0x0524
    char                  HasPower;                  // +0x0660

    // FUNCTION: GAMEMD 0x452360
    void GoOffline();
    // FUNCTION: GAMEMD 0x452480 (decl; reloc) — BuildingClass::DisableStuff.
    void DisableStuff();
};
GG_STATIC_ASSERT(offsetof(BuildingClass_00452360, NeedsRedraw) == 0x80);
GG_STATIC_ASSERT(offsetof(BuildingClass_00452360, Owner) == 0x21C);
GG_STATIC_ASSERT(offsetof(BuildingClass_00452360, Type) == 0x520);
GG_STATIC_ASSERT(offsetof(BuildingClass_00452360, HasPower) == 0x660);

#endif  // GG_MATCH_COMBAT_BUILDING_CLASS_OFFLINE_METHODS_H
