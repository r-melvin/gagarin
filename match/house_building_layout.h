// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Canonical BuildingClass member offsets: every member that two or more house/building clusters read, named once.
//   The five BuildingClass views (BuildingAView, BA2Building, BuildingA3View, BA4Building, BuildingBView) stay
//   separate (see house_building_views.h for why) but each asserts its members against these values, so the views
//   cannot drift apart. Offsets are retail [reg+disp] operands from gamemd.exe v1.001.
//   Regenerate the enum and the per-view asserts together when a view gains a member.
#ifndef GG_MATCH_ECONOMY_HOUSE_BUILDING_HOUSE_BUILDING_LAYOUT_H
#define GG_MATCH_ECONOMY_HOUSE_BUILDING_HOUSE_BUILDING_LAYOUT_H

enum HBBuildingOffset
{
    HB_BLD_UNKNOWN_38                    = 0x038,   // building-a3 unknown_38, building-a4 unknown_38
    HB_BLD_HEALTH                        = 0x06C,   // building-b Health, building-a unknown_6C, building-a2 unknown_6C, building-a3 unknown_6C
    HB_BLD_UNKNOWN_70                    = 0x070,   // building-a unknown_70, building-a2 unknown_70
    HB_BLD_NEEDS_REDRAW                  = 0x080,   // building-b NeedsRedraw, building-a unknown_80, building-a2 unknown_80, building-a3 unknown_80, building-a4 unknown_80
    HB_BLD_IN_LIMBO                      = 0x081,   // building-b InLimbo, building-a unknown_81, building-a2 unknown_81, building-a3 unknown_81, building-a4 unknown_81
    HB_BLD_IS_ALIVE                      = 0x090,   // building-b IsAlive, building-a2 unknown_90, building-a4 unknown_90
    HB_BLD_LOCATION                      = 0x09C,   // building-b Location, building-a Location, building-a2 Location, building-a3 Location, building-a4 Location
    HB_BLD_CURRENT_MISSION               = 0x0AC,   // building-b CurrentMission, building-a unknown_AC, building-a2 unknown_AC, building-a4 unknown_AC
    HB_BLD_UNKNOWN_B4                    = 0x0B4,   // building-a unknown_B4, building-a4 unknown_B4
    HB_BLD_STATUS                        = 0x0BC,   // building-a unknown_BC, building-a2 unknown_BC, building-a3 Status, building-a4 unknown_BC
    HB_BLD_UNKNOWN_C4                    = 0x0C4,   // building-a unknown_C4, building-a4 unknown_C4
    HB_BLD_UNKNOWN_E8                    = 0x0E8,   // building-a unknown_E8, building-a2 unknown_E8, building-a3 unknown_E8, building-a4 unknown_E8
    HB_BLD_UNKNOWN_114                   = 0x114,   // building-a unknown_114, building-a2 unknown_114, building-a3 unknown_114
    HB_BLD_UNKNOWN_150                   = 0x150,   // building-a unknown_150, building-a2 unknown_150
    HB_BLD_UNKNOWN_210                   = 0x210,   // building-a3 unknown_210, building-a4 unknown_210
    HB_BLD_UNKNOWN_218                   = 0x218,   // building-b unknown_218, building-a2 unknown_218, building-a3 unknown_218
    HB_BLD_OWNER                         = 0x21C,   // building-b Owner, building-a Owner, building-a2 Owner, building-a3 Owner, building-a4 Owner
    HB_BLD_UNKNOWN_268                   = 0x268,   // building-a unknown_268, building-a3 unknown_268
    HB_BLD_UNKNOWN_294                   = 0x294,   // building-b unknown_294, building-a4 unknown_294
    HB_BLD_TARGET                        = 0x2B4,   // building-a Target, building-a2 unknown_2B4, building-a4 Target
    HB_BLD_MIND_CONTROLLED_BY            = 0x2C0,   // building-b MindControlledBy, building-a unknown_2C0, building-a2 unknown_2C0
    HB_BLD_UNKNOWN_2FC                   = 0x2FC,   // building-a unknown_2FC, building-a2 unknown_2FC, building-a3 unknown_2FC
    HB_BLD_UNKNOWN_30C                   = 0x30C,   // building-b unknown_30C, building-a2 unknown_30C, building-a4 unknown_30C
    HB_BLD_UNKNOWN_33C                   = 0x33C,   // building-a2 unknown_33C, building-a3 unknown_33C
    HB_BLD_STAGE                         = 0x350,   // building-a2 Stage, building-a3 unknown_350, building-a4 unknown_350
    HB_BLD_TURRET                        = 0x370,   // building-a2 Turret, building-a3 Facing370, building-a4 unknown_370
    HB_BLD_FACING                        = 0x388,   // building-a Facing, building-a2 Facing, building-a3 Facing388, building-a4 Facing
    HB_BLD_UNKNOWN_3D3                   = 0x3D3,   // building-a unknown_3D3, building-a4 unknown_3D3
    HB_BLD_UNKNOWN_418                   = 0x418,   // building-a2 unknown_418, building-a3 unknown_418, building-a4 unknown_418
    HB_BLD_UNKNOWN_41A                   = 0x41A,   // building-b unknown_41A, building-a2 unknown_41A, building-a3 unknown_41A, building-a4 unknown_41A
    HB_BLD_UNKNOWN_41B                   = 0x41B,   // building-b unknown_41B, building-a unknown_41B, building-a4 unknown_41B
    HB_BLD_TYPE                          = 0x520,   // building-b Type, building-a Type, building-a2 Type, building-a3 Type, building-a4 Type
    HB_BLD_FACTORY                       = 0x524,   // building-b Factory, building-a Factory, building-a2 unknown_524, building-a4 unknown_524
    // RESOLVED: a 0xC-byte countdown timer {StartTime, unknown, TimeLeft}: building-a2 (0x442230) tests +0x528 against -1 and Frame-minus-start against +0x530 (the time-left test); building-a3 (0x4415F0) starts it, Frame into +0x528 and 0 or 8 into +0x530, through a coordinate-shaped stand-in whose middle word comes from a stack temporary.
    HB_BLD_C4_TIMER                      = 0x528,   // building-b C4Timer, building-a2 unknown_528, building-a3 unknown_528
    HB_BLD_BSTATE                        = 0x534,   // building-b BState, building-a BState, building-a2 BState
    HB_BLD_OWNER_COUNTRY_INDEX           = 0x53C,   // building-b OwnerCountryIndex, building-a unknown_53C, building-a2 unknown_53C
    HB_BLD_C4_APPLIED_BY                 = 0x540,   // building-b C4AppliedBy, building-a C4AppliedBy, building-a3 C4AppliedBy
    HB_BLD_UNKNOWN_544                   = 0x544,   // building-b unknown_544, building-a4 unknown_544
    HB_BLD_FIRESTORM_ANIM                = 0x548,   // building-b FirestormAnim, building-a FirestormAnim
    HB_BLD_PSI_WARN_ANIM                 = 0x54C,   // building-b PsiWarnAnim, building-a3 unknown_54C
    // RESOLVED: AnimClass* Anims[21] (+0x55C..+0x5AF); building-a3 names single entries [8] +0x57C, [9] +0x580, [11] +0x588, [12] +0x58C.
    HB_BLD_ANIMS                         = 0x55C,   // building-b Anims, building-a Anims, building-a2 Anims, building-a4 Anims
    HB_BLD_DAMAGE_FIRE_ANIMS             = 0x5C8,   // building-b DamageFireAnims, building-a DamageFireAnims, building-a2 DamageFireAnims, building-a3 DamageFireAnims, building-a4 DamageFireAnims
    // RESOLVED: BuildingTypeClass* Upgrades[3] at +0x5EC (building-a, building-b index from 0). building-a2 / building-a4 declare a 4-entry array at +0x5E8 and index it with the upgrade level (1..3), which is the same element: retail addresses it as [level*4 + 0x5E8].
    HB_BLD_UPGRADES                      = 0x5EC,   // building-b Upgrades, building-a Upgrades
    HB_BLD_UNKNOWN_5FC                   = 0x5FC,   // building-b unknown_5FC, building-a3 unknown_5FC
    HB_BLD_SPOTLIGHT                     = 0x600,   // building-b Spotlight, building-a Spotlight, building-a4 Spotlight
    HB_BLD_LIGHT_SOURCE                  = 0x614,   // building-b LightSource, building-a LightSource, building-a2 LightSource, building-a3 LightSource, building-a4 unknown_614
    HB_BLD_LASER_FENCE_FRAME             = 0x618,   // building-b LaserFenceFrame, building-a4 unknown_618
    HB_BLD_HAS_POWER                     = 0x660,   // building-b HasPower, building-a unknown_660, building-a2 unknown_660
    HB_BLD_OVERPOWERERS                  = 0x66C,   // building-b Overpowerers, building-a Overpowerers
    HB_BLD_OCCUPANTS                     = 0x684,   // building-b Occupants, building-a Occupants
    HB_BLD_AUDIO7                        = 0x6A0,   // building-b Audio7, building-a unknown_6A0, building-a2 Audio
    HB_BLD_SHOULD_REBUILD                = 0x6CB,   // building-b ShouldRebuild, building-a4 unknown_6CB
    HB_BLD_HAS_ENGINEER                  = 0x6CC,   // building-b HasEngineer, building-a4 unknown_6CC
    // RESOLVED: a 0xC-byte timer (building-b reads its time left); building-a3 / building-a4 store a 12-byte temporary into it through same-size stand-ins (timer / coordinate).
    HB_BLD_CASH_PRODUCTION_TIMER         = 0x6D0,   // building-b CashProductionTimer, building-a3 unknown_6D0, building-a4 unknown_6D0
    HB_BLD_UNKNOWN_6DC                   = 0x6DC,   // building-b unknown_6DC, building-a unknown_6DC
    HB_BLD_IS_READY_TO_COMMENCE          = 0x6DD,   // building-b IsReadyToCommence, building-a unknown_6DD, building-a2 unknown_6DD, building-a3 unknown_6DD, building-a4 unknown_6DD
    HB_BLD_NEEDS_REPAIRS                 = 0x6DE,   // building-b NeedsRepairs, building-a unknown_6DE
    HB_BLD_C4_APPLIED                    = 0x6DF,   // building-b C4Applied, building-a unknown_6DF
    HB_BLD_NO_CREW                       = 0x6E0,   // building-b NoCrew, building-a2 unknown_6E0, building-a3 unknown_6E0
    HB_BLD_HAS_BEEN_CAPTURED             = 0x6E3,   // building-b HasBeenCaptured, building-a unknown_6E3, building-a4 unknown_6E3
    HB_BLD_ACTUALLY_PLACED_ON_MAP        = 0x6E4,   // building-b ActuallyPlacedOnMap, building-a3 unknown_6E4, building-a4 unknown_6E4
    HB_BLD_IS_DAMAGED                    = 0x6E6,   // building-b IsDamaged, building-a2 unknown_6E6
    HB_BLD_IS_BEING_REPAIRED             = 0x6E8,   // building-b IsBeingRepaired, building-a unknown_6E8, building-a4 unknown_6E8
    HB_BLD_STUFF_ENABLED                 = 0x6EA,   // building-b StuffEnabled, building-a4 unknown_6EA
    HB_BLD_HAS_CLOAKING_DATA             = 0x6EB,   // building-b HasCloakingData, building-a2 unknown_6EB, building-a3 unknown_6EB, building-a4 unknown_6EB
    HB_BLD_CLOAK_RADIUS                  = 0x6EC,   // building-b CloakRadius, building-a2 unknown_6EC, building-a3 unknown_6EC, building-a4 unknown_6EC
    HB_BLD_TRANSLUCENCY                  = 0x6ED,   // building-b Translucency, building-a4 unknown_6ED
    HB_BLD_UNKNOWN_700                   = 0x700,   // building-b unknown_short_700, building-a4 unknown_700
    HB_BLD_UPGRADE_LEVEL                 = 0x702,   // building-b UpgradeLevel, building-a2 unknown_702, building-a4 unknown_702
    HB_BLD_UNKNOWN_714                   = 0x714,   // building-a unknown_714, building-a4 unknown_714
    HB_BLD_END
};

#endif
