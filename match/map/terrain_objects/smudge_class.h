// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check (names only)
//   Layout, tables and vptr offsets read from the retail gamemd.exe v1.001: RTTI .?AVSmudgeClass@@
//   (terrain_common_views.h), the constructor 0x6B4A50 (every member store below), the scalar deleting
//   destructor 0x6B4FA0, and the allocation sites 0x6B4D51, 0x6B5556 and 0x6B55C3
//   (`PUSH 0xB0; CALL 0x7C8E17`, three sites, all agreeing).
//
// SmudgeClass: one smudge (scorch mark, crater, bib) on the map. Derives the ObjectClass-shaped
// partial view of terrain_common_views.h.
//
//   +0x00..+0xAB  MapObjClassView (terrain_common_views.h)
//   +0xAC  Type  (SmudgeTypeClass*)  ctor argument 1; swizzled by Load
//   sizeof 0xB0 (from the allocation)
#ifndef GG_MATCH_MAP_TERRAIN_OBJECTS_SMUDGE_CLASS_H
#define GG_MATCH_MAP_TERRAIN_OBJECTS_SMUDGE_CLASS_H

#include "terrain_common_types.h"
#include "terrain_common_vectors.h"
#include "terrain_common_views.h"
#include "../../_layout/object_class.h"
#include "../../_layout/geometry2d.h"

// GLOBAL: GAMEMD 0xA8B1E0 - SmudgeClass::Array, every live smudge (vptr 0x7E9DA4).
extern DynamicVectorClass<SmudgeClass*> SmudgeArray;

// GLOBAL: GAMEMD 0xB0B728 - the all-zero coordinate the constructor compares its coordinate with.
extern MapObjCoord SmudgeEmptyCoord;

// GLOBAL: GAMEMD 0x83FFD8 - an int the constructor sets to its third argument around the placement
// and resets to -1 (initialised to -1 in .data; no reader was found by Ghidra's x-ref).
extern int SmudgeCreateArg;

// VTABLE: GAMEMD 0x7F32FC (IPersistStream side) and GAMEMD 0x7F32D8 / 0x7F32F4 / 0x7F32D0
class SmudgeClass : public ObjectClass
{
public:
    // FUNCTION: GAMEMD 0x6B4A50
    SmudgeClass(SmudgeTypeClass* type, const MapObjCoord& coord, int arg3);
    // No-init constructor: Load re-runs it through placement new to restore
    // the vptrs without touching members.
    SmudgeClass(const AbstractNoInit& noInit) : ObjectClass(noInit) {}

    // ---- primary table (IPersistStream side) overrides ---------------------------------------
    virtual HRESULT __stdcall GetClassID(CLSID* pClassID);                  // 3   0x6B4F50
    virtual HRESULT __stdcall Load(IStream* pStm);                          // 5   0x6B4EA0
    virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty);        // 6   0x6B4F00
    // Slot 8: the scalar deleting destructor 0x6B4FA0 is compiler output; the destructor body is
    // inline (it is expanded into that entry, and the base body 0x5F3B80 is out of line).
    // FUNCTION: GAMEMD 0x6B4B40 (body in tu216_smudge_class.cpp)
    virtual ~SmudgeClass();
    virtual int vf_11();                                                    // 11  0x6B4F40
    virtual int vf_12();                                                    // 12  0x6B4F30
    virtual ObjectTypeClass* vf_34();                                       // 34  0x6B4F20
    virtual void vf_69(Point2D* where, RectangleStruct* clip);              // 69  0x6B4F90
    virtual bool vf_73(int arg);                                            // 73  0x6B4BE0

    // ---- members (complete-object offsets) ---------------------------------------------------
    SmudgeTypeClass* Type;   // +0xAC
};

GG_STATIC_ASSERT(offsetof(SmudgeClass, Type) == 0xAC);
// sizeof is from the allocation: `PUSH 0xB0; CALL 0x7C8E17` at 0x6B4D51, 0x6B5556, 0x6B55C3.
GG_STATIC_ASSERT(sizeof(SmudgeClass) == 0xB0);

#endif  // GG_MATCH_MAP_TERRAIN_OBJECTS_SMUDGE_CLASS_H
