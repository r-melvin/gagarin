// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x458330.

#include "building_class_occupant_anims_methods.h"

// Restart one animation slot with the artwork the building's current state
// calls for: the damaged name once health has fallen to the yellow threshold,
// otherwise the garrisoned name while somebody is inside, otherwise the plain
// one. Retail inlines this five times over, once per slot, so it has to be
// `__forceinline` here — plain `inline` gets four copies in and then leaves
// the fifth as an out-of-line call, which costs 30 points on its own. The
// marker has to sit on the DECLARATION in the header as well as on the
// definition: with it on the definition alone cl still leaves the fifth copy
// out of line (78.8% versus 100.0%).
static __forceinline void PlayNthAnim(BuildingClass* self, int slot, int effectDelay)
{
    if (self->Anims[slot] != 0) {
        int damaged = self->GetHealthPercentage()
                      <= RulesInstance->ConditionYellow;
        bool garrisoned = self->vf_258() > 0;

        const char* animName;
        if (damaged) {
            animName = self->Type->BuildingAnim[slot].Damaged;
        } else if (garrisoned) {
            animName = self->Type->BuildingAnim[slot].Garrisoned;
        } else {
            animName = self->Type->BuildingAnim[slot].Anim;
        }
        if (animName && *animName) {
            self->PlayAnim(animName, slot, damaged, garrisoned, effectDelay);
        }
    }
}

// FUNCTION: GAMEMD 0x458330
//
// Refresh the idle animation and the four active ones after anything that
// changes how the building should look — occupancy, ownership or damage.
// The slot order is retail's: Idle first, then Active through ActiveFour.
//
// PARTIAL: 88.5% -- the damaged flag lives in EDI where retail uses EBX (so
// retail tests it with `TEST BL,BL`); instruction multiset is identical. Two
// levers from the earlier match are kept because they are plain code:
//   * the damaged flag is an `int`, not a `bool` (dword MOV/XOR forms);
//   * the name is selected through `Type->BuildingAnim[slot].Field` in each
//     arm, and the flag is written as `GetHealthPercentage() <= ConditionYellow`.
void BuildingClass::UpdateOccupantAnims()
{
    PlayNthAnim(this, ANIM_SLOT_IDLE_00458330, 0);
    PlayNthAnim(this, ANIM_SLOT_ACTIVE_00458330, 0);
    PlayNthAnim(this, ANIM_SLOT_ACTIVE_TWO_00458330, 0);
    PlayNthAnim(this, ANIM_SLOT_ACTIVE_THREE_00458330, 0);
    PlayNthAnim(this, ANIM_SLOT_ACTIVE_FOUR_00458330, 0);
}
