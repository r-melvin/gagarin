// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   The two vector instances only the ParticleClass / ParticleTypeClass TUs touch, read from the retail
//   image: the global ParticleClass::Array at 0xA83DC8 (vptr 0x7E9D64, DynamicVectorClass<ParticleClass*>)
//   and the colour list of ParticleTypeClass at +0x2B8 (vptrs 0x7E4E38 / 0x7E4E58, vector of 3-byte
//   colours plus one dword). The vector templates themselves are shared (particle_common_vectors.h).
#ifndef GG_MATCH_EFFECTS_PARTICLES_PARTICLE_VECTORS_H
#define GG_MATCH_EFFECTS_PARTICLES_PARTICLE_VECTORS_H

#include <stddef.h>
#include "../../_rt/gg_static_assert.h"
#include "particle_common_types.h"
#include "particle_common_vectors.h"

typedef ParticleDynVector<ParticleClass*> ParticleClassVector;
GG_STATIC_ASSERT(sizeof(ParticleClassVector) == 0x18);

// GLOBAL: GAMEMD 0xA83DC8 - ParticleClass::Array, every live particle.
extern ParticleClassVector ParticleArray;

// The colour list of ParticleTypeClass (+0x2B8, 0x1C bytes): a dynamic vector of 3-byte colours and
// one extra dword. Its constructor runs the out-of-line vector constructor and stores the list's own
// vptr (0x7E4E58) without initialising Count / CapacityIncrement (Load, ReadINI: nothing else is
// stored); the implicit assignment is the out-of-line vector assignment followed by the three
// remaining dwords, which is what the reader's `ColorList = ...` expands to.
class ParticleColorList : public ParticleDynVector<ParticleColor>
{
public:
    ParticleColorList(int capacity, ParticleColor* mem) : ParticleDynVector<ParticleColor>(capacity, mem) {}

    ParticleColorList() {}
    int unknown_18;   // +0x18
};
GG_STATIC_ASSERT(offsetof(ParticleColorList, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(ParticleColorList, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(ParticleColorList, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(ParticleColorList, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(ParticleColorList, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(offsetof(ParticleColorList, unknown_18) == 0x18);
GG_STATIC_ASSERT(sizeof(ParticleColorList) == 0x1C);

#endif  // GG_MATCH_EFFECTS_PARTICLES_PARTICLE_VECTORS_H
