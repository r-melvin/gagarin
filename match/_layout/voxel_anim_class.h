// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   RTTI for .?AVVoxelAnimClass@@ identifies ObjectClass at +0 and BounceClass
//   at +0xB0. Native allocation requests 0x148 bytes; constructor 0x7493B0
//   and member accesses establish the offsets below. The primary and adjusted
//   vtable addresses and override targets are read from the pinned retail image.
//   Native bindings for these targets are required when callers reference them;
//   this declaration adds no override body definitions or provider migrations.
#ifndef GG_MATCH_LAYOUT_VOXEL_ANIM_CLASS_H
#define GG_MATCH_LAYOUT_VOXEL_ANIM_CLASS_H

#include <stddef.h>
#include "object_class.h"
#include "../movement/bounce_class.h"

class VoxelAnimTypeClass;

// VTABLE: GAMEMD 0x7F6318
// VTABLE: GAMEMD 0x7F62FC
// VTABLE: GAMEMD 0x7F62F4
// VTABLE: GAMEMD 0x7F62EC
// The adjusted tables are the 6/1/1-slot ObjectClass interface subobjects at
// +0x04/+0x08/+0x0C; their entries equal the corresponding ObjectClass targets.
class VoxelAnimClass : public ObjectClass, public BounceClass
{
public:
    // CALLEE: GAMEMD 0x7493B0
    // The native constructor transports a type pointer; its original const qualification is unknown.
    // This const-qualified API preserves the type-list item qualification at this caller.
    VoxelAnimClass(const VoxelAnimTypeClass* type, const CoordStruct& location, int unknown_arg2);

    // Primary-table override declarations retain canonical base signatures.
    // Their native targets are documented here; this header supplies no bodies.
    // CALLEE: GAMEMD 0x74AAD0
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);
    // CALLEE: GAMEMD 0x74A970
    virtual HRESULT __stdcall Load(IStream* pStm);
    // CALLEE: GAMEMD 0x74AA10
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);
    // CALLEE: GAMEMD 0x7499F0
    // The primary slot contains deleting-destructor thunk 0x74AB50.
    virtual ~VoxelAnimClass();
    // CALLEE: GAMEMD 0x74AB20
    virtual int vf_11();
    // CALLEE: GAMEMD 0x74AB10
    virtual int vf_12();
    // CALLEE: GAMEMD 0x74AA30
    virtual void vf_13(Obj_004A1D30* crc);
    // CALLEE: GAMEMD 0x749F30
    virtual void vf_23();
    // CALLEE: GAMEMD 0x74A960
    virtual int vf_30();
    // CALLEE: GAMEMD 0x74AB30
    virtual ObjectTypeClass* vf_34();
    // CALLEE: GAMEMD 0x749B20
    virtual bool vf_65(RectangleStruct* rect, bool force, int a3);
    // CALLEE: GAMEMD 0x74AB40
    virtual void* vf_66(int a1);
    // CALLEE: GAMEMD 0x749B70
    virtual void vf_69(Point2D* point, RectangleStruct* clip);

    int                unknown_100;       // +0x100
    VoxelAnimTypeClass* unknown_104;      // +0x104; pointer used as the type in ctor
    int                unknown_108;       // +0x108
    int                unknown_10C;       // +0x10C
    unsigned char      unknown_110;       // +0x110
    unsigned char      unknown_111[3];    // +0x111..+0x113
    AudioController    unknown_114;       // +0x114 (0x14)
    AudioController    unknown_128;       // +0x128 (0x14)
    unsigned char      unknown_13C;       // +0x13C
    unsigned char      unknown_13D[3];    // +0x13D..+0x13F
    int                unknown_140;       // +0x140
    int                unknown_144;       // +0x144
};

GG_STATIC_ASSERT(sizeof(void*) == 0x04);
GG_STATIC_ASSERT(sizeof(int) == 0x04);
GG_STATIC_ASSERT(sizeof(AudioController) == 0x14);
GG_STATIC_ASSERT(sizeof(ObjectClass) == 0xAC);
GG_STATIC_ASSERT(sizeof(BounceClass) == 0x50);
GG_STATIC_ASSERT(offsetof(VoxelAnimClass, Location) == 0x9C);
GG_STATIC_ASSERT(offsetof(VoxelAnimClass, Coords) == 0xC8);
GG_STATIC_ASSERT(offsetof(VoxelAnimClass, unknown_100) == 0x100);
GG_STATIC_ASSERT(offsetof(VoxelAnimClass, unknown_100) - sizeof(BounceClass) == 0xB0);
GG_STATIC_ASSERT(offsetof(VoxelAnimClass, unknown_104) == 0x104);
GG_STATIC_ASSERT(offsetof(VoxelAnimClass, unknown_108) == 0x108);
GG_STATIC_ASSERT(offsetof(VoxelAnimClass, unknown_10C) == 0x10C);
GG_STATIC_ASSERT(offsetof(VoxelAnimClass, unknown_110) == 0x110);
GG_STATIC_ASSERT(sizeof(((VoxelAnimClass*)0)->unknown_110) == 0x01);
GG_STATIC_ASSERT(offsetof(VoxelAnimClass, unknown_111) == 0x111);
GG_STATIC_ASSERT(sizeof(((VoxelAnimClass*)0)->unknown_111) == 0x03);
GG_STATIC_ASSERT(offsetof(VoxelAnimClass, unknown_114) == 0x114);
GG_STATIC_ASSERT(offsetof(VoxelAnimClass, unknown_128) == 0x128);
GG_STATIC_ASSERT(offsetof(VoxelAnimClass, unknown_13C) == 0x13C);
GG_STATIC_ASSERT(sizeof(((VoxelAnimClass*)0)->unknown_13C) == 0x01);
GG_STATIC_ASSERT(offsetof(VoxelAnimClass, unknown_13D) == 0x13D);
GG_STATIC_ASSERT(sizeof(((VoxelAnimClass*)0)->unknown_13D) == 0x03);
GG_STATIC_ASSERT(offsetof(VoxelAnimClass, unknown_140) == 0x140);
GG_STATIC_ASSERT(offsetof(VoxelAnimClass, unknown_144) == 0x144);
GG_STATIC_ASSERT(sizeof(VoxelAnimClass) == 0x148);

#endif  // GG_MATCH_LAYOUT_VOXEL_ANIM_CLASS_H
