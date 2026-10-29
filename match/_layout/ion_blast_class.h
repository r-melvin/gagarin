// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   IonBlastClass methods recovered from gamemd.exe v1.001 (see the TUs that
//   define them); the object layout is not modelled, only the method surface.
#ifndef GG_MATCH_LAYOUT_ION_BLAST_CLASS_H
#define GG_MATCH_LAYOUT_ION_BLAST_CLASS_H

#include "vector_class.h"

struct IonBlastClass
{
    // FUNCTION: GAMEMD 0x53D580 (decl; reloc)
    void Draw();
    // GAMEMD 0x53CBE0 (declared; reloc)
    void Update();                 // __thiscall

    // FUNCTION: GAMEMD 0x53D850
    static void DrawAll();
    // GAMEMD 0x53D310
    static void UpdateAll();
};

// GLOBAL: GAMEMD 0xAA0118 -- IonBlastClass::Array. Items at 0xAA011C (+0x04),
// Count at 0xAA0128 (+0x10).
extern DynamicVectorClassLayout IonBlastArray;

#endif  // GG_MATCH_LAYOUT_ION_BLAST_CLASS_H
