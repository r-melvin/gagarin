// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | linear objdump decode of the retail bytes
//   BuildingClass primary-table slot 81 (+0x144): the reaction to an event code (1, 4, 5 and 0x37 are handled,
//   everything else just returns true). Span 0x443410..0x4436EB (0x2DB bytes, no tables). The method names are slot
//   labels / FUN_<addr>; no original name is confirmed.
// CAPPED (final) at 70.0% positional (156/223, 141 exact + 15 reloc-normalised), 76.7% by sequence alignment; the instruction
// multiset is identical to retail (223 vs 223) and the frame (0x8C), every offset and the whole mode 4 / mode 5 / mode 1 cell
// paths match. Delta: for modes 0x37 and 1 retail keeps the FIRST copy of the queue-insert code (right after the mode 0x37 event
// constructor) and cross-jumps the mode 1 path back to it; the compiler here keeps the LAST copy (mode 0x37 jumps forward), which shifts
// every later branch target and the shared `return true` epilogue by 7 bytes.
// Variants tried: named buffers for the target references (frame 0x98), temporaries for them (matches), constructor against member
// forms of the event, a goto-shared queue label, a mode-1-before-0x37 order (48%), a switch (jump table), head-first and count-first
// store order of the ring buffer (mode 4 uses head first, modes 0x37 / 1 count first).

#include "building_a3_views.h"
// The 256-lepton cell a coordinate lies in.
inline HBCell BA3CellOf(const HBCoord& where)
{
    HBCell cell;
    cell.X = (short)(where.X / 256);
    cell.Y = (short)(where.Y / 256);
    return cell;
}
// FUNCTION: GAMEMD 0x443410
bool BuildingA3View::vf_81(int mode, BA3ObjView* target, int unused)
{
    if (mode == 5) {
        if (target) {
            vf_222(1, target, 0, 0);
            return true;
        }
    } else if (mode == 4) {
        if (Type->unknown_EB8 != 0) {
            BA3QueueEventHeadFirst(BA3Event(vf_14(), 0x11, BA3TargetRef(this)));
        }
        if (Type->unknown_CD1) {
            vf_222(0x10, target, 0, 0);
        }
        if (Type->unknown_16AE || Type->unknown_16AF) {
            vf_222(0x10, target, 0, 0);
        }
        if (vf_258() > 0) {
            vf_222(0x10, target, 0, 0);
            return true;
        }
    } else if (mode == 0x37) {
        BA3QueueEvent(BA3Event(unknown_38->unknown_28->unknown_30, 10, BA3TargetRef(this)));
        return true;
    } else if (mode == 1) {
        int kind = Type->unknown_EB8;
        if (kind == 0x10 || kind == 0x28 || kind == 3) {
            FUN_00443860(BA3CellOf(target->vf_18()), 1);
            return true;
        }
        BA3QueueEvent(BA3Event(vf_14(), 0x1E, BA3TargetRef(this), BA3TargetRef(target)));
    }
    return true;
}
