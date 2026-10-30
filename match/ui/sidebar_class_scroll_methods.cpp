// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6A6A00.

#include "sidebar_class_scroll_methods.h"

// FUNCTION: GAMEMD 0x6A6A00
//
// Scrolls one sidebar column by one row. Refused while a dialog is up. A tab
// of -1 means the active tab. Scrolling up only needs the column not to be at
// the top; scrolling down first works out how many rows fit in the sidebar
// (the strip height less the bottom margin, which shrinks when the scenario
// flag at +0x34B8 is set, in 50-pixel rows), then allows the move while the
// observer's view is below its row cap, or while a normal player still has
// cameos below the last visible row. Either way the scroll target row moves
// and the redraw hook fires.
//
// PARTIAL (74.7%, 62/83). Three register-scheduling deltas remain, all with
// the same instruction multiset as retail:
//   * the margin: retail loads the scenario flag into EAX, tests it, then
//     materialises `MOV EAX,0x1A` between the TEST and the JZ; cl 8804 hoists
//     the constant above the flag load and tests the flag in EDI;
//   * the observer compare: retail loads TopRowIndex into EDI before the CDQ
//     /SUB/SAR halving and adds it into EAX (`ADD EAX,EDI; CMP EAX,EDX`); ours
//     halves first and adds into EDX (`ADD EDX,EAX; CMP EAX,EDX`), which then
//     also flips the branch sense (JLE vs JGE);
//   * the +0x48 increment/decrement temporaries and the vtable load use EAX
//     in retail and EDX/EDI here.
// Variants tried: margin as if/else, `= 0x1A; if (flag) = 0x12` (kept),
// `= 0x12; if (!flag) = 0x1A`, ternary, `-= 8`, `0x1A - (flag ? 8 : 0)`, a
// flag/bool local read first, the flag reused as the margin variable, and an
// inlined helper (ternary/helper/`-` forms go branchless NEG/SBB/AND); the
// compare as `top + rows/2 < limit`, `rows/2 + top < limit`, `limit > ...`
// (kept: it stops VC6 cross-jumping the two compares), a named `top`, a named
// `half`, a named `limit`, `top += rows/2`, and an inlined Half() helper; both
// success bodies as early-outs feeding one shared body (loses the shared false
// tail, 39.8%); strip as pointer, reference, and direct `Tabs[tab]`; the
// redraw hook as pointer-to-member and as a real virtual; `up` as bool, char,
// unsigned char and int; the function returning int. The remaining pattern
// (an immediate hoisted above an unrelated load, temps preferring EDX over
// EAX) matches the suspected 8447-vs-8804 scheduling class already recorded
// in the methodology. Re-probed this pass: a `top` local bound inside the
// observer arm, and `top` plus a named `half` with the sum written
// `half + top` (both 74.7%, the sum still lands in top's register), and the
// sum-first compare `half + top < limit` with those locals (51.8%, the two
// compares cross-jump again).
bool SidebarClass::Scroll(bool up, int tab)
{
    if (WSDialogCount) {
        return false;
    }
    if (tab == -1) {
        tab = this->unknown_539C;
    }
    StripClass* strip = &this->Strips[tab];

    if (up) {
        if (strip->TopRowIndex == 0) {
            return false;
        }
        strip->At_48 = strip->At_48 - 1;
        FlagToRedraw(0);
        return true;
    }

    int margin = 0x1A;
    if (ScenarioInstance->At_34B8) {
        margin = 0x12;
    }
    int rows = (DAT_00886F9C - DAT_00B0B4F8 - margin - 7 + DAT_00886F94) / 50;

    if (CurrentPlayer == Observer) {
        if (DAT_00884CF8 > strip->TopRowIndex + rows / 2) {
            strip->At_48 = strip->At_48 + 1;
            FlagToRedraw(0);
            return true;
        }
    } else {
        if ((strip->TopRowIndex + rows) * 2 < strip->CameoCount) {
            strip->At_48 = strip->At_48 + 1;
            FlagToRedraw(0);
            return true;
        }
    }
    return false;
}
