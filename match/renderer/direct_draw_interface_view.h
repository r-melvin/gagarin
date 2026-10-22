// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra. DirectDraw COM prefix and slots observed | YRpp-cross-check
// at GAMEMD 0x8A0094; declarations stop after the last required slot.
#ifndef GG_MATCH_RENDERER_DIRECT_DRAW_INTERFACE_VIEW_H
#define GG_MATCH_RENDERER_DIRECT_DRAW_INTERFACE_VIEW_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct DirectDrawInterfaceView;
struct DDSurfaceDesc;
struct DDSurface;
typedef unsigned long (__stdcall* DirectDrawReleaseFn)(DirectDrawInterfaceView*);
typedef long (__stdcall* DirectDrawRestoreDisplayModeFn)(DirectDrawInterfaceView*);
typedef long (__stdcall* DirectDrawCreateSurfaceFn)(
    DirectDrawInterfaceView*, DDSurfaceDesc*, DDSurface**, void*);

// Modeled prefix through +0x4C; unobserved later COM slots are omitted.
struct DirectDrawVtablePrefix
{
    void* unknown_00[2];
    DirectDrawReleaseFn Release; // +0x08
    void* unknown_0C[3];
    DirectDrawCreateSurfaceFn CreateSurface; // +0x18
    void* unknown_1C[12];
    DirectDrawRestoreDisplayModeFn RestoreDisplayMode; // +0x4C
};
GG_STATIC_ASSERT(offsetof(DirectDrawVtablePrefix, Release) == 0x08);
GG_STATIC_ASSERT(offsetof(DirectDrawVtablePrefix, CreateSurface) == 0x18);
GG_STATIC_ASSERT(offsetof(DirectDrawVtablePrefix, RestoreDisplayMode) == 0x4C);
GG_STATIC_ASSERT(sizeof(DirectDrawVtablePrefix) == 0x50);

// Only the interface vptr prefix is modeled, not a complete COM object.
struct DirectDrawInterfaceView
{
    const DirectDrawVtablePrefix* lpVtbl;
};
GG_STATIC_ASSERT(offsetof(DirectDrawInterfaceView, lpVtbl) == 0);
GG_STATIC_ASSERT(sizeof(DirectDrawInterfaceView) == 4);

// GLOBAL: GAMEMD 0x8A0094
extern DirectDrawInterfaceView* DAT_008A0094;


#endif
