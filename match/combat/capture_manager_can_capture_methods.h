// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets and slots read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x471C90: on the manager `[EBX+0x48]`
//   (Owner), `[EBX+0x40]` (InfiniteControl byte), `[EBX+0x3C]`
//   (MaxControlNodes), `[EBX+0x34]` (ControlNodes.Count); on the target
//   techno the slots `[EAX+0x3C]`, `[EAX+0x84]` (returns the type, whose
//   byte `[EAX+0xD35]` is tested), `[EDX+0x2C]` (compared to 1) and
//   `[EAX+0x160]` (AL result), the members `[ESI+0x2E4]`, `[ESI+0x2CC]` and
//   `[ESI+0xAC]` (compared to 0x13 / 0x12), and the direct call 0x7105E0.
//   Names cross-checked against YRpp CaptureManagerClass.h / TechnoClass.h /
//   TechnoTypeClass.h (consult-only, NO LICENSE); every offset reconfirmed
//   here and against match/_layout/techno_class.h (MindControlledByHouse
//   @0x2CC, BunkerLinkedItem @0x2E4) and mission_class.h (CurrentMission
//   @0xAC).
#ifndef GG_MATCH_COMBAT_CAPTURE_MANAGER_CAN_CAPTURE_METHODS_H
#define GG_MATCH_COMBAT_CAPTURE_MANAGER_CAN_CAPTURE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// TechnoTypeClass — only the byte at +0xD35 (ImmuneToPsionics) is read.
struct Type_00471C90
{
    char _pad000[0xD35];       // +0x0000
    char ImmuneToPsionics;     // +0x0D35
};
GG_STATIC_ASSERT(offsetof(Type_00471C90, ImmuneToPsionics) == 0xD35);

// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_00471C90;

// TechnoClass — the capture target. Only the members this predicate reads.
struct Techno_00471C90
{
    Vtbl_00471C90* Vtbl;                 // +0x0000
    char  _pad004[0xAC - 0x04];          // +0x0004
    int   CurrentMission;                // +0x00AC
    char  _pad0B0[0x2CC - 0xB0];         // +0x00B0
    void* MindControlledByHouse;         // +0x02CC
    char  _pad2D0[0x2E4 - 0x2D0];        // +0x02D0
    Techno_00471C90* BunkerLinkedItem;   // +0x02E4

    // FUNCTION: GAMEMD 0x7105E0 (decl; reloc) — TechnoClass::IsMindControlled.
    bool IsMindControlled() const;
};
GG_STATIC_ASSERT(offsetof(Techno_00471C90, CurrentMission)       == 0xAC);
GG_STATIC_ASSERT(offsetof(Techno_00471C90, MindControlledByHouse) == 0x2CC);
GG_STATIC_ASSERT(offsetof(Techno_00471C90, BunkerLinkedItem)     == 0x2E4);

typedef int             (Techno_00471C90::*Fn02C_00471C90)();   // WhatAmI
typedef void*           (Techno_00471C90::*Fn03C_00471C90)();   // owning house
typedef Type_00471C90*  (Techno_00471C90::*Fn084_00471C90)();   // GetTechnoType
typedef bool            (Techno_00471C90::*Fn160_00471C90)();   // IsIronCurtained

struct Vtbl_00471C90
{
    char           _pad000[0x2C];             // +0x0000
    Fn02C_00471C90 WhatAmI;                   // +0x002C
    char           _pad030[0x3C - 0x30];      // +0x0030
    Fn03C_00471C90 GetOwningHouse;            // +0x003C
    char           _pad040[0x84 - 0x40];      // +0x0040
    Fn084_00471C90 GetTechnoType;             // +0x0084
    char           _pad088[0x160 - 0x88];     // +0x0088
    Fn160_00471C90 IsIronCurtained;           // +0x0160
};
GG_STATIC_ASSERT(offsetof(Vtbl_00471C90, WhatAmI)        == 0x2C);
GG_STATIC_ASSERT(offsetof(Vtbl_00471C90, GetOwningHouse) == 0x3C);
GG_STATIC_ASSERT(offsetof(Vtbl_00471C90, GetTechnoType)  == 0x84);
GG_STATIC_ASSERT(offsetof(Vtbl_00471C90, IsIronCurtained)== 0x160);

// CaptureManagerClass — mind-control bookkeeping on a TechnoClass. Layout
// mirrors match/combat/capture_manager_class.h (ControlNodes vector @0x24,
// Count @0x34, MaxControlNodes @0x3C, InfiniteControl @0x40) plus Owner @0x48.
struct CaptureManagerClass
{
    char          _pad000[0x34];         // +0x0000 AbstractClass base + vector head
    int           ControlNodes_Count;    // +0x0034
    int           ControlNodes_CapInc;   // +0x0038
    int           MaxControlNodes;       // +0x003C
    unsigned char InfiniteControl;       // +0x0040
    char          _pad041[0x48 - 0x41];  // +0x0041
    Techno_00471C90* Owner;              // +0x0048

    // FUNCTION: GAMEMD 0x471C90
    bool CanCapture(Techno_00471C90* target) const;
};
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, ControlNodes_Count) == 0x34);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, MaxControlNodes)    == 0x3C);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, InfiniteControl)    == 0x40);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, Owner)              == 0x48);

#endif  // GG_MATCH_COMBAT_CAPTURE_MANAGER_CAN_CAPTURE_METHODS_H
