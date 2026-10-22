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

// CellStruct — 2D short cell coordinate (sizeof = 4). Self-guarded for reuse.
#ifndef GG_MATCH_LAYOUT_CELLSTRUCT_DEFINED
#define GG_MATCH_LAYOUT_CELLSTRUCT_DEFINED
struct CellStruct
{
    short X;   // +0x00
    short Y;   // +0x02
};
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);
#endif

// FootClass  (0x520..0x6BF, sizeof = 0x6C0)
struct FootClass : TechnoClass
{
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
    void*           Team;                              // +0x5D4 TeamClass*
    void*           NextTeamMember;                    // +0x5D8 FootClass*
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
