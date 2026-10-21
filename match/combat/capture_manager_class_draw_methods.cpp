// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x472640.

#include "capture_manager_class_draw_methods.h"

// FUNCTION: GAMEMD 0x472640  CaptureManagerClass::NeedsToDrawLinks (__thiscall)
// Mind-control links are drawn when either end is selected, or while any link
// is still inside its fade window. Retail walks the node list *descending* and
// gives each `return true` its own epilogue rather than setting a flag.
bool CaptureManagerClass::NeedsToDrawLinks()
{
    if (((ObjectClass*)Owner)->IsSelected)
        return true;

    if (((TechnoClass*)Owner)->Transporter != 0
        && ((ObjectClass*)((TechnoClass*)Owner)->Transporter)->IsSelected)
        return true;

    for (int i = ControlNodes.Count - 1; i >= 0; i--) {
        ControlNode* node = ((ControlNode**)ControlNodes.Items)[i];

        if (((ObjectClass*)node->Unit)->IsSelected)
            return true;

        int remaining = node->Duration;
        if (node->StartFrame != -1) {
            int elapsed = CurrentFrame - node->StartFrame;
            if (elapsed >= remaining)
                continue;

            remaining -= elapsed;
        }

        if (remaining > 0)
            return true;
    }

    return false;
}
