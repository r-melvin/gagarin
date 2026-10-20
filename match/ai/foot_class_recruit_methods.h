// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and offsets read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x4DA230. Every member name here matches the committed
//   P2 spine and is reconfirmed from the member-access instructions:
//   ObjectClass::InLimbo @0x81, TechnoClass::Owner @0x21C,
//   TechnoClass::RecruitableA @0x421, FootClass::Team @0x5D4. Method name
//   cross-checked against YRpp (`FootClass::CanBeRecruited`, consult-only).
//
// A local offset-pinned shim rather than the full spine: this TU needs four
// members spread across three levels of the hierarchy and nothing else.
#ifndef GG_MATCH_AI_FOOT_CLASS_RECRUIT_METHODS_H
#define GG_MATCH_AI_FOOT_CLASS_RECRUIT_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct HouseClass;
struct FootClass;

// Recruitability predicate on the AbstractType, at 0x005B36E0 — __fastcall with
// the type in ECX (`MOV ECX,EAX; CALL rel32`). Descriptive name; the address
// carries no confirmed Westwood one.
bool __fastcall IsRecruitableRTTI(int rtti);

// WhatAmI() — virtual at +0x184 of this vtable, dispatched through the tree's
// usual __fastcall-fn-pointer idiom.
typedef int (__fastcall* WhatAmIFunc)(FootClass*);
#define FOOT_WHAT_AM_I(o) ((*(WhatAmIFunc*)(*(char**)(o) + 0x184))(o))

struct FootClass
{
    char          _pad000[0x81];            // +0x0000
    bool          InLimbo;                  // +0x0081  ObjectClass
    char          _pad082[0x21C - 0x82];    // +0x0082
    HouseClass*   Owner;                    // +0x021C  TechnoClass
    char          _pad220[0x421 - 0x220];   // +0x0220
    unsigned char RecruitableA;             // +0x0421  TechnoClass
    char          _pad422[0x5D4 - 0x422];   // +0x0422
    void*         Team;                     // +0x05D4  FootClass (TeamClass*)

    bool CanBeRecruited(HouseClass* house);   // GAMEMD 0x4DA230
};

GG_STATIC_ASSERT(offsetof(FootClass, InLimbo)      == 0x81);
GG_STATIC_ASSERT(offsetof(FootClass, Owner)        == 0x21C);
GG_STATIC_ASSERT(offsetof(FootClass, RecruitableA) == 0x421);
GG_STATIC_ASSERT(offsetof(FootClass, Team)         == 0x5D4);

#endif  // GG_MATCH_AI_FOOT_CLASS_RECRUIT_METHODS_H
