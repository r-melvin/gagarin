// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x62E380 / 0x62E430), cross-checked
//   against YRpp ParticleSystemClass.h / ParticleSystemTypeClass.h / ParticleClass.h
//   / ArrayClasses.h (consult-only; every offset reconfirmed numerically here).
//
// ParticleSystemClass::SpawnParticle — allocates a ParticleClass (operator new,
// 0x138 bytes), constructs it (ctor @0x62B5E0), then appends it to the system's
// Particles vector (DynamicVectorClass::AddItem, inlined by the original).
#ifndef GG_MATCH_COMBAT_PARTICLE_SYSTEM_CLASS_H
#define GG_MATCH_COMBAT_PARTICLE_SYSTEM_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "particles/particle_system_type_class.h"

class ParticleTypeClass;       // array element; only ever used as a pointer here

// CoordStruct == Vector3D<int> (YRpp). 0xC bytes. Passed by const-ref (address).
struct CoordStruct
{
    int X;
    int Y;
    int Z;
};

// ParticleClass — only its size (0x138, the operator-new argument) and its
// constructor @0x62B5E0 matter here. Full decomposition is out of scope.
class ParticleClass
{
public:
    // GAMEMD 0x62B5E0 __thiscall — declared (no body) so cl emits a call (reloc).
    // `throw()`: the original `new` emits no exception-unwind cleanup around the
    // ctor (retail has no SEH frame), i.e. the compiler treated it as nothrow.
    ParticleClass(ParticleTypeClass* type,
                  const CoordStruct& coord1,
                  const CoordStruct& coord2,
                  class ParticleSystemClass* system) throw();
    char _storage[0x138];
};
GG_STATIC_ASSERT(sizeof(ParticleClass) == 0x138);

// DynamicVectorClass<ParticleClass*> as it appears at ParticleSystemClass+0xBC.
// The virtuals are declared only to pin the vtable slot order so the inlined
// AddItem reaches SetCapacity through [vtable+0x8] (slot 2), exactly as retail.
struct ParticleSpawnVector
{
    // slot 0 / 1 / 2 — declarations only (never instantiated in this TU).
    virtual ~ParticleSpawnVector();
    virtual bool operator==(const ParticleSpawnVector& other) const;
    virtual bool SetCapacity(int capacity, ParticleClass** pMem);

    // VectorClass<T> data (vptr occupies +0x00):
    ParticleClass** Items;          // +0x04
    int             Capacity;       // +0x08
    bool            IsInitialized;  // +0x0C
    bool            IsAllocated;    // +0x0D
    // DynamicVectorClass<T> data:
    int             Count;          // +0x10
    int             CapacityIncrement; // +0x14

    // DynamicVectorClass<T>::AddItem — inlined into SpawnParticle by the original.
    bool AddItem(ParticleClass* item)
    {
        if (Count >= Capacity) {
            if (!IsAllocated && Capacity != 0) {
                return false;
            }
            if (CapacityIncrement <= 0) {
                return false;
            }
            if (!SetCapacity(Capacity + CapacityIncrement, 0)) {
                return false;
            }
        }
        int index = Count;
        Count = index + 1;
        Items[index] = item;
        return true;
    }
};

class ParticleSystemClass
{
public:
    // FUNCTION: GAMEMD 0x62E380  ParticleSystemClass::SpawnParticle (__thiscall)
    ParticleClass* SpawnParticle(const CoordStruct& coords1, const CoordStruct& coords2);
    // FUNCTION: GAMEMD 0x62E430  ParticleSystemClass::SpawnParticle (__thiscall)
    ParticleClass* SpawnParticle(ParticleTypeClass* pType, const CoordStruct& coords);

    char                     _base[0xAC];   // +0x000  ObjectClass base (P2)
    ParticleSystemTypeClass* Type;          // +0x0AC
    char                     _gap_b0[0x0C]; // +0x0B0  SpawnDistanceToOwner (CoordStruct)
    ParticleSpawnVector      Particles;     // +0x0BC
};

GG_STATIC_ASSERT(offsetof(ParticleSystemClass, Type)      == 0xAC);
GG_STATIC_ASSERT(offsetof(ParticleSystemClass, Particles) == 0xBC);
#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(ParticleSpawnVector, Items)             == 0x04);
GG_STATIC_ASSERT(offsetof(ParticleSpawnVector, Capacity)          == 0x08);
GG_STATIC_ASSERT(offsetof(ParticleSpawnVector, IsAllocated)       == 0x0D);
GG_STATIC_ASSERT(offsetof(ParticleSpawnVector, Count)             == 0x10);
GG_STATIC_ASSERT(offsetof(ParticleSpawnVector, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(ParticleSpawnVector)                      == 0x18);
#endif

#endif  // GG_MATCH_COMBAT_PARTICLE_SYSTEM_CLASS_H
