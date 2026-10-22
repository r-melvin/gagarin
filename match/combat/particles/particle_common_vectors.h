// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   The seven-slot VectorClass / DynamicVectorClass shape every pointer array and list of the particle
//   module uses (ParticleClass::Array 0xA83DC8 vptrs 0x7E9D84 / 0x7E9D64, the system arrays, the colour
//   list of ParticleTypeClass at +0x2B8 with vptrs 0x7E4E38 / 0x7E4E58). Layout and slot order match
//   match/core/vector_class.h, which this module only reads. Virtual slots are declared (no bodies
//   here) so inlined AddItem / RemoveItem reach SetCapacity / FindItemIndex through the same vtable
//   slots as retail; the out-of-line entries (0x645A70 / 0x478850 constructors, 0x4788E0 assignment,
//   0x478440 cleanup target (also matched as VectorClass<RGBClass>::Clear; the original source
//   call form is unestablished), 0x6302A0 constructor for ParticleClass*) belong to other owners and are
//   bound by address.
//
// ParticleVector<T> is the common base. Two DynamicVectorClass flavours derive from it, and they can
// NOT be merged without changing bytes: retail expands DynamicVectorClass::AddItem and the default
// constructor differently in the two groups of translation units, and VC6 compiles the two source
// shapes below differently (a shared AddItem regressed rows in both groups).
//   ParticleDynVector<T>        particle / particle-type TUs: AddItem with early returns; the default
//                               constructor calls the out-of-line base constructor 0x478850-style
//                               (capacity 0u, no memory) and then stores the growth step and count.
//   ParticleInlineDynVector<T>  system / system-type TUs: AddItem as one short-circuit condition; the
//                               default constructor is the base's inline default constructor
//                               (Items 0, Capacity 0, IsInitialized true, IsAllocated false).
// RemoveItem is identical in both and Count / CapacityIncrement sit at +0x10 / +0x14 in both.
#ifndef GG_MATCH_EFFECTS_PARTICLES_PARTICLE_COMMON_VECTORS_H
#define GG_MATCH_EFFECTS_PARTICLES_PARTICLE_COMMON_VECTORS_H

#include <stddef.h>
#include <stdlib.h>
#include "../../_rt/gg_static_assert.h"
#include "particle_common_types.h"

// VectorClass<T> layout: vptr, Items, Capacity, IsInitialized, IsAllocated.
template <class T> class ParticleVector
{
public:
    // Inline default constructor (the system TUs' default-constructed arrays).
    ParticleVector() : Items(0), Capacity(0), IsInitialized(true), IsAllocated(false) {}
    // FUNCTION: GAMEMD 0x645A70 (ColorList instance), 0x6302A0 (ParticleClass* instance; read-only
    // here) - stores the base vptr and the capacity, allocates only when asked.
    ParticleVector(int capacity, T* mem);
    // FUNCTION: GAMEMD 0x478850 (ColorList instance; read-only here) - a second out-of-line copy of
    // the constructor above (the type constructor's own); the unsigned capacity only selects it.
    ParticleVector(unsigned int capacity, T* mem);
    // FUNCTION: GAMEMD 0x4788E0 (ColorList instance; read-only here)
    ParticleVector<T>& operator=(const ParticleVector<T>& other);
    // FUNCTION: GAMEMD 0x478440 (ColorList instance; read-only here) - a cleanup target also matched
    // as VectorClass<RGBClass>::Clear; the original source call form is unestablished.
    // Defined inline by the translation unit that needs it (see particle_type_class.cpp: retail
    // expands it in the type's deleting destructor but not in the INI reader above it).
    virtual ~ParticleVector();
    virtual bool operator==(const ParticleVector<T>& other) const;             // 1
    virtual bool SetCapacity(int capacity, T* mem);                            // 2
    virtual void Clear();                                                      // 3
    virtual int FindItemIndex(const T& item) const;                            // 4
    virtual int Slot5(T* element) const;                                       // 5
    virtual T Slot6(int index) const;                                          // 6
    T& operator[](int index) { return Items[index]; }

    T*            Items;           // +0x04
    int           Capacity;        // +0x08
    bool          IsInitialized;   // +0x0C
    bool          IsAllocated;     // +0x0D
    unsigned char unknown_0E[2];   // +0x0E
};

// DynamicVectorClass<T> layout (particle flavour): the base plus Count and CapacityIncrement. The
// inlined members are the non-virtual bodies retail expands in its callers.
template <class T> class ParticleDynVector : public ParticleVector<T>
{
public:
    ParticleDynVector(int capacity, T* mem) : ParticleVector<T>(capacity, mem) {}
    // The full dynamic-vector constructor (type constructor 0x644BE0): growth step 10, no items.
    ParticleDynVector() : ParticleVector<T>(0u, 0) { CapacityIncrement = 10; Count = 0; }

    bool AddItem(const T& item)
    {
        if (Count >= this->Capacity) {
            if (!this->IsAllocated && this->Capacity != 0)
                return false;
            if (CapacityIncrement <= 0)
                return false;
            if (!this->SetCapacity(this->Capacity + CapacityIncrement, 0))
                return false;
        }
        int index = Count++;
        this->Items[index] = item;
        return true;
    }

    // The non-virtual lookup retail expands inline where it names the class explicitly.
    int FindIndex(const T& item) const
    {
        int i;
        for (i = 0; i < Count; ++i) {
            if (this->Items[i] == item)
                goto found;
        }
        i = -1;
    found:
        return i;
    }

    bool RemoveItem(const T& item)
    {
        int index = this->FindItemIndex(item);
        if (index != -1 && index < Count) {
            Count = Count - 1;
            for (; index < Count; ++index)
                this->Items[index] = this->Items[index + 1];
            return true;
        }
        return false;
    }

    int Count;               // +0x10
    int CapacityIncrement;   // +0x14
};

// DynamicVectorClass<T> layout (system flavour); see the file header for why it is separate.
template <class T> class ParticleInlineDynVector : public ParticleVector<T>
{
public:
    ParticleInlineDynVector() { CapacityIncrement = 10; Count = 0; }
    ParticleInlineDynVector(int capacity, T* mem) : ParticleVector<T>(capacity, mem)
    {
        CapacityIncrement = 10;
        Count = 0;
    }

    // DynamicVectorClass::AddItem, inlined by the original.
    bool AddItem(const T& item)
    {
        int cap = this->Capacity;
        if (Count < cap
            || ((this->IsAllocated || cap == 0)
                && CapacityIncrement > 0
                && this->SetCapacity(CapacityIncrement + cap, 0))) {
            (*this)[Count++] = item;
            return true;
        }
        return false;
    }

    // DynamicVectorClass::RemoveItem, inlined by the original.
    bool RemoveItem(const T& item)
    {
        int index = this->FindItemIndex(item);
        if (index != -1 && index < Count) {
            Count = Count - 1;
            for (; index < Count; ++index) {
                this->Items[index] = this->Items[index + 1];
            }
            return true;
        }
        return false;
    }

    int Count;               // +0x10
    int CapacityIncrement;   // +0x14
};
GG_STATIC_ASSERT(sizeof(ParticleVector<ParticleClass*>) == 0x10);
GG_STATIC_ASSERT(sizeof(ParticleDynVector<ParticleClass*>) == 0x18);
GG_STATIC_ASSERT(sizeof(ParticleInlineDynVector<ParticleClass*>) == 0x18);

#endif  // GG_MATCH_EFFECTS_PARTICLES_PARTICLE_COMMON_VECTORS_H
