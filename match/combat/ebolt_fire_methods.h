// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x4C2A60: seven stacked dwords (`RET 0x1C`) stored as two
//   three-dword coordinates at this+0x00 (`MOV EAX,ESI`) and this+0x0C
//   (`LEA EDX,[ESI+0xC]`) plus the int at [ESI+0x18]; the Randomizer at
//   0x886B88 (`MOV ECX,0x886B88; CALL 0x65C7E0` with 0 and 0x100) stored at
//   [ESI+0x1C]; the global vector at 0x8A0E88 read as `[0x8A0E90]` capacity,
//   `[0x8A0E95]` byte allocated flag, `[0x8A0E98]` count, `[0x8A0E9C]`
//   increment, `[0x8A0E8C]` items, with Resize through `MOV EDX,[0x8A0E88];
//   CALL [EDX+8]` (the inlined AddItem); `PUSH 0x100; CALL 0x7C8E17`
//   (operator new) null-tested, then the 6-argument __thiscall 0x62DC50 on
//   the block with `[[0x8871E0]+0x1020]`, the address of the second
//   coordinate, 0, 0, 0x8A0E50 and 0. Names cross-checked against YRpp
//   EBolt.h / RulesClass.h (consult-only; every offset reconfirmed above).
#ifndef GG_MATCH_COMBAT_EBOLT_FIRE_METHODS_H
#define GG_MATCH_COMBAT_EBOLT_FIRE_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"
#include "../core/randomizer.h"

struct CoordStruct_004C2A60
{
    int X;   // +0x0
    int Y;   // +0x4
    int Z;   // +0x8
};
GG_STATIC_ASSERT(sizeof(CoordStruct_004C2A60) == 0xC);

// RulesClass — only the type pointer at +0x1020 is read.
struct Rules_004C2A60
{
    char  _pad0000[0x1020];   // +0x0000
    void* At_1020;            // +0x1020
};
GG_STATIC_ASSERT(offsetof(Rules_004C2A60, At_1020) == 0x1020);
// GLOBAL: GAMEMD 0x8871E0 — RulesClass::Instance.
extern Rules_004C2A60* DAT_008871E0;

// GLOBAL: GAMEMD 0x8A0E50 — the object whose address is the fifth argument
// of 0x62DC50.
extern char DAT_008A0E50;

// The 0x100-byte object built by 0x62DC50 (a particle system).
struct ParticleSystem_004C2A60
{
    char opaque[0x100];

    // FUNCTION: GAMEMD 0x62DC50 (decl; reloc) — the constructor, six stack
    // arguments; called explicitly on the raw block so no EH frame is
    // registered.
    ParticleSystem_004C2A60* Construct(void* type, CoordStruct_004C2A60* coord,
                                       int a, int b, void* p, int c);
};
GG_STATIC_ASSERT(sizeof(ParticleSystem_004C2A60) == 0x100);

struct EBolt;

// DynamicVectorClass<EBolt*> — the live-bolt list at 0x8A0E88.
struct EBoltVector
{
    virtual void vt_000();
    virtual void vt_004();
    virtual bool Resize(int newCapacity, void* array);   // +0x0008

    EBolt** Items;             // +0x0004
    int   Capacity;            // +0x0008
    char  _pad0C[0x1];
    char  IsAllocated;         // +0x000D
    char  _pad0E[0x10 - 0x0E];
    int   Count;               // +0x0010
    int   CapacityIncrement;   // +0x0014

    // DynamicVectorClass::AddItem, expanded inline by VC6 at the call site.
    // Same phrasing as match/map/cell_class_tag_methods.h (0x485250).
    bool AddItem(EBolt* item)
    {
        int cap = Capacity;
        if (Count < cap
            || ((IsAllocated || cap == 0)
                && CapacityIncrement > 0
                && Resize(cap + CapacityIncrement, 0))) {
            int index = Count++;
            Items[index] = item;
            return true;
        }
        return false;
    }
};
GG_STATIC_ASSERT(offsetof(EBoltVector, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(EBoltVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(EBoltVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(EBoltVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(EBoltVector, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(EBoltVector) == 0x18);

// GLOBAL: GAMEMD 0x8A0E88 — EBolt::Array (an object: retail loads its address
// as the immediate `MOV ECX,0x8A0E88`).
extern EBoltVector DAT_008A0E88;

// EBolt — only the leading 0x20 bytes are written here.
struct EBolt
{
    CoordStruct_004C2A60 Point1;   // +0x0000
    CoordStruct_004C2A60 Point2;   // +0x000C
    int                  At_18;    // +0x0018
    int                  At_1C;    // +0x001C  random 0..0x100

    // FUNCTION: GAMEMD 0x4C2A60
    void Fire(CoordStruct_004C2A60 from, CoordStruct_004C2A60 to, int color);
};
GG_STATIC_ASSERT(offsetof(EBolt, Point2) == 0x0C);
GG_STATIC_ASSERT(offsetof(EBolt, At_18) == 0x18);
GG_STATIC_ASSERT(offsetof(EBolt, At_1C) == 0x1C);

#endif  // GG_MATCH_COMBAT_EBOLT_FIRE_METHODS_H
