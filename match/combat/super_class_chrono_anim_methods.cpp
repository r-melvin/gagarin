// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Bytes matched against retail gamemd.exe v1.001 at 0x6CB3A0.

#include "super_class_chrono_anim_methods.h"

// FUNCTION: GAMEMD 0x6CB3A0
//
// Replace the superweapon's placement animation: detach any existing one
// (clear its +0x195 byte, drop the pending-list entry), likewise drop the
// entry when the +0x6C flag says one is pending, then create the rules anim
// type five units above the given coordinates (loop delay 0, one loop, flags
// 0x600) and, if that succeeded, remember it and register this super in the
// pending list (DynamicVectorClass::AddItem expanded inline).
//
// MATCHED (100.0%, 93/93). The residual — retail accumulating
// `CapacityIncrement + Capacity` into the register already holding the
// increment (`ADD ECX,EAX`) and loading the vtable into the freed EAX before
// the argument pushes, where cl 8804 accumulated into EAX and loaded the
// vtable after the pushes — was not the register-naming class it was filed
// as. It is the shape of the inlined append: written as a member of the
// vector the body scores 95.7%, written as a free inline function taking the
// vector as its first pointer parameter the same body scores 100%. Same lever
// as 0x41D300 in match/core/registered_object_ctor_methods.cpp, found there
// first and confirmed here on the first try.
//
// Coord phrasings tried in earlier passes (all with the member spelling):
// named local before the new (40.9%), three-int ctor temporary inside the new
// (48.4%), ctor-body assignments, named z / x,y,z locals, (const&, dz) ctor,
// three int parameters (all 48.4%), operator+ with a constant offset and an
// inline struct-returning helper (both 95.7%).
//
// The append written as a free inline helper taking the vector as a pointer
// parameter rather than as a member of the vector — the lever that resolved the
// same inlined-AddItem residual at 0x41D300.
static inline bool AddItem_006CB3A0(SuperVector_006CB3A0* self,
                                    SuperClass_006CB3A0* item)
{
    if (self->Count >= self->Capacity) {
        if (!self->IsAllocated && self->Capacity != 0) {
            return false;
        }
        if (self->CapacityIncrement <= 0) {
            return false;
        }
        if (!self->SetCapacity(self->CapacityIncrement + self->Capacity, 0)) {
            return false;
        }
    }
    int idx = self->Count++;
    self->Items[idx] = item;
    return true;
}

void SuperClass_006CB3A0::CreateChronoAnim(CoordStruct_006CB3A0 coords)
{
    if (this->Animation != 0) {
        this->Animation->At_195 = 0;
        this->Animation = 0;
        DAT_00B0F5B8.Remove(this);
    }

    if (this->At_6C) {
        DAT_00B0F5B8.Remove(this);
        this->At_6C = false;
    }

    AnimClass_006CB3A0* anim = new AnimClass_006CB3A0(
        RulesInstance_006CB3A0->At_330,
        coords + CoordStruct_006CB3A0(0, 0, 5),
        0, 1, 0x600, 0, false);
    if (anim != 0) {
        this->Animation = anim;
        AddItem_006CB3A0(&DAT_00B0F5B8, this);
    }
}
