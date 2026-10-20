// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra and raw retail reads. RTTI identifies
// XSurface at 0x7E2104 (COL 0x7FB2C8), primary base Surface at displacement
// 0. Its Lock/Unlock/IsLocked/unknown_84 targets and +0x0C accesses are from
// 0x411560/570/580/590. No complete XSurface size is claimed.
#ifndef GG_MATCH_RENDERER_XSURFACE_CLASS_H
#define GG_MATCH_RENDERER_XSURFACE_CLASS_H

#include <stddef.h>
#include "surface_class.h"

// VTABLE: GAMEMD 0x7E2104 XSurface (vtable[-1] at 0x7E2100 -> COL 0x7FB2C8).
// RTTI base chain is XSurface : Surface with primary-base offset zero.
class XSurface : public Surface
{
public:
    // Slot 0 is XSurface's scalar-deleting destructor at 0x4115A0; that body
    // is outside this candidate cluster and is not annotated as an ordinary dtor.
    virtual ~XSurface();

    // FUNCTION: GAMEMD 0x411560; slot +0x5C, RET 8; origin is two DWORDs.
    virtual void* Lock(Point2D origin);
    // FUNCTION: GAMEMD 0x411570; slot +0x60.
    virtual bool Unlock();
    // FUNCTION: GAMEMD 0x411580; slot +0x6C.
    virtual bool IsLocked();
    // FUNCTION: GAMEMD 0x411590; slot +0x84.
    virtual bool unknown_84();
    // FUNCTION: GAMEMD 0x7BAF90; slot +0x88, RET 12; writes a bounded pixel.
    // Original method names and source-level const qualifiers remain unknown.
    virtual bool unknown_88(const Point2D& point, unsigned int color,
                            const XYWHStruct& bounds);
    // FUNCTION: GAMEMD 0x7BAF10; slot +0x8C, RET 8; reads a bounded pixel.
    virtual unsigned int unknown_8C(const Point2D& point, const XYWHStruct& bounds);

    unsigned int unknown_0C; // +0x0C, read/written by 411560/570/580
};
GG_STATIC_ASSERT(offsetof(XSurface, unknown_0C) == 0x0C);

// XSurface inherits Surface's 34-slot prefix and appends two virtuals at
// +0x88/+0x8C. Target addresses below are direct retail reads; these assertions
// pin every slot position through the confirmed end at the next COL.
struct XSurfaceVtableLayout
{
    void* deletingDestructor; // +0x00 -> 0x4115A0
    void* inherited_04[22];   // +0x04..+0x58
    void* Lock;                // +0x5C -> 0x411560
    void* Unlock;              // +0x60 -> 0x411570
    void* unknown_64;          // +0x64 -> 0x4114F0
    void* unknown_68;          // +0x68 -> 0x411500
    void* IsLocked;            // +0x6C -> 0x411580
    void* GetBytesPerPixel;    // +0x70 -> pure-call 0x4C9150
    void* GetPitch;            // +0x74 -> pure-call 0x4C9150
    void* GetRect;             // +0x78 -> 0x411510
    void* GetWidth;            // +0x7C -> 0x411540
    void* GetHeight;           // +0x80 -> 0x411550
    void* unknown_84;          // +0x84 -> 0x411590
    void* unknown_88;          // +0x88 -> 0x7BAF90
    void* unknown_8C;          // +0x8C -> 0x7BAF10
};
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, deletingDestructor) == 0x00);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, inherited_04) + 0 * sizeof(void*) == 0x04);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, inherited_04) + 1 * sizeof(void*) == 0x08);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, inherited_04) + 2 * sizeof(void*) == 0x0C);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, inherited_04) + 3 * sizeof(void*) == 0x10);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, inherited_04) + 4 * sizeof(void*) == 0x14);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, inherited_04) + 5 * sizeof(void*) == 0x18);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, inherited_04) + 6 * sizeof(void*) == 0x1C);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, inherited_04) + 7 * sizeof(void*) == 0x20);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, inherited_04) + 8 * sizeof(void*) == 0x24);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, inherited_04) + 9 * sizeof(void*) == 0x28);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, inherited_04) + 10 * sizeof(void*) == 0x2C);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, inherited_04) + 11 * sizeof(void*) == 0x30);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, inherited_04) + 12 * sizeof(void*) == 0x34);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, inherited_04) + 13 * sizeof(void*) == 0x38);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, inherited_04) + 14 * sizeof(void*) == 0x3C);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, inherited_04) + 15 * sizeof(void*) == 0x40);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, inherited_04) + 16 * sizeof(void*) == 0x44);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, inherited_04) + 17 * sizeof(void*) == 0x48);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, inherited_04) + 18 * sizeof(void*) == 0x4C);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, inherited_04) + 19 * sizeof(void*) == 0x50);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, inherited_04) + 20 * sizeof(void*) == 0x54);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, inherited_04) + 21 * sizeof(void*) == 0x58);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, Lock) == 0x5C);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, Unlock) == 0x60);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, unknown_64) == 0x64);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, unknown_68) == 0x68);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, IsLocked) == 0x6C);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, GetBytesPerPixel) == 0x70);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, GetPitch) == 0x74);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, GetRect) == 0x78);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, GetWidth) == 0x7C);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, GetHeight) == 0x80);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, unknown_84) == 0x84);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, unknown_88) == 0x88);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, unknown_8C) == 0x8C);
GG_STATIC_ASSERT(sizeof(XSurfaceVtableLayout) == 0x90);

#endif
