// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /GR /DNDEBUG /Gy /MT
// Placement lead: this file regresses under the project /Ob2 default, so a
// definition it can see probably lived in another original file.
// Entry-point disassembly 0x5F9720..0x5F994A establishes cleanup before the
// base Load, reconstruction of cache state, and optional alpha-image lookup.
#include "../_layout/object_type_class.h"
#include <new.h>
#include <stdlib.h>

// FUNCTION: GAMEMD 0x5B40B0 (decl; reloc) -- ECX=name, DL=force, EAX=data.
// Existing source provider is in platform/mix_file_class.cpp.
void* __fastcall MixFileClass_Retrieve(char* name, bool force);

GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Image) == 0xA4);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->Image) == 4);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ImageAllocated) == 0xA8);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->ImageAllocated) == 1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, AlphaImage) == 0xAC);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->AlphaImage) == 4);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, AlphaImageFile) == 0x213);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->AlphaImageFile) == 0x19);

// FUNCTION: GAMEMD 0x5F9720
HRESULT __stdcall ObjectTypeClass::Load(IStream* stream)
{
    // Retail expands the first cleanup and calls the emitted entry for the
    // other three; both forms share the same field and ownership contract.
    VoxelMainCache.ResetStorage();
    VoxelTurretWeaponCache.FUN_005F9B60();
    VoxelShadowCache.FUN_005F9B60();
    VoxelTurretBarrelCache.FUN_005F9B60();

    delete MainVoxel.unknown_00;
    MainVoxel.unknown_00 = 0;
    delete MainVoxel.HVAData;
    MainVoxel.HVAData = 0;
    delete TurretVoxel.unknown_00;
    TurretVoxel.unknown_00 = 0;
    delete TurretVoxel.HVAData;
    TurretVoxel.HVAData = 0;
    delete BarrelVoxel.unknown_00;
    BarrelVoxel.unknown_00 = 0;
    delete BarrelVoxel.HVAData;
    BarrelVoxel.HVAData = 0;
    FUN_005F8080();

    HRESULT result = AbstractClass::Load(stream);
    if (result >= 0)
    {
        Image = 0;
        ImageAllocated = false;
        AlphaImage = 0;
        new (&VoxelMainCache) IndexClass;
        new (&VoxelTurretWeaponCache) IndexClass;
        new (&VoxelShadowCache) IndexClass;
        new (&VoxelTurretBarrelCache) IndexClass;
        MainVoxel.unknown_00 = 0;
        MainVoxel.HVAData = 0;
        TurretVoxel.unknown_00 = 0;
        TurretVoxel.HVAData = 0;
        BarrelVoxel.unknown_00 = 0;
        BarrelVoxel.HVAData = 0;
        for (int i = 0; i < 18; ++i)
        {
            ChargerTurrets[i].unknown_00 = 0;
            ChargerTurrets[i].HVAData = 0;
            ChargerBarrels[i].unknown_00 = 0;
            ChargerBarrels[i].HVAData = 0;
        }
        if (AlphaImageFile[0])
        {
            char path[260];
            // STRING: GAMEMD 0x81834C
            _makepath(path, 0, 0, AlphaImageFile, ".SHP");
            AlphaImage = MixFileClass_Retrieve(path, false);
        }
        result = S_OK;
    }
    return result;
}

// FUNCTION: GAMEMD 0x5F9B60
void IndexClass::FUN_005F9B60()
{
    ResetStorage();
}
