// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes, globals and sizes read off the user's retail gamemd.exe v1.001 via
//   the local Ghidra CLI at the four addresses below. They are four
//   instantiations of one template — same instruction sequence throughout,
//   differing only in the array globals, the allocation size and the
//   constructor. That was established by diffing the constant sets rather than
//   assumed from the names.
//
//   class                    entry      Items      Count      sizeof  ctor
//   AnimTypeClass            0x428B80   0x8B4154   0x8B4160   0x378   0x427530
//   ParticleSystemTypeClass  0x644890   0xA83D6C   0xA83D78   0x310   0x6440A0
//   TerrainTypeClass         0x71E2A0   0xA8E31C   0xA8E328   0x2BC   0x71DA80
//   WarheadTypeClass         0x75E3B0   0x8874C4   0x8874D0   0x1D0   0x75CEC0
//
//   Items and Count are 0xC apart in every case, so each vector object sits at
//   Items - 4. The ID compared against is AbstractTypeClass::ID @0x24, matching
//   the committed spine. Both reject literals are shared: "<none>" (0x817474)
//   and "none" (0x817694).
#ifndef GG_MATCH_CORE_TYPE_CLASS_FINDORALLOC_METHODS_H
#define GG_MATCH_CORE_TYPE_CLASS_FINDORALLOC_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_layout/vector_class.h"

// The constructors are declared `throw()`. Retail's allocate path has no SEH
// frame at all, and `new T(id)` with a potentially-throwing constructor makes
// VC6 emit one (`PUSH -1; PUSH 0; MOV EAX,FS:[0]`) so operator delete can run
// on unwind — that prologue alone costs the whole match. Same precedent as
// WaypointPathClass in match/economy/house_class_misc_methods.h.

// CRT case-insensitive compare at 0x007C8D20 (__cdecl).
extern "C" int __cdecl _stricmp(const char* a, const char* b);

// ---------------------------------------------------------------------------
// AnimTypeClass — GAMEMD 0x428B80, sizeof 0x378, ctor GAMEMD 0x427530
// ---------------------------------------------------------------------------
struct AnimTypeClass
{
    char _pad00[0x24];              // +0x0000  AbstractClass prefix
    char ID[0x378 - 0x24];         // +0x0024  AbstractTypeClass::ID onwards

    AnimTypeClass(const char* id) throw();   // GAMEMD 0x427530 (declared; reloc)

    static AnimTypeClass* __fastcall FindOrAllocate(const char* id);   // GAMEMD 0x428B80
};
GG_STATIC_ASSERT(offsetof(AnimTypeClass, ID) == 0x24);
GG_STATIC_ASSERT(sizeof(AnimTypeClass) == 0x378);

// GLOBAL: GAMEMD 0x8B4150 — AnimTypeClass::Array.
extern DynamicVectorClassLayout AnimTypeClassArray;

// ---------------------------------------------------------------------------
// ParticleSystemTypeClass — GAMEMD 0x644890, sizeof 0x310, ctor GAMEMD 0x6440A0
// ---------------------------------------------------------------------------
struct ParticleSystemTypeClass
{
    char _pad00[0x24];              // +0x0000  AbstractClass prefix
    char ID[0x310 - 0x24];         // +0x0024  AbstractTypeClass::ID onwards

    ParticleSystemTypeClass(const char* id) throw();   // GAMEMD 0x6440A0 (declared; reloc)

    static ParticleSystemTypeClass* __fastcall FindOrAllocate(const char* id);   // GAMEMD 0x644890
};
GG_STATIC_ASSERT(offsetof(ParticleSystemTypeClass, ID) == 0x24);
GG_STATIC_ASSERT(sizeof(ParticleSystemTypeClass) == 0x310);

// GLOBAL: GAMEMD 0xA83D68 — ParticleSystemTypeClass::Array.
extern DynamicVectorClassLayout ParticleSystemTypeClassArray;

// ---------------------------------------------------------------------------
// TerrainTypeClass — GAMEMD 0x71E2A0, sizeof 0x2BC, ctor GAMEMD 0x71DA80
// ---------------------------------------------------------------------------
struct TerrainTypeClass
{
    char _pad00[0x24];              // +0x0000  AbstractClass prefix
    char ID[0x2BC - 0x24];         // +0x0024  AbstractTypeClass::ID onwards

    TerrainTypeClass(const char* id) throw();   // GAMEMD 0x71DA80 (declared; reloc)

    static TerrainTypeClass* __fastcall FindOrAllocate(const char* id);   // GAMEMD 0x71E2A0
};
GG_STATIC_ASSERT(offsetof(TerrainTypeClass, ID) == 0x24);
GG_STATIC_ASSERT(sizeof(TerrainTypeClass) == 0x2BC);

// GLOBAL: GAMEMD 0xA8E318 — TerrainTypeClass::Array.
extern DynamicVectorClassLayout TerrainTypeClassArray;

// ---------------------------------------------------------------------------
// WarheadTypeClass — GAMEMD 0x75E3B0, sizeof 0x1D0, ctor GAMEMD 0x75CEC0
// ---------------------------------------------------------------------------
struct WarheadTypeClass
{
    char _pad00[0x24];              // +0x0000  AbstractClass prefix
    char ID[0x1D0 - 0x24];         // +0x0024  AbstractTypeClass::ID onwards

    WarheadTypeClass(const char* id) throw();   // GAMEMD 0x75CEC0 (declared; reloc)

    static WarheadTypeClass* __fastcall FindOrAllocate(const char* id);   // GAMEMD 0x75E3B0
};
GG_STATIC_ASSERT(offsetof(WarheadTypeClass, ID) == 0x24);
GG_STATIC_ASSERT(sizeof(WarheadTypeClass) == 0x1D0);

// GLOBAL: GAMEMD 0x8874C0 — WarheadTypeClass::Array.
extern DynamicVectorClassLayout WarheadTypeClassArray;

#endif  // GG_MATCH_CORE_TYPE_CLASS_FINDORALLOC_METHODS_H
