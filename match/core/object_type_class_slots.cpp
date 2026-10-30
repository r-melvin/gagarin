// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// Canonical ObjectTypeClass methods, ordered by retail address. The original TU
// placement of most recovered bodies is not established by available evidence.

#include "../_layout/object_type_class.h"
#include "object_type_registry.h"
#include "vector_class_operations.h"
#include "../platform/ccfile_class.h"
#include <stdio.h>
#include <stdlib.h>
#include "../platform/ccini_class_methods.h"
#include "../audio/voc_class_methods.h"
#include <string.h>
#include <new.h>
#include "../_layout/techno_type_class.h"
#include "../_layout/cell.h"

// ImageFile, assigns empty AlphaImageFile, and appends this to the type registry.
// GLOBAL: GAMEMD 0x889F64
extern const char DAT_00889F64[];

// Each function retains its own native replacement/failure semantics.

// ObjectType layout. Key addresses, field widths and both return paths were
// checked from entry-point disassembly; sound and RGB readers use shared APIs.

// GLOBAL: GAMEMD 0x887180 -- art INI receiver in the native read calls.
extern CCINIClass DAT_00887180;
// STRING: GAMEMD 0x889F64 -- shared empty default text.
// FUNCTION: GAMEMD 0x5B40B0 (decl; reloc), ECX=path, DL=force.
void* __fastcall MixFileClass_Retrieve(char* path, bool force);

GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ID) == 0x24);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->ID) == 0x19);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ImageFile) == 0x1F8);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->ImageFile) == 0x19);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, AlphaImageFile) == 0x213);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->AlphaImageFile) == 0x19);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, CrushSound) == 0x1F0);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->CrushSound) == 0x4);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, AmbientSound) == 0x1F4);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->AmbientSound) == 0x4);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Crushable) == 0x22D);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->Crushable) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Bombable) == 0x22E);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->Bombable) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, NoSpawnAlt) == 0x1E8);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->NoSpawnAlt) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, AlternateArcticArt) == 0x211);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->AlternateArcticArt) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, RadarInvisible) == 0x22F);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->RadarInvisible) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Selectable) == 0x230);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->Selectable) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, LegalTarget) == 0x231);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->LegalTarget) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Armor) == 0x9C);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->Armor) == 0x4);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Strength) == 0xA0);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->Strength) == 0x4);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Immune) == 0x233);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->Immune) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Insignificant) == 0x232);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->Insignificant) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, HasRadialIndicator) == 0x238);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->HasRadialIndicator) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, RadialColor) == 0x98);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->RadialColor) == 0x3);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, IgnoresFirestorm) == 0x239);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->IgnoresFirestorm) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, UseLineTrail) == 0x23A);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->UseLineTrail) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, LineTrailColor) == 0x23B);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->LineTrailColor) == 0x3);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, LineTrailColorDecrement) == 0x240);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->LineTrailColorDecrement) == 0x4);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Theater) == 0x22C);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->Theater) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, NewTheater) == 0x237);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->NewTheater) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Voxel) == 0x236);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->Voxel) == 0x1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, AlphaImage) == 0xAC);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->AlphaImage) == 0x4);

// charger resources and destroys cache/voxel members in reverse order.

GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Image) == 0xA4);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->Image) == 4);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ImageAllocated) == 0xA8);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->ImageAllocated) == 1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ChargerTurrets) == 0xC8);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ChargerBarrels) == 0x158);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->ChargerTurrets) == 0x90);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->ChargerBarrels) == 0x90);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, VoxelMainCache) == 0x244);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, VoxelTurretWeaponCache) == 0x258);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, VoxelShadowCache) == 0x26C);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, VoxelTurretBarrelCache) == 0x280);
GG_STATIC_ASSERT(sizeof(IndexClass) == 0x14);

// base Load, reconstruction of cache state, and optional alpha-image lookup.

// FUNCTION: GAMEMD 0x5B40B0 (decl; reloc) -- ECX=name, DL=force, EAX=data.
// Existing source provider is in platform/mix_file_class.cpp.
void* __fastcall MixFileClass_Retrieve(char* name, bool force);

GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->AlphaImage) == 4);

// the kind is 0x28, virtual slot39 returns a pointer, and byte +0xCA1 is set.

//
// order. 0x428E40 sits in the address range of the AnimTypeClass unit, the
// others in the ObjectTypeClass unit (0x5F75B0..). ObjectTypeClass is declared
// in _layout/object_type_class.h.


// GLOBAL: GAMEMD 0xAC1474 -- this unit's copy of a header height constant.
extern int DAT_00AC1474;

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x41CF80
CoordStruct ObjectTypeClass::vf_27(const CoordStruct& coord)
{
    return coord;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.
// FUNCTION: GAMEMD 0x41CFA0
void* ObjectTypeClass::vf_39()
{
    return Image;
}

// TU-WINDOW: past the proven bound of this TU; it may belong to a later header-less object.

// FUNCTION: GAMEMD 0x428E40
int ObjectTypeClass::vf_28()
{
    return -1;
}

// FUNCTION: GAMEMD 0x5F7090
ObjectTypeClass::ObjectTypeClass(const char* id)
    : AbstractTypeClass(id), RadialColor(0, 0, 0), Armor(0), Strength(0),
      Image(0), ImageAllocated(false), AlphaImage(0), NoSpawnAlt(false),
      MaxDimension(0), CrushSound(-1), AmbientSound(-1),
      AlternateArcticArt(false), ArcticArtInUse(false),
      Theater(false), Crushable(false), Bombable(true), RadarInvisible(false),
      Selectable(true), LegalTarget(true), Insignificant(false), Immune(false),
      IsLogic(false), AllowCellContent(true), Voxel(false), NewTheater(false),
      HasRadialIndicator(false), IgnoresFirestorm(false), UseLineTrail(false),
      LineTrailColor(128, 128, 128), LineTrailColorDecrement(16)
{
    ID.CopyTo(ImageFile);
    GgBoundedText<25>(DAT_00889F64).CopyTo(AlphaImageFile);
    StaticVectorHolder_00AC1418::DAT_00AC1418.AddItem(this);
}
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, RadialColor) == 0x98);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Armor) == 0x9C);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Strength) == 0xA0);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Image) == 0xA4);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ImageAllocated) == 0xA8);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, AlphaImage) == 0xAC);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, MainVoxel) == 0xB0);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, TurretVoxel) == 0xB8);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, BarrelVoxel) == 0xC0);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ChargerTurrets) == 0xC8);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ChargerBarrels) == 0x158);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, NoSpawnAlt) == 0x1E8);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, MaxDimension) == 0x1EC);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, CrushSound) == 0x1F0);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, AmbientSound) == 0x1F4);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ImageFile) == 0x1F8);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, AlternateArcticArt) == 0x211);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ArcticArtInUse) == 0x212);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, AlphaImageFile) == 0x213);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Theater) == 0x22C);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Crushable) == 0x22D);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Bombable) == 0x22E);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, RadarInvisible) == 0x22F);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Selectable) == 0x230);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, LegalTarget) == 0x231);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Insignificant) == 0x232);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Immune) == 0x233);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, IsLogic) == 0x234);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, AllowCellContent) == 0x235);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Voxel) == 0x236);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, NewTheater) == 0x237);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, HasRadialIndicator) == 0x238);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, IgnoresFirestorm) == 0x239);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, UseLineTrail) == 0x23A);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, LineTrailColor) == 0x23B);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, LineTrailColorDecrement) == 0x240);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, VoxelMainCache) == 0x244);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, VoxelTurretWeaponCache) == 0x258);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, VoxelShadowCache) == 0x26C);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, VoxelTurretBarrelCache) == 0x280);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->ChargerTurrets) == 0x90);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->ChargerBarrels) == 0x90);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->AlphaImageFile) == 25);

// FUNCTION: GAMEMD 0x5F7320
ObjectTypeClass::ObjectTypeClass(const AbstractNoInit& noInit)
    : AbstractTypeClass(noInit), Image(0), MainVoxel(noInit), TurretVoxel(noInit), BarrelVoxel(noInit), ImageFile(noInit), AlphaImageFile(noInit)
{
}

// FUNCTION: GAMEMD 0x5F7400
ObjectTypeClass::~ObjectTypeClass()
{
    StaticVectorHolder_00AC1418::DAT_00AC1418.RemoveItem(this);
    if (ImageAllocated && Image)
    {
        ::operator delete(Image);
        Image = 0;
        ImageAllocated = false;
    }
    FUN_005F8080();
}

// FUNCTION: GAMEMD 0x5F75B0
int ObjectTypeClass::vf_29()
{
    return 0;
}

// FUNCTION: GAMEMD 0x5F75C0
CoordStruct ObjectTypeClass::vf_30()
{
    CoordStruct coord;
    coord.X = 10;
    coord.Y = 10;
    coord.Z = 10;
    return coord;
}

// FUNCTION: GAMEMD 0x5F75E0
CoordStruct ObjectTypeClass::vf_31()
{
    CoordStruct coord;
    coord.X = 256;
    coord.Y = 256;
    coord.Z = DAT_00AC1474 * 2;
    return coord;
}

// FUNCTION: GAMEMD 0x5F7610
int ObjectTypeClass::vf_33(HouseClass*)
{
    return 0;
}

// FUNCTION: GAMEMD 0x5F7620
int ObjectTypeClass::vf_34()
{
    return 0;
}

// FUNCTION: GAMEMD 0x5F7630
SHPStruct* ObjectTypeClass::vf_38()
{
    return 0;
}

// Function-local static of slot 36: two cells, (0, 0) and (0x7FFF, 0x7FFF), built through temporaries; the
// empty destructor is registered with atexit (retail 0x5F76A0 is a lone RET).
struct Range_005F7640 {
    CellStruct cells[2];
    Range_005F7640()
    {
        CellStruct low;
        low.X = 0;
        low.Y = 0;
        cells[0] = low;
        CellStruct high;
        high.X = 0x7FFF;
        high.Y = 0x7FFF;
        cells[1] = high;
    }
    ~Range_005F7640() {}
};

// FUNCTION: GAMEMD 0x5F7640
CellStruct* ObjectTypeClass::vf_36(int a1)
{
    static Range_005F7640 range;
    return range.cells;
}

// FUNCTION: GAMEMD 0x5F7A90
bool ObjectTypeClass::FUN_005F7A90(const char* image, int index)
{
    char name[256];
    char path[260];
    // STRING: GAMEMD 0x832ABC
    // STRING: GAMEMD 0x832AB4
    if (index == 0) sprintf(name, "%sTUR", image);
    else sprintf(name, "%sTUR%d", image, index);
    // STRING: GAMEMD 0x8194AC
    _makepath(path, 0, 0, name, ".VXL");
    CCFileClass modelFile(path);
    if (!modelFile.Exists(0)) return false;
    if (ChargerTurrets[index].unknown_00) {
        delete ChargerTurrets[index].unknown_00;
        ChargerTurrets[index].unknown_00 = 0;
    }
    bool modelLoaded = false;
    ChargerTurrets[index].unknown_00 = new Obj_00755D10(&modelFile, 0);
    if (ChargerTurrets[index].unknown_00 && !ChargerTurrets[index].unknown_00->unknown_00)
        modelLoaded = true;
    if (index == 0) sprintf(name, "%sTUR", image);
    else sprintf(name, "%sTUR%d", image, index);
    // STRING: GAMEMD 0x8194A0
    _makepath(path, 0, 0, name, ".HVA");
    CCFileClass animationFile(path);
    if (ChargerTurrets[index].HVAData) {
        delete ChargerTurrets[index].HVAData;
        ChargerTurrets[index].HVAData = 0;
    }
    bool animationLoaded = false;
    ChargerTurrets[index].HVAData = new Obj_005BD5A0(&animationFile);
    if (ChargerTurrets[index].HVAData && !ChargerTurrets[index].HVAData->unknown_00)
        animationLoaded = true;
    if (modelLoaded && animationLoaded) {
        ChargerTurrets[index].HVAData->FUN_005BD730(
            ChargerTurrets[index].unknown_00->FUN_007564b0(0, 0)->unknown_0C);
        return true;
    }
    if (ChargerTurrets[index].unknown_00) {
        delete ChargerTurrets[index].unknown_00;
        ChargerTurrets[index].unknown_00 = 0;
    }
    if (ChargerTurrets[index].HVAData) {
        delete ChargerTurrets[index].HVAData;
        ChargerTurrets[index].HVAData = 0;
    }
    return false;
}

// FUNCTION: GAMEMD 0x5F7DB0
bool ObjectTypeClass::FUN_005F7DB0(const char* image, int index)
{
    char name[256];
    char path[260];
    // STRING: GAMEMD 0x832AD0
    // STRING: GAMEMD 0x832AC4
    if (index == 0) sprintf(name, "%sBARL", image);
    else sprintf(name, "%sBARL%d", image, index);
    _makepath(path, 0, 0, name, ".VXL");
    CCFileClass modelFile(path);
    if (!modelFile.Exists(0)) return true;
    bool modelLoaded = false;
    ChargerBarrels[index].unknown_00 = new Obj_00755D10(&modelFile, 0);
    if (ChargerBarrels[index].unknown_00 && !ChargerBarrels[index].unknown_00->unknown_00)
        modelLoaded = true;
    if (index == 0) sprintf(name, "%sBARL", image);
    else sprintf(name, "%sBARL%d", image, index);
    _makepath(path, 0, 0, name, ".HVA");
    CCFileClass animationFile(path);
    bool animationLoaded = false;
    ChargerBarrels[index].HVAData = new Obj_005BD5A0(&animationFile);
    if (ChargerBarrels[index].HVAData && !ChargerBarrels[index].HVAData->unknown_00)
        animationLoaded = true;
    if (modelLoaded && animationLoaded) {
        ChargerBarrels[index].HVAData->FUN_005BD730(
            ChargerBarrels[index].unknown_00->FUN_007564b0(0, 0)->unknown_0C);
        return true;
    }
    // Native 0x5F7FD0 onward releases failed resources without clearing slots.
    if (ChargerBarrels[index].unknown_00) delete ChargerBarrels[index].unknown_00;
    if (ChargerBarrels[index].HVAData) delete ChargerBarrels[index].HVAData;
    return false;
}
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ChargerTurrets) == 0xC8);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ChargerBarrels) == 0x158);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->ChargerTurrets) == 0x90);
GG_STATIC_ASSERT(sizeof(((ObjectTypeClass*)0)->ChargerBarrels) == 0x90);

// FUNCTION: GAMEMD 0x5F8080
void ObjectTypeClass::FUN_005F8080()
{
    for (int i = 0; i < 18; ++i)
    {
        if (ChargerTurrets[i].unknown_00)
        {
            delete ChargerTurrets[i].unknown_00;
            ChargerTurrets[i].unknown_00 = 0;
        }
        if (ChargerTurrets[i].HVAData)
        {
            delete ChargerTurrets[i].HVAData;
            ChargerTurrets[i].HVAData = 0;
        }
        if (ChargerBarrels[i].unknown_00)
        {
            delete ChargerBarrels[i].unknown_00;
            ChargerBarrels[i].unknown_00 = 0;
        }
        if (ChargerBarrels[i].HVAData)
        {
            delete ChargerBarrels[i].HVAData;
            ChargerBarrels[i].HVAData = 0;
        }
    }
}

// FUNCTION: GAMEMD 0x5F8CE0
void ObjectTypeClass::FUN_005F8CE0()
{
    // Native UnitType RTTI at table7F6218 lists the TechnoType base at +0.
    if (vf_11() == 0x28 && vf_39() && static_cast<TechnoTypeClass*>(this)->bools_C8C[21]) {
        char name[256];
        char path[260];
        // STRING: GAMEMD 0x832ABC
        sprintf(name, "%sTUR", ImageFile.Data);
        // STRING: GAMEMD 0x8194AC
        _makepath(path, 0, 0, name, ".VXL");
        CCFileClass turretFile(path);
        if (turretFile.Exists(0)) {
            delete TurretVoxel.unknown_00;
            TurretVoxel.unknown_00 = new Obj_00755D10(&turretFile, 0);
            if (TurretVoxel.unknown_00 && !TurretVoxel.unknown_00->unknown_00) {
                sprintf(name, "%sTUR", ImageFile.Data);
                // STRING: GAMEMD 0x8194A0
                _makepath(path, 0, 0, name, ".HVA");
                CCFileClass animationFile(path);
                delete TurretVoxel.HVAData;
                TurretVoxel.HVAData = new Obj_005BD5A0(&animationFile);
                TurretVoxel.HVAData->FUN_005BD730(TurretVoxel.unknown_00->FUN_007564b0(0, 0)->unknown_0C);
            }
        }
        // STRING: GAMEMD 0x832AD0
        sprintf(name, "%sBARL", ImageFile.Data);
        _makepath(path, 0, 0, name, ".VXL");
        CCFileClass barrelFile(path);
        if (barrelFile.Exists(0)) {
            delete BarrelVoxel.unknown_00;
            BarrelVoxel.unknown_00 = new Obj_00755D10(&barrelFile, 0);
            if (BarrelVoxel.unknown_00 && !BarrelVoxel.unknown_00->unknown_00) {
                sprintf(name, "%sBARL", ImageFile.Data);
                _makepath(path, 0, 0, name, ".HVA");
                CCFileClass animationFile(path);
                delete BarrelVoxel.HVAData;
                BarrelVoxel.HVAData = new Obj_005BD5A0(&animationFile);
                BarrelVoxel.HVAData->FUN_005BD730(BarrelVoxel.unknown_00->FUN_007564b0(0, 0)->unknown_0C);
            }
        }
    }
}
GG_STATIC_ASSERT(offsetof(TechnoTypeClass, bools_C8C) + 21 == 0xCA1);
GG_STATIC_ASSERT(sizeof(((TechnoTypeClass*)0)->bools_C8C[21]) == 1);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ImageFile) == 0x1F8);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, TurretVoxel) == 0xB8);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, BarrelVoxel) == 0xC0);

// FUNCTION: GAMEMD 0x5F92D0
bool ObjectTypeClass::vf_25(CCINIClass* ini)
{
    ini->Reset();
    if (AbstractTypeClass::vf_25(ini))
    {
        char previous[25];
        char soundName[128];
        char path[260];
        strcpy(previous, ImageFile);
        // STRING: GAMEMD 0x819420
        ini->FUN_00528A10(ID, "Image", previous, ImageFile, 25);
        strcpy(previous, AlphaImageFile);
        // STRING: GAMEMD 0x832C00
        ini->FUN_00528A10(ID, "AlphaImage", previous, AlphaImageFile, 25);

        int sound = CrushSound;
        // STRING: GAMEMD 0x832BF4
        if (ini->FUN_00528A10(ID, "CrushSound", DAT_00889F64, soundName, 128))
        {
            int found = VocClass::FindIndex(soundName);
            if (found != -1)
                sound = found;
        }
        CrushSound = sound;
        sound = AmbientSound;
        int ambient = -1;
        // STRING: GAMEMD 0x832BE4
        if (ini->FUN_00528A10(ID, "AmbientSound", DAT_00889F64, soundName, 128))
            ambient = VocClass::FindIndex(soundName);
        AmbientSound = ambient != -1 ? ambient : sound;
        // STRING: GAMEMD 0x832BD8
        Crushable = ini->FUN_005295F0(ID, "Crushable", Crushable);
        // STRING: GAMEMD 0x832BCC
        Bombable = ini->FUN_005295F0(ID, "Bombable", Bombable);
        // STRING: GAMEMD 0x832BC0
        NoSpawnAlt = ini->FUN_005295F0(ID, "NoSpawnAlt", NoSpawnAlt);
        // STRING: GAMEMD 0x832BAC
        AlternateArcticArt = ini->FUN_005295F0(ID, "AlternateArcticArt", AlternateArcticArt);
        // STRING: GAMEMD 0x832B9C
        RadarInvisible = ini->FUN_005295F0(ID, "RadarInvisible", RadarInvisible);
        // STRING: GAMEMD 0x832B90
        Selectable = ini->FUN_005295F0(ID, "Selectable", Selectable);
        // STRING: GAMEMD 0x832B84
        LegalTarget = ini->FUN_005295F0(ID, "LegalTarget", LegalTarget);
        // STRING: GAMEMD 0x81D9D4
        Armor = ini->ReadArmor(ID, "Armor", Armor);
        // STRING: GAMEMD 0x832B78
        Strength = ini->FUN_005276D0(ID, "Strength", Strength);
        // STRING: GAMEMD 0x832B70
        Immune = ini->FUN_005295F0(ID, "Immune", Immune);
        // STRING: GAMEMD 0x832B60
        Insignificant = ini->FUN_005295F0(ID, "Insignificant", Insignificant);
        // STRING: GAMEMD 0x832B4C
        HasRadialIndicator = ini->FUN_005295F0(ID, "HasRadialIndicator", HasRadialIndicator);
        // STRING: GAMEMD 0x832B40
        RadialColor = ini->Read3Bytes(ID, "RadialColor", RadialColor);
        // STRING: GAMEMD 0x832B2C
        IgnoresFirestorm = ini->FUN_005295F0(ID, "IgnoresFirestorm", IgnoresFirestorm);
        // STRING: GAMEMD 0x832B1C
        UseLineTrail = DAT_00887180.FUN_005295F0(ImageFile, "UseLineTrail", UseLineTrail);
        // STRING: GAMEMD 0x832B0C
        LineTrailColor = DAT_00887180.Read3Bytes(ImageFile, "LineTrailColor", LineTrailColor);
        // STRING: GAMEMD 0x832AF4
        LineTrailColorDecrement = DAT_00887180.FUN_005276D0(ImageFile, "LineTrailColorDecrement", LineTrailColorDecrement);
        // STRING: GAMEMD 0x818658
        Theater = DAT_00887180.FUN_005295F0(ImageFile, "Theater", Theater);
        // STRING: GAMEMD 0x81864C
        NewTheater = DAT_00887180.FUN_005295F0(ImageFile, "NewTheater", NewTheater);
        // STRING: GAMEMD 0x832AEC
        Voxel = DAT_00887180.FUN_005295F0(ImageFile, "Voxel", Voxel);
        if (!Voxel && vf_11() != 5)
            FUN_005F9070();
        if (AlphaImageFile[0])
        {
            // STRING: GAMEMD 0x81834C
            _makepath(path, 0, 0, AlphaImageFile, ".SHP");
            AlphaImage = MixFileClass_Retrieve(path, false);
        }
        return true;
    }
    return false;
}

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

// FUNCTION: GAMEMD 0x5F9950
HRESULT __stdcall ObjectTypeClass::Save(IStream* pStm, BOOL fClearDirty)
{
    HRESULT hr = AbstractClass::Save(pStm, fClearDirty);
    if (hr >= 0)
        hr = 0;
    return hr;
}

// FUNCTION: GAMEMD 0x5F9970
HRESULT __stdcall ObjectTypeClass::GetSizeMax(ULARGE_INTEGER* size)
{
    HRESULT result = AbstractClass::GetSizeMax(size);
    if (result >= 0)
        result = S_OK;
    return result;
}

// SYNTHETIC: GAMEMD 0x5F9AE0
// Compiler-generated scalar deleting destructor for ObjectTypeClass.
