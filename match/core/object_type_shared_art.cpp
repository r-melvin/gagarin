// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// /Ob1 and /Ob2 reproduce both native bodies.
// Native 0x5F76B0 loads four shared art resources, recording raw-file
// ownership before MIX fallback. Native 0x5F77F0 uses array destruction
// (36-byte elements, destructor 0x69E500) only for the owned entries.
#include "../_layout/obj_0069e430.h"
#include "../platform/ccfile_class.h"
// FUNCTION: GAMEMD 0x5B40B0 (decl; reloc)
void* __fastcall MixFileClass_Retrieve(char* name, bool force);
// Gagarin storage view of native AC1478..AC148B, not an original type name.
// The four pointers precede four ownership bytes in the zero-filled .data tail.
struct GgSharedArtStorage
{
    Obj_0069E430* Images[4];
    bool Owned[4];
};
GG_STATIC_ASSERT(offsetof(GgSharedArtStorage, Images) == 0);
GG_STATIC_ASSERT(sizeof(((GgSharedArtStorage*)0)->Images) == 16);
GG_STATIC_ASSERT(offsetof(GgSharedArtStorage, Owned) == 16);
GG_STATIC_ASSERT(sizeof(((GgSharedArtStorage*)0)->Owned) == 4);
GG_STATIC_ASSERT(sizeof(GgSharedArtStorage) == 20);
// GLOBAL: GAMEMD 0xAC1478
GgSharedArtStorage DAT_00AC1478;

// FUNCTION: GAMEMD 0x5F76B0
void FUN_005F76B0()
{
    if (!DAT_00AC1478.Images[0]) {
        // STRING: GAMEMD 0x832aa8
        RawFileClass file("PIPBRD.SHP");
        // Native cleanup walks these allocations with the 36-byte resource type.
        DAT_00AC1478.Images[0] = static_cast<Obj_0069E430*>(file.ReadWholeFile());
        DAT_00AC1478.Owned[0] = DAT_00AC1478.Images[0] != 0;
        if (!DAT_00AC1478.Images[0]) DAT_00AC1478.Images[0] = static_cast<Obj_0069E430*>(MixFileClass_Retrieve("PIPBRD.SHP", false));
    }
    if (!DAT_00AC1478.Images[1]) {
        // STRING: GAMEMD 0x832a9c
        RawFileClass file("PIPS.SHP");
        // Native cleanup walks these allocations with the 36-byte resource type.
        DAT_00AC1478.Images[1] = static_cast<Obj_0069E430*>(file.ReadWholeFile());
        DAT_00AC1478.Owned[1] = DAT_00AC1478.Images[1] != 0;
        if (!DAT_00AC1478.Images[1]) DAT_00AC1478.Images[1] = static_cast<Obj_0069E430*>(MixFileClass_Retrieve("PIPS.SHP", false));
    }
    if (!DAT_00AC1478.Images[2]) {
        // STRING: GAMEMD 0x832a90
        RawFileClass file("PIPS2.SHP");
        // Native cleanup walks these allocations with the 36-byte resource type.
        DAT_00AC1478.Images[2] = static_cast<Obj_0069E430*>(file.ReadWholeFile());
        DAT_00AC1478.Owned[2] = DAT_00AC1478.Images[2] != 0;
        if (!DAT_00AC1478.Images[2]) DAT_00AC1478.Images[2] = static_cast<Obj_0069E430*>(MixFileClass_Retrieve("PIPS2.SHP", false));
    }
    if (!DAT_00AC1478.Images[3]) {
        // STRING: GAMEMD 0x832a80
        RawFileClass file("TALKBUBL.SHP");
        // Native cleanup walks these allocations with the 36-byte resource type.
        DAT_00AC1478.Images[3] = static_cast<Obj_0069E430*>(file.ReadWholeFile());
        DAT_00AC1478.Owned[3] = DAT_00AC1478.Images[3] != 0;
        if (!DAT_00AC1478.Images[3]) DAT_00AC1478.Images[3] = static_cast<Obj_0069E430*>(MixFileClass_Retrieve("TALKBUBL.SHP", false));
    }
}

// FUNCTION: GAMEMD 0x5F77F0
void FUN_005F77F0()
{
    if (DAT_00AC1478.Owned[0]) {
        delete[] DAT_00AC1478.Images[0];
        DAT_00AC1478.Owned[0] = false;
    }
    if (DAT_00AC1478.Owned[1]) {
        delete[] DAT_00AC1478.Images[1];
        DAT_00AC1478.Owned[1] = false;
    }
    if (DAT_00AC1478.Owned[2]) {
        delete[] DAT_00AC1478.Images[2];
        DAT_00AC1478.Owned[2] = false;
    }
    if (DAT_00AC1478.Owned[3]) {
        delete[] DAT_00AC1478.Images[3];
        DAT_00AC1478.Owned[3] = false;
    }
}
GG_STATIC_ASSERT(sizeof(Obj_0069E430) == 0x24);
GG_STATIC_ASSERT(sizeof(void*) == 4);
GG_STATIC_ASSERT(sizeof(bool) == 1);
