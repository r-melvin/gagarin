// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Reconstruction storage for two native zero-initialized surface pointers.
// Native constructor and exchange paths are documented in composite_surface.h;
// their original source-file owner is not established.
#include "composite_surface.h"
#include "../_rt/gg_static_assert.h"

GG_STATIC_ASSERT(sizeof(DSurface*) == 4);
// GLOBAL: GAMEMD 0x8872FC
DSurface* DAT_008872FC;
// GLOBAL: GAMEMD 0x88731C
DSurface* DAT_0088731C;
