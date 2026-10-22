// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra; names are descriptive, entry bindings are retail addresses. | YRpp-cross-check
#ifndef GG_MATCH_MOVEMENT_ROCKET_LOCOMOTION_MATH_H
#define GG_MATCH_MOVEMENT_ROCKET_LOCOMOTION_MATH_H
#include "loco_interfaces.h"
struct RocketMatrix : LocoMatrix3D {
    RocketMatrix() {}
    void RotateY(float angle);
};
GG_STATIC_ASSERT(sizeof(RocketMatrix)==0x30);
extern "C" double __cdecl LocoSqrt(double value);
extern "C" double __cdecl LocoSin(double angle);
extern "C" double __cdecl LocoCos(double angle);
extern "C" double __cdecl LocoAtan2(double y,double x);
#endif
