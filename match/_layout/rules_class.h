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
class OverlayTypeClass;
class WeaponTypeClass;
class UnitTypeClass;
class ObjectTypeClass;
class VoxelAnimTypeClass;
class SmudgeTypeClass;
class BuildingTypeClass;
class AircraftTypeClass;
class InfantryTypeClass;
class TerrainTypeClass;
class BulletTypeClass;
class ParticleSystemTypeClass;

// Three-byte colour with the out-of-line zeroing constructor 0x4B9BD0 (RulesClass+0x1860
// and the ColorAdd array, both built through it by the constructors). The Save loop at
// 0x675205 calls RGBClass::Save (0x6614F0) on each ColorAdd entry, so this is most likely
// RGBClass itself (0x4B9BD0 being another translation unit's copy of its inline constructor).
struct RulesColor_004B9BD0 : ColorStruct
{
    // FUNCTION: GAMEMD 0x4B9BD0 (decl; reloc)
    RulesColor_004B9BD0();
    RulesColor_004B9BD0(unsigned char r, unsigned char g, unsigned char b) : ColorStruct(r, g, b) {}
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
    // FUNCTION: GAMEMD 0x674730
    void Save(struct IStream* stream);

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
    // FUNCTION: GAMEMD 0x66B900  RulesClass::Read_CrateRules
    bool Read_CrateRules(CCINIClass* pINI);
    // FUNCTION: GAMEMD 0x671EA0  RulesClass::Read_MultiplayerDialogSettings
    bool Read_MultiplayerDialogSettings(CCINIClass* pINI);
    // FUNCTION: GAMEMD 0x668FB0  RulesClass::Read_SpecialWeapons
    bool Read_SpecialWeapons(CCINIClass* pINI);
    // FUNCTION: GAMEMD 0x66BBB0  RulesClass::Read_CombatDamage
    bool Read_CombatDamage(CCINIClass* pINI);


    int DetailMinFrameRateNormal; // 0x6850FB -> fastcall55AF40
    int DetailMinFrameRateMovie;
    int DetailBufferZoneWidth; // 0x685108 -> fastcall55AF50
    int AmmoCrateDamage;   // +0xC
    void* LargeVisceroid;   // +0x10
    void* SmallVisceroid;   // +0x14
    int AttackingAircraftSightRange;   // +0x18
    char unknown_1C[0x4];
    double TunnelSpeed;   // +0x20
    double TiberiumHeal;   // +0x28
    int SelfHealInfantryFrames;   // +0x30
    int SelfHealInfantryAmount;   // +0x34
    int SelfHealUnitFrames;   // +0x38
    int SelfHealUnitAmount;   // +0x3C
    bool FreeMCV;   // +0x40
    bool BerzerkAllowed;   // +0x41
    char unknown_42[0x2];
    int PoseDir;    // +0x044 read by AircraftClass 0x41B760 as its facing fallback
    int DeployDir;   // +0x48
    AnimTypeClass* DropPodPuff; // +0x04C
    int WaypointAnimationSpeed; // 0x6D26BE reads DWORD duration; 0x6D26E1 stores it to Tactical+DAC.
    AnimTypeClass* BarrelExplode;   // +0x54
    TypeList<const VoxelAnimTypeClass*> list_0058;  // +0x0058
    ParticleSystemTypeClass* BarrelParticle;   // +0x74
    float RadarEventColorSpeed;   // +0x78
    int RadarEventMinRadius;   // +0x7C
    float RadarEventSpeed;   // +0x80
    float RadarEventRotationSpeed;   // +0x84
    int FlashFrameTime;   // +0x88
    int RadarCombatFlashTime;
    int MaxWaypointPathLength;   // +0x90
    AnimTypeClass* Wake;   // +0x94
    AnimTypeClass* NukeTakeOff;   // +0x98
    AnimTypeClass* InfantryExplode;   // +0x9C
    AnimTypeClass* FlamingInfantry;   // +0xA0
    AnimTypeClass* InfantryHeadPop;   // +0xA4
    AnimTypeClass* InfantryNuked;   // +0xA8
    AnimTypeClass* InfantryVirus;   // +0xAC
    AnimTypeClass* InfantryBrute;   // +0xB0
    AnimTypeClass* InfantryMutate;   // +0xB4
    AnimTypeClass* Behind;   // +0xB8
    char unknown_BC[0x4];
    double AITriggerSuccessWeightDelta;   // +0xC0
    double AITriggerFailureWeightDelta;   // +0xC8
    double AITriggerTrackRecordCoefficient;   // +0xD0
    int VeinholeMonsterStrength;   // +0xD8
    int MaxVeinholeGrowth;   // +0xDC
    int VeinholeGrowthRate;   // +0xE0
    int VeinholeShrinkRate;   // +0xE4
    AnimTypeClass* VeinAttack;   // +0xE8
    int VeinDamage;   // +0xEC
    int MaximumQueuedObjects;   // +0xF0
    int AircraftFogReveal;   // +0xF4
    OverlayTypeClass* WoodCrateImg;   // +0xF8
    OverlayTypeClass* CrateImg;   // +0xFC
    OverlayTypeClass* WaterCrateImg;   // +0x100
    TypeList<const AnimTypeClass*> TouchdownAnims;  // +0x0104
    TypeList<const AnimTypeClass*> list_0120;  // +0x0120
    TypeList<const AnimTypeClass*> list_013C;  // +0x013C
    TypeList<const AnimTypeClass*> list_0158;  // +0x0158
    int DigSound;   // +0x174
    int CreateUnitSound;   // +0x178
    int CreateInfantrySound;   // +0x17C
    int CreateAircraftSound;   // +0x180
    int BaseUnderAttackSound;   // +0x184
    int GUIMainButtonSound;   // +0x188
    int GUIBuildSound;   // +0x18C
    int GUITabSound;   // +0x190
    int GUIOpenSound;   // +0x194
    int GUICloseSound;   // +0x198
    int GUIMoveOutSound;   // +0x19C
    int GUIMoveInSound;
    int GUIComboOpenSound;   // +0x1A4
    int GUIComboCloseSound;   // +0x1A8
    int GUICheckboxSound;   // +0x1AC
    int ScoreAnimSound;   // +0x1B0
    int IFVTransformSound;   // +0x1B4
    int PsychicSensorDetectSound;   // +0x1B8
    int BuildingGarrisonedSound;   // +0x1BC
    int BuildingAbandonedSound;   // +0x1C0
    int BuildingRepairedSound;   // +0x1C4
    int CheerSound;      // +0x1C8 read by HouseClass::CanOverpower
    int PlaceBeaconSound;   // +0x1CC
    int DefaultChronoSound;   // +0x1D0
    int StartPlanningModeSound;    // +0x1D4 sound played on entering planning mode
    int AddPlanningModeCommandSound;   // +0x1D8
    int ExecutePlanSound;   // +0x1DC
    int EndPlanningModeSound;    // +0x1E0 sound played on leaving it
    int CrateMoneySound;   // +0x1E4
    int CrateRevealSound;   // +0x1E8
    int CrateFireSound;   // +0x1EC
    int CrateArmourSound;   // +0x1F0
    int CrateSpeedSound;   // +0x1F4
    int CrateUnitSound;   // +0x1F8
    int CratePromoteSound;   // +0x1FC
    int ImpactWaterSound;   // +0x200
    int ImpactLandSound;   // +0x204
    int SinkingSound;   // +0x208
    int BombTickingSound;   // +0x20C
    int BombAttachSound;   // +0x210
    int YuriMindControlSound; // 4692E3: signed sentinel; 469333: sound argument
    int ChronoInSound;   // +0x218
    int ChronoOutSound;   // +0x21C
    int SpySatActivationSound;   // +0x220
    int SpySatDeactivationSound;   // +0x224
    int UpgradeVeteranSound;   // +0x228
    int UpgradeEliteSound;   // +0x22C
    int VoiceIFVRepair;   // +0x230
    int SlavesFreeSound;   // +0x234
    int SlaveMinerDeploySound;   // +0x238
    int SlaveMinerUndeploySound;   // +0x23C
    int BunkerWallsUpSound;   // +0x240
    int BunkerWallsDownSound;
    int RepairBridgeSound;   // +0x248
    int PsychicDominatorActivateSound;   // +0x24C
    int GeneticMutatorActivateSound;   // +0x250
    int PsychicRevealActivateSound;   // +0x254
    int MasterMindOverloadDeathSound;   // +0x258
    int AirstrikeAbortSound;   // +0x25C
    int AirstrikeAttackVoice;   // +0x260
    int MindClearedSound;   // +0x264
    int EnterGrinderSound;   // +0x268
    int LeaveGrinderSound;   // +0x26C
    int EnterBioReactorSound;   // +0x270
    int LeaveBioReactorSound;   // +0x274
    int ActivateSound;   // +0x278
    int DeactivateSound;   // +0x27C
    int SpyPlaneCamera;   // +0x280
    int LetsDoTheTimeWarpOutAgain;   // +0x284
    int LetsDoTheTimeWarpInAgain;   // +0x288
    int DiskLaserChargeUp;   // +0x28C
    int SpyPlaneCameraFrames;   // +0x290
    AnimTypeClass* Dig;   // +0x294
    AnimTypeClass* IonBlast;   // +0x298
    AnimTypeClass* IonBeam;   // +0x29C
    TypeList<const AnimTypeClass*> list_02A0;  // +0x02A0
    TypeList<const AnimTypeClass*> list_02BC;  // +0x02BC
    TypeList<const AnimTypeClass*> list_02D8;  // +0x02D8
    AnimTypeClass* WeatherConBoltExplosion;   // +0x2F4
    WarheadTypeClass* DominatorWarhead;   // +0x2F8
    AnimTypeClass* DominatorFirstAnim;   // +0x2FC
    AnimTypeClass* DominatorSecondAnim;   // +0x300
    int DominatorFireAtPercentage;   // +0x304
    int DominatorCaptureRange;   // +0x308
    int DominatorDamage;   // +0x30C
    int MindControlAttackLineFrames;   // +0x310
    int DrainMoneyFrameDelay;   // +0x314
    int DrainMoneyAmount;   // +0x318
    AnimTypeClass* DrainAnimationType;   // +0x31C
    AnimTypeClass* ControlledAnimationType;   // +0x320
    AnimTypeClass* PermaControlledAnimationType;   // +0x324
    AnimTypeClass* ChronoBlast;   // +0x328
    AnimTypeClass* ChronoBlastDest;   // +0x32C
    AnimTypeClass* ChronoPlacement;   // +0x330
    AnimTypeClass* ChronoBeam;   // +0x334
    AnimTypeClass* WarpIn;   // +0x338
    void* WarpOut;   // +0x33C
    void* WarpAway;   // +0x340
    AnimTypeClass* ChronoSparkle1;
    AnimTypeClass* IronCurtainInvokeAnim;   // +0x348
    AnimTypeClass* ForceShieldInvokeAnim;   // +0x34C
    AnimTypeClass* WeaponNullifyAnim; // 46A2A1 special-impact animation constructor argument
    AnimTypeClass* AtmosphereEntry; // +0x354
    TypeList<int> list_0358;  // +0x0358
    TypeList<int> list_0374;  // +0x0374
    TypeList<int> list_0390;  // +0x0390
    TypeList<int> list_03AC;  // +0x03AC
    TypeList<int> list_03C8;  // +0x03C8
    TypeList<int> list_03E4;  // +0x03E4
    void* PrerequisiteProcAlternate;   // +0x400
    int GateUp;   // +0x404
    int GateDown;   // +0x408
    int unknown_40C;   // +0x40C
    int unknown_410;   // +0x410
    char unknown_414[0x4];
    double unknown_418;   // +0x418
    int unknown_420;   // +0x420
    char unknown_424[0x4];
    double unknown_428;   // +0x428
    double unknown_430;   // +0x430
    int unknown_438;   // +0x438
    TypeList<int> list_043C;  // +0x043C
    TypeList<int> list_0458;  // +0x0458
    TypeList<int> list_0474;  // +0x0474
    int IonCannonDamage;   // +0x490
    int RailgunDamageRadius;   // +0x494
    int PrismType;   // +0x498
    int unknown_49C;   // +0x49C
    int PrismSupportMax;   // +0x4A0
    int PrismSupportDelay;   // +0x4A4
    int PrismSupportDuration;   // +0x4A8
    int PrismSupportHeight;   // +0x4AC
    int V3RocketPauseFrames;   // +0x4B0
    int V3RocketTiltFrames;   // +0x4B4
    float V3RocketPitchInitial;   // +0x4B8
    float V3RocketPitchFinal;   // +0x4BC
    float V3RocketTurnRate;   // +0x4C0
    int unknown_4C4;   // +0x4C4
    float V3RocketAcceleration;   // +0x4C8
    int V3RocketAltitude;   // +0x4CC
    int V3RocketDamage;   // +0x4D0
    int V3RocketEliteDamage;   // +0x4D4
    int V3RocketBodyLength;   // +0x4D8
    bool V3RocketLazyCurve;   // +0x4DC
    char unknown_4DD[0x3];
    int TypeA;          // +0x4E0
    int DMislPauseFrames;   // +0x4E4
    int DMislTiltFrames;   // +0x4E8
    float DMislPitchInitial;   // +0x4EC
    float DMislPitchFinal;   // +0x4F0
    float DMislTurnRate;   // +0x4F4
    int unknown_4F8;   // +0x4F8
    float DMislAcceleration;   // +0x4FC
    int DMislAltitude;   // +0x500
    int DMislDamage;   // +0x504
    int DMislEliteDamage;   // +0x508
    int DMislBodyLength;   // +0x50C
    bool DMislLazyCurve;   // +0x510
    char unknown_511[0x3];
    int TypeB;          // +0x514
    int CMislPauseFrames;   // +0x518
    int CMislTiltFrames;   // +0x51C
    float CMislPitchInitial;   // +0x520
    float CMislPitchFinal;   // +0x524
    float CMislTurnRate;   // +0x528
    int unknown_52C;   // +0x52C
    float CMislAcceleration;   // +0x530
    int CMislAltitude;   // +0x534
    int CMislDamage;   // +0x538
    int CMislEliteDamage;   // +0x53C
    int CMislBodyLength;   // +0x540
    bool CMislLazyCurve;   // +0x544
    char unknown_545[0x3];
    int CMislType;   // +0x548
    int ParadropRadius;
    double ZoomInFactor;   // +0x550
    double ConditionRedSparkingProbability;   // +0x558
    double ConditionYellowSparkingProbability;   // +0x560
    int TiberiumExplosionDamage;   // +0x568
    int TiberiumStrength;   // +0x56C
    float MinLowPowerProductionSpeed;   // +0x570
    float MaxLowPowerProductionSpeed;   // +0x574
    float LowPowerPenaltyModifier;   // +0x578
    float MultipleFactory;   // +0x57C
    int MaximumCheerRate;
    char unknown_584[0x4];
    double TreeFlammability;   // +0x588
    double MissileSpeedVar;   // +0x590
    double MissileROTVar;
    int MissileSafetyAltitude;
    WeaponTypeClass* DropPodWeapon; // +0x5A4
    int DropPodHeight;
    int DropPodSpeed; // +0x5AC
    double DropPodAngle; // +0x5B0
    double ScrollMultiplier;   // +0x5B8
    double CrewEscape;   // +0x5C0
    int ShakeScreen;   // +0x5C8
    int HoverHeight;   // +0x5CC
    double HoverBob;   // +0x5D0
    double HoverBoost;   // +0x5D8
    double HoverAcceleration;   // +0x5E0
    double HoverBrake;   // +0x5E8
    double HoverDampen;   // +0x5F0
    double PlacementDelay;   // +0x5F8
    TypeList<const VoxelAnimTypeClass*> list_0600;  // +0x0600
    void* TireVoxelDebris;   // +0x61C
    void* ScrapVoxelDebris;   // +0x620
    int BridgeVoxelMax;   // +0x624
    int CloakingStages;   // +0x628
    int RevealTriggerRadius;   // +0x62C
    double ShipSinkingWeight;   // +0x630
    double IceCrackingWeight;   // +0x638
    double IceBreakingWeight;   // +0x640
    TypeList<int> list_0648;  // +0x0648
    bool CliffBackImpassability;   // +0x664
    char unknown_665[0x3];
    double VeteranRatio;   // +0x668
    double VeteranCombat;   // +0x670
    double VeteranSpeed;   // +0x678
    double VeteranSight;   // +0x680
    double VeteranArmor;   // +0x688
    double VeteranROF;   // +0x690
    double VeteranCap;   // +0x698
    int CloakSound;   // +0x6A0
    int SellSound;   // +0x6A4
    int GameClosed;   // +0x6A8
    int IncomingMessage;
    int SystemError;   // +0x6B0
    int OptionsChanged;   // +0x6B4
    int GameForming;   // +0x6B8
    int PlayerLeft;   // +0x6BC
    int PlayerJoined;   // +0x6C0
    int MessageCharTyped;
    int Construction;   // +0x6C8
    TypeList<int> list_06CC;  // +0x06CC
    int BuildingDieSound;   // +0x6E8
    int BuildingSlam;   // +0x6EC
    int RadarOn;   // +0x6F0
    int RadarOff;   // +0x6F4
    int MovieOn;   // +0x6F8
    int MovieOff;   // +0x6FC
    int ScoldSound;    // +0x700 sound played when planning guard areas are refused
    int TeslaCharge;   // +0x704
    int TeslaZap;   // +0x708
    int GenericClick;   // +0x70C
    int GenericBeep;   // +0x710
    int BuildingDamageSound;   // +0x714
    int HealCrateSound;   // +0x718
    int ChuteSound;   // +0x71C
    int StopSound;   // +0x720
    int GuardSound;
    int ScatterSound;
    int unknown_72C;
    int StormSound;   // +0x730
    TypeList<int> list_0734;  // +0x0734
    int ShellButtonSlideSound;   // +0x750
    char unknown_754[0x4];
    double WallBuildSpeedCoefficient;   // +0x758
    double ChargeToDrainRatio;   // +0x760
    double TrackedUphill;   // +0x768
    double TrackedDownhill;   // +0x770
    double WheeledUphill;   // +0x778
    double WheeledDownhill;   // +0x780
    int SpotlightMovementRadius;
    int SpotlightLocationRadius;
    double SpotlightSpeed;   // +0x790
    double SpotlightAcceleration;   // +0x798
    double SpotlightAngle;   // +0x7A0
    int SpotlightRadius;
    int WindDirection;   // +0x7AC
    int CameraRange;   // +0x7B0
    int FlightLevel; // native717810 reads fallback scalar via pointer8871E0
    int ParachuteMaxFallRate;   // +0x7B8
    int NoParachuteMaxFallRate;   // +0x7BC
    int BuildingDrop;   // +0x7C0
    TypeList<const SmudgeTypeClass*> list_07C4;  // +0x07C4
    TypeList<const SmudgeTypeClass*> list_07E0;  // +0x07E0
    TypeList<const SmudgeTypeClass*> list_07FC;  // +0x07FC
    TypeList<const SmudgeTypeClass*> list_0818;  // +0x0818
    TypeList<const SmudgeTypeClass*> list_0834;  // +0x0834
    TypeList<const BuildingTypeClass*> list_0850;  // +0x0850
    void* GDIGateOne;   // +0x86C
    void* GDIGateTwo;   // +0x870
    void* NodGateOne;   // +0x874
    void* NodGateTwo;   // +0x878
    void* WallTower;   // +0x87C
    TypeList<const BuildingTypeClass*> list_0880;  // +0x0880
    int GDIPowerPlant;   // +0x89C
    int NodRegularPower;   // +0x8A0
    int NodAdvancedPower;   // +0x8A4
    int ThirdPowerPlant;   // +0x8A8
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
    double GDIWallDefense;   // +0xAF8
    double GDIWallDefenseCoefficient;   // +0xB00
    double NodBaseDefenseCoefficient;   // +0xB08
    double GDIBaseDefenseCoefficient;   // +0xB10
    int ComputerBaseDefenseResponse;   // +0xB18
    int MaximumBaseDefenseValue;   // +0xB1C
    TypeList<const UnitTypeClass*> unknown_B20;  // +0x0B20
    TypeList<const UnitTypeClass*> list_0B3C;  // +0x0B3C
    TypeList<const AircraftTypeClass*> list_0B58;  // +0x0B58
    TypeList<const AnimTypeClass*> list_0B74;  // +0x0B74
    TypeList<const AnimTypeClass*> list_0B90;  // +0x0B90
    AnimTypeClass* Smoke;   // +0xBAC
    AnimTypeClass* Smoke_BB0;   // +0xBB0
    AnimTypeClass* MoveFlash;   // +0xBB4
    AnimTypeClass* BombParachute;   // +0xBB8
    AnimTypeClass* Parachute;   // +0xBBC
    TypeList<const AnimTypeClass*> list_0BC0;  // +0x0BC0
    AnimTypeClass* SmallFire;   // +0xBDC
    AnimTypeClass* LargeFire;   // +0xBE0
    int Paratrooper;   // +0xBE4
    int EliteFlashTimer;   // +0xBE8
    int ChronoDelay;   // +0xBEC
    int ChronoReinfDelay;   // +0xBF0
    int ChronoDistanceFactor;   // +0xBF4
    char ChronoTrigger;   // +0xBF8
    char unknown_BF9[0x3];
    int ChronoMinimumDelay;   // +0xBFC
    int ChronoRangeMinimum;   // +0xC00
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
    int SpyPowerBlackout;   // +0xD64
    float SpyMoneyStealPercent;   // +0xD68
    bool AttackCursorOnDisguise;   // +0xD6C
    char unknown_D6D[0x3];
    float AIMinorSuperReadyPercent; // +0xD70
    int AISafeDistance;   // +0xD74
    int HarvesterTooFarDistance;   // +0xD78
    int ChronoHarvTooFarDistance;   // +0xD7C
    TypeList<int> list_0D80;  // +0x0D80
    TypeList<int> list_0D9C;  // +0x0D9C
    TypeList<int> list_0DB8;  // +0x0DB8
    TypeList<int> list_0DD4;  // +0x0DD4
    int AIRestrictReplaceTime;   // +0xDF0
    int ThreatPerOccupant;   // +0xDF4
    int ApproachTargetResetMultiplier;   // +0xDF8
    int CampaignMoneyDeltaEasy;   // +0xDFC
    int CampaignMoneyDeltaHard;   // +0xE00
    int GuardAreaTargetingDelay;
    int NormalTargetingDelay;   // +0xE08
    int AINavalYardAdjacency;   // +0xE0C
    TypeList<int> list_0E10;  // +0x0E10
    TypeList<int> list_0E2C;  // +0x0E2C
    int MaximumBuildingPlacementFailures;   // +0xE48
    TypeList<int> list_0E4C;  // +0x0E4C
    TypeList<int> list_0E68;  // +0x0E68
    TypeList<int> list_0E84;  // +0x0E84
    TypeList<int> list_0EA0;  // +0x0EA0
    char AICaptureLowMoneyMark[0x8];
    TypeList<int> list_0EC4;  // +0x0EC4
    int AISuperDefenseFrames;   // +0xEE0
    int AISuperDefenseDistance;   // +0xEE4
    TypeList<int> list_0EE8;  // +0x0EE8
    TypeList<int> list_0F04;  // +0x0F04
    TypeList<int> list_0F20;  // +0x0F20
    float PurifierBonus;   // +0xF3C
    float OccupyDamageMultiplier;   // +0xF40
    float OccupyROFMultiplier;   // +0xF44
    int OccupyWeaponRange;   // +0xF48 added to the range of an object with slot 256 set (TechnoClass 0x6F7220)
    float BunkerDamageMultiplier;   // +0xF4C
    float BunkerROFMultiplier;   // +0xF50
    int BunkerWeaponRangeBonus;   // +0xF54 range bonus while bunkered, not a building (0x6F7220)
    float OpenToppedDamageMultiplier;   // +0xF58
    int OpenToppedRangeBonus;   // +0xF5C range bonus for an open-topped passenger (0x6F7220)
    int OpenToppedWarpDistance;   // +0xF60
    float FallingDamageMultiplier;   // +0xF64
    bool CurrentStrengthDamage;   // +0xF68
    char unknown_F69[0x3];
    int Technician;   // +0xF6C
    int Engineer;   // +0xF70
    int Pilot;   // +0xF74
    int AlliedCrew;   // +0xF78
    int SovietCrew;   // +0xF7C
    int ThirdCrew;   // +0xF80
    WarheadTypeClass* FlameDamage;   // +0xF84
    WarheadTypeClass* FlameDamage2;   // +0xF88
    WarheadTypeClass* NukeWarhead; // 469CA7 compares this pointer with Bullet.WH
    BulletTypeClass* NukeProjectile;   // +0xF90
    BulletTypeClass* NukeDown;   // +0xF94
    WarheadTypeClass* MutateWarhead;   // +0xF98
    WarheadTypeClass* MutateExplosionWarhead;   // +0xF9C
    WarheadTypeClass* EMPulseWarhead;   // +0xFA0
    BulletTypeClass* EMPulseProjectile;   // +0xFA4
    WarheadTypeClass* C4Warhead;
    WarheadTypeClass* CrushWarhead;   // +0xFAC
    WarheadTypeClass* V3Warhead;   // +0xFB0
    WarheadTypeClass* DMislWarhead;   // +0xFB4
    WarheadTypeClass* V3EliteWarhead;   // +0xFB8
    WarheadTypeClass* DMislEliteWarhead;   // +0xFBC
    WarheadTypeClass* CMislWarhead;   // +0xFC0
    WarheadTypeClass* CMislEliteWarhead;   // +0xFC4
    WarheadTypeClass* IvanWarhead;   // +0xFC8
    int IvanDamage;   // +0xFCC
    int IvanTimedDelay;      // +0xFD0
    bool CanDetonateTimeBomb;   // +0xFD4
    bool CanDetonateDeathBomb;   // +0xFD5
    char unknown_FD6[0x2];
    int IvanIconFlickerRate;      // +0xFD8
    WeaponTypeClass* DeathWeapon;   // +0xFDC
    void* unknown_FE0;   // +0xFE0 BOMBCURS.SHP
    void* unknown_FE4;   // +0xFE4 CHRONOSK.SHP
    int IronCurtainDuration;   // +0xFE8
    int PsychicRevealRadius;   // +0xFEC
    WarheadTypeClass* IonCannonWarhead;   // +0xFF0
    int VeinholeTypeClass;   // +0xFF4
    TypeList<const TerrainTypeClass*> list_0FF8;  // +0x0FF8
    int InfantryBlinkDisguiseTime;   // +0x1014
    ParticleSystemTypeClass* DefaultLargeGreySmokeSystem;   // +0x1018
    ParticleSystemTypeClass* DefaultSmallGreySmokeSystem;   // +0x101C
    ParticleSystemTypeClass* DefaultSparkSystem;   // +0x1020
    ParticleSystemTypeClass* DefaultLargeRedSmokeSystem;   // +0x1024
    ParticleSystemTypeClass* DefaultSmallRedSmokeSystem;   // +0x1028
    ParticleSystemTypeClass* DefaultDebrisSmokeSystem;   // +0x102C
    ParticleSystemTypeClass* DefaultFireStreamSystem;   // +0x1030
    ParticleSystemTypeClass* DefaultTestParticleSystem;   // +0x1034
    ParticleSystemTypeClass* DefaultRepairParticleSystem;   // +0x1038
    char unknown_103C[0x4];
    double MyEffectivenessCoefficientDefault;   // +0x1040
    double TargetEffectivenessCoefficientDefault;   // +0x1048
    double TargetSpecialThreatCoefficientDefault;   // +0x1050
    double TargetStrengthCoefficientDefault;   // +0x1058
    double TargetDistanceCoefficientDefault;   // +0x1060
    double DumbMyEffectivenessCoefficient;   // +0x1068
    double DumbTargetEffectivenessCoefficient;   // +0x1070
    double DumbTargetSpecialThreatCoefficient;   // +0x1078
    double DumbTargetStrengthCoefficient;   // +0x1080
    double DumbTargetDistanceCoefficient;   // +0x1088
    double EnemyHouseThreatBonus;   // +0x1090
    double TurboBoost;   // +0x1098
    double AttackInterval;   // +0x10A0
    double AttackDelay;   // +0x10A8
    double PowerEmergency;   // +0x10B0
    double AirstripRatio;   // +0x10B8
    int AirstripLimit;   // +0x10C0
    char unknown_10C4[0x4];
    double HelipadRatio;   // +0x10C8
    int HelipadLimit;   // +0x10D0
    char unknown_10D4[0x4];
    double TeslaRatio;   // +0x10D8
    int TeslaLimit;   // +0x10E0
    char unknown_10E4[0x4];
    double AARatio;   // +0x10E8
    int AALimit;   // +0x10F0
    char unknown_10F4[0x4];
    double DefenseRatio;   // +0x10F8
    int DefenseLimit;   // +0x1100
    char unknown_1104[0x4];
    double WarRatio;   // +0x1108
    int WarLimit;   // +0x1110
    char unknown_1114[0x4];
    double BarracksRatio;   // +0x1118
    int BarracksLimit;   // +0x1120
    int RefineryLimit;   // +0x1124
    double RefineryRatio;   // +0x1128
    int BaseSizeAdd;   // +0x1130
    int PowerSurplus;   // +0x1134
    int InfantryReserve;   // +0x1138
    int InfantryBaseMult;   // +0x113C
    int SoloCrateMoney;   // +0x1140
    int TreeStrength;   // +0x1144
    UnitTypeClass* UnitCrateType;   // +0x1148
    char unknown_114C[0x4];
    double PatrolScan;   // +0x1150
    TypeList<int> list_1158;  // +0x1158
    TypeList<int> list_1174;  // +0x1174
    int DissolveUnfilledTeamDelay;   // +0x1190
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
    int AIAlternateProductionCreditCutoff;   // +0x1300
    TypeList<int> list_1304;  // +0x1304
    TypeList<int> list_1320;  // +0x1320
    TypeList<int> list_133C;  // +0x133C
    TypeList<int> list_1358;  // +0x1358
    TypeList<int> list_1374;  // +0x1374
    TypeList<int> list_1390;  // +0x1390
    TypeList<int> list_13AC;  // +0x13AC
    TypeList<int> list_13C8;  // +0x13C8
    char unknown_13E4[0x4];
    double AIUseTurbineUpgradeProbability;   // +0x13E8
    TypeList<int> list_13F0;  // +0x13F0
    char unknown_140C[0x4];
    double CloakDelay;   // +0x1410
    double GameSpeedBias;   // +0x1418
    double BaseBias;   // +0x1420
    double ExpSpread;   // +0x1428
    int FireSupress;   // +0x1430
    int unknown_1434;
    int unknown_1438_1438;   // +0x1438
    int unknown_143C;   // +0x143C
    int unknown_1440;   // +0x1440
    int unknown_1444;   // +0x1444
    int unknown_1448;   // +0x1448
    int unknown_144C;   // +0x144C
    int unknown_1450;   // +0x1450
    int unknown_1454;   // +0x1454
    int unknown_1458;   // +0x1458
    int unknown_145C;   // +0x145C
    int AIBaseSpacing;   // +0x1460
    int SilverCrate;   // +0x1464
    int WoodCrate;   // +0x1468
    int WaterCrate;   // +0x146C
    int CrateMinimum;   // +0x1470
    int CrateMaximum;   // +0x1474
    int unknown_1478_1478;   // +0x1478
    AnimTypeClass* DropZoneAnim;   // +0x147C
    int MinMoney;   // +0x1480
    int Money; // native697F74 default Credits
    int MaxMoney;   // +0x1488
    int MoneyIncrement;   // +0x148C
    int MinUnitCount;   // +0x1490
    int UnitCount;
    int MaxUnitCount;   // +0x1498
    int TechLevel;   // +0x149C
    int GameSpeed;
    int AIDifficulty;   // +0x14A4
    int AIPlayers;   // +0x14A8
    bool BridgeDestruction;   // +0x14AC
    bool ShadowGrow;   // +0x14AD
    bool Shroud; // byte test0x6849D6
    bool Bases;   // +0x14AF
    bool TiberiumGrows;   // +0x14B0
    bool Crates;
    bool CaptureTheFlag;   // +0x14B2
    bool HarvesterTruce;   // +0x14B3
    bool MultiEngineer;   // +0x14B4
    bool AlliesAllowed;
    bool ShortGame;
    bool FogOfWar;
    bool MCVRedeploys;
    bool SuperWeaponsAllowed;
    bool BuildOffAlly;
    bool AllyChangeAllowed;
    int DropZoneRadius;   // +0x14BC
    double MessageDelay;
    double SavourDelay;   // +0x14C8
    int Players;
    char unknown_14D4[0x4];
    double BaseDefenseDelay;   // +0x14D8
    int SuspendPriority;   // +0x14E0
    char unknown_14E4[0x4];
    double SuspendDelay;   // +0x14E8
    double SurvivorRate;   // +0x14F0
    int AlliedSurvivorDivisor;   // +0x14F8
    int SovietSurvivorDivisor;   // +0x14FC
    int ThirdSurvivorDivisor;   // +0x1500
    char unknown_1504[0x4];
    double ReloadRate;   // +0x1508
    double AutocreateTime;   // +0x1510
    double BuildupTime;   // +0x1518
    int HarvesterLoadRate;   // +0x1520
    char unknown_1524[0x4];
    double HarvesterDumpRate;   // +0x1528
    int AtomDamage;   // +0x1530
    char unknown_1534[0x104];
    double GrowthRate;   // +0x1638
    double ShroudRate;   // +0x1640
    double FogRate;   // +0x1648
    double IceGrowthRate;   // +0x1650
    double VeinGrowthRate;   // +0x1658
    int IceSolidifyFrameTime;   // +0x1660
    char unknown_1664[0x4];
    double AmbientChangeRate;   // +0x1668
    double AmbientChangeStep;   // +0x1670
    double CrateRegen;   // +0x1678
    double TimerWarning;   // +0x1680
    char TiberiumTransmogrify[0x8];
    double unknown_1690;   // +0x1690
    double unknown_1698;   // +0x1698
    double unknown_16A0;   // +0x16A0
    double SpeakDelay;   // +0x16A8
    double DamageDelay;   // +0x16B0
    int Gravity;
    int LeptonsPerSightIncrease;   // +0x16BC
    int Incoming;   // +0x16C0
    int MinDamage;   // +0x16C4
    int MaxDamage;   // +0x16C8
    int RepairStep; // native712125 reads scalar via pointer8871E0
    double RepairPercent; // native 0x7120D0 loads the full 8-byte value
    int IRepairStep; // native524795 reads dword via pointer8871E0
    char unknown_16DC[0x4];
    double RepairRate;   // +0x16E0
    double URepairRate;   // +0x16E8
    double IRepairRate;   // +0x16F0
    double unknown_16F8;   // +0x16F8
    double ConditionYellow;
    double ConditionRed;
    double IdleActionFrequency;   // +0x1710
    int CloseEnough;   // +0x1718
    int Stray;   // +0x171C
    int RelaxedStray;   // +0x1720
    char GuardModeStray[0x4];
    int Crush;   // +0x1728
    int CrateRadius;   // +0x172C
    int HomingScatter;   // +0x1730
    int BallisticScatter;
    double RefundPercent;   // +0x1738
    int BridgeStrength;   // +0x1740
    char unknown_1744[0x4];
    double BuildSpeed; // native 0x711EE0 loads the full 8-byte value
    double C4Delay;   // +0x1750
    int CreditReserve;   // +0x1758
    char unknown_175C[0x4];
    double PathDelay;   // +0x1760
    int BlockagePathDelay;   // +0x1768
    char unknown_176C[0x4];
    double MovieTime;   // +0x1770
    int TiberiumShortScan;   // +0x1778
    int TiberiumLongScan;   // +0x177C
    int SlaveMinerShortScan;   // +0x1780
    int SlaveMinerSlaveScan;   // +0x1784
    int SlaveMinerLongScan;   // +0x1788
    int SlaveMinerScanCorrection;   // +0x178C
    int SlaveMinerKickFrameDelay;   // +0x1790
    int LightningDeferment;   // +0x1794
    int LightningDamage;   // +0x1798
    int LightningStormDuration;   // +0x179C
    int LightningHitDelay;   // +0x17A0
    int LightningScatterDelay;   // +0x17A4
    int LightningCellSpread;   // +0x17A8
    int LightningSeparation;   // +0x17AC
    bool LightningPrintText;   // +0x17B0
    char unknown_17B1[0x3];
    int LightningWarhead;   // +0x17B4
    int ForceShieldRadius;   // +0x17B8
    int ForceShieldDuration;   // +0x17BC
    int ForceShieldBlackoutDuration;   // +0x17C0
    int ForceShieldPlayFadeSoundTime;   // +0x17C4
    bool MutateExplosion;   // +0x17C8
    char unknown_17C9[0x3];
    int CollapseChance;   // +0x17CC
    int WeedCapacity;   // +0x17D0
    int unknown_17D4_17D4;   // +0x17D4
    int unknown_17D8;   // +0x17D8
    int unknown_17DC;   // +0x17DC
    bool Paranoid;   // +0x17E0
    bool CurleyShuffle;   // +0x17E1
    bool BlendedFog;   // +0x17E2
    bool CompEasyBonus;   // +0x17E3
    bool FineDiffControl;   // +0x17E4
    bool TiberiumExplosive;   // +0x17E5
    bool EnemyHealth;   // +0x17E6
    bool AllyReveal;   // +0x17E7
    bool SeparateAircraft;   // +0x17E8
    bool TreeTargeting;   // +0x17E9
    bool NamedCivilians;   // +0x17EA
    bool PlayerAutoCrush;   // +0x17EB
    bool PlayerReturnFire;   // +0x17EC
    bool PlayerScatter;   // +0x17ED
    bool RevealByHeight;   // +0x17EE
    bool AllowShroudedSubteranneanMoves;   // +0x17EF
    bool ShroudGrow;   // +0x17F0
    bool NodAIBuildsWalls;   // +0x17F1
    bool AIBuildsWalls;   // +0x17F2
    bool UseMinDefenseRule;   // +0x17F3
    AnimTypeClass* EMPulseSparkles;   // +0x17F4
    float EngineerCaptureLevel;   // +0x17F8
    float EngineerCaptureLevel_17FC;   // +0x17FC
    int TalkBubbleTime;   // +0x1800
    int RadDurationMultiple;
    int RadApplicationDelay;   // +0x1808
    int RadLevelMax;   // +0x180C
    int RadLevelDelay;   // +0x1810
    int RadLightDelay;   // +0x1814
    double RadLevelFactor;   // +0x1818
    double RadLightFactor;   // +0x1820
    double RadTintFactor;   // +0x1828
    bool RadColorR;   // +0x1830
    bool RadColorG;   // +0x1831
    bool RadColorB;   // +0x1832
    char unknown_1833[0x1];
    WarheadTypeClass* RadSiteWarhead;   // +0x1834
    int ElevationIncrement;            // +0x1838
    char unknown_183C[0x4];
    double ElevationIncrementBonus;    // +0x1840
    double ElevationBonusCap;          // +0x1848
    bool AlliedWallTransparency;       // +0x1850
    char unknown_1851[0x7];
    double WallPenetratorThreshold;    // +0x1858 (default pushed as two dwords)
    RulesColor_004B9BD0 unknown_1860;   // +0x1860 (ctor 0x4B9BD0)
    ColorStruct unknown_1863;   // +0x1863
    ColorStruct unknown_1866;   // +0x1866 read at 0x66B7AD
    ColorStruct unknown_1869;   // +0x1869 read at 0x66B7D7
    int OreTwinkleChance; // random upper bound minus one0x68508F
    AnimTypeClass* OreTwinkle; // 0x6850D9 -> AnimClass constructor0x421EA0
    RulesColor_004B9BD0 ColorAdd[0x10];     // +0x1874
    int LaserTargetColor;   // +0x18A4
    int IronCurtainColor;   // +0x18A8
    int BerserkColor;   // +0x18AC
    int ForceShieldColor;   // +0x18B0
    float DirectRockingCoefficient; // 0x469817: FMUL float ptr [ECX + 0x18b4]
    float FallBackCoefficient;   // +0x18B8
    char unknown_18BC[0x4];
};

GG_STATIC_ASSERT(offsetof(RulesClass, WaypointAnimationSpeed) == 0x50);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->WaypointAnimationSpeed) == 4);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_B20) == 0xB20);
GG_STATIC_ASSERT(offsetof(RulesClass, BunkerWallsDownSound) == 0x244);
GG_STATIC_ASSERT(offsetof(RulesClass, DetailMinFrameRateNormal) == 0x000);
GG_STATIC_ASSERT(offsetof(RulesClass, DetailBufferZoneWidth) == 0x008);
GG_STATIC_ASSERT(offsetof(RulesClass, OreTwinkleChance) == 0x186C);
GG_STATIC_ASSERT(offsetof(RulesClass, CheerSound) == 0x1C8);
GG_STATIC_ASSERT(offsetof(RulesClass, TypeA) == 0x4E0);
GG_STATIC_ASSERT(offsetof(RulesClass, TypeB) == 0x514);
GG_STATIC_ASSERT(offsetof(RulesClass, AIMinorSuperReadyPercent) == 0xD70);
GG_STATIC_ASSERT(offsetof(RulesClass, IvanTimedDelay) == 0xFD0);
GG_STATIC_ASSERT(offsetof(RulesClass, IvanIconFlickerRate) == 0xFD8);
GG_STATIC_ASSERT(offsetof(RulesClass, ElevationIncrement) == 0x1838);
GG_STATIC_ASSERT(offsetof(RulesClass, ElevationIncrementBonus) == 0x1840);
GG_STATIC_ASSERT(offsetof(RulesClass, ElevationBonusCap) == 0x1848);
GG_STATIC_ASSERT(offsetof(RulesClass, AlliedWallTransparency) == 0x1850);
GG_STATIC_ASSERT(offsetof(RulesClass, WallPenetratorThreshold) == 0x1858);
GG_STATIC_ASSERT(offsetof(RulesClass, ColorAdd) == 0x1874);
GG_STATIC_ASSERT(offsetof(RulesClass, OreTwinkle) == 0x1870);

GG_STATIC_ASSERT(offsetof(RulesClass, ParadropRadius) == 0x54C);
GG_STATIC_ASSERT(offsetof(RulesClass, DropPodPuff) == 0x04C);
GG_STATIC_ASSERT(offsetof(RulesClass, AtmosphereEntry) == 0x354);
GG_STATIC_ASSERT(offsetof(RulesClass, DropPodWeapon) == 0x5A4);
GG_STATIC_ASSERT(offsetof(RulesClass, DropPodHeight) == 0x5A8);
GG_STATIC_ASSERT(offsetof(RulesClass, StartPlanningModeSound) == 0x1D4);
GG_STATIC_ASSERT(offsetof(RulesClass, EndPlanningModeSound) == 0x1E0);
GG_STATIC_ASSERT(offsetof(RulesClass, ScoldSound) == 0x700);
GG_STATIC_ASSERT(offsetof(RulesClass, DropPodSpeed) == 0x5AC);
GG_STATIC_ASSERT(offsetof(RulesClass, DropPodAngle) == 0x5B0);
GG_STATIC_ASSERT(offsetof(RulesClass, ChronoSparkle1) == 0x344);
GG_STATIC_ASSERT(offsetof(RulesClass, GuardAreaTargetingDelay) == 0xE04);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_D54) == 0xD54);
GG_STATIC_ASSERT(offsetof(RulesClass, SpotlightMovementRadius) == 0x788);
GG_STATIC_ASSERT(offsetof(RulesClass, SpotlightLocationRadius) == 0x78C);
GG_STATIC_ASSERT(offsetof(RulesClass, SpotlightRadius) == 0x7A8);
GG_STATIC_ASSERT(offsetof(RulesClass, C4Warhead) == 0x0FA8);
GG_STATIC_ASSERT(offsetof(RulesClass, ConditionYellow) == 0x1700);
GG_STATIC_ASSERT(offsetof(RulesClass, ConditionRed) == 0x1708);
GG_STATIC_ASSERT(offsetof(RulesClass, RadDurationMultiple) == 0x1804);

GG_STATIC_ASSERT(offsetof(RulesClass, PoseDir) == 0x44);



GG_STATIC_ASSERT(offsetof(RulesClass, CrateMinimum) == 0x1470);

GG_STATIC_ASSERT(offsetof(RulesClass, CrateMaximum) == 0x1474);

GG_STATIC_ASSERT(offsetof(RulesClass, Players) == 0x14D0);

// GLOBAL: GAMEMD 0x008871E0 — active RulesClass pointer.
extern RulesClass* RulesInstance;

GG_STATIC_ASSERT(offsetof(RulesClass, RadarCombatFlashTime) == 0x08C);
GG_STATIC_ASSERT(offsetof(RulesClass, MaximumCheerRate) == 0x580);
GG_STATIC_ASSERT(offsetof(RulesClass, MissileROTVar) == 0x598);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->MissileROTVar) == 8);
GG_STATIC_ASSERT(offsetof(RulesClass, MissileSafetyAltitude) == 0x5A0);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->MissileSafetyAltitude) == 4);
GG_STATIC_ASSERT(offsetof(RulesClass, GuardSound) == 0x724);
GG_STATIC_ASSERT(offsetof(RulesClass, ScatterSound) == 0x728);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_72C) == 0x72C);
GG_STATIC_ASSERT(offsetof(RulesClass, Shroud) == 0x14AE);
GG_STATIC_ASSERT(offsetof(RulesClass, AlliesAllowed) == 0x14B5);
GG_STATIC_ASSERT(offsetof(RulesClass, AllyChangeAllowed) == 0x14BB);

GG_STATIC_ASSERT(offsetof(RulesClass, Money) == 0x1484);
GG_STATIC_ASSERT(offsetof(RulesClass, UnitCount) == 0x1494);
GG_STATIC_ASSERT(offsetof(RulesClass, GameSpeed) == 0x14A0);
GG_STATIC_ASSERT(offsetof(RulesClass, Crates) == 0x14B1);
GG_STATIC_ASSERT(offsetof(RulesClass, ShortGame) == 0x14B6);
GG_STATIC_ASSERT(offsetof(RulesClass, MCVRedeploys) == 0x14B8);
GG_STATIC_ASSERT(offsetof(RulesClass, SuperWeaponsAllowed) == 0x14B9);
GG_STATIC_ASSERT(offsetof(RulesClass, BuildOffAlly) == 0x14BA);

GG_STATIC_ASSERT(offsetof(RulesClass, GUIMoveInSound)  == 0x1A0);
GG_STATIC_ASSERT(offsetof(RulesClass, MessageCharTyped)  == 0x6C4);
GG_STATIC_ASSERT(offsetof(RulesClass, C4Warhead) == 0xFA8);
GG_STATIC_ASSERT(offsetof(RulesClass, FlightLevel) == 0x7B4);
GG_STATIC_ASSERT(offsetof(RulesClass, RepairStep) == 0x16CC);
GG_STATIC_ASSERT(offsetof(RulesClass, Gravity) == 0x16B8);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->Gravity) == 4);
GG_STATIC_ASSERT(offsetof(RulesClass, RepairPercent) == 0x16D0);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->RepairPercent) == 8);
GG_STATIC_ASSERT(offsetof(RulesClass, BallisticScatter) == 0x1734);
GG_STATIC_ASSERT(offsetof(RulesClass, IRepairStep) == 0x16D8);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->IRepairStep) == 4);
GG_STATIC_ASSERT(offsetof(RulesClass, BuildSpeed) == 0x1748);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->BuildSpeed) == 8);
GG_STATIC_ASSERT(offsetof(RulesClass, AISuperDefenseFrames) == 0xEE0);
GG_STATIC_ASSERT(offsetof(RulesClass, MaxWaypointPathLength) == 0x90);
GG_STATIC_ASSERT(offsetof(RulesClass, DefaultSparkSystem) == 0x1020);
GG_STATIC_ASSERT(offsetof(RulesClass, WeedCapacity) == 0x17D0);
GG_STATIC_ASSERT(offsetof(RulesClass, MaxVeinholeGrowth) == 0xDC);
GG_STATIC_ASSERT(offsetof(RulesClass, VeteranSpeed) == 0x678);
GG_STATIC_ASSERT(offsetof(RulesClass, LeptonsPerSightIncrease) == 0x16BC);
GG_STATIC_ASSERT(offsetof(RulesClass, LightningDeferment) == 0x1794);
GG_STATIC_ASSERT(offsetof(RulesClass, WarpAway) == 0x340);
GG_STATIC_ASSERT(offsetof(RulesClass, OpenToppedWarpDistance) == 0xF60);
GG_STATIC_ASSERT(offsetof(RulesClass, OccupyWeaponRange) == 0xF48);
GG_STATIC_ASSERT(offsetof(RulesClass, BunkerWeaponRangeBonus) == 0xF54);
GG_STATIC_ASSERT(offsetof(RulesClass, OpenToppedRangeBonus) == 0xF5C);
GG_STATIC_ASSERT(offsetof(RulesClass, SlaveMinerKickFrameDelay) == 0x1790);
GG_STATIC_ASSERT(offsetof(RulesClass, InfantryExplode) == 0x9C);
GG_STATIC_ASSERT(offsetof(RulesClass, BombParachute) == 0xBB8);
GG_STATIC_ASSERT(offsetof(RulesClass, Parachute) == 0xBBC);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1863) == 0x1863);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1866) == 0x1866);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1869) == 0x1869);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_16F8) == 0x16F8);
GG_STATIC_ASSERT(offsetof(RulesClass, GDIGateOne) == 0x86C);
GG_STATIC_ASSERT(offsetof(RulesClass, GDIGateTwo) == 0x870);
GG_STATIC_ASSERT(offsetof(RulesClass, NodGateOne) == 0x874);
GG_STATIC_ASSERT(offsetof(RulesClass, NodGateTwo) == 0x878);
GG_STATIC_ASSERT(offsetof(RulesClass, WallTower) == 0x87C);
GG_STATIC_ASSERT(offsetof(RulesClass, ChronoInSound) == 0x218);
GG_STATIC_ASSERT(offsetof(RulesClass, ChronoOutSound) == 0x21C);
GG_STATIC_ASSERT(offsetof(RulesClass, WarpOut) == 0x33C);
GG_STATIC_ASSERT(offsetof(RulesClass, ChronoDelay) == 0xBEC);
GG_STATIC_ASSERT(offsetof(RulesClass, ChronoDistanceFactor) == 0xBF4);
GG_STATIC_ASSERT(offsetof(RulesClass, ChronoTrigger) == 0xBF8);
GG_STATIC_ASSERT(offsetof(RulesClass, ChronoMinimumDelay) == 0xBFC);
GG_STATIC_ASSERT(offsetof(RulesClass, ChronoRangeMinimum) == 0xC00);
GG_STATIC_ASSERT(offsetof(RulesClass, TunnelSpeed) == 0x20);
GG_STATIC_ASSERT(offsetof(RulesClass, GenericBeep) == 0x710);
GG_STATIC_ASSERT(offsetof(RulesClass, RadarOn) == 0x6F0);
GG_STATIC_ASSERT(offsetof(RulesClass, RadarOff) == 0x6F4);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_D58) == 0xD58);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_D5C) == 0xD5C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_D60) == 0xD60);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_420) == 0x420);
GG_STATIC_ASSERT(offsetof(RulesClass, ParachuteMaxFallRate) == 0x7B8);
GG_STATIC_ASSERT(offsetof(RulesClass, NoParachuteMaxFallRate) == 0x7BC);
GG_STATIC_ASSERT(offsetof(RulesClass, GUIMainButtonSound) == 0x188);
GG_STATIC_ASSERT(offsetof(RulesClass, GUIBuildSound) == 0x18C);
GG_STATIC_ASSERT(offsetof(RulesClass, GUITabSound) == 0x190);
GG_STATIC_ASSERT(offsetof(RulesClass, GUIOpenSound) == 0x194);
GG_STATIC_ASSERT(offsetof(RulesClass, GUICloseSound) == 0x198);
GG_STATIC_ASSERT(offsetof(RulesClass, WallBuildSpeedCoefficient) == 0x758);
GG_STATIC_ASSERT(sizeof(RulesClass)              == 0x18C0);

extern RulesClass* Rules;   // GLOBAL: GAMEMD 0x8871E0



GG_STATIC_ASSERT(offsetof(RulesClass, IncomingMessage) == 0x6AC);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1434) == 0x1434);
GG_STATIC_ASSERT(offsetof(RulesClass, MessageDelay) == 0x14C0);

GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->C4Warhead) == 4);
GG_STATIC_ASSERT(offsetof(RulesClass, NukeWarhead) == 0xF8C);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->NukeWarhead) == 4);

// Bullet impact caller layout closure, native 4690B0 entry-origin assembly.
GG_STATIC_ASSERT(offsetof(RulesClass, YuriMindControlSound) == 0x214);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->YuriMindControlSound) == 4);
GG_STATIC_ASSERT(offsetof(RulesClass, WeaponNullifyAnim) == 0x350);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->WeaponNullifyAnim) == 4);
GG_STATIC_ASSERT(offsetof(RulesClass, DirectRockingCoefficient) == 0x18B4);
GG_STATIC_ASSERT(sizeof(((RulesClass*)0)->DirectRockingCoefficient) == 4);

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

// Scalar fields named from the stores of constructor 0x665650 and the INI readers that load them
// (0x6691E0, 0x66BBB0, 0x66D530, 0x672AE0, ...); a name is the INI key read into that slot.
GG_STATIC_ASSERT(offsetof(RulesClass, AmmoCrateDamage) == 0xC);
GG_STATIC_ASSERT(offsetof(RulesClass, LargeVisceroid) == 0x10);
GG_STATIC_ASSERT(offsetof(RulesClass, SmallVisceroid) == 0x14);
GG_STATIC_ASSERT(offsetof(RulesClass, AttackingAircraftSightRange) == 0x18);
GG_STATIC_ASSERT(offsetof(RulesClass, TiberiumHeal) == 0x28);
GG_STATIC_ASSERT(offsetof(RulesClass, SelfHealInfantryFrames) == 0x30);
GG_STATIC_ASSERT(offsetof(RulesClass, SelfHealInfantryAmount) == 0x34);
GG_STATIC_ASSERT(offsetof(RulesClass, SelfHealUnitFrames) == 0x38);
GG_STATIC_ASSERT(offsetof(RulesClass, SelfHealUnitAmount) == 0x3C);
GG_STATIC_ASSERT(offsetof(RulesClass, FreeMCV) == 0x40);
GG_STATIC_ASSERT(offsetof(RulesClass, BerzerkAllowed) == 0x41);
GG_STATIC_ASSERT(offsetof(RulesClass, DeployDir) == 0x48);
GG_STATIC_ASSERT(offsetof(RulesClass, BarrelExplode) == 0x54);
GG_STATIC_ASSERT(offsetof(RulesClass, BarrelParticle) == 0x74);
GG_STATIC_ASSERT(offsetof(RulesClass, RadarEventColorSpeed) == 0x78);
GG_STATIC_ASSERT(offsetof(RulesClass, RadarEventMinRadius) == 0x7C);
GG_STATIC_ASSERT(offsetof(RulesClass, RadarEventSpeed) == 0x80);
GG_STATIC_ASSERT(offsetof(RulesClass, RadarEventRotationSpeed) == 0x84);
GG_STATIC_ASSERT(offsetof(RulesClass, FlashFrameTime) == 0x88);
GG_STATIC_ASSERT(offsetof(RulesClass, Wake) == 0x94);
GG_STATIC_ASSERT(offsetof(RulesClass, NukeTakeOff) == 0x98);
GG_STATIC_ASSERT(offsetof(RulesClass, FlamingInfantry) == 0xA0);
GG_STATIC_ASSERT(offsetof(RulesClass, InfantryHeadPop) == 0xA4);
GG_STATIC_ASSERT(offsetof(RulesClass, InfantryNuked) == 0xA8);
GG_STATIC_ASSERT(offsetof(RulesClass, InfantryVirus) == 0xAC);
GG_STATIC_ASSERT(offsetof(RulesClass, InfantryBrute) == 0xB0);
GG_STATIC_ASSERT(offsetof(RulesClass, InfantryMutate) == 0xB4);
GG_STATIC_ASSERT(offsetof(RulesClass, Behind) == 0xB8);
GG_STATIC_ASSERT(offsetof(RulesClass, AITriggerSuccessWeightDelta) == 0xC0);
GG_STATIC_ASSERT(offsetof(RulesClass, AITriggerFailureWeightDelta) == 0xC8);
GG_STATIC_ASSERT(offsetof(RulesClass, AITriggerTrackRecordCoefficient) == 0xD0);
GG_STATIC_ASSERT(offsetof(RulesClass, VeinholeMonsterStrength) == 0xD8);
GG_STATIC_ASSERT(offsetof(RulesClass, VeinholeGrowthRate) == 0xE0);
GG_STATIC_ASSERT(offsetof(RulesClass, VeinholeShrinkRate) == 0xE4);
GG_STATIC_ASSERT(offsetof(RulesClass, VeinAttack) == 0xE8);
GG_STATIC_ASSERT(offsetof(RulesClass, VeinDamage) == 0xEC);
GG_STATIC_ASSERT(offsetof(RulesClass, MaximumQueuedObjects) == 0xF0);
GG_STATIC_ASSERT(offsetof(RulesClass, AircraftFogReveal) == 0xF4);
GG_STATIC_ASSERT(offsetof(RulesClass, WoodCrateImg) == 0xF8);
GG_STATIC_ASSERT(offsetof(RulesClass, CrateImg) == 0xFC);
GG_STATIC_ASSERT(offsetof(RulesClass, WaterCrateImg) == 0x100);
GG_STATIC_ASSERT(offsetof(RulesClass, DigSound) == 0x174);
GG_STATIC_ASSERT(offsetof(RulesClass, CreateUnitSound) == 0x178);
GG_STATIC_ASSERT(offsetof(RulesClass, CreateInfantrySound) == 0x17C);
GG_STATIC_ASSERT(offsetof(RulesClass, CreateAircraftSound) == 0x180);
GG_STATIC_ASSERT(offsetof(RulesClass, BaseUnderAttackSound) == 0x184);
GG_STATIC_ASSERT(offsetof(RulesClass, GUIMoveOutSound) == 0x19C);
GG_STATIC_ASSERT(offsetof(RulesClass, GUIComboOpenSound) == 0x1A4);
GG_STATIC_ASSERT(offsetof(RulesClass, GUIComboCloseSound) == 0x1A8);
GG_STATIC_ASSERT(offsetof(RulesClass, GUICheckboxSound) == 0x1AC);
GG_STATIC_ASSERT(offsetof(RulesClass, ScoreAnimSound) == 0x1B0);
GG_STATIC_ASSERT(offsetof(RulesClass, IFVTransformSound) == 0x1B4);
GG_STATIC_ASSERT(offsetof(RulesClass, PsychicSensorDetectSound) == 0x1B8);
GG_STATIC_ASSERT(offsetof(RulesClass, BuildingGarrisonedSound) == 0x1BC);
GG_STATIC_ASSERT(offsetof(RulesClass, BuildingAbandonedSound) == 0x1C0);
GG_STATIC_ASSERT(offsetof(RulesClass, BuildingRepairedSound) == 0x1C4);
GG_STATIC_ASSERT(offsetof(RulesClass, PlaceBeaconSound) == 0x1CC);
GG_STATIC_ASSERT(offsetof(RulesClass, DefaultChronoSound) == 0x1D0);
GG_STATIC_ASSERT(offsetof(RulesClass, AddPlanningModeCommandSound) == 0x1D8);
GG_STATIC_ASSERT(offsetof(RulesClass, ExecutePlanSound) == 0x1DC);
GG_STATIC_ASSERT(offsetof(RulesClass, CrateMoneySound) == 0x1E4);
GG_STATIC_ASSERT(offsetof(RulesClass, CrateRevealSound) == 0x1E8);
GG_STATIC_ASSERT(offsetof(RulesClass, CrateFireSound) == 0x1EC);
GG_STATIC_ASSERT(offsetof(RulesClass, CrateArmourSound) == 0x1F0);
GG_STATIC_ASSERT(offsetof(RulesClass, CrateSpeedSound) == 0x1F4);
GG_STATIC_ASSERT(offsetof(RulesClass, CrateUnitSound) == 0x1F8);
GG_STATIC_ASSERT(offsetof(RulesClass, CratePromoteSound) == 0x1FC);
GG_STATIC_ASSERT(offsetof(RulesClass, ImpactWaterSound) == 0x200);
GG_STATIC_ASSERT(offsetof(RulesClass, ImpactLandSound) == 0x204);
GG_STATIC_ASSERT(offsetof(RulesClass, SinkingSound) == 0x208);
GG_STATIC_ASSERT(offsetof(RulesClass, BombTickingSound) == 0x20C);
GG_STATIC_ASSERT(offsetof(RulesClass, BombAttachSound) == 0x210);
GG_STATIC_ASSERT(offsetof(RulesClass, SpySatActivationSound) == 0x220);
GG_STATIC_ASSERT(offsetof(RulesClass, SpySatDeactivationSound) == 0x224);
GG_STATIC_ASSERT(offsetof(RulesClass, UpgradeVeteranSound) == 0x228);
GG_STATIC_ASSERT(offsetof(RulesClass, UpgradeEliteSound) == 0x22C);
GG_STATIC_ASSERT(offsetof(RulesClass, VoiceIFVRepair) == 0x230);
GG_STATIC_ASSERT(offsetof(RulesClass, SlavesFreeSound) == 0x234);
GG_STATIC_ASSERT(offsetof(RulesClass, SlaveMinerDeploySound) == 0x238);
GG_STATIC_ASSERT(offsetof(RulesClass, SlaveMinerUndeploySound) == 0x23C);
GG_STATIC_ASSERT(offsetof(RulesClass, BunkerWallsUpSound) == 0x240);
GG_STATIC_ASSERT(offsetof(RulesClass, RepairBridgeSound) == 0x248);
GG_STATIC_ASSERT(offsetof(RulesClass, PsychicDominatorActivateSound) == 0x24C);
GG_STATIC_ASSERT(offsetof(RulesClass, GeneticMutatorActivateSound) == 0x250);
GG_STATIC_ASSERT(offsetof(RulesClass, PsychicRevealActivateSound) == 0x254);
GG_STATIC_ASSERT(offsetof(RulesClass, MasterMindOverloadDeathSound) == 0x258);
GG_STATIC_ASSERT(offsetof(RulesClass, AirstrikeAbortSound) == 0x25C);
GG_STATIC_ASSERT(offsetof(RulesClass, AirstrikeAttackVoice) == 0x260);
GG_STATIC_ASSERT(offsetof(RulesClass, MindClearedSound) == 0x264);
GG_STATIC_ASSERT(offsetof(RulesClass, EnterGrinderSound) == 0x268);
GG_STATIC_ASSERT(offsetof(RulesClass, LeaveGrinderSound) == 0x26C);
GG_STATIC_ASSERT(offsetof(RulesClass, EnterBioReactorSound) == 0x270);
GG_STATIC_ASSERT(offsetof(RulesClass, LeaveBioReactorSound) == 0x274);
GG_STATIC_ASSERT(offsetof(RulesClass, ActivateSound) == 0x278);
GG_STATIC_ASSERT(offsetof(RulesClass, DeactivateSound) == 0x27C);
GG_STATIC_ASSERT(offsetof(RulesClass, SpyPlaneCamera) == 0x280);
GG_STATIC_ASSERT(offsetof(RulesClass, LetsDoTheTimeWarpOutAgain) == 0x284);
GG_STATIC_ASSERT(offsetof(RulesClass, LetsDoTheTimeWarpInAgain) == 0x288);
GG_STATIC_ASSERT(offsetof(RulesClass, DiskLaserChargeUp) == 0x28C);
GG_STATIC_ASSERT(offsetof(RulesClass, SpyPlaneCameraFrames) == 0x290);
GG_STATIC_ASSERT(offsetof(RulesClass, Dig) == 0x294);
GG_STATIC_ASSERT(offsetof(RulesClass, IonBlast) == 0x298);
GG_STATIC_ASSERT(offsetof(RulesClass, IonBeam) == 0x29C);
GG_STATIC_ASSERT(offsetof(RulesClass, WeatherConBoltExplosion) == 0x2F4);
GG_STATIC_ASSERT(offsetof(RulesClass, DominatorWarhead) == 0x2F8);
GG_STATIC_ASSERT(offsetof(RulesClass, DominatorFirstAnim) == 0x2FC);
GG_STATIC_ASSERT(offsetof(RulesClass, DominatorSecondAnim) == 0x300);
GG_STATIC_ASSERT(offsetof(RulesClass, DominatorFireAtPercentage) == 0x304);
GG_STATIC_ASSERT(offsetof(RulesClass, DominatorCaptureRange) == 0x308);
GG_STATIC_ASSERT(offsetof(RulesClass, DominatorDamage) == 0x30C);
GG_STATIC_ASSERT(offsetof(RulesClass, MindControlAttackLineFrames) == 0x310);
GG_STATIC_ASSERT(offsetof(RulesClass, DrainMoneyFrameDelay) == 0x314);
GG_STATIC_ASSERT(offsetof(RulesClass, DrainMoneyAmount) == 0x318);
GG_STATIC_ASSERT(offsetof(RulesClass, DrainAnimationType) == 0x31C);
GG_STATIC_ASSERT(offsetof(RulesClass, ControlledAnimationType) == 0x320);
GG_STATIC_ASSERT(offsetof(RulesClass, PermaControlledAnimationType) == 0x324);
GG_STATIC_ASSERT(offsetof(RulesClass, ChronoBlast) == 0x328);
GG_STATIC_ASSERT(offsetof(RulesClass, ChronoBlastDest) == 0x32C);
GG_STATIC_ASSERT(offsetof(RulesClass, ChronoPlacement) == 0x330);
GG_STATIC_ASSERT(offsetof(RulesClass, ChronoBeam) == 0x334);
GG_STATIC_ASSERT(offsetof(RulesClass, WarpIn) == 0x338);
GG_STATIC_ASSERT(offsetof(RulesClass, IronCurtainInvokeAnim) == 0x348);
GG_STATIC_ASSERT(offsetof(RulesClass, ForceShieldInvokeAnim) == 0x34C);
GG_STATIC_ASSERT(offsetof(RulesClass, PrerequisiteProcAlternate) == 0x400);
GG_STATIC_ASSERT(offsetof(RulesClass, GateUp) == 0x404);
GG_STATIC_ASSERT(offsetof(RulesClass, GateDown) == 0x408);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_40C) == 0x40C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_410) == 0x410);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_418) == 0x418);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_428) == 0x428);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_430) == 0x430);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_438) == 0x438);
GG_STATIC_ASSERT(offsetof(RulesClass, IonCannonDamage) == 0x490);
GG_STATIC_ASSERT(offsetof(RulesClass, RailgunDamageRadius) == 0x494);
GG_STATIC_ASSERT(offsetof(RulesClass, PrismType) == 0x498);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_49C) == 0x49C);
GG_STATIC_ASSERT(offsetof(RulesClass, PrismSupportMax) == 0x4A0);
GG_STATIC_ASSERT(offsetof(RulesClass, PrismSupportDelay) == 0x4A4);
GG_STATIC_ASSERT(offsetof(RulesClass, PrismSupportDuration) == 0x4A8);
GG_STATIC_ASSERT(offsetof(RulesClass, PrismSupportHeight) == 0x4AC);
GG_STATIC_ASSERT(offsetof(RulesClass, V3RocketPauseFrames) == 0x4B0);
GG_STATIC_ASSERT(offsetof(RulesClass, V3RocketTiltFrames) == 0x4B4);
GG_STATIC_ASSERT(offsetof(RulesClass, V3RocketPitchInitial) == 0x4B8);
GG_STATIC_ASSERT(offsetof(RulesClass, V3RocketPitchFinal) == 0x4BC);
GG_STATIC_ASSERT(offsetof(RulesClass, V3RocketTurnRate) == 0x4C0);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_4C4) == 0x4C4);
GG_STATIC_ASSERT(offsetof(RulesClass, V3RocketAcceleration) == 0x4C8);
GG_STATIC_ASSERT(offsetof(RulesClass, V3RocketAltitude) == 0x4CC);
GG_STATIC_ASSERT(offsetof(RulesClass, V3RocketDamage) == 0x4D0);
GG_STATIC_ASSERT(offsetof(RulesClass, V3RocketEliteDamage) == 0x4D4);
GG_STATIC_ASSERT(offsetof(RulesClass, V3RocketBodyLength) == 0x4D8);
GG_STATIC_ASSERT(offsetof(RulesClass, V3RocketLazyCurve) == 0x4DC);
GG_STATIC_ASSERT(offsetof(RulesClass, DMislPauseFrames) == 0x4E4);
GG_STATIC_ASSERT(offsetof(RulesClass, DMislTiltFrames) == 0x4E8);
GG_STATIC_ASSERT(offsetof(RulesClass, DMislPitchInitial) == 0x4EC);
GG_STATIC_ASSERT(offsetof(RulesClass, DMislPitchFinal) == 0x4F0);
GG_STATIC_ASSERT(offsetof(RulesClass, DMislTurnRate) == 0x4F4);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_4F8) == 0x4F8);
GG_STATIC_ASSERT(offsetof(RulesClass, DMislAcceleration) == 0x4FC);
GG_STATIC_ASSERT(offsetof(RulesClass, DMislAltitude) == 0x500);
GG_STATIC_ASSERT(offsetof(RulesClass, DMislDamage) == 0x504);
GG_STATIC_ASSERT(offsetof(RulesClass, DMislEliteDamage) == 0x508);
GG_STATIC_ASSERT(offsetof(RulesClass, DMislBodyLength) == 0x50C);
GG_STATIC_ASSERT(offsetof(RulesClass, DMislLazyCurve) == 0x510);
GG_STATIC_ASSERT(offsetof(RulesClass, CMislPauseFrames) == 0x518);
GG_STATIC_ASSERT(offsetof(RulesClass, CMislTiltFrames) == 0x51C);
GG_STATIC_ASSERT(offsetof(RulesClass, CMislPitchInitial) == 0x520);
GG_STATIC_ASSERT(offsetof(RulesClass, CMislPitchFinal) == 0x524);
GG_STATIC_ASSERT(offsetof(RulesClass, CMislTurnRate) == 0x528);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_52C) == 0x52C);
GG_STATIC_ASSERT(offsetof(RulesClass, CMislAcceleration) == 0x530);
GG_STATIC_ASSERT(offsetof(RulesClass, CMislAltitude) == 0x534);
GG_STATIC_ASSERT(offsetof(RulesClass, CMislDamage) == 0x538);
GG_STATIC_ASSERT(offsetof(RulesClass, CMislEliteDamage) == 0x53C);
GG_STATIC_ASSERT(offsetof(RulesClass, CMislBodyLength) == 0x540);
GG_STATIC_ASSERT(offsetof(RulesClass, CMislLazyCurve) == 0x544);
GG_STATIC_ASSERT(offsetof(RulesClass, CMislType) == 0x548);
GG_STATIC_ASSERT(offsetof(RulesClass, ZoomInFactor) == 0x550);
GG_STATIC_ASSERT(offsetof(RulesClass, ConditionRedSparkingProbability) == 0x558);
GG_STATIC_ASSERT(offsetof(RulesClass, ConditionYellowSparkingProbability) == 0x560);
GG_STATIC_ASSERT(offsetof(RulesClass, TiberiumExplosionDamage) == 0x568);
GG_STATIC_ASSERT(offsetof(RulesClass, TiberiumStrength) == 0x56C);
GG_STATIC_ASSERT(offsetof(RulesClass, MinLowPowerProductionSpeed) == 0x570);
GG_STATIC_ASSERT(offsetof(RulesClass, MaxLowPowerProductionSpeed) == 0x574);
GG_STATIC_ASSERT(offsetof(RulesClass, LowPowerPenaltyModifier) == 0x578);
GG_STATIC_ASSERT(offsetof(RulesClass, MultipleFactory) == 0x57C);
GG_STATIC_ASSERT(offsetof(RulesClass, TreeFlammability) == 0x588);
GG_STATIC_ASSERT(offsetof(RulesClass, MissileSpeedVar) == 0x590);
GG_STATIC_ASSERT(offsetof(RulesClass, ScrollMultiplier) == 0x5B8);
GG_STATIC_ASSERT(offsetof(RulesClass, CrewEscape) == 0x5C0);
GG_STATIC_ASSERT(offsetof(RulesClass, ShakeScreen) == 0x5C8);
GG_STATIC_ASSERT(offsetof(RulesClass, HoverHeight) == 0x5CC);
GG_STATIC_ASSERT(offsetof(RulesClass, HoverBob) == 0x5D0);
GG_STATIC_ASSERT(offsetof(RulesClass, HoverBoost) == 0x5D8);
GG_STATIC_ASSERT(offsetof(RulesClass, HoverAcceleration) == 0x5E0);
GG_STATIC_ASSERT(offsetof(RulesClass, HoverBrake) == 0x5E8);
GG_STATIC_ASSERT(offsetof(RulesClass, HoverDampen) == 0x5F0);
GG_STATIC_ASSERT(offsetof(RulesClass, PlacementDelay) == 0x5F8);
GG_STATIC_ASSERT(offsetof(RulesClass, TireVoxelDebris) == 0x61C);
GG_STATIC_ASSERT(offsetof(RulesClass, ScrapVoxelDebris) == 0x620);
GG_STATIC_ASSERT(offsetof(RulesClass, BridgeVoxelMax) == 0x624);
GG_STATIC_ASSERT(offsetof(RulesClass, CloakingStages) == 0x628);
GG_STATIC_ASSERT(offsetof(RulesClass, RevealTriggerRadius) == 0x62C);
GG_STATIC_ASSERT(offsetof(RulesClass, ShipSinkingWeight) == 0x630);
GG_STATIC_ASSERT(offsetof(RulesClass, IceCrackingWeight) == 0x638);
GG_STATIC_ASSERT(offsetof(RulesClass, IceBreakingWeight) == 0x640);
GG_STATIC_ASSERT(offsetof(RulesClass, CliffBackImpassability) == 0x664);
GG_STATIC_ASSERT(offsetof(RulesClass, VeteranRatio) == 0x668);
GG_STATIC_ASSERT(offsetof(RulesClass, VeteranCombat) == 0x670);
GG_STATIC_ASSERT(offsetof(RulesClass, VeteranSight) == 0x680);
GG_STATIC_ASSERT(offsetof(RulesClass, VeteranArmor) == 0x688);
GG_STATIC_ASSERT(offsetof(RulesClass, VeteranROF) == 0x690);
GG_STATIC_ASSERT(offsetof(RulesClass, VeteranCap) == 0x698);
GG_STATIC_ASSERT(offsetof(RulesClass, CloakSound) == 0x6A0);
GG_STATIC_ASSERT(offsetof(RulesClass, SellSound) == 0x6A4);
GG_STATIC_ASSERT(offsetof(RulesClass, GameClosed) == 0x6A8);
GG_STATIC_ASSERT(offsetof(RulesClass, SystemError) == 0x6B0);
GG_STATIC_ASSERT(offsetof(RulesClass, OptionsChanged) == 0x6B4);
GG_STATIC_ASSERT(offsetof(RulesClass, GameForming) == 0x6B8);
GG_STATIC_ASSERT(offsetof(RulesClass, PlayerLeft) == 0x6BC);
GG_STATIC_ASSERT(offsetof(RulesClass, PlayerJoined) == 0x6C0);
GG_STATIC_ASSERT(offsetof(RulesClass, Construction) == 0x6C8);
GG_STATIC_ASSERT(offsetof(RulesClass, BuildingDieSound) == 0x6E8);
GG_STATIC_ASSERT(offsetof(RulesClass, BuildingSlam) == 0x6EC);
GG_STATIC_ASSERT(offsetof(RulesClass, MovieOn) == 0x6F8);
GG_STATIC_ASSERT(offsetof(RulesClass, MovieOff) == 0x6FC);
GG_STATIC_ASSERT(offsetof(RulesClass, TeslaCharge) == 0x704);
GG_STATIC_ASSERT(offsetof(RulesClass, TeslaZap) == 0x708);
GG_STATIC_ASSERT(offsetof(RulesClass, GenericClick) == 0x70C);
GG_STATIC_ASSERT(offsetof(RulesClass, BuildingDamageSound) == 0x714);
GG_STATIC_ASSERT(offsetof(RulesClass, HealCrateSound) == 0x718);
GG_STATIC_ASSERT(offsetof(RulesClass, ChuteSound) == 0x71C);
GG_STATIC_ASSERT(offsetof(RulesClass, StopSound) == 0x720);
GG_STATIC_ASSERT(offsetof(RulesClass, StormSound) == 0x730);
GG_STATIC_ASSERT(offsetof(RulesClass, ShellButtonSlideSound) == 0x750);
GG_STATIC_ASSERT(offsetof(RulesClass, ChargeToDrainRatio) == 0x760);
GG_STATIC_ASSERT(offsetof(RulesClass, TrackedUphill) == 0x768);
GG_STATIC_ASSERT(offsetof(RulesClass, TrackedDownhill) == 0x770);
GG_STATIC_ASSERT(offsetof(RulesClass, WheeledUphill) == 0x778);
GG_STATIC_ASSERT(offsetof(RulesClass, WheeledDownhill) == 0x780);
GG_STATIC_ASSERT(offsetof(RulesClass, SpotlightSpeed) == 0x790);
GG_STATIC_ASSERT(offsetof(RulesClass, SpotlightAcceleration) == 0x798);
GG_STATIC_ASSERT(offsetof(RulesClass, SpotlightAngle) == 0x7A0);
GG_STATIC_ASSERT(offsetof(RulesClass, WindDirection) == 0x7AC);
GG_STATIC_ASSERT(offsetof(RulesClass, CameraRange) == 0x7B0);
GG_STATIC_ASSERT(offsetof(RulesClass, BuildingDrop) == 0x7C0);
GG_STATIC_ASSERT(offsetof(RulesClass, GDIPowerPlant) == 0x89C);
GG_STATIC_ASSERT(offsetof(RulesClass, NodRegularPower) == 0x8A0);
GG_STATIC_ASSERT(offsetof(RulesClass, NodAdvancedPower) == 0x8A4);
GG_STATIC_ASSERT(offsetof(RulesClass, ThirdPowerPlant) == 0x8A8);
GG_STATIC_ASSERT(offsetof(RulesClass, GDIWallDefense) == 0xAF8);
GG_STATIC_ASSERT(offsetof(RulesClass, GDIWallDefenseCoefficient) == 0xB00);
GG_STATIC_ASSERT(offsetof(RulesClass, NodBaseDefenseCoefficient) == 0xB08);
GG_STATIC_ASSERT(offsetof(RulesClass, GDIBaseDefenseCoefficient) == 0xB10);
GG_STATIC_ASSERT(offsetof(RulesClass, ComputerBaseDefenseResponse) == 0xB18);
GG_STATIC_ASSERT(offsetof(RulesClass, MaximumBaseDefenseValue) == 0xB1C);
GG_STATIC_ASSERT(offsetof(RulesClass, Smoke) == 0xBAC);
GG_STATIC_ASSERT(offsetof(RulesClass, Smoke_BB0) == 0xBB0);
GG_STATIC_ASSERT(offsetof(RulesClass, MoveFlash) == 0xBB4);
GG_STATIC_ASSERT(offsetof(RulesClass, SmallFire) == 0xBDC);
GG_STATIC_ASSERT(offsetof(RulesClass, LargeFire) == 0xBE0);
GG_STATIC_ASSERT(offsetof(RulesClass, Paratrooper) == 0xBE4);
GG_STATIC_ASSERT(offsetof(RulesClass, EliteFlashTimer) == 0xBE8);
GG_STATIC_ASSERT(offsetof(RulesClass, ChronoReinfDelay) == 0xBF0);
GG_STATIC_ASSERT(offsetof(RulesClass, SpyPowerBlackout) == 0xD64);
GG_STATIC_ASSERT(offsetof(RulesClass, SpyMoneyStealPercent) == 0xD68);
GG_STATIC_ASSERT(offsetof(RulesClass, AttackCursorOnDisguise) == 0xD6C);
GG_STATIC_ASSERT(offsetof(RulesClass, AISafeDistance) == 0xD74);
GG_STATIC_ASSERT(offsetof(RulesClass, HarvesterTooFarDistance) == 0xD78);
GG_STATIC_ASSERT(offsetof(RulesClass, ChronoHarvTooFarDistance) == 0xD7C);
GG_STATIC_ASSERT(offsetof(RulesClass, AIRestrictReplaceTime) == 0xDF0);
GG_STATIC_ASSERT(offsetof(RulesClass, ThreatPerOccupant) == 0xDF4);
GG_STATIC_ASSERT(offsetof(RulesClass, ApproachTargetResetMultiplier) == 0xDF8);
GG_STATIC_ASSERT(offsetof(RulesClass, CampaignMoneyDeltaEasy) == 0xDFC);
GG_STATIC_ASSERT(offsetof(RulesClass, CampaignMoneyDeltaHard) == 0xE00);
GG_STATIC_ASSERT(offsetof(RulesClass, NormalTargetingDelay) == 0xE08);
GG_STATIC_ASSERT(offsetof(RulesClass, AINavalYardAdjacency) == 0xE0C);
GG_STATIC_ASSERT(offsetof(RulesClass, MaximumBuildingPlacementFailures) == 0xE48);
GG_STATIC_ASSERT(offsetof(RulesClass, AISuperDefenseDistance) == 0xEE4);
GG_STATIC_ASSERT(offsetof(RulesClass, PurifierBonus) == 0xF3C);
GG_STATIC_ASSERT(offsetof(RulesClass, OccupyDamageMultiplier) == 0xF40);
GG_STATIC_ASSERT(offsetof(RulesClass, OccupyROFMultiplier) == 0xF44);
GG_STATIC_ASSERT(offsetof(RulesClass, BunkerDamageMultiplier) == 0xF4C);
GG_STATIC_ASSERT(offsetof(RulesClass, BunkerROFMultiplier) == 0xF50);
GG_STATIC_ASSERT(offsetof(RulesClass, OpenToppedDamageMultiplier) == 0xF58);
GG_STATIC_ASSERT(offsetof(RulesClass, FallingDamageMultiplier) == 0xF64);
GG_STATIC_ASSERT(offsetof(RulesClass, CurrentStrengthDamage) == 0xF68);
GG_STATIC_ASSERT(offsetof(RulesClass, Technician) == 0xF6C);
GG_STATIC_ASSERT(offsetof(RulesClass, Engineer) == 0xF70);
GG_STATIC_ASSERT(offsetof(RulesClass, Pilot) == 0xF74);
GG_STATIC_ASSERT(offsetof(RulesClass, AlliedCrew) == 0xF78);
GG_STATIC_ASSERT(offsetof(RulesClass, SovietCrew) == 0xF7C);
GG_STATIC_ASSERT(offsetof(RulesClass, ThirdCrew) == 0xF80);
GG_STATIC_ASSERT(offsetof(RulesClass, FlameDamage) == 0xF84);
GG_STATIC_ASSERT(offsetof(RulesClass, FlameDamage2) == 0xF88);
GG_STATIC_ASSERT(offsetof(RulesClass, NukeProjectile) == 0xF90);
GG_STATIC_ASSERT(offsetof(RulesClass, NukeDown) == 0xF94);
GG_STATIC_ASSERT(offsetof(RulesClass, MutateWarhead) == 0xF98);
GG_STATIC_ASSERT(offsetof(RulesClass, MutateExplosionWarhead) == 0xF9C);
GG_STATIC_ASSERT(offsetof(RulesClass, EMPulseWarhead) == 0xFA0);
GG_STATIC_ASSERT(offsetof(RulesClass, EMPulseProjectile) == 0xFA4);
GG_STATIC_ASSERT(offsetof(RulesClass, CrushWarhead) == 0xFAC);
GG_STATIC_ASSERT(offsetof(RulesClass, V3Warhead) == 0xFB0);
GG_STATIC_ASSERT(offsetof(RulesClass, DMislWarhead) == 0xFB4);
GG_STATIC_ASSERT(offsetof(RulesClass, V3EliteWarhead) == 0xFB8);
GG_STATIC_ASSERT(offsetof(RulesClass, DMislEliteWarhead) == 0xFBC);
GG_STATIC_ASSERT(offsetof(RulesClass, CMislWarhead) == 0xFC0);
GG_STATIC_ASSERT(offsetof(RulesClass, CMislEliteWarhead) == 0xFC4);
GG_STATIC_ASSERT(offsetof(RulesClass, IvanWarhead) == 0xFC8);
GG_STATIC_ASSERT(offsetof(RulesClass, IvanDamage) == 0xFCC);
GG_STATIC_ASSERT(offsetof(RulesClass, CanDetonateTimeBomb) == 0xFD4);
GG_STATIC_ASSERT(offsetof(RulesClass, CanDetonateDeathBomb) == 0xFD5);
GG_STATIC_ASSERT(offsetof(RulesClass, DeathWeapon) == 0xFDC);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_FE0) == 0xFE0);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_FE4) == 0xFE4);
GG_STATIC_ASSERT(offsetof(RulesClass, IronCurtainDuration) == 0xFE8);
GG_STATIC_ASSERT(offsetof(RulesClass, PsychicRevealRadius) == 0xFEC);
GG_STATIC_ASSERT(offsetof(RulesClass, IonCannonWarhead) == 0xFF0);
GG_STATIC_ASSERT(offsetof(RulesClass, VeinholeTypeClass) == 0xFF4);
GG_STATIC_ASSERT(offsetof(RulesClass, InfantryBlinkDisguiseTime) == 0x1014);
GG_STATIC_ASSERT(offsetof(RulesClass, DefaultLargeGreySmokeSystem) == 0x1018);
GG_STATIC_ASSERT(offsetof(RulesClass, DefaultSmallGreySmokeSystem) == 0x101C);
GG_STATIC_ASSERT(offsetof(RulesClass, DefaultLargeRedSmokeSystem) == 0x1024);
GG_STATIC_ASSERT(offsetof(RulesClass, DefaultSmallRedSmokeSystem) == 0x1028);
GG_STATIC_ASSERT(offsetof(RulesClass, DefaultDebrisSmokeSystem) == 0x102C);
GG_STATIC_ASSERT(offsetof(RulesClass, DefaultFireStreamSystem) == 0x1030);
GG_STATIC_ASSERT(offsetof(RulesClass, DefaultTestParticleSystem) == 0x1034);
GG_STATIC_ASSERT(offsetof(RulesClass, DefaultRepairParticleSystem) == 0x1038);
GG_STATIC_ASSERT(offsetof(RulesClass, MyEffectivenessCoefficientDefault) == 0x1040);
GG_STATIC_ASSERT(offsetof(RulesClass, TargetEffectivenessCoefficientDefault) == 0x1048);
GG_STATIC_ASSERT(offsetof(RulesClass, TargetSpecialThreatCoefficientDefault) == 0x1050);
GG_STATIC_ASSERT(offsetof(RulesClass, TargetStrengthCoefficientDefault) == 0x1058);
GG_STATIC_ASSERT(offsetof(RulesClass, TargetDistanceCoefficientDefault) == 0x1060);
GG_STATIC_ASSERT(offsetof(RulesClass, DumbMyEffectivenessCoefficient) == 0x1068);
GG_STATIC_ASSERT(offsetof(RulesClass, DumbTargetEffectivenessCoefficient) == 0x1070);
GG_STATIC_ASSERT(offsetof(RulesClass, DumbTargetSpecialThreatCoefficient) == 0x1078);
GG_STATIC_ASSERT(offsetof(RulesClass, DumbTargetStrengthCoefficient) == 0x1080);
GG_STATIC_ASSERT(offsetof(RulesClass, DumbTargetDistanceCoefficient) == 0x1088);
GG_STATIC_ASSERT(offsetof(RulesClass, EnemyHouseThreatBonus) == 0x1090);
GG_STATIC_ASSERT(offsetof(RulesClass, TurboBoost) == 0x1098);
GG_STATIC_ASSERT(offsetof(RulesClass, AttackInterval) == 0x10A0);
GG_STATIC_ASSERT(offsetof(RulesClass, AttackDelay) == 0x10A8);
GG_STATIC_ASSERT(offsetof(RulesClass, PowerEmergency) == 0x10B0);
GG_STATIC_ASSERT(offsetof(RulesClass, AirstripRatio) == 0x10B8);
GG_STATIC_ASSERT(offsetof(RulesClass, AirstripLimit) == 0x10C0);
GG_STATIC_ASSERT(offsetof(RulesClass, HelipadRatio) == 0x10C8);
GG_STATIC_ASSERT(offsetof(RulesClass, HelipadLimit) == 0x10D0);
GG_STATIC_ASSERT(offsetof(RulesClass, TeslaRatio) == 0x10D8);
GG_STATIC_ASSERT(offsetof(RulesClass, TeslaLimit) == 0x10E0);
GG_STATIC_ASSERT(offsetof(RulesClass, AARatio) == 0x10E8);
GG_STATIC_ASSERT(offsetof(RulesClass, AALimit) == 0x10F0);
GG_STATIC_ASSERT(offsetof(RulesClass, DefenseRatio) == 0x10F8);
GG_STATIC_ASSERT(offsetof(RulesClass, DefenseLimit) == 0x1100);
GG_STATIC_ASSERT(offsetof(RulesClass, WarRatio) == 0x1108);
GG_STATIC_ASSERT(offsetof(RulesClass, WarLimit) == 0x1110);
GG_STATIC_ASSERT(offsetof(RulesClass, BarracksRatio) == 0x1118);
GG_STATIC_ASSERT(offsetof(RulesClass, BarracksLimit) == 0x1120);
GG_STATIC_ASSERT(offsetof(RulesClass, RefineryLimit) == 0x1124);
GG_STATIC_ASSERT(offsetof(RulesClass, RefineryRatio) == 0x1128);
GG_STATIC_ASSERT(offsetof(RulesClass, BaseSizeAdd) == 0x1130);
GG_STATIC_ASSERT(offsetof(RulesClass, PowerSurplus) == 0x1134);
GG_STATIC_ASSERT(offsetof(RulesClass, InfantryReserve) == 0x1138);
GG_STATIC_ASSERT(offsetof(RulesClass, InfantryBaseMult) == 0x113C);
GG_STATIC_ASSERT(offsetof(RulesClass, SoloCrateMoney) == 0x1140);
GG_STATIC_ASSERT(offsetof(RulesClass, TreeStrength) == 0x1144);
GG_STATIC_ASSERT(offsetof(RulesClass, UnitCrateType) == 0x1148);
GG_STATIC_ASSERT(offsetof(RulesClass, PatrolScan) == 0x1150);
GG_STATIC_ASSERT(offsetof(RulesClass, DissolveUnfilledTeamDelay) == 0x1190);
GG_STATIC_ASSERT(offsetof(RulesClass, AIAlternateProductionCreditCutoff) == 0x1300);
GG_STATIC_ASSERT(offsetof(RulesClass, AIUseTurbineUpgradeProbability) == 0x13E8);
GG_STATIC_ASSERT(offsetof(RulesClass, CloakDelay) == 0x1410);
GG_STATIC_ASSERT(offsetof(RulesClass, GameSpeedBias) == 0x1418);
GG_STATIC_ASSERT(offsetof(RulesClass, BaseBias) == 0x1420);
GG_STATIC_ASSERT(offsetof(RulesClass, ExpSpread) == 0x1428);
GG_STATIC_ASSERT(offsetof(RulesClass, FireSupress) == 0x1430);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1438_1438) == 0x1438);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_143C) == 0x143C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1440) == 0x1440);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1444) == 0x1444);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1448) == 0x1448);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_144C) == 0x144C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1450) == 0x1450);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1454) == 0x1454);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1458) == 0x1458);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_145C) == 0x145C);
GG_STATIC_ASSERT(offsetof(RulesClass, AIBaseSpacing) == 0x1460);
GG_STATIC_ASSERT(offsetof(RulesClass, SilverCrate) == 0x1464);
GG_STATIC_ASSERT(offsetof(RulesClass, WoodCrate) == 0x1468);
GG_STATIC_ASSERT(offsetof(RulesClass, WaterCrate) == 0x146C);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1478_1478) == 0x1478);
GG_STATIC_ASSERT(offsetof(RulesClass, DropZoneAnim) == 0x147C);
GG_STATIC_ASSERT(offsetof(RulesClass, MinMoney) == 0x1480);
GG_STATIC_ASSERT(offsetof(RulesClass, MaxMoney) == 0x1488);
GG_STATIC_ASSERT(offsetof(RulesClass, MoneyIncrement) == 0x148C);
GG_STATIC_ASSERT(offsetof(RulesClass, MinUnitCount) == 0x1490);
GG_STATIC_ASSERT(offsetof(RulesClass, MaxUnitCount) == 0x1498);
GG_STATIC_ASSERT(offsetof(RulesClass, TechLevel) == 0x149C);
GG_STATIC_ASSERT(offsetof(RulesClass, AIDifficulty) == 0x14A4);
GG_STATIC_ASSERT(offsetof(RulesClass, AIPlayers) == 0x14A8);
GG_STATIC_ASSERT(offsetof(RulesClass, BridgeDestruction) == 0x14AC);
GG_STATIC_ASSERT(offsetof(RulesClass, ShadowGrow) == 0x14AD);
GG_STATIC_ASSERT(offsetof(RulesClass, Bases) == 0x14AF);
GG_STATIC_ASSERT(offsetof(RulesClass, TiberiumGrows) == 0x14B0);
GG_STATIC_ASSERT(offsetof(RulesClass, CaptureTheFlag) == 0x14B2);
GG_STATIC_ASSERT(offsetof(RulesClass, HarvesterTruce) == 0x14B3);
GG_STATIC_ASSERT(offsetof(RulesClass, MultiEngineer) == 0x14B4);
GG_STATIC_ASSERT(offsetof(RulesClass, DropZoneRadius) == 0x14BC);
GG_STATIC_ASSERT(offsetof(RulesClass, SavourDelay) == 0x14C8);
GG_STATIC_ASSERT(offsetof(RulesClass, BaseDefenseDelay) == 0x14D8);
GG_STATIC_ASSERT(offsetof(RulesClass, SuspendPriority) == 0x14E0);
GG_STATIC_ASSERT(offsetof(RulesClass, SuspendDelay) == 0x14E8);
GG_STATIC_ASSERT(offsetof(RulesClass, SurvivorRate) == 0x14F0);
GG_STATIC_ASSERT(offsetof(RulesClass, AlliedSurvivorDivisor) == 0x14F8);
GG_STATIC_ASSERT(offsetof(RulesClass, SovietSurvivorDivisor) == 0x14FC);
GG_STATIC_ASSERT(offsetof(RulesClass, ThirdSurvivorDivisor) == 0x1500);
GG_STATIC_ASSERT(offsetof(RulesClass, ReloadRate) == 0x1508);
GG_STATIC_ASSERT(offsetof(RulesClass, AutocreateTime) == 0x1510);
GG_STATIC_ASSERT(offsetof(RulesClass, BuildupTime) == 0x1518);
GG_STATIC_ASSERT(offsetof(RulesClass, HarvesterLoadRate) == 0x1520);
GG_STATIC_ASSERT(offsetof(RulesClass, HarvesterDumpRate) == 0x1528);
GG_STATIC_ASSERT(offsetof(RulesClass, AtomDamage) == 0x1530);
GG_STATIC_ASSERT(offsetof(RulesClass, GrowthRate) == 0x1638);
GG_STATIC_ASSERT(offsetof(RulesClass, ShroudRate) == 0x1640);
GG_STATIC_ASSERT(offsetof(RulesClass, FogRate) == 0x1648);
GG_STATIC_ASSERT(offsetof(RulesClass, IceGrowthRate) == 0x1650);
GG_STATIC_ASSERT(offsetof(RulesClass, VeinGrowthRate) == 0x1658);
GG_STATIC_ASSERT(offsetof(RulesClass, IceSolidifyFrameTime) == 0x1660);
GG_STATIC_ASSERT(offsetof(RulesClass, AmbientChangeRate) == 0x1668);
GG_STATIC_ASSERT(offsetof(RulesClass, AmbientChangeStep) == 0x1670);
GG_STATIC_ASSERT(offsetof(RulesClass, CrateRegen) == 0x1678);
GG_STATIC_ASSERT(offsetof(RulesClass, TimerWarning) == 0x1680);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1690) == 0x1690);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_1698) == 0x1698);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_16A0) == 0x16A0);
GG_STATIC_ASSERT(offsetof(RulesClass, SpeakDelay) == 0x16A8);
GG_STATIC_ASSERT(offsetof(RulesClass, DamageDelay) == 0x16B0);
GG_STATIC_ASSERT(offsetof(RulesClass, Incoming) == 0x16C0);
GG_STATIC_ASSERT(offsetof(RulesClass, MinDamage) == 0x16C4);
GG_STATIC_ASSERT(offsetof(RulesClass, MaxDamage) == 0x16C8);
GG_STATIC_ASSERT(offsetof(RulesClass, RepairRate) == 0x16E0);
GG_STATIC_ASSERT(offsetof(RulesClass, URepairRate) == 0x16E8);
GG_STATIC_ASSERT(offsetof(RulesClass, IRepairRate) == 0x16F0);
GG_STATIC_ASSERT(offsetof(RulesClass, IdleActionFrequency) == 0x1710);
GG_STATIC_ASSERT(offsetof(RulesClass, CloseEnough) == 0x1718);
GG_STATIC_ASSERT(offsetof(RulesClass, Stray) == 0x171C);
GG_STATIC_ASSERT(offsetof(RulesClass, RelaxedStray) == 0x1720);
GG_STATIC_ASSERT(offsetof(RulesClass, Crush) == 0x1728);
GG_STATIC_ASSERT(offsetof(RulesClass, CrateRadius) == 0x172C);
GG_STATIC_ASSERT(offsetof(RulesClass, HomingScatter) == 0x1730);
GG_STATIC_ASSERT(offsetof(RulesClass, RefundPercent) == 0x1738);
GG_STATIC_ASSERT(offsetof(RulesClass, BridgeStrength) == 0x1740);
GG_STATIC_ASSERT(offsetof(RulesClass, C4Delay) == 0x1750);
GG_STATIC_ASSERT(offsetof(RulesClass, CreditReserve) == 0x1758);
GG_STATIC_ASSERT(offsetof(RulesClass, PathDelay) == 0x1760);
GG_STATIC_ASSERT(offsetof(RulesClass, BlockagePathDelay) == 0x1768);
GG_STATIC_ASSERT(offsetof(RulesClass, MovieTime) == 0x1770);
GG_STATIC_ASSERT(offsetof(RulesClass, TiberiumShortScan) == 0x1778);
GG_STATIC_ASSERT(offsetof(RulesClass, TiberiumLongScan) == 0x177C);
GG_STATIC_ASSERT(offsetof(RulesClass, SlaveMinerShortScan) == 0x1780);
GG_STATIC_ASSERT(offsetof(RulesClass, SlaveMinerSlaveScan) == 0x1784);
GG_STATIC_ASSERT(offsetof(RulesClass, SlaveMinerLongScan) == 0x1788);
GG_STATIC_ASSERT(offsetof(RulesClass, SlaveMinerScanCorrection) == 0x178C);
GG_STATIC_ASSERT(offsetof(RulesClass, LightningDamage) == 0x1798);
GG_STATIC_ASSERT(offsetof(RulesClass, LightningStormDuration) == 0x179C);
GG_STATIC_ASSERT(offsetof(RulesClass, LightningHitDelay) == 0x17A0);
GG_STATIC_ASSERT(offsetof(RulesClass, LightningScatterDelay) == 0x17A4);
GG_STATIC_ASSERT(offsetof(RulesClass, LightningCellSpread) == 0x17A8);
GG_STATIC_ASSERT(offsetof(RulesClass, LightningSeparation) == 0x17AC);
GG_STATIC_ASSERT(offsetof(RulesClass, LightningPrintText) == 0x17B0);
GG_STATIC_ASSERT(offsetof(RulesClass, LightningWarhead) == 0x17B4);
GG_STATIC_ASSERT(offsetof(RulesClass, ForceShieldRadius) == 0x17B8);
GG_STATIC_ASSERT(offsetof(RulesClass, ForceShieldDuration) == 0x17BC);
GG_STATIC_ASSERT(offsetof(RulesClass, ForceShieldBlackoutDuration) == 0x17C0);
GG_STATIC_ASSERT(offsetof(RulesClass, ForceShieldPlayFadeSoundTime) == 0x17C4);
GG_STATIC_ASSERT(offsetof(RulesClass, MutateExplosion) == 0x17C8);
GG_STATIC_ASSERT(offsetof(RulesClass, CollapseChance) == 0x17CC);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_17D4_17D4) == 0x17D4);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_17D8) == 0x17D8);
GG_STATIC_ASSERT(offsetof(RulesClass, unknown_17DC) == 0x17DC);
GG_STATIC_ASSERT(offsetof(RulesClass, Paranoid) == 0x17E0);
GG_STATIC_ASSERT(offsetof(RulesClass, CurleyShuffle) == 0x17E1);
GG_STATIC_ASSERT(offsetof(RulesClass, BlendedFog) == 0x17E2);
GG_STATIC_ASSERT(offsetof(RulesClass, CompEasyBonus) == 0x17E3);
GG_STATIC_ASSERT(offsetof(RulesClass, FineDiffControl) == 0x17E4);
GG_STATIC_ASSERT(offsetof(RulesClass, TiberiumExplosive) == 0x17E5);
GG_STATIC_ASSERT(offsetof(RulesClass, EnemyHealth) == 0x17E6);
GG_STATIC_ASSERT(offsetof(RulesClass, AllyReveal) == 0x17E7);
GG_STATIC_ASSERT(offsetof(RulesClass, SeparateAircraft) == 0x17E8);
GG_STATIC_ASSERT(offsetof(RulesClass, TreeTargeting) == 0x17E9);
GG_STATIC_ASSERT(offsetof(RulesClass, NamedCivilians) == 0x17EA);
GG_STATIC_ASSERT(offsetof(RulesClass, PlayerAutoCrush) == 0x17EB);
GG_STATIC_ASSERT(offsetof(RulesClass, PlayerReturnFire) == 0x17EC);
GG_STATIC_ASSERT(offsetof(RulesClass, PlayerScatter) == 0x17ED);
GG_STATIC_ASSERT(offsetof(RulesClass, RevealByHeight) == 0x17EE);
GG_STATIC_ASSERT(offsetof(RulesClass, AllowShroudedSubteranneanMoves) == 0x17EF);
GG_STATIC_ASSERT(offsetof(RulesClass, ShroudGrow) == 0x17F0);
GG_STATIC_ASSERT(offsetof(RulesClass, NodAIBuildsWalls) == 0x17F1);
GG_STATIC_ASSERT(offsetof(RulesClass, AIBuildsWalls) == 0x17F2);
GG_STATIC_ASSERT(offsetof(RulesClass, UseMinDefenseRule) == 0x17F3);
GG_STATIC_ASSERT(offsetof(RulesClass, EMPulseSparkles) == 0x17F4);
GG_STATIC_ASSERT(offsetof(RulesClass, EngineerCaptureLevel) == 0x17F8);
GG_STATIC_ASSERT(offsetof(RulesClass, EngineerCaptureLevel_17FC) == 0x17FC);
GG_STATIC_ASSERT(offsetof(RulesClass, TalkBubbleTime) == 0x1800);
GG_STATIC_ASSERT(offsetof(RulesClass, RadApplicationDelay) == 0x1808);
GG_STATIC_ASSERT(offsetof(RulesClass, RadLevelMax) == 0x180C);
GG_STATIC_ASSERT(offsetof(RulesClass, RadLevelDelay) == 0x1810);
GG_STATIC_ASSERT(offsetof(RulesClass, RadLightDelay) == 0x1814);
GG_STATIC_ASSERT(offsetof(RulesClass, RadLevelFactor) == 0x1818);
GG_STATIC_ASSERT(offsetof(RulesClass, RadLightFactor) == 0x1820);
GG_STATIC_ASSERT(offsetof(RulesClass, RadTintFactor) == 0x1828);
GG_STATIC_ASSERT(offsetof(RulesClass, RadColorR) == 0x1830);
GG_STATIC_ASSERT(offsetof(RulesClass, RadSiteWarhead) == 0x1834);
GG_STATIC_ASSERT(offsetof(RulesClass, LaserTargetColor) == 0x18A4);
GG_STATIC_ASSERT(offsetof(RulesClass, IronCurtainColor) == 0x18A8);
GG_STATIC_ASSERT(offsetof(RulesClass, BerserkColor) == 0x18AC);
GG_STATIC_ASSERT(offsetof(RulesClass, ForceShieldColor) == 0x18B0);
GG_STATIC_ASSERT(offsetof(RulesClass, FallBackCoefficient) == 0x18B8);


GG_STATIC_ASSERT(offsetof(RulesClass, DetailMinFrameRateMovie) == 0x4);
GG_STATIC_ASSERT(offsetof(RulesClass, AICaptureLowMoneyMark) == 0xEBC);
GG_STATIC_ASSERT(offsetof(RulesClass, FogOfWar) == 0x14B7);
GG_STATIC_ASSERT(offsetof(RulesClass, TiberiumTransmogrify) == 0x1688);
GG_STATIC_ASSERT(offsetof(RulesClass, GuardModeStray) == 0x1724);
#endif
