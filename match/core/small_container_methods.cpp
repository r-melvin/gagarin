// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Small container helpers repeated at several addresses, each bound to its own
// owner or global: a 256-entry ring buffer push (head at +0x318, tail at
// +0x314), a lookup of a record by name in a global DynamicVectorClass of
// pointers, and release of three heap blocks. Owners are placeholders `Obj_<ADDR>`; globals are named by
// retail address. Each address is verified separately.

#include <stddef.h>
#include "../_layout/voxel_resource_data.h"
#include "vector_class_operations.h"
#include "../_rt/gg_static_assert.h"

// LIBRARY: GAMEMD 0x7C8B3D -- CRT free.
extern "C" void __cdecl gg_free(void*);
// LIBRARY: GAMEMD 0x7C8D20 -- CRT case-insensitive string compare (cdecl, two pointers).
extern "C" int __cdecl strcmpi(const char* a, const char* b);

struct Obj_0054F1C0 {
    unsigned char unknown_00[0x114];
    unsigned short Ring[256];       // +0x114
    int Tail;                       // +0x314
    int Head;                       // +0x318
    bool FUN_0054F1C0(unsigned short value);
};
GG_STATIC_ASSERT(offsetof(Obj_0054F1C0, Ring) == 0x114);
GG_STATIC_ASSERT(offsetof(Obj_0054F1C0, Tail) == 0x314);
GG_STATIC_ASSERT(offsetof(Obj_0054F1C0, Head) == 0x318);

// FUNCTION: GAMEMD 0x0054F1C0
bool Obj_0054F1C0::FUN_0054F1C0(unsigned short value)
{
    int next = (Head + 1) % 256;
    if (next != Tail) {
        Ring[Head] = value;
        Head = next;
        return true;
    }
    return false;
}

struct Obj_0054F670 {
    unsigned char unknown_00[0x114];
    unsigned short Ring[256];       // +0x114
    int Tail;                       // +0x314
    int Head;                       // +0x318
    bool FUN_0054F670(unsigned short value);
};
GG_STATIC_ASSERT(offsetof(Obj_0054F670, Ring) == 0x114);
GG_STATIC_ASSERT(offsetof(Obj_0054F670, Tail) == 0x314);
GG_STATIC_ASSERT(offsetof(Obj_0054F670, Head) == 0x318);

// FUNCTION: GAMEMD 0x0054F670
bool Obj_0054F670::FUN_0054F670(unsigned short value)
{
    int next = (Head + 1) % 256;
    if (next != Tail) {
        Ring[Head] = value;
        Head = next;
        return true;
    }
    return false;
}

struct Obj_005F9990 {
    unsigned char unknown_00[0x24];
    char ID[1];                     // +0x24, name buffer
    static Obj_005F9990* FUN_005F9990(const char* name);
};
extern DynamicVectorClass<Obj_005F9990*> DAT_00AC1418;

// FUNCTION: GAMEMD 0x005F9990
Obj_005F9990* Obj_005F9990::FUN_005F9990(const char* name)
{
    for (int i = 0; i < DAT_00AC1418.Count; ++i) {
        if (strcmpi(DAT_00AC1418.Items[i]->ID, name) == 0)
            return DAT_00AC1418.Items[i];
    }
    return 0;
}

// FUNCTION: GAMEMD 0x00755D10
Obj_00755D10::~Obj_00755D10()
{
    if (Block0 != 0)
        ::operator delete(Block0);
    Block0 = 0;
    if (Block1 != 0)
        ::operator delete(Block1);
    Block1 = 0;
    if (Block2 != 0)
        ::operator delete(Block2);
    Block2 = 0;
}

// FUNCTION: GAMEMD 0x00755D60
void Obj_00755D10::FUN_00755D60()
{
    if (Block0 != 0)
        ::operator delete(Block0);
    Block0 = 0;
    if (Block1 != 0)
        ::operator delete(Block1);
    Block1 = 0;
    if (Block2 != 0)
        ::operator delete(Block2);
    Block2 = 0;
}

struct Obj_0075E4A0 {
    unsigned char unknown_00[0x24];
    char ID[1];                     // +0x24, name buffer
    static Obj_0075E4A0* FUN_0075E4A0(const char* name);
};
extern DynamicVectorClass<Obj_0075E4A0*> DAT_008874C0;

// FUNCTION: GAMEMD 0x0075E4A0
Obj_0075E4A0* Obj_0075E4A0::FUN_0075E4A0(const char* name)
{
    for (int i = 0; i < DAT_008874C0.Count; ++i) {
        if (strcmpi(DAT_008874C0.Items[i]->ID, name) == 0)
            return DAT_008874C0.Items[i];
    }
    return 0;
}
