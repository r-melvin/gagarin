// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x54E7B0: the stream's `CALL [EAX+0xC]` (IStream::Read,
//   __stdcall with stream, buffer, size, null) first into a 4-byte count and
//   then into each 8-byte node from `PUSH 8; CALL 0x7C8E17` (operator new);
//   the swizzle helper 0x6CF240 called with `PUSH EDI` / `PUSH 0xB0C110`
//   for the node's +0 and +4 pointers; the node vector `LEA ESI,[ECX+0xC]`
//   with Capacity `[ECX+0x14]`, Count `[ECX+0x1C]`, IsAllocated
//   `MOV CL,[ESI+0xD]`, CapacityIncrement `[ESI+0x14]`, Items `[ESI+0x4]`
//   and Resize `CALL [EDX+0x8]` (the inlined AddItem); the loop counter in
//   the parameter's home slot [ESP+0x1C]; `RET 4`. Same Kamikaze / vector /
//   swizzle model as match/combat/kamikaze_update_methods.h and
//   match/movement/locomotion_class_load_methods.h. Method name from YRpp
//   Kamikaze.h (consult-only; name only).
#ifndef GG_MATCH_COMBAT_KAMIKAZE_LOAD_METHODS_H
#define GG_MATCH_COMBAT_KAMIKAZE_LOAD_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The COM stream: only slot +0x0C (Read) is called, __stdcall.
struct IStream_0054E7B0
{
    virtual long          __stdcall QueryInterface(const void* riid, void** ppv) = 0; // +0x00
    virtual unsigned long __stdcall AddRef() = 0;                                     // +0x04
    virtual unsigned long __stdcall Release() = 0;                                    // +0x08
    virtual long          __stdcall Read(void* pv, unsigned long cb,
                                         unsigned long* pcbRead) = 0;                 // +0x0C
};

// The swizzle manager at 0xB0C110; __stdcall with the manager as the first
// stacked argument.
struct Swizzle_0054E7B0
{
    // FUNCTION: GAMEMD 0x6CF240 (decl; reloc) — queue a pointer for fix-up.
    long __stdcall FUN_006CF240(void** pointer);
};
// GLOBAL: GAMEMD 0xB0C110 — SwizzleManagerClass::Instance.
extern Swizzle_0054E7B0 DAT_00B0C110;

// Per-aircraft node: Item at +0, Target at +4 — both swizzled after the read.
struct KamikazeControl_0054E7B0
{
    void* Item;      // +0x00
    void* Target;    // +0x04
};
GG_STATIC_ASSERT(offsetof(KamikazeControl_0054E7B0, Target) == 0x04);
GG_STATIC_ASSERT(sizeof(KamikazeControl_0054E7B0) == 0x08);

// DynamicVectorClass<KamikazeControl*>: slot +0x08 is Resize(newCapacity,
// array), the allocation flag is the byte at +0x0D.
struct NodeVector_0054E7B0
{
    virtual void vt_000();
    virtual void vt_004();
    virtual bool Resize(int newCapacity, void* array);   // +0x0008

    KamikazeControl_0054E7B0** Items;   // +0x0004
    int   Capacity;                     // +0x0008
    char  _pad0C[0x1];
    char  IsAllocated;                  // +0x000D
    char  _pad0E[0x10 - 0x0E];
    int   Count;                        // +0x0010
    int   CapacityIncrement;            // +0x0014

    // DynamicVectorClass::AddItem, expanded inline by VC6 at the call site.
    // Same phrasing as match/map/cell_class_tag_methods.h (0x485250).
    bool AddItem(KamikazeControl_0054E7B0* item)
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
GG_STATIC_ASSERT(offsetof(NodeVector_0054E7B0, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(NodeVector_0054E7B0, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(NodeVector_0054E7B0, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(NodeVector_0054E7B0, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(NodeVector_0054E7B0, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(NodeVector_0054E7B0) == 0x18);

// Kamikaze — the suicide-run manager: the 12-byte UpdateTimer, then the node
// vector at +0x0C (Capacity @0x14, Count @0x1C).
struct Kamikaze
{
    char                 UpdateTimer[0x0C];   // +0x0000  CDTimerClass, untouched here
    NodeVector_0054E7B0  Nodes;               // +0x000C

    // FUNCTION: GAMEMD 0x54E7B0
    long Load(IStream_0054E7B0* stream);
};
GG_STATIC_ASSERT(offsetof(Kamikaze, Nodes) == 0x0C);
GG_STATIC_ASSERT(offsetof(Kamikaze, Nodes.Capacity) == 0x14);
GG_STATIC_ASSERT(offsetof(Kamikaze, Nodes.Count) == 0x1C);

#endif  // GG_MATCH_COMBAT_KAMIKAZE_LOAD_METHODS_H
