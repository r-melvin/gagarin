// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Retail globals and out-of-partition functions the particle module reads, bound by address.
//   Module header: nothing here is defined by the module.
#ifndef GG_MATCH_EFFECTS_PARTICLES_PARTICLE_SHARED_H
#define GG_MATCH_EFFECTS_PARTICLES_PARTICLE_SHARED_H

#include "particle_common_types.h"
#include "particle_common_vectors.h"
#include "particle_common_views.h"
#include "particle_views.h"
#include "particle_vectors.h"
#include "particle_type_shared.h"

// GLOBAL: GAMEMD 0xAC49D8 - the all-zero coordinate the constructors copy (decl; reloc) (read-only here).
extern ParticleCoord ParticleEmptyCoord;

// GLOBAL: GAMEMD 0xB0F670 - the registry of every type object (a dynamic vector of the type objects'
// base pointers; read-only here).
// ParticleAbstractTypeArray reuses the canonical typed view over DAT_00B0F670.
// GLOBAL: GAMEMD 0xA83D98 - ParticleTypeClass::Array, every particle type.
// ParticleTypeArray is declared by particle_type_shared.h.

// The scenario's random number generator (0xA8B230 -> scenario object, generator embedded at +0x218).
class ParticleRandomView
{
public:
    // FUNCTION: GAMEMD 0x65C780 (decl; reloc) (read-only here) - the next raw value.
    int Random();
    // FUNCTION: GAMEMD 0x65C7E0 (decl; reloc) (read-only here) - a value in [min, max].
    int Random(int min, int max);
};
struct ParticleScenarioView
{
    unsigned int       Flags;                // +0x000  bit 0x1000 is tested by the draw slot
    char               unknown_004[0x214];   // +0x004
    ParticleRandomView Random;               // +0x218
};
GG_STATIC_ASSERT(offsetof(ParticleScenarioView, Random) == 0x218);
// GLOBAL: GAMEMD 0xA8B230 - pointer to the scenario object (decl; reloc) (read-only here).
extern ParticleScenarioView* ParticleScenario;

// FUNCTION: GAMEMD 0x4CAC40 (decl; reloc) (read-only here) - square root, __cdecl, the operand pushed as a double.
double __cdecl ParticleSqrt(double value);

inline void ParticleVec3::Normalize()
{
    double length = ParticleSqrt(X * X + Y * Y + Z * Z);
    ParticleVec3 unit;
    if (length != 0.0)
        unit = ParticleVec3((float)(X / length), (float)(Y / length), (float)(Z / length));
    else
        unit = *this;
    *this = unit;
}

// GLOBAL: GAMEMD 0x889F64 - the shared empty string the readers use as their text default.
// ParticleEmptyText is declared by particle_type_shared.h.

// FUNCTION: GAMEMD 0x524EC0 (decl; reloc) (read-only here) - `MOV EAX,ECX; RET`: the identity on a name pointer.
const char* __fastcall ParticleNameOf(const char* name);

class ParticleWarheadView;
// FUNCTION: GAMEMD 0x75E3B0 (decl; reloc) (read-only here) - finds (or creates) the warhead of that name.
// __fastcall: the name in ECX.
ParticleWarheadView* __fastcall ParticleFindWarhead(const char* name);

// A screen position (x, y).
struct ParticleScreenPoint
{
    int X;   // +0x00
    int Y;   // +0x04
};
GG_STATIC_ASSERT(sizeof(ParticleScreenPoint) == 8);

// FUNCTION: GAMEMD 0x55AF60 (decl; reloc) (read-only here) - the frame limit the draw slot compares against.
unsigned int ParticleFrameLimit();
// GLOBAL: GAMEMD 0xABCD44 - the current frame counter.
extern unsigned int ParticleFrameCounter;
// GLOBAL: GAMEMD 0xA8EB78 - the detail / game-mode setting (0, 1 or 2).
extern int ParticleDetailMode;
// GLOBAL: GAMEMD 0xA8ED6B (flag) and 0xB73550 (value) - both gate the shroud test.
extern bool ParticleSkipShroudTest;
extern int ParticleShroudEnabled;
// FUNCTION: GAMEMD 0x6D20E0 (decl; reloc) (read-only here) - a height scaled by a float constant, __fastcall (ECX).
int __fastcall ParticleHeightScale(int value);

// The light map object (global pointer 0x87E8A4; read-only here).
struct ParticleLightMapView
{
    int unknown_00;   // +0x00
    int OriginY;      // +0x04
    // FUNCTION: GAMEMD 0x4114B0 (decl; reloc) (read-only here) - the light level at a cell position.
    unsigned short* GetLevel(int x, int y);
};
// GLOBAL: GAMEMD 0x87E8A4
extern ParticleLightMapView* ParticleLightMap;

// The viewport object (global pointer 0x887644; read-only here).
struct ParticleViewportView
{
    int            unknown_00;   // +0x00
    int            OriginY;      // +0x04
    char           unknown_08[0x1C];   // +0x08
    short          Height;       // +0x24
    // FUNCTION: GAMEMD 0x7BD130 (decl; reloc) (read-only here) - the height limit at a position.
    unsigned short* GetLimit(int x, int y);
};
// GLOBAL: GAMEMD 0x887644
extern ParticleViewportView* ParticleViewport;
// GLOBAL: GAMEMD 0x886FA4 - vertical offset added to projected positions.
extern int ParticleScreenYOffset;

// The drawing surface (global pointer 0x887314; read-only here). Slot 9 plots one pixel.
class ParticleSurfaceView
{
public:
    virtual void vf_0();  virtual void vf_1();  virtual void vf_2();  virtual void vf_3();
    virtual void vf_4();  virtual void vf_5();  virtual void vf_6();  virtual void vf_7();
    virtual void vf_8();
    virtual void PlotPixel(ParticleScreenPoint* where, unsigned int color);   // 9  (+0x24)
};
// GLOBAL: GAMEMD 0x887314
extern ParticleSurfaceView* ParticleSurface;
// GLOBAL: GAMEMD 0x87F6C0 - pointer handed to the shape drawer (decl; reloc) (read-only here).
extern void* ParticleDrawContext;
// FUNCTION: GAMEMD 0x4AED70 (decl; reloc) (read-only here) - draws a shape; __fastcall (surface, context), 14 stack
// dwords.
void __fastcall ParticleDrawShape(ParticleSurfaceView* surface, void* context, void* object, int frame,
                                  void* where, ParticleRect* clip, int flags, int a6, int zAdjust,
                                  int a8, int a9, int a10, int a11, int a12, int a13, int a14);
// GLOBAL: GAMEMD 0x8A0DD0..0x8A0DE4 - the pixel format's colour shifts (red right/left, blue, green).
extern int ParticleRedRight, ParticleRedLeft, ParticleBlueRight, ParticleBlueLeft, ParticleGreenRight, ParticleGreenLeft;



// GLOBAL: GAMEMD 0x887324 - pointer to the tactical (view) object (decl; reloc) (read-only here).
class ParticleTacticalView
{
public:
    // FUNCTION: GAMEMD 0x6D2140 (decl; reloc) (read-only here) - lepton coordinate to client position; false when
    // the position is off the visible area.
    bool CoordsToClient(const ParticleCoord* coord, ParticleScreenPoint* out);
};
extern ParticleTacticalView* ParticleTactical;

// FUNCTION: GAMEMD 0x75F230 (decl; reloc) (read-only here) - the 8-way facing (0..7) of the line from one screen
// point to another. __fastcall: the two points in ECX and EDX.
int __fastcall ParticleFacingBetween(ParticleScreenPoint* from, ParticleScreenPoint* to);

#endif  // GG_MATCH_EFFECTS_PARTICLES_PARTICLE_SHARED_H
