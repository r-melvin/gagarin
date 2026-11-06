// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   IonBlastClass methods recovered from gamemd.exe v1.001 (see the TUs that
//   define them); the object layout is not modelled, only the method surface.
#ifndef GG_MATCH_LAYOUT_ION_BLAST_CLASS_H
#define GG_MATCH_LAYOUT_ION_BLAST_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../vector_class.h"
#include "coord_struct.h"

class IonBlastClass
{
public:
    // FUNCTION: GAMEMD 0x53CB10 -- stores the location, clears the two trailing words and
    // appends itself to IonBlastArray (RET 0xC: the location is passed by value).
    IonBlastClass(CoordStruct where);

    CoordStruct Location;  // +0x00 (0x53CB10 stores x, y, z)
    int unknown_0C;        // +0x0C cleared by the constructor
    int unknown_10;        // +0x10 cleared by the constructor

    // FUNCTION: GAMEMD 0x53D580 (decl; reloc)
    void Draw();
    // GAMEMD 0x53CBE0 (declared; reloc)
    void Update();                 // __thiscall

    // FUNCTION: GAMEMD 0x53D850
    static void DrawAll();
    // GAMEMD 0x53D310
    static void UpdateAll();
};

GG_STATIC_ASSERT(offsetof(IonBlastClass, Location) == 0x00);
GG_STATIC_ASSERT(offsetof(IonBlastClass, unknown_0C) == 0x0C);
GG_STATIC_ASSERT(offsetof(IonBlastClass, unknown_10) == 0x10);
GG_STATIC_ASSERT(sizeof(IonBlastClass) == 0x14);

// GLOBAL: GAMEMD 0xAA0118 -- IonBlastClass::Array. Items at 0xAA011C (+0x04),
// Count at 0xAA0128 (+0x10).
extern DynamicVectorClass<IonBlastClass*> IonBlastArray;

#endif  // GG_MATCH_LAYOUT_ION_BLAST_CLASS_H
