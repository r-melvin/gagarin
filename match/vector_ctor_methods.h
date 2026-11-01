// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Entry points and vtable addresses extracted individually from the user's
//   retail gamemd.exe v1.001 via the local Ghidra CLI. Three remaining instances
//   share the VectorBase layout pinned in vector_resize_methods.h. None is
//   bound by YRpp.
//
// VectorClass construction. Take a size and an optional caller-supplied buffer:
// adopt the buffer when one is given, allocate when it is not, and do neither
// when the size is zero. The ownership flag is set only on the allocating path,
// which is what later lets Resize know whether it may free the buffer.
//
// The remaining bindings retain an object-returning layout view. The recovered
// ParticleSystemType pointer constructor at 0x45AD80 now uses the native
// VectorClass template in vector_particlesystemtype_methods.cpp.
#ifndef GG_MATCH_CORE_VECTOR_CTOR_METHODS_H
#define GG_MATCH_CORE_VECTOR_CTOR_METHODS_H

#include "vector_resize_methods.h"

extern char VT_007E180C[];   // VTABLE: GAMEMD 0x7E180C
extern char VT_007E37EC[];   // VTABLE: GAMEMD 0x7E37EC
extern char VT_007E4BC4[];   // VTABLE: GAMEMD 0x7E4BC4

struct VectorCtor : VectorBase
{
    // FUNCTION: GAMEMD 0x40BD00
    VectorCtor* FUN_0040BD00(int size, void** array);
    // FUNCTION: GAMEMD 0x42DC50
    VectorCtor* FUN_0042DC50(int size, void** array);
    // FUNCTION: GAMEMD 0x473140
    VectorCtor* FUN_00473140(int size, void** array);
};

#endif  // GG_MATCH_CORE_VECTOR_CTOR_METHODS_H
