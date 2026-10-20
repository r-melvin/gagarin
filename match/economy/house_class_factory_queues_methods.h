// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets read numerically off the user's retail gamemd.exe v1.001 via the
//   local Ghidra CLI at 0x509140. On the house (EBP): the five factory slots
//   `MOV ESI,[EBP+0x53AC]` (aircraft), `[EBP+0x53B0]` (infantry),
//   `[EBP+0x53B4]` / `[EBP+0x53B8]` (ground and naval units, selected by the
//   second parameter) and `[EBP+0x53BC]` / `[EBP+0x53CC]` (buildings,
//   selected by the third parameter being 5). On the factory (ESI):
//   `MOV EDX,[ESI+0x44]` / `MOV EAX,[ESI+0x50]` (the queue's Items and Count),
//   `MOV ECX,[ESI+0x58]` (the object in production), `MOV AL,[ESI+0x70]` and
//   `MOV AL,[ESI+0x71]`, and the vtable slot `CALL [EAX+0x20]`. The queued
//   items and the produced object's type are asked through slot 0x94 with
//   four pushed arguments (1, 0/1, 1, house); the object itself through slot
//   0x84 (GetTechnoType). The player singleton is the dword global 0xA83D4C
//   compared straight against the house. Conventions off the call sites:
//   0x4C9FF0 and 0x4CA5A0 take only ECX, 0x4C9E60 and 0x4C9EA0 one pushed
//   argument (__thiscall); 0x6ABCD0 sets ECX and EDX with one push
//   (__fastcall); 0x6A60A0 is `MOV ECX,0x87F7E8` plus one push. The switch is
//   a jump table: `ADD EAX,-3; CMP EAX,0x25; JA default;
//   MOV CL,[EAX+0x5092C0]; JMP [ECX*4+0x5092AC]`, with the dword table
//   0x5092AC = {0x50919B, 0x509168, 0x509193, 0x50917F, 0x5092A3} and the
//   0x26-byte index table selecting RTTI 3, 7, 0x10 and 0x28 — the block
//   bodies are laid out in the source order 7, 0x28, 0x10, 3. The FactoryClass
//   offsets agree with match/economy/factory_class_methods.h (Items @0x44,
//   Count @0x50, Object @0x58, IsSuspended @0x70, IsManual @0x71). Names
//   cross-checked against YRpp HouseClass / FactoryClass (consult-only, NO
//   LICENSE) and re-derived here from the disassembly.
#ifndef GG_MATCH_ECONOMY_HOUSE_CLASS_FACTORY_QUEUES_METHODS_H
#define GG_MATCH_ECONOMY_HOUSE_CLASS_FACTORY_QUEUES_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../_rt/gg_vslot.h"

struct House_00509140;

struct TypeVtbl_00509140;

struct TechnoType_00509140
{
    TypeVtbl_00509140* Vtbl;   // +0x0000
};

typedef int (TechnoType_00509140::*Fn94_00509140)(int a1, int a2, int a3,
                                                  House_00509140* house);

struct TypeVtbl_00509140
{
    char           _pad000[0x94];   // +0x0000
    Fn94_00509140  At_94;           // +0x0094  "can this house build it now?"
};
GG_STATIC_ASSERT(offsetof(TypeVtbl_00509140, At_94) == 0x94);

struct ObjVtbl_00509140;

struct Techno_00509140
{
    ObjVtbl_00509140* Vtbl;   // +0x0000
};

typedef TechnoType_00509140* (Techno_00509140::*Fn84_00509140)();

struct ObjVtbl_00509140
{
    char           _pad000[0x84];   // +0x0000
    Fn84_00509140  GetTechnoType;   // +0x0084
};
GG_STATIC_ASSERT(offsetof(ObjVtbl_00509140, GetTechnoType) == 0x84);

// DynamicVectorClass<TechnoTypeClass*> head, as in
// match/economy/factory_class_methods.h.
struct DynVec_00509140
{
    void*                 vtable;             // +0x00
    TechnoType_00509140** Items;              // +0x04
    int                   Capacity;           // +0x08
    int                   IsAllocated;        // +0x0C
    int                   Count;              // +0x10
    int                   CapacityIncrement;  // +0x14
};

struct FactoryVtbl_00509140;

struct Factory_00509140
{
    FactoryVtbl_00509140* Vtbl;                    // +0x0000
    char                  _pad004[0x40 - 0x4];     // +0x0004
    DynVec_00509140       QueuedObjects;           // +0x0040
    Techno_00509140*      Object;                  // +0x0058
    char                  _pad005C[0x70 - 0x5C];   // +0x005C
    bool                  IsSuspended;             // +0x0070
    bool                  IsManual;                // +0x0071
    char                  _pad0072[2];             // +0x0072

    // FUNCTION: GAMEMD 0x4C9E60 (decl; reloc) — suspend production.
    void FUN_004C9E60(int a1);
    // FUNCTION: GAMEMD 0x4C9EA0 (decl; reloc) — resume production.
    void FUN_004C9EA0(int a1);
    // FUNCTION: GAMEMD 0x4C9FF0 (decl; reloc) — FactoryClass::AbandonProduction.
    void FUN_004C9FF0();
    // FUNCTION: GAMEMD 0x4CA5A0 (decl; reloc) — drop the queue.
    void FUN_004CA5A0();
};
GG_STATIC_ASSERT(offsetof(Factory_00509140, QueuedObjects.Items) == 0x44);
GG_STATIC_ASSERT(offsetof(Factory_00509140, QueuedObjects.Count) == 0x50);
GG_STATIC_ASSERT(offsetof(Factory_00509140, Object)              == 0x58);
GG_STATIC_ASSERT(offsetof(Factory_00509140, IsSuspended)         == 0x70);
GG_STATIC_ASSERT(offsetof(Factory_00509140, IsManual)            == 0x71);
GG_STATIC_ASSERT(sizeof(Factory_00509140) == 0x74);

typedef int (Factory_00509140::*Fn20_00509140)(int a1);

struct FactoryVtbl_00509140
{
    char           _pad000[0x20];   // +0x0000
    Fn20_00509140  At_20;           // +0x0020
};
GG_STATIC_ASSERT(offsetof(FactoryVtbl_00509140, At_20) == 0x20);

// FUNCTION: GAMEMD 0x6ABCD0 (decl; reloc) — map the (rtti, build category,
// naval) triple to a sidebar tab. __fastcall: rtti in ECX, category in EDX.
unsigned int __fastcall FUN_006ABCD0(int rtti, int buildCat, bool isNaval);

struct Map_00509140
{
    char opaque[4];
    // FUNCTION: GAMEMD 0x6A60A0 (decl; reloc) — repaint that sidebar tab.
    void FUN_006A60A0(unsigned int tab);
};
// GLOBAL: GAMEMD 0x87F7E8 — MapClass::Instance (an object, not a pointer);
// the same singleton reached by `MOV ECX,0x87F7E8` throughout match/map.
extern Map_00509140 DAT_0087F7E8;

struct House_00509140
{
    char              _pad0000[0x53AC];        // +0x0000
    Factory_00509140* At_53AC;                 // +0x53AC  aircraft
    Factory_00509140* At_53B0;                 // +0x53B0  infantry
    Factory_00509140* At_53B4;                 // +0x53B4  ground units
    Factory_00509140* At_53B8;                 // +0x53B8  naval units
    Factory_00509140* At_53BC;                 // +0x53BC  buildings
    char              _pad53C0[0x53CC - 0x53C0]; // +0x53C0
    Factory_00509140* At_53CC;                 // +0x53CC  defences

    // FUNCTION: GAMEMD 0x509140 — HouseClass::Update_FactoriesQueues.
    void UpdateFactoriesQueues(int rtti, bool isNaval, int buildCat);
};
GG_STATIC_ASSERT(offsetof(House_00509140, At_53AC) == 0x53AC);
GG_STATIC_ASSERT(offsetof(House_00509140, At_53B0) == 0x53B0);
GG_STATIC_ASSERT(offsetof(House_00509140, At_53B4) == 0x53B4);
GG_STATIC_ASSERT(offsetof(House_00509140, At_53B8) == 0x53B8);
GG_STATIC_ASSERT(offsetof(House_00509140, At_53BC) == 0x53BC);
GG_STATIC_ASSERT(offsetof(House_00509140, At_53CC) == 0x53CC);

// GLOBAL: GAMEMD 0xA83D4C — HouseClass::CurrentPlayer.
extern House_00509140* DAT_00A83D4C;

#endif  // GG_MATCH_ECONOMY_HOUSE_CLASS_FACTORY_QUEUES_METHODS_H
