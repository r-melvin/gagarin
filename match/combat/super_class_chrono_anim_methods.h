// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Offsets, globals and slots read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at 0x6CB3A0: `[ESI+0x68]`
//   (Animation, its byte `[EAX+0x195]` cleared), `[ESI+0x6C]` (pending-list
//   flag), the vector object at 0xB0F5B8 (`MOV ECX,0xB0F5B8`, slot +0x10
//   FindItemIndex with a stacked copy of `this`, `CALL 0x45ADD0` remove by
//   index, slot +0x8 SetCapacity, Items 0xB0F5BC, Capacity 0xB0F5C0,
//   IsAllocated 0xB0F5C5, Count 0xB0F5C8, CapacityIncrement 0xB0F5CC),
//   `MOV ECX,[0x8871E0]` / `[ECX+0x330]` (RulesClass::Instance anim type),
//   `PUSH 0x1C8` / `CALL 0x7C8E17` / `CALL 0x421EA0` (sizeof(AnimClass) and
//   its 7-arg ctor) and the by-value CoordStruct argument (`RET 0xC`, Z read
//   from `[ESP+0x20]` and stored +5). Names cross-checked against YRpp
//   SuperClass.h / AnimClass.h / Notifications.h (consult-only; NO LICENSE).
#ifndef GG_MATCH_COMBAT_SUPER_CLASS_CHRONO_ANIM_METHODS_H
#define GG_MATCH_COMBAT_SUPER_CLASS_CHRONO_ANIM_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct CoordStruct_006CB3A0
{
    int X;   // +0x00
    int Y;   // +0x04
    int Z;   // +0x08

    CoordStruct_006CB3A0(int x, int y, int z) : X(x), Y(y), Z(z) {}
};
GG_STATIC_ASSERT(sizeof(CoordStruct_006CB3A0) == 0xC);

// The raised coordinate is a temporary built inside the new-expression
// (retail stores its three words between the argument pushes, after operator
// new succeeded, from EDX/EDI/EBP). Only a by-value struct result — this
// operator+ with a constant (0, 0, 5) offset, or an inline helper returning
// the struct — loads all three words into registers first as retail does; a
// three-int ctor temporary, with or without named locals, stores X straight
// from memory and never needs EDI/EBP (48.4%).
inline CoordStruct_006CB3A0 operator+(const CoordStruct_006CB3A0& a,
                                      const CoordStruct_006CB3A0& b)
{
    return CoordStruct_006CB3A0(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
}

struct AnimTypeClass_006CB3A0;   // opaque — only ever passed through

// AnimClass — sizeof 0x1C8; the ctor is body-less (reloc CALL).
struct AnimClass_006CB3A0
{
    // FUNCTION: GAMEMD 0x421EA0 (decl; reloc)
    AnimClass_006CB3A0(AnimTypeClass_006CB3A0* type,
                       const CoordStruct_006CB3A0& coords, int loopDelay,
                       int loopCount, unsigned int flags, int forceZAdjust,
                       bool reverse) throw();

    char _pad000[0x195];            // +0x0000
    char At_195;                    // +0x0195
    char _pad196[0x1C8 - 0x196];    // +0x0196
};
GG_STATIC_ASSERT(offsetof(AnimClass_006CB3A0, At_195) == 0x195);
GG_STATIC_ASSERT(sizeof(AnimClass_006CB3A0) == 0x1C8);

// RulesClass — only the anim type pointer at +0x330 is read.
struct Rules_006CB3A0
{
    char                    _pad000[0x330];   // +0x0000
    AnimTypeClass_006CB3A0* At_330;           // +0x0330  (YRpp: ChronoPlacement)
};
GG_STATIC_ASSERT(offsetof(Rules_006CB3A0, At_330) == 0x330);

// GLOBAL: GAMEMD 0x8871E0 — RulesClass::Instance.
extern Rules_006CB3A0* RulesInstance_006CB3A0;

struct SuperClass_006CB3A0;

// DynamicVectorClass<SuperClass*> at 0xB0F5B8 (an object: its address is the
// immediate `MOV ECX,0xB0F5B8`). Slot +0x8 is SetCapacity, +0x10 FindItemIndex.
struct SuperVector_006CB3A0
{
    virtual void vt_000();
    virtual void vt_004();
    virtual bool SetCapacity(int capacity, void* pMem);          // +0x0008
    virtual void vt_00C();
    virtual int  FindItemIndex(SuperClass_006CB3A0* const& item); // +0x0010

    SuperClass_006CB3A0** Items;            // +0x0004
    int                   Capacity;         // +0x0008
    unsigned char         IsInitialized;    // +0x000C
    unsigned char         IsAllocated;      // +0x000D
    unsigned char         _pad00E[2];       // +0x000E
    int                   Count;            // +0x0010
    int                   CapacityIncrement;// +0x0014

    // FUNCTION: GAMEMD 0x45ADD0 (decl; reloc) — remove the item at an index.
    void FUN_0045ADD0(int index);

    // DynamicVectorClass::Remove(item), expanded inline twice at 0x6CB3A0.
    bool Remove(SuperClass_006CB3A0* const& item)
    {
        int index = FindItemIndex(item);
        if (index != -1) {
            FUN_0045ADD0(index);
            return true;
        }
        return false;
    }

    // DynamicVectorClass::AddItem, expanded inline at the tail of 0x6CB3A0.
    bool AddItem(SuperClass_006CB3A0* item)
    {
        if (this->Count >= this->Capacity) {
            if (!this->IsAllocated && this->Capacity != 0) {
                return false;
            }
            if (this->CapacityIncrement <= 0) {
                return false;
            }
            if (!this->SetCapacity(this->CapacityIncrement + this->Capacity, 0)) {
                return false;
            }
        }
        int idx = this->Count++;
        this->Items[idx] = item;
        return true;
    }
};
GG_STATIC_ASSERT(offsetof(SuperVector_006CB3A0, Items)             == 0x04);
GG_STATIC_ASSERT(offsetof(SuperVector_006CB3A0, Capacity)          == 0x08);
GG_STATIC_ASSERT(offsetof(SuperVector_006CB3A0, IsAllocated)       == 0x0D);
GG_STATIC_ASSERT(offsetof(SuperVector_006CB3A0, Count)             == 0x10);
GG_STATIC_ASSERT(offsetof(SuperVector_006CB3A0, CapacityIncrement) == 0x14);

// GLOBAL: GAMEMD 0xB0F5B8 — the supers with a placement animation pending.
extern SuperVector_006CB3A0 DAT_00B0F5B8;

// SuperClass : AbstractClass — only the animation slot and the pending flag.
struct SuperClass_006CB3A0
{
    char                _pad000[0x68];   // +0x0000
    AnimClass_006CB3A0* Animation;       // +0x0068
    bool                At_6C;           // +0x006C

    // FUNCTION: GAMEMD 0x6CB3A0 — SuperClass::CreateChronoAnim.
    void CreateChronoAnim(CoordStruct_006CB3A0 coords);
};
GG_STATIC_ASSERT(offsetof(SuperClass_006CB3A0, Animation) == 0x68);
GG_STATIC_ASSERT(offsetof(SuperClass_006CB3A0, At_6C)     == 0x6C);

#endif  // GG_MATCH_COMBAT_SUPER_CLASS_CHRONO_ANIM_METHODS_H
