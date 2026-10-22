// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
//   Measured: the holder is a scope object whose destructor is the release,
//   and under the locked /GX cl wraps the scope in an unwind frame retail has
//   no trace of (0% against a body that is otherwise instruction-for-
//   instruction correct). Without /GX the prologue is retail's bare four
//   pushes. Same category as match/platform/ccini_class_type_list_methods.cpp.
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   The flyer's per-frame draw offset. Bytes diffed against the user's retail
//   gamemd.exe v1.001.
#include "fly_locomotion_draw_offset_methods.h"

// VTABLE: GAMEMD 0x7E89F4 — the locomotor interface vtable (base offset 4).
// GLOBAL: GAMEMD 0x822410 — the queried interface id.
// GLOBAL: GAMEMD 0xA8ED84 — Unsorted::CurrentFrame.
// GLOBAL: GAMEMD 0x7E8AF0 — double pi/10, one bob cycle per twenty frames.
// GLOBAL: GAMEMD 0x7E48F0 — double 1.5, the bob amplitude.
// GLOBAL: GAMEMD 0x7E1738 — double 0.5, the rounding bias.

// ILocomotion slot +0x2C — the draw offset for a flyer. A flyer that is
// neither a ground-hugging type nor landing nor taking off, and that is
// higher above the ground than the interface it aggregates says it needs to
// be, bobs on a twenty-frame sine; everything else sits still. The X
// component is always zero.
//
// Three levers, measured in this order from a 72.3% first draft whose
// instruction multiset was already identical to retail's. The release written
// as an explicit statement before the return lets cl sink both component
// stores past it (72.3%); making it the holder's destructor puts them where
// retail has them but emits the destructor out of line (74.5%); defining that
// destructor in-class expands it (88.3%). The last eleven instructions were a
// two-slot frame exchange - retail keeps the holder in the dead receiver's
// home slot and the query's out-parameter in the frame's one real slot, cl
// the other way round - and it is decided by where the holder is declared
// relative to the receiver read: after it, 100%; before it, 88.3%; with the
// out-parameter hoisted to function scope ahead of it, 84.0%.
// FUNCTION: GAMEMD 0x4CF830
Pair_004CF830 __stdcall FlyLocoOffset::GetDrawOffset()
{
    int bob = 0;
    Foot_004CF830* client = this->LinkedTo;
    Holder_004CF830 held;
    held.Held = 0;

    if (client != 0) {
        IFace_004CF830* got;
        long hr = client->Vtbl->QueryInterface(client, riid_00822410,
                                               (void**)&got);
        if (hr < 0) {
            FUN_004D0430(&held);
            held.Held = 0;
        } else {
            IFace_004CF830* taken = got;
            FUN_004D0430(&held);
            held.Held = taken;
        }
        if (hr < 0 && hr != 0x80004002) {
            FUN_007DC720(hr);
        }
    }

    int clearance = 0;
    if (held.Held != 0) {
        clearance = held.Held->Vtbl->GetGroundClearance(held.Held);
    }

    if ((this->LinkedTo->*this->LinkedTo->Vtbl->At_84)()->IsFlatOnGround == 0 &&
        this->IsLanding == 0 && this->IsTakingOff == 0 &&
        (this->LinkedTo->*this->LinkedTo->Vtbl->At_1C8)() > clearance) {
        bob = (int)(FUN_004CACB0((double)(CurrentFrame % 20)
                                 * 0.3141592653589793) * 1.5 + 0.5);
    }

    Pair_004CF830 result;
    result.A = 0;
    result.B = bob;
    return result;
}
