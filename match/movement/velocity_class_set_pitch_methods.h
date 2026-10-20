// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: the user's retail gamemd.exe v1.001 through the local Ghidra
//   CLI at 0x5B2A30. The body seats no vtable and carries no runtime type
//   information, so the class was typed from its own instruction stream and
//   from the five Dir16 primitives that sit immediately below it in the same
//   address run (match/movement/dir16_operator_methods.*).
//
// VelocityClass -- the engine's three-double velocity/direction vector. Every
// member offset below is read straight off this body and its neighbours:
//
//   * `FLD double ptr [ESI]`      -> X at +0x00
//   * `FLD double ptr [ESI + 8]`  -> Y at +0x08
//   * `FLD double ptr [ESI + 0x10]` and the dword pair
//     `[ESI+0x10] / [ESI+0x14]` pushed as one atan2 argument -> Z at +0x10
//
// so the object is three doubles, 0x18 bytes wide. The leaf helpers at
// 0x41C350 / 0x41C430 (2D length), 0x41C3C0 (3D length) and 0x41C2E0 (pitch
// as a Dir16) address the same three slots, which is the independent
// confirmation.
//
// Angle convention. A Dir16 is a binary angle with 0x0000 at north; the
// binary carries four doubles that move between radians and that angle:
//
//   0x007E2800  0.0
//   0x007E2810 -2*pi/65536        (Dir16 -> radians, after the 0x3FFF bias)
//   0x007E2818 -65536/(2*pi)      (radians -> Dir16)
//   0x007E2820  pi/2              (the north-is-zero quarter turn)
//
// The 0x3FFF bias (not 0x4000) is retail's own; it is reproduced literally.
#ifndef GG_MATCH_MOVEMENT_VELOCITY_CLASS_SET_PITCH_METHODS_H
#define GG_MATCH_MOVEMENT_VELOCITY_CLASS_SET_PITCH_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "dir16_operator_methods.h"

// GLOBAL: GAMEMD 0x007E2800
extern const double GG_ZERO;
// GLOBAL: GAMEMD 0x007E2810
extern const double GG_DIR16_TO_RADIANS;
// GLOBAL: GAMEMD 0x007E2818
extern const double GG_RADIANS_TO_DIR16;
// GLOBAL: GAMEMD 0x007E2820
extern const double GG_QUARTER_TURN;

struct VelocityClass
{
    double X;  // +0x00
    double Y;  // +0x08
    double Z;  // +0x10

    // FUNCTION: GAMEMD 0x005B2A30
    void SetPitch(Dir16 const& pitch);
};

GG_STATIC_ASSERT(offsetof(VelocityClass, X) == 0x00 &&
                 offsetof(VelocityClass, Y) == 0x08 &&
                 offsetof(VelocityClass, Z) == 0x10 &&
                 sizeof(VelocityClass) == 0x18);

#endif  // GG_MATCH_MOVEMENT_VELOCITY_CLASS_SET_PITCH_METHODS_H
