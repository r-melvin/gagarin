// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x456580.

#include "foundation_occupy_methods.h"

// FUNCTION: GAMEMD 0x456580
//
// Mark every cell of the object's foundation as occupied by it, then record that
// it is placed.
//
// PARTIAL (74.3%, 26/35) — identical multiset, scheduling only. Retail loads
// the object's own coordinate before the foundation entry's in both sums
// (`MOV EAX,[ESI+0x208]; MOV EDX,[ECX+EDI*8]; ADD EAX,EDX`), computes the x
// sum first and pushes y, x, receiver; cl 8804 loads the entry's component
// first in both sums and computes y first. Binding the entry to a pointer
// local, which is what retail's `LEA ECX,[ECX+EDI*8]` between the two
// component loads describes, lifts this from the 68.6% the earlier pass
// recorded to 74.3% — the item address is formed once and both components
// come off it.
//
// Variants measured this pass, all 74.3% unless noted: the entry as a pointer
// local, as a `const&` and as a by-value copy (28.6%, a real struct copy);
// the sums as `member; += entry`, as `entry + member`, and through an inline
// `SumRL(b, a) { return a + b; }` helper exploiting cl's right-to-left
// argument evaluation to make the member the first operand evaluated; the
// whole cell-mark lifted into an inline helper taking the base coordinates
// and the entry pointer (the flattened-boundary lever); an inline forwarder
// with its parameters declared `(o, y, x)` so that cl's right-to-left order
// evaluates x first, both with by-value and `const&` parameters; and the
// base coordinates read through `const&` locals. The 68.6% forms (both sums
// written inline in the call, and locals without the entry pointer) are
// strictly worse. cl's load order inside a two-term sum is not reachable
// from source here — the remaining nine positions are that tie-break.
//
// The cell count is re-read on every iteration — retail's `MOV EAX,[EBX+0x10]` at
// 0x4565CA is inside the loop — so the bound stays a member read.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply here.
// Retail's callee-saved pushes sit exactly where ours do (prologue EBX, ESI,
// EDI on both sides), the
// number of epilogues agrees, and the compiled block order already matches,
// so there are no merged return blocks to split. The residual is register
// naming downstream of that, not a prologue hoist.
void BuildingClass_00456580::FUN_00456580()
{
    CellList_00456580* cells = DAT_0087F7E8.FUN_00656580(this->Foundation);

    int i = 0;
    while (i < cells->Count) {
        Offset_00456580* entry = &cells->Items[i];
        int x = this->X + entry->X;
        int y = this->Y + entry->Y;
        DAT_0087F7E8.FUN_00655560(this, x, y);
        i++;
    }

    this->At_423 = 1;
}
