// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check (names only, consult-only)
//   Small views used only by ParticleClass / ParticleTypeClass, read from the retail gamemd.exe v1.001
//   (constructors 0x62B5E0 / 0x62BB20, draw slot 0x62CEC0). Everything the whole particle module
//   shares (coordinates, colours, the ObjectClass / ObjectTypeClass base views, the secondary
//   interface bases, the CRC / INI / swizzle / map views) lives in particle_common_*.h.
#ifndef GG_MATCH_EFFECTS_PARTICLES_PARTICLE_VIEWS_H
#define GG_MATCH_EFFECTS_PARTICLES_PARTICLE_VIEWS_H

#include "particle_common_types.h"
#include "particle_common_vectors.h"
#include "particle_common_views.h"

// Three floats (a direction or a position in floating point).
struct ParticleVec3
{
    float X;   // +0x00
    float Y;   // +0x04
    float Z;   // +0x08

    ParticleVec3() {}
    ParticleVec3(float x, float y, float z) : X(x), Y(y), Z(z) {}

    // Scales the vector to unit length (left unchanged when its length is zero).
    void Normalize();
};
GG_STATIC_ASSERT(sizeof(ParticleVec3) == 0xC);

// FUNCTION: GAMEMD 0x661020 (decl; reloc) (read-only here) - blends two colours: result = a * (1 - t) + b * t. The
// result is written through `this` (a scratch colour) and `this` is returned.
struct ParticleColorMixer
{
    ParticleColor* Mix(const ParticleColor* a, const ParticleColor* b, float t);
    ParticleColor  Scratch;
};

#endif  // GG_MATCH_EFFECTS_PARTICLES_PARTICLE_VIEWS_H
