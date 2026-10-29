// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | RE-findings-cross-check | behaviour-confirmed-name
//   Bytes and offsets from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (0x544CB0, 0x5471B0, 0x5471F0).
//
//   RECEIVER PROVED BY RTTI, not taken from a document. 0x00544CB0 has exactly
//   one DATA reference, 0x007ECCE4, and it is the slot the other two bodies
//   dispatch (`CALL [EAX+0x9C]`), so the vtable base is 0x007ECC48:
//     ghidra memory read 0x007ECC44 4   -> complete object locator 0x00804BC0
//     ghidra memory read 0x00804BCC 4   -> type descriptor 0x008290C8
//     ghidra memory read 0x008290C8 64  -> ".?AVIsometricTileTypeClass@@"
//   The retail class name is IsometricTileTypeClass.
//
//   Member offsets confirmed numerically from the bodies:
//     +0x0A4  unknown_A4   `MOV EAX,[ESI+0xa4]`, twice in 0x544CB0
//     +0x2F4  the byte gating the lazy load, `MOV CL,[ESI+0x2f4]`
//   Tile-image header, reached through slot +0x9C:
//     +0x00 / +0x04  the two dimensions, multiplied to give the sub-tile count
//     +0x10          the sub-tile pointer array (`[ECX + EDX*4 + 0x10]`)
//   Sub-tile image:
//     +0x24  flag word, bit 2 is the connect/ramp flag (`SHR EAX,2; AND EAX,1`)
//     +0x2A  the morph/slope byte, read with MOVSX, so signed char
//
//   The morph byte, the connect flag and the modulo are read from the bodies;
//   see the .cpp for the fall-back value.
#ifndef GG_MATCH_MAP_ISO_TILE_TYPE_CLASS_TILE_DATA_METHODS_H
#define GG_MATCH_MAP_ISO_TILE_TYPE_CLASS_TILE_DATA_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/iso_tile_type_class.h"

#endif // GG_MATCH_MAP_ISO_TILE_TYPE_CLASS_TILE_DATA_METHODS_H
