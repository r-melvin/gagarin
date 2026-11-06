// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra. The Direct3D COM interfaces the renderer setup at 0x4C16A0 reaches
// through the globals 0x8A0DF4 (the Direct3D interface queried from the DirectDraw object), 0x8A0DF8 (the
// device it creates) and 0x8A0DFC (the viewport); only the slots observed at the call sites are typed, and
// every slot offset is read from those call sites. Observed structure sizes: the viewport block is 0x2C
// bytes (dwSize in its first dword), each device description 0xFC bytes.
#ifndef GG_MATCH_RENDERER_DIRECT3D_INTERFACE_VIEW_H
#define GG_MATCH_RENDERER_DIRECT3D_INTERFACE_VIEW_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"

struct _GUID;
struct DDSurface;
struct Direct3DInterfaceView;
struct Direct3DDeviceView;
struct Direct3DViewportView;
struct Direct3DViewportDesc;
struct Direct3DDeviceDesc;

typedef unsigned long (__stdcall* Direct3DReleaseFn)(Direct3DInterfaceView*);
typedef long (__stdcall* Direct3DCreateViewportFn)(Direct3DInterfaceView*, Direct3DViewportView**, void*);
typedef long (__stdcall* Direct3DCreateDeviceFn)(Direct3DInterfaceView*, const _GUID*, DDSurface*, Direct3DDeviceView**);

struct Direct3DVtablePrefix
{
    void* unknown_00[2];
    Direct3DReleaseFn Release;                 // +0x08
    void* unknown_0C[3];
    Direct3DCreateViewportFn CreateViewport;   // +0x18
    void* unknown_1C;
    Direct3DCreateDeviceFn CreateDevice;       // +0x20
};
GG_STATIC_ASSERT(offsetof(Direct3DVtablePrefix, Release) == 0x08);
GG_STATIC_ASSERT(offsetof(Direct3DVtablePrefix, CreateViewport) == 0x18);
GG_STATIC_ASSERT(offsetof(Direct3DVtablePrefix, CreateDevice) == 0x20);
struct Direct3DInterfaceView { const Direct3DVtablePrefix* lpVtbl; };

typedef unsigned long (__stdcall* Direct3DDeviceReleaseFn)(Direct3DDeviceView*);
typedef long (__stdcall* Direct3DDeviceGetCapsFn)(Direct3DDeviceView*, Direct3DDeviceDesc*, Direct3DDeviceDesc*);
typedef long (__stdcall* Direct3DDeviceAddViewportFn)(Direct3DDeviceView*, Direct3DViewportView*);

struct Direct3DDeviceVtablePrefix
{
    void* unknown_00[2];
    Direct3DDeviceReleaseFn Release;           // +0x08
    Direct3DDeviceGetCapsFn GetCaps;           // +0x0C
    void* unknown_10[2];
    Direct3DDeviceAddViewportFn AddViewport;   // +0x18
    void* unknown_1C[6];
    Direct3DDeviceAddViewportFn SetCurrentViewport; // +0x34
};
GG_STATIC_ASSERT(offsetof(Direct3DDeviceVtablePrefix, Release) == 0x08);
GG_STATIC_ASSERT(offsetof(Direct3DDeviceVtablePrefix, GetCaps) == 0x0C);
GG_STATIC_ASSERT(offsetof(Direct3DDeviceVtablePrefix, AddViewport) == 0x18);
GG_STATIC_ASSERT(offsetof(Direct3DDeviceVtablePrefix, SetCurrentViewport) == 0x34);
struct Direct3DDeviceView { const Direct3DDeviceVtablePrefix* lpVtbl; };

typedef unsigned long (__stdcall* Direct3DViewportReleaseFn)(Direct3DViewportView*);
typedef long (__stdcall* Direct3DViewportSetFn)(Direct3DViewportView*, Direct3DViewportDesc*);

struct Direct3DViewportVtablePrefix
{
    void* unknown_00[2];
    Direct3DViewportReleaseFn Release;         // +0x08
    void* unknown_0C[14];
    Direct3DViewportSetFn SetViewport2;        // +0x44
};
GG_STATIC_ASSERT(offsetof(Direct3DViewportVtablePrefix, Release) == 0x08);
GG_STATIC_ASSERT(offsetof(Direct3DViewportVtablePrefix, SetViewport2) == 0x44);
struct Direct3DViewportView { const Direct3DViewportVtablePrefix* lpVtbl; };

// The viewport block handed to SetViewport2: size, the rectangle, the clip extents as floats and the far depth.
struct Direct3DViewportDesc
{
    unsigned long dwSize;          // +0x00 (0x2C)
    unsigned long unknown_04[2];   // +0x04
    unsigned long dwWidth;         // +0x0C
    unsigned long dwHeight;        // +0x10
    unsigned long unknown_14[2];   // +0x14
    float ClipWidth;               // +0x1C
    float ClipHeight;              // +0x20
    float unknown_24;              // +0x24
    float MaxZ;                    // +0x28 (1.0)
};
GG_STATIC_ASSERT(offsetof(Direct3DViewportDesc, dwWidth) == 0x0C);
GG_STATIC_ASSERT(offsetof(Direct3DViewportDesc, ClipWidth) == 0x1C);
GG_STATIC_ASSERT(offsetof(Direct3DViewportDesc, ClipHeight) == 0x20);
GG_STATIC_ASSERT(offsetof(Direct3DViewportDesc, MaxZ) == 0x28);
GG_STATIC_ASSERT(sizeof(Direct3DViewportDesc) == 0x2C);

// The device description GetCaps fills (0xFC bytes); only the words the capability check tests are named.
struct Direct3DDeviceDesc
{
    unsigned long dwSize;          // +0x00 (0xFC)
    unsigned long unknown_04;      // +0x04 (mask 0x1C3 required)
    unsigned long unknown_08;      // +0x08 (bit 1 tested)
    unsigned long unknown_0C;      // +0x0C (bits 10 and 9 tested)
    unsigned long unknown_10[(0x70 - 0x10) / 4];
    unsigned long unknown_70;      // +0x70 (mask 0xA tested)
    unsigned long unknown_74;      // +0x74 (bit 1 tested)
    unsigned long unknown_78;      // +0x78 (bit 1 tested)
    unsigned long unknown_7C[(0x9C - 0x7C) / 4];
    unsigned long unknown_9C;      // +0x9C (bit 10 tested)
    unsigned long unknown_A0;      // +0xA0 (bit 10 tested)
    unsigned long unknown_A4[(0xB4 - 0xA4) / 4];
    unsigned long unknown_B4;      // +0xB4 (at least 0x100 required)
    unsigned long unknown_B8;      // +0xB8 (at least 0x100 required)
    unsigned long unknown_BC[(0xFC - 0xBC) / 4];
};
GG_STATIC_ASSERT(offsetof(Direct3DDeviceDesc, unknown_04) == 0x04);
GG_STATIC_ASSERT(offsetof(Direct3DDeviceDesc, unknown_70) == 0x70);
GG_STATIC_ASSERT(offsetof(Direct3DDeviceDesc, unknown_9C) == 0x9C);
GG_STATIC_ASSERT(offsetof(Direct3DDeviceDesc, unknown_B4) == 0xB4);
GG_STATIC_ASSERT(offsetof(Direct3DDeviceDesc, unknown_B8) == 0xB8);
GG_STATIC_ASSERT(sizeof(Direct3DDeviceDesc) == 0xFC);

#endif
