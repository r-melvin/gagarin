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

// FUNCTION: GAMEMD 0x006B5440
int Obj_006B5440::FUN_006B5440(const char* name)
{
    if (name != 0) {
        for (int i = 0; i < DAT_00A8EC18.Count; ++i) {
            if (FUN_007C8D20(DAT_00A8EC18.Items[i]->ID, name) == 0)
                return i;
        }
    }
    return -1;
}

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

