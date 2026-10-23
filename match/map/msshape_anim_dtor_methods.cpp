// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Two more out-of-line copies of the shape animation's destructor, sitting in
// neighbouring translation units far from the animation family's own run
// (0x5CD320..0x5CEDC6). Each seats the shape animation's vtable, releases the
// decoded buffer when it is owned, and seats the base animation's vtable; the
// first seat survives because the release call between them can observe it.
// The class and its inlined destructor come from the family header.

#include "msanim_family_methods.h"

// FUNCTION: GAMEMD 0x5CB750
void MSShapeAnim_DestroyAtA(MSShapeAnim* self)
{
    self->MSShapeAnim::~MSShapeAnim();
}

// FUNCTION: GAMEMD 0x5CC2F0
void MSShapeAnim_DestroyAtB(MSShapeAnim* self)
{
    self->MSShapeAnim::~MSShapeAnim();
}
