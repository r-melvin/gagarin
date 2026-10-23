// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and offsets read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4DA230. Every member name here matches the committed
//   P2 spine and is reconfirmed from the member-access instructions:
//   ObjectClass::InLimbo @0x81, TechnoClass::Owner @0x21C,
//   TechnoClass::RecruitableA @0x421, FootClass::Team @0x5D4. Method name
//   cross-checked against YRpp (`FootClass::CanBeRecruited`).
//
// A local offset-pinned shim rather than the full spine: this TU needs four
// members spread across three levels of the hierarchy and nothing else.
#ifndef GG_MATCH_AI_FOOT_CLASS_RECRUIT_METHODS_H
#define GG_MATCH_AI_FOOT_CLASS_RECRUIT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/foot_class.h"


// Recruitability predicate on the AbstractType, at 0x005B36E0 — __fastcall with
// the type in ECX (`MOV ECX,EAX; CALL rel32`). Descriptive name; the address
// carries no binary-attested one.
bool IsRecruitableRTTI(int rtti);

// WhatAmI() — virtual at +0x184 of this vtable, dispatched through the tree's
// usual __fastcall-fn-pointer idiom.
#endif  // GG_MATCH_AI_FOOT_CLASS_RECRUIT_METHODS_H
