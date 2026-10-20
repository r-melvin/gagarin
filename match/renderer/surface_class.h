// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra. Surface RTTI, primary vtable, methods,
// and member offsets are from retail gamemd.exe v1.001 at 0x7E2198 and
// instructions in 0x4AEC60, 0x411510, 0x411540, 0x411550, 0x4115F0,
// 0x411570, 0x411580, and their callers. This models only the confirmed
// Surface prefix; derived classes and unconfirmed tail fields are omitted.
#ifndef GG_MATCH_RENDERER_SURFACE_CLASS_H
#define GG_MATCH_RENDERER_SURFACE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/geometry2d.h"

// VTABLE: GAMEMD 0x7E2198 Surface (vtable[-1] at 0x7E2194 -> COL 0x7FB2F8).
class Surface
{
public:
    // The empty inline destructor reproduces the body embedded in the
    // scalar-deleting destructor at 0x4115D0. No separate ordinary entry is bound.
    virtual ~Surface() {}
    // FUNCTION: GAMEMD 0x4AEC60 (decl; reloc)
    Surface(int width, int height);

    virtual void unknown_04() = 0;
    virtual void unknown_08() = 0;
    virtual void unknown_0C() = 0;
    virtual void unknown_10() = 0;
    virtual void unknown_14() = 0;
    virtual void unknown_18() = 0;
    virtual void unknown_1C() = 0;
    virtual void unknown_20() = 0;
    virtual void unknown_24() = 0;
    virtual void unknown_28() = 0;
    virtual void unknown_2C() = 0;
    virtual void unknown_30() = 0;
    virtual void unknown_34() = 0;
    virtual void unknown_38() = 0;
    virtual void unknown_3C() = 0;
    virtual void unknown_40() = 0;
    virtual void unknown_44() = 0;
    virtual void unknown_48() = 0;
    virtual void unknown_4C() = 0;
    virtual void unknown_50() = 0;
    virtual void unknown_54() = 0;
    virtual void unknown_58() = 0;
    virtual void* Lock(Point2D origin) = 0;
    virtual bool Unlock() = 0;
    // FUNCTION: GAMEMD 0x4114F0; true result, RET 8; args unresolved.
    virtual bool unknown_64(unsigned int, unsigned int);
    // FUNCTION: GAMEMD 0x411500; true result, RET 8; args unresolved.
    virtual bool unknown_68(unsigned int, unsigned int);
    virtual bool IsLocked() = 0;
    virtual int GetBytesPerPixel() = 0;
    virtual unsigned int GetPitch() = 0;
    // FUNCTION: GAMEMD 0x411510; returns hidden-result 4-int rectangle.
    virtual LTRBStruct GetRect() const;
    // FUNCTION: GAMEMD 0x411540
    virtual int GetWidth() const;
    // FUNCTION: GAMEMD 0x411550
    virtual int GetHeight() const;
    // FUNCTION: GAMEMD 0x4115C0; returns false.
    virtual bool unknown_84();

    int Width;  // +0x04, written by 0x4AEC60 and read by 0x411510/540
    int Height; // +0x08, written by 0x4AEC60 and read by 0x411510/550
};
GG_STATIC_ASSERT(offsetof(Surface, Width) == 0x04);
GG_STATIC_ASSERT(offsetof(Surface, Height) == 0x08);
// The known fields end at +0x0C; the complete Surface size is not claimed.
GG_STATIC_ASSERT(offsetof(Surface, Height) + sizeof(int) == 0x0C);

struct SurfaceVtableLayout
{
    void* deletingDestructor; // +0x00
    void* unknown_04[22];     // +0x04..+0x58
    void* Lock;               // +0x5C
    void* Unlock;             // +0x60
    void* unknown_64;         // +0x64
    void* unknown_68;         // +0x68
    void* IsLocked;           // +0x6C
    void* GetBytesPerPixel;   // +0x70
    void* GetPitch;           // +0x74
    void* GetRect;            // +0x78
    void* GetWidth;           // +0x7C
    void* GetHeight;          // +0x80
    void* unknown_84;         // +0x84
};
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, deletingDestructor) == 0x00);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_04) + 0 * sizeof(void*) == 0x04);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_04) + 1 * sizeof(void*) == 0x08);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_04) + 2 * sizeof(void*) == 0x0C);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_04) + 3 * sizeof(void*) == 0x10);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_04) + 4 * sizeof(void*) == 0x14);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_04) + 5 * sizeof(void*) == 0x18);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_04) + 6 * sizeof(void*) == 0x1C);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_04) + 7 * sizeof(void*) == 0x20);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_04) + 8 * sizeof(void*) == 0x24);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_04) + 9 * sizeof(void*) == 0x28);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_04) + 10 * sizeof(void*) == 0x2C);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_04) + 11 * sizeof(void*) == 0x30);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_04) + 12 * sizeof(void*) == 0x34);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_04) + 13 * sizeof(void*) == 0x38);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_04) + 14 * sizeof(void*) == 0x3C);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_04) + 15 * sizeof(void*) == 0x40);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_04) + 16 * sizeof(void*) == 0x44);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_04) + 17 * sizeof(void*) == 0x48);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_04) + 18 * sizeof(void*) == 0x4C);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_04) + 19 * sizeof(void*) == 0x50);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_04) + 20 * sizeof(void*) == 0x54);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_04) + 21 * sizeof(void*) == 0x58);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_64) == 0x64);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_68) == 0x68);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, Lock) == 0x5C);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, Unlock) == 0x60);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, IsLocked) == 0x6C);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, GetBytesPerPixel) == 0x70);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, GetPitch) == 0x74);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, GetRect) == 0x78);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, GetWidth) == 0x7C);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, GetHeight) == 0x80);
GG_STATIC_ASSERT(offsetof(SurfaceVtableLayout, unknown_84) == 0x84);
GG_STATIC_ASSERT(sizeof(SurfaceVtableLayout) == 0x88);

#endif
