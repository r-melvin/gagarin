// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT /Ob1
// /Ob1 and /Ob2 both give the native body; no /Ob2-only expansion is needed.
// Native 0x5F7090..0x5F7316 initializes the component records, copies ID to
// ImageFile, assigns empty AlphaImageFile, and appends this to the type registry.
#include "../_layout/object_type_class.h"
#include "object_type_registry.h"
#include "vector_class_operations.h"
// GLOBAL: GAMEMD 0x889F64
extern const char DAT_00889F64[];

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
