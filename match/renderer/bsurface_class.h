// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Raw RTTI/vtable 0x7E2070 proves BSurface : XSurface : Surface at offset0.
// Entries 0x4115F0/0x411630/0x411640/0x411650 and helper 0x43AE50 establish
// the fields below. Lock and the two getters are native methods; lifetime
// implementation remains a separate matching view.
#ifndef GG_MATCH_RENDERER_BSURFACE_CLASS_H
#define GG_MATCH_RENDERER_BSURFACE_CLASS_H
#include "surface_class.h"
#include "../_layout/memory_buffer.h"
// VTABLE: GAMEMD 0x7E2070 -- BSurface; 36 slots, same prefix as XSurface.
class BSurface : public XSurface
{
public:
    virtual ~BSurface();
    // FUNCTION: GAMEMD 0x4115F0 (decl; reloc)
    virtual void* Lock(Point2D origin);
    // FUNCTION: GAMEMD 0x411630 (decl; reloc)
    virtual int GetBytesPerPixel();
    // FUNCTION: GAMEMD 0x411640 (decl; reloc)
    virtual unsigned int GetPitch();
    unsigned int BytesPerPixel; // +0x10
    MemoryBuffer Pixels;     // +0x14
};
GG_STATIC_ASSERT(offsetof(BSurface, BytesPerPixel) == 0x10);
GG_STATIC_ASSERT(offsetof(BSurface, Pixels) == 0x14);
GG_STATIC_ASSERT(offsetof(BSurface, Pixels) + offsetof(MemoryBuffer, Buffer) == 0x14);
GG_STATIC_ASSERT(offsetof(BSurface, Pixels) + offsetof(MemoryBuffer, Size) == 0x18);
GG_STATIC_ASSERT(offsetof(BSurface, Pixels) + offsetof(MemoryBuffer, Allocated) == 0x1C);
// Allocation at 0x4AEF42 pushes 0x20 before operator new at 0x7C8E17.
GG_STATIC_ASSERT(sizeof(BSurface) == 0x20);
#endif
