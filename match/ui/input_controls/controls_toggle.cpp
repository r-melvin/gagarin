// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Flag bisection: a paired /GX probe of every entry in this TU produced the same scores as the
// line above. /GX is omitted because controls_static_button.cpp shows retail has no unwind code.
//
// ToggleClass::Action. The layout is match/ui/toggle_class_methods.h, used unchanged:
// +0x2C (unknown_2C) is the pressed flag, +0x2D (IsOn) the latched state and +0x30
// (unknown_30) the latch style (1 toggles, 2 only switches on), as the stores below show.
#include "controls_views.h"


// FUNCTION: GAMEMD 0x723EC0
// CAPPED at 65.4% (83 of 127 instructions; multiset delta: retail has 2 `jmp` more; ours duplicates the
// closing `ControlClass::Action` call, 6 `push`, 4 `mov`, 2 `call`, 6 `pop` and 2 `ret`). The first 0xB0
// bytes (mouse hit test, redraw on hover, press handling) are exact. In the release branch retail
// jumps from the latched-toggle path to the one shared `ControlClass::Action(flags, key, 0)` tail
// after loading the vtable slot before the `sete`/store; cl instead copies the tail into the branches.
// Variants tried: explicit per-style blocks (63%), the shared clear-and-redraw form (this), and the
// inverted `!unknown_2C` arm first (63.2%).
int ToggleClass::Action(unsigned flags, unsigned* key, int modifier)
{
    bool inside = (unsigned)(DAT_00887640->GetX() - X) < (unsigned)Width
        && (unsigned)(DAT_00887640->GetY() - Y) < (unsigned)Height;

    if (flags == 0) {
        if (inside) {
            if (!unknown_2C) {
                unknown_2C = 1;
                MarkRedraw();
            }
        } else if (unknown_2C) {
            unknown_2C = 0;
            MarkRedraw();
        }
    }
    StickyProcess(flags);

    if (flags & 0x11) {
        unknown_2C = 1;
        MarkRedraw();
        flags &= ~0x11;
        ControlClass::Action(flags, key, 0);
        *key = 0;
        return 1;
    }
    if (flags & 0x44) {
        if (unknown_2C) {
            if (inside) {
                if (unknown_30 == 1)
                    IsOn = !IsOn;
                else if (unknown_30 == 2 && !IsOn)
                    IsOn = 1;
            }
            unknown_2C = 0;
            MarkRedraw();
        } else {
            flags &= ~0x44;
        }
    }
    return ControlClass::Action(flags, key, 0);
}
