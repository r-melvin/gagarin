// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly), cross-checked against YRpp
//   (every offset
//   reconfirmed against the user's binary below).
//
// ScriptClass action-fetch accessors (GetCurrentAction / GetNextAction). These
// copy a ScriptActionNode {int Action; int Argument;} out of the cursor's
// ScriptTypeClass action list into a caller-supplied buffer and return it.
//
// Members touched, all confirmed numerically from the disassembly:
//   ScriptClass::Type            @ +0x24  (ScriptTypeClass*)  MOV r,[ECX+0x24]
//   ScriptClass::CurrentMission  @ +0x2C  (int)               [ECX+0x2C]
//   ScriptTypeClass::ActionsCount@ +0xA0  (int)   CMP ...,[Type+0xA0]; JL (signed)
//   ScriptTypeClass::ScriptActions@+0xA4  (ScriptActionNode[]) [Type+idx*8+0xA4]
//       element 0: Action @ +0xA4, Argument @ +0xA8  (stride 8)
// ActionsCount is modelled as a SIGNED int: GetNextAction's bound check emits a
// signed JL (CurrentMission+1 < ActionsCount), not the unsigned SBB/NEG idiom.
#ifndef GG_MATCH_AI_SCRIPT_CLASS_ACTION_METHODS_H
#define GG_MATCH_AI_SCRIPT_CLASS_ACTION_METHODS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

// One AI script step: an action opcode plus its argument (8 bytes, stride 8).
struct ScriptActionNode
{
    int Action;    // +0x00
    int Argument;  // +0x04
};
GG_STATIC_ASSERT(offsetof(ScriptActionNode, Argument) == 0x4);

// ---------------------------------------------------------------------------
// Minimal, offset-pinned model of ScriptTypeClass: only ActionsCount @0xA0 and
// the ScriptActions list @0xA4 are touched. The full AbstractTypeClass-derived
// layout lives in ai/script_type_class.h (P2). ActionsCount is SIGNED here.
// ---------------------------------------------------------------------------
struct ScriptTypeClass_Min
{
    char             _pad0[0xA0];        // +0x00  AbstractTypeClass base + ArrayIndex/IsGlobal (P2)
    int              ActionsCount;       // +0xA0
    ScriptActionNode ScriptActions[50];  // +0xA4
};
GG_STATIC_ASSERT(offsetof(ScriptTypeClass_Min, ActionsCount)  == 0xA0);
GG_STATIC_ASSERT(offsetof(ScriptTypeClass_Min, ScriptActions) == 0xA4);

// ---------------------------------------------------------------------------
// ScriptClass — the per-team running AI script instance (mission cursor over a
// ScriptTypeClass's ScriptActions list).
// ---------------------------------------------------------------------------
class ScriptClass
{
public:
    // Declared ascending by retail address (reccmp/isle TU discipline).
    ScriptActionNode* GetCurrentAction(ScriptActionNode* buffer) const;  // GAMEMD 0x691500 __thiscall
    ScriptActionNode* GetNextAction(ScriptActionNode* buffer) const;     // GAMEMD 0x691540 __thiscall

    char                 _pad0[0x24];     // +0x00  AbstractClass (vtable + members, P2)
    ScriptTypeClass_Min* Type;            // +0x24
    int                  field_28;        // +0x28
    int                  CurrentMission;  // +0x2C
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(ScriptClass, Type)           == 0x24);
GG_STATIC_ASSERT(offsetof(ScriptClass, CurrentMission) == 0x2C);
#endif

#endif  // GG_MATCH_AI_SCRIPT_CLASS_ACTION_METHODS_H
