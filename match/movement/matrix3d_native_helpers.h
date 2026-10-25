// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Native 0x7559B0 copies twelve dwords from a 0x30-stride table indexed
// by the full EDX argument into the hidden result in ECX and returns it.
#ifndef GG_MATCH_MOVEMENT_MATRIX3D_NATIVE_HELPERS_H
#define GG_MATCH_MOVEMENT_MATRIX3D_NATIVE_HELPERS_H
#include "../_layout/matrix3d.h"
// GLOBAL: GAMEMD 0xB45188
extern "C" Matrix3D DAT_00B45188[];
// Native function 0x7559B0; annotated definition in core/unowned_leaf_sweep_c.cpp.
Matrix3D FUN_007559B0(int index);
#endif
