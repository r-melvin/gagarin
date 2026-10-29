// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 with the
//   local Ghidra CLI inside 0x6386E0:
//     the planning token returned by the no-argument __thiscall 0x705D20 has
//     the owner at [EDI+0x00] (0x638748), a polymorphic sub-object at
//     [EDI+0x04] whose slot 0x0C is called with LEA ECX,[EDI+4] (0x6387F6),
//     the node array at [EDI+0x08] (0x638742), the node count at [EDI+0x14]
//     (0x638715, 0x638731), the byte cleared on the way out at [EBX+0x1C]
//     (0x638826) and the five fields reset at [EDI+0x8C], [EDI+0x90],
//     [EDI+0x94] and the bytes [EDI+0x98] / [EDI+0x99] (0x638806..0x63881F).
//     One node: the entry array at [ESI+0x04] (0x63875B) and the int at
//     [ESI+0x10] (0x638797); one entry: the block freed at [EDX+0x04]
//     (0x638775). The guard argument's byte is [EDI+0x1D] (MOVSX at
//     0x638709) — the same +0x1D as the planning record in the already-matched
//     match/ai/techno_class_planning_token_methods.h (read, not edited).
//     Owner side: [EAX+0x21C] (0x6387C2) and [ECX+0x30] / [EAX+0x30]
//     (0x6387C8, 0x6387DD).
//   Names cross-checked against YRpp; every offset
//   reconfirmed above.
#ifndef GG_MATCH_AI_TECHNO_CLASS_CLEAR_TOKENS_METHODS_H
#define GG_MATCH_AI_TECHNO_CLASS_CLEAR_TOKENS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"
#include "../_layout/house_class.h"

// LIBRARY: GAMEMD 0x7C8B3D (decl; reloc) -- YR game-heap free (operator
// delete); __cdecl, one pointer argument, caller pops.
void __cdecl GameDelete_006386E0(void* block);

// One planning record. Only the byte at +0x1D gates this function.
struct Record_006386E0
{
    char _pad000[0x1D];   // +0x0000
    char At_01D;          // +0x001D
};
GG_STATIC_ASSERT(offsetof(Record_006386E0, At_01D) == 0x1D);

// One entry hanging off a planning node; only the block at +4 is freed.
struct Entry_006386E0
{
    char  _pad000[0x04];  // +0x0000
    void* At_004;         // +0x0004
};
GG_STATIC_ASSERT(offsetof(Entry_006386E0, At_004) == 0x04);

// One planning node.
struct Node_006386E0
{
    char            _pad000[0x04];  // +0x0000
    Entry_006386E0** Entries;       // +0x0004
    char            _pad008[0x08];  // +0x0008
    int             At_010;         // +0x0010

    // FUNCTION: GAMEMD 0x634290 (decl; reloc) -- index of the owner's entry, or -1.
    int FUN_00634290(void* owner);
    // FUNCTION: GAMEMD 0x635060 (decl; reloc) -- unhook one entry.
    void FUN_00635060(void* entry);
    // FUNCTION: GAMEMD 0x63DFD0 (decl; reloc) -- remove the entry named by the slot.
    void FUN_0063DFD0(void* slot);
    // FUNCTION: GAMEMD 0x63D9C0 (decl; reloc) -- scalar deleting destructor.
    void* FUN_0063D9C0(int freeFlag);
};
GG_STATIC_ASSERT(offsetof(Node_006386E0, Entries) == 0x04);
GG_STATIC_ASSERT(offsetof(Node_006386E0, At_010) == 0x10);

// FUNCTION: GAMEMD 0x639F80 (decl; reloc) -- decrements the pending-request
// counter of a house index (ECX); the index is the house's ArrayIndex (+0x30).
void FUN_00639F80(int house);

struct Owner_006386E0
{
    char              _pad000[0x21C];  // +0x0000
    HouseClass*       At_21C;          // +0x021C the owning house
};
GG_STATIC_ASSERT(offsetof(Owner_006386E0, At_21C) == 0x21C);

#include "../_layout/player_ptr_00a83d4c.h"

// The list object at 0xAC4C40 (retail loads its address as an immediate).
struct List_006386E0
{
    // FUNCTION: GAMEMD 0x63E900 (decl; reloc)
    void FUN_0063E900(void* slot);
};
// GLOBAL: GAMEMD 0xAC4C40
extern List_006386E0 DAT_00AC4C40;

// The token's polymorphic sub-object at +4; only slot 0x0C is used.
struct SubVtbl_006386E0;
struct Sub_006386E0
{
    SubVtbl_006386E0* Vtbl;   // +0x0000
};
typedef void (Sub_006386E0::*Fn0C_006386E0)();
struct SubVtbl_006386E0
{
    char          _pad000[0x0C];   // +0x0000
    Fn0C_006386E0 At_00C;          // +0x000C
};
GG_STATIC_ASSERT(offsetof(SubVtbl_006386E0, At_00C) == 0x0C);

// PlanningTokenClass.
struct Token_006386E0
{
    Owner_006386E0* Owner;          // +0x0000
    Sub_006386E0    Sub;            // +0x0004
    Node_006386E0** Nodes;          // +0x0008
    char            _pad00C[0x08];  // +0x000C
    int             NodeCount;      // +0x0014
    char            _pad018[0x04];  // +0x0018
    char            At_01C;         // +0x001C
    char            _pad01D[0x8C - 0x1D]; // +0x001D
    int             At_08C;         // +0x008C
    int             At_090;         // +0x0090
    int             At_094;         // +0x0094
    char            At_098;         // +0x0098
    char            At_099;         // +0x0099
};
GG_STATIC_ASSERT(offsetof(Token_006386E0, Sub)       == 0x04);
GG_STATIC_ASSERT(offsetof(Token_006386E0, Nodes)     == 0x08);
GG_STATIC_ASSERT(offsetof(Token_006386E0, NodeCount) == 0x14);
GG_STATIC_ASSERT(offsetof(Token_006386E0, At_01C)    == 0x1C);
GG_STATIC_ASSERT(offsetof(Token_006386E0, At_08C)    == 0x8C);
GG_STATIC_ASSERT(offsetof(Token_006386E0, At_099)    == 0x99);

struct Techno_006386E0
{
    // FUNCTION: GAMEMD 0x705D20 (decl; reloc) -- the planning token this unit is on.
    Token_006386E0* FUN_00705D20();

    // FUNCTION: GAMEMD 0x6386E0 -- TechnoClass::ClearPlanningTokens.
    // A member, not a free function: the unit arrives in ECX and the gating
    // record in EDX, which is `__fastcall` on a member (this in ECX, the first
    // explicit argument in EDX, nothing cleaned). A plain __thiscall member
    // would push the record and return `RET 4`, so the convention is kept.
    void __fastcall ClearPlanningTokens(Record_006386E0* gate);
};

#endif  // GG_MATCH_AI_TECHNO_CLASS_CLEAR_TOKENS_METHODS_H
