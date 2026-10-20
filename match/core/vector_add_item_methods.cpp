// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Bytes matched against retail gamemd.exe v1.001 at 0x413A70 and 0x42D830.

#include "vector_add_item_methods.h"

// FUNCTION: GAMEMD 0x413A70
//
// Append one element, growing first if the vector is full.
//
// Three separate ways to refuse, all landing on the same `XOR AL,AL` tail:
// the storage is borrowed rather than owned (`IsAllocated` clear) and non-empty,
// the growth step is not positive, or the resize itself fails. Retail reaches
// the grow attempt through `JNZ` on IsAllocated with a `TEST ECX,ECX; JNZ fail`
// underneath it, which is `IsAllocated || Capacity == 0` - an unallocated but
// empty vector is still allowed to grow.
//
// All three refusals share one `XOR AL,AL` epilogue at 0x413A9F, so they are a
// single `return false` reached by one condition chain. Written as three
// separate early returns VC6 emits three copies of the epilogue and scores
// 19.5%; the chained form below routes every failure to the one tail, and
// retail's `JL` at 0x413A7B jumps straight into the store block.
//
// The store re-reads Count rather than reusing the value compared at the top,
// because Resize may have changed it; `LEA ECX,[EAX+1]` with the old value kept
// in EAX is the post-increment.
bool VectorAddTarget::FUN_00413A70(const int& item)
{
    if (Count < Capacity
        || ((IsAllocated || Capacity == 0)
            && CapacityIncrement > 0
            && Resize(Capacity + CapacityIncrement, 0))) {

        int   index = Count;
        int*  items = (int*)Items;

        Count = index + 1;
        items[index] = item;

        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x42D830
//
// The same routine for a second element type of the same width - the two are
// byte-identical, which is what a template instantiated twice looks like.
bool VectorAddTarget::FUN_0042D830(const int& item)
{
    if (Count < Capacity
        || ((IsAllocated || Capacity == 0)
            && CapacityIncrement > 0
            && Resize(Capacity + CapacityIncrement, 0))) {

        int   index = Count;
        int*  items = (int*)Items;

        Count = index + 1;
        items[index] = item;

        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x439030
//
// The same append with the answer thrown away: every path lands on a bare
// `POP ESI; RET 4` and nothing sets AL, so this instantiation returns void. It
// also takes its element by value rather than by reference - retail has no
// dereference between loading the argument and storing it.
// Written out longhand rather than derived from the pair above.
void VectorAddTarget::FUN_00439030(int item)
{
    if (Count < Capacity
        || ((IsAllocated || Capacity == 0)
            && CapacityIncrement > 0
            && Resize(Capacity + CapacityIncrement, 0))) {

        int   index = Count;
        int*  items = (int*)Items;

        Count = index + 1;
        items[index] = item;
    }
}
