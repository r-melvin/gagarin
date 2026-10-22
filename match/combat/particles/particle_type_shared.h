// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | retail PE globals and call targets
//   Type-only dependencies for ParticleTypeClass. This header intentionally
//   excludes the renderer, map, viewport, and tactical views in particle_shared.h.
#ifndef GG_MATCH_EFFECTS_PARTICLES_PARTICLE_TYPE_SHARED_H
#define GG_MATCH_EFFECTS_PARTICLES_PARTICLE_TYPE_SHARED_H

#include "particle_common_types.h"
#include "particle_common_vectors.h"
#include "particle_common_views.h"
#include "../../core/abstract_registry.h"

// GLOBAL: GAMEMD 0xA83D98 - ParticleTypeClass::Array.
extern ParticleDynVector<ParticleTypeClass*> ParticleTypeArray;

// GLOBAL: GAMEMD 0xB0F670 - the shared AbstractType registry storage. The
// source-level view is ParticleTypeObjectView*, while storage is owned by
// core/abstract_registry.h; this macro introduces no second global object.
#define ParticleAbstractTypeArray (*((ParticleDynVector<ParticleTypeObjectView*>*)(void*)&DAT_00B0F670))

// STRING: GAMEMD 0x889F64 - shared empty INI default text.
extern const char ParticleEmptyText[];

// FUNCTION: GAMEMD 0x524EC0 (decl; reloc) - identity call view for name pointers.
const char* ParticleNameOf(const char* name);

class ParticleWarheadView;
// FUNCTION: GAMEMD 0x75E3B0 (decl; reloc) - lookup by the supplied name.
ParticleWarheadView* ParticleFindWarhead(const char* name);

#endif
