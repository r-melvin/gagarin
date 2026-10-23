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
        if ((char)damaged) {
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
// MATCHED (100.0%, 217/217). Four levers, all of them about how the two
// booleans are typed and tested rather than about the shape:
//   * the damaged flag must be an `int`, not a `bool`. Retail materialises it
//     with `MOV EBX,0x1` / `XOR EBX,EBX`, the dword forms; a `bool` gets the
//     byte forms and spills the pair differently (35.9%).
//   * the name has to be selected through `Type->BuildingAnim[slot].Field` in
//     each arm, not through a reference to the record bound once. Retail folds
//     the record offset and the field offset into a single `ADD EAX,0x1424`
//     per arm and reloads the type inside each arm; binding the record first
//     splits it into a base `ADD` plus an `ADD EAX,0x10`/`0x20`.
//   * the flag has to be written as the comparison itself,
//     `GetHealthPercentage() <= ConditionYellow`, not as `!(... > ...)`:
//     70.0% versus 88.5%, although both produce the same FCOMP/FNSTSW/
//     TEST AH,0x41 idiom.
//   * the last 11.5% is the register the flag lives in. Retail uses EBX (and
//     so can test it with `TEST BL,BL`), cl 8804 picks EDI, which has no byte
//     subregister and therefore tests the full dword; the two choices differ
//     in 25 instructions spread over the five copies while the instruction
//     multiset stays identical. Testing the flag through a `(char)` cast makes
//     the byte test explicit, which forces the allocator onto a
//     byte-addressable register, and EBX and the whole prologue/epilogue order
//     follow. Thirteen spellings were measured across three batches: `bool`,
//     `unsigned`, `register int`, `!(h > cy)`, `(h > cy) ? 0 : 1`,
//     `damaged != 0`, `(bool)damaged`, `(int)(bool)(h <= cy)` (5.3%), the
//     flags declared in the other order (4.6%), the helper written as a macro
//     and as a free `__forceinline` function taking the building — only the
//     `(char)` test reaches 100.0%.
void BuildingClass::UpdateOccupantAnims()
{
    PlayNthAnim(this, ANIM_SLOT_IDLE_00458330, 0);
    PlayNthAnim(this, ANIM_SLOT_ACTIVE_00458330, 0);
    PlayNthAnim(this, ANIM_SLOT_ACTIVE_TWO_00458330, 0);
    PlayNthAnim(this, ANIM_SLOT_ACTIVE_THREE_00458330, 0);
    PlayNthAnim(this, ANIM_SLOT_ACTIVE_FOUR_00458330, 0);
}
