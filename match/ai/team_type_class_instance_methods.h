// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets/convention derived from the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI (member-access disassembly at 0x6F1F30 / 0x6F1F70),
//   cross-checked against YRpp
//   (every offset/global/call target reconfirmed numerically below).
//
// TeamTypeClass instance-enumeration helpers.  Neither method dereferences any
// TeamTypeClass member: `this` is used only as a pointer-identity key, matched
// against each live TeamClass's Type pointer.  Both walk the global
// TeamClass::Array (a DynamicVectorClass<TeamClass*> at GAMEMD 0x8B40E8):
//   Items @ 0x8B40EC  (MOV ESI,[0x8b40ec] / MOV EAX,[0x8b40ec])
//   Count @ 0x8B40F8  (MOV EDI,[0x8b40f8] / CMP …,[0x8b40f8])
// confirming the standard VectorClass layout (base 0x8B40E8 + 0x04 / + 0x10).
#ifndef GG_MATCH_AI_TEAM_TYPE_CLASS_INSTANCE_METHODS_H
#define GG_MATCH_AI_TEAM_TYPE_CLASS_INSTANCE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector_class.h"
#include "../_layout/team_class.h"
#include "../_layout/team_type_class.h"

// Global TeamClass::Array (DynamicVectorClass<TeamClass*>) — GAMEMD 0x8B40E8.
extern DynamicVectorClassLayout DAT_008B40E8;

#endif  // GG_MATCH_AI_TEAM_TYPE_CLASS_INSTANCE_METHODS_H
