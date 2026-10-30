// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, vtable slots and callees read off the user's retail gamemd.exe
//   v1.001 (Ghidra disasm) at the addresses annotated below. Methods live on
//   the canonical TechnoClass (match/_layout/techno_class.h).
//
// Address index:
//   0x707750  TechnoClass::FUN_00707750
//   0x707D20  TechnoClass::FUN_00707D20

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/techno_class.h"
#include "../_layout/techno_type_class.h"
#include "../_layout/house_class.h"
#include "../_layout/house_type_class.h"
#include "../core/randomizer.h"

// The tactical view object (GLOBAL 0x887324): only the word at +0xB4 is read.
struct TacticalView_r21_4
{
    char  _pad000[0xB4];
    short ViewWord;            // +0xB4
};
GG_STATIC_ASSERT(offsetof(TacticalView_r21_4, ViewWord) == 0xB4);
// GLOBAL: GAMEMD 0x887324 -- Tactical::Instance.
extern TacticalView_r21_4* TacticalInstance_r21_4;

// FUNCTION: GAMEMD 0x707750
//
// Derive the +0x3CA angle word from the tactical view word, the first
// argument and the second argument's word, then pull it back by 8 or 12
// depending on which eighth of the circle the primary facing points into.
void TechnoClass::FUN_00707750(int a, DirStruct d)
{
    short t = TacticalInstance_r21_4->ViewWord;
    t += a;
    this->unknown_3CA = t + d.Raw - 10;
    DirStruct* cur = this->PrimaryFacing.FUN_004C93D0(&d);
    int octant = ((*(unsigned int*)cur >> 12) + 1) >> 1 & 7;
    if (octant == 0 || octant == 6) {
        this->unknown_3CA -= 8;
    } else if (octant == 7) {
        this->unknown_3CA -= 12;
    }
}

// The rules object, as far as the four per-side crew values.
struct RulesView_00707D20
{
    char _pad000[0xF6C];
    int  DefaultCrew;          // +0xF6C
    char _pad0F70[0x8];
    int  SideCrew0;            // +0xF78
    int  SideCrew1;            // +0xF7C
    int  SideCrew2;            // +0xF80
};
GG_STATIC_ASSERT(offsetof(RulesView_00707D20, DefaultCrew) == 0xF6C);
GG_STATIC_ASSERT(offsetof(RulesView_00707D20, SideCrew0) == 0xF78);
GG_STATIC_ASSERT(offsetof(RulesView_00707D20, SideCrew2) == 0xF80);
// GLOBAL: GAMEMD 0x8871E0 -- the rules.
extern RulesView_00707D20* RulesInstance_00707D20;

// The scenario object, as far as the random number generator it carries.
struct ScenarioView_00707D20
{
    char       _pad000[0x218];
    Randomizer Random;         // +0x218
};
GG_STATIC_ASSERT(offsetof(ScenarioView_00707D20, Random) == 0x218);
// GLOBAL: GAMEMD 0xA8B230 -- the scenario.
extern ScenarioView_00707D20* ScenarioInstance_00707D20;

// FUNCTION: GAMEMD 0x707D20
//
// The crew value for a crewed object: picked by the owner's side index,
// replaced by the default when the owner's type has no side, and also
// replaced by the default when the object is armed and a 0..99 roll lands
// below 15. Zero for an uncrewed type.
int TechnoClass::FUN_00707D20()
{
    if (!vf_33()->Crewed) {
        return 0;
    }
    HouseClass* house = this->Owner;
    int crew;
    if (house->SideIndex == 0) {
        crew = RulesInstance_00707D20->SideCrew0;
    } else if (house->SideIndex == 1) {
        crew = RulesInstance_00707D20->SideCrew1;
    } else if (house->SideIndex == 2) {
        crew = RulesInstance_00707D20->SideCrew2;
    } else {
        crew = RulesInstance_00707D20->DefaultCrew;
    }
    if (house->Type->SideIndex != -1) {
        if (IsArmed()) {
            if (ScenarioInstance_00707D20->Random.RandomRanged(0, 99) < 15) {
                crew = RulesInstance_00707D20->DefaultCrew;
            }
        }
    } else {
        crew = RulesInstance_00707D20->DefaultCrew;
    }
    return crew;
}

// BEGIN defined globals (define_globals.py)
// GLOBAL: GAMEMD 0x887324
TacticalView_r21_4* TacticalInstance_r21_4;
// END defined globals
