// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x49F420.

#include "map_class_random_coords_methods.h"

// MapClass::GetRandomCoordsNear (0x49F420) has no body here: written without
// the address-taken alias on the direction the plain version scored 8.7%
// (the earlier 77.2% depended on that alias to order the 16-bit store and the
// bit-field insert). The declaration lives in the header.
