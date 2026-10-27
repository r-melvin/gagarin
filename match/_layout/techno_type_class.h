// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: ctor FUN_0x00710AF0,
//   "TechnoTypeClass (0x294-0xDF7) - BINARY-ACCURATE"), cross-checked vs YRpp
//   Verified by all 12 YRpp pad anchors landing exactly
//   (0x2FC, 0x35C, 0x398, 0x39C, 0x3C0, 0x3C4, 0x6EF, 0x70E, 0xCB4, 0xCC8,
//   0xCC9, 0xDF4) plus ctor ground-truth spot-checks (WalkRate@0x294=1,
//   VeteranAbilities@0x29C, Locomotor@0x34C, Cost@0x610, CameoFile@0x6D6,
//   Palette@0xDF0).
//
// TechnoTypeClass - base blueprint for every "techno" object type (units,
// infantry, aircraft, buildings). Largest type struct in the family (329
// members). Derives ObjectTypeClass (the AbstractClass COM spine + type
// strings + art/voxel fields) at offset 0, and adds the combat / movement /
// voice / weapon / cameo blueprint fields from 0x294. Leaf type classes
// (UnitTypeClass, InfantryTypeClass, AircraftTypeClass, BuildingTypeClass)
// start at 0xDF8.
//
// Pointer / TypeList / WeaponStruct / *Class* members read as int/undefined4 in
// decomp are 64-bit truncation sites; modelled here as real 4-byte pointers /
// exact-size structs so every downstream offset stays byte-exact.
#ifndef GG_MATCH_LAYOUT_TECHNO_TYPE_CLASS_H
#define GG_MATCH_LAYOUT_TECHNO_TYPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "object_type_class.h"   // ObjectTypeClass (sizeof 0x294), AbilitiesStruct
#include "vector_class.h"        // DynamicVectorClassLayout (sizeof 0x18)
#include "../core/type_list.h"  // RTTI-backed TypeList<T> hierarchy and typed fields

// ---------------------------------------------------------------------------
// Local component structs (sizes proven by the oracle doc).
// ---------------------------------------------------------------------------

// CoordStruct - lepton 3-space coordinate (size = 0xC); now provided, guarded,
// by object_type_class.h.

// _GUID - Locomotor class id (size = 0x10).
struct GUIDStruct
{
    unsigned long  Data1;     // +0x00
    unsigned short Data2;     // +0x04
    unsigned short Data3;     // +0x06
    unsigned char  Data4[8];  // +0x08
};
GG_STATIC_ASSERT(sizeof(GUIDStruct) == 0x10);

// TypeList<T> - DynamicVectorClass (0x18) + a trailing unknown_18 dword (0x1C).
struct TypeListLayout
{
    DynamicVectorClassLayout Vector;     // +0x00 (0x18)
    int                unknown_18; // +0x18
};
GG_STATIC_ASSERT(sizeof(TypeListLayout) == 0x1C);

// WeaponStruct - weapon slot (WeaponType ptr + FLH + flags); size = 0x1C.
// Internal members not member-resolved in the oracle; exact-size byte block.
class WeaponTypeClass;
struct WeaponStruct
{
    WeaponTypeClass* WeaponType;   // +0x00
    unsigned char    unknown_04[0x18];
};
GG_STATIC_ASSERT(sizeof(WeaponStruct) == 0x1C);

// TurretControl - turret/barrel animation control block (size = 0x10).
// Shares techno_class.h's guard; whichever header comes first defines it.
#ifndef GG_MATCH_LAYOUT_TURRETCONTROL_DEFINED
#define GG_MATCH_LAYOUT_TURRETCONTROL_DEFINED
struct TurretControl
{
    unsigned char _raw[0x10];
};
#endif
GG_STATIC_ASSERT(sizeof(TurretControl) == 0x10);

// Opaque forward decls for the truncation-site pointer members (4 bytes each).
struct SHPStruct;
class BuildingTypeClass;
class UnitTypeClass;
class InfantryTypeClass;
class AircraftTypeClass;
class AnimTypeClass;
class VoxelAnimTypeClass;
class ParticleSystemTypeClass;
class WeaponTypeClass;
struct ColorScheme;
class HouseClass;
struct CellStruct;

// TypeList specializations used by TechnoTypeClass fields. Aliases keep VC6
// offsetof expressions simple and provide actual-type layout anchors.
typedef TypeList<int> TechnoTypeListInt;
typedef TypeList<const BuildingTypeClass*> TechnoTypeListBuilding;
typedef TypeList<const VoxelAnimTypeClass*> TechnoTypeListVoxelAnim;
typedef TypeList<const AnimTypeClass*> TechnoTypeListAnim;
typedef TypeList<const ParticleSystemTypeClass*> TechnoTypeListParticleSystem;

// ---------------------------------------------------------------------------
// TechnoTypeClass  (0x294..0xDF7, sizeof = 0xDF8)
// ---------------------------------------------------------------------------
class TechnoTypeClass : public ObjectTypeClass
{
public:
    // Declaration: GAMEMD 0x7170A0, COM slot7; also AircraftType7E2868 slot7.
    virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* size);

    // FUNCTION: GAMEMD 0x710AF0 (declaration; constructor) -- RET 8.
    TechnoTypeClass(const char* id, int speedType);
    // FUNCTION: GAMEMD 0x711840 (declaration; no-initialisation constructor)
    TechnoTypeClass(const AbstractNoInit& noInit);
    // FUNCTION: GAMEMD 0x711AE0 (declaration; destructor)
    ~TechnoTypeClass();
    // Native711EC0 overrides ObjectType slot28; full EAX integer, no args.
    virtual int vf_28();
    // FUNCTION: GAMEMD 0x716290; overrides ObjectType slot29.
    virtual int vf_29();
    // FUNCTION: GAMEMD 0x711F00; slot 33 consumes the House owner pointer.
    virtual int vf_33(HouseClass* owner);
    virtual int vf_34();                                          // 34 0x711EE0
    virtual HRESULT __stdcall Load(IStream* pStm);                        // 5   0x7162F0
    // Declaration: GAMEMD 0x716DC0, overrides ObjectTypeClass COM slot 6.
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL clearDirty);
    virtual void vf_13(Obj_004A1D30* crc);                                // 13  0x7171A0
    virtual bool vf_25(CCINIClass* ini);                                  // 25  0x712170
    // FUNCTION: GAMEMD 0x717880 (decl; reloc) -- non-virtual; ECX = the type.
    bool FUN_00717880();
    // FUNCTION: GAMEMD 0x7177C0 (decl; reloc) -- the weapon in slot `index`.
    WeaponStruct* GetWeapon(int index);
    // FUNCTION: GAMEMD 0x7177E0 (decl; reloc) -- the elite weapon in slot `index`.
    WeaponStruct* GetEliteWeapon(int index);
    virtual bool vf_40();                                                 // 40
    virtual bool vf_41();                                                 // 41
    // Slots 42-47, introduced by TechnoTypeClass (48 slots in all; retail table 0x7F4ED8).
    // Names are placeholders; argument counts come from RET n, return types are not recovered.
    virtual bool vf_42(CellStruct* cell, HouseClass* owner);       // 42 0x716150; BuildingClass 0x449440 passes the cell and its owner, tests AL
    virtual int vf_43(); // 43 0x711EB0; EAX summed at caller0x688793
    virtual int vf_44();                                           // 44 0x7120D0
    // Native712120 returns a dword; caller6F4D14 compares full EAX signed.
    virtual int vf_45();                                           // 45 0x712120
    virtual void vf_46(int a1, int a2);                            // 46 0x711F60
    // Native717800 returns field618 or the fallback dword in EAX; Process4CCB81
    // stores it whole and MoveTo4CCE6C adds it as an integer.
    virtual int vf_47();                                           // 47 0x717800

    int             WalkRate;                       // +0x294
    int             IdleRate;                       // +0x298
    AbilitiesStruct VeteranAbilities;               // +0x29C (0x12)
    AbilitiesStruct EliteAbilities;                 // +0x2AE (0x12)
    double          SpecialThreatValue;             // +0x2C0
    double          MyEffectivenessCoefficient;     // +0x2C8
    double          TargetEffectivenessCoefficient; // +0x2D0
    double          TargetSpecialThreatCoefficient; // +0x2D8
    double          TargetStrengthCoefficient;      // +0x2E0
    double          TargetDistanceCoefficient;      // +0x2E8
    double          ThreatAvoidanceCoefficient;     // +0x2F0
    int             SlowdownDistance;               // +0x2F8
    unsigned char   align_2FC[4];                   // +0x2FC
    double          DecelerationFactor;             // +0x300
    double          AccelerationFactor;             // +0x308
    int             CloakingSpeed;                  // +0x310
    TypeList<const VoxelAnimTypeClass*> DebrisTypes;                    // +0x314
    TypeList<int> DebrisMaximums;                 // +0x330 (TypeList<int>)
    GUIDStruct      Locomotor;                      // +0x34C (0x10)
    unsigned char   align_35C[4];                   // +0x35C
    double          VoxelScaleX;                    // +0x360
    double          VoxelScaleY;                    // +0x368
    double          Weight;                         // +0x370
    double          PhysicalSize;                   // +0x378
    double          Size;                           // +0x380
    double          SizeLimit;                      // +0x388
    bool            HoverAttack;                    // +0x390
    unsigned char   _pad_391[3];                    // +0x391
    int             VHPScan;                        // +0x394
    int             unknown_int_398;                // +0x398
    unsigned char   align_39C[4];                   // +0x39C
    double          RollAngle;                      // +0x3A0
    double          PitchSpeed;                     // +0x3A8
    double          PitchAngle;                     // +0x3B0
    int             BuildLimit;                     // +0x3B8
    int             Category;                       // +0x3BC (enum)
    unsigned long   unknown_3C0;                    // +0x3C0 (DWORD)
    unsigned char   align_3C4[4];                   // +0x3C4
    double          DeployTime;                     // +0x3C8
    int             FireAngle;                      // +0x3D0
    int             PipScale;                       // +0x3D4 (enum)
    bool            PipsDrawForAll;                 // +0x3D8
    unsigned char   _pad_3D9[3];                    // +0x3D9
    int             LeptonMindControlOffset;        // +0x3DC
    int             PixelSelectionBracketDelta;     // +0x3E0
    int             PipWrap;                        // +0x3E4
    TypeList<const BuildingTypeClass*> Dock;                           // +0x3E8
    BuildingTypeClass* DeploysInto;                 // +0x404
    UnitTypeClass*  UndeploysInto;                  // +0x408
    UnitTypeClass*  PowersUnit;                     // +0x40C
    bool            PoweredUnit;                    // +0x410
    unsigned char   _pad_411[3];                    // +0x411
    TypeList<int> VoiceSelect;                    // +0x414
    TypeList<int> VoiceSelectEnslaved;            // +0x430
    TypeList<int> VoiceSelectDeactivated;         // +0x44C
    TypeList<int> VoiceMove;                      // +0x468
    TypeList<int> VoiceAttack;                    // +0x484
    TypeList<int> VoiceSpecialAttack;             // +0x4A0
    TypeList<int> VoiceDie;                       // +0x4BC
    TypeList<int> VoiceFeedback;                  // +0x4D8
    TypeList<int> MoveSound;                      // +0x4F4
    TypeList<int> DieSound;                       // +0x510
    int             AuxSound1;                      // +0x52C
    int             AuxSound2;                      // +0x530
    int             CreateSound;                    // +0x534
    int             DamageSound;                    // +0x538
    int             ImpactWaterSound;               // +0x53C
    int             ImpactLandSound;                // +0x540
    int             CrashingSound;                  // +0x544
    int             SinkingSound;                   // +0x548
    int             VoiceFalling;                   // +0x54C
    int             VoiceCrashing;                  // +0x550
    int             VoiceSinking;                   // +0x554
    int             VoiceEnter;                     // +0x558
    int             VoiceCapture;                   // +0x55C
    int             TurretRotateSound;              // +0x560
    int             EnterTransportSound;            // +0x564
    int             LeaveTransportSound;            // +0x568
    int             DeploySound;                    // +0x56C
    int             UndeploySound;                  // +0x570
    int             ChronoInSound;                  // +0x574
    int             ChronoOutSound;                 // +0x578
    int             VoiceHarvest;                   // +0x57C
    int             VoicePrimaryWeaponAttack;       // +0x580
    int             VoicePrimaryEliteWeaponAttack;  // +0x584
    int             VoiceSecondaryWeaponAttack;     // +0x588
    int             VoiceSecondaryEliteWeaponAttack;// +0x58C
    int             VoiceDeploy;                    // +0x590
    int             VoiceUndeploy;                  // +0x594
    int             EnterGrinderSound;              // +0x598
    int             LeaveGrinderSound;              // +0x59C
    int             EnterBioReactorSound;           // +0x5A0
    int             LeaveBioReactorSound;           // +0x5A4
    int             ActivateSound;                  // +0x5A8
    int             DeactivateSound;                // +0x5AC
    int             MindClearedSound;               // +0x5B0
    int             MovementZone;                   // +0x5B4 (enum)
    int             GuardRange;                     // +0x5B8
    int             MaxDebris;                      // +0x5BC
    int             MinDebris;                      // +0x5C0
    TypeList<const AnimTypeClass*> DebrisAnims;                    // +0x5C4
    int             Passengers;                     // +0x5E0
    bool            OpenTopped;                     // +0x5E4
    unsigned char   _pad_5E5[3];                    // +0x5E5
    int             Sight;                          // +0x5E8
    bool            ResourceGatherer;               // +0x5EC
    bool            ResourceDestination;            // +0x5ED
    bool            RevealToAll;                    // +0x5EE
    bool            Drainable;                      // +0x5EF
    int             SensorsSight;                   // +0x5F0
    int             DetectDisguiseRange;            // +0x5F4
    int             BombSight;                      // +0x5F8
    int             LeadershipRating;               // +0x5FC
    int             NavalTargeting;                 // +0x600 (enum)
    int             LandTargeting;                  // +0x604 (enum)
    float           BuildTimeMultiplier;            // +0x608
    int             MindControlRingOffset;          // +0x60C
    int             Cost;                           // +0x610
    int             Soylent;                        // +0x614
    int             FlightLevel;                    // +0x618
    int             AirstrikeTeam;                  // +0x61C
    int             EliteAirstrikeTeam;             // +0x620
    AircraftTypeClass* AirstrikeTeamType;           // +0x624
    AircraftTypeClass* EliteAirstrikeTeamType;      // +0x628
    int             AirstrikeRechargeTime;          // +0x62C
    int             EliteAirstrikeRechargeTime;     // +0x630
    int             TechLevel;                      // +0x634
    TypeList<int> Prerequisite;                   // +0x638 (TypeList<int>)
    TypeList<int> PrerequisiteOverride;           // +0x654 (TypeList<int>)
    int             ThreatPosed;                    // +0x670
    int             Points;                         // +0x674
    int             Speed;                          // +0x678
    int             SpeedType;                      // +0x67C (enum)
    int             InitialAmmo;                    // +0x680
    int             Ammo;                           // +0x684
    int             IFVMode;                        // +0x688
    int             AirRangeBonus;                  // +0x68C
    bool            BerserkFriendly;                // +0x690
    bool            SprayAttack;                    // +0x691
    bool            Pushy;                          // +0x692
    bool            Natural;                        // +0x693
    bool            Unnatural;                      // +0x694
    bool            CloseRange;                     // +0x695
    unsigned char   _pad_696[2];                    // +0x696
    int             Reload;                         // +0x698
    int             EmptyReload;                    // +0x69C
    int             ReloadIncrement;                // +0x6A0
    int             RadialFireSegments;             // +0x6A4
    int             DeployFireWeapon;               // +0x6A8
    bool            DeployFire;                     // +0x6AC
    bool            DeployToLand;                   // +0x6AD
    bool            MobileFire;                     // +0x6AE
    bool            OpportunityFire;                // +0x6AF
    bool            DistributedFire;                // +0x6B0
    bool            DamageReducesReadiness;         // +0x6B1
    unsigned char   _pad_6B2[2];                    // +0x6B2
    int             ReadinessReductionMultiplier;   // +0x6B4
    UnitTypeClass*  UnloadingClass;                 // +0x6B8
    AnimTypeClass*  DeployingAnim;                  // +0x6BC
    bool            AttackFriendlies;               // +0x6C0
    bool            AttackCursorOnFriendlies;       // +0x6C1
    unsigned char   _pad_6C2[2];                    // +0x6C2
    int             UndeployDelay;                  // +0x6C4
    bool            PreventAttackMove;              // +0x6C8
    unsigned char   _pad_6C9[3];                    // +0x6C9
    unsigned long   OwnerFlags;                     // +0x6CC (DWORD)
    int             AIBasePlanningSide;             // +0x6D0
    bool            StupidHunt;                     // +0x6D4
    bool            AllowedToStartInMultiplayer;    // +0x6D5
    char            CameoFile[0x19];                // +0x6D6 (0x6D6..0x6EE)
    unsigned char   align_6EF[1];                   // +0x6EF
    SHPStruct*      Cameo;                          // +0x6F0
    bool            CameoAllocated;                 // +0x6F4
    char            AltCameoFile[0x19];             // +0x6F5 (0x6F5..0x70D)
    unsigned char   align_70E[2];                   // +0x70E
    SHPStruct*      AltCameo;                       // +0x710
    bool            AltCameoAllocated;              // +0x714
    unsigned char   _pad_715[3];                    // +0x715
    int             RotCount;                       // +0x718
    int             ROT;                            // +0x71C
    int             TurretOffset;                   // +0x720
    bool            CanBeHidden;                    // +0x724
    unsigned char   _pad_725[3];                    // +0x725
    int             Points2;                        // +0x728
    TypeList<const AnimTypeClass*> Explosion;                      // +0x72C
    TypeList<const AnimTypeClass*> DestroyAnim;                    // +0x748
    ParticleSystemTypeClass* NaturalParticleSystem; // +0x764
    CoordStruct     NaturalParticleSystemLocation;  // +0x768 (0xC)
    ParticleSystemTypeClass* RefinerySmokeParticleSystem; // +0x774
    TypeList<const ParticleSystemTypeClass*> DamageParticleSystems;          // +0x778
    TypeList<const ParticleSystemTypeClass*> DestroyParticleSystems;         // +0x794
    CoordStruct     DamageSmokeOffset;              // +0x7B0 (0xC)
    bool            DamSmkOffScrnRel;               // +0x7BC
    unsigned char   _pad_7BD[3];                    // +0x7BD
    CoordStruct     DestroySmokeOffset;             // +0x7C0 (0xC)
    CoordStruct     RefinerySmokeOffsetOne;         // +0x7CC (0xC)
    CoordStruct     RefinerySmokeOffsetTwo;         // +0x7D8 (0xC)
    CoordStruct     RefinerySmokeOffsetThree;       // +0x7E4 (0xC)
    CoordStruct     RefinerySmokeOffsetFour;        // +0x7F0 (0xC)
    int             ShadowIndex;                    // +0x7FC
    int             Storage;                        // +0x800
    bool            TurretNotExportedOnGround;      // +0x804
    bool            Gunner;                         // +0x805
    bool            HasTurretTooltips;              // +0x806
    unsigned char   _pad_807[1];                    // +0x807
    int             TurretCount;                    // +0x808
    int             WeaponCount;                    // +0x80C
    bool            IsChargeTurret;                 // +0x810
    unsigned char   _pad_811[3];                    // +0x811
    int             TurretWeapon[18];               // +0x814 (0x48)
    CoordStruct     AlternativeFLH[5];              // +0x85C (0x3C)
    WeaponStruct    Weapon[18];                     // +0x898 (0x1F8)
    bool            ClearAllWeapons;                // +0xA90
    unsigned char   _pad_A91[3];                    // +0xA91
    WeaponStruct    EliteWeapon[18];                // +0xA94 (0x1F8)
    // 23 x bool: TypeImmune .. TurretRecoil (0xC8C..0xCA2), names collapsed in
    // the oracle; exact-size byte block keeps downstream offsets byte-exact.
    bool            bools_C8C[23];                  // +0xC8C (0xC8C..0xCA2)
    unsigned char   _pad_CA3[1];                    // +0xCA3
    TurretControl   TurretAnimData;                 // +0xCA4 (0x10)
    bool            unknown_bool_CB4;               // +0xCB4
    unsigned char   _pad_CB5[3];                    // +0xCB5
    TurretControl   BarrelAnimData;                 // +0xCB8 (0x10)
    bool            unknown_bool_CC8;               // +0xCC8
    unsigned char   align_CC9[3];                   // +0xCC9 (CC9/CCA/CCB)
    bool            Repairable;                     // +0xCCC
    bool            Crewed;                         // +0xCCD
    bool            Naval;                          // +0xCCE
    bool            Remapable;                      // +0xCCF
    bool            Cloakable;                      // +0xCD0
    bool            GapGenerator;                   // +0xCD1
    char            GapRadiusInCells;               // +0xCD2
    char            SuperGapRadiusInCells;          // +0xCD3
    bool            Teleporter;                     // +0xCD4
    bool            IsGattling;                     // +0xCD5
    unsigned char   _pad_CD6[2];                    // +0xCD6
    int             WeaponStages;                   // +0xCD8
    int             WeaponStage[6];                 // +0xCDC (0x18)
    int             EliteStage[6];                  // +0xCF4 (0x18)
    int             RateUp;                         // +0xD0C
    int             RateDown;                       // +0xD10
    bool            SelfHealing;                    // +0xD14
    bool            Explodes;                       // +0xD15
    unsigned char   _pad_D16[2];                    // +0xD16
    WeaponTypeClass* DeathWeapon;                   // +0xD18
    float           DeathWeaponDamageModifier;      // +0xD1C
    // 31 x bool: NoAutoFire .. RejoinTeamIfLimboed, Slaved (0xD20..0xD3E).
    bool            bools_D20[31];                  // +0xD20 (0xD20..0xD3E)
    unsigned char   _pad_D3F[1];                    // +0xD3F
    InfantryTypeClass* Enslaves;                    // +0xD40
    int             SlavesNumber;                   // +0xD44
    int             SlaveRegenRate;                 // +0xD48
    int             SlaveReloadRate;                // +0xD4C
    int             OpenTransportWeapon;            // +0xD50
    bool            Spawned;                        // +0xD54
    unsigned char   _pad_D55[3];                    // +0xD55
    AircraftTypeClass* Spawns;                      // +0xD58
    int             SpawnsNumber;                   // +0xD5C
    int             SpawnRegenRate;                 // +0xD60
    int             SpawnReloadRate;                // +0xD64
    bool            MissileSpawn;                   // +0xD68
    bool            Underwater;                     // +0xD69
    bool            BalloonHover;                   // +0xD6A
    unsigned char   _pad_D6B[1];                    // +0xD6B
    int             SuppressionThreshold;           // +0xD6C
    int             JumpjetTurnRate;                // +0xD70
    int             JumpjetSpeed;                   // +0xD74
    float           JumpjetClimb;                   // +0xD78
    float           JumpjetCrash;                   // +0xD7C
    int             JumpjetHeight;                  // +0xD80
    float           JumpjetAccel;                   // +0xD84
    float           JumpjetWobbles;                 // +0xD88
    bool            JumpjetNoWobbles;               // +0xD8C
    unsigned char   _pad_D8D[3];                    // +0xD8D
    int             JumpjetDeviation;               // +0xD90
    // 10 x bool: JumpJet .. RequiresStolenAlliedTech (0xD94..0xD9D).
    bool            bools_D94[10];                  // +0xD94 (0xD94..0xD9D)
    unsigned char   _pad_D9E[2];                    // +0xD9E
    unsigned long   RequiredHouses;                 // +0xDA0 (DWORD)
    unsigned long   ForbiddenHouses;                // +0xDA4 (DWORD)
    unsigned long   SecretHouses;                   // +0xDA8 (DWORD)
    bool            UseBuffer;                       // +0xDAC
    unsigned char   _pad_DAD[3];                    // +0xDAD
    CoordStruct     SecondSpawnOffset;              // +0xDB0 (0xC)
    bool            IsSelectableCombatant;          // +0xDBC
    bool            Accelerates;                    // +0xDBD
    bool            DisableVoxelCache;              // +0xDBE
    bool            DisableShadowCache;             // +0xDBF
    int             ZFudgeCliff;                    // +0xDC0
    int             ZFudgeColumn;                   // +0xDC4
    int             ZFudgeTunnel;                   // +0xDC8
    int             ZFudgeBridge;                   // +0xDCC
    char            PaletteFile[0x20];              // +0xDD0 (0xDD0..0xDEF)
    DynamicVectorClassLayout* Palette;                    // +0xDF0 (DynamicVectorClass<ColorScheme*>*)
    unsigned long   align_DF4;                      // +0xDF4 (DWORD)
};

// --- Representative offset asserts (spanning the struct) + final sizeof ------
// Native constructor byte stores: 0x710FE4 (+0x5E4), 0x711363 (+0x805).
// FootClass::RemoveFirstPassenger reads the Gunner byte at 0x4DE72E.
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, OpenTopped) == 0x5E4);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->OpenTopped) == 1);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Gunner) == 0x805);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->Gunner) == 1);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, TechLevel) == 0x634); // 0x6886B0 accesses
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, OwnerFlags) == 0x6CC); // 0x6886B0 accesses
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, AllowedToStartInMultiplayer) == 0x6D5); // 0x6886B0 accesses
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, WalkRate)          == 0x294);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, VeteranAbilities)  == 0x29C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, SpecialThreatValue)== 0x2C0);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, align_2FC)         == 0x2FC);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Locomotor)         == 0x34C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, align_35C)         == 0x35C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, unknown_int_398)   == 0x398);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, align_39C)         == 0x39C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, unknown_3C0)       == 0x3C0);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, align_3C4)         == 0x3C4);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, AuxSound1)         == 0x52C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, MindClearedSound)  == 0x5B0);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Cost)              == 0x610);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Reload)            == 0x698);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, CameoFile)         == 0x6D6);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, align_6EF)         == 0x6EF);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, align_70E)         == 0x70E);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Weapon)            == 0x898);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, EliteWeapon)       == 0xA94);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, bools_C8C)         == 0xC8C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, TurretAnimData)    == 0xCA4);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, unknown_bool_CB4)  == 0xCB4);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, BarrelAnimData)    == 0xCB8);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, unknown_bool_CC8)  == 0xCC8);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, align_CC9)         == 0xCC9);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, WeaponStage)       == 0xCDC);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, bools_D20)         == 0xD20);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Enslaves)          == 0xD40);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, SecondSpawnOffset) == 0xDB0);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, PaletteFile)       == 0xDD0);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Palette)           == 0xDF0);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, align_DF4)         == 0xDF4);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, FlightLevel) == 0x618);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, PreventAttackMove) == 0x6C8);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, PipScale) == 0x3D4);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->PipScale) == 4);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Passengers) == 0x5E0);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->Passengers) == 4);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Ammo) == 0x684);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->Ammo) == 4);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Weapon) +
                 offsetof(WeaponStruct, WeaponType) == 0x898);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->Weapon[0].WeaponType) == 4);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Weapon) +
                 offsetof(WeaponStruct, WeaponType) +
                 0xA4 == 0x93C); // WeaponTypeClass::Damage is asserted in its canonical header.
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, DebrisTypes) == 0x314);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->DebrisTypes) == 0x1C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, DebrisTypes) +
                 offsetof(TechnoTypeListVoxelAnim, Count) == 0x324);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, DebrisMaximums) == 0x330);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->DebrisMaximums) == 0x1C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, DebrisMaximums) +
                 offsetof(TechnoTypeListInt, Count) == 0x340);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Dock) == 0x3E8);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->Dock) == 0x1C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Dock) +
                 offsetof(TechnoTypeListBuilding, Count) == 0x3F8);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, VoiceSelect) == 0x414);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->VoiceSelect) == 0x1C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, VoiceSelect) +
                 offsetof(TechnoTypeListInt, Count) == 0x424);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, VoiceSelectEnslaved) == 0x430);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->VoiceSelectEnslaved) == 0x1C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, VoiceSelectEnslaved) +
                 offsetof(TechnoTypeListInt, Count) == 0x440);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, VoiceSelectDeactivated) == 0x44C);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->VoiceSelectDeactivated) == 0x1C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, VoiceSelectDeactivated) +
                 offsetof(TechnoTypeListInt, Count) == 0x45C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, VoiceMove) == 0x468);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->VoiceMove) == 0x1C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, VoiceMove) +
                 offsetof(TechnoTypeListInt, Count) == 0x478);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, VoiceAttack) == 0x484);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->VoiceAttack) == 0x1C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, VoiceAttack) +
                 offsetof(TechnoTypeListInt, Count) == 0x494);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, VoiceSpecialAttack) == 0x4A0);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->VoiceSpecialAttack) == 0x1C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, VoiceSpecialAttack) +
                 offsetof(TechnoTypeListInt, Count) == 0x4B0);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, VoiceDie) == 0x4BC);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->VoiceDie) == 0x1C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, VoiceDie) +
                 offsetof(TechnoTypeListInt, Count) == 0x4CC);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, VoiceFeedback) == 0x4D8);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->VoiceFeedback) == 0x1C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, VoiceFeedback) +
                 offsetof(TechnoTypeListInt, Count) == 0x4E8);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, MoveSound) == 0x4F4);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->MoveSound) == 0x1C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, MoveSound) +
                 offsetof(TechnoTypeListInt, Count) == 0x504);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, DieSound) == 0x510);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->DieSound) == 0x1C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, DieSound) +
                 offsetof(TechnoTypeListInt, Count) == 0x520);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, DebrisAnims) == 0x5C4);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->DebrisAnims) == 0x1C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, DebrisAnims) +
                 offsetof(TechnoTypeListAnim, Count) == 0x5D4);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Prerequisite) == 0x638);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->Prerequisite) == 0x1C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Prerequisite) +
                 offsetof(TechnoTypeListInt, Count) == 0x648);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, PrerequisiteOverride) == 0x654);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->PrerequisiteOverride) == 0x1C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, PrerequisiteOverride) +
                 offsetof(TechnoTypeListInt, Count) == 0x664);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Explosion) == 0x72C);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->Explosion) == 0x1C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, Explosion) +
                 offsetof(TechnoTypeListAnim, Count) == 0x73C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, DestroyAnim) == 0x748);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->DestroyAnim) == 0x1C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, DestroyAnim) +
                 offsetof(TechnoTypeListAnim, Count) == 0x758);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, DamageParticleSystems) == 0x778);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->DamageParticleSystems) == 0x1C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, DamageParticleSystems) +
                 offsetof(TechnoTypeListParticleSystem, Count) == 0x788);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, DestroyParticleSystems) == 0x794);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->DestroyParticleSystems) == 0x1C);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, DestroyParticleSystems) +
                 offsetof(TechnoTypeListParticleSystem, Count) == 0x7A4);
GG_STATIC_ASSERT(offsetof(WeaponStruct, WeaponType) == 0);
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, bools_C8C) + 13 == 0xC99);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->bools_C8C[0]) == 1);
GG_STATIC_ASSERT(sizeof(TechnoTypeClass)                      == 0xDF8);

#endif  // GG_MATCH_LAYOUT_TECHNO_TYPE_CLASS_H
