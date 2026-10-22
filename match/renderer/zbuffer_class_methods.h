// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes and offsets read off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x7BCAE0. Class identity cross-checked against YRpp,
//   which binds 0x7BCAE0 to ZBuffer::ReleaseSurface (consult-only,
//   no LICENSE).
//
// ZBuffer — the engine's depth buffer. Only the owned drawing surface at +0x14
// is modelled here.
#ifndef GG_MATCH_RENDERER_ZBUFFER_CLASS_METHODS_H
#define GG_MATCH_RENDERER_ZBUFFER_CLASS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "surface_class.h"

struct ZBuffer
{
    char     _pad00[0x14];   // +0x0000
    Surface* Buffer;         // +0x0014  (MOV ECX,[ECX+0x14] @0x7BCAE0)

    void ReleaseSurface();   // GAMEMD 0x7BCAE0
};
GG_STATIC_ASSERT(offsetof(ZBuffer, Buffer) == 0x14);

#endif  // GG_MATCH_RENDERER_ZBUFFER_CLASS_METHODS_H
