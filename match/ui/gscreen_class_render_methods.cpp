// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Bytes matched against retail gamemd.exe v1.001 at 0x4F42F0 and 0x4F4480.

#include "gscreen_class_render_methods.h"
#include "../renderer/dsurface_class.h"

// FUNCTION: GAMEMD 0x4F42F0
//
// GScreenClass::FlagToRedraw, slot 14 of GScreenClass's vtable 0x7EA6FC and of
// every derived map layer's. Flag the tactical view for redraw, latch the
// redraw mode unless a full redraw (2) is already pending, and bump the map's
// redraw counter.
void GScreen_004F4480::FlagToRedraw(int mode)
{
    if (DAT_00887324)
    {
        DAT_00887324->NeedsRedraw = 1;
    }
    if (mode != 0)
    {
        if (this->RedrawFlag != 2)
        {
            this->RedrawFlag = mode;
        }
        DAT_0087F7E8.FUN_00578AC0();
    }
}

// FUNCTION: GAMEMD 0x4F4480
//
// One frame of screen drawing. The temp surface is pointed at the composite
// for the duration; the mouse is taken off it, the redraw flag is consumed
// (any value = redraw, 2 = full), the tactical view is rendered in its three
// passes around this object's own +0x40 pass unless the global check says
// drawing is off, the sidebar gets its mouse pass when flagged, the optional
// overlays, message list, tooltip and debug output are drawn, the mouse is
// put back, this object's +0x44 pass runs and the temp surface is restored.
void GScreen_004F4480::Render()
{
    Surface* saved = DAT_00887314;
    DAT_00887314 = DAT_0088731C;
    (DAT_00887640->*DAT_00887640->Vtbl->At_40)(DAT_0088731C, false);

    bool any  = this->RedrawFlag != 0;
    bool full = this->RedrawFlag == 2;
    this->RedrawFlag = 0;

    if (!FUN_0053BAE0()) {
        DAT_00887324->Render(DAT_0088731C, any, 0);
        DAT_00887324->Render(DAT_0088731C, any, 1);
        (this->*this->Vtbl->At_40)(full);
        DAT_00887324->Render(DAT_0088731C, any, 2);
    }

    if (DAT_00B0B519 && !DAT_00A8ED6B) {
        (DAT_00887640->*DAT_00887640->Vtbl->At_40)(DAT_00887300, true);
        DAT_00B0B519 = false;
    }

    if (DAT_00A8EF54) {
        (DAT_00A8EF54->*DAT_00A8EF54->Vtbl->At_2C)(0);
    }
    DAT_00A8BC60.Draw();
    if (DAT_00887368) {
        (DAT_00887368->*DAT_00887368->Vtbl->At_0C)(0);
    }
    if (DAT_00A8B8B4) {
        FUN_0055F1E0(false);
    }

    (DAT_00887640->*DAT_00887640->Vtbl->At_3C)(DAT_0088731C, false);
    (this->*this->Vtbl->At_44)();
    DAT_00887314 = saved;
}
