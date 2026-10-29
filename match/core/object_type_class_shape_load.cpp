// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Os /Gr /GR /DNDEBUG /Gy /MT /Ob1
// Entry 0x5F9070..0x5F92C3: arctic suffix, theater filenames, shape lookup,
// fallback filename byte and maximum signed dimension.
#include "../_layout/object_type_class.h"
#include "../_layout/shp_struct.h"
#include "scenario_class_methods.h"
#include "theater_methods.h"
#include <stdio.h>
#include <stdlib.h>
#include <new.h>
// GLOBAL: GAMEMD 0xA8B230
extern ScenarioClass* ScenarioInstance;
// GLOBAL: GAMEMD 0x7E1B78
extern Theater Theater_Array[6];
// FUNCTION: GAMEMD 0x5B40B0 (decl; reloc)
void* __fastcall MixFileClass_Retrieve(char*, bool);

static inline char GgLowerFilenameByte(char c)
{
    if (c >= 'A' && c <= 'Z') c += 'a' - 'A';
    return c;
}

// FUNCTION: GAMEMD 0x5F9070
void ObjectTypeClass::FUN_005F9070()
{
    if (AlternateArcticArt && ScenarioInstance->unknown_1258 == 1 && !ImageAllocated) {
        if (!ArcticArtInUse) {
            char alternate[256];
            // STRING: GAMEMD 0x832AE8
            sprintf(alternate, "%sA", ImageFile.Data);
            GgBoundedText<25>(alternate).CopyTo(ImageFile);
            ArcticArtInUse = true;
        }
    } else {
        ArcticArtInUse = false;
    }
    char path[260];
    // STRING: GAMEMD 0x81834C
    _makepath(path, 0, 0, ImageFile, ".SHP");
    if (Theater) {
        _makepath(path, 0, 0, ImageFile, Theater_Array[ScenarioInstance->unknown_1258].Extension);
    } else if (NewTheater && ScenarioInstance->unknown_1258 != -1) {
        char first = GgLowerFilenameByte(path[0]);
        char second = GgLowerFilenameByte(path[1]);
        if ((first == 'g' || first == 'n' || first == 'c' || first == 'y') &&
            (second == 'a' || second == 't'))
            path[1] = Theater_Array[ScenarioInstance->unknown_1258].unknown_56;
    }
    if (ImageAllocated && Image) ::operator delete(Image);
    Image = 0;
    ImageAllocated = false;
    if (vf_11() == 0x15 || vf_11() == 5) {
        Image = MixFileClass_Retrieve(path, true);
        if (!Image) {
            path[1] = 'G';
            Image = MixFileClass_Retrieve(path, true);
        }
    } else if (vf_11() != 0x1E && vf_11() != 0x25) {
        Image = MixFileClass_Retrieve(path, false);
        if (!Image) {
            path[1] = 'G';
            Image = MixFileClass_Retrieve(path, false);
        }
    }
    if (Image) {
        // The native loads signed 16-bit dimensions at image+2 and image+4.
        SHPStruct* shape = static_cast<SHPStruct*>(Image);
        int dimension = shape->unknown_02 > shape->unknown_04 ? shape->unknown_02 : shape->unknown_04;
        if (dimension <= 8) dimension = 8;
        MaxDimension = dimension;
    }
}
GG_STATIC_ASSERT(offsetof(ScenarioClass, unknown_1258) == 0x1258);
GG_STATIC_ASSERT(sizeof(((ScenarioClass*)0)->unknown_1258) == 4);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, AlternateArcticArt) == 0x211);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ArcticArtInUse) == 0x212);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ImageAllocated) == 0xA8);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Image) == 0xA4);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ImageFile) == 0x1F8);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Theater) == 0x22C);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, NewTheater) == 0x237);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, MaxDimension) == 0x1EC);
GG_STATIC_ASSERT(sizeof(((Theater*)0)->Extension) == 4);
GG_STATIC_ASSERT(sizeof(((Theater*)0)->unknown_56) == 1);
