// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x6385C0: the token returned by the no-argument
//   __thiscall 0x705D20 is read at `[EBX+0x14]` (node count), `[EBX+0x8C]`
//   and the byte `[EBX+0x1C]` (set to 1 on the way out); the owner's vtable
//   slot `[EAX+0x1E8]` is called with (0x1C, 1); 0x636590 is __thiscall on the
//   token with a hidden result pointer and returns a 0x6F-byte record
//   (`MOV ECX,0x1B; REP MOVSD; MOVSW; MOVSB`), of which byte +0 (compared with
//   4) and byte +0x1D (set to 2) are touched; `PUSH 0x6F; CALL 0x7C8E17` is
//   operator new; the record is appended to the DynamicVectorClass at
//   0xAC4B48 (vtable +0, Items 0xAC4B4C, Capacity 0xAC4B50, IsAllocated
//   0xAC4B55, Count 0xAC4B58, CapacityIncrement 0xAC4B5C) by the inlined
//   AddItem. Names cross-checked against YRpp TechnoClass.h /
//   PlanningTokenClass.h (consult-only) and used as names only.
#ifndef GG_MATCH_AI_TECHNO_CLASS_PLANNING_TOKEN_METHODS_H
#define GG_MATCH_AI_TECHNO_CLASS_PLANNING_TOKEN_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// The 0x6F-byte planning record. The default constructor clears only the
// leading byte (the `MOV byte ptr [EAX],0` after operator new).
struct Node_006385C0
{
    char At_000;              // +0x0000  kind; 4 gets At_01D forced to 2
    char _pad001[0x1C];       // +0x0001
    char At_01D;              // +0x001D
    char _pad01E[0x6F - 0x1E];// +0x001E

    Node_006385C0() { this->At_000 = 0; }
};
GG_STATIC_ASSERT(offsetof(Node_006385C0, At_01D) == 0x1D);
GG_STATIC_ASSERT(sizeof(Node_006385C0) == 0x6F);

// PlanningTokenClass — the three members read plus the record builder.
struct Token_006385C0
{
    char _pad000[0x14];       // +0x0000  OwnerUnit, PlanningNodes vtable/Items/Capacity/flags
    int  NodeCount;           // +0x0014  PlanningNodes.Count
    char _pad018[4];          // +0x0018
    char At_01C;              // +0x001C
    char _pad01D[0x8C - 0x1D];// +0x001D
    int  At_08C;              // +0x008C

    // FUNCTION: GAMEMD 0x636590 (decl; reloc) — builds the next record.
    Node_006385C0 FUN_00636590();
};
GG_STATIC_ASSERT(offsetof(Token_006385C0, NodeCount) == 0x14);
GG_STATIC_ASSERT(offsetof(Token_006385C0, At_01C) == 0x1C);
GG_STATIC_ASSERT(offsetof(Token_006385C0, At_08C) == 0x8C);

// DynamicVectorClass<Node_006385C0*> at 0xAC4B48.
struct NodeVector_006385C0
{
    virtual void vt_000();
    virtual void vt_004();
    virtual bool Resize(int newCapacity, void* array);   // +0x0008

    Node_006385C0** Items;    // +0x0004
    int   Capacity;           // +0x0008
    char  _pad00C[1];         // +0x000C
    char  IsAllocated;        // +0x000D
    char  _pad00E[2];         // +0x000E
    int   Count;              // +0x0010
    int   CapacityIncrement;  // +0x0014

    // DynamicVectorClass::AddItem, expanded inline by VC6 at the call site.
    bool AddItem(Node_006385C0* item)
    {
        int cap = Capacity;
        if (Count < cap
            || ((IsAllocated || cap == 0)
                && CapacityIncrement > 0
                && Resize(cap + CapacityIncrement, 0))) {
            int index = Count++;
            Items[index] = item;
            return true;
        }
        return false;
    }
};
GG_STATIC_ASSERT(offsetof(NodeVector_006385C0, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(NodeVector_006385C0, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(NodeVector_006385C0, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(NodeVector_006385C0, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(NodeVector_006385C0, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(NodeVector_006385C0) == 0x18);
// GLOBAL: GAMEMD 0xAC4B48 — the planning record list (an object: retail loads
// its address as the immediate `MOV ECX,0xAC4B48`).
extern NodeVector_006385C0 DAT_00AC4B48;

// Declaration order matters — see match/_rt/gg_vslot.h.
struct TechnoVtbl_006385C0;
struct Techno_006385C0
{
    TechnoVtbl_006385C0* Vtbl;    // +0x0000

    // FUNCTION: GAMEMD 0x705D20 (decl; reloc) — the planning token this unit is on.
    Token_006385C0* FUN_00705D20();

    // FUNCTION: GAMEMD 0x6385C0 — TechnoClass::TryNextPlanningTokenNode.
    bool TryNextPlanningTokenNode();
};
typedef int (Techno_006385C0::*Fn1E8_006385C0)(int mission, int immediate);
struct TechnoVtbl_006385C0
{
    char _pad000[0x1E8];          // +0x0000
    Fn1E8_006385C0 QueueMission;  // +0x01E8
};
GG_STATIC_ASSERT(offsetof(TechnoVtbl_006385C0, QueueMission) == 0x1E8);

#endif  // GG_MATCH_AI_TECHNO_CLASS_PLANNING_TOKEN_METHODS_H
