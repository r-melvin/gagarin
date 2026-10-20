// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// BSurface vtable 0x7E2070 slots +0x70/+0x74 select these entry-origin bodies.
#include "bsurface_class.h"

// FUNCTION: GAMEMD 0x411630
int BSurface::GetBytesPerPixel()
{
    return BytesPerPixel;
}

// FUNCTION: GAMEMD 0x411640
unsigned int BSurface::GetPitch()
{
    return GetWidth() * BytesPerPixel;
}
