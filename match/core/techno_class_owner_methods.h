// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x70F7E0 / 0x70F820 /
//   0x734270). Names cross-checked against YRpp (every offset reconfirmed numerically below from the matched
//   bodies). Only the members the matched bodies touch are modelled; the full
//   layout is the committed spine (match/_layout/techno_class.h) / P2.
//
// This TU matches three TechnoClass query/mutator helpers:
//   * TargetingTimerFinished — true once the inlined TargetingTimer countdown
//     (a CDTimerClass::GetTimeLeft) has reached 0.
//   * GetOriginalOwner       — the house that originally owned this object:
//     defers to the mind-controller's CaptureManager when mind-controlled,
//     else OriginallyOwnedByHouse when controlled by a house, else the Owner.
//   * ClearSidebarTabObject   — clears this object out of the two sidebar
//     "tab object" globals (and clears both when invoked on a null this).
// Confirmed offsets (from the matched bodies):
//   * TechnoClass::TargetingTimer.StartTime  +0x180  `MOV EDX,[ECX+0x180]`
//   * TechnoClass::TargetingTimer.TimeLeft   +0x188  `MOV EAX,[ECX+0x188]`
//   * TechnoClass::Owner                     +0x21C  `MOV EAX,[ECX+0x21C]`
//   * TechnoClass::CaptureManager            +0x2BC  `MOV ECX,[EAX+0x2BC]`
//   * TechnoClass::MindControlledBy          +0x2C0  `MOV EAX,[ECX+0x2C0]`
//   * TechnoClass::MindControlledByHouse     +0x2CC  `MOV EAX,[ECX+0x2CC]`
//   * TechnoClass::OriginallyOwnedByHouse    +0x2E0  `MOV EAX,[ECX+0x2E0]`
//   * Unsorted::CurrentFrame  global @ 0x00A8ED84   `MOV ECX,[0x00A8ED84]`
//   * sidebar tab object globals @ 0x00B0FE5C / 0x00B0FE60
#ifndef GG_MATCH_CORE_TECHNO_CLASS_OWNER_METHODS_H
#define GG_MATCH_CORE_TECHNO_CLASS_OWNER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#ifndef NULL
#define NULL 0
#endif

class TechnoClass;
class HouseClass;

// Unsorted::CurrentFrame — global game-frame counter @ 0x00A8ED84. Declared-only
// so cl emits a reloc-normalised absolute load.
#include "../core/frame_counter.h"

// ---------------------------------------------------------------------------
// CDTimerClass — count-down frame timer (sizeof 0xC). StartTime @0, an
// accumulator/clock slot @4 (untouched here), TimeLeft @8. Matches the spine.
// ---------------------------------------------------------------------------
struct CDTimerClass
{
    int StartTime;    // +0x00
    int unknown_04;   // +0x04
    int TimeLeft;     // +0x08
};
GG_STATIC_ASSERT(offsetof(CDTimerClass, TimeLeft) == 0x08);
GG_STATIC_ASSERT(sizeof(CDTimerClass)             == 0x0C);

// ---------------------------------------------------------------------------
// CaptureManagerClass — only its GetOriginalOwner lookup is referenced (the
// mind-controller's capture manager resolves the original house). Declared-only
// so cl emits a reloc-normalised CALL.
// ---------------------------------------------------------------------------
class CaptureManagerClass
{
public:
    HouseClass* GetOriginalOwner(TechnoClass* unit);   // GAMEMD 0x4722F0 (referenced; matched elsewhere)
};

// ---------------------------------------------------------------------------
// TechnoClass — minimal offset-pinned model for the three matched helpers.
// The pad gaps stand in for the full RadioClass/MissionClass/ObjectClass/
// TechnoClass spine (match/_layout/techno_class.h); only the touched members
// are named.
// ---------------------------------------------------------------------------
class TechnoClass
{
public:
    // Declared ascending by retail address (reccmp/isle TU discipline).
    bool        TargetingTimerFinished() const;   // GAMEMD 0x70F7E0 __thiscall
    HouseClass* GetOriginalOwner() const;         // GAMEMD 0x70F820 __thiscall
    void        ClearSidebarTabObject();          // GAMEMD 0x734270 __thiscall

    char                _pad_000[0x180];               // +0x000 .. +0x17F
    CDTimerClass        TargetingTimer;                // +0x180  (0xC)
    char                _pad_18C[0x21C - 0x18C];       // +0x18C .. +0x21B
    HouseClass*         Owner;                         // +0x21C  HouseClass*
    char                _pad_220[0x2BC - 0x220];       // +0x220 .. +0x2BB
    CaptureManagerClass* CaptureManager;               // +0x2BC  CaptureManagerClass*
    TechnoClass*        MindControlledBy;              // +0x2C0  TechnoClass*
    char                _pad_2C4[0x2CC - 0x2C4];       // +0x2C4 .. +0x2CB
    HouseClass*         MindControlledByHouse;         // +0x2CC  HouseClass*
    char                _pad_2D0[0x2E0 - 0x2D0];       // +0x2D0 .. +0x2DF
    HouseClass*         OriginallyOwnedByHouse;        // +0x2E0  HouseClass*
};

GG_STATIC_ASSERT(offsetof(TechnoClass, TargetingTimer)         == 0x180);
GG_STATIC_ASSERT(offsetof(TechnoClass, Owner)                  == 0x21C);
GG_STATIC_ASSERT(offsetof(TechnoClass, CaptureManager)         == 0x2BC);
GG_STATIC_ASSERT(offsetof(TechnoClass, MindControlledBy)       == 0x2C0);
GG_STATIC_ASSERT(offsetof(TechnoClass, MindControlledByHouse)  == 0x2CC);
GG_STATIC_ASSERT(offsetof(TechnoClass, OriginallyOwnedByHouse) == 0x2E0);

#endif  // GG_MATCH_CORE_TECHNO_CLASS_OWNER_METHODS_H
