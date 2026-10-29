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
#include "../core/type_list.h"
#include "color_struct.h"
struct AbstractNoInit;
class CCINIClass;
class WarheadTypeClass;
class AnimTypeClass;
class WeaponTypeClass;
class UnitTypeClass;
class ObjectTypeClass;
class VoxelAnimTypeClass;
class SmudgeTypeClass;
class BuildingTypeClass;
class AircraftTypeClass;
class InfantryTypeClass;
class TerrainTypeClass;

// Three-byte colour with the out-of-line zeroing constructor 0x4B9BD0 (RulesClass+0x1860
// and the ColorAdd array, both built through it by the constructors). The Save loop at
// 0x675205 calls RGBClass::Save (0x6614F0) on each ColorAdd entry, so this is most likely
// RGBClass itself (0x4B9BD0 being another translation unit's copy of its inline constructor).
struct RulesColor_004B9BD0 : ColorStruct
{
    // FUNCTION: GAMEMD 0x4B9BD0 (decl; reloc)
    RulesColor_004B9BD0();
    RulesColor_004B9BD0& operator=(const ColorStruct& c) { ColorStruct::operator=(c); return *this; }
};

// Merged observations and offset assertions from core/rules_class.h.
struct RulesClass
{
    // FUNCTION: GAMEMD 0x664D20
    RulesClass(const AbstractNoInit& noInit);
    // FUNCTION: GAMEMD 0x665650
    RulesClass();
    // FUNCTION: GAMEMD 0x667A30
    ~RulesClass();

    // FUNCTION: GAMEMD 0x66D3A0
    bool Read_Colors(CCINIClass* pINI);
    // FUNCTION: GAMEMD 0x66D480
    bool Read_ColorAdd(CCINIClass* pINI);
    // FUNCTION: GAMEMD 0x66D150
    bool Read_ElevationModel(CCINIClass* pINI);
    // GAMEMD 0x66D1F0 __thiscall
    bool Read_WallModel(CCINIClass* pINI);
    // FUNCTION: GAMEMD 0x674650
    bool Read_AdvancedCommandBar(CCINIClass* pINI, bool multiplayer);
    // FUNCTION: GAMEMD 0x672280  RulesClass::Read_InfantryTypes  (__thiscall)
    bool Read_InfantryTypes(CCINIClass* pINI);
    // FUNCTION: GAMEMD 0x672360  RulesClass::Read_VehicleTypes   (__thiscall)
    bool Read_VehicleTypes(CCINIClass* pINI);
    // FUNCTION: GAMEMD 0x6723D0  RulesClass::Read_AircraftTypes  (__thiscall)
    bool Read_AircraftTypes(CCINIClass* pINI);


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
    // Declaration: GAMEMD 0x672740 -- thiscall, one INI pointer, RET4.
    bool Read_Teams(CCINIClass* pINI);


    int unknown_000; // 0x6850FB -> fastcall55AF40
    int unknown_004;
    int unknown_008; // 0x685108 -> fastcall55AF50
    char unknown_00C[0x20 - 0xC];
    double unknown_20;   // +0x20
    char unknown_028[0x44 - 0x28];
    int unknown_044;    // +0x044 read by AircraftClass 0x41B760 as its facing fallback
    char unknown_048[0x04C - 0x048];
    AnimTypeClass* LandAnim; // +0x04C
    int unknown_050; // 0x6D26BE reads DWORD duration; 0x6D26E1 stores it to Tactical+DAC.
    char unknown_54[0x58 - 0x54];
    TypeList<const VoxelAnimTypeClass*> list_0058;  // +0x0058
    char unknown_74[0x8C - 0x74];
    int unknown_08C;
    int unknown_90;   // +0x90
    char unknown_094[0x9C - 0x94];
    AnimTypeClass* unknown_9C;   // +0x9C
    char unknown_0A0[0xDC - 0xA0];
    int unknown_DC;   // +0xDC
    char unknown_E0[0x104 - 0xE0];
    TypeList<const AnimTypeClass*> TouchdownAnims;  // +0x0104
    TypeList<const AnimTypeClass*> list_0120;  // +0x0120
    TypeList<const AnimTypeClass*> list_013C;  // +0x013C
    TypeList<const AnimTypeClass*> list_0158;  // +0x0158
    char unknown_174[0x188 - 0x174];
    int unknown_188;   // +0x188
    int unknown_18C;   // +0x18C
    int unknown_190;   // +0x190
    int unknown_194;   // +0x194
    int unknown_198;   // +0x198
    char unknown_19C[0x1A0 - 0x19C];
    int unknown_1A0;
    char unknown_1A4[0x1C8 - 0x1A4];
    int field_1C8;      // +0x1C8 read by HouseClass::CanOverpower
    char unknown_1CC[0x1D4 - 0x1CC];
    int unknown_1D4;    // +0x1D4 sound played on entering planning mode
    char unknown_1D8[0x1E0 - 0x1D8];
    int unknown_1E0;    // +0x1E0 sound played on leaving it
    char unknown_1E4[0x214 - 0x1E4];
    int unknown_214; // 4692E3: signed sentinel; 469333: sound argument
    int unknown_218;   // +0x218
    int unknown_21C;   // +0x21C
    char unknown_220[0x244 - 0x220];
    int BunkerSound;
    char unknown_248[0x2A0 - 0x248];
    TypeList<const AnimTypeClass*> list_02A0;  // +0x02A0
    TypeList<const AnimTypeClass*> list_02BC;  // +0x02BC
    TypeList<const AnimTypeClass*> list_02D8;  // +0x02D8
    char unknown_2F4[0x33C - 0x2F4];
    void* unknown_33C;   // +0x33C
    void* unknown_340;   // +0x340
    AnimTypeClass* unknown_344;
    char unknown_348[0x350 - 0x348];
    AnimTypeClass* unknown_350; // 46A2A1 special-impact animation constructor argument
    AnimTypeClass* SpawnAnim; // +0x354
    TypeList<int> list_0358;  // +0x0358
    TypeList<int> list_0374;  // +0x0374
    TypeList<int> list_0390;  // +0x0390
    TypeList<int> list_03AC;  // +0x03AC
    TypeList<int> list_03C8;  // +0x03C8
    TypeList<int> list_03E4;  // +0x03E4
    char unknown_400[0x420 - 0x400];
    int unknown_420;   // +0x420
    char unknown_424[0x43C - 0x424];
    TypeList<int> list_043C;  // +0x043C
    TypeList<int> list_0458;  // +0x0458
    TypeList<int> list_0474;  // +0x0474
    char unknown_490[0x4E0 - 0x490];
    int TypeA;          // +0x4E0
    char unknown_4E4[0x514 - 0x4E4];
    int TypeB;          // +0x514
    char unknown_518[0x54C - 0x518];
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
    char unknown_5B8[0x600 - 0x5B8];
    TypeList<const VoxelAnimTypeClass*> list_0600;  // +0x0600
    char unknown_61C[0x648 - 0x61C];
    TypeList<int> list_0648;  // +0x0648
    char unknown_664[0x678 - 0x664];
    double unknown_678;   // +0x678
    char unknown_680[0x6AC - 0x680];
    int unknown_06AC;
    char unknown_6B0[0x6C4 - 0x6B0];
    int unknown_6C4;
    char unknown_6C8[0x6CC - 0x6C8];
    TypeList<int> list_06CC;  // +0x06CC
    char unknown_6E8[0x6F0 - 0x6E8];
    int unknown_6F0;   // +0x6F0
    int unknown_6F4;   // +0x6F4
    char unknown_6F8[0x700 - 0x6F8];
    int unknown_700;    // +0x700 sound played when planning guard areas are refused
    char unknown_704[0x710 - 0x704];
    int unknown_710;   // +0x710
    char unknown_714[0x724 - 0x714];
    int unknown_724;
    int unknown_728;
    int unknown_72C;
    char unknown_730[0x734 - 0x730];
    TypeList<int> list_0734;  // +0x0734
    char unknown_750[0x758 - 0x750];
    double unknown_758;   // +0x758
    char unknown_760[0x788 - 0x760];
    int unknown_788;
    int unknown_78C;
    char unknown_790[0x7A8 - 0x790];
    int unknown_7A8;
    char unknown_7AC[0x7B4 - 0x7AC];
    int unknown_7B4; // native717810 reads fallback scalar via pointer8871E0
    int unknown_7B8;   // +0x7B8
    int unknown_7BC;   // +0x7BC
    char unknown_7C0[0x7C4 - 0x7C0];
    TypeList<const SmudgeTypeClass*> list_07C4;  // +0x07C4
    TypeList<const SmudgeTypeClass*> list_07E0;  // +0x07E0
    TypeList<const SmudgeTypeClass*> list_07FC;  // +0x07FC
    TypeList<const SmudgeTypeClass*> list_0818;  // +0x0818
    TypeList<const SmudgeTypeClass*> list_0834;  // +0x0834
    TypeList<const BuildingTypeClass*> list_0850;  // +0x0850
    void* unknown_86C;   // +0x86C
    void* unknown_870;   // +0x870
    void* unknown_874;   // +0x874
    void* unknown_878;   // +0x878
    void* unknown_87C;   // +0x87C
    TypeList<const BuildingTypeClass*> list_0880;  // +0x0880
    char unknown_89C[0x8AC - 0x89C];
    TypeList<const BuildingTypeClass*> list_08AC;  // +0x08AC
    TypeList<const BuildingTypeClass*> list_08C8;  // +0x08C8
    TypeList<const BuildingTypeClass*> list_08E4;  // +0x08E4
    TypeList<const BuildingTypeClass*> list_0900;  // +0x0900
    TypeList<const BuildingTypeClass*> list_091C;  // +0x091C
    TypeList<const BuildingTypeClass*> list_0938;  // +0x0938
    TypeList<const BuildingTypeClass*> list_0954;  // +0x0954
    TypeList<const BuildingTypeClass*> list_0970;  // +0x0970
    TypeList<const BuildingTypeClass*> list_098C;  // +0x098C
    TypeList<int> list_09A8;  // +0x09A8
    TypeList<const BuildingTypeClass*> list_09C4;  // +0x09C4
    TypeList<const BuildingTypeClass*> list_09E0;  // +0x09E0
    TypeList<const BuildingTypeClass*> list_09FC;  // +0x09FC
    TypeList<const BuildingTypeClass*> list_0A18;  // +0x0A18
    TypeList<const BuildingTypeClass*> list_0A34;  // +0x0A34
    TypeList<const BuildingTypeClass*> list_0A50;  // +0x0A50
    TypeList<const BuildingTypeClass*> list_0A6C;  // +0x0A6C
    TypeList<const BuildingTypeClass*> list_0A88;  // +0x0A88
    TypeList<const BuildingTypeClass*> list_0AA4;  // +0x0AA4
    TypeList<const BuildingTypeClass*> list_0AC0;  // +0x0AC0
    TypeList<const BuildingTypeClass*> list_0ADC;  // +0x0ADC
    char unknown_AF8[0xB20 - 0xAF8];
    TypeList<const UnitTypeClass*> unknown_B20;  // +0x0B20
    TypeList<const UnitTypeClass*> list_0B3C;  // +0x0B3C
    TypeList<const AircraftTypeClass*> list_0B58;  // +0x0B58
    TypeList<const AnimTypeClass*> list_0B74;  // +0x0B74
    TypeList<const AnimTypeClass*> list_0B90;  // +0x0B90
    char unknown_BAC[0xBB8 - 0xBAC];
    AnimTypeClass* unknown_BB8;   // +0xBB8
    AnimTypeClass* unknown_BBC;   // +0xBBC
    TypeList<const AnimTypeClass*> list_0BC0;  // +0x0BC0
    char unknown_BDC[0xBEC - 0xBDC];
    int unknown_BEC;   // +0xBEC
    char unknown_BF0[0xBF4 - 0xBF0];
    int unknown_BF4;   // +0xBF4
    char unknown_BF8;   // +0xBF8
    char unknown_BF9[0xBFC - 0xBF9];
    int unknown_BFC;   // +0xBFC
    int unknown_C00;   // +0xC00
    TypeList<const InfantryTypeClass*> list_0C04;  // +0x0C04
    TypeList<int> list_0C20;  // +0x0C20
    TypeList<const InfantryTypeClass*> list_0C3C;  // +0x0C3C
    TypeList<int> list_0C58;  // +0x0C58
    TypeList<const InfantryTypeClass*> list_0C74;  // +0x0C74
    TypeList<int> list_0C90;  // +0x0C90
    TypeList<const InfantryTypeClass*> list_0CAC;  // +0x0CAC
    TypeList<int> list_0CC8;  // +0x0CC8
    TypeList<const InfantryTypeClass*> list_0CE4;  // +0x0CE4
    TypeList<const InfantryTypeClass*> list_0D00;  // +0x0D00
    TypeList<const UnitTypeClass*> list_0D1C;  // +0x0D1C
    TypeList<const BuildingTypeClass*> list_0D38;  // +0x0D38
    int unknown_D54;
    ObjectTypeClass* unknown_D58;   // +0xD58
    ObjectTypeClass* unknown_D5C;   // +0xD5C
    ObjectTypeClass* unknown_D60;   // +0xD60
    char unknown_D64[0xD70 - 0xD64];
    float AIMinorSuperReadyPercent; // +0xD70
    char unknown_D74[0xD80 - 0xD74];
    TypeList<int> list_0D80;  // +0x0D80
    TypeList<int> list_0D9C;  // +0x0D9C
    TypeList<int> list_0DB8;  // +0x0DB8
    TypeList<int> list_0DD4;  // +0x0DD4
    char unknown_DF0[0xE04 - 0xDF0];
    int unknown_E04;
    char unknown_E08[0xE10 - 0xE08];
    TypeList<int> list_0E10;  // +0x0E10
    TypeList<int> list_0E2C;  // +0x0E2C
    char unknown_E48[0xE4C - 0xE48];
    TypeList<int> list_0E4C;  // +0x0E4C
    TypeList<int> list_0E68;  // +0x0E68
    TypeList<int> list_0E84;  // +0x0E84
    TypeList<int> list_0EA0;  // +0x0EA0
    char unknown_EBC[0xEC4 - 0xEBC];
    TypeList<int> list_0EC4;  // +0x0EC4
    int unknown_EE0;   // +0xEE0
    char unknown_EE4[0xEE8 - 0xEE4];
    TypeList<int> list_0EE8;  // +0x0EE8
    TypeList<int> list_0F04;  // +0x0F04
    TypeList<int> list_0F20;  // +0x0F20
    char unknown_F3C[0xF48 - 0xF3C];
    int unknown_F48;   // +0xF48 added to the range of an object with slot 256 set (TechnoClass 0x6F7220)
    char unknown_F4C[0xF54 - 0xF4C];
    int unknown_F54;   // +0xF54 range bonus while bunkered, not a building (0x6F7220)
    char unknown_F58[0xF5C - 0xF58];
    int unknown_F5C;   // +0xF5C range bonus for an open-topped passenger (0x6F7220)
    int unknown_F60;   // +0xF60
    char unknown_F64[0xF8C - 0xF64];
    WarheadTypeClass* unknown_F8C; // 469CA7 compares this pointer with Bullet.WH
    char unknown_F90[0xFA8 - 0xF90];
    WarheadTypeClass* C4Warhead;
    char unknown_FAC[0xFD0 - 0xFAC];
    int field_FD0;      // +0xFD0
    char unknown_FD4[0xFD8 - 0xFD4];
    int field_FD8;      // +0xFD8
    char unknown_FDC[0xFF8 - 0xFDC];
    TypeList<const TerrainTypeClass*> list_0FF8;  // +0x0FF8
    char unknown_1014[0x1020 - 0x1014];
    void* unknown_1020;   // +0x1020
    char unknown_1024[0x1158 - 0x1024];
    TypeList<int> list_1158;  // +0x1158
    TypeList<int> list_1174;  // +0x1174
    char unknown_1190[0x1194 - 0x1190];
    TypeList<int> list_1194;  // +0x1194
    TypeList<int> list_11B0;  // +0x11B0
    TypeList<int> list_11CC;  // +0x11CC
    TypeList<int> list_11E8;  // +0x11E8
    TypeList<int> list_1204;  // +0x1204
    TypeList<int> list_1220;  // +0x1220
    TypeList<int> list_123C;  // +0x123C
    TypeList<int> list_1258;  // +0x1258
    TypeList<int> list_1274;  // +0x1274
    TypeList<int> list_1290;  // +0x1290
    TypeList<int> list_12AC;  // +0x12AC
    TypeList<int> list_12C8;  // +0x12C8
    TypeList<int> list_12E4;  // +0x12E4
    char unknown_1300[0x1304 - 0x1300];
    TypeList<int> list_1304;  // +0x1304
    TypeList<int> list_1320;  // +0x1320
    TypeList<int> list_133C;  // +0x133C
    TypeList<int> list_1358;  // +0x1358
    TypeList<int> list_1374;  // +0x1374
    TypeList<int> list_1390;  // +0x1390
    TypeList<int> list_13AC;  // +0x13AC
    TypeList<int> list_13C8;  // +0x13C8
    char unknown_13E4[0x13F0 - 0x13E4];
    TypeList<int> list_13F0;  // +0x13F0
    char unknown_140C[0x1434 - 0x140C];
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
    int unknown_16BC;   // +0x16BC
    char unknown_16C0[0x16CC - 0x16C0];
    int unknown_16CC; // native712125 reads scalar via pointer8871E0
    double unknown_16D0; // native 0x7120D0 loads the full 8-byte value
    int unknown_16D8; // native524795 reads dword via pointer8871E0
    char unknown_16DC[0x16F8 - 0x16DC];
    double unknown_16F8;   // +0x16F8
    double ConditionYellow;
    double ConditionRed;
    char unknown_1710[0x1734 - 0x1710];
    int unknown_1734;
    char unknown_1738[0x1748 - 0x1738];
    double unknown_1748; // native 0x711EE0 loads the full 8-byte value
    char unknown_1750[0x1790 - 0x1750];
    int unknown_1790;   // +0x1790
    int unknown_1794;   // +0x1794
    char unknown_1798[0x17D0 - 0x1798];
    int unknown_17D0;   // +0x17D0
    char unknown_17D4[0x1804 - 0x17D4];
    int RadDurationMultiple;
    char unknown_1808[0x1838 - 0x1808];
    int ElevationIncrement;            // +0x1838
    char unknown_183C[0x1840 - 0x183C];
    double ElevationIncrementBonus;    // +0x1840
    double ElevationBonusCap;          // +0x1848
    bool AlliedWallTransparency;       // +0x1850
    char unknown_1851[0x1858 - 0x1851];
    double WallPenetratorThreshold;    // +0x1858 (default pushed as two dwords)
    RulesColor_004B9BD0 unknown_1860;   // +0x1860 (ctor 0x4B9BD0)
    ColorStruct unknown_1863;   // +0x1863
    ColorStruct unknown_1866;   // +0x1866 read at 0x66B7AD
    ColorStruct unknown_1869;   // +0x1869 read at 0x66B7D7
    int unknown_186C; // random upper bound minus one0x68508F
    AnimTypeClass* unknown_1870; // 0x6850D9 -> AnimClass constructor0x421EA0
    RulesColor_004B9BD0 ColorAdd[0x10];     // +0x1874
    char unknown_18A4[0x18B4 - 0x18A4];
    float unknown_18B4; // 0x469817: FMUL float ptr [ECX + 0x18b4]
    char unknown_18B8[8];
};

GG_STATIC_ASSERT(offsetof(RulesClass, unknown_050) == 0x50);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->unknown_050) == 4);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_B20) == 0xB20);
GG_STATIC_ASSERT(offsetof(RulesClass, BunkerSound) == 0x244);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_000) == 0x000);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_008) == 0x008);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_186C) == 0x186C);
GG_STATIC_ASSERT(offsetof(RulesClass, field_1C8) == 0x1C8);
GG_STATIC_ASSERT(offsetof(RulesClass, TypeA) == 0x4E0);
GG_STATIC_ASSERT(offsetof(RulesClass, TypeB) == 0x514);
GG_STATIC_ASSERT(offsetof(RulesClass, AIMinorSuperReadyPercent) == 0xD70);
GG_STATIC_ASSERT(offsetof(RulesClass, field_FD0) == 0xFD0);
GG_STATIC_ASSERT(offsetof(RulesClass, field_FD8) == 0xFD8);
GG_STATIC_ASSERT(offsetof(RulesClass, ElevationIncrement) == 0x1838);
GG_STATIC_ASSERT(offsetof(RulesClass, ElevationIncrementBonus) == 0x1840);
GG_STATIC_ASSERT(offsetof(RulesClass, ElevationBonusCap) == 0x1848);
GG_STATIC_ASSERT(offsetof(RulesClass, AlliedWallTransparency) == 0x1850);
GG_STATIC_ASSERT(offsetof(RulesClass, WallPenetratorThreshold) == 0x1858);
GG_STATIC_ASSERT(offsetof(RulesClass, ColorAdd) == 0x1874);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1870) == 0x1870);

GG_STATIC_ASSERT(offsetof(RulesClass, At_54C) == 0x54C);
GG_STATIC_ASSERT(offsetof(RulesClass, LandAnim) == 0x04C);
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
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_D54) == 0xD54);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_788) == 0x788);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_78C) == 0x78C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_7A8) == 0x7A8);
GG_STATIC_ASSERT(offsetof(RulesClass, C4Warhead) == 0x0FA8);
GG_STATIC_ASSERT(offsetof(RulesClass, ConditionYellow) == 0x1700);
GG_STATIC_ASSERT(offsetof(RulesClass, ConditionRed) == 0x1708);
GG_STATIC_ASSERT(offsetof(RulesClass, RadDurationMultiple) == 0x1804);

GG_STATIC_ASSERT(offsetof(RulesClass, unknown_044) == 0x44);



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
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_EE0) == 0xEE0);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_90) == 0x90);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1020) == 0x1020);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_17D0) == 0x17D0);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_DC) == 0xDC);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_678) == 0x678);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_16BC) == 0x16BC);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1794) == 0x1794);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_340) == 0x340);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_F60) == 0xF60);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_F48) == 0xF48);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_F54) == 0xF54);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_F5C) == 0xF5C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1790) == 0x1790);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_9C) == 0x9C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_BB8) == 0xBB8);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_BBC) == 0xBBC);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1863) == 0x1863);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1866) == 0x1866);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1869) == 0x1869);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_16F8) == 0x16F8);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_86C) == 0x86C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_870) == 0x870);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_874) == 0x874);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_878) == 0x878);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_87C) == 0x87C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_218) == 0x218);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_21C) == 0x21C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_33C) == 0x33C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_BEC) == 0xBEC);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_BF4) == 0xBF4);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_BF8) == 0xBF8);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_BFC) == 0xBFC);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_C00) == 0xC00);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_20) == 0x20);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_710) == 0x710);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_6F0) == 0x6F0);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_6F4) == 0x6F4);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_D58) == 0xD58);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_D5C) == 0xD5C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_D60) == 0xD60);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_420) == 0x420);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_7B8) == 0x7B8);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_7BC) == 0x7BC);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_188) == 0x188);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_18C) == 0x18C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_190) == 0x190);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_194) == 0x194);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_198) == 0x198);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_758) == 0x758);
GG_STATIC_ASSERT(sizeof(RulesClass)              == 0x18C0);

extern RulesClass* Rules;   // GLOBAL: GAMEMD 0x8871E0



GG_STATIC_ASSERT(offsetof(RulesClass, unknown_06AC) == 0x6AC);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1434) == 0x1434);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_14C0) == 0x14C0);

GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->C4Warhead) == 4);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_F8C) == 0xF8C);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->unknown_F8C) == 4);

// Bullet impact caller layout closure, native 4690B0 entry-origin assembly.
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_214) == 0x214);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->unknown_214) == 4);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_350) == 0x350);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->unknown_350) == 4);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_18B4) == 0x18B4);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->unknown_18B4) == 4);

// The typed container members, read off the constructors 0x664D20 / 0x665650 and destructor 0x667A30.
GG_STATIC_ASSERT(offsetof(RulesClass, list_0058) == 0x58);
GG_STATIC_ASSERT(offsetof(RulesClass, TouchdownAnims) == 0x104);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0120) == 0x120);
GG_STATIC_ASSERT(offsetof(RulesClass, list_013C) == 0x13C);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0158) == 0x158);
GG_STATIC_ASSERT(offsetof(RulesClass, list_02A0) == 0x2A0);
GG_STATIC_ASSERT(offsetof(RulesClass, list_02BC) == 0x2BC);
GG_STATIC_ASSERT(offsetof(RulesClass, list_02D8) == 0x2D8);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0358) == 0x358);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0374) == 0x374);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0390) == 0x390);
GG_STATIC_ASSERT(offsetof(RulesClass, list_03AC) == 0x3AC);
GG_STATIC_ASSERT(offsetof(RulesClass, list_03C8) == 0x3C8);
GG_STATIC_ASSERT(offsetof(RulesClass, list_03E4) == 0x3E4);
GG_STATIC_ASSERT(offsetof(RulesClass, list_043C) == 0x43C);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0458) == 0x458);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0474) == 0x474);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0600) == 0x600);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0648) == 0x648);
GG_STATIC_ASSERT(offsetof(RulesClass, list_06CC) == 0x6CC);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0734) == 0x734);
GG_STATIC_ASSERT(offsetof(RulesClass, list_07C4) == 0x7C4);
GG_STATIC_ASSERT(offsetof(RulesClass, list_07E0) == 0x7E0);
GG_STATIC_ASSERT(offsetof(RulesClass, list_07FC) == 0x7FC);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0818) == 0x818);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0834) == 0x834);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0850) == 0x850);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0880) == 0x880);
GG_STATIC_ASSERT(offsetof(RulesClass, list_08AC) == 0x8AC);
GG_STATIC_ASSERT(offsetof(RulesClass, list_08C8) == 0x8C8);
GG_STATIC_ASSERT(offsetof(RulesClass, list_08E4) == 0x8E4);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0900) == 0x900);
GG_STATIC_ASSERT(offsetof(RulesClass, list_091C) == 0x91C);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0938) == 0x938);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0954) == 0x954);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0970) == 0x970);
GG_STATIC_ASSERT(offsetof(RulesClass, list_098C) == 0x98C);
GG_STATIC_ASSERT(offsetof(RulesClass, list_09A8) == 0x9A8);
GG_STATIC_ASSERT(offsetof(RulesClass, list_09C4) == 0x9C4);
GG_STATIC_ASSERT(offsetof(RulesClass, list_09E0) == 0x9E0);
GG_STATIC_ASSERT(offsetof(RulesClass, list_09FC) == 0x9FC);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0A18) == 0xA18);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0A34) == 0xA34);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0A50) == 0xA50);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0A6C) == 0xA6C);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0A88) == 0xA88);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0AA4) == 0xAA4);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0AC0) == 0xAC0);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0ADC) == 0xADC);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0B3C) == 0xB3C);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0B58) == 0xB58);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0B74) == 0xB74);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0B90) == 0xB90);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0BC0) == 0xBC0);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0C04) == 0xC04);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0C20) == 0xC20);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0C3C) == 0xC3C);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0C58) == 0xC58);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0C74) == 0xC74);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0C90) == 0xC90);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0CAC) == 0xCAC);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0CC8) == 0xCC8);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0CE4) == 0xCE4);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0D00) == 0xD00);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0D1C) == 0xD1C);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0D38) == 0xD38);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0D80) == 0xD80);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0D9C) == 0xD9C);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0DB8) == 0xDB8);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0DD4) == 0xDD4);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0E10) == 0xE10);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0E2C) == 0xE2C);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0E4C) == 0xE4C);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0E68) == 0xE68);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0E84) == 0xE84);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0EA0) == 0xEA0);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0EC4) == 0xEC4);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0EE8) == 0xEE8);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0F04) == 0xF04);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0F20) == 0xF20);
GG_STATIC_ASSERT(offsetof(RulesClass, list_0FF8) == 0xFF8);
GG_STATIC_ASSERT(offsetof(RulesClass, list_1158) == 0x1158);
GG_STATIC_ASSERT(offsetof(RulesClass, list_1174) == 0x1174);
GG_STATIC_ASSERT(offsetof(RulesClass, list_1194) == 0x1194);
GG_STATIC_ASSERT(offsetof(RulesClass, list_11B0) == 0x11B0);
GG_STATIC_ASSERT(offsetof(RulesClass, list_11CC) == 0x11CC);
GG_STATIC_ASSERT(offsetof(RulesClass, list_11E8) == 0x11E8);
GG_STATIC_ASSERT(offsetof(RulesClass, list_1204) == 0x1204);
GG_STATIC_ASSERT(offsetof(RulesClass, list_1220) == 0x1220);
GG_STATIC_ASSERT(offsetof(RulesClass, list_123C) == 0x123C);
GG_STATIC_ASSERT(offsetof(RulesClass, list_1258) == 0x1258);
GG_STATIC_ASSERT(offsetof(RulesClass, list_1274) == 0x1274);
GG_STATIC_ASSERT(offsetof(RulesClass, list_1290) == 0x1290);
GG_STATIC_ASSERT(offsetof(RulesClass, list_12AC) == 0x12AC);
GG_STATIC_ASSERT(offsetof(RulesClass, list_12C8) == 0x12C8);
GG_STATIC_ASSERT(offsetof(RulesClass, list_12E4) == 0x12E4);
GG_STATIC_ASSERT(offsetof(RulesClass, list_1304) == 0x1304);
GG_STATIC_ASSERT(offsetof(RulesClass, list_1320) == 0x1320);
GG_STATIC_ASSERT(offsetof(RulesClass, list_133C) == 0x133C);
GG_STATIC_ASSERT(offsetof(RulesClass, list_1358) == 0x1358);
GG_STATIC_ASSERT(offsetof(RulesClass, list_1374) == 0x1374);
GG_STATIC_ASSERT(offsetof(RulesClass, list_1390) == 0x1390);
GG_STATIC_ASSERT(offsetof(RulesClass, list_13AC) == 0x13AC);
GG_STATIC_ASSERT(offsetof(RulesClass, list_13C8) == 0x13C8);
GG_STATIC_ASSERT(offsetof(RulesClass, list_13F0) == 0x13F0);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1860) == 0x1860);
GG_STATIC_ASSERT(sizeof(RulesColor_004B9BD0) == 3);
GG_STATIC_ASSERT(offsetof(RulesClass, list_013C) + 4 == 0x140);  // Items
GG_STATIC_ASSERT(offsetof(RulesClass, list_013C) + 0x10 == 0x14C);  // Count

#endif
