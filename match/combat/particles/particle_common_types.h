// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check (names only)
//   Small value types shared by every class of the particle module (ParticleClass,
//   ParticleTypeClass, ParticleSystemClass, ParticleSystemTypeClass). Each is declared once, here,
//   with the union of the members the module's bodies use. Layouts were read from the retail
//   gamemd.exe v1.001 (constructors 0x62B5E0 / 0x62BB20 / 0x62DC50 / 0x62DF20 and the INI readers).
#ifndef GG_MATCH_EFFECTS_PARTICLES_PARTICLE_COMMON_TYPES_H
#define GG_MATCH_EFFECTS_PARTICLES_PARTICLE_COMMON_TYPES_H

#include <stddef.h>
#include <new.h>
#include <objidl.h>   // IStream, CLSID, HRESULT (VC98 SDK, LIBRARY)
#include "../../_rt/gg_static_assert.h"

class ParticleClass;
class ParticleTypeClass;
class ParticleSystemClass;
class ParticleSystemTypeClass;

// Three-dword world coordinate (a lepton triple).
struct ParticleCoord
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08

    ParticleCoord() {}
    ParticleCoord(int x, int y, int z) : X(x), Y(y), Z(z) {}
};
GG_STATIC_ASSERT(sizeof(ParticleCoord) == 0xC);

inline ParticleCoord operator-(ParticleCoord a, ParticleCoord b)
{
    return ParticleCoord(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
}

// A 24-bit colour (three bytes, no padding; copied as a word plus a byte). The empty default
// constructor keeps the no-init constructors from touching members.
struct ParticleColor
{
    unsigned char R;   // +0x00
    unsigned char G;   // +0x01
    unsigned char B;   // +0x02

    ParticleColor() {}
    ParticleColor(unsigned char r, unsigned char g, unsigned char b) : R(r), G(g), B(b) {}
};
GG_STATIC_ASSERT(sizeof(ParticleColor) == 3);

// Marker for the no-initialisation constructors (Load's placement new re-runs the vptr stores).
struct ParticleNoInit {};

// Clip rectangle handed to the draw slot (x, y, width, height).
struct ParticleRect
{
    int X;        // +0x00
    int Y;        // +0x04
    int Width;    // +0x08
    int Height;   // +0x0C
};
GG_STATIC_ASSERT(sizeof(ParticleRect) == 0x10);

// Two 16-bit halves (a cell coordinate). The user-declared destructor is what makes VC6 register an
// atexit stub (retail 0x62D760, a bare RET) for the function-local static in ParticleClass::vf_66.
struct ParticleCellCoord
{
    short X;   // +0x00
    short Y;   // +0x02

    ParticleCellCoord(short x, short y) : X(x), Y(y) {}
    ~ParticleCellCoord() {}
};
GG_STATIC_ASSERT(sizeof(ParticleCellCoord) == 4);

#endif  // GG_MATCH_EFFECTS_PARTICLES_PARTICLE_COMMON_TYPES_H
