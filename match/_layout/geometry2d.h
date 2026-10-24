// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// XYWH bounds fields are read at 0x7BAF10/0x7BAF90 (XSurface pixel access).
// Point fields/stack width: retail BitFont::Lock 0x4348F0 and ToolTipManager
// accesses at 0x724AD0. Rectangle result layout: Surface::GetRect 0x411510.
#ifndef GG_MATCH_LAYOUT_GEOMETRY2D_H
#define GG_MATCH_LAYOUT_GEOMETRY2D_H
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Point2D has an empty user-declared constructor: retail
// VectorClass<Point2D>::SetCapacity 0x5D0850 (0xD0 bytes) and
// DynamicVectorClass<Point2D>::SetCapacity 0x5D09C0 (0xE0 bytes) run a
// constructor loop over the new array, which a plain aggregate does not emit.
// It also makes VC6 return Point2D through a hidden result pointer, as the
// 0x53D8E0 helper does (LEA ECX,[ESP+0xC] before the call, [EAX] after).
struct Point2D
{
    int X;  // +0x00
    int Y;  // +0x04

    Point2D() {}
    Point2D(int x, int y) : X(x), Y(y) {}

    // Member-wise equality, X then Y: the element compare that
    // VectorClass<Point2D>::operator== (0x5D07F0) and FindItemIndex (0x5D0950)
    // inline, two CMP/JNZ pairs on +0 then +4.
    bool operator==(const Point2D& o) const { return X == o.X && Y == o.Y; }
    bool operator!=(const Point2D& o) const { return !(*this == o); }

    // CALLEE: GAMEMD 0x00487F20
    Point2D operator-(Point2D const& other) const;
    // CALLEE: GAMEMD 0x004C1B50
    int Length() const;
};
GG_STATIC_ASSERT(offsetof(Point2D, X) == 0x00);
GG_STATIC_ASSERT(offsetof(Point2D, Y) == 0x04);
GG_STATIC_ASSERT(sizeof(Point2D) == 0x08);

// Coordinates plus dimensions, as distinct from left/top/right/bottom bounds.
// RectangleStruct is the existing reconstruction's name; binary evidence
// establishes the layout, not the original source type spelling.
#ifndef GG_MATCH_LAYOUT_RECTANGLESTRUCT_DEFINED
#define GG_MATCH_LAYOUT_RECTANGLESTRUCT_DEFINED
struct RectangleStruct {
    int X; int Y; int Width; int Height;
    // Declaration: GAMEMD 0x45A130 -- ECX result, point/width/height stacked.
    RectangleStruct* FromPointSize(const Point2D* point, int width, int height);
};
#endif
typedef RectangleStruct XYWHStruct;
GG_STATIC_ASSERT(offsetof(XYWHStruct, X) == 0x00);
GG_STATIC_ASSERT(offsetof(XYWHStruct, Y) == 0x04);
GG_STATIC_ASSERT(offsetof(XYWHStruct, Width) == 0x08);
GG_STATIC_ASSERT(offsetof(XYWHStruct, Height) == 0x0C);
GG_STATIC_ASSERT(sizeof(XYWHStruct) == 0x10);

struct LTRBStruct { int Left; int Top; int Right; int Bottom; };
GG_STATIC_ASSERT(offsetof(LTRBStruct, Left) == 0x00);
GG_STATIC_ASSERT(offsetof(LTRBStruct, Top) == 0x04);
GG_STATIC_ASSERT(offsetof(LTRBStruct, Right) == 0x08);
GG_STATIC_ASSERT(offsetof(LTRBStruct, Bottom) == 0x0C);
GG_STATIC_ASSERT(sizeof(LTRBStruct) == 0x10);
// TRect: the rectangle template RTTI names as a class (`.?AV?$TRect@H@@`,
// VectorClass<TRect<int>> vtable 0x7ED970). Same four-int layout as
// RectangleStruct. The empty constructor and member-wise compare are what the
// VectorClass<TRect<int>> bodies (SetCapacity 0x5ACD30, FindItemIndex
// 0x5ACE50) expand.
template<class T> class TRect
{
public:
    T X;       // +0x00
    T Y;       // +0x04
    T Width;   // +0x08
    T Height;  // +0x0C

    TRect() {}
    bool operator==(const TRect<T>& o) const
    {
        return X == o.X && Y == o.Y && Width == o.Width && Height == o.Height;
    }
    bool operator!=(const TRect<T>& o) const { return !(*this == o); }
};
GG_STATIC_ASSERT(sizeof(TRect<int>) == 0x10);


#endif
