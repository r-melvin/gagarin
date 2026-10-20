// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes diffed against retail gamemd.exe v1.001 at 0x472160.

#include "capture_manager_class_draw_links_methods.h"

// FUNCTION: GAMEMD 0x472160  CaptureManagerClass::DrawLinks (__thiscall)
//
// Draw the mind-control tethers. A link is drawn when either end is selected
// or the link's own count-down timer still has time on it; the line runs from
// the controller to the controlled unit's coordinate lifted by the unit type's
// +0x3DC, in the owning house's colour, with the per-link index cycling
// backwards through five offsets.
//
// PARTIAL (31.2%, 34/109; multiset is retail plus two `mov`). The control flow
// is instruction-for-instruction identical; what differs is callee-saved
// register naming across three long-lived locals. Retail keeps the loop index
// in EBP, the count-down remainder in the scratch EDX and the elapsed frames in
// ESI; VC6 puts the index in ESI and promotes the remainder into EBP, which
// then costs one extra spill: retail keeps the link coordinate's X in EBP and
// spills only Y, while VC6 spills both X and Y before the type call. Because
// the diff does not normalise register names the whole tail reads as divergent
// -- the honest measure is the two-instruction multiset delta. Variants tried:
// member-wise coordinate construction (23.9%); whole-struct copy
// `Coord from = unit->Location;` (31.2%, kept -- this is what puts `active` in
// BL as retail does); an inline by-value MakeCoord built in the pushed argument
// block (22.9%); `active` declared after the node/unit locals (31.2%, no
// change); the CDTimerClass read hand-inlined at the call site instead of
// through the member (31.2%, byte-identical output); the same read written as
// three early returns (16.2%).
// Lift pass 2 (2026-09-18): one more rejected - the whole CDTimerClass copied
// into a local before the test (`CDTimer_00472160 timer = node->Timer;`), the
// member-struct-copy lever that lifted 0x447AC0; here it spills all three timer
// words and drops to 16.8%. Re-read against retail the residual is a clean
// three-way register permutation with no instruction difference in the loop
// head: retail index->EBP, duration->EDX, elapsed->ESI; cl 8804
// index->ESI, duration->EBP, elapsed->EDX. That is the banked EBX/EBP
// callee-saved preference difference (0x50D440); best form kept at 31.2%.
//
// TAIL-MERGE DIAGNOSTIC (eleventh-batch lever): does NOT apply here.
// Retail's callee-saved pushes sit exactly where ours do (prologue EBX, EBP,
// ESI, EDI on both sides, none sunk), the
// number of epilogues agrees, and the compiled block order already matches,
// so there are no merged return blocks to split. The residual is register
// naming downstream of that, not a prologue hoist.
void CaptureManager_00472160::DrawLinks()
{
    bool ownerSelected = false;
    if (Owner->IsSelected)
        ownerSelected = true;

    for (int i = ControlNodes_Count - 1; i >= 0; i--)
    {
        bool active = false;

        ControlNode_00472160* node = ControlNodes_Items[i];
        Unit_00472160* unit = node->Unit;

        if (node->Timer.GetTimeLeft() > 0)
            active = true;

        if (unit->IsSelected)
            active = true;

        if (Owner != 0 && unit != 0 && (ownerSelected || active))
        {
            Coord_00472160 from = unit->Location;
            from.Z = from.Z + (unit->*unit->Vptr->GetType)()->unknown_3DC;

            Owner_00472160* owner = Owner;
            Color_00472160 color = owner->Owner->LinkColor;
            Coord_00472160 offset;
            offset.X = 0;
            offset.Y = 0;
            offset.Z = 0;

            Owner->FUN_00704E40(
                (owner->*owner->Vptr->At_B0)(-1 - (i % 5), offset, from, color));
        }
    }
}
