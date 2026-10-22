// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Layout + offsets derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly), cross-checked against YRpp
//   (every offset
//   reconfirmed against the user's binary below).
//
// ScriptClass mission cursor accessors. ScriptClass : AbstractClass; the two
// members these methods touch are:
//   Type            @ +0x24  (ScriptTypeClass*)  — MOV ECX,[ECX+0x24]
//   CurrentMission  @ +0x2C  (int)               — [ECX+0x2C]
// The intervening base (AbstractClass) layout is P2; padded here.
#ifndef GG_MATCH_AI_SCRIPT_CLASS_METHODS_H
#define GG_MATCH_AI_SCRIPT_CLASS_METHODS_H

#include <stddef.h>  // offsetof
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// Minimal, offset-pinned model of ScriptTypeClass: only ActionsCount @0xA0 is
// touched (CMP against [Type+0xA0] in NextMission/HasNextMission). The full
// AbstractTypeClass-derived layout is modelled in ai/script_type_class.h (P2).
// Declared `unsigned` because the comparison is emitted with the CF-based
// SBB/NEG idiom (unsigned `below`), confirmed from the disassembly.
// ---------------------------------------------------------------------------
struct ScriptTypeClass_Min
{
    char         _pad0[0xA0];   // +0x00  AbstractTypeClass base + ArrayIndex/IsGlobal (P2)
    unsigned int ActionsCount;  // +0xA0
};
GG_STATIC_ASSERT(offsetof(ScriptTypeClass_Min, ActionsCount) == 0xA0);

// ---------------------------------------------------------------------------
// ScriptClass — the per-team running AI script instance (mission cursor over a
// ScriptTypeClass's ScriptActions list).
// ---------------------------------------------------------------------------
struct ScriptClass
{
    // Declared ascending by retail address (reccmp/isle TU discipline).
    bool ClearMission();              // GAMEMD 0x691590 __thiscall
    bool SetMission(int nLine);       // GAMEMD 0x6915A0 __thiscall
    bool NextMission();               // GAMEMD 0x6915B0 __thiscall

    char               _pad0[0x24];   // +0x00  AbstractClass (vtable + members, P2)
    ScriptTypeClass_Min* Type;        // +0x24
    int                field_28;      // +0x28
    int                CurrentMission;// +0x2C
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(ScriptClass, Type)           == 0x24);
GG_STATIC_ASSERT(offsetof(ScriptClass, CurrentMission) == 0x2C);
#endif

#endif  // GG_MATCH_AI_SCRIPT_CLASS_METHODS_H
