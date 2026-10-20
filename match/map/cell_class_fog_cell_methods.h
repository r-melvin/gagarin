// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x486A70:
//     * `MOV EAX,[0xA8B230]; MOV EDX,[EAX]; TEST DH,0x10` — ScenarioClass
//       instance pointer, its leading flag dword, bit 0x1000.
//     * `MOV ECX,[ECX+0x24]` — CellClass::MapCoords (packed CellStruct),
//       copied to the stack and stepped (+1,+1) each iteration; `MOVSX
//       EAX,byte ptr [EBP+0x11B]` Level; `[EBP+0x140]` Flags with bit
//       0x400000; `[EBP+0x28]` the fogged-object vector; `[EBP+0xE4]` the
//       cell's first occupier.
//     * the allocated object is `operator new(0x18)` with `[p+4]=0`,
//       `[p+8]=0`, `byte [p+0xC]=1`, `byte [p+0xD]=0`, `[p]=0x7E44F4`,
//       `[p+0x14]=10`, `[p+0x10]=0` — a DynamicVectorClass whose vptr sits at
//       +0 ahead of the VectorClass base at +4, i.e. the derived class is the
//       one that introduces the virtuals. Slot +0x08 is then called with
//       (1, 0) and `[p+0x14]` set to 1; slot +0x00 is the scalar deleting
//       destructor (`PUSH 1`).
//     * the occupier walk: `MOV ESI,[ESI+0x30]` next pointer; `MOV ECX,[ESI+4];
//       LEA EAX,[ESI+4]; PUSH EAX; CALL [ECX+0xC]` — the COM RTTI interface
//       at +4, slot 3, `this` pushed (__stdcall); object slots `[vt+0x80]`
//       (bool), `[vt+0x150]` (void) and `[vt+0x1B8]` (CellStruct by hidden
//       pointer, already confirmed in match/combat/building_class_fog_methods.h);
//       `MOV AL,byte ptr [ESI+0x6ED]` compared with 0xF.
//   0x5657A0 MapClass::GetCellAt, 0x457A10 BuildingClass::CheckFog and
//   0x457AA0 are declared only. Names cross-checked against YRpp CellClass.h /
//   BuildingClass.h (consult-only, NO LICENSE).
#ifndef GG_MATCH_MAP_CELL_CLASS_FOG_CELL_METHODS_H
#define GG_MATCH_MAP_CELL_CLASS_FOG_CELL_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct CellStruct { short X; short Y; };
GG_STATIC_ASSERT(sizeof(CellStruct) == 4);

struct Scenario_00486A70
{
    int Flags;   // +0x0000  bit 0x1000 gates the whole routine
};

// GLOBAL: GAMEMD 0xA8B230 — ScenarioClass::Instance (a pointer).
extern Scenario_00486A70* DAT_00A8B230;

// ---------------------------------------------------------------------------
// The per-cell fogged-object vector. Its vptr is at +0x00 and the
// VectorClass base members follow at +0x04, so the vptr is modelled as a
// plain member (the campaign_class.cpp idiom) and the base as an embedded
// struct whose constructor runs first.
// ---------------------------------------------------------------------------
struct FogVecVtbl_00486A70;

struct FogVecBase_00486A70
{
    void** Items;           // +0x04 (within the vector)
    int    Capacity;        // +0x08
    char   IsInitialized;   // +0x0C
    char   IsAllocated;     // +0x0D

    FogVecBase_00486A70()
    {
        Items         = 0;
        Capacity      = 0;
        IsInitialized = 1;
        IsAllocated   = 0;
    }
};

struct FogVec_00486A70
{
    FogVecVtbl_00486A70* Vptr;            // +0x00
    FogVecBase_00486A70  Base;            // +0x04
    int                  Count;           // +0x10
    int                  GrowthStep;      // +0x14

    // The constructor body, expanded by hand: under /GX a real `new T` wraps
    // the allocation in an exception frame with an unwind funclet that retail
    // does not have (the banked rule, see match/core/campaign_class.cpp).
    __forceinline FogVec_00486A70* Construct()
    {
        this->Base.Items         = 0;
        this->Base.Capacity      = 0;
        this->Base.IsInitialized = 1;
        this->Base.IsAllocated   = 0;
        this->Vptr       = (FogVecVtbl_00486A70*)0x7E44F4;
        this->GrowthStep = 10;
        this->Count      = 0;
        return this;
    }
};
GG_STATIC_ASSERT(offsetof(FogVec_00486A70, Base)       == 0x04);
GG_STATIC_ASSERT(offsetof(FogVec_00486A70, Count)      == 0x10);
GG_STATIC_ASSERT(offsetof(FogVec_00486A70, GrowthStep) == 0x14);
GG_STATIC_ASSERT(sizeof(FogVec_00486A70)               == 0x18);

typedef void (FogVec_00486A70::*Fn00_00486A70)(int freeFlag);
typedef bool (FogVec_00486A70::*Fn08_00486A70)(int capacity, void* array);

struct FogVecVtbl_00486A70
{
    Fn00_00486A70 At_00;            // +0x00  scalar deleting destructor
    char          _pad004[0x8 - 0x4];
    Fn08_00486A70 At_08;            // +0x08  Resize
};
GG_STATIC_ASSERT(offsetof(FogVecVtbl_00486A70, At_08) == 0x8);

// ---------------------------------------------------------------------------
// A cell occupier (a BuildingClass in the RTTI == 6 arm).
// ---------------------------------------------------------------------------
struct RTTIVtbl_00486A70;

struct RTTIFace_00486A70
{
    RTTIVtbl_00486A70* Vptr;   // +0x00 of the interface (= object +0x04)
};

typedef int (__stdcall *FnWhatAmI_00486A70)(RTTIFace_00486A70* self);

struct RTTIVtbl_00486A70
{
    char               _pad000[0xC];   // +0x00
    FnWhatAmI_00486A70 WhatAmI;        // +0x0C
};
GG_STATIC_ASSERT(offsetof(RTTIVtbl_00486A70, WhatAmI) == 0xC);

struct ObjVtbl_00486A70;
struct CellClass;

struct Obj_00486A70
{
    ObjVtbl_00486A70* Vptr;                    // +0x0000
    RTTIFace_00486A70 RTTI;                    // +0x0004
    char              _pad0008[0x30 - 0x08];   // +0x0008
    Obj_00486A70*     NextObject;              // +0x0030
    char              _pad0034[0x6ED - 0x34];  // +0x0034
    char              Unknown_6ED;             // +0x06ED

    // FUNCTION: GAMEMD 0x457A10 (decl; reloc) — BuildingClass::CheckFog.
    bool CheckFog();
    // FUNCTION: GAMEMD 0x457AA0 (decl; reloc) — append this occupier's fogged
    // record to the vector.
    void FUN_00457AA0(FogVec_00486A70* fogged, CellClass* cell, bool flag);
};
GG_STATIC_ASSERT(offsetof(Obj_00486A70, RTTI)        == 0x0004);
GG_STATIC_ASSERT(offsetof(Obj_00486A70, NextObject)  == 0x0030);
GG_STATIC_ASSERT(offsetof(Obj_00486A70, Unknown_6ED) == 0x06ED);

typedef bool        (Obj_00486A70::*Fn80_00486A70)();
typedef void        (Obj_00486A70::*Fn150_00486A70)();
typedef CellStruct* (Obj_00486A70::*Fn1B8_00486A70)(CellStruct* out);

struct ObjVtbl_00486A70
{
    char           _pad000[0x80];              // +0x0000
    Fn80_00486A70  At_80;                      // +0x0080
    char           _pad084[0x150 - 0x84];      // +0x0084
    Fn150_00486A70 At_150;                     // +0x0150
    char           _pad154[0x1B8 - 0x154];     // +0x0154
    Fn1B8_00486A70 GetMapCoords;               // +0x01B8
};
GG_STATIC_ASSERT(offsetof(ObjVtbl_00486A70, At_80)        == 0x80);
GG_STATIC_ASSERT(offsetof(ObjVtbl_00486A70, At_150)       == 0x150);
GG_STATIC_ASSERT(offsetof(ObjVtbl_00486A70, GetMapCoords) == 0x1B8);

// ---------------------------------------------------------------------------
struct CellClass
{
    char              _pad000[0x24];            // +0x0000
    CellStruct        MapCoords;                // +0x0024
    FogVec_00486A70*  FoggedObjects;            // +0x0028
    char              _pad02C[0xE4 - 0x2C];     // +0x002C
    Obj_00486A70*     FirstObject;              // +0x00E4
    char              _pad0E8[0x11B - 0xE8];    // +0x00E8
    signed char       Level;                    // +0x011B
    char              _pad11C[0x140 - 0x11C];   // +0x011C
    int               Flags;                    // +0x0140

    // FUNCTION: GAMEMD 0x486A70 — CellClass::FogCell.
    void FogCell();
};
GG_STATIC_ASSERT(offsetof(CellClass, MapCoords)     == 0x24);
GG_STATIC_ASSERT(offsetof(CellClass, FoggedObjects) == 0x28);
GG_STATIC_ASSERT(offsetof(CellClass, FirstObject)   == 0xE4);
GG_STATIC_ASSERT(offsetof(CellClass, Level)         == 0x11B);
GG_STATIC_ASSERT(offsetof(CellClass, Flags)         == 0x140);

struct MapClass_00486A70
{
    // FUNCTION: GAMEMD 0x5657A0 (decl; reloc) — MapClass::GetCellAt.
    CellClass* GetCellAt(CellStruct const& cell);
};

// LIBRARY: GAMEMD 0x7C8E17 — operator new (excluded from the match target).
void* __cdecl FogOperatorNew(unsigned int size);

#endif  // GG_MATCH_MAP_CELL_CLASS_FOG_CELL_METHODS_H
