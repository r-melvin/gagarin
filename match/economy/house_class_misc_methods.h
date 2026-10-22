// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x4F9750 / 0x4FCDC0 / 0x504740),
//   cross-checked against YRpp (every
//   offset reconfirmed numerically from the disassembly below).
//
// HouseClass-misc — three independent HouseClass leaves:
//   ForceEnd                  declare win/lose end-of-game state
//   GetWeedStoragePercentage  weed-store fill ratio (mirrors GetStoragePercentage)
//   EnsurePlanningPathExists  lazily allocate a planning WaypointPath slot
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_MISC_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_MISC_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "storage_class.h"

// Unsorted::CurrentFrame — global frame counter @0x00A8ED84 (read by ForceEnd).
#include "../core/frame_counter.h"

// ---------------------------------------------------------------------------
// WaypointPathClass — the per-slot "planning mode" path object.
//
// Confirmed from 0x504740: a 0x40-byte object (PUSH 0x40 to operator new) with
// a one-int constructor at 0x763810. Only the size + ctor signature matter for
// the EnsurePlanningPathExists `new` pattern; full layout is P2.
// ---------------------------------------------------------------------------
struct WaypointPathClass
{
    explicit WaypointPathClass(int index) throw();  // GAMEMD 0x763810 __thiscall (declared; reloc)
                                                    // throw(): retail `new` has no EH-cleanup funclet
    char _layout_pad_P2[0x40];               // sizeof = 0x40
};
GG_STATIC_ASSERT(sizeof(WaypointPathClass) == 0x40);

// ---------------------------------------------------------------------------
// RulesClass shim — only the weed-storage capacity divisor @0x17D0 is needed.
//
// Confirmed from 0x4F9750: MOV EAX,[0x008871E0] (the global RulesClass*),
// FIDIV dword ptr [EAX+0x17D0] — the int divisor for the fill ratio.
// ---------------------------------------------------------------------------
struct RulesShim
{
    char _layout_pad_P2[0x17D0];   // +0x0000
    int  WeedStorageAmount;        // +0x17D0  (int; FIDIV operand)
};
GG_STATIC_ASSERT(offsetof(RulesShim, WeedStorageAmount) == 0x17D0);

// GLOBAL: GAMEMD 0x008871E0 — pointer to the active RulesClass instance.
extern RulesShim* RulesGlobalPtr;

// ---------------------------------------------------------------------------
// HouseClass — only the members these three methods touch are modelled; the
// full AbstractClass-derived layout is P2. Each offset is asserted below and
// confirmed numerically from the disassembly.
//   IsWinner      @0x1F7  bool   (MOV AL,[ECX+0x1F7])
//   IsLoser       @0x1F8  bool   (MOV AL,[ECX+0x1F8])
//   PlanningPaths @0x210  ptr[12](MOV [EDI+ESI*4+0x210])
//   EndFrame_298  @0x298  int    (CMP [ECX+0x298],-1)
//   OwnedWeed     @0x314  Storage(LEA ESI,[ECX+0x314])
// ---------------------------------------------------------------------------
struct HouseClass
{
    char               _pad0[0x1F7];                  // +0x0000
    bool               IsWinner;                      // +0x01F7
    bool               IsLoser;                       // +0x01F8
    char               _pad1[0x210 - 0x1F9];          // +0x01F9
    WaypointPathClass* PlanningPaths[12];             // +0x0210
    char               _pad2[0x298 - (0x210 + 12*4)]; // +0x0240
    int                EndFrame_298;                  // +0x0298
    char               _pad3[0x314 - (0x298 + 4)];    // +0x029C
    StorageClass       OwnedWeed;                     // +0x0314

    // Declared ascending by retail address.
    double             GetWeedStoragePercentage();    // GAMEMD 0x4F9750 __thiscall
    void               ForceEnd();                    // GAMEMD 0x4FCDC0 __thiscall
    WaypointPathClass* EnsurePlanningPathExists(int index);  // GAMEMD 0x504740 __thiscall

    // Retail callee we are NOT matching here — declared (no body) so cl emits a
    // reloc-normalised CALL.  HouseClass::Win(bool) @0x4FC9E0, returns BYTE.
    unsigned char      Win(bool savour);              // GAMEMD 0x4FC9E0 __thiscall
};

GG_STATIC_ASSERT(offsetof(HouseClass, IsWinner)      == 0x1F7);
GG_STATIC_ASSERT(offsetof(HouseClass, IsLoser)       == 0x1F8);
GG_STATIC_ASSERT(offsetof(HouseClass, PlanningPaths) == 0x210);
GG_STATIC_ASSERT(offsetof(HouseClass, EndFrame_298)  == 0x298);
GG_STATIC_ASSERT(offsetof(HouseClass, OwnedWeed)     == 0x314);

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_MISC_METHODS_H
