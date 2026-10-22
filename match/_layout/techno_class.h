// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: TechnoClass ctor FUN_0x006F2B40 (chains RadioClass ctor
//   FUN_0x0065A750 at offset 0). EVERY offset below is read directly from a
//   field-init write in that ctor — the whole 0xF0..0x51F span is covered, and
//   the last member DisguisedAsHouse @0x51C closes the object at 0x520. Key
//   confirmations from the ctor: Owner @0x21C (=param_1, the HouseClass*),
//   Ammo @0x2FC (=-1), TargetingTimer.TimeLeft @0x188 (=45), Tiberium
//   StorageClass ctor FUN_0x006C95E0(this+0x33C), UnloadTimer TransitionTimer
//   ctor FUN_0x004A50F0(this+0x350), BarrelFacing FacingClass ctor
//   FUN_0x004C91E0(this+0x370,3), the three DynamicVectorClass vptrs
//   @0x440/0x458/0x470 (PTR_FUN_007e4e78 / PTR_FUN_007e91ec), and the four
//   AudioController ctors FUN_0x00405BE0(this+0x488/0x4A4/0x4C0/0x4DC). The four
//   COM vptrs are written last (PTR_FUN_007f4960 et al). Cross-checked vs YRpp
//   (which static_asserts sizeof==0x520).
//
// TechnoClass — base of every buildable/ownable combat object (units,
// buildings, infantry, aircraft). Derives RadioClass at offset 0 and adds the
// enormous combat/veterancy/cloak/facing/targeting state block from 0xF0.
#ifndef GG_MATCH_LAYOUT_TECHNO_CLASS_H
#define GG_MATCH_LAYOUT_TECHNO_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "radio_class.h"      // RadioClass spine + CDTimerClass + CoordStruct + AudioController
#include "vector_class.h"     // VectorClass / DynamicVectorClass

// --- TechnoClass-side leaf components ---------------------------------------
// Self-guarded so a downstream layer (FootClass and the leaf classes) can reuse
// them. CDTimerClass / CoordStruct / AudioController come from the included
// chain (mission_class.h / object_class.h).

// FlashData — health-flash blink state (sizeof = 8).
#ifndef GG_MATCH_LAYOUT_FLASHDATA_DEFINED
#define GG_MATCH_LAYOUT_FLASHDATA_DEFINED
struct FlashData
{
    int           DurationRemaining;   // +0x00
    unsigned char FlashingNow;         // +0x04  (bool)
    unsigned char _pad_05[3];          // +0x05
};
GG_STATIC_ASSERT(sizeof(FlashData) == 8);
#endif

// StageClass — staged frame timer (sizeof = 0x1C). Value/HasChanged/Timer/
// Rate/Step; embeds a CDTimerClass.
#ifndef GG_MATCH_LAYOUT_STAGECLASS_DEFINED
#define GG_MATCH_LAYOUT_STAGECLASS_DEFINED
struct StageClass
{
    int           Value;        // +0x00
    unsigned char HasChanged;   // +0x04  (bool)
    unsigned char _pad_05[3];   // +0x05
    CDTimerClass  Timer;        // +0x08  (0xC)
    int           Rate;         // +0x14
    int           Step;         // +0x18
};
GG_STATIC_ASSERT(offsetof(StageClass, Timer) == 0x08);
GG_STATIC_ASSERT(offsetof(StageClass, Rate)  == 0x14);
GG_STATIC_ASSERT(sizeof(StageClass)          == 0x1C);
#endif

// PassengersClass — transport occupant list head (sizeof = 8). Confirmed
// anchor: NumPassengers @0, FirstPassenger @4.
#ifndef GG_MATCH_LAYOUT_PASSENGERSCLASS_DEFINED
#define GG_MATCH_LAYOUT_PASSENGERSCLASS_DEFINED
struct PassengersClass
{
    int   NumPassengers;     // +0x00
    void* FirstPassenger;    // +0x04  FootClass*
};
GG_STATIC_ASSERT(offsetof(PassengersClass, FirstPassenger) == 0x04);
GG_STATIC_ASSERT(sizeof(PassengersClass)                   == 8);
#endif

// VeterancyStruct — single packed promotion gauge (sizeof = 4).
#ifndef GG_MATCH_LAYOUT_VETERANCYSTRUCT_DEFINED
#define GG_MATCH_LAYOUT_VETERANCYSTRUCT_DEFINED
struct VeterancyStruct
{
    float Veterancy;   // +0x00
};
GG_STATIC_ASSERT(sizeof(VeterancyStruct) == 4);
#endif

// Point2D — 2D integer point (sizeof = 8).
#ifndef GG_MATCH_LAYOUT_POINT2D_DEFINED
#define GG_MATCH_LAYOUT_POINT2D_DEFINED
struct Point2D
{
    int X;   // +0x00
    int Y;   // +0x04
};
GG_STATIC_ASSERT(sizeof(Point2D) == 8);
#endif

// StorageClass — four-tiberium-type cargo cells (sizeof = 0x10). Owns the
// matched StorageClass::GetTotalValue @0x6C9600 family.
#ifndef GG_MATCH_LAYOUT_STORAGECLASS_DEFINED
#define GG_MATCH_LAYOUT_STORAGECLASS_DEFINED
struct StorageClass
{
    float Tiberium1;   // +0x00
    float Tiberium2;   // +0x04
    float Tiberium3;   // +0x08
    float Tiberium4;   // +0x0C
};
GG_STATIC_ASSERT(sizeof(StorageClass) == 0x10);
#endif

// TransitionTimer — deploy/unload cycle timer (sizeof = 0x20; 8-aligned due to
// the leading double). Ctor FUN_0x004A50F0.
#ifndef GG_MATCH_LAYOUT_TRANSITIONTIMER_DEFINED
#define GG_MATCH_LAYOUT_TRANSITIONTIMER_DEFINED
struct TransitionTimer
{
    double        Rate1;         // +0x00
    CDTimerClass  ActionTimer;   // +0x08  (0xC)
    unsigned int  Rate2;         // +0x14
    unsigned char State1;        // +0x18  (bool)
    unsigned char State2;        // +0x19  (bool)
    unsigned char _pad_1A[6];    // +0x1A  (tail pad to the 8-byte size)
};
GG_STATIC_ASSERT(offsetof(TransitionTimer, ActionTimer) == 0x08);
GG_STATIC_ASSERT(offsetof(TransitionTimer, Rate2)       == 0x14);
GG_STATIC_ASSERT(sizeof(TransitionTimer)                == 0x20);
#endif

// DirStruct — 16-bit binary heading + 16-bit pad (sizeof = 4).
#ifndef GG_MATCH_LAYOUT_DIRSTRUCT_DEFINED
#define GG_MATCH_LAYOUT_DIRSTRUCT_DEFINED
struct DirStruct
{
    unsigned short Raw;       // +0x00
    unsigned short Padding;   // +0x02
};
GG_STATIC_ASSERT(sizeof(DirStruct) == 4);
#endif

// FacingClass — desired/current heading + rotation timer (sizeof = 0x18). Ctors
// FUN_0x004C91E0 / FUN_0x004C91C0.
#ifndef GG_MATCH_LAYOUT_FACINGCLASS_DEFINED
#define GG_MATCH_LAYOUT_FACINGCLASS_DEFINED
struct FacingClass
{
    DirStruct    DesiredFacing;   // +0x00
    DirStruct    StartFacing;     // +0x04
    CDTimerClass RotationTimer;   // +0x08  (0xC)
    DirStruct    ROT;             // +0x14
};
GG_STATIC_ASSERT(offsetof(FacingClass, RotationTimer) == 0x08);
GG_STATIC_ASSERT(sizeof(FacingClass)                  == 0x18);
#endif

// TurretControl — recoil travel parameters (sizeof = 0x10).
#ifndef GG_MATCH_LAYOUT_TURRETCONTROL_DEFINED
#define GG_MATCH_LAYOUT_TURRETCONTROL_DEFINED
struct TurretControl
{
    int Travel;          // +0x00
    int CompressFrames;  // +0x04
    int RecoverFrames;   // +0x08
    int HoldFrames;      // +0x0C
};
GG_STATIC_ASSERT(sizeof(TurretControl) == 0x10);
#endif

// RecoilData — per-barrel/turret recoil animation state (sizeof = 0x20).
#ifndef GG_MATCH_LAYOUT_RECOILDATA_DEFINED
#define GG_MATCH_LAYOUT_RECOILDATA_DEFINED
struct RecoilData
{
    TurretControl Turret;            // +0x00  (0x10)
    float         TravelPerFrame;    // +0x10
    float         TravelSoFar;       // +0x14
    unsigned int  State;             // +0x18  (RecoilState enum)
    int           TravelFramesLeft;  // +0x1C
};
GG_STATIC_ASSERT(offsetof(RecoilData, TravelPerFrame) == 0x10);
GG_STATIC_ASSERT(sizeof(RecoilData)                   == 0x20);
#endif

class PlanningTokenClass;

// TechnoClass  (0xF0..0x51F, sizeof = 0x520)
// Retail RTTI 0x817B58 establishes the class key; public access preserves this ABI view.
class TechnoClass : public RadioClass
{
public:
    // FUNCTION: GAMEMD 0x705D20 (decl; reloc) -- the planning token this unit is on.
    PlanningTokenClass* FUN_00705D20();
    // FUNCTION: GAMEMD 0x707CB0 (decl; reloc) -- kill the passengers (one
    // stack argument, the killer).
    void KillPassengers(TechnoClass* killer);

    FlashData          Flashing;                 // +0xF0  (8)
    StageClass         Animation;                // +0xF8  (0x1C)
    PassengersClass    Passengers;               // +0x114 (8)
    void*              Transporter;              // +0x11C TechnoClass*
    int                LastFireBulletFrame;      // +0x120 (ctor = -100)
    int                CurrentTurretNumber;      // +0x124 (ctor = -1)
    int                unknown_int_128;          // +0x128 (ctor = -1)
    void*              BehindAnim;               // +0x12C AnimClass*
    void*              DeployAnim;               // +0x130 AnimClass*
    unsigned char      InAir;                    // +0x134 (bool)
    unsigned char      align_135[3];             // +0x135
    int                CurrentWeaponNumber;      // +0x138
    int                CurrentRanking;           // +0x13C (Rank enum, ctor = -1)
    int                CurrentGattlingStage;     // +0x140
    int                GattlingValue;            // +0x144
    int                TurretAnimFrame;          // +0x148
    void*              InitialOwner;             // +0x14C HouseClass* (set late = param_1)
    VeterancyStruct    Veterancy;                // +0x150 (4; ctor FUN_0074FF30)
    unsigned int       align_154;                // +0x154 (aligns the double)
    double             ArmorMultiplier;          // +0x158 (ctor = 1.0)
    double             FirepowerMultiplier;      // +0x160 (ctor = 1.0)
    CDTimerClass       IdleActionTimer;          // +0x168 (0xC)
    CDTimerClass       RadarFlashTimer;          // +0x174 (0xC)
    CDTimerClass       TargetingTimer;           // +0x180 (0xC; TimeLeft ctor = 45)
    CDTimerClass       IronCurtainTimer;         // +0x18C (0xC)
    CDTimerClass       IronTintTimer;            // +0x198 (0xC)
    int                IronTintStage;            // +0x1A4 (ctor = 10)
    CDTimerClass       AirstrikeTimer;           // +0x1A8 (0xC)
    CDTimerClass       AirstrikeTintTimer;       // +0x1B4 (0xC)
    unsigned int       AirstrikeTintStage;       // +0x1C0
    int                ForceShielded;            // +0x1C4
    unsigned char      Deactivated;              // +0x1C8 (bool)
    unsigned char      align_1C9[3];             // +0x1C9
    void*              DrainTarget;              // +0x1CC TechnoClass*
    void*              DrainingMe;               // +0x1D0 TechnoClass*
    void*              DrainAnim;                // +0x1D4 AnimClass*
    unsigned char      Disguised;                // +0x1D8 (bool)
    unsigned char      align_1D9[3];             // +0x1D9
    unsigned int       DisguiseCreationFrame;    // +0x1DC
    CDTimerClass       InfantryBlinkTimer;       // +0x1E0 (0xC)
    CDTimerClass       DisguiseBlinkTimer;       // +0x1EC (0xC)
    unsigned char      UnlimboingInfantry;       // +0x1F8 (bool)
    unsigned char      align_1F9[3];             // +0x1F9
    CDTimerClass       ReloadTimer;              // +0x1FC (0xC)
    Point2D            RadarPosition;            // +0x208 (8)
    unsigned int       DisplayProductionTo;      // +0x210 (IndexBitfield<HouseClass*>)
    int                Group;                    // +0x214 (ctor = -1)
    void*              ArchiveTarget;            // +0x218 AbstractClass*
    void*              Owner;                    // +0x21C HouseClass* (ctor = param_1)
    int                CloakState;               // +0x220 (CloakState enum)
    StageClass         CloakProgress;            // +0x224 (0x1C)
    CDTimerClass       CloakDelayTimer;          // +0x240 (0xC)
    float              WarpFactor;               // +0x24C
    unsigned char      unknown_bool_250;         // +0x250 (bool)
    unsigned char      align_251[3];             // +0x251
    CoordStruct        LastSightCoords;          // +0x254 (0xC)
    int                LastSightRange;           // +0x260
    int                LastSightHeight;          // +0x264
    unsigned char      GapSuperCharged;          // +0x268 (bool)
    unsigned char      GeneratingGap;            // +0x269 (bool)
    unsigned char      align_26A[2];             // +0x26A
    int                GapRadius;                // +0x26C
    unsigned char      BeingWarpedOut;           // +0x270 (bool)
    unsigned char      WarpingOut;               // +0x271 (bool)
    unsigned char      unknown_bool_272;         // +0x272 (bool)
    unsigned char      unused_273;               // +0x273
    void*              TemporalImUsing;          // +0x274 TemporalClass*
    void*              TemporalTargetingMe;      // +0x278 TemporalClass*
    unsigned char      IsImmobilized;            // +0x27C (bool)
    unsigned char      align_27D[3];             // +0x27D
    unsigned int       unknown_280;              // +0x280
    int                ChronoLockRemaining;      // +0x284
    CoordStruct        ChronoDestCoords;         // +0x288 (0xC)
    void*              Airstrike;                // +0x294 AirstrikeClass*
    unsigned char      Berzerk;                  // +0x298 (bool)
    unsigned char      align_299[3];             // +0x299
    int                BerzerkDurationLeft;      // +0x29C
    unsigned int       SprayOffsetIndex;         // +0x2A0
    unsigned char      Uncrushable;              // +0x2A4 (bool)
    unsigned char      align_2A5[3];             // +0x2A5
    void*              DirectRockerLinkedUnit;   // +0x2A8 FootClass*
    void*              LocomotorTarget;          // +0x2AC FootClass*
    void*              LocomotorSource;          // +0x2B0 FootClass*
    void*              Target;                   // +0x2B4 AbstractClass*
    void*              LastTarget;               // +0x2B8 AbstractClass*
    void*              CaptureManager;           // +0x2BC CaptureManagerClass*
    void*              MindControlledBy;         // +0x2C0 TechnoClass*
    unsigned char      MindControlledByAUnit;    // +0x2C4 (bool)
    unsigned char      align_2C5[3];             // +0x2C5
    void*              MindControlRingAnim;      // +0x2C8 AnimClass*
    void*              MindControlledByHouse;    // +0x2CC HouseClass*
    void*              SpawnManager;             // +0x2D0 SpawnManagerClass*
    void*              SpawnOwner;               // +0x2D4 TechnoClass*
    void*              SlaveManager;             // +0x2D8 SlaveManagerClass*
    void*              SlaveOwner;               // +0x2DC TechnoClass*
    void*              OriginallyOwnedByHouse;   // +0x2E0 HouseClass*
    void*              BunkerLinkedItem;         // +0x2E4 TechnoClass*
    float              PitchAngle;               // +0x2E8
    CDTimerClass       RearmTimer;               // +0x2EC (0xC)
    int                ChargeTurretDelay;        // +0x2F8
    int                Ammo;                     // +0x2FC (ctor = -1)
    int                Value;                    // +0x300
    void*              FireParticleSystem;       // +0x304 ParticleSystemClass*
    void*              SparkParticleSystem;      // +0x308
    void*              NaturalParticleSystem;    // +0x30C
    void*              DamageParticleSystem;     // +0x310
    void*              RailgunParticleSystem;    // +0x314
    void*              unk1ParticleSystem;       // +0x318
    void*              unk2ParticleSystem;       // +0x31C
    void*              FiringParticleSystem;     // +0x320
    void*              Wave;                     // +0x324 WaveClass*
    float              AngleRotatedSideways;     // +0x328
    float              AngleRotatedForwards;     // +0x32C
    float              RockingSidewaysPerFrame;  // +0x330
    float              RockingForwardsPerFrame;  // +0x334
    int                HijackerInfantryType;     // +0x338 (ctor = -1)
    StorageClass       Tiberium;                 // +0x33C (0x10; ctor FUN_006C95E0)
    unsigned int       unknown_34C;              // +0x34C
    TransitionTimer    UnloadTimer;              // +0x350 (0x20; ctor FUN_004A50F0)
    FacingClass        BarrelFacing;             // +0x370 (0x18)
    FacingClass        PrimaryFacing;            // +0x388 (0x18)
    FacingClass        SecondaryFacing;          // +0x3A0 (0x18)
    int                CurrentBurstIndex;        // +0x3B8
    CDTimerClass       TargetLaserTimer;         // +0x3BC (0xC)
    short              unknown_short_3C8;        // +0x3C8
    unsigned short     unknown_3CA;              // +0x3CA
    unsigned char      CountedAsOwned;           // +0x3CC (bool)
    unsigned char      IsSinking;                // +0x3CD (bool)
    unsigned char      WasSinkingAlready;        // +0x3CE (bool)
    unsigned char      unknown_bool_3CF;         // +0x3CF (bool)
    unsigned char      IsUseless;                // +0x3D0 (bool)
    unsigned char      HasBeenAttacked;          // +0x3D1 (bool)
    unsigned char      Cloakable;                // +0x3D2 (bool)
    unsigned char      IsPrimaryFactory;         // +0x3D3 (bool)
    unsigned char      Spawned;                  // +0x3D4 (bool)
    unsigned char      IsInPlayfield;            // +0x3D5 (bool)
    unsigned char      align_3D6[2];             // +0x3D6
    RecoilData         TurretRecoil;             // +0x3D8 (0x20)
    RecoilData         BarrelRecoil;             // +0x3F8 (0x20)
    unsigned char      IsTether;                 // +0x418 (bool)
    unsigned char      IsAlternativeTether;      // +0x419 (bool)
    unsigned char      IsOwnedByCurrentPlayer;   // +0x41A (bool)
    unsigned char      DiscoveredByCurrentPlayer;// +0x41B (bool)
    unsigned char      DiscoveredByComputer;     // +0x41C (bool)
    unsigned char      unknown_bool_41D;         // +0x41D (bool)
    unsigned char      unknown_bool_41E;         // +0x41E (bool)
    unsigned char      unknown_bool_41F;         // +0x41F (bool)
    char               SightIncrease;            // +0x420
    unsigned char      RecruitableA;             // +0x421 (bool, ctor = 1)
    unsigned char      RecruitableB;             // +0x422 (bool, ctor = 1)
    unsigned char      IsRadarTracked;           // +0x423 (bool)
    unsigned char      IsOnCarryall;             // +0x424 (bool)
    unsigned char      IsCrashing;               // +0x425 (bool)
    unsigned char      WasCrashingAlready;       // +0x426 (bool)
    unsigned char      IsBeingManipulated;       // +0x427 (bool)
    void*              BeingManipulatedBy;       // +0x428 TechnoClass*
    void*              ChronoWarpedByHouse;      // +0x42C HouseClass*
    unsigned char      unknown_bool_430;         // +0x430 (bool)
    unsigned char      IsMouseHovering;          // +0x431 (bool)
    unsigned char      ShouldBeReselectOnUnlimbo;// +0x432 (bool)
    unsigned char      align_433;                // +0x433
    void*              OldTeam;                  // +0x434 TeamClass*
    unsigned char      CountedAsOwnedSpecial;    // +0x438 (bool)
    unsigned char      Absorbed;                 // +0x439 (bool)
    unsigned char      unknown_bool_43A;         // +0x43A (bool)
    unsigned char      align_43B;                // +0x43B
    unsigned int       unknown_43C;              // +0x43C
    DynamicVectorClassLayout CurrentTargetThreatValues;// +0x440 (0x18; vptr 0x7E4E78)
    DynamicVectorClassLayout CurrentTargets;           // +0x458 (0x18; vptr 0x7E91EC)
    DynamicVectorClassLayout AttackedTargets;          // +0x470 (0x18; vptr 0x7E91EC)
    AudioController    TurretRotateSoundController; // +0x488 (0x14; ctor FUN_00405BE0)
    int                IsTurretRotateSoundPlaying;  // +0x49C (BOOL, ctor = 1)
    int                TurretIsRotating;            // +0x4A0 (BOOL)
    AudioController    GattlingSoundController;      // +0x4A4 (0x14; ctor FUN_00405BE0)
    unsigned char      IsGattlingSoundPlaying;       // +0x4B8 (bool)
    unsigned char      align_4B9[3];                 // +0x4B9
    unsigned int       unknown_4BC;                  // +0x4BC
    AudioController    UnusedGattlingSoundController; // +0x4C0 (0x14; ctor FUN_00405BE0)
    unsigned char      IsUnusedGattlingSoundPlaying; // +0x4D4 (bool)
    unsigned char      align_4D5[3];                 // +0x4D5
    unsigned int       unknown_4D8;                  // +0x4D8
    AudioController    QueuedVoiceSoundController;    // +0x4DC (0x14; ctor FUN_00405BE0)
    unsigned int       QueuedVoiceIndex;             // +0x4F0 (ctor = -1)
    unsigned int       unknown_4F4;                  // +0x4F4 (ctor = -1)
    unsigned char      unknown_bool_4F8;             // +0x4F8 (bool)
    unsigned char      align_4F9[3];                 // +0x4F9
    unsigned int       unknown_4FC;                  // +0x4FC
    void*              QueueUpToEnter;               // +0x500 TechnoClass*
    unsigned int       EMPLockRemaining;             // +0x504
    unsigned int       ThreatPosed;                  // +0x508
    unsigned int       ShouldLoseTargetNow;          // +0x50C
    void*              FiringRadBeam;                // +0x510 RadBeam*
    void*              PlanningToken;                // +0x514 PlanningTokenClass*
    void*              Disguise;                     // +0x518 ObjectTypeClass*
    void*              DisguisedAsHouse;             // +0x51C HouseClass*
};

GG_STATIC_ASSERT(offsetof(TechnoClass, Flashing)                 == 0xF0);
GG_STATIC_ASSERT(offsetof(TechnoClass, Animation)                == 0xF8);
GG_STATIC_ASSERT(offsetof(TechnoClass, Passengers)               == 0x114);
GG_STATIC_ASSERT(offsetof(TechnoClass, Transporter)              == 0x11C);
GG_STATIC_ASSERT(offsetof(TechnoClass, InitialOwner)             == 0x14C);
GG_STATIC_ASSERT(offsetof(TechnoClass, Veterancy)                == 0x150);
GG_STATIC_ASSERT(offsetof(TechnoClass, ArmorMultiplier)          == 0x158);
GG_STATIC_ASSERT(offsetof(TechnoClass, TargetingTimer)           == 0x180);
GG_STATIC_ASSERT(offsetof(TechnoClass, IronTintStage)            == 0x1A4);
GG_STATIC_ASSERT(offsetof(TechnoClass, ReloadTimer)              == 0x1FC);
GG_STATIC_ASSERT(offsetof(TechnoClass, RadarPosition)            == 0x208);
GG_STATIC_ASSERT(offsetof(TechnoClass, Group)                    == 0x214);
GG_STATIC_ASSERT(offsetof(TechnoClass, Owner)                    == 0x21C);
GG_STATIC_ASSERT(offsetof(TechnoClass, CloakState)               == 0x220);
GG_STATIC_ASSERT(offsetof(TechnoClass, CloakProgress)            == 0x224);
GG_STATIC_ASSERT(offsetof(TechnoClass, LastSightCoords)          == 0x254);
GG_STATIC_ASSERT(offsetof(TechnoClass, Target)                   == 0x2B4);
GG_STATIC_ASSERT(offsetof(TechnoClass, MindControlledBy)         == 0x2C0);
GG_STATIC_ASSERT(offsetof(TechnoClass, SpawnManager)             == 0x2D0);
GG_STATIC_ASSERT(offsetof(TechnoClass, RearmTimer)               == 0x2EC);
GG_STATIC_ASSERT(offsetof(TechnoClass, Ammo)                     == 0x2FC);
GG_STATIC_ASSERT(offsetof(TechnoClass, FireParticleSystem)       == 0x304);
GG_STATIC_ASSERT(offsetof(TechnoClass, HijackerInfantryType)     == 0x338);
GG_STATIC_ASSERT(offsetof(TechnoClass, Tiberium)                 == 0x33C);
GG_STATIC_ASSERT(offsetof(TechnoClass, UnloadTimer)              == 0x350);
GG_STATIC_ASSERT(offsetof(TechnoClass, BarrelFacing)             == 0x370);
GG_STATIC_ASSERT(offsetof(TechnoClass, PrimaryFacing)            == 0x388);
GG_STATIC_ASSERT(offsetof(TechnoClass, SecondaryFacing)          == 0x3A0);
GG_STATIC_ASSERT(offsetof(TechnoClass, TargetLaserTimer)         == 0x3BC);
GG_STATIC_ASSERT(offsetof(TechnoClass, TurretRecoil)             == 0x3D8);
GG_STATIC_ASSERT(offsetof(TechnoClass, BarrelRecoil)             == 0x3F8);
GG_STATIC_ASSERT(offsetof(TechnoClass, CurrentTargetThreatValues)== 0x440);
GG_STATIC_ASSERT(offsetof(TechnoClass, CurrentTargets)           == 0x458);
GG_STATIC_ASSERT(offsetof(TechnoClass, AttackedTargets)          == 0x470);
GG_STATIC_ASSERT(offsetof(TechnoClass, TurretRotateSoundController) == 0x488);
GG_STATIC_ASSERT(offsetof(TechnoClass, GattlingSoundController)  == 0x4A4);
GG_STATIC_ASSERT(offsetof(TechnoClass, UnusedGattlingSoundController) == 0x4C0);
GG_STATIC_ASSERT(offsetof(TechnoClass, QueuedVoiceSoundController) == 0x4DC);
GG_STATIC_ASSERT(offsetof(TechnoClass, QueueUpToEnter)           == 0x500);
GG_STATIC_ASSERT(offsetof(TechnoClass, DisguisedAsHouse)         == 0x51C);
GG_STATIC_ASSERT(sizeof(TechnoClass)                             == 0x520);

#endif  // GG_MATCH_LAYOUT_TECHNO_CLASS_H
