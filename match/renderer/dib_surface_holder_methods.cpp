// Provenance: own-binary-via-Ghidra
// SPDX-License-Identifier: GPL-3.0-or-later
// Owner of a GDI DIB section and the software surface wrapped around its bits.
// The constructor that ends at 0x4A69EB allocates the BITMAPINFO-shaped header
// stored at +0x04 (biSize 0x28 written at [+4]+0), creates the section into
// +0x08 with its bits pointer returned through +0x0C, records width/height at
// +0x10/+0x14 and the dword-aligned pitch at +0x1C, then stores a newly
// allocated surface at +0x20; on any failure it sets the byte at +0x00.
// 0x4A69F0 is the matching teardown: free the header, DeleteObject the section
// (import slot 0x7E10AC), then delete the surface through its slot-0
// deleting destructor.
#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// IMPORT: GAMEMD 0x7E10AC -- gdi32 DeleteObject.
extern "C" __declspec(dllimport) int __stdcall DeleteObject(void* object);
// LIBRARY: GAMEMD 0x7C8B3D -- operator delete.

// Slot zero of the owned surface is its scalar deleting destructor.
struct DibOwnedSurface
{
    virtual ~DibOwnedSurface();
};

class DibSurfaceHolder
{
public:
    // FUNCTION: GAMEMD 0x4A69F0
    ~DibSurfaceHolder();

    bool             Failed;        // +0x00 set when construction fails
    unsigned char    unknown_01[3]; // +0x01
    void*            Header;        // +0x04 BITMAPINFO-shaped header
    void*            Bitmap;        // +0x08 DIB section handle
    void*            Bits;          // +0x0C section pixels
    int              Width;         // +0x10
    int              Height;        // +0x14
    int              unknown_18;    // +0x18
    int              Pitch;         // +0x1C
    DibOwnedSurface* Surface;       // +0x20
};
GG_STATIC_ASSERT(offsetof(DibSurfaceHolder, Failed) == 0x00);
GG_STATIC_ASSERT(offsetof(DibSurfaceHolder, Header) == 0x04);
GG_STATIC_ASSERT(offsetof(DibSurfaceHolder, Bitmap) == 0x08);
GG_STATIC_ASSERT(offsetof(DibSurfaceHolder, Bits) == 0x0C);
GG_STATIC_ASSERT(offsetof(DibSurfaceHolder, Width) == 0x10);
GG_STATIC_ASSERT(offsetof(DibSurfaceHolder, Height) == 0x14);
GG_STATIC_ASSERT(offsetof(DibSurfaceHolder, Pitch) == 0x1C);
GG_STATIC_ASSERT(offsetof(DibSurfaceHolder, Surface) == 0x20);

// FUNCTION: GAMEMD 0x4A69F0
DibSurfaceHolder::~DibSurfaceHolder()
{
    if (Header != 0) {
        operator delete(Header);
    }
    if (Bitmap != 0) {
        DeleteObject(Bitmap);
    }
    if (Surface != 0) {
        delete Surface;
    }
}
