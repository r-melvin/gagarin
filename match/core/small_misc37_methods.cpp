// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at the five addresses below.

#include "small_misc37_methods.h"

// FUNCTION: GAMEMD 0x4019A0
//
// The usual deleting-destructor shape: install this class's vtable, tear down
// the members, install the base's vtable, run the base destructor, and free
// only when the caller's flag bit says the object was heap-allocated. The
// object pointer is handed back either way.
void* BufferHolder_004019A0::FUN_004019A0(char flags)
{
    Vtable = &VT_007E16B0;
    Reset  = 0;

    FUN_0043AE50(Buffer);

    Vtable = &VT_007E1668;

    FUN_00431B80(this);

    if (flags & 1) {
        FUN_007C8B3D(this);
    }

    return this;
}

// FUNCTION: GAMEMD 0x4023F0
//
// `AND AL,0xFA` is the whole-word `&= ~5` narrowed by VC6 - the load and the
// store are both dwords, only the mask is a byte.
int Obj_004023F0::FUN_004023F0()
{
    // Volatile pins both the order and the width. Plain stores let VC6 hoist
    // the Flags load above the Pending store, and a plain `&=` comes out as
    // `AND EDX,0xFFFFFFFA` where retail has the narrowed `AND AL,0xFA` - the
    // narrowing peephole only fires for the AL form, and only once the value is
    // in EAX. The volatile read-modify-write puts it there.
    *(volatile int*)&Pending = 0;
    *(volatile int*)&Flags &= ~5;
    *(volatile int*)&FlagsHigh = 0;

    FUN_00401000(Sub);

    Handler_004023F0 handler = Handler;

    if (handler) {
        return handler(this);
    }

    return 0;
}

// FUNCTION: GAMEMD 0x405580
//
// Both flag writes are volatile, and both need to be. The volatile is not about
// width here but about order: a plain `|= 0x60` on the detach path lets VC6
// hoist the owner re-read in between, and retail loads +0xB0 only after the
// flag store lands. The widths then fall out on their own - `OR AL,0x60` on the
// detach path and `OR ECX,0x60` on the other, from the same source expression,
// because the two blocks get different registers.
void __fastcall FUN_00405580(Obj_00405580* self)
{
    // Retail tests the flag byte in place (`TEST byte ptr [ESI+0x18],0x20`)
    // rather than loading the word first, which is what the byte-width read
    // gives; `self->Flags & 0x20` on the int emits `MOV EAX,..; TEST AL,0x20`.
    if (*(unsigned char*)&self->Flags & 0x20) {
        return;
    }

    Owner_00405580* owner = self->Owner;

    if (owner && self == owner->Current) {
        FUN_004026A0(owner);

        *(volatile int*)&self->Flags |= 0x60;

        FUN_004026B0(self->Owner);

        return;
    }

    *(volatile int*)&self->Flags |= 0x60;
}

// FUNCTION: GAMEMD 0x406550
//
// Both resets act on the same sub-object, so its address is taken once; the
// second is a tail call, which is what the free-function form gives.
void __fastcall FUN_00406550(Obj_00406550* self)
{
    void* sub = self->Sub;

    FUN_00407150(sub);
    FUN_004071C0(sub);
}

// FUNCTION: GAMEMD 0x41BEA0
//
// `CDQ; AND EDX,0xFF; ADD EAX,EDX; SAR EAX,8` is the signed divide-by-256
// idiom, so both members are 8.8 fixed-point and the result is their whole
// parts.
Packed16 Obj_0041BEA0::FUN_0041BEA0()
{
    Packed16 packed;

    packed.X = (short)(ValueX / 256);
    packed.Y = (short)(ValueY / 256);

    return packed;
}
