// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x4722F0), cross-checked against
//   YRpp CaptureManagerClass.h (consult-only; reconfirmed here).
//
// CaptureManagerClass — additional accessor (GetOriginalOwner). Layout mirrors
// match/combat/capture_manager_class.h; only the members the method touches are
// modelled and asserted (ControlNodes vector Items@0x28 / Count@0x34, and the
// ControlNode {Unit@0, OriginalOwner@4}).
#ifndef GG_MATCH_COMBAT_CAPTURE_MANAGER_CLASS_MORE_METHODS_H
#define GG_MATCH_COMBAT_CAPTURE_MANAGER_CLASS_MORE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

class TechnoClass;
class HouseClass;

// ControlNode — one controlled unit. Unit pointer at +0 (CMP [EDI],ESI), the
// captured house at +4 (MOV EAX,[EAX+4]).
struct ControlNode
{
    TechnoClass* Unit;          // +0x00
    HouseClass*  OriginalOwner; // +0x04
    // CDTimerClass LinkDrawTimer (+0x08) — not touched here.
};

struct CaptureManagerClass
{
    HouseClass* GetOriginalOwner(TechnoClass* unit) const;  // GAMEMD 0x4722F0

    char  _abstract_base[0x24];            // AbstractClass base (COM + members) — P2
    // ControlNodes : DynamicVectorClass<ControlNode*> @ 0x24
    void*         _cn_vtable;              // +0x24
    ControlNode** ControlNodes_Items;      // +0x28
    int           ControlNodes_Capacity;   // +0x2C
    int           ControlNodes_IsAllocated;// +0x30
    int           ControlNodes_Count;      // +0x34
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, ControlNodes_Items) == 0x28);
GG_STATIC_ASSERT(offsetof(CaptureManagerClass, ControlNodes_Count) == 0x34);
GG_STATIC_ASSERT(offsetof(ControlNode, Unit) == 0x00);
GG_STATIC_ASSERT(offsetof(ControlNode, OriginalOwner) == 0x04);
#endif

#endif  // GG_MATCH_COMBAT_CAPTURE_MANAGER_CLASS_MORE_METHODS_H
