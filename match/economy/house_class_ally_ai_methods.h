// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x501640: on the rules object `[0x8871E0]` the byte
//   `[EAX+0x14B5]`; the object pointer `[0xA8B23C]` dispatched through
//   `MOV EDX,[ECX]; CALL [EDX+4]` (a bool query); on the scenario
//   `[0xA8B230]` the byte `[EAX+0x11E0]`; the house array `[0xA8022C]`
//   (Items) / `[0xA80238]` (Count); on each house `[ESI+0x1F5]` (Defeated),
//   `[ESI+0x1EC]` (IsHumanPlayer), `[ESI+0x1ED]` (IsInPlayerControl) and the
//   store `[ESI+0x24A]`; the session game mode `[0xA8B238]`; the callees
//   `CALL 0x4F9F90` (HouseClass::MakeEnemy) and `CALL 0x4F9B70`
//   (HouseClass::MakeAlly), both __thiscall with (house, 0) pushed. Names
//   cross-checked against YRpp;
//   declaration style follows match/economy/house_class_can_ally_methods.h
//   and the inlined IsControlledByHuman shape of house_class_accessor_methods.
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_ALLY_AI_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_ALLY_AI_METHODS_H

#include <stddef.h>
#include "../_layout/session_class.h"
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

// RulesClass — the byte that forces AI alliances.
struct Rules_00501640
{
    char _pad000[0x14B5];   // +0x0000
    bool At_14B5;           // +0x14B5
};
GG_STATIC_ASSERT(offsetof(Rules_00501640, At_14B5) == 0x14B5);
// GLOBAL: GAMEMD 0x8871E0 — RulesClass::Instance.
extern Rules_00501640* DAT_008871E0;

// ScenarioClass — the byte that suppresses AI alliances.
struct Scenario_00501640
{
    char _pad000[0x11E0];   // +0x0000
    char At_11E0;           // +0x11E0  (bool)
};
GG_STATIC_ASSERT(offsetof(Scenario_00501640, At_11E0) == 0x11E0);
// GLOBAL: GAMEMD 0xA8B230 — ScenarioClass::Instance.
extern Scenario_00501640* DAT_00A8B230;

// Declaration order matters — see match/_rt/gg_vslot.h.
struct ModeVtbl_00501640;

// The object at 0xA8B23C, asked through its second virtual slot.
struct Mode_00501640
{
    ModeVtbl_00501640* Vtbl;   // +0x0000
};
typedef bool (Mode_00501640::*Fn4_00501640)();
struct ModeVtbl_00501640
{
    char          _pad000[4];   // +0x0000
    Fn4_00501640  At_4;         // +0x0004
};
GG_STATIC_ASSERT(offsetof(ModeVtbl_00501640, At_4) == 0x4);
// GLOBAL: GAMEMD 0xA8B23C — the game-mode object queried before allying.
extern Mode_00501640* DAT_00A8B23C;


// HouseClass — only the members AllyAIHouses touches.
struct House_00501640
{
    char _pad000[0x1EC];          // +0x0000
    bool IsHumanPlayer;           // +0x01EC
    bool IsInPlayerControl;       // +0x01ED
    char _pad1EE[0x1F5 - 0x1EE];  // +0x01EE
    bool Defeated;                // +0x01F5
    char _pad1F6[0x24A - 0x1F6];  // +0x01F6
    bool At_24A;                  // +0x024A  set once the AI house has allied

    // FUNCTION: GAMEMD 0x50B730 (inlined here) — HouseClass::IsControlledByHuman.
    bool IsControlledByHuman() const
    {
        if (Session_00A8B238.GameMode != 0) {
            return IsHumanPlayer;
        }
        bool result = IsHumanPlayer;
        result = result || IsInPlayerControl;
        return result;
    }

    // FUNCTION: GAMEMD 0x4F9B70 (decl; reloc) — HouseClass::MakeAlly.
    void MakeAlly(House_00501640* who, bool announce);
    // FUNCTION: GAMEMD 0x4F9F90 (decl; reloc) — HouseClass::MakeEnemy.
    void MakeEnemy(House_00501640* who, bool announce);

    // FUNCTION: GAMEMD 0x501640 — HouseClass::AllyAIHouses (`this` unused).
    void AllyAIHouses();
};
GG_STATIC_ASSERT(offsetof(House_00501640, IsHumanPlayer)     == 0x1EC);
GG_STATIC_ASSERT(offsetof(House_00501640, IsInPlayerControl) == 0x1ED);
GG_STATIC_ASSERT(offsetof(House_00501640, Defeated)          == 0x1F5);
GG_STATIC_ASSERT(offsetof(House_00501640, At_24A)            == 0x24A);

// GLOBAL: GAMEMD 0xA8022C — HouseClass::Array.Items.
extern House_00501640** DAT_00A8022C;
// GLOBAL: GAMEMD 0xA80238 — HouseClass::Array.Count.
extern int DAT_00A80238;

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_ALLY_AI_METHODS_H
