// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: BuildingClass ctor FUN_0x0043B740 (chains TechnoClass ctor
//   FUN_0x006F2B40 at offset 0). The ctor stores essentially every field in the
//   0x520..0x71B span; each member below carries the address of the store (or
//   the read) that proves it. Secondary sweep: all 35 BuildingClass-bound
//   addresses in the YRpp method map were disassembled and their
//   [reg+disp] operands collected, which re-confirms 0x520, 0x524, 0x528,
//   0x534, 0x538, 0x540, 0x548, 0x55C, 0x5B8, 0x5C8, 0x5EC, 0x600, 0x614,
//   0x618, 0x61C, 0x660, 0x664, 0x668, 0x669, 0x66C, 0x684, 0x694, 0x69C,
//   0x6F0, 0x6F4, 0x700, 0x702, 0x718 from live code paths.
//
//   sizeof: `PUSH 0x720` immediately precedes the ctor call at 11 of the 11
//   allocation sites found by `ghidra x-ref to 0x43B740`.
//
//   RTTI (read from the binary, outranks any document): the four vptrs stored
//   at 0x0043B9FA..0x0043BA0E (0x007E3EBC / 0x007E3EA0 / 0x007E3E98 /
//   0x007E3E90) all resolve to ".?AVBuildingClass@@", COL base-offset
//   0 / 4 / 8 / 12.
//
//   Two structural facts the ctor settles outright:
//     * AnimStates is exactly 0x15 bytes at 0x5B0 — the ctor zeroes it as five
//       dwords (0x5B0/0x5B4/0x5B8/0x5BC/0x5C0) plus one byte (0x5C4),
//       @0x0043BA7F..0x0043BAA3. That is 21 bytes, matching Anims[0x15].
//     * RepairProgress is a StageClass at 0x620: Value 0x620, HasChanged 0x624,
//       Timer.StartTime 0x628, Timer.TimeLeft 0x630, Rate 0x634, Step 0x638(=1)
//       — the exact StageClass shape already proven in techno_class.h.
//
//   DISAGREEMENTS / gaps vs YRpp:
//     * YRpp annotates the 0x5E8..0x5F8 region "5E8 - 5F8 ????????" and is
//       unsure where Upgrades[3] sits. The binary settles it: the ctor stores
//       the same value to 0x5EC, 0x5F0 and 0x5F4 in one run
//       (@0x0043BA22/0x0043BA2A/0x0043BA30), and BuildingClass code takes
//       `LEA EDI,[ESI+0x5EC]` @0x0045270A to walk it. Upgrades[3] is at 0x5EC.
//     * YRpp's member list ends at TankBunkerState (0x718) but the object is
//       0x720 bytes. The trailing dword at 0x71C is NOT accounted for by YRpp
//       and we could not confirm it: the only [reg+0x71C] in BuildingClass code
//       (@0x0044B068) is taken off `[ESI+0x520]`, i.e. off BuildingTypeClass,
//       not off the BuildingClass. It goes in as unknown_71C.
//
// BuildingClass — a structure. Derives TechnoClass at offset 0
// (sizeof(TechnoClass) == 0x520); NOT a FootClass.
#ifndef GG_MATCH_LAYOUT_BUILDING_CLASS_H
#define GG_MATCH_LAYOUT_BUILDING_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "techno_class.h"     // TechnoClass spine + CDTimerClass + CoordStruct + StageClass + AudioController
#include "vector_class.h"     // DynamicVectorClass
#include "components.h"       // ColorStruct

// Shared XYWH rectangle; offsets are asserted in geometry2d.h.
#include "geometry2d.h"

// RateTimer — a CDTimerClass plus its reload rate (sizeof = 0x10). Proven here
// by BuildingClass::GateTimer: ctor stores StartTime 0x604, TimeLeft 0x60C,
// Rate 0x610, and the next member (LightSource) is read at 0x614.
#ifndef GG_MATCH_LAYOUT_RATETIMER_DEFINED
#define GG_MATCH_LAYOUT_RATETIMER_DEFINED
struct RateTimer
{
    CDTimerClass Timer;   // +0x00  (0xC)
    int          Rate;    // +0x0C
};
GG_STATIC_ASSERT(offsetof(RateTimer, Rate) == 0x0C);
GG_STATIC_ASSERT(sizeof(RateTimer)         == 0x10);
#endif

struct BuildingClass : TechnoClass
{
    void*          Type;                  // +0x520 BuildingTypeClass*; ctor MOV [ESI+0x520],ECX(=pType) @0x0043B756
    void*          Factory;               // +0x524 FactoryClass*; ctor @0x0043B75C (=0)
    CDTimerClass   C4Timer;               // +0x528 (0xC) ctor StartTime @0x0043B76B, TimeLeft @0x0043B771
    int            BState;                // +0x534 ctor @0x0043B777
    int            QueueBState;           // +0x538 ctor @0x0043B77D
    unsigned int   OwnerCountryIndex;     // +0x53C ctor @0x0043B783
    void*          C4AppliedBy;           // +0x540 InfantryClass*; ctor @0x0043B789
    unsigned int   unknown_544;           // +0x544 ctor @0x0043B78F
    void*          FirestormAnim;         // +0x548 AnimClass*; ctor @0x0043B795
    void*          PsiWarnAnim;           // +0x54C AnimClass*; ctor @0x0043B79B
    CDTimerClass   FactoryRetryTimer;     // +0x550 (0xC) ctor StartTime @0x0043B7A7, TimeLeft @0x0043B7AD
    void*          Anims[0x15];           // +0x55C .. 0x5AF  ctor: MOV ECX,0x15 / LEA EDI,[ESI+0x55C] /
                                          //   REP STOSD @0x0043BA63..0x0043BA70 — 21 dwords, exact
    unsigned char  AnimStates[0x15];      // +0x5B0 .. 0x5C4  ctor zeroes 5 dwords + 1 byte @0x0043BA7F..0x0043BAA3
    unsigned char  align_5C5[3];          // +0x5C5
    void*          DamageFireAnims[0x8];  // +0x5C8 .. 0x5E7  ctor: MOV ECX,8 / LEA EDI,[ESI+0x5C8] /
                                          //   REP STOSD @0x0043BA72..0x0043BA7D
    unsigned char  RequiresDamageFires;   // +0x5E8 ctor MOV byte [ESI+0x5E8],BL @0x0043B7B3
    unsigned char  align_5E9[3];          // +0x5E9
    void*          Upgrades[0x3];         // +0x5EC ctor @0x0043BA22/0x0043BA2A/0x0043BA30; walked by
                                          //   LEA EDI,[ESI+0x5EC] @0x0045270A
    int            FiringSWType;          // +0x5F8 ctor @0x0043B7B9
    unsigned int   unknown_5FC;           // +0x5FC ctor @0x0043B7BF
    void*          Spotlight;             // +0x600 BuildingLightClass*; ctor @0x0043B7C5
    RateTimer      GateTimer;             // +0x604 (0x10) ctor StartTime @0x0043B7D7, TimeLeft @0x0043B7D1,
                                          //   Rate @0x0043B7DD
    void*          LightSource;           // +0x614 LightSourceClass*; ctor @0x0043B7E3
    unsigned int   LaserFenceFrame;       // +0x618 ctor @0x0043B7E9
    unsigned int   FirestormWallFrame;    // +0x61C ctor @0x0043B7EF
    StageClass     RepairProgress;        // +0x620 (0x1C) ctor @0x0043B7F5..0x0043B819 (Step = 1)
    RectangleStruct unknown_rect_63C;     // +0x63C (0x10) ctor LEA EDX,[ESI+0x63C] @0x0043B829
    CoordStruct    unknown_coord_64C;     // +0x64C (0xC)  ctor LEA EDX,[ESI+0x64C] @0x0043B856
    int            unknown_int_658;       // +0x658 ctor @0x0043B876
    unsigned int   unknown_65C;           // +0x65C ctor @0x0043B87C
    unsigned char  HasPower;              // +0x660 ctor MOV byte [ESI+0x660],1 @0x0043B882
    unsigned char  IsOverpowered;         // +0x661 ctor @0x0043B889
    unsigned char  RegisteredAsPoweredUnitSource; // +0x662 ctor @0x0043B88F
    unsigned char  align_663;             // +0x663
    unsigned int   SupportingPrisms;      // +0x664 ctor @0x0043B895
    unsigned char  HasExtraPowerBonus;    // +0x668 ctor @0x0043B89B
    unsigned char  HasExtraPowerDrain;    // +0x669 ctor @0x0043B8AB
    unsigned char  align_66A[2];          // +0x66A
    DynamicVectorClassLayout Overpowerers;      // +0x66C (0x18) ctor vptr @0x0043B8CA, fields
                                          //   @0x0043B8B1/0x0043B8B7/0x0043B8BD/0x0043B8C4/0x0043B8D6/0x0043B8D0
    DynamicVectorClassLayout Occupants;         // +0x684 (0x18) ctor vptr @0x0043B8F5, fields
                                          //   @0x0043B8DC/0x0043B8E2/0x0043B8E8/0x0043B8EF/0x0043B901/0x0043B8FB
    int            FiringOccupantIndex;   // +0x69C ctor @0x0043B907
    AudioController Audio7;               // +0x6A0 (0x14) ctor LEA ECX,[ESI+0x6A0]; CALL 0x00405BE0 @0x0043BA85
    AudioController Audio8;               // +0x6B4 (0x14) ctor LEA ECX,[ESI+0x6B4]; CALL 0x00405BE0 @0x0043BAAE
    unsigned char  WasOnline;             // +0x6C8 ctor @0x0043B90D
    unsigned char  ShowRealName;          // +0x6C9 ctor @0x0043B913
    unsigned char  BeingProduced;         // +0x6CA ctor @0x0043B919
    unsigned char  ShouldRebuild;         // +0x6CB ctor @0x0043B91F
    unsigned char  HasEngineer;           // +0x6CC ctor @0x0043B925
    unsigned char  align_6CD[3];          // +0x6CD
    CDTimerClass   CashProductionTimer;   // +0x6D0 (0xC) ctor StartTime @0x0043B937, TimeLeft @0x0043B931
    unsigned char  AI_Sellable;           // +0x6DC ctor MOV byte [ESI+0x6DC],1 @0x0043B93D
    unsigned char  IsReadyToCommence;     // +0x6DD ctor @0x0043B944
    unsigned char  NeedsRepairs;          // +0x6DE ctor @0x0043B94D
    unsigned char  C4Applied;             // +0x6DF ctor @0x0043B953
    unsigned char  NoCrew;                // +0x6E0 ctor @0x0043B95A
    unsigned char  unknown_bool_6E1;      // +0x6E1 ctor @0x0043B960
    unsigned char  unknown_bool_6E2;      // +0x6E2 ctor @0x0043B966
    unsigned char  HasBeenCaptured;       // +0x6E3 ctor @0x0043B96C
    unsigned char  ActuallyPlacedOnMap;   // +0x6E4 ctor @0x0043B972
    unsigned char  unknown_bool_6E5;      // +0x6E5 ctor @0x0043B978
    unsigned char  IsDamaged;             // +0x6E6 ctor @0x0043B97E
    unsigned char  IsFogged;              // +0x6E7 ctor @0x0043B984
    unsigned char  IsBeingRepaired;       // +0x6E8 ctor @0x0043B98A
    unsigned char  HasBuildUp;            // +0x6E9 ctor @0x0043B990
    unsigned char  StuffEnabled;          // +0x6EA ctor MOV byte [ESI+0x6EA],1 @0x0043B996
    signed char    HasCloakingData;       // +0x6EB ctor @0x0043B99D
    unsigned char  CloakRadius;           // +0x6EC ctor @0x0043B9A3
    signed char    Translucency;          // +0x6ED ctor @0x0043B9A9
    unsigned char  align_6EE[2];          // +0x6EE
    unsigned int   StorageFilledSlots;    // +0x6F0 ctor @0x0043B9AF
    void*          SecretProduction;      // +0x6F4 TechnoTypeClass*; ctor @0x0043B9B5
    ColorStruct    ColorAdd;              // +0x6F8 (3) ctor @0x0043B9BB/0x0043B9C1/0x0043B9C7
    unsigned char  align_6FB;             // +0x6FB
    int            unknown_int_6FC;       // +0x6FC ctor @0x0043B9CD
    short          unknown_short_700;     // +0x700 ctor MOV word [ESI+0x700],0x3E8 @0x0043B9D3
    unsigned char  UpgradeLevel;          // +0x702 ctor @0x0043B9DC
    signed char    GateStage;             // +0x703 ctor @0x0043B9E2
    int            PrismStage;            // +0x704 ctor @0x0043B9E8
    CoordStruct    PrismTargetCoords;     // +0x708 (0xC) ctor LEA EDX,[ESI+0x708] @0x0043BA1C
    unsigned int   DelayBeforeFiring;     // +0x714 ctor @0x0043B9EE
    int            TankBunkerState;       // +0x718 ctor @0x0043B9F4
    unsigned int   unknown_71C;           // +0x71C NOT confirmed — see header note; closes the object at 0x720
};

GG_STATIC_ASSERT(offsetof(BuildingClass, Type)                == 0x520);
GG_STATIC_ASSERT(offsetof(BuildingClass, Factory)             == 0x524);
GG_STATIC_ASSERT(offsetof(BuildingClass, C4Timer)             == 0x528);
GG_STATIC_ASSERT(offsetof(BuildingClass, BState)              == 0x534);
GG_STATIC_ASSERT(offsetof(BuildingClass, QueueBState)         == 0x538);
GG_STATIC_ASSERT(offsetof(BuildingClass, OwnerCountryIndex)   == 0x53C);
GG_STATIC_ASSERT(offsetof(BuildingClass, C4AppliedBy)         == 0x540);
GG_STATIC_ASSERT(offsetof(BuildingClass, unknown_544)         == 0x544);
GG_STATIC_ASSERT(offsetof(BuildingClass, FirestormAnim)       == 0x548);
GG_STATIC_ASSERT(offsetof(BuildingClass, PsiWarnAnim)         == 0x54C);
GG_STATIC_ASSERT(offsetof(BuildingClass, FactoryRetryTimer)   == 0x550);
GG_STATIC_ASSERT(offsetof(BuildingClass, Anims)               == 0x55C);
GG_STATIC_ASSERT(offsetof(BuildingClass, AnimStates)          == 0x5B0);
GG_STATIC_ASSERT(offsetof(BuildingClass, DamageFireAnims)     == 0x5C8);
GG_STATIC_ASSERT(offsetof(BuildingClass, RequiresDamageFires) == 0x5E8);
GG_STATIC_ASSERT(offsetof(BuildingClass, Upgrades)            == 0x5EC);
GG_STATIC_ASSERT(offsetof(BuildingClass, FiringSWType)        == 0x5F8);
GG_STATIC_ASSERT(offsetof(BuildingClass, unknown_5FC)         == 0x5FC);
GG_STATIC_ASSERT(offsetof(BuildingClass, Spotlight)           == 0x600);
GG_STATIC_ASSERT(offsetof(BuildingClass, GateTimer)           == 0x604);
GG_STATIC_ASSERT(offsetof(BuildingClass, LightSource)         == 0x614);
GG_STATIC_ASSERT(offsetof(BuildingClass, LaserFenceFrame)     == 0x618);
GG_STATIC_ASSERT(offsetof(BuildingClass, FirestormWallFrame)  == 0x61C);
GG_STATIC_ASSERT(offsetof(BuildingClass, RepairProgress)      == 0x620);
GG_STATIC_ASSERT(offsetof(BuildingClass, unknown_rect_63C)    == 0x63C);
GG_STATIC_ASSERT(offsetof(BuildingClass, unknown_coord_64C)   == 0x64C);
GG_STATIC_ASSERT(offsetof(BuildingClass, unknown_int_658)     == 0x658);
GG_STATIC_ASSERT(offsetof(BuildingClass, unknown_65C)         == 0x65C);
GG_STATIC_ASSERT(offsetof(BuildingClass, HasPower)            == 0x660);
GG_STATIC_ASSERT(offsetof(BuildingClass, IsOverpowered)       == 0x661);
GG_STATIC_ASSERT(offsetof(BuildingClass, RegisteredAsPoweredUnitSource) == 0x662);
GG_STATIC_ASSERT(offsetof(BuildingClass, SupportingPrisms)    == 0x664);
GG_STATIC_ASSERT(offsetof(BuildingClass, HasExtraPowerBonus)  == 0x668);
GG_STATIC_ASSERT(offsetof(BuildingClass, HasExtraPowerDrain)  == 0x669);
GG_STATIC_ASSERT(offsetof(BuildingClass, Overpowerers)        == 0x66C);
GG_STATIC_ASSERT(offsetof(BuildingClass, Occupants)           == 0x684);
GG_STATIC_ASSERT(offsetof(BuildingClass, FiringOccupantIndex) == 0x69C);
GG_STATIC_ASSERT(offsetof(BuildingClass, Audio7)              == 0x6A0);
GG_STATIC_ASSERT(offsetof(BuildingClass, Audio8)              == 0x6B4);
GG_STATIC_ASSERT(offsetof(BuildingClass, WasOnline)           == 0x6C8);
GG_STATIC_ASSERT(offsetof(BuildingClass, HasEngineer)         == 0x6CC);
GG_STATIC_ASSERT(offsetof(BuildingClass, CashProductionTimer) == 0x6D0);
GG_STATIC_ASSERT(offsetof(BuildingClass, AI_Sellable)         == 0x6DC);
GG_STATIC_ASSERT(offsetof(BuildingClass, NoCrew)              == 0x6E0);
GG_STATIC_ASSERT(offsetof(BuildingClass, HasBeenCaptured)     == 0x6E3);
GG_STATIC_ASSERT(offsetof(BuildingClass, IsDamaged)           == 0x6E6);
GG_STATIC_ASSERT(offsetof(BuildingClass, IsBeingRepaired)     == 0x6E8);
GG_STATIC_ASSERT(offsetof(BuildingClass, StuffEnabled)        == 0x6EA);
GG_STATIC_ASSERT(offsetof(BuildingClass, HasCloakingData)     == 0x6EB);
GG_STATIC_ASSERT(offsetof(BuildingClass, CloakRadius)         == 0x6EC);
GG_STATIC_ASSERT(offsetof(BuildingClass, Translucency)        == 0x6ED);
GG_STATIC_ASSERT(offsetof(BuildingClass, StorageFilledSlots)  == 0x6F0);
GG_STATIC_ASSERT(offsetof(BuildingClass, SecretProduction)    == 0x6F4);
GG_STATIC_ASSERT(offsetof(BuildingClass, ColorAdd)            == 0x6F8);
GG_STATIC_ASSERT(offsetof(BuildingClass, unknown_int_6FC)     == 0x6FC);
GG_STATIC_ASSERT(offsetof(BuildingClass, unknown_short_700)   == 0x700);
GG_STATIC_ASSERT(offsetof(BuildingClass, UpgradeLevel)        == 0x702);
GG_STATIC_ASSERT(offsetof(BuildingClass, GateStage)           == 0x703);
GG_STATIC_ASSERT(offsetof(BuildingClass, PrismStage)          == 0x704);
GG_STATIC_ASSERT(offsetof(BuildingClass, PrismTargetCoords)   == 0x708);
GG_STATIC_ASSERT(offsetof(BuildingClass, DelayBeforeFiring)   == 0x714);
GG_STATIC_ASSERT(offsetof(BuildingClass, TankBunkerState)     == 0x718);
GG_STATIC_ASSERT(offsetof(BuildingClass, unknown_71C)         == 0x71C);
GG_STATIC_ASSERT(sizeof(BuildingClass)                        == 0x720);

// VTABLE: GAMEMD 0x007E3EBC  BuildingClass            (COL base 0)
// VTABLE: GAMEMD 0x007E3EA0  BuildingClass::(+0x04)   (COL base 4)
// VTABLE: GAMEMD 0x007E3E98  BuildingClass::(+0x08)   (COL base 8)
// VTABLE: GAMEMD 0x007E3E90  BuildingClass::(+0x0C)   (COL base 12)

#endif  // GG_MATCH_LAYOUT_BUILDING_CLASS_H
