// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra. DSurface (RTTI .?AVDSurface@@, vtable | YRpp-cross-check | behaviour-confirmed-name
// 0x7E85D4) layout, DirectDraw COM calls and global addresses read from retail
// gamemd.exe v1.001. Method entry spans and data references are recorded in
// the project evidence; data addresses are not function entry points.
// Slot names that are not evidenced by behaviour keep unknown_XX.
// Ordinary methods only. Constructors and lifetime bodies remain deferred.
#ifndef GG_MATCH_RENDERER_DSURFACE_CLASS_H
#define GG_MATCH_RENDERER_DSURFACE_CLASS_H

#include "surface_class.h"
#include "pixel_shift_view.h"

// ---------------------------------------------------------------------------
// DirectDraw (COM, __stdcall through the interface vtable with `this` pushed).
// Only the members that DSurface's call sites touch are typed; everything else
// is padding. IDirectDrawSurface slot offsets are read from the call sites:
// +0x08 Release, +0x14 Blt, +0x34 GetBltStatus, +0x58 GetSurfaceDesc, +0x60
// IsLost, +0x64 Lock, +0x6C Restore, +0x70 SetClipper, +0x80 Unlock. DSurface
// constructors are outside this method-only package.
// ---------------------------------------------------------------------------
#define DDERR_SURFACELOST_VALUE 0x887601C2

struct DDSurfaceDesc // 0x6C bytes: DDSURFACEDESC
{
    unsigned long dwSize;          // +0x00 (0x6C)
    unsigned long dwFlags;         // +0x04 (7: caps | height | width on creation)
    unsigned long dwHeight;        // +0x08
    unsigned long dwWidth;         // +0x0C
    long lPitch;                   // +0x10
    unsigned long unknown_14[4];   // +0x14
    void* lpSurface;               // +0x24
    unsigned long unknown_28[11];  // +0x28
    unsigned long dwRGBBitCount;   // +0x54 (pixel format)
    unsigned long unknown_58[4];   // +0x58
    unsigned long dwCaps;          // +0x68
};
GG_STATIC_ASSERT(offsetof(DDSurfaceDesc, dwSize) == 0);
GG_STATIC_ASSERT(offsetof(DDSurfaceDesc, dwFlags) == 0x04);
GG_STATIC_ASSERT(offsetof(DDSurfaceDesc, dwHeight) == 0x08);
GG_STATIC_ASSERT(offsetof(DDSurfaceDesc, dwWidth) == 0x0C);
GG_STATIC_ASSERT(offsetof(DDSurfaceDesc, lPitch) == 0x10);
GG_STATIC_ASSERT(offsetof(DDSurfaceDesc, lpSurface) == 0x24);
GG_STATIC_ASSERT(offsetof(DDSurfaceDesc, dwRGBBitCount) == 0x54);
GG_STATIC_ASSERT(offsetof(DDSurfaceDesc, dwCaps) == 0x68);
GG_STATIC_ASSERT(sizeof(DDSurfaceDesc) == 0x6C);

struct DDRect { long left; long top; long right; long bottom; };
GG_STATIC_ASSERT(offsetof(DDRect, left) == 0);
GG_STATIC_ASSERT(offsetof(DDRect, top) == 4);
GG_STATIC_ASSERT(offsetof(DDRect, right) == 8);
GG_STATIC_ASSERT(offsetof(DDRect, bottom) == 0xC);
GG_STATIC_ASSERT(sizeof(DDRect) == 0x10);

struct DDBltFx // 0x64 bytes: DDBLTFX, only dwSize and the fill colour are touched
{
    unsigned long dwSize;          // +0x00 (0x64)
    unsigned long unknown_04[19];  // +0x04
    unsigned long dwFillColor;     // +0x50
    unsigned long unknown_54[4];   // +0x54
};
GG_STATIC_ASSERT(offsetof(DDBltFx, dwSize) == 0);
GG_STATIC_ASSERT(offsetof(DDBltFx, dwFillColor) == 0x50);
GG_STATIC_ASSERT(sizeof(DDBltFx) == 0x64);

struct DDSurface;
struct DDClipper;

typedef long(__stdcall* DDSurfaceIsLostFn)(DDSurface*);

struct DDSurfaceVtbl
{
    void* unknown_00[2];                                                                  // +0x00 QueryInterface, AddRef
    unsigned long(__stdcall* Release)(DDSurface*);                                        // +0x08
    void* unknown_0C[2];                                                                  // +0x0C
    long(__stdcall* Blt)(DDSurface*, DDRect*, DDSurface*, DDRect*, unsigned long, DDBltFx*); // +0x14
    void* unknown_18[7];                                                                  // +0x18
    long(__stdcall* GetBltStatus)(DDSurface*, unsigned long);                             // +0x34
    void* unknown_38[8];                                                                  // +0x38
    long(__stdcall* GetSurfaceDesc)(DDSurface*, DDSurfaceDesc*);                          // +0x58
    void* unknown_5C;                                                                     // +0x5C
    long(__stdcall* IsLost)(DDSurface*);                                                  // +0x60
    long(__stdcall* Lock)(DDSurface*, DDRect*, DDSurfaceDesc*, unsigned long, void*);     // +0x64
    void* unknown_68;                                                                     // +0x68
    long(__stdcall* Restore)(DDSurface*);                                                 // +0x6C
    long(__stdcall* SetClipper)(DDSurface*, DDClipper*);                                  // +0x70
    void* unknown_74[3];                                                                  // +0x74
    long(__stdcall* Unlock)(DDSurface*, void*);                                           // +0x80
};
GG_STATIC_ASSERT(offsetof(DDSurfaceVtbl, Release) == 0x08);
GG_STATIC_ASSERT(offsetof(DDSurfaceVtbl, Blt) == 0x14);
GG_STATIC_ASSERT(offsetof(DDSurfaceVtbl, GetBltStatus) == 0x34);
GG_STATIC_ASSERT(offsetof(DDSurfaceVtbl, GetSurfaceDesc) == 0x58);
GG_STATIC_ASSERT(offsetof(DDSurfaceVtbl, IsLost) == 0x60);
GG_STATIC_ASSERT(offsetof(DDSurfaceVtbl, Lock) == 0x64);
GG_STATIC_ASSERT(offsetof(DDSurfaceVtbl, Restore) == 0x6C);
GG_STATIC_ASSERT(offsetof(DDSurfaceVtbl, SetClipper) == 0x70);
GG_STATIC_ASSERT(offsetof(DDSurfaceVtbl, Unlock) == 0x80);
GG_STATIC_ASSERT(sizeof(DDSurfaceVtbl) == 0x84);
struct DDSurface { const DDSurfaceVtbl* lpVtbl; };
GG_STATIC_ASSERT(offsetof(DDSurface, lpVtbl) == 0);
GG_STATIC_ASSERT(sizeof(DDSurface) == 4);

struct DDClipperVtbl
{
    void* unknown_00[2];
    unsigned long(__stdcall* Release)(DDClipper*); // +0x08
};
GG_STATIC_ASSERT(offsetof(DDClipperVtbl, Release) == 0x08);
struct DDClipper { const DDClipperVtbl* lpVtbl; };

// Byte-width storage views; original source types/names are not established.
// GLOBAL: GAMEMD 0x89F978
extern "C" unsigned char DAT_0089F978;
// GLOBAL: GAMEMD 0xA8ED80
extern "C" unsigned char DAT_00A8ED80;
// GLOBAL: GAMEMD 0x8205D4
extern "C" unsigned char DAT_008205D4;
// GLOBAL: GAMEMD 0x8A0DF1 -- byte guard; original type/name unknown.
extern "C" unsigned char DAT_008A0DF1;
// GLOBAL: GAMEMD 0x8A0980 -- 257 observed dwords; original element type unknown.
extern "C" unsigned int DAT_008A0980[257];

// The old logical name was an indexed array of contiguous {left,right} pairs.
// In the canonical address view, physical pair order is pos0, pos2, pos1.
inline int DSurfacePixelShift(unsigned int channel, unsigned int side)
{
    const unsigned char* base = reinterpret_cast<const unsigned char*>(&gg_b_translucent_pixel_format);
    return *reinterpret_cast<const int*>(base + channel * 8 + side * 4);
}

// ---------------------------------------------------------------------------
// DSurface -- RTTI .?AVDSurface@@, vtable 0x7E85D4 (38 slots), DSurface : XSurface.
// sizeof 0x24 (allocation size immediate 0x24 at 0x4BA8DD and 0x5340EA).
// ---------------------------------------------------------------------------
// Retail address point 0x7E85D4; table contents are outside this method-only package.
class DSurface : public XSurface
{
public:
    // Declared for the class interface; constructor body not part of this package.
    DSurface(int width, int height, bool systemMemory, bool offscreen3D);
    DSurface(DDSurface* surface);
    // Declared for the class interface; deleting wrapper/body not part of this package.
    virtual ~DSurface();

    virtual bool CopyFromWhole(Surface* src, bool a, bool b);
    virtual bool CopyFromPart(RectangleStruct* dest, Surface* src, RectangleStruct* srcRect, bool a, bool b);
    virtual bool CopyFrom(RectangleStruct* destClip, RectangleStruct* destRect, Surface* src,
                          RectangleStruct* srcClip, RectangleStruct* srcRect, bool a, bool b);
    virtual bool FillRectEx(RectangleStruct* clip, RectangleStruct* rect, unsigned int color);
    virtual bool FillRect(RectangleStruct* rect, unsigned int color);
    virtual bool unknown_1C(RectangleStruct* rect, RectangleStruct* colorBytes, int percent);
    virtual bool unknown_34(RectangleStruct* clip, Point2D* from, Point2D* to, unsigned int color, int zEnd, int zStart, bool writeZ);
    virtual bool unknown_38(RectangleStruct* clip, Point2D* from, Point2D* to, int brightness, int zFrom, int zTo, bool writeZ);
    virtual bool unknown_3C(RectangleStruct* clip, Point2D* from, Point2D* to, unsigned char* rgb, int zFrom, int zTo, bool writeZ, bool blendA, bool blendB, bool blendC, float scale);
    virtual bool unknown_40(RectangleStruct* clip, Point2D* from, Point2D* to, unsigned char* color, float scale, int zFrom, int zTo);
    virtual int unknown_4C(Point2D* from, Point2D* to, unsigned short color, unsigned char* pattern, int phase, bool invert);
    virtual bool unknown_50(Point2D* from, Point2D* to, int color, bool flag);
    virtual void* Lock(Point2D origin);
    virtual bool Unlock();
    virtual bool unknown_64(unsigned int, unsigned int);
    virtual int GetBytesPerPixel();
    virtual unsigned int GetPitch();
    virtual bool unknown_84();
    // DSurface-only slots.
    virtual bool DrawLineGradient(RectangleStruct* clip, Point2D* from, Point2D* to, const unsigned char* colorA,
                                  const unsigned char* colorB, float* step, float* blend);
    virtual bool unknown_94();

    int BytesPerPixel;       // +0x10
    void* Buffer;            // +0x14 locked pixel pointer (DDSURFACEDESC.lpSurface)
    bool IsPrimary;          // +0x18
    bool InVideoMemory;      // +0x19 DDSCAPS_VIDEOMEMORY of the surface desc
    unsigned char unknown_1A[2]; // +0x1A
    DDSurface* DDSurf;       // +0x1C
    DDSurfaceDesc* Desc;     // +0x20

private:
    // Inline source helper used by candidate methods; false denotes failed recovery.
    bool Recover();
};
GG_STATIC_ASSERT(offsetof(DSurface, BytesPerPixel) == 0x10);
GG_STATIC_ASSERT(offsetof(DSurface, Buffer) == 0x14);
GG_STATIC_ASSERT(offsetof(DSurface, IsPrimary) == 0x18);
GG_STATIC_ASSERT(offsetof(DSurface, InVideoMemory) == 0x19);
GG_STATIC_ASSERT(offsetof(DSurface, unknown_1A) == 0x1A);
GG_STATIC_ASSERT(sizeof(((DSurface*)0)->unknown_1A) == 2);
GG_STATIC_ASSERT(offsetof(DSurface, DDSurf) == 0x1C);
GG_STATIC_ASSERT(offsetof(DSurface, Desc) == 0x20);
GG_STATIC_ASSERT(sizeof(DSurface) == 0x24);

// Modeled inherited vtable prefix plus the two DSurface-only slots. This is an
// ABI layout view; this candidate does not claim emitted-vtable verification.
struct DSurfaceVtableLayout
{
    XSurfaceVtableLayout base;
    void* DrawLineGradient; // +0x90
    void* unknown_94;       // +0x94
};
GG_STATIC_ASSERT(offsetof(DSurfaceVtableLayout, base) == 0);
GG_STATIC_ASSERT(offsetof(DSurfaceVtableLayout, DrawLineGradient) == 0x90);
GG_STATIC_ASSERT(offsetof(DSurfaceVtableLayout, unknown_94) == 0x94);
GG_STATIC_ASSERT(sizeof(DSurfaceVtableLayout) == 0x98);

// Address-local source reconstruction used by these methods. The observed callers
// handle false differently: Lock and CopyFrom return failure; Unlock continues.
inline bool DSurface::Recover()
{
    if (DDSurf && DDSurf->lpVtbl->IsLost(DDSurf) == (long)DDERR_SURFACELOST_VALUE) {
        if (DDSurf->lpVtbl->Restore(DDSurf))
            return false;
        if (DDSurf->lpVtbl->IsLost(DDSurf))
            return false;
        int saved = LockLevel;
        if (saved > 0) {
            int none = 0;
            Point2D zero;
            LockLevel = none;
            zero.X = none;
            zero.Y = none;
            Lock(zero);
            ++LockLevel;
            Unlock();
            LockLevel = saved;
        }
    }
    return true;
}

#endif // GG_MATCH_RENDERER_DSURFACE_CLASS_H
