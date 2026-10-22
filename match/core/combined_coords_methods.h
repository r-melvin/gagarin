// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x422BE0. `RET 0x4` with the result written through
//   `[ESP+0x24]` is the hidden-buffer convention for a 12-byte return, and the
//   0x18 of locals is two of those structs.
#ifndef GG_MATCH_CORE_COMBINED_COORDS_METHODS_H
#define GG_MATCH_CORE_COMBINED_COORDS_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct Coord_00422BE0
{
    int X;    // +0x0000
    int Y;    // +0x0004
    int Z;    // +0x0008
};
GG_STATIC_ASSERT(sizeof(Coord_00422BE0) == 0xC);

// Declaration order per match/_rt/gg_vslot.h.
struct AttachVtbl_00422BE0;
struct Attach_00422BE0 { AttachVtbl_00422BE0* Vptr; };
typedef Coord_00422BE0* (Attach_00422BE0::*Fn48_00422BE0)(Coord_00422BE0* out);
struct AttachVtbl_00422BE0
{
    char _pad000[0x48];        // +0x0000
    Fn48_00422BE0 At_48;       // +0x0048
};
GG_STATIC_ASSERT(offsetof(AttachVtbl_00422BE0, At_48) == 0x48);

// CLASS IDENTITY (whole-image RTTI sweep; renamed from
// the raw `Obj_`/`Sub_`/`Subject_` placeholder). AnimClass's own vtable is 0x7E3354.
//   0x422BE0 -> AnimClass slot 18 (byte-off 0x48).
// That table is the only table in the image that holds it, so the slot is
// declared on AnimClass and not inherited from TechnoClass/ObjectClass above it.
// The METHOD name is still unknown; only the class is proven, so the
// `FUN_<addr>` member name stays as the transitional placeholder.
struct AnimClass_00422BE0
{
    char _pad000[0xCC];        // +0x0000
    Attach_00422BE0* Attach;   // +0x00CC

    // FUNCTION: GAMEMD 0x5F65A0 — this object's own coordinate, written into the
    // caller's buffer and returned by pointer.
    Coord_00422BE0* FUN_005F65A0(Coord_00422BE0* out);

    // FUNCTION: GAMEMD 0x422BE0
    Coord_00422BE0 FUN_00422BE0();
};
GG_STATIC_ASSERT(offsetof(AnimClass_00422BE0, Attach) == 0xCC);

#endif  // GG_MATCH_CORE_COMBINED_COORDS_METHODS_H
