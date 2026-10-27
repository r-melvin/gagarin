// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   No RTTI TypeDescriptor and no vtable: the ctor 0x665650 stores 5 into
//   [this+0] first. sizeof from FUN_0052BA60: PUSH 0x18C0; CALL operator new;
//   then the ctor; the result goes to the global at 0x8871E0.
//   C4Warhead: `MOV EAX,[0x8871E0]; MOV ECX,[EAX+0xFA8]` in HouseClass::DestroyAll.
//   No RTTI attests the class key, so the existing `struct` key is kept (no re-key).
#ifndef GG_MATCH_LAYOUT_RULES_CLASS_H
#define GG_MATCH_LAYOUT_RULES_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../core/vector_class.h"
class CCINIClass;
class WarheadTypeClass;
class AnimTypeClass;
class WeaponTypeClass;
class UnitTypeClass;
// Merged observations and offset assertions from core/rules_class.h.
struct RulesClass
{
    // FUNCTION: GAMEMD 0x66D3A0
    bool Read_Colors(CCINIClass* pINI);


    // Existing list readers: binary-confirmed section/allocator calls.
    // Declaration: GAMEMD 0x6722F0 -- thiscall, one INI pointer, RET4.
    bool Read_Countries(CCINIClass* pINI);
    // Declaration: GAMEMD 0x6725F0 -- thiscall, one INI pointer, RET4.
    bool Read_SuperWeaponTypes(CCINIClass* pINI);
    // Declaration: GAMEMD 0x672660 -- thiscall, one INI pointer, RET4.
    bool Read_BuildingTypes(CCINIClass* pINI);
    // Declaration: GAMEMD 0x6726D0 -- thiscall, one INI pointer, RET4.
    bool Read_TerrainTypes(CCINIClass* pINI);
    // Declaration: GAMEMD 0x6727D0 -- thiscall, one INI pointer, RET4.
    bool Read_SmudgeTypes(CCINIClass* pINI);
    // Declaration: GAMEMD 0x672840 -- thiscall, one INI pointer, RET4.
    bool Read_OverlayTypes(CCINIClass* pINI);
    // Declaration: GAMEMD 0x6728B0 -- thiscall, one INI pointer, RET4.
    bool Read_Animations(CCINIClass* pINI);
    // Declaration: GAMEMD 0x672920 -- thiscall, one INI pointer, RET4.
    bool Read_VoxelAnims(CCINIClass* pINI);
    // Declaration: GAMEMD 0x672990 -- thiscall, one INI pointer, RET4.
    bool Read_Warheads(CCINIClass* pINI);
    // Declaration: GAMEMD 0x672A00 -- thiscall, one INI pointer, RET4.
    bool Read_Particles(CCINIClass* pINI);
    // Declaration: GAMEMD 0x672A70 -- thiscall, one INI pointer, RET4.
    bool Read_ParticleSystems(CCINIClass* pINI);


    int unknown_000; // 0x6850FB -> fastcall55AF40
    int unknown_004;
    int unknown_008; // 0x685108 -> fastcall55AF50
    char unknown_00C[0x04C - 0x00C];
    AnimTypeClass* LandAnim; // +0x04C
    int unknown_050; // 0x6D26BE reads DWORD duration; 0x6D26E1 stores it to Tactical+DAC.
    char unknown_054[0x8C - 0x054];
    int unknown_08C;
    char unknown_090[0x108 - 0x090];
    AnimTypeClass** TouchdownAnims; // +0x108
    char unknown_10C[0x1A0 - 0x10C];
    int unknown_1A0;
    char unknown_1A4[0x1D4 - 0x1A4];
    int unknown_1D4;    // +0x1D4 sound played on entering planning mode
    char unknown_1D8[0x1E0 - 0x1D8];
    int unknown_1E0;    // +0x1E0 sound played on leaving it
    char unknown_1E4[0x244 - 0x1E4];
    int BunkerSound;
    char unknown_248[0x344 - 0x248];
    AnimTypeClass* unknown_344;
    char unknown_348[0x354 - 0x348];
    AnimTypeClass* SpawnAnim; // +0x354
    char unknown_358[0x54C - 0x358];
    int At_54C;
    char unknown_550[0x580 - 0x550];
    int unknown_580;
    char unknown_584[0x598 - 0x584];
    double unknown_598;
    int unknown_5A0;
    WeaponTypeClass* Weapon; // +0x5A4
    int unknown_5A8;
    int MinFall; // +0x5AC
    double Angle; // +0x5B0
    char unknown_5B8[0x6AC - 0x5B8];
    int unknown_06AC;
    char unknown_6B0[0x6C4 - 0x6B0];
    int unknown_6C4;
    char unknown_6C8[0x700 - 0x6C8];
    int unknown_700;    // +0x700 sound played when planning guard areas are refused
    char unknown_704[0x724 - 0x704];
    int unknown_724;
    int unknown_728;
    int unknown_72C;
    char unknown_730[0x788 - 0x730];
    int unknown_788;
    int unknown_78C;
    char unknown_790[0x7A8 - 0x790];
    int unknown_7A8;
    char unknown_7AC[0x7B4 - 0x7AC];
    int unknown_7B4; // native717810 reads fallback scalar via pointer8871E0
    char unknown_7B8[0xB20 - 0x7B8];
    DynamicVectorClass<UnitTypeClass*> unknown_B20; // constructor-type list0x688B55
    char unknown_B38[0xD04 - 0xB38];
    // Three pointer collections selected at 0x68C164..0x68C1A5.
    void** unknown_D04;
    char unknown_D08[8];
    int unknown_D10;
    char unknown_D14[0xD20 - 0xD14];
    void** unknown_D20;
    char unknown_D24[8];
    int unknown_D2C;
    char unknown_D30[0xD3C - 0xD30];
    void** unknown_D3C;
    char unknown_D40[8];
    int unknown_D48;
    char unknown_D4C[8];
    int unknown_D54;
    char unknown_D58[0xE04 - 0xD58];
    int unknown_E04;
    char unknown_E08[0x0FA8 - 0xE08];
    WarheadTypeClass* C4Warhead;
    char unknown_FAC[0x1178 - 0xFAC];
    int* unknown_1178; // 0x686A17/0x686A23 indexes by House AIDifficulty
    char unknown_117C[0x1308 - 0x117C];
    int* unknown_1308; // 0x686A52/0x686A5E
    char unknown_130C[0x1434 - 0x130C];
    int unknown_1434;
    char unknown_1438[0x1470 - 0x1438];
    int unknown_1470;
    int unknown_1474;
    char unknown_1478[0x1484 - 0x1478];
    int unknown_1484; // native697F74 default Credits
    char unknown_1488[0x1494 - 0x1488];
    int unknown_1494;
    char unknown_1498[8];
    int unknown_14A0;
    char unknown_14A4[0x14AE - 0x14A4];
    bool unknown_14AE; // byte test0x6849D6
    char unknown_14AF[0x14B1 - 0x14AF];
    bool unknown_14B1;
    char unknown_14B2[3];
    bool unknown_14B5;
    bool unknown_14B6;
    char unknown_14B7;
    bool unknown_14B8;
    bool unknown_14B9;
    bool unknown_14BA;
    bool unknown_14BB;
    char unknown_14BC[4];
    double unknown_14C0;
    char unknown_14C8[8];
    int unknown_14D0;
    char unknown_14D4[0x16B8 - 0x14D4];
    int unknown_16B8;
    char unknown_16BC[0x16CC - 0x16BC];
    int unknown_16CC; // native712125 reads scalar via pointer8871E0
    double unknown_16D0; // native 0x7120D0 loads the full 8-byte value
    int unknown_16D8; // native524795 reads dword via pointer8871E0
    char unknown_16DC[0x1700 - 0x16DC];
    double ConditionYellow;
    double ConditionRed;
    char unknown_1710[0x1734 - 0x1710];
    int unknown_1734;
    char unknown_1738[0x1748 - 0x1738];
    double unknown_1748; // native 0x711EE0 loads the full 8-byte value
    char unknown_1750[0x1804 - 0x1750];
    int RadDurationMultiple;
    char unknown_1808[0x186C - 0x1808];
    int unknown_186C; // random upper bound minus one0x68508F
    AnimTypeClass* unknown_1870; // 0x6850D9 -> AnimClass constructor0x421EA0
    char unknown_1874[0x18C0 - 0x1874];
};

GG_STATIC_ASSERT(offsetof(RulesClass, unknown_050) == 0x50);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->unknown_050) == 4);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_B20) == 0xB20);
GG_STATIC_ASSERT(offsetof(RulesClass, BunkerSound) == 0x244);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_000) == 0x000);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_008) == 0x008);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_186C) == 0x186C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1870) == 0x1870);

GG_STATIC_ASSERT(offsetof(RulesClass, At_54C) == 0x54C);
GG_STATIC_ASSERT(offsetof(RulesClass, LandAnim) == 0x04C);
GG_STATIC_ASSERT(offsetof(RulesClass, TouchdownAnims) == 0x108);
GG_STATIC_ASSERT(offsetof(RulesClass, SpawnAnim) == 0x354);
GG_STATIC_ASSERT(offsetof(RulesClass, Weapon) == 0x5A4);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_5A8) == 0x5A8);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1D4) == 0x1D4);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1E0) == 0x1E0);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_700) == 0x700);
GG_STATIC_ASSERT(offsetof(RulesClass, MinFall) == 0x5AC);
GG_STATIC_ASSERT(offsetof(RulesClass, Angle) == 0x5B0);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_344) == 0x344);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_E04) == 0xE04);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_D04) == 0xD04);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_D10) == 0xD10);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_D20) == 0xD20);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_D2C) == 0xD2C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_D3C) == 0xD3C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_D48) == 0xD48);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_D54) == 0xD54);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_788) == 0x788);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_78C) == 0x78C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_7A8) == 0x7A8);
GG_STATIC_ASSERT(offsetof(RulesClass, C4Warhead) == 0x0FA8);
GG_STATIC_ASSERT(offsetof(RulesClass, ConditionYellow) == 0x1700);
GG_STATIC_ASSERT(offsetof(RulesClass, ConditionRed) == 0x1708);
GG_STATIC_ASSERT(offsetof(RulesClass, RadDurationMultiple) == 0x1804);

GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1178) == 0x1178);

GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1308) == 0x1308);

GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1470) == 0x1470);

GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1474) == 0x1474);

GG_STATIC_ASSERT(offsetof(RulesClass, unknown_14D0) == 0x14D0);

// GLOBAL: GAMEMD 0x008871E0 — active RulesClass pointer.
extern RulesClass* RulesInstance;

GG_STATIC_ASSERT(offsetof(RulesClass, unknown_08C) == 0x08C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_580) == 0x580);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_598) == 0x598);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->unknown_598) == 8);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_5A0) == 0x5A0);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->unknown_5A0) == 4);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_724) == 0x724);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_728) == 0x728);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_72C) == 0x72C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_14AE) == 0x14AE);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_14B5) == 0x14B5);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_14BB) == 0x14BB);

GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1484) == 0x1484);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1494) == 0x1494);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_14A0) == 0x14A0);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_14B1) == 0x14B1);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_14B6) == 0x14B6);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_14B8) == 0x14B8);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_14B9) == 0x14B9);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_14BA) == 0x14BA);

GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1A0)  == 0x1A0);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_6C4)  == 0x6C4);
GG_STATIC_ASSERT(offsetof(RulesClass, C4Warhead) == 0xFA8);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_7B4) == 0x7B4);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_16CC) == 0x16CC);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_16B8) == 0x16B8);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->unknown_16B8) == 4);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_16D0) == 0x16D0);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->unknown_16D0) == 8);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1734) == 0x1734);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_16D8) == 0x16D8);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->unknown_16D8) == 4);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1748) == 0x1748);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->unknown_1748) == 8);
GG_STATIC_ASSERT(sizeof(RulesClass)              == 0x18C0);

extern RulesClass* Rules;   // GLOBAL: GAMEMD 0x8871E0



GG_STATIC_ASSERT(offsetof(RulesClass, unknown_06AC) == 0x6AC);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1434) == 0x1434);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_14C0) == 0x14C0);

GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->C4Warhead) == 4);
#endif
