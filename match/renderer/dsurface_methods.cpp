// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// Retail-compatible DSurface methods; no constructors or deleting wrapper.
// Provenance: frozen M2 entry-origin bodies, checked against retail.
#include <string.h>
#include "dsurface_class.h"

// FUNCTION: GAMEMD 0x4BAD60
int DSurface::GetBytesPerPixel()
{
    return BytesPerPixel;
}

// FUNCTION: GAMEMD 0x4BAD70
unsigned int DSurface::GetPitch()
{
    return Desc->lPitch;
}

// FUNCTION: GAMEMD 0x4BAD80
void* DSurface::Lock(Point2D origin)
{
    if (!DAT_0089F978 && !DAT_00A8ED80)
        return 0;
    if (!Recover())
        return 0;
    if (origin.X < 0 || origin.Y < 0)
        return 0;
    if (LockLevel == 0) {
        DDSurfaceDesc desc;
        memset(&desc, 0, sizeof(desc));
        desc.dwSize = sizeof(desc);
        if (DDSurf->lpVtbl->Lock(DDSurf, 0, &desc, 1, 0))
            return 0;
        *Desc = desc;
        BytesPerPixel = (Desc->dwRGBBitCount + 7) >> 3;
        InVideoMemory = (Desc->dwCaps >> 14) & 1;
        Buffer = Desc->lpSurface;
    }
    ++LockLevel;
    return (char*)Buffer + (GetPitch() * origin.Y + GetBytesPerPixel() * origin.X);
}

// FUNCTION: GAMEMD 0x4BAEC0
bool DSurface::unknown_64(unsigned int, unsigned int)
{
    if (LockLevel == 0) {
        DDSurfaceDesc desc;
        memset(&desc, 0, sizeof(desc));
        desc.dwSize = sizeof(desc);
        if (DDSurf->lpVtbl->Lock(DDSurf, 0, &desc, 0, 0))
            return false;
        DDSurf->lpVtbl->Unlock(DDSurf, desc.lpSurface);
    }
    return true;
}

// FUNCTION: GAMEMD 0x4BAF20
bool DSurface::unknown_94()
{
    return DDSurf->lpVtbl->GetBltStatus(DDSurf, 1) == 0;
}

// FUNCTION: GAMEMD 0x4BAF40
bool DSurface::Unlock()
{
    if (DAT_0089F978 || DAT_00A8ED80)
        Recover();
    if (LockLevel > 0) {
        if (--LockLevel == 0) {
            DDSurf->lpVtbl->Unlock(DDSurf, Buffer);
            Buffer = 0;
        }
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x4C1A90
bool DSurface::CopyFromWhole(Surface* src, bool a, bool b)
{
    return XSurface::CopyFromWhole(src, a, b);
}

// FUNCTION: GAMEMD 0x4C1AB0
bool DSurface::unknown_84()
{
    return true;
}
