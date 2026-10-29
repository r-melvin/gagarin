// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Small functions read off the user's retail gamemd.exe v1.001 with the local Ghidra CLI at the
//   address in each annotation. The receiver is a placeholder view named after its address.
//   Address index: 0x74BF40, 0x74BD50.
//   (/Ob2: retail inlines the selection step 0x74BF40 into 0x74BD50.)

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x54A900 (decl; reloc)
void __fastcall FUN_0054A900(unsigned char* bits, int index, int value);
// FUNCTION: GAMEMD 0x54A950 (decl; reloc)
int __fastcall FUN_0054A950(unsigned char* bits, int index);

// Polymorphic part of the selection holder: vptr at +0xC, bit array at +0x10.
struct Sub_0074BF40
{
    virtual void Slot0();
    virtual bool Slot1(Sub_0074BF40* other);
    unsigned char* Bits;   // +0x10
};

struct Obj_0074BF40
{
    unsigned int  Limit;     // +0x00
    unsigned char Flag;      // +0x04
    unsigned char _pad_05[3];
    unsigned int  Current;   // +0x08
    Sub_0074BF40  Sub;       // +0x0C

    // FUNCTION: GAMEMD 0x74BF40 (__thiscall, RET 4)
    void Select(unsigned int index);
    // FUNCTION: GAMEMD 0x74BD50 (__thiscall, RET 4)
    int Matches(Obj_0074BF40* other);
};
GG_STATIC_ASSERT(offsetof(Obj_0074BF40, Flag) == 0x04);
GG_STATIC_ASSERT(offsetof(Obj_0074BF40, Current) == 0x08);
GG_STATIC_ASSERT(offsetof(Obj_0074BF40, Sub) == 0x0C);
GG_STATIC_ASSERT(offsetof(Obj_0074BF40, Sub.Bits) == 0x10);

// FUNCTION: GAMEMD 0x74BF40
// Make index (or none, when it is out of range) the selected bit: the previous
// selection's flag is stored back into the array and the new bit's value is
// saved in Flag.
void Obj_0074BF40::Select(unsigned int index)
{
    if (index >= Limit) {
        index = (unsigned int)-1;
    }
    if (index != Current) {
        if (Current != (unsigned int)-1) {
            FUN_0054A900(Sub.Bits, Current, Flag);
        }
        if (index != (unsigned int)-1) {
            Flag = (unsigned char)FUN_0054A950(Sub.Bits, index);
        }
        Current = index;
    }
}

// FUNCTION: GAMEMD 0x74BD50
// Re-select the current bit, then compare limits and the polymorphic part.
int Obj_0074BF40::Matches(Obj_0074BF40* other)
{
    Select(Current);
    if (Limit == other->Limit && Sub.Slot1(&other->Sub)) {
        return 1;
    }
    return 0;
}
