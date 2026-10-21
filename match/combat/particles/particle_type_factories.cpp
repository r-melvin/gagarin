// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Cluster methods use the existing 0x644890 and 0x645820 function bodies as
// source hypotheses; row identity and relocations require the current raw oracle.
// VC6FLAGS: /nologo /c /O2 /DNDEBUG /Gy

// Binary-backed string references (retail bytes including the terminating NUL):
// STRING: GAMEMD 0x817474 "<none>"
// STRING: GAMEMD 0x817694 "none"

#include <string.h>
#include "particle_system_type_class.h"
#include "particle_type_class.h"

// FUNCTION: GAMEMD 0x644890
ParticleSystemTypeClass* __fastcall ParticleSystemTypeClass::FindOrAllocate(const char* id)
{
    if (_stricmp("<none>", id) == 0)
        return 0;
    if (_stricmp("none", id) == 0)
        return 0;

    for (int i = 0; i < DAT_00A83D68.Count; i++) {
        if (_stricmp(((ParticleSystemTypeClass**)DAT_00A83D68.Items)[i]->ID, id) == 0)
            return ((ParticleSystemTypeClass**)DAT_00A83D68.Items)[i];
    }

    return new ParticleSystemTypeClass(id);
}

// FUNCTION: GAMEMD 0x645820
ParticleTypeClass* __fastcall ParticleTypeClass::FindOrAllocate(const char* id)
{
    if (_stricmp("<none>", id) == 0)
        return 0;
    if (_stricmp("none", id) == 0)
        return 0;

    for (int i = 0; i < ParticleTypeArray.Count; i++) {
        if (_stricmp(((ParticleTypeClass**)ParticleTypeArray.Items)[i]->ID, id) == 0)
            return ((ParticleTypeClass**)ParticleTypeArray.Items)[i];
    }

    return new ParticleTypeClass(id);
}
