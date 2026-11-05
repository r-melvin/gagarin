// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The buffered surface pair retail expands inline at 0x4A699A and 0x52FEC0: XSurface
//   vtable 0x7E2104, then BSurface 0x7E2070, pixels through MemoryBuffer 0x43AD00. The
//   canonical BSurface header has no constructor and declares Surface's out of line.
#ifndef GG_MATCH_LAYOUT_DIB_SURFACE_H
#define GG_MATCH_LAYOUT_DIB_SURFACE_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "memory_buffer.h"

// VTABLE: GAMEMD 0x7E2104
struct DibSurfaceBase
{
    DibSurfaceBase(int width, int height) : Width(width), Height(height), LockLevel(0) {}
    virtual ~DibSurfaceBase();

    int Width;       // +0x04
    int Height;      // +0x08
    int LockLevel;   // +0x0C
};

// VTABLE: GAMEMD 0x7E2070
struct DibSurface : DibSurfaceBase
{
    DibSurface(int width, int height, int bpp, void* buffer)
        : DibSurfaceBase(width, height), BytesPerPixel(bpp), Pixels(buffer, width * height * bpp)
    {
    }
    virtual ~DibSurface();

    int          BytesPerPixel;   // +0x10
    MemoryBuffer Pixels;          // +0x14
};
GG_STATIC_ASSERT(offsetof(DibSurface, BytesPerPixel) == 0x10);
GG_STATIC_ASSERT(offsetof(DibSurface, Pixels) == 0x14);
GG_STATIC_ASSERT(sizeof(DibSurface) == 0x20);   // operator new(0x20) at 0x4A699A

#endif
