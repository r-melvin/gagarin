// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x4721xx–0x4722xx), cross-checked
//   against YRpp CaptureManagerClass.h (consult-only; reconfirmed here).
//
// CaptureManagerClass — per-TechnoClass mind-control manager: a vector of
// ControlNode (the controlled units) plus the control-capacity bookkeeping.
#ifndef GG_MATCH_COMBAT_CAPTURE_MANAGER_CLASS_H
#define GG_MATCH_COMBAT_CAPTURE_MANAGER_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class TechnoClass;
class HouseClass;

// ControlNode — one controlled unit. Unit pointer at +0 (FreeAll loads [node+0]).
struct ControlNode
{
    TechnoClass* Unit;          // +0x00
    HouseClass*  OriginalOwner; // +0x04
    // CDTimerClass LinkDrawTimer (+0x08) — not touched by the matched methods.
};

// CaptureManagerClass. The AbstractClass base (COM IPersistStream + members)
// occupies [0x00..0x23]; its full decomposition is P2. Every field below is
// confirmed numerically from the disassembly and asserted.
struct CaptureManagerClass
{
    void  FreeAll();                       // GAMEMD 0x472140 __thiscall
    bool  CannotControlAnyMore() const;    // GAMEMD 0x4722A0 __thiscall
    bool  IsControllingSomething() const;  // GAMEMD 0x4722C0 __thiscall
    int   GetControlledCount();            // GAMEMD 0x4722D0 __thiscall
    bool  FreeUnit(TechnoClass* unit);     // GAMEMD 0x471FF0 (declared for FreeAll's call)

    char  _abstract_base[0x24];            // AbstractClass base (COM + members) — P2
    // ControlNodes : DynamicVectorClass<ControlNode*> @ 0x24
    void*        _cn_vtable;               // +0x24
    ControlNode** ControlNodes_Items;      // +0x28
    int          ControlNodes_Capacity;    // +0x2C
    int          ControlNodes_IsAllocated; // +0x30
    int          ControlNodes_Count;       // +0x34
    int          ControlNodes_CapacityInc; // +0x38
    int          MaxControlNodes;          // +0x3C
    unsigned char InfiniteControl;         // +0x40
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, ControlNodes_Items) == 0x28);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, ControlNodes_Count) == 0x34);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, MaxControlNodes)    == 0x3C);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, InfiniteControl)    == 0x40);
#endif

#endif  // GG_MATCH_COMBAT_CAPTURE_MANAGER_CLASS_H
