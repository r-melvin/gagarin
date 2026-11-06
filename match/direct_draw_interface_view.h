// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra. DirectDraw COM prefix and slots observed | YRpp-cross-check
// at GAMEMD 0x8A0094; declarations stop after the last required slot.
#ifndef GG_MATCH_RENDERER_DIRECT_DRAW_INTERFACE_VIEW_H
#define GG_MATCH_RENDERER_DIRECT_DRAW_INTERFACE_VIEW_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"

struct DirectDrawInterfaceView;
struct DDSurfaceDesc;
struct DDSurface;
struct _GUID;
struct DirectDrawCaps;
typedef long (__stdcall* DirectDrawQueryInterfaceFn)(DirectDrawInterfaceView*, const _GUID*, void*);
typedef long (__stdcall* DirectDrawGetCapsFn)(DirectDrawInterfaceView*, DirectDrawCaps*, DirectDrawCaps*);
typedef unsigned long (__stdcall* DirectDrawReleaseFn)(DirectDrawInterfaceView*);
typedef long (__stdcall* DirectDrawRestoreDisplayModeFn)(DirectDrawInterfaceView*);
typedef long (__stdcall* DirectDrawCreateSurfaceFn)(
    DirectDrawInterfaceView*, DDSurfaceDesc*, DDSurface**, void*);

// Modeled prefix through +0x4C; unobserved later COM slots are omitted.
struct DirectDrawVtablePrefix
{
    DirectDrawQueryInterfaceFn QueryInterface; // +0x00
    void* unknown_04;
    DirectDrawReleaseFn Release; // +0x08
    void* unknown_0C[3];
    DirectDrawCreateSurfaceFn CreateSurface; // +0x18
    void* unknown_1C[4];
    DirectDrawGetCapsFn GetCaps; // +0x2C
    void* unknown_30[7];
    DirectDrawRestoreDisplayModeFn RestoreDisplayMode; // +0x4C
};
GG_STATIC_ASSERT(offsetof(DirectDrawVtablePrefix, QueryInterface) == 0x00);
GG_STATIC_ASSERT(offsetof(DirectDrawVtablePrefix, GetCaps) == 0x2C);
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

// The capability block GetCaps fills (0x13C bytes, DirectX 5 DDCAPS size, dwSize in the first dword); only the
// words the Direct3D setup tests are named.
struct DirectDrawCaps
{
    unsigned long dwSize;          // +0x00 (0x13C)
    unsigned long unknown_04;      // +0x04 (bit 0 tested)
    unsigned long unknown_08[(0x38 - 0x08) / 4];
    unsigned long unknown_38;      // +0x38 (bit 10 tested)
    unsigned long unknown_3C[(0x84 - 0x3C) / 4];
    unsigned long unknown_84;      // +0x84 (bits 13, 12 and 17 tested)
    unsigned long unknown_88[(0x13C - 0x88) / 4];
};
GG_STATIC_ASSERT(offsetof(DirectDrawCaps, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(DirectDrawCaps, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(DirectDrawCaps, unknown_84) == 0x84);
GG_STATIC_ASSERT(sizeof(DirectDrawCaps) == 0x13C);

// GLOBAL: GAMEMD 0x8A0094
extern DirectDrawInterfaceView* DAT_008A0094;


#endif
