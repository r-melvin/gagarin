// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Retail 0x4E12F0..0x4E133E establishes all stores and the conditional flag OR.
// Partial: 17/26 instructions (65.4%); remaining differences are load/store
// scheduling. Source rewrites, flag bisection and a validated bounded permuter
// run did not improve this complete, native C++ body.
#include "gadget_class_methods.h"

// FUNCTION: GAMEMD 0x4E12F0
GadgetClass::GadgetClass(int x, int y, int width, int height,
                         unsigned int flags, char sticky)
    : X(x), Y(y), Width(width), Height(height), RedrawPending(0),
      IsSticky(sticky), IsDisabled(0), Flags(flags)
{
    Next = 0;
    Previous = 0;
    if (sticky != 0) {
        Flags |= 5;
    }
}
