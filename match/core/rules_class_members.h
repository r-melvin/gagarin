// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Member layout of the retail RulesClass (sizeof 0x18C0) as constructed by the
//   no-init constructor 0x664D20 (one stack argument, RET 4, returns this) (the
//   destructor 0x667A30 uses the same member list). Every offset and element type is read off those two
//   functions: each member is "LEA reg,[ESI+off]; call <capacity ctor>; MOV
//   [reg],<TypeList vtable>". Capacity ctors 0x67AC70 (VoxelAnim), 0x525250
//   (Anim), 0x477DB0 (int), 0x67AFF0 (Smudge), 0x5AC900 (Building), 0x513190
//   (Unit), 0x513560 (Aircraft), 0x512DC0 (Infantry), 0x67B370 (Terrain) pair
//   with the TypeList vtables 0x7F0D3C / 0x7EB6D4 / 0x7E4DD8 / 0x7F0D1C /
//   0x7ED90C / 0x7EABE8 / 0x7EABC8 / 0x7EAC08 / 0x7F0CFC.
//   The canonical RulesClass in _layout/rules_class.h keeps the bytes in the
//   gaps as padding and overlays several of these lists with raw-field views
//   (Items/Count of 0x104, 0x13C, 0xB20, 0xD00..0xD48, 0x1174, 0x1304), which
//   are in use elsewhere, so the typed members live in this view.
#ifndef GG_MATCH_CORE_RULES_CLASS_MEMBERS_H
#define GG_MATCH_CORE_RULES_CLASS_MEMBERS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "type_list.h"
#include "../_layout/color_struct.h"

class VoxelAnimTypeClass;
class AnimTypeClass;
class SmudgeTypeClass;
class BuildingTypeClass;
class UnitTypeClass;
class AircraftTypeClass;
class InfantryTypeClass;
class TerrainTypeClass;

// Three-byte colour with the out-of-line zeroing constructor 0x4B9BD0.
struct RulesColor_004B9BD0
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
    // FUNCTION: GAMEMD 0x4B9BD0 (decl; reloc)
    RulesColor_004B9BD0();
};

struct RulesClassMembers_00664D20
{
    // FUNCTION: GAMEMD 0x664D20
    RulesClassMembers_00664D20(const AbstractNoInit& noInit);
    // FUNCTION: GAMEMD 0x667A30
    ~RulesClassMembers_00664D20();

    char pad_0000[0x0058 - 0x0000];
    TypeList<const VoxelAnimTypeClass*> list_0058;  // +0x0058
    char pad_0074[0x0104 - 0x0074];
    TypeList<const AnimTypeClass*> list_0104;  // +0x0104
    TypeList<const AnimTypeClass*> list_0120;  // +0x0120
    TypeList<const AnimTypeClass*> list_013C;  // +0x013C
    TypeList<const AnimTypeClass*> list_0158;  // +0x0158
    char pad_0174[0x02A0 - 0x0174];
    TypeList<const AnimTypeClass*> list_02A0;  // +0x02A0
    TypeList<const AnimTypeClass*> list_02BC;  // +0x02BC
    TypeList<const AnimTypeClass*> list_02D8;  // +0x02D8
    char pad_02F4[0x0358 - 0x02F4];
    TypeList<int> list_0358;  // +0x0358
    TypeList<int> list_0374;  // +0x0374
    TypeList<int> list_0390;  // +0x0390
    TypeList<int> list_03AC;  // +0x03AC
    TypeList<int> list_03C8;  // +0x03C8
    TypeList<int> list_03E4;  // +0x03E4
    char pad_0400[0x043C - 0x0400];
    TypeList<int> list_043C;  // +0x043C
    TypeList<int> list_0458;  // +0x0458
    TypeList<int> list_0474;  // +0x0474
    char pad_0490[0x0600 - 0x0490];
    TypeList<const VoxelAnimTypeClass*> list_0600;  // +0x0600
    char pad_061C[0x0648 - 0x061C];
    TypeList<int> list_0648;  // +0x0648
    char pad_0664[0x06CC - 0x0664];
    TypeList<int> list_06CC;  // +0x06CC
    char pad_06E8[0x0734 - 0x06E8];
    TypeList<int> list_0734;  // +0x0734
    char pad_0750[0x07C4 - 0x0750];
    TypeList<const SmudgeTypeClass*> list_07C4;  // +0x07C4
    TypeList<const SmudgeTypeClass*> list_07E0;  // +0x07E0
    TypeList<const SmudgeTypeClass*> list_07FC;  // +0x07FC
    TypeList<const SmudgeTypeClass*> list_0818;  // +0x0818
    TypeList<const SmudgeTypeClass*> list_0834;  // +0x0834
    TypeList<const BuildingTypeClass*> list_0850;  // +0x0850
    char pad_086C[0x0880 - 0x086C];
    TypeList<const BuildingTypeClass*> list_0880;  // +0x0880
    char pad_089C[0x08AC - 0x089C];
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
    char pad_0AF8[0x0B20 - 0x0AF8];
    TypeList<const UnitTypeClass*> list_0B20;  // +0x0B20
    TypeList<const UnitTypeClass*> list_0B3C;  // +0x0B3C
    TypeList<const AircraftTypeClass*> list_0B58;  // +0x0B58
    TypeList<const AnimTypeClass*> list_0B74;  // +0x0B74
    TypeList<const AnimTypeClass*> list_0B90;  // +0x0B90
    char pad_0BAC[0x0BC0 - 0x0BAC];
    TypeList<const AnimTypeClass*> list_0BC0;  // +0x0BC0
    char pad_0BDC[0x0C04 - 0x0BDC];
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
    char pad_0D54[0x0D80 - 0x0D54];
    TypeList<int> list_0D80;  // +0x0D80
    TypeList<int> list_0D9C;  // +0x0D9C
    TypeList<int> list_0DB8;  // +0x0DB8
    TypeList<int> list_0DD4;  // +0x0DD4
    char pad_0DF0[0x0E10 - 0x0DF0];
    TypeList<int> list_0E10;  // +0x0E10
    TypeList<int> list_0E2C;  // +0x0E2C
    char pad_0E48[0x0E4C - 0x0E48];
    TypeList<int> list_0E4C;  // +0x0E4C
    TypeList<int> list_0E68;  // +0x0E68
    TypeList<int> list_0E84;  // +0x0E84
    TypeList<int> list_0EA0;  // +0x0EA0
    char pad_0EBC[0x0EC4 - 0x0EBC];
    TypeList<int> list_0EC4;  // +0x0EC4
    char pad_0EE0[0x0EE8 - 0x0EE0];
    TypeList<int> list_0EE8;  // +0x0EE8
    TypeList<int> list_0F04;  // +0x0F04
    TypeList<int> list_0F20;  // +0x0F20
    char pad_0F3C[0x0FF8 - 0x0F3C];
    TypeList<const TerrainTypeClass*> list_0FF8;  // +0x0FF8
    char pad_1014[0x1158 - 0x1014];
    TypeList<int> list_1158;  // +0x1158
    TypeList<int> list_1174;  // +0x1174
    char pad_1190[0x1194 - 0x1190];
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
    char pad_1300[0x1304 - 0x1300];
    TypeList<int> list_1304;  // +0x1304
    TypeList<int> list_1320;  // +0x1320
    TypeList<int> list_133C;  // +0x133C
    TypeList<int> list_1358;  // +0x1358
    TypeList<int> list_1374;  // +0x1374
    TypeList<int> list_1390;  // +0x1390
    TypeList<int> list_13AC;  // +0x13AC
    TypeList<int> list_13C8;  // +0x13C8
    char pad_13E4[0x13F0 - 0x13E4];
    TypeList<int> list_13F0;  // +0x13F0
    char pad_140C[0x1860 - 0x140C];
    RulesColor_004B9BD0 color_1860;  // +0x1860
    ColorStruct color_1863;  // +0x1863 LineTrailColorOverride
    ColorStruct color_1866;  // +0x1866 ChronoBeamColor
    ColorStruct color_1869;  // +0x1869 MagnaBeamColor
    char pad_186C[0x1874 - 0x186C];
    RulesColor_004B9BD0 colorAdd[16];  // +0x1874
    char pad_18A4[0x18C0 - 0x18A4];
};
GG_STATIC_ASSERT(sizeof(RulesClassMembers_00664D20) == 0x18C0);
GG_STATIC_ASSERT(offsetof(RulesClassMembers_00664D20, list_0058) == 0x58);
GG_STATIC_ASSERT(offsetof(RulesClassMembers_00664D20, list_0B20) == 0xB20);
GG_STATIC_ASSERT(offsetof(RulesClassMembers_00664D20, list_13F0) == 0x13F0);
GG_STATIC_ASSERT(offsetof(RulesClassMembers_00664D20, colorAdd) == 0x1874);

#endif
