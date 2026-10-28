// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets derived from the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI (member-access disassembly at 0x556B50 / 0x556DF0), cross-checked
//   against YRpp (reconfirmed
//   numerically here).
//
// LineTrail — a fading line-segment trail (e.g. tracer / phase trail). Owns a
// 32-entry ring of LineTrailNode and is tracked in a global DynamicVectorClass.
#ifndef GG_MATCH_RENDERER_LINE_TRAIL_H
#define GG_MATCH_RENDERER_LINE_TRAIL_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// __cdecl free used by DeleteAll for each freed trail and for the array block
// (raw `push arg; call 0x7C8B3D; add esp,4`). Declared (no body) so cl emits a
// normalised call reloc. GAMEMD 0x7C8B3D.
// ---------------------------------------------------------------------------
void __cdecl GameDelete(void* block);

// The owner object back-link cleared by DeleteAll: store of 0 to a dword at
// +0xA8 (`MOV [EAX+0xA8], EBX`). Only that member is modelled here.
struct LineTrailOwner
{
    char _pad0[0xA8];      // +0x00  full ObjectClass layout = P2
    int  AttachedTrail;    // +0xA8  back-link cleared by DeleteAll (dword)
};

// DynamicVectorClass<LineTrail*> head. The virtual called from DeleteAll lands
// at vtable +0x10 (slot 4 = FindItemIndex); RemoveItem/Remove are inlined.
struct LineTrail;

class LineTrailVector
{
public:
    // Virtuals in retail declaration order so FindItemIndex sits at slot 4
    // (+0x10). Bodies live in the TU that constructs the global Array; declared
    // (no body) here — the only use is the normalised virtual call.
    virtual ~LineTrailVector();                                     // slot 0 (+0x00)
    virtual bool operator==(const LineTrailVector& other) const;    // slot 1 (+0x04)
    virtual bool SetCapacity(int capacity, LineTrail** mem);        // slot 2 (+0x08)
    virtual void Clear();                                           // slot 3 (+0x0C)
    virtual int  FindItemIndex(LineTrail* const& item) const;       // slot 4 (+0x10)

    // Non-virtual, inlined into DeleteAll.
    bool RemoveItem(int index)
    {
        if (index < this->Count)
        {
            --this->Count;
            for (int i = index; i < this->Count; ++i)
                this->Items[i] = this->Items[i + 1];
            return true;
        }
        return false;
    }

    bool Remove(LineTrail* const& item)
    {
        int idx = this->FindItemIndex(item);
        if (idx != -1)
            return this->RemoveItem(idx);
        return false;
    }

    // vptr at +0x00 (implicit)
    LineTrail**   Items;             // +0x04
    int           Capacity;          // +0x08
    bool          IsInitialized;     // +0x0C
    bool          IsAllocated;       // +0x0D
    int           Count;             // +0x10
    int           CapacityIncrement; // +0x14
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(LineTrailVector, Items)       == 0x04);
GG_STATIC_ASSERT(offsetof(LineTrailVector, Capacity)    == 0x08);
GG_STATIC_ASSERT(offsetof(LineTrailVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(offsetof(LineTrailVector, Count)       == 0x10);
#endif

// One ring entry; only the dword at +0x0C is read (by FUN_00556D20).
struct LineTrailNode
{
    int unknown_00[3];
    int unknown_0C;
};

struct LineTrail
{
    void SetDecrement(int val);             // GAMEMD 0x556B50 __thiscall
    static void __stdcall DeleteAll();      // GAMEMD 0x556DF0 __stdcall
    int  FUN_00556D20();                    // GAMEMD 0x556D20 __thiscall

    unsigned char   Color[3];   // +0x00  ColorStruct (R,G,B)
    unsigned char   _pad0;      // +0x03
    LineTrailOwner* Owner;      // +0x04
    int             Decrement;  // +0x08
    int             ActiveSlot; // +0x0C
    LineTrailNode   Trails[32]; // +0x10
};

#if GG_TARGET_ABI_32
GG_STATIC_ASSERT(offsetof(LineTrail, Owner)     == 0x04);
#endif
GG_STATIC_ASSERT(offsetof(LineTrail, Decrement) == 0x08);
GG_STATIC_ASSERT(offsetof(LineTrail, ActiveSlot) == 0x0C);
GG_STATIC_ASSERT(offsetof(LineTrail, Trails) == 0x10);
GG_STATIC_ASSERT(offsetof(LineTrailNode, unknown_0C) == 0x0C);

#endif  // GG_MATCH_RENDERER_LINE_TRAIL_H
