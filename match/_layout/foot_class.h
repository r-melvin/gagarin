// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: FootClass ctor FUN_0x004D31E0 (chains TechnoClass ctor
//   FUN_0x006F2B40 at offset 0). EVERY offset below is read directly from a
//   field-init write in that ctor — the whole 0x520..0x6BF span is covered, and
//   the last (protected) member unused_6BC @0x6BC closes the object at 0x6C0.
//   Key confirmations from the ctor: PlanningPathIdx @0x520 (=-1),
//   MoveSoundAudioController ctor FUN_0x00405BE0(this+0x544), CurrentTunnelCoords
//   @0x568, SpeedMultiplier @0x580 (=1.0), the two DynamicVectorClass vptrs
//   @0x588/0x5AC (PTR_FUN_007e91ec), MegaMission @0x5C4 (=-1), PathDirections[0]
//   @0x5E0 (=-1), Locomotor @0x674, unknown_point3d_678 @0x678, TubeIndex @0x684
//   (=0xFF), ParalysisTimer @0x6A0, FrozenStill @0x6B6 (=1), and the four COM
//   vptrs written late (PTR_FUN_007e8c94 et al). Cross-checked vs YRpp
//   (which static_asserts sizeof==0x6C0).
//
//   NOTE: the binary places MoveSoundAudioController at 0x544 (ctor's
//   FUN_00405BE0 site), so there is an extra 4-byte slot at 0x540 that YRpp's
//   does not enumerate (YRpp lists only IsMoveSoundPlaying +
//   MoveSoundDelay before it). We follow the binary: a byte-zeroed slot exists
//   at 0x53C and a dword slot at 0x540, with the AudioController at 0x544.
//
// FootClass — base of every self-propelled object (units, infantry, aircraft;
// NOT buildings). Derives TechnoClass at offset 0 and adds the movement /
// pathfinding / locomotor / team state block from 0x520.
#ifndef GG_MATCH_LAYOUT_FOOT_CLASS_H
#define GG_MATCH_LAYOUT_FOOT_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "techno_class.h"     // TechnoClass spine + CDTimerClass + CoordStruct + AudioController
#include "vector_class.h"     // DynamicVectorClass

#include "cell.h"            // CellStruct, Cell

class TeamClass;

// FootClass  (0x520..0x6BF, sizeof = 0x6C0)
class FootClass : public TechnoClass
{
public:
    // Slots 309-340, introduced by FootClass (341 slots in all; retail table 0x7E8C94).
    // Names are placeholders; argument widths come from native RET n cleanup.
    // Slot 323 forwards its sixteen dwords to TechnoClass::FUN_00705E00.
    virtual void vf_309(int a1);                                   // 309 0x4DE750
    virtual void vf_310(FootClass* passenger);                     // 310 0x4DE760; 0x4DE742 passes the FootClass* that 0x473430 returned
    virtual void vf_311();                                         // 311 0x4DC790
    virtual void vf_312();                                         // 312 0x4DBFD0
    virtual bool vf_313();                                         // 313 0x41C060, native AL=false
    virtual void vf_314(int a1);                                   // 314 0x4DE7B0
    virtual void vf_315(int a1);                                   // 315 0x4DE940
    virtual void vf_316(int a1);                                   // 316 0x4D9FF0
    virtual void vf_317();                                         // 317 0x4DC030
    virtual void vf_318();                                         // 318 0x41C080
    virtual void vf_319(int a1);                                   // 319 0x4D55F0
    virtual void vf_320();                                         // 320 0x4D55C0
    virtual void vf_321();                                         // 321 0x4DB9B0
    virtual void vf_322(int a1, int a2, int a3);                   // 322 0x4DF7F0
    // Native slot 323 forwards 16 dwords to the typed TechnoClass helper at 0x41C090.
    virtual void vf_323(SHPStruct* a1, int a2, Point2D* a3, RectangleStruct* a4,
                        int a5, int a6, int a7, int a8, int a9, int a10,
                        int a11, int a12, int a13, int a14, int a15, int a16); // 323 0x41C090
    virtual void vf_324(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);// 324 0x4DAF10
    virtual void vf_325();                                         // 325 0x41C0F0
    virtual void vf_326();                                         // 326 0x41C100
    virtual void vf_327();                                         // 327 0x41C110
    virtual void vf_328(int a1);                                   // 328 0x41C120
    virtual void vf_329();                                         // 329 0x4D9C00
    virtual void vf_330(int a1, int a2, int a3);                   // 330 0x4DF040
    virtual void* vf_331(void* a1, int a2, int a3, int* a4);      // 331 0x4DEE80
    virtual void* vf_332(void* a1, int a2, int a3);                // 332 0x4DEE50
    virtual void vf_333(int a1, int a2);                           // 333 0x41C130
    virtual void vf_334();                                         // 334 0x4DB1A0
    virtual void vf_335(int a1);                                   // 335 0x4D5690
    virtual void vf_336(int a1);                                   // 336 0x41C140
    virtual void vf_337(int a1, int a2);                           // 337 0x4D3710
    virtual void vf_338();                                         // 338 0x4DBA30
    virtual void vf_339();                                         // 339 0x4DBA40
    virtual void vf_340(int a1);                                   // 340 0x4DDC60
    // FUNCTION: GAMEMD 0x4CBC40
    // Searches square rings of growing radius around `center`, starting from
    // the side facing `from`, for the first cell the object may enter
    // (ObjectClass::vf_107 returns 0). Rings run from `firstRadius` up to but
    // not including `endRadius`. Hidden result pointer first, RET 0x14.
    Cell FUN_004CBC40(CellStruct* from, CellStruct* center, int firstRadius, int endRadius);
    // GAMEMD 0x4DE710: takes the first passenger off Passengers @0x114 (0x473430) and calls
    // slot 310 with it when the type byte @0x805 is set and no passengers remain.
    FootClass* RemoveFirstPassenger();
    // GAMEMD 0x4E00B0 (RET 4): moves the jumpjet cell reservation to `coords`.
    void Jumpjet_OccupyCell(CellStruct coords);
    // GAMEMD 0x4DA230 (RET 4): owner, limbo, team, slot-97 kind (0x5B36E0) and RecruitableA tests.
    bool CanBeRecruited(HouseClass* house);
    // GAMEMD 0x4DA0E0 (RET 4): appends `target` to NavQueue @0x5AC.
    void QueueNavigationList(AbstractClass* target);
    // GAMEMD 0x4DA1C0: NavQueue.Clear() (vector slot 3).
    void ClearNavigationList();
    // GAMEMD 0x4DF0D0: zeroes unknown_5A0 and Destination.
    void AbortMotion();
    // GAMEMD 0x4DD890: a weed cell within `radius`, or the 0x8B3D88 sentinel; result through a hidden pointer.
    Cell FindWeedCell(int radius);
    // GAMEMD 0x4DDB90 (RET 4)
    bool MoveToWeed(int radius);
    // GAMEMD 0x4CBBA0 (RET 0x18): A* route from this object's cell to `dest`.
    void* FindPath(Cell* dest, int* buffer, int unused1, int unused2, int dirCount, int mode);
    // GAMEMD 0x7104F0: moves every passenger to this object's Location (slot 109).
    void UpdatePassengerCoords();
    // GAMEMD 0x629E90 (RET 0xC): three wake animations around (x, y, z).
    void CreateWakes(int x, int y, int z);

    int             PlanningPathIdx;                  // +0x520 (ctor = -1)
    CellStruct      WaypointNearbyAccessibleCellDelta;// +0x524 (4)
    CellStruct      WaypointCell;                     // +0x528 (4)
    unsigned int    unknown_52C;                      // +0x52C
    unsigned int    unknown_530;                      // +0x530
    unsigned int    unknown_534;                      // +0x534
    unsigned char   IsMoveSoundPlaying;               // +0x538 (bool)
    unsigned char   align_539[3];                     // +0x539
    unsigned char   unknown_bool_53C;                 // +0x53C (binary byte-zeroes this)
    unsigned char   align_53D[3];                     // +0x53D
    int             MoveSoundDelay;                   // +0x540
    AudioController MoveSoundAudioController;          // +0x544 (0x14; ctor FUN_00405BE0)
    CellStruct      CurrentMapCoords;                 // +0x558 (4)
    CellStruct      LastMapCoords;                    // +0x55C (4)
    CellStruct      LastFlightMapCoords;              // +0x560 (4)
    CellStruct      CurrentJumpjetMapCoords;          // +0x564 (4)
    CoordStruct     CurrentTunnelCoords;              // +0x568 (0xC)
    unsigned int    unused_574;                       // +0x574
    double          SpeedPercentage;                  // +0x578
    double          SpeedMultiplier;                  // +0x580 (ctor = 1.0)
    DynamicVectorClassLayout unknown_abstract_array_588;    // +0x588 (0x18; vptr 0x7E91EC)
    void*           unknown_5A0;                       // +0x5A0 AbstractClass*
    void*           Destination;                       // +0x5A4 AbstractClass*
    void*           LastDestination;                   // +0x5A8 AbstractClass*
    DynamicVectorClassLayout NavQueue;                       // +0x5AC (0x18; vptr 0x7E91EC)
    int             MegaMission;                       // +0x5C4 (Mission enum, ctor = -1)
    void*           MegaDestination;                   // +0x5C8 AbstractClass*
    void*           MegaTarget;                        // +0x5CC AbstractClass*
    unsigned char   unknown_5D0;                       // +0x5D0
    unsigned char   HaveAttackMoveTarget;              // +0x5D1 (bool)
    unsigned char   align_5D2[2];                      // +0x5D2
    TeamClass*      Team;                              // +0x5D4 (0x707CB0 calls TeamClass 0x6EA870 on it)
    FootClass*      NextTeamMember;                    // +0x5D8 (TeamClass::ScanLimit 0x6EC3A0 walks it)
    unsigned int    unknown_5DC;                       // +0x5DC
    int             PathDirections[24];                // +0x5E0 (0x60; [0] ctor = -1)
    CDTimerClass    PathDelayTimer;                    // +0x640 (0xC)
    int             PathWaitTimes;                     // +0x64C (ctor = 10)
    CDTimerClass    unknown_timer_650;                 // +0x650 (0xC)
    CDTimerClass    SightTimer;                        // +0x65C (0xC)
    CDTimerClass    BlockagePathTimer;                 // +0x668 (0xC)
    void*           Locomotor;                         // +0x674 ILocomotionPtr (COM ptr)
    CoordStruct     unknown_point3d_678;               // +0x678 (0xC)
    signed char     TubeIndex;                         // +0x684 (ctor = -1)
    signed char     TubeFaceIndex;                     // +0x685
    signed char     WaypointIndex;                     // +0x686
    unsigned char   ShouldScatterInNextIdle;           // +0x687 (bool)
    unsigned char   IsScanLimited;                     // +0x688 (bool)
    unsigned char   IsInitiated;                       // +0x689 (bool)
    unsigned char   ShouldScanForTarget;               // +0x68A (bool)
    unsigned char   unknown_bool_68B;                  // +0x68B (bool)
    unsigned char   IsDeploying;                       // +0x68C (bool)
    unsigned char   IsFiring;                          // +0x68D (bool)
    unsigned char   unknown_bool_68E;                  // +0x68E (bool)
    unsigned char   ShouldEnterAbsorber;               // +0x68F (bool)
    unsigned char   ShouldEnterOccupiable;             // +0x690 (bool)
    unsigned char   ShouldGarrisonStructure;           // +0x691 (bool)
    unsigned char   align_692[2];                      // +0x692
    void*           ParasiteEatingMe;                  // +0x694 FootClass*
    int             LastBeParasitedStartFrame;         // +0x698
    void*           ParasiteImUsing;                   // +0x69C ParasiteClass*
    CDTimerClass    ParalysisTimer;                    // +0x6A0 (0xC)
    unsigned char   unknown_bool_6AC;                  // +0x6AC (bool)
    unsigned char   IsAttackedByLocomotor;             // +0x6AD (bool)
    unsigned char   IsLetGoByLocomotor;                // +0x6AE (bool)
    unsigned char   unknown_bool_6AF;                  // +0x6AF (bool)
    unsigned char   unknown_bool_6B0;                  // +0x6B0 (bool)
    unsigned char   unknown_bool_6B1;                  // +0x6B1 (bool)
    unsigned char   unknown_bool_6B2;                  // +0x6B2 (bool)
    unsigned char   unknown_bool_6B3;                  // +0x6B3 (bool)
    unsigned char   unknown_bool_6B4;                  // +0x6B4 (bool)
    unsigned char   IsCrushingSomething;               // +0x6B5 (bool)
    unsigned char   FrozenStill;                       // +0x6B6 (bool, ctor = 1)
    unsigned char   IsWaitingBlockagePath;             // +0x6B7 (bool)
    unsigned char   unknown_bool_6B8;                  // +0x6B8 (bool)
    unsigned char   align_6B9[3];                      // +0x6B9
    unsigned int    unused_6BC;                        // +0x6BC (PROTECTED_PROPERTY)

    // Overrides of base slots reached by InfantryClass (retail table 0x7E8C94).
    virtual void vf_10(void* a1, bool a2);                         // 10  0x4D9960
    virtual void vf_13(Obj_004A1D30* crc);                         // 13  0x4DBAD0
    virtual bool vf_53();                                          // 53  0x4DB260
    virtual int vf_138();                                          // 138 0x4D5350
    virtual int vf_139();                                          // 139 0x4D4200
    virtual AbstractClass* vf_241(unsigned int threat, CoordStruct* coord, bool a3); // 241 0x4D9920 (IsScanLimited @0x688 wrapper of 0x6F8DF0)
    // Native primary slot 288: RET 8; this override receives the target and flag.
    virtual void SetDestination(AbstractClass* target, bool a2);   // 288 0x4D94B0
};

GG_STATIC_ASSERT(offsetof(FootClass, PlanningPathIdx)            == 0x520);
GG_STATIC_ASSERT(offsetof(FootClass, unknown_52C)               == 0x52C);
GG_STATIC_ASSERT(offsetof(FootClass, MoveSoundAudioController)   == 0x544);
GG_STATIC_ASSERT(offsetof(FootClass, CurrentMapCoords)          == 0x558);
GG_STATIC_ASSERT(offsetof(FootClass, CurrentTunnelCoords)       == 0x568);
GG_STATIC_ASSERT(offsetof(FootClass, SpeedPercentage)           == 0x578);
GG_STATIC_ASSERT(offsetof(FootClass, SpeedMultiplier)           == 0x580);
GG_STATIC_ASSERT(offsetof(FootClass, unknown_abstract_array_588)== 0x588);
GG_STATIC_ASSERT(offsetof(FootClass, Destination)               == 0x5A4);
GG_STATIC_ASSERT(offsetof(FootClass, NavQueue)                  == 0x5AC);
GG_STATIC_ASSERT(offsetof(FootClass, MegaMission)               == 0x5C4);
GG_STATIC_ASSERT(offsetof(FootClass, Team)                      == 0x5D4);
GG_STATIC_ASSERT(offsetof(FootClass, NextTeamMember)            == 0x5D8);
GG_STATIC_ASSERT(offsetof(FootClass, PathDirections)            == 0x5E0);
GG_STATIC_ASSERT(offsetof(FootClass, PathDelayTimer)            == 0x640);
GG_STATIC_ASSERT(offsetof(FootClass, BlockagePathTimer)         == 0x668);
GG_STATIC_ASSERT(offsetof(FootClass, Locomotor)                 == 0x674);
GG_STATIC_ASSERT(offsetof(FootClass, unknown_point3d_678)       == 0x678);
GG_STATIC_ASSERT(offsetof(FootClass, TubeIndex)                 == 0x684);
GG_STATIC_ASSERT(offsetof(FootClass, ParalysisTimer)            == 0x6A0);
GG_STATIC_ASSERT(offsetof(FootClass, FrozenStill)               == 0x6B6);
GG_STATIC_ASSERT(offsetof(FootClass, unused_6BC)                == 0x6BC);
GG_STATIC_ASSERT(sizeof(FootClass)                              == 0x6C0);

#endif  // GG_MATCH_LAYOUT_FOOT_CLASS_H
