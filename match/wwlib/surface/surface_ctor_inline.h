// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Inline body of Surface::Surface(int, int) (0x4AEC60) for the units whose retail code expands the BSurface
// construction in place (0x6C99D0, 0x4A699A, 0x52FEC0): the width and height stores; the Surface vptr store is dead
// behind the XSurface and BSurface stores. Retail's out-of-line copy is 0x4AEC60.
#ifndef GG_MATCH_WWLIB_SURFACE_SURFACE_CTOR_INLINE_H
#define GG_MATCH_WWLIB_SURFACE_SURFACE_CTOR_INLINE_H
#include "surface_class.h"
inline Surface::Surface(int width, int height) : Width(width), Height(height) {}
#endif
