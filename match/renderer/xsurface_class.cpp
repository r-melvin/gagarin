// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// ^ no /GX: paired probe on the XSurface scalar deleting destructor (0x4115A0): with /GX VC6 keeps a
// separate ~XSurface call (0/12), without it the destructor inlines and matches (12/12). The Blit*
// stack locals of 0x7BBB90 also carry no unwind frame in retail.
// Provenance: own-binary-via-Ghidra. XSurface (RTTI .?AVXSurface@@, vtable | YRpp-cross-check
// 0x7E2104) members that are not drawing algorithms; spans are CFG-closed.
#include "surface_class.h"

// FUNCTION: GAMEMD 0x411560
void* XSurface::Lock(Point2D origin)
{
    ++LockLevel;
    return 0;
}

// FUNCTION: GAMEMD 0x411570
bool XSurface::Unlock()
{
    --LockLevel;
    return true;
}

// FUNCTION: GAMEMD 0x411580
bool XSurface::IsLocked()
{
    return LockLevel != 0;
}

// FUNCTION: GAMEMD 0x411590
bool XSurface::unknown_84()
{
    return false;
}

// FUNCTION: GAMEMD 0x7BA5E0
bool XSurface::DrawLine(Point2D* from, Point2D* to, unsigned int color)
{
    return XSurface::DrawLineEx(&GetRect(), from, to, color);
}

// FUNCTION: GAMEMD 0x7BAB30
int XSurface::unknown_4C(Point2D*, Point2D*, unsigned short, unsigned char*, int, bool)
{
    return 0;
}

// FUNCTION: GAMEMD 0x7BAB40
bool XSurface::unknown_50(Point2D*, Point2D*, int, bool)
{
    return false;
}

// FUNCTION: GAMEMD 0x7BAB50
bool XSurface::unknown_34(RectangleStruct*, Point2D*, Point2D*, unsigned int, int, int, bool)
{
    return false;
}

// FUNCTION: GAMEMD 0x7BAB60
bool XSurface::unknown_38(RectangleStruct*, Point2D*, Point2D*, int, int, int, bool)
{
    return false;
}

// FUNCTION: GAMEMD 0x7BAB70
bool XSurface::unknown_3C(RectangleStruct*, Point2D*, Point2D*, unsigned char*, int, int, bool, bool, bool, bool, float)
{
    return false;
}

// FUNCTION: GAMEMD 0x7BAB80
bool XSurface::unknown_40(RectangleStruct*, Point2D*, Point2D*, unsigned char*, float, int, int)
{
    return false;
}

// FUNCTION: GAMEMD 0x7BAD90
bool XSurface::DrawRect(RectangleStruct* rect, unsigned int color)
{
    return XSurface::DrawRectEx(&GetRect(), rect, color);
}

// FUNCTION: GAMEMD 0x7BADC0
// Draws the four edges of `rect` (inclusive right/bottom) with DrawLineEx.
bool XSurface::DrawRectEx(RectangleStruct* clip, RectangleStruct* rect, unsigned int color)
{
    Point2D topLeft;
    Point2D topRight;
    Point2D bottomRight;
    Point2D bottomLeft;

    topLeft.X = rect->X;
    topLeft.Y = rect->Y;
    topRight.X = rect->X + rect->Width - 1;
    topRight.Y = rect->Y;
    bottomRight.X = topRight.X;
    bottomLeft.Y = rect->Y + rect->Height - 1;
    bottomRight.Y = bottomLeft.Y;
    bottomLeft.X = rect->X;

    DrawLineEx(clip, &topLeft, &topRight, color);
    DrawLineEx(clip, &topLeft, &bottomLeft, color);
    DrawLineEx(clip, &topRight, &bottomRight, color);
    DrawLineEx(clip, &bottomLeft, &bottomRight, color);
    return true;
}

// FUNCTION: GAMEMD 0x7BAE60
unsigned int XSurface::GetPixel(const Point2D* point)
{
    unsigned int color = 0;
    void* buffer = Lock(*point);

    if (buffer) {
        if (GetBytesPerPixel() == 2)
            color = *(unsigned short*)buffer;
        else
            color = *(unsigned char*)buffer;
        Unlock();
    }
    return color;
}

// FUNCTION: GAMEMD 0x7BAEB0
bool XSurface::PutPixel(const Point2D* point, unsigned int color)
{
    void* buffer = Lock(*point);

    if (buffer) {
        if (GetBytesPerPixel() == 2)
            *(unsigned short*)buffer = (unsigned short)color;
        else
            *(unsigned char*)buffer = (unsigned char)color;
        Unlock();
        return true;
    }
    return false;
}

// FUNCTION: GAMEMD 0x7BAF10
// Full 0x77-byte span through RET 8 at 0x7BAF84. Bounds are half-open XYWH.
unsigned int XSurface::GetPixelClipped(const Point2D& point, const XYWHStruct& bounds)
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
bool XSurface::PutPixelClipped(const Point2D& point, unsigned int color, const XYWHStruct& bounds)
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

// FUNCTION: GAMEMD 0x7BB020
bool XSurface::FillRect(RectangleStruct* rect, unsigned int color)
{
    return XSurface::FillRectEx(rect, &GetRect(), color);
}

// FUNCTION: GAMEMD 0x7BB340
bool XSurface::unknown_1C(RectangleStruct*, RectangleStruct*, int)
{
    return false;
}

// FUNCTION: GAMEMD 0x7BBAB0
bool XSurface::Fill(unsigned int color)
{
    return FillRectEx(&GetRect(), &GetRect(), color);
}
