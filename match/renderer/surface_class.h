// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra. Surface/XSurface RTTI, vtables, slot | YRpp-cross-check
// bodies and member offsets are read from retail gamemd.exe v1.001; every
// address cited below was disassembled from its entry point. Slot names
// describe the behaviour of the slot bodies; the others keep unknown_XX names.
#ifndef GG_MATCH_RENDER_SURFACES_SURFACE_H
#define GG_MATCH_RENDER_SURFACES_SURFACE_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/geometry2d.h"

class Surface;
class Blitter;

// Per-pixel callback of DrawLineCallback (slot +0x44). Retail calls it with
// ECX = pointer to the pixel's Point2D and no stack arguments (0x7BAC7B,
// 0x7BAD14: `lea ecx,[esp+N]; call ebx`), i.e. one __fastcall argument.
typedef void(__fastcall* SurfacePixelCallback)(Point2D* pixel);

// ---------------------------------------------------------------------------
// Read-only dependencies called by the Surface/XSurface bodies. They are owned
// by other modules; they are declared here only so the bodies compile with the
// retail calling sequence. Conventions are read from the callee prologues.
// ---------------------------------------------------------------------------

// FUNCTION: GAMEMD 0x421B60 (decl; reloc) (decl; reloc). Rectangle intersection. ECX = result
// (hidden), EDX = first rectangle, stack = second rectangle plus two optional
// offset-out pointers, RET 0xC. Returns the result pointer in EAX. A degenerate
// intersection yields an all-zero rectangle.
RectangleStruct* __fastcall RectIntersect(RectangleStruct* result,
                                          const RectangleStruct* a,
                                          const RectangleStruct* b, int* adjustX,
                                          int* adjustY);

// FUNCTION: GAMEMD 0x45A130 (decl; reloc) (decl; reloc). thiscall rectangle builder:
// ECX = destination, stack = (const Point2D*, width, height), RET 0xC.
struct RectBuilder : public RectangleStruct
{
    RectangleStruct* FromPointSize(const Point2D* origin, int width, int height);
};

// FUNCTION: GAMEMD 0x437F30 (decl; reloc) (decl; reloc). thiscall copy of a Point2D into the
// stack result: ECX = source, stack = destination, RET 4, returns destination.
struct PointCopier : public Point2D
{
    Point2D* CopyTo(Point2D* destination) const;
};

// FUNCTION: GAMEMD 0x7BBE20 (decl; reloc) (decl; reloc). Blit rectangle clipper. ECX = dest
// rectangle (edited), EDX = destination surface rectangle, stack = source
// rectangle (edited) and source surface rectangle, RET 8. Returns whether any
// pixels remain. Not in the surface cluster's reserved list: expansion lead.
bool __fastcall ClipBlitRects(RectangleStruct* destRect,
                              const RectangleStruct* destSurfaceRect,
                              RectangleStruct* srcRect,
                              const RectangleStruct* srcSurfaceRect);

// FUNCTION: GAMEMD 0x7BC2B0 (decl; reloc) (decl; reloc). Line clipper (Cohen-Sutherland with
// double arithmetic). ECX = first point, EDX = second point (both edited),
// stack = clip rectangle, RET 4. Returns whether any of the line survives.
// Not in the reserved list: expansion lead.
bool __fastcall ClipLine(Point2D* a, Point2D* b, const RectangleStruct* clip);

// FUNCTION: GAMEMD 0x437350 (decl; reloc) (decl; reloc). Scanline blit driver. ECX = destination
// surface, EDX = destination rectangle, stack = (source surface, source
// rectangle, Blitter*, 0, 3, 1000, 0), RET 0x1C. Returns the driver result in
// AL. Not in the reserved list: expansion lead (blitter module's neighbour).
bool __fastcall BlitDriver(Surface* dest, const RectangleStruct* destRect,
                           Surface* src, const RectangleStruct* srcRect,
                           Blitter* blitter, int a, int b, int c, int d);

// ---------------------------------------------------------------------------
// Surface -- RTTI .?AVSurface@@ (TD 0x817878, COL 0x7FB2F8), vtable 0x7E2198.
//
// Layout: vptr +0x00, Width +0x04, Height +0x08. XSurface's first member sits
// at +0x0C, so this modeled base prefix has size 0xC. A complete standalone
// Surface allocation is not established by these methods. The "sizeof 32 / ctor 0x4AEC60" allocation leads in the task data
// are BSurface allocations (the same sites store the XSurface vptr 0x7E2104
// and finally the BSurface vptr 0x7E2070); they say nothing about Surface.
//
// 34 slots (0x00..0x84). Slots 1..24, 27, 28 and 29 point at 0x4C9150, the
// program's __purecall replacement (LIBRARY, never defined here).
// ---------------------------------------------------------------------------
// VTABLE: GAMEMD 0x7E2198 Surface (vtable[-1] at 0x7E2194 -> COL 0x7FB2F8).
class Surface
{
public:
    // The scalar deleting destructor at 0x4115D0 is annotated in the source; the empty inline
    // body only stores the Surface vptr and conditionally calls operator delete.
    virtual ~Surface() {}

    // FUNCTION: GAMEMD 0x4AEC60 (decl; reloc)
    Surface(int width, int height);

    // +0x04, XSurface 0x7BBAF0
    virtual bool CopyFromWhole(Surface* src, bool a, bool b) = 0;
    // +0x08, XSurface 0x7BBB90; arg4 selects the
    // BlitTrans leaf, arg5 is unread
    virtual bool CopyFromPart(RectangleStruct* dest, Surface* src,
                              RectangleStruct* srcRect, bool a, bool b) = 0;
    // +0x0C, XSurface 0x7BBCF0;
    // arg1/arg4 are the destination/source surface bounds, arg2/arg5 the rectangles; arg7 is unread
    virtual bool CopyFrom(RectangleStruct* destClip, RectangleStruct* destRect,
                          Surface* src, RectangleStruct* srcClip,
                          RectangleStruct* srcRect, bool a, bool b) = 0;
    // +0x10, XSurface 0x7BB050
    virtual bool FillRectEx(RectangleStruct* clip, RectangleStruct* rect,
                            unsigned int color) = 0;
    // +0x14, XSurface 0x7BB020
    virtual bool FillRect(RectangleStruct* rect, unsigned int color) = 0;
    // +0x18, XSurface 0x7BBAB0
    virtual bool Fill(unsigned int color) = 0;
    // +0x1C, XSurface stub 0x7BB340 (returns false)
    virtual bool unknown_1C(RectangleStruct* clip, RectangleStruct* rect, int a) = 0;
    // +0x20, XSurface 0x7BB350
    virtual bool DrawEllipse(int cx, int cy, int rx, int ry,
                             RectangleStruct clip, unsigned int color) = 0;
    // +0x24, XSurface 0x7BAEB0
    virtual bool PutPixel(const Point2D* point, unsigned int color) = 0;
    // +0x28, XSurface 0x7BAE60
    virtual unsigned int GetPixel(const Point2D* point) = 0;
    // +0x2C, XSurface 0x7BA610
    virtual bool DrawLineEx(RectangleStruct* clip, Point2D* from, Point2D* to,
                            unsigned int color) = 0;
    // +0x30, XSurface 0x7BA5E0
    virtual bool DrawLine(Point2D* from, Point2D* to, unsigned int color) = 0;
    // +0x34..+0x40, XSurface stubs returning false (RET 0x1C, 0x1C, 0x2C, 0x1C)
    virtual bool unknown_34(RectangleStruct* clip, Point2D* from, Point2D* to, unsigned int color, int zEnd, int zStart, bool writeZ) = 0;
    virtual bool unknown_38(RectangleStruct* clip, Point2D* from, Point2D* to, int brightness, int zFrom, int zTo, bool writeZ) = 0;
    virtual bool unknown_3C(RectangleStruct* clip, Point2D* from, Point2D* to, unsigned char* rgb, int zFrom, int zTo, bool writeZ, bool blendA, bool blendB, bool blendC, float scale) = 0;
    virtual bool unknown_40(RectangleStruct* clip, Point2D* from, Point2D* to, unsigned char* color, float scale, int zFrom, int zTo) = 0;
    // +0x44, XSurface 0x7BAB90
    virtual bool DrawLineCallback(RectangleStruct* clip, Point2D* from,
                                  Point2D* to, SurfacePixelCallback callback) = 0;
    // +0x48, XSurface 0x7BA8C0: unclipped; pattern is a 16-entry byte table indexed by a
    // phase that wraps modulo 16; returns the phase after the last pixel.
    virtual unsigned int DrawDottedLine(Point2D* from, Point2D* to,
                                        unsigned int color,
                                        unsigned char* pattern,
                                        unsigned int phase) = 0;
    // +0x4C, XSurface stub 0x7BAB30 (returns 0; RET 0x18)
    virtual int unknown_4C(Point2D* from, Point2D* to, unsigned short color, unsigned char* pattern, int phase, bool invert) = 0;
    // +0x50, XSurface stub 0x7BAB40 (returns false; RET 0x10)
    virtual bool unknown_50(Point2D* from, Point2D* to, int color, bool flag) = 0;
    // +0x54, XSurface 0x7BADC0
    virtual bool DrawRectEx(RectangleStruct* clip, RectangleStruct* rect,
                            unsigned int color) = 0;
    // +0x58, XSurface 0x7BAD90
    virtual bool DrawRect(RectangleStruct* rect, unsigned int color) = 0;

    // +0x5C, XSurface 0x411560 (RET 8: Point2D by value)
    virtual void* Lock(Point2D origin) = 0;
    // +0x60, XSurface 0x411570
    virtual bool Unlock() = 0;
    // FUNCTION: GAMEMD 0x4114F0 (decl; reloc) -- returns true, RET 8, arguments unread.
    virtual bool unknown_64(unsigned int, unsigned int);
    // FUNCTION: GAMEMD 0x411500 (decl; reloc) -- returns true, RET 8, arguments unread.
    virtual bool unknown_68(unsigned int, unsigned int);
    // +0x6C, XSurface 0x411580
    virtual bool IsLocked() = 0;
    // +0x70 pure
    virtual int GetBytesPerPixel() = 0;
    // +0x74 pure
    virtual unsigned int GetPitch() = 0;
    // FUNCTION: GAMEMD 0x411510 (decl; reloc) -- hidden-result ABI, RET 4.
    virtual RectangleStruct GetRect() const;
    // FUNCTION: GAMEMD 0x411540 (decl; reloc)
    virtual int GetWidth() const;
    // FUNCTION: GAMEMD 0x411550 (decl; reloc)
    virtual int GetHeight() const;
    // FUNCTION: GAMEMD 0x4115C0 (decl; reloc) -- returns false.
    virtual bool unknown_84();

    int Width;  // +0x04
    int Height; // +0x08
};
GG_STATIC_ASSERT(offsetof(Surface, Width) == 0x04);
GG_STATIC_ASSERT(offsetof(Surface, Height) == 0x08);
GG_STATIC_ASSERT(sizeof(Surface) == 0x0C);

// ---------------------------------------------------------------------------
// XSurface -- RTTI .?AVXSurface@@ (TD 0x817890, COL 0x7FB2C8), vtable 0x7E2104,
// base chain XSurface : Surface at offset 0.
//
// XSurface adds the lock counter at +0x0C. BSurface's first own member is at
// +0x10, so this modeled XSurface prefix has size 0x10. XSurface keeps GetBytesPerPixel and
// GetPitch pure (slots 28/29 hold 0x4C9150) and is never allocated; retail
// builds it only as the intermediate step of the inlined BSurface constructor
// (store vptr 0x7E2104, LockLevel = 0, ... then the BSurface vptr).
//
// 36 slots (0x00..0x8C): Surface's 34 plus unknown slots +0x88 / +0x8C.
// ---------------------------------------------------------------------------
// VTABLE: GAMEMD 0x7E2104 XSurface (vtable[-1] at 0x7E2100 -> COL 0x7FB2C8).
class XSurface : public Surface
{
public:
    // SYNTHETIC: GAMEMD 0x4115A0 -- scalar deleting destructor of the implicit
    // (virtual) destructor; stores the Surface vptr 0x7E2198, optionally deletes.
    // An explicit empty ~XSurface() makes VC6 emit a separate call to it instead.

    // Inlined at every allocation site (retail has no out-of-line body).
    XSurface(int width, int height) : Surface(width, height), LockLevel(0) {}

    // FUNCTION: GAMEMD 0x7BBAF0 (decl; reloc)
    virtual bool CopyFromWhole(Surface* src, bool a, bool b);
    // FUNCTION: GAMEMD 0x7BBB90 (decl; reloc)
    virtual bool CopyFromPart(RectangleStruct* dest, Surface* src,
                              RectangleStruct* srcRect, bool a, bool b);
    // FUNCTION: GAMEMD 0x7BBCF0 (decl; reloc)
    virtual bool CopyFrom(RectangleStruct* destClip, RectangleStruct* destRect,
                          Surface* src, RectangleStruct* srcClip,
                          RectangleStruct* srcRect, bool a, bool b);
    // FUNCTION: GAMEMD 0x7BB050 (decl; reloc)
    virtual bool FillRectEx(RectangleStruct* clip, RectangleStruct* rect,
                            unsigned int color);
    // FUNCTION: GAMEMD 0x7BB020 (decl; reloc)
    virtual bool FillRect(RectangleStruct* rect, unsigned int color);
    // FUNCTION: GAMEMD 0x7BBAB0 (decl; reloc)
    virtual bool Fill(unsigned int color);
    // FUNCTION: GAMEMD 0x7BB340 (decl; reloc)
    virtual bool unknown_1C(RectangleStruct* clip, RectangleStruct* rect, int a);
    // FUNCTION: GAMEMD 0x7BB350 (decl; reloc)
    virtual bool DrawEllipse(int cx, int cy, int rx, int ry,
                             RectangleStruct clip, unsigned int color);
    // FUNCTION: GAMEMD 0x7BAEB0 (decl; reloc)
    virtual bool PutPixel(const Point2D* point, unsigned int color);
    // FUNCTION: GAMEMD 0x7BAE60 (decl; reloc)
    virtual unsigned int GetPixel(const Point2D* point);
    // FUNCTION: GAMEMD 0x7BA610 (decl; reloc)
    virtual bool DrawLineEx(RectangleStruct* clip, Point2D* from, Point2D* to,
                            unsigned int color);
    // FUNCTION: GAMEMD 0x7BA5E0 (decl; reloc)
    virtual bool DrawLine(Point2D* from, Point2D* to, unsigned int color);
    // FUNCTION: GAMEMD 0x7BAB50 (decl; reloc) / 0x7BAB60 / 0x7BAB70 / 0x7BAB80
    virtual bool unknown_34(RectangleStruct* clip, Point2D* from, Point2D* to, unsigned int color, int zEnd, int zStart, bool writeZ);
    virtual bool unknown_38(RectangleStruct* clip, Point2D* from, Point2D* to, int brightness, int zFrom, int zTo, bool writeZ);
    virtual bool unknown_3C(RectangleStruct* clip, Point2D* from, Point2D* to, unsigned char* rgb, int zFrom, int zTo, bool writeZ, bool blendA, bool blendB, bool blendC, float scale);
    virtual bool unknown_40(RectangleStruct* clip, Point2D* from, Point2D* to, unsigned char* color, float scale, int zFrom, int zTo);
    // FUNCTION: GAMEMD 0x7BAB90 (decl; reloc)
    virtual bool DrawLineCallback(RectangleStruct* clip, Point2D* from,
                                  Point2D* to, SurfacePixelCallback callback);
    // FUNCTION: GAMEMD 0x7BA8C0 (decl; reloc)
    virtual unsigned int DrawDottedLine(Point2D* from, Point2D* to,
                                        unsigned int color,
                                        unsigned char* pattern,
                                        unsigned int phase);
    // FUNCTION: GAMEMD 0x7BAB30 (decl; reloc)
    virtual int unknown_4C(Point2D* from, Point2D* to, unsigned short color, unsigned char* pattern, int phase, bool invert);
    // FUNCTION: GAMEMD 0x7BAB40 (decl; reloc)
    virtual bool unknown_50(Point2D* from, Point2D* to, int color, bool flag);
    // FUNCTION: GAMEMD 0x7BADC0 (decl; reloc)
    virtual bool DrawRectEx(RectangleStruct* clip, RectangleStruct* rect,
                            unsigned int color);
    // FUNCTION: GAMEMD 0x7BAD90 (decl; reloc)
    virtual bool DrawRect(RectangleStruct* rect, unsigned int color);

    // FUNCTION: GAMEMD 0x411560 (decl; reloc)
    virtual void* Lock(Point2D origin);
    // FUNCTION: GAMEMD 0x411570 (decl; reloc)
    virtual bool Unlock();
    // FUNCTION: GAMEMD 0x411580 (decl; reloc)
    virtual bool IsLocked();
    // FUNCTION: GAMEMD 0x411590 (decl; reloc) -- returns false.
    virtual bool unknown_84();
    // FUNCTION: GAMEMD 0x7BAF90 (decl; reloc) -- bounded pixel write; bounds are half-open XYWH.
    virtual bool PutPixelClipped(const Point2D& point, unsigned int color,
                                 const XYWHStruct& bounds);
    // FUNCTION: GAMEMD 0x7BAF10 (decl; reloc) -- bounded pixel read.
    virtual unsigned int GetPixelClipped(const Point2D& point,
                                         const XYWHStruct& bounds);

    // FUNCTION: GAMEMD 0x7BB920 -- midpoint circle as four mirrored spans.
    void FUN_007BB920(int cx, int cy, int radius, RectangleStruct clip,
                      unsigned int color);

    int LockLevel; // +0x0C: ++ by Lock, -- by Unlock, IsLocked is (!= 0)
};
GG_STATIC_ASSERT(offsetof(XSurface, LockLevel) == 0x0C);
GG_STATIC_ASSERT(sizeof(XSurface) == 0x10);

// Vtable images (slot-by-slot offset asserts). Surface has 34 slots, XSurface 36; targets are in README.md.
struct SurfaceVtableLayout
{
    void* deletingDestructor; // +0x00
    void* CopyFromWhole; // +0x04
    void* CopyFromPart; // +0x08
    void* CopyFrom; // +0x0C
    void* FillRectEx; // +0x10
    void* FillRect; // +0x14
    void* Fill; // +0x18
    void* unknown_1C; // +0x1C
    void* DrawEllipse; // +0x20
    void* PutPixel; // +0x24
    void* GetPixel; // +0x28
    void* DrawLineEx; // +0x2C
    void* DrawLine; // +0x30
    void* unknown_34; // +0x34
    void* unknown_38; // +0x38
    void* unknown_3C; // +0x3C
    void* unknown_40; // +0x40
    void* DrawLineCallback; // +0x44
    void* DrawDottedLine; // +0x48
    void* unknown_4C; // +0x4C
    void* unknown_50; // +0x50
    void* DrawRectEx; // +0x54
    void* DrawRect; // +0x58
    void* Lock; // +0x5C
    void* Unlock; // +0x60
    void* unknown_64; // +0x64
    void* unknown_68; // +0x68
    void* IsLocked; // +0x6C
    void* GetBytesPerPixel; // +0x70
    void* GetPitch; // +0x74
    void* GetRect; // +0x78
    void* GetWidth; // +0x7C
    void* GetHeight; // +0x80
    void* unknown_84; // +0x84
};
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, deletingDestructor) == 0x00);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, CopyFromWhole) == 0x04);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, CopyFromPart) == 0x08);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, CopyFrom) == 0x0C);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, FillRectEx) == 0x10);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, FillRect) == 0x14);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, Fill) == 0x18);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, DrawEllipse) == 0x20);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, PutPixel) == 0x24);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, GetPixel) == 0x28);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, DrawLineEx) == 0x2C);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, DrawLine) == 0x30);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, DrawLineCallback) == 0x44);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, DrawDottedLine) == 0x48);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_50) == 0x50);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, DrawRectEx) == 0x54);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, DrawRect) == 0x58);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, Lock) == 0x5C);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, Unlock) == 0x60);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_64) == 0x64);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_68) == 0x68);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, IsLocked) == 0x6C);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, GetBytesPerPixel) == 0x70);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, GetPitch) == 0x74);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, GetRect) == 0x78);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, GetWidth) == 0x7C);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, GetHeight) == 0x80);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_84) == 0x84);
GG_STATIC_ASSERT(sizeof(SurfaceVtableLayout) == 0x88);
struct XSurfaceVtableLayout
{
    void* deletingDestructor; // +0x00
    void* CopyFromWhole; // +0x04
    void* CopyFromPart; // +0x08
    void* CopyFrom; // +0x0C
    void* FillRectEx; // +0x10
    void* FillRect; // +0x14
    void* Fill; // +0x18
    void* unknown_1C; // +0x1C
    void* DrawEllipse; // +0x20
    void* PutPixel; // +0x24
    void* GetPixel; // +0x28
    void* DrawLineEx; // +0x2C
    void* DrawLine; // +0x30
    void* unknown_34; // +0x34
    void* unknown_38; // +0x38
    void* unknown_3C; // +0x3C
    void* unknown_40; // +0x40
    void* DrawLineCallback; // +0x44
    void* DrawDottedLine; // +0x48
    void* unknown_4C; // +0x4C
    void* unknown_50; // +0x50
    void* DrawRectEx; // +0x54
    void* DrawRect; // +0x58
    void* Lock; // +0x5C
    void* Unlock; // +0x60
    void* unknown_64; // +0x64
    void* unknown_68; // +0x68
    void* IsLocked; // +0x6C
    void* GetBytesPerPixel; // +0x70
    void* GetPitch; // +0x74
    void* GetRect; // +0x78
    void* GetWidth; // +0x7C
    void* GetHeight; // +0x80
    void* unknown_84; // +0x84
    void* PutPixelClipped; // +0x88
    void* GetPixelClipped; // +0x8C
};
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, deletingDestructor) == 0x00);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, CopyFromWhole) == 0x04);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, CopyFromPart) == 0x08);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, CopyFrom) == 0x0C);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, FillRectEx) == 0x10);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, FillRect) == 0x14);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, Fill) == 0x18);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, unknown_1C) == 0x1C);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, DrawEllipse) == 0x20);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, PutPixel) == 0x24);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, GetPixel) == 0x28);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, DrawLineEx) == 0x2C);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, DrawLine) == 0x30);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, unknown_34) == 0x34);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, unknown_38) == 0x38);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, unknown_3C) == 0x3C);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, unknown_40) == 0x40);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, DrawLineCallback) == 0x44);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, DrawDottedLine) == 0x48);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, unknown_4C) == 0x4C);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, unknown_50) == 0x50);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, DrawRectEx) == 0x54);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, DrawRect) == 0x58);
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
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, PutPixelClipped) == 0x88);
GG_STATIC_ASSERT(offsetof(XSurfaceVtableLayout, GetPixelClipped) == 0x8C);
GG_STATIC_ASSERT(sizeof(XSurfaceVtableLayout) == 0x90);

#endif
