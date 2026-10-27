// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: UnitTypeClass ctor FUN_0x007470D0 member-access sites
//   (start 0xDF8, size ~0xE78), cross-checked vs YRpp.
//   Verified by the pad anchor unknown_E10@0xE10 plus the ctor spot-checks
//   Facings@0xE3C, AltImage@0xE58, WalkFrames@0xE5C. Parent ctor 0x710AF0
//   (TechnoTypeClass) runs first, so the leaf body starts at 0xDF8.
//
// UnitTypeClass - blueprint for a tracked/wheeled vehicle type. Derives
// TechnoTypeClass (the full combat/movement/voice/cameo blueprint spine) at
// offset 0 and appends the vehicle-only animation-frame, deploy, turret-shadow
// and alt-image fields from 0xDF8.
//
// Pointer members read as int/undefined4 in the decomp are 64-bit truncation
// sites; modelled here as real 4-byte pointers so every offset stays byte-exact.
#ifndef GG_MATCH_LAYOUT_UNIT_TYPE_CLASS_H
#define GG_MATCH_LAYOUT_UNIT_TYPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "techno_type_class.h"   // TechnoTypeClass (sizeof 0xDF8), CoordStruct, SHPStruct

// ---------------------------------------------------------------------------
// UnitTypeClass  (0xDF8..0xE77, sizeof = 0xE78)
// ---------------------------------------------------------------------------
class UnitTypeClass : public TechnoTypeClass
{
public:
    // Declaration: GAMEMD 0x747F20 -- slot45, full EAX scalar, no args.
    virtual int vf_45();
    int          ArrayIndex;               // +0xDF8
    int          MovementRestrictedTo;     // +0xDFC (LandType enum)
    CoordStruct  HalfDamageSmokeLocation;  // +0xE00 (0xC)
    bool         Passive;                  // +0xE0C
    bool         CrateGoodie;              // +0xE0D
    bool         Harvester;                // +0xE0E
    bool         Weeder;                   // +0xE0F
    bool         unknown_E10;              // +0xE10 (anchor)
    bool         HasTurret;                // +0xE11
    bool         DeployToFire;             // +0xE12
    bool         IsSimpleDeployer;         // +0xE13
    bool         IsTilter;                 // +0xE14
    bool         UseTurretShadow;          // +0xE15
    bool         TooBigToFitUnderBridge;   // +0xE16
    bool         CanBeach;                 // +0xE17
    bool         SmallVisceroid;           // +0xE18
    bool         LargeVisceroid;           // +0xE19
    bool         CarriesCrate;             // +0xE1A
    bool         NonVehicle;               // +0xE1B
    int          StandingFrames;           // +0xE1C
    int          DeathFrames;              // +0xE20
    int          DeathFrameRate;           // +0xE24
    int          StartStandFrame;          // +0xE28
    int          StartWalkFrame;           // +0xE2C
    int          StartFiringFrame;         // +0xE30
    int          StartDeathFrame;          // +0xE34
    int          MaxDeathCounter;          // +0xE38
    int          Facings;                  // +0xE3C
    int          FiringSyncFrame0;         // +0xE40
    int          FiringSyncFrame1;         // +0xE44
    int          BurstDelay[4];            // +0xE48 (0xE48..0xE57)
    SHPStruct*   AltImage;                 // +0xE58 (truncation)
    char         WalkFrames;               // +0xE5C
    char         FiringFrames;             // +0xE5D
    char         AltImageFile[0x19];       // +0xE5E (0xE5E..0xE76)
    unsigned char align_E77[1];            // +0xE77 (pad to 8-aligned 0xE78)
};

// --- Representative offset asserts (spanning the struct) + final sizeof ------
GG_STATIC_ASSERT(offsetof(UnitTypeClass, ArrayIndex)             == 0xDF8);
GG_STATIC_ASSERT(offsetof(UnitTypeClass, MovementRestrictedTo)   == 0xDFC);
GG_STATIC_ASSERT(offsetof(UnitTypeClass, HalfDamageSmokeLocation)== 0xE00);
GG_STATIC_ASSERT(offsetof(UnitTypeClass, Passive)                == 0xE0C);
GG_STATIC_ASSERT(offsetof(UnitTypeClass, unknown_E10)            == 0xE10);
GG_STATIC_ASSERT(offsetof(UnitTypeClass, DeployToFire)            == 0xE12);
GG_STATIC_ASSERT(sizeof(((UnitTypeClass*)0)->DeployToFire)        == 1);
GG_STATIC_ASSERT(offsetof(UnitTypeClass, NonVehicle)             == 0xE1B);
GG_STATIC_ASSERT(offsetof(UnitTypeClass, StandingFrames)         == 0xE1C);
GG_STATIC_ASSERT(offsetof(UnitTypeClass, MaxDeathCounter)        == 0xE38);
GG_STATIC_ASSERT(offsetof(UnitTypeClass, Facings)                == 0xE3C);
GG_STATIC_ASSERT(offsetof(UnitTypeClass, BurstDelay)             == 0xE48);
GG_STATIC_ASSERT(offsetof(UnitTypeClass, AltImage)              == 0xE58);
GG_STATIC_ASSERT(offsetof(UnitTypeClass, WalkFrames)             == 0xE5C);
GG_STATIC_ASSERT(offsetof(UnitTypeClass, FiringFrames)           == 0xE5D);
GG_STATIC_ASSERT(offsetof(UnitTypeClass, AltImageFile)           == 0xE5E);
GG_STATIC_ASSERT(sizeof(UnitTypeClass)                           == 0xE78);

#endif  // GG_MATCH_LAYOUT_UNIT_TYPE_CLASS_H
