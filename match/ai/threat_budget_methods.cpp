// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes diffed against retail gamemd.exe v1.001 at 0x45ED50.

#include "threat_budget_methods.h"

// FUNCTION: GAMEMD 0x45ED50
//
// Start from the base budget, and when this object is the one the host's pair
// points at — and the host is not in the suppressed state — take off half the
// two measurements. Whatever the trailing object measures comes off as well,
// and that result is clamped at zero; the early exit is not clamped.
//
// PARTIAL (56.6%, 30/53). Everything up to and including the pair adjustment is
// byte-exact, including the callee-saved naming (budget in ESI, the pair entry
// in EDI). The whole residual is the trailing object: retail parks it in EBX —
// reusing the register that held `this`, which dies at that load — and pays a
// `MOV ECX,EBX` before the slot call, where VC6 loads it straight into ECX and
// skips the copy. Everything after is the same instruction stream renamed.
//
// The ESI/EDI half was fixed by phrasing: subtracting into a fresh local
// (`int r = budget - ...`) rather than back into `budget` lowers the budget
// variable's use count, and VC6 hands ESI to the lighter of the two. Written as
// `budget -= ...; return budget > 0 ? budget : 0` the names come out swapped
// (47.2%).
//
// The EBX half is not source-selectable so far. Rejected, all 56.6% or worse:
// a `this`-walking local reassigned to the trailing object; a `for`/`while`
// whose induction variable starts at `this` and whose body always returns; a
// reference instead of a pointer; re-reading `this->At_EA0` twice and letting
// CSE pick the register; a static inline wrapper around the slot call; a
// genuine `virtual` at slot 43 instead of the member-pointer idiom; declaring
// the locals `register`; and the flag sweep /G3 /G5 /G6 /GB /Gr /Gd /Zp1 /Oa
// /Ow /Gf /Ob0 /Ob2 /Ox (all identical). /O1 /Os and dropping /Oy change the
// whole function and score 0%.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply here.
// Retail's callee-saved pushes sit exactly where ours do (prologue EBX, EBP,
// ESI, EDI on both sides, none sunk), the
// number of epilogues agrees, and the compiled block order already matches,
// so there are no merged return blocks to split. The residual is register
// naming downstream of that, not a prologue hoist.
int BuildingTypeClass_0045ED50::FUN_0045ED50()
{
    int budget = FUN_00711EB0();
    Host_0045ED50* host = DAT_008871E0;
    BuildingTypeClass_0045ED50** pair = host->At_B5C;
    BuildingTypeClass_0045ED50* first = pair[0];

    if (this == *first->At_3EC && host->At_17E8 == 0) {
        BuildingTypeClass_0045ED50* second = pair[1];

        budget += -(((second->*second->Vptr->At_AC)()
                     + (first->*first->Vptr->At_AC)()) / 2);
    }

    BuildingTypeClass_0045ED50* trailing = this->At_EA0;
    if (trailing != 0) {
        int result = budget - (trailing->*trailing->Vptr->At_AC)();
        return result > 0 ? result : 0;
    }

    return budget;
}
