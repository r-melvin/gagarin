// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra.
// Private migration note: this is a provisional canonical-renderer TU for the
// Radar surface setup helper. Radar.cpp currently includes the legacy ui_common
// Surface declaration, which conflicts with renderer/surface_class.h; keep this
// body in the separate TU unless that ownership is explicitly revisited.

#include "input_controls/ui_display_chain.h"
#include "../renderer/bsurface_class.h"
#include "../renderer/dsurface_class.h"
#include "../_rt/gg_static_assert.h"
#include <new>
#include <stddef.h>

// Declaration: GAMEMD 0x7C8E17 -- library operator new(size_t) declaration used by this body.
extern "C" void* __cdecl FUN_007C8E17(unsigned int size);
// CALLEE: GAMEMD 0x7C8B3D -- library operator delete(void*) called by this body.
extern "C" void __cdecl FUN_007C8B3D(void* block);

GG_STATIC_ASSERT(offsetof(RadarClass, unknown_11F0) == 0x11F0);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_11F4) == 0x11F4);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_121C) == 0x121C);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1220) == 0x1220);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_123C) == 0x123C);
GG_STATIC_ASSERT(offsetof(RadarClass, unknown_1274) == 0x1274);
GG_STATIC_ASSERT(offsetof(RadarClass, RadarBounds) == 0x149C);
GG_STATIC_ASSERT(offsetof(RectangleStruct, X) == 0x00);
GG_STATIC_ASSERT(offsetof(RectangleStruct, Y) == 0x04);
GG_STATIC_ASSERT(offsetof(RectangleStruct, Width) == 0x08);
GG_STATIC_ASSERT(offsetof(RectangleStruct, Height) == 0x0C);
GG_STATIC_ASSERT(sizeof(BSurface) == 0x20);
GG_STATIC_ASSERT(sizeof(DSurface) == 0x24);
GG_STATIC_ASSERT(sizeof(void*) == 4);

// FUNCTION: GAMEMD 0x654650
void RadarClass::FUN_00654650()
{
    if (RadarBounds.Width <= 0 || RadarBounds.Height <= 0)
        return;

    RadarBounds.Y = 0;
    RadarBounds.X = 0;

    if (unknown_1220 != 0) {
        delete unknown_1220;
        unknown_1220 = 0;
    }
    if (unknown_123C != 0) {
        FUN_007C8B3D(unknown_123C);
        unknown_123C = 0;
    }
    if (unknown_1274 != 0) {
        FUN_007C8B3D(unknown_1274);
        unknown_1274 = 0;
    }

    // The native call returns a RectangleStruct through the hidden result
    // pointer, while both explicit rectangle arguments point at RadarBounds.
    RectangleStruct helperResult =
        FUN_006547C0(&RadarBounds, &RadarBounds, true);
    (void)helperResult;

    RadarBounds.Width = unknown_1220->GetWidth();
    RadarBounds.Height = unknown_1220->GetHeight();

    RadarBounds.X = unknown_11F0;
    if (RadarBounds.Width < 0x8C)
        RadarBounds.X += (0x8C - RadarBounds.Width) / 2;

    RadarBounds.Y = unknown_11F4;
    if (RadarBounds.Height < 0x6C)
        RadarBounds.Y += (0x6C - RadarBounds.Height) / 2;

    if (unknown_121C != 0) {
        delete unknown_121C;
        unknown_121C = 0;
    }

    void* storage = FUN_007C8E17(sizeof(DSurface));
    DSurface* made;
    if (storage != 0) {
        // The native code caches +0x1220 in EDI and uses that same pointer for
        // both calls, so retain a single source pointer across the callbacks.
        BSurface* surface = unknown_1220;
        int height = surface->GetHeight();
        int width = surface->GetWidth();
        made = new (storage) DSurface(width, height, true, false);
    } else {
        made = 0;
    }
    unknown_121C = made;
    unknown_121C->Fill(0);

    FUN_006563B0();
}
