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
//   Names cross-checked against YRpp AITriggerTypeClass.h / RulesClass.h
//   (consult-only; NO LICENSE; every offset reconfirmed above). YRpp lists
//   the two counters positionally as TimesExecuted / TimesCompleted; the
//   retail bodies show +0x104 bumped on success only and +0x108 on both, so
//   they are named Successes / Attempts here.
#ifndef GG_MATCH_AI_AI_TRIGGER_REGISTER_METHODS_H
#define GG_MATCH_AI_AI_TRIGGER_REGISTER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// RulesClass — only the three AI-trigger weight tunables are read.
struct Rules_0041FD60
{
    char   _pad000[0xC0];                   // +0x0000
    double AITriggerSuccessWeightDelta;     // +0x00C0
    double AITriggerFailureWeightDelta;     // +0x00C8
    double AITriggerTrackRecordCoefficient; // +0x00D0
};
GG_STATIC_ASSERT(offsetof(Rules_0041FD60, AITriggerSuccessWeightDelta) == 0xC0);
GG_STATIC_ASSERT(offsetof(Rules_0041FD60, AITriggerFailureWeightDelta) == 0xC8);
GG_STATIC_ASSERT(offsetof(Rules_0041FD60, AITriggerTrackRecordCoefficient) == 0xD0);

// GLOBAL: GAMEMD 0x8871E0 — RulesClass::Instance.
extern Rules_0041FD60* Rules;

struct AITriggerTypeClass
{
    char   _pad000[0xB8];      // +0x0000
    double Weight_Current;     // +0x00B8
    double Weight_Minimum;     // +0x00C0
    double Weight_Maximum;     // +0x00C8
    char   _pad0D0[0x104 - 0xD0];
    int    Successes;          // +0x0104
    int    Attempts;           // +0x0108

    // FUNCTION: GAMEMD 0x41FD60
    void RegisterSuccess();

    // FUNCTION: GAMEMD 0x41FE20
    void RegisterFailure();
};
GG_STATIC_ASSERT(offsetof(AITriggerTypeClass, Weight_Current) == 0xB8);
GG_STATIC_ASSERT(offsetof(AITriggerTypeClass, Weight_Minimum) == 0xC0);
GG_STATIC_ASSERT(offsetof(AITriggerTypeClass, Weight_Maximum) == 0xC8);
GG_STATIC_ASSERT(offsetof(AITriggerTypeClass, Successes) == 0x104);
GG_STATIC_ASSERT(offsetof(AITriggerTypeClass, Attempts) == 0x108);

#endif  // GG_MATCH_AI_AI_TRIGGER_REGISTER_METHODS_H
