// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   The shared spine of the COM locomotor family. Everything here was read back
//   out of the user's retail gamemd.exe v1.001 (sha256 1cdd1180...4298c) through
//   the local Ghidra CLI; each member carries the address of the instruction
//   that proves it. Nothing rests on scripts/data/*.json, which are leads.
//
//   This header exists so the ten sibling locomotor layout headers
//   (drive/ship/hover/jumpjet/rocket/teleport/walk/droppod/mech/tunnel) do not
//   each re-derive the 0x18-byte base. match/_layout/fly_locomotion_class.h
//   predates it and carries its own copy behind the SAME
//   GG_MATCH_LAYOUT_LOCOMOTIONCLASS_DEFINED guard with the identical
//   definition, so the two compose in either include order and neither file has
//   to be touched.
//
//   THE TWO BASE SHAPES. RTTI in the binary splits the family in half, and the
//   split is a LAYOUT difference, not a cosmetic one. Read from each class's
//   complete object locator set (four bytes below each vtable is the locator,
//   +0xC the type descriptor, the name eight bytes in):
//
//     two locators - base offsets 0 (IPersistStream) and 4 (ILocomotion):
//       FlyLocomotionClass, HoverLocomotionClass, RocketLocomotionClass,
//       MechLocomotionClass, TunnelLocomotionClass.
//       RTTI identifies LocomotionClass at base offset 0; their own data starts
//       at 0x18. The legacy layout mirrors below use a uniquely named
//       address-local storage view for that prefix.
//
//     three locators - base offsets 0, 4 AND 0x18 (IPiggyback):
//       DriveLocomotionClass   (0x007FFEB0 / 0x007FFDE8 / 0x007FFDD0)
//       ShipLocomotionClass    (0x00809408 / 0x008093A0 / 0x00809388)
//       WalkLocomotionClass    (0x0080D2A8 / 0x0080D240 / 0x0080D228)
//       TeleportLocomotionClass(0x0080C1E0 / 0x0080C178 / 0x0080C160)
//       JumpjetLocomotionClass (0x00804CF0 / 0x00804C88 / 0x00804C70)
//       DropPodLocomotionClass (0x008000A8 / 0x00800040 / 0x00800028)
//       -> 0x18 is a THIRD VPTR, and their own data starts at 0x1C. Each of the
//          six constructors stores it: e.g. `MOV DWORD PTR [ESI+0x18],0x7E7E8C`
//          @0x004AF5CF in DriveLocomotionClass::DriveLocomotionClass.
//       RTTI identifies LocomotionPiggybackBase as their storage base at +0x18;
//       the legacy layout mirrors below use that address-local view.
//
//   INTERFACE-RELATIVE READS. Almost every method in the family is an
//   __stdcall on the ILocomotion interface at base offset 4, so a body reading
//   `[ESP+0x4]` has the interface pointer and every displacement in it is
//   OBJECT OFFSET MINUS 4. The citations in the sibling headers state the
//   object offset and give the instruction that proves it; where the
//   instruction is interface-relative it is marked "(if+N)".
#ifndef GG_MATCH_LAYOUT_LOCOMOTION_CLASS_H
#define GG_MATCH_LAYOUT_LOCOMOTION_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// CoordStruct - lepton 3-space coordinate (sizeof = 0xC). Self-guarded so this
// header composes with techno_class.h / fly_locomotion_class.h / bounce_class.h.
#include "coord_struct.h"
GG_STATIC_ASSERT(sizeof(CoordStruct) == 0xC);

// CDTimerClass = TimerStruct<FrameTimer> (sizeof = 0xC). Definition identical to
// match/_layout/mission_class.h. Its signature in a locomotor constructor is
// unmistakable and recurs six times in this family: StartTime <- the global
// frame counter at 0x00A8ED84, the middle dword NEVER written (it is the empty
// FrameTimer clock slot), TimeLeft <- 0.
#include "frame_timer.h"
GG_STATIC_ASSERT(offsetof(CDTimerClass, TimeLeft) == 0x08);
GG_STATIC_ASSERT(sizeof(CDTimerClass)             == 0xC);

// RateTimer = CDTimerClass + Rate (sizeof = 0x10). Definition identical to
// match/_layout/building_class.h. Proven to be the shape at
// DriveLocomotionClass+0x24 by DriveLocomotionClass::Draw_Matrix 0x004AFF60,
// which reads StartTime (if+0x20) @0x004AFF85, TimeLeft (if+0x28) @0x004AFF88
// and then FIDIVs the elapsed fraction by Rate (if+0x2c) @0x004AFFAC.
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

#include "facing_class.h"

// ---------------------------------------------------------------------------
// LocomotionClass - the shared COM spine (sizeof = 0x18).
//
// Oracle: the base constructor 0x0055A6C0, whose whole body is eight
// instructions and writes every member:
//     0055a6c6  MOV DWORD PTR [EAX+0x8],ECX    (ECX = 0)
//     0055a6c9  MOV DWORD PTR [EAX+0xC],ECX
//     0055a6cc  MOV BYTE  PTR [EAX+0x10],DL    (DL = 1)
//     0055a6cf  MOV BYTE  PTR [EAX+0x11],DL
//     0055a6d2  MOV DWORD PTR [EAX+0x14],ECX
//     0055a6d5  MOV DWORD PTR [EAX],0x7EAEC0
//     0055a6db  MOV DWORD PTR [EAX+0x4],0x7EADF4
// Every one of the eleven derived constructors calls it first and then writes
// its own fields from 0x18 (two-locator classes) or 0x1C (three-locator
// classes) upward, which is what fixes sizeof at 0x18. LocomotionClass has its
// own two RTTI locators, base offsets 0 (vtable 0x007EAEC0, locator 0x008032E8)
// and 4 (vtable 0x007EADF4, locator 0x008032A0).
// ---------------------------------------------------------------------------
#ifndef GG_MATCH_LAYOUT_LOCOMOTIONCLASS_DEFINED
#define GG_MATCH_LAYOUT_LOCOMOTIONCLASS_DEFINED
struct LocomotionLayoutView_0055A6C0
{
    void* PersistVptr;      // +0x00  IPersistStream; ctor @0x0055A6D5 = 0x7EAEC0
    void* LocomotorVptr;    // +0x04  ILocomotion;    ctor @0x0055A6DB = 0x7EADF4
    void* Owner;            // +0x08  FootClass*; ctor @0x0055A6C6 (= 0)
    void* LinkedTo;         // +0x0C  FootClass*; ctor @0x0055A6C9 (= 0);
                            //        read as [reg+0xC] object-relative and
                            //        [reg+0x8] through the locomotor interface
                            //        throughout the family
    char  Powered;          // +0x10  ctor @0x0055A6CC (= 1)
    char  Dirty;            // +0x11  ctor @0x0055A6CF (= 1); read by the shared
                            //        Is_Dirty 0x004B4C30 (`MOV DL,[ECX+0x11]`
                            //        @0x004B4C36), which every persist vtable
                            //        in the family carries at slot +0x10
    char  unknown_12[2];    // +0x12  never written, never read - alignment
    int   RefCount;         // +0x14  ctor @0x0055A6D2 (= 0)
};
GG_STATIC_ASSERT(offsetof(LocomotionLayoutView_0055A6C0, LocomotorVptr) == 0x04);
GG_STATIC_ASSERT(offsetof(LocomotionLayoutView_0055A6C0, Owner)         == 0x08);
GG_STATIC_ASSERT(offsetof(LocomotionLayoutView_0055A6C0, LinkedTo)      == 0x0C);
GG_STATIC_ASSERT(offsetof(LocomotionLayoutView_0055A6C0, Powered)       == 0x10);
GG_STATIC_ASSERT(offsetof(LocomotionLayoutView_0055A6C0, Dirty)         == 0x11);
GG_STATIC_ASSERT(offsetof(LocomotionLayoutView_0055A6C0, RefCount)      == 0x14);
GG_STATIC_ASSERT(sizeof(LocomotionLayoutView_0055A6C0)                  == 0x18);
#endif

// ---------------------------------------------------------------------------
// LocomotionPiggybackBase (sizeof = 0x1C) - LAYOUT CONSTRUCT, NOT AN RTTI CLASS
// NAME. There is no such class in the binary; this is the shared shape of the
// six locomotors whose RTTI carries a third complete object locator at base
// offset 0x18 (IPiggyback). The name is deliberately not a *Class name so it
// cannot be mistaken for a recovered symbol.
// ---------------------------------------------------------------------------
#ifndef GG_MATCH_LAYOUT_LOCOMOTIONPIGGYBACKBASE_DEFINED
#define GG_MATCH_LAYOUT_LOCOMOTIONPIGGYBACKBASE_DEFINED
struct LocomotionPiggybackBase : LocomotionLayoutView_0055A6C0
{
    void* PiggybackVptr;    // +0x18  IPiggyback; stored by each of the six
                            //        constructors - Drive @0x004AF5CF
                            //        (=0x7E7E8C), Ship @0x0069ECDF (=0x7F2D68),
                            //        Walk @0x0075AAEC (=0x7F69D4), Teleport
                            //        @0x0071806B (=0x7F4FDC), Jumpjet
                            //        @0x0054ACD0 (=0x7ECD44), DropPod
                            //        @0x004B5AEA (=0x7E8254)
};
GG_STATIC_ASSERT(offsetof(LocomotionPiggybackBase, PiggybackVptr) == 0x18);
GG_STATIC_ASSERT(sizeof(LocomotionPiggybackBase)                  == 0x1C);
#endif

#endif  // GG_MATCH_LAYOUT_LOCOMOTION_CLASS_H
