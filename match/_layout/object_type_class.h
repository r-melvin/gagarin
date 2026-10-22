// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Oracle: ctor FUN_0x005F7090 (docs/decomp_spec/type_hierarchy_layout.md),
//   field writes cross-checked vs YRpp ObjectTypeClass.h. Triple-confirmed via
//   YRpp pad anchors (unused_9B / align_A9 / align_1E9 / align_23E) and the
//   downstream TechnoTypeClass align_2FC@0x2FC, which lands only if size==0x294.
//
// ObjectTypeClass — base blueprint for every drawable object type (units,
// buildings, infantry, aircraft, anims, bullets, terrain, smudge, overlay, …).
// Derives AbstractTypeClass (the AbstractClass COM spine + ID/Name strings) at
// offset 0, and adds the shared art/voxel/strength fields from 0x98.
#ifndef GG_MATCH_LAYOUT_OBJECT_TYPE_CLASS_H
#define GG_MATCH_LAYOUT_OBJECT_TYPE_CLASS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "abstract_type_class.h"
#include "components.h"

// ObjectTypeClass  (0x98..0x293, sizeof = 0x294)
struct ObjectTypeClass : AbstractTypeClass
{
    // Slots 27-39 of the primary table (40 slots, RTTI ".?AVObjectTypeClass@@").
    // Placeholders; argument counts from each base body's RET n. Slots 32 and
    // 35 hold the shared stub 0x4C9150 in the ObjectTypeClass table.
    virtual void* vf_27(void* a1, void* a2);   // 27  0x41CF80
    virtual int vf_28();                       // 28  0x428E40
    virtual int vf_29();                       // 29  0x5F75B0
    virtual int vf_30(int a1);                 // 30  0x5F75C0
    virtual int vf_31(int a1);                 // 31  0x5F75E0
    virtual int vf_32();                       // 32  0x4C9150
    virtual int vf_33(int a1);                 // 33  0x5F7610
    virtual int vf_34();                       // 34  0x5F7620
    virtual int vf_35();                       // 35  0x4C9150
    virtual void* vf_36(int a1);               // 36  0x5F7640
    virtual void vf_37(int a1, int a2, int a3, int a4); // 37  0x5F7900
    virtual int vf_38();                       // 38  0x5F7630
    virtual void* vf_39();                     // 39  0x41CFA0: returns Image (+0xA4)

    ColorStruct   RadialColor;            // +0x98  (3 bytes)
    unsigned char unused_9B;              // +0x9B
    int           Armor;                  // +0x9C  (enum)
    int           Strength;               // +0xA0
    void*         Image;                  // +0xA4  SHPStruct* (truncation)
    bool          ImageAllocated;         // +0xA8
    unsigned char align_A9[3];            // +0xA9
    void*         AlphaImage;             // +0xAC  SHPStruct* (truncation)
    VoxelStruct   MainVoxel;              // +0xB0  (8 bytes)
    VoxelStruct   TurretVoxel;            // +0xB8
    VoxelStruct   BarrelVoxel;            // +0xC0
    VoxelStruct   ChargerTurrets[0x12];   // +0xC8  (0xC8..0x157)
    VoxelStruct   ChargerBarrels[0x12];   // +0x158 (0x158..0x1E7)
    bool          NoSpawnAlt;             // +0x1E8
    unsigned char align_1E9[3];           // +0x1E9
    int           MaxDimension;           // +0x1EC
    int           CrushSound;             // +0x1F0  (ctor = -1)
    int           AmbientSound;           // +0x1F4  (ctor = -1)
    char          ImageFile[0x19];        // +0x1F8 (0x1F8..0x210)
    bool          AlternateArcticArt;     // +0x211
    bool          ArcticArtInUse;         // +0x212
    char          AlphaImageFile[0x19];   // +0x213 (0x213..0x22B)
    bool          Theater;                // +0x22C
    bool          Crushable;              // +0x22D
    bool          Bombable;               // +0x22E  (ctor = 1)
    bool          RadarInvisible;         // +0x22F
    bool          Selectable;             // +0x230  (ctor = 1)
    bool          LegalTarget;            // +0x231  (ctor = 1)
    bool          Insignificant;          // +0x232
    bool          Immune;                 // +0x233
    bool          IsLogic;                // +0x234
    bool          AllowCellContent;       // +0x235  (ctor = 1)
    bool          Voxel;                  // +0x236
    bool          NewTheater;             // +0x237
    bool          HasRadialIndicator;     // +0x238
    bool          IgnoresFirestorm;       // +0x239
    bool          UseLineTrail;           // +0x23A
    ColorStruct   LineTrailColor;         // +0x23B  (3 bytes)
    unsigned char align_23E[2];           // +0x23E
    int           LineTrailColorDecrement;// +0x240
    IndexClass    VoxelMainCache;         // +0x244  (0x14)
    IndexClass    VoxelTurretWeaponCache; // +0x258  (0x14)
    IndexClass    VoxelShadowCache;       // +0x26C  (0x14)
    IndexClass    VoxelTurretBarrelCache; // +0x280  (0x14)
};

GG_STATIC_ASSERT(offsetof(ObjectTypeClass, RadialColor)            == 0x98);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Armor)                  == 0x9C);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Strength)               == 0xA0);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Image)                  == 0xA4);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, AlphaImage)             == 0xAC);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, MainVoxel)              == 0xB0);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ChargerTurrets)         == 0xC8);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ChargerBarrels)         == 0x158);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, MaxDimension)           == 0x1EC);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, ImageFile)              == 0x1F8);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, AlphaImageFile)         == 0x213);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, Theater)                == 0x22C);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, LineTrailColor)         == 0x23B);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, LineTrailColorDecrement)== 0x240);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, VoxelMainCache)         == 0x244);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, VoxelTurretWeaponCache) == 0x258);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, VoxelShadowCache)       == 0x26C);
GG_STATIC_ASSERT(offsetof(ObjectTypeClass, VoxelTurretBarrelCache) == 0x280);
GG_STATIC_ASSERT(sizeof(ObjectTypeClass)                           == 0x294);

#endif  // GG_MATCH_LAYOUT_OBJECT_TYPE_CLASS_H
