// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x41FD60 / 0x41FE20 (the two bodies share one shape):
//     Weight_Current   [ECX+0xB8]  (FADD/FST/FLD double, copied as two dwords
//                                   at 0x41FDCC/0x41FDD8)
//     Weight_Minimum   [ECX+0xC0]  (FCOMP double; dwords at 0xC0/0xC4)
//     Weight_Maximum   [ECX+0xC8]  (FCOMP double; dwords at 0xC8/0xCC)
//     Successes        [ECX+0x104] (FILD; INC at 0x41FE0F, success only)
//     Attempts         [ECX+0x108] (MOV EDX at entry; INC at the tail)
//     RulesClass +0xC0 [EAX+0xC0]  double (FLD at 0x41FDA5, success delta)
//     RulesClass +0xC8 [ESI+0xC8]  double (FLD at 0x41FE6D, failure delta)
//     RulesClass +0xD0 [ESI+0xD0]  double (FMUL at 0x41FE50, failure coeff)
//   Globals: RulesClass::Instance 0x8871E0; the 0.0 double at 0x7E2800 and
//   the 0.5 double at 0x7E1738 (both read with `ghidra memory read`).
//   Names cross-checked against YRpp
//   (every offset reconfirmed above). YRpp lists
//   the two counters positionally as TimesExecuted / TimesCompleted; the
//   retail bodies show +0x104 bumped on success only and +0x108 on both, so
//   they are named Successes / Attempts here.
#ifndef GG_MATCH_AI_AI_TRIGGER_REGISTER_METHODS_H
#define GG_MATCH_AI_AI_TRIGGER_REGISTER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// RulesClass: the canonical layout supplies the three AI-trigger weight tunables read here.
#include "../_layout/rules_class.h"

// AITriggerTypeClass: the canonical class (weights +0xB8..+0xC8, Successes
// +0x104, Attempts +0x108).
#include "../_layout/ai_trigger_type_class.h"

#endif  // GG_MATCH_AI_AI_TRIGGER_REGISTER_METHODS_H
