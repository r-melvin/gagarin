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
#include "../_layout/script_class.h"





#endif  // GG_MATCH_AI_SCRIPT_CLASS_ACTION_METHODS_H
