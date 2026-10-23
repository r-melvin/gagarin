// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//
// Lookup of an element index by name in a global DynamicVectorClass of
// pointers, repeated for three element types. Each record carries its name
// buffer at +0x24 (the string compare is the statically linked CRT routine
// at 0x7C8D20). The three owners are placeholders `Obj_<ADDR>`; the global
// vectors are named by retail address.

#include "vector_class_operations.h"

// LIBRARY: GAMEMD 0x7C8D20 -- CRT string compare (cdecl, two pointers).
extern "C" int __cdecl FUN_007C8D20(const char* a, const char* b);

struct Obj_006B5440 {
    unsigned char unknown_00[0x24];
    char ID[1];                     // +0x24, name buffer
    static int FUN_006B5440(const char* name);
};
extern DynamicVectorClass<Obj_006B5440*> DAT_00A8EC18;


struct Obj_006CEE60 {
    unsigned char unknown_00[0x24];
    char ID[1];                     // +0x24, name buffer
    static int FUN_006CEE60(const char* name);
};
extern DynamicVectorClass<Obj_006CEE60*> DAT_00A8E330;

// FUNCTION: GAMEMD 0x006CEE60
int Obj_006CEE60::FUN_006CEE60(const char* name)
{
    if (name != 0) {
        for (int i = 0; i < DAT_00A8E330.Count; ++i) {
            if (FUN_007C8D20(DAT_00A8E330.Items[i]->ID, name) == 0)
                return i;
        }
    }
    return -1;
}

struct Obj_0074B640 {
    unsigned char unknown_00[0x24];
    char ID[1];                     // +0x24, name buffer
    static int FUN_0074B640(const char* name);
};
extern DynamicVectorClass<Obj_0074B640*> DAT_00A8EB28;

struct Obj_006E81D0 {
    unsigned char unknown_00[0x64];
    char ID[1];                     // +0x64, name buffer
    static Obj_006E81D0* FUN_006E81D0(const char* name);
};
extern DynamicVectorClass<Obj_006E81D0*> DAT_00A8E8D0;

// FUNCTION: GAMEMD 0x006E81D0
// Returns the element itself (null when `name` is null or nothing matches).
Obj_006E81D0* Obj_006E81D0::FUN_006E81D0(const char* name)
{
    if (name != 0) {
        for (int i = 0; i < DAT_00A8E8D0.Count; ++i) {
            if (FUN_007C8D20(name, DAT_00A8E8D0.Items[i]->ID) == 0)
                return DAT_00A8E8D0.Items[i];
        }
    }
    return 0;
}

// FUNCTION: GAMEMD 0x0074B640
int Obj_0074B640::FUN_0074B640(const char* name)
{
    if (name != 0) {
        for (int i = 0; i < DAT_00A8EB28.Count; ++i) {
            if (FUN_007C8D20(DAT_00A8EB28.Items[i]->ID, name) == 0)
                return i;
        }
    }
    return -1;
}

struct Obj_00773030 {
    unsigned char unknown_00[0x24];
    char ID[1];                     // +0x24, name buffer
    static int FUN_00773030(const char* name);
};
extern DynamicVectorClass<Obj_00773030*> DAT_00887568;

// FUNCTION: GAMEMD 0x00773030
// No null test on `name` here, unlike the lookups above.
int Obj_00773030::FUN_00773030(const char* name)
{
    for (int i = 0; i < DAT_00887568.Count; ++i) {
        if (FUN_007C8D20(DAT_00887568.Items[i]->ID, name) == 0)
            return i;
    }
    return -1;
}
