// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
// Entry-origin retail span 0x6E5B60..0x6E5C99: 314 bytes, RET 4.
// Instructions confirm base construction, field/vptr writes, identity copy,
// array index and two vector appends. Original private names remain unknown.
// LIBRARY: GAMEMD 0x7C91D0 -- strncpy.
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy
// GX emits exception cleanup absent from the retail body.
#include <stddef.h>
#include "../_layout/tag_type_class.h"
#include "../core/abstract_registry.h"

extern "C" char* __cdecl strncpy(char*, const char*, unsigned int);

struct TagTypeCtorVector
{
    virtual ~TagTypeCtorVector();
    virtual bool Equals(const TagTypeCtorVector& other) const;
    virtual bool SetCapacity(int capacity, void* memory);
    void* Items;
    int Capacity;
    unsigned char IsInitialized;
    unsigned char IsAllocated;
    unsigned char unknown_0E[2];
    int Count;
    int CapacityIncrement;
};
GG_STATIC_ASSERT(offsetof(TagTypeCtorVector, Items) == 4);
GG_STATIC_ASSERT(offsetof(TagTypeCtorVector, Capacity) == 8);
GG_STATIC_ASSERT(offsetof(TagTypeCtorVector, IsAllocated) == 0xD);
GG_STATIC_ASSERT(offsetof(TagTypeCtorVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(TagTypeCtorVector, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(TagTypeCtorVector) == 0x18);

static inline bool TagTypeCtorAdd(TagTypeCtorVector* vector, TagTypeClass* item)
{
    if (vector->Count >= vector->Capacity) {
        if (!vector->IsAllocated && vector->Capacity != 0)
            return false;
        if (vector->CapacityIncrement <= 0)
            return false;
        if (!vector->SetCapacity(vector->Capacity + vector->CapacityIncrement, 0))
            return false;
    }
    int index = vector->Count++;
    ((TagTypeClass**)vector->Items)[index] = item;
    return true;
}

// FUNCTION: GAMEMD 0x6E5B60
TagTypeClass::TagTypeClass(const char* id)
    : AbstractTypeClass(id), unknown_98(-1), Persistence(0), FirstTrigger(0)
{

    char name[0x31];
    if (ID == 0) {
        name[0] = 0;
    } else {
        strncpy(name, ID, 0x30);
        name[0x30] = 0;
    }
    char* destination = Name;
    if (name != destination) {
        for (int i = 0; i < 0x31; ++i)
            destination[i] = name[i];
    }

    unknown_98 = TagTypes.Count;
    TagTypeCtorAdd(reinterpret_cast<TagTypeCtorVector*>(&TagTypes), this);
    TagTypeCtorAdd(reinterpret_cast<TagTypeCtorVector*>(&DAT_00B0F670), this);
}
