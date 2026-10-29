// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, globals and vtable slots read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI: `[EAX+0xFF4]` off the rules
//   instance at 0x74EF05; the registry Items/Count words at 0xB1D294/0xB1D2A0
//   (0x74CDF0, 0x74EA30); the per-monster `[ECX+0x100]` byte and `[ECX+0xB0]`
//   pointer at 0x74EA45/0x74EA4F; the `CALL [EDX+0x5C]` slot at 0x74CE08 and
//   the `PUSH 1; CALL [EAX+0x20]` deleting-destructor slot at 0x74EA62; the
//   three stack words forwarded at 0x74EEE0. YRpp was
//   consulted for the method names only (nothing copied).
//
// VeinholeMonsterClass — the vein-spawning monster.
// This TU covers its per-frame driver and three small statics; the class is a
// placeholder shape (vtable index + the two members the sweep tests), not the
// full 0x108-byte layout.
#ifndef GG_MATCH_MAP_VEINHOLE_MONSTER_METHODS_H
#define GG_MATCH_MAP_VEINHOLE_MONSTER_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// The rules instance, read only for the veinhole terrain type at +0xFF4.
// ---------------------------------------------------------------------------
struct Rules_0074EF00
{
    char  _pad000[0xFF4];       // +0x0000
    void* VeinholeTerrainType;  // +0x0FF4  (TerrainTypeClass*)
};
GG_STATIC_ASSERT(offsetof(Rules_0074EF00, VeinholeTerrainType) == 0xFF4);

// GLOBAL: GAMEMD 0x8871E0 — RulesClass::Instance.
extern Rules_0074EF00* RulesInstance;

// ---------------------------------------------------------------------------
// The global vein-monster registry @0xB1D290, a DynamicVectorClass of
// VeinholeMonsterClass*. Only Items @+0x04 (0xB1D294) and Count @+0x10
// (0xB1D2A0) are touched here.
// ---------------------------------------------------------------------------
class VeinholeMonsterView_0074CDF0;

struct VeinholeArray_0074CDF0
{
    void*                   _vtable;   // +0x00
    VeinholeMonsterView_0074CDF0**  Items;     // +0x04
    int                     Capacity;  // +0x08
    char                    _pad00C[4];
    int                     Count;     // +0x10
    int                     CapacityIncrement;
};
GG_STATIC_ASSERT(offsetof(VeinholeArray_0074CDF0, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(VeinholeArray_0074CDF0, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(VeinholeArray_0074CDF0)          == 0x18);

// GLOBAL: GAMEMD 0xB1D290 — VeinholeMonsterClass::Array.
extern VeinholeArray_0074CDF0 VeinholeArray;

// The growth queue hanging off each monster at +0xB0. The sweep only asks
// whether its first word (the pending-node count) is zero.
struct Queue_0074CDF0
{
    int Count;   // +0x0000
};
GG_STATIC_ASSERT(offsetof(Queue_0074CDF0, Count) == 0x00);

// ---------------------------------------------------------------------------
// VeinholeMonsterClass : ObjectClass (COM-rooted). The vtable indices that
// matter are reproduced with dummy virtuals: Save @+0x18 (index 6), the
// deleting destructor @+0x20 (index 8) and Update @+0x5C (index 23). No
// constructor is defined here, so no vtable is emitted.
// ---------------------------------------------------------------------------
class VeinholeMonsterView_0074CDF0
{
public:
    virtual long vf_00();   // +0x00  IUnknown
    virtual long vf_04();   // +0x04
    virtual long vf_08();   // +0x08
    virtual long vf_0C();   // +0x0C  GetClassID
    virtual long vf_10();   // +0x10  Load
    virtual long vf_14();   // +0x14
    // FUNCTION: GAMEMD 0x74EEE0 — IPersistStream::Save, __stdcall.
    virtual long __stdcall Save(void* pStm, int fClearDirty);   // +0x18
    virtual long vf_1C();   // +0x1C  GetSizeMax
    virtual ~VeinholeMonsterView_0074CDF0();   // +0x20  deleting destructor
    virtual long vf_24();
    virtual long vf_28();
    virtual long vf_2C();
    virtual long vf_30();
    virtual long vf_34();
    virtual long vf_38();
    virtual long vf_3C();
    virtual long vf_40();
    virtual long vf_44();
    virtual long vf_48();
    virtual long vf_4C();
    virtual long vf_50();
    virtual long vf_54();
    virtual long vf_58();
    virtual void Update();   // +0x5C  AbstractClass::Update

    char             _pad004[0xB0 - 0x04];   // +0x0004  (ObjectClass body + GrowthLogic.NextFreeNodeIndex)
    Queue_0074CDF0*  unknown_B0;            // +0x00B0
    char             _padB4[0x100 - 0xB4];   // +0x00B4
    char             IsDead;                 // +0x0100

    // FUNCTION: GAMEMD 0x74CDF0
    static void UpdateAllVeinholes();

    // FUNCTION: GAMEMD 0x74EA30
    static void DestroyAll();

    // FUNCTION: GAMEMD 0x74EF00
    static void* GetTerrainType();
};
GG_STATIC_ASSERT(offsetof(VeinholeMonsterView_0074CDF0, unknown_B0) == 0xB0);
GG_STATIC_ASSERT(offsetof(VeinholeMonsterView_0074CDF0, IsDead)      == 0x100);

// FUNCTION: GAMEMD 0x410320 (decl; reloc) — the shared object save, __stdcall
// with the receiver pushed first.
long __stdcall FUN_00410320(VeinholeMonsterView_0074CDF0* subject, void* pStm, int fClearDirty);

#endif  // GG_MATCH_MAP_VEINHOLE_MONSTER_METHODS_H
