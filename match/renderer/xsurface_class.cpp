// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra. XSurface RTTI/vtable at 0x7E2104;
// method bodies and +0x0C field accesses confirmed at each entry below.
#include "xsurface_class.h"

// FUNCTION: GAMEMD 0x411560
void* XSurface::Lock(Point2D origin)
{
    ++unknown_0C;
    return 0;
}

// FUNCTION: GAMEMD 0x411570
bool XSurface::Unlock()
{
    --unknown_0C;
    return true;
}

// FUNCTION: GAMEMD 0x411580
bool XSurface::IsLocked()
{
    return unknown_0C != 0;
}

// FUNCTION: GAMEMD 0x411590
bool XSurface::unknown_84()
{
    return false;
}

// FUNCTION: GAMEMD 0x7BAF10
// Full 0x77-byte span through RET 8 at 0x7BAF84. Bounds are half-open XYWH.
unsigned int XSurface::unknown_8C(const Point2D& point, const XYWHStruct& bounds)
{
    unsigned int color = 0;
    if (point.X >= bounds.X && point.X < bounds.X + bounds.Width &&
        point.Y >= bounds.Y && point.Y < bounds.Y + bounds.Height) {
        void* buffer = Lock(point);
        if (buffer) {
            if (GetBytesPerPixel() == 2)
                color = *(unsigned short*)buffer;
            else
                color = *(unsigned char*)buffer;
            Unlock();
        }
    }
    return color;
}
// FUNCTION: GAMEMD 0x7BAF90
// Full 0x82-byte span through RET 12 at 0x7BB00F.
bool XSurface::unknown_88(const Point2D& point, unsigned int color, const XYWHStruct& bounds)
{
    if (point.X >= bounds.X && point.X < bounds.X + bounds.Width &&
        point.Y >= bounds.Y && point.Y < bounds.Y + bounds.Height) {
        void* buffer = Lock(point);
        if (buffer) {
            if (GetBytesPerPixel() == 2)
                *(unsigned short*)buffer = (unsigned short)color;
            else
                *(unsigned char*)buffer = (unsigned char)color;
            Unlock();
            return true;
        }
    }
    return false;
}
