// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and layout read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at 0x6406F0:
//     PreviewClass::ImageSurface sits at [ECX+0x0] (`MOV ECX,[ESI]` /
//     `MOV dword ptr [ESI],0x0`), matching the same member already confirmed
//     in match/ui/preview_class_pcx_methods.h (read, not edited; re-derived
//     here so this TU stands alone). The surface is released through its own
//     vtable slot 0 with a pushed `1` (the scalar-deleting-destructor
//     "free the block too" flag), the same slot already confirmed in
//     match/ui/preview_class_surface_methods.h.
//   Name cross-checked against YRpp
//   (`~PreviewClass() JMP_THIS(0x6406F0)`; consult-only, NO LICENSE; the
//   offset reconfirmed above).
#ifndef GG_MATCH_UI_PREVIEW_CLASS_DTOR_METHODS_H
#define GG_MATCH_UI_PREVIEW_CLASS_DTOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// Declaration order matters -- see match/_rt/gg_vslot.h.
struct SurfaceVtbl_006406F0;

// The image surface: only its scalar-deleting-destructor slot is reached.
struct Surface_006406F0
{
    SurfaceVtbl_006406F0* Vtbl;   // +0x0000
};

typedef void* (Surface_006406F0::*Fn000_006406F0)(int freeFlag);
struct SurfaceVtbl_006406F0
{
    Fn000_006406F0 At_000;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(SurfaceVtbl_006406F0, At_000) == 0x0);

struct PreviewClass_006406F0
{
    Surface_006406F0* ImageSurface;   // +0x0000

    // FUNCTION: GAMEMD 0x6406F0
    void Dtor();
};
GG_STATIC_ASSERT(offsetof(PreviewClass_006406F0, ImageSurface) == 0x0);

#endif  // GG_MATCH_UI_PREVIEW_CLASS_DTOR_METHODS_H
