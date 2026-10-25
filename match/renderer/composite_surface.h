// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native 0x533FD0 constructs both surfaces through 0x4BA5A0 (size 0x24).
// The temporary installed by 0x53B560 is constructed the same way in
// 0x53B460. Tactical 0x6D3D10 exchanges these two pointers. Constructor
// 0x4BA5A0 installs the DSurface table 0x7E85D4 and returns its receiver;
// native RTTI gives zero-offset XSurface and Surface primary bases.
#ifndef GG_MATCH_RENDERER_COMPOSITE_SURFACE_H
#define GG_MATCH_RENDERER_COMPOSITE_SURFACE_H

class DSurface;
// GLOBAL: GAMEMD 0x88731C
extern DSurface* DAT_0088731C;
// GLOBAL: GAMEMD 0x8872FC
extern DSurface* DAT_008872FC;

#endif
