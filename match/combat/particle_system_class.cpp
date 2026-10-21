// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Target bytes: user's retail gamemd.exe v1.001 (Ghidra disasm). Names
//   cross-checked against YRpp ParticleSystemClass.h / ParticleClass.h
//   (consult-only).
//
// reccmp annotations (ascending by retail address within this TU):
//   FUNCTION: GAMEMD 0x62E380  ParticleSystemClass::SpawnParticle(coord,coord) (__thiscall)
//   FUNCTION: GAMEMD 0x62E430  ParticleSystemClass::SpawnParticle(type,coord)  (__thiscall)
//   FUNCTION: GAMEMD 0x62B5E0  ParticleClass::ParticleClass    (declared call target; reconstruction remains capped elsewhere)

#include "particle_system_class.h"
#include "particles/particle_type_class.h"

// A static all-zero CoordStruct at GAMEMD 0x00AC4A58, passed as the second
// coordinate by the (type, coord) overload (push 0xAC4A58). Reloc-normalised.
extern CoordStruct DefaultSpawnCoords;

// FUNCTION: GAMEMD 0x62E380  (__thiscall)
// Spawn a particle of the system's own configured type between two coordinates.
ParticleClass* ParticleSystemClass::SpawnParticle(const CoordStruct& coords1,
                                                  const CoordStruct& coords2)
{
    ParticleClass* particle;

    if (this->Type->HoldsWhat == -1) {
        goto fail;
    }

    particle = new ParticleClass(
        ParticleTypeArray.Items[this->Type->HoldsWhat],
        coords1, coords2, this);

    if (particle) {
        this->Particles.AddItem(particle);
        return particle;
    }

fail:
    return 0;
}

// FUNCTION: GAMEMD 0x62E430  (__thiscall)
// Spawn a particle of an explicitly supplied type at the given coordinate.
ParticleClass* ParticleSystemClass::SpawnParticle(ParticleTypeClass* pType,
                                                  const CoordStruct& coords)
{
    ParticleClass* particle = new ParticleClass(
        pType, coords, DefaultSpawnCoords, this);

    if (particle) {
        this->Particles.AddItem(particle);
        return particle;
    }
    return 0;
}
