// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x458330. The body is five copies of one inlined
//   block, and the two constant strides fall straight out of the five copies:
//     * the animation pointer on the building is `[ESI+0x5A4]`, `[ESI+0x568]`,
//       `[ESI+0x56C]`, `[ESI+0x570]`, `[ESI+0x574]` for slots 0x12, 3, 4, 5
//       and 6 — one dword per slot from a base of 0x55C (0x55C + 4*3 = 0x568,
//       0x55C + 4*0x12 = 0x5A4), which agrees with the Anims array already
//       pinned at 0x55C by 0x452260 in this tree;
//     * the name triples on the type are `Type+0x1414/0x1424/0x1434` for slot
//       0x12 and `Type+0x1018/0x1028/0x1038`, `+0x105C/..`, `+0x10A0/..`,
//       `+0x10E4/..` for slots 3..6 — a 0x44 stride from a base of 0xF4C
//       (0xF4C + 0x44*3 = 0x1018, 0xF4C + 0x44*0x12 = 0x1414), the same
//       0x44-byte record and 0xF4C base 0x452260 already pins, with the three
//       names at +0x00, +0x10 and +0x20 of the record;
//     * `MOV EAX,[0x8871E0]` then `FCOMP double ptr [EAX+0x1700]` — the rules
//       singleton (YRpp RulesClass::Instance) and a double at 0x1700;
//     * vtable slot `[EDX+0x408]` is the occupant count, as at 0x457CE0;
//     * callees 0x5F5C60 (__thiscall, answers a double on the x87 stack) and
//       0x451890 (__thiscall, five pushed arguments).
//   Names cross-checked against YRpp BuildingClass::PlayNthAnim / PlayAnim,
//   BuildingTypeClass::BuildingAnimStruct, RulesClass::ConditionYellow,
//   ObjectClass::GetHealthPercentage and the BuildingAnimSlot enum (Active=3,
//   ActiveTwo=4, ActiveThree=5, ActiveFour=6, Idle=18) — consult-only, NO
//   LICENSE; every offset above is re-derived from the user's binary.
#ifndef GG_MATCH_COMBAT_BUILDING_CLASS_OCCUPANT_ANIMS_METHODS_H
#define GG_MATCH_COMBAT_BUILDING_CLASS_OCCUPANT_ANIMS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"
#include "../_layout/object_class.h"
#include "../core/rules_class.h"

#define ANIM_COUNT_00458330 21

// BuildingAnimSlot, as far as this method uses it.
#define ANIM_SLOT_ACTIVE_00458330       3
#define ANIM_SLOT_ACTIVE_TWO_00458330   4
#define ANIM_SLOT_ACTIVE_THREE_00458330 5
#define ANIM_SLOT_ACTIVE_FOUR_00458330  6
#define ANIM_SLOT_IDLE_00458330         0x12

// One per-slot animation record of the type; 0x44 bytes, three 0x10-byte
// names first.
struct AnimRecord_00458330
{
    char Anim[0x10];        // +0x0000
    char Damaged[0x10];     // +0x0010
    char Garrisoned[0x10];  // +0x0020
    char _pad30[0x14];      // +0x0030
};
GG_STATIC_ASSERT(offsetof(AnimRecord_00458330, Damaged)    == 0x10 &&
                 offsetof(AnimRecord_00458330, Garrisoned) == 0x20 &&
                 sizeof(AnimRecord_00458330)               == 0x44);

struct BuildingType_00458330
{
    char                _pad0000[0xF4C];                      // +0x0000
    AnimRecord_00458330 BuildingAnim[ANIM_COUNT_00458330];    // +0x0F4C
};
GG_STATIC_ASSERT(offsetof(BuildingType_00458330, BuildingAnim) == 0xF4C);

struct Anim_00458330;

// Declaration order matters — see match/_rt/gg_vslot.h.
struct Vtbl_00458330;

// Sparse BuildingClass view using the confirmed ObjectClass prefix; this does
// not assert the intervening direct-base hierarchy.
struct BuildingClass_00458330 : ObjectClass
{
    char                    unknown_AC[0x520 - 0xAC];          // +0x00AC
    BuildingType_00458330*  Type;                              // +0x0520
    char                    _pad0524[0x55C - 0x524];           // +0x0524
    Anim_00458330*          Anims[ANIM_COUNT_00458330];        // +0x055C

    // FUNCTION: GAMEMD 0x451890 (decl; reloc) — BuildingClass::PlayAnim.
    void PlayAnim(const char* animName, int slot, int damaged, bool garrisoned,
                  int effectDelay);

    __forceinline void PlayNthAnim(int slot, int effectDelay);


    // FUNCTION: GAMEMD 0x458330
    void UpdateOccupantAnims();
};
GG_STATIC_ASSERT(offsetof(BuildingClass_00458330, _vtable_IPersistStream) == 0 &&
                 offsetof(BuildingClass_00458330, Health) == 0x6C &&
                 offsetof(BuildingClass_00458330, Type)  == 0x520 &&
                 offsetof(BuildingClass_00458330, Anims) == 0x55C);

typedef int (BuildingClass_00458330::*Fn408_00458330)();

struct Vtbl_00458330
{
    char            _pad0000[0x408];   // +0x0000
    Fn408_00458330  GetOccupantCount;  // +0x0408
};
GG_STATIC_ASSERT(offsetof(Vtbl_00458330, GetOccupantCount) == 0x408);

#endif  // GG_MATCH_COMBAT_BUILDING_CLASS_OCCUPANT_ANIMS_METHODS_H
