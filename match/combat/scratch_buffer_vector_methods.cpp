// SPDX-License-Identifier: GPL-3.0-or-later
// VC6FLAGS: /nologo /c /O2 /Gr /DNDEBUG /Gy /MT
//   This TU must build without /GX, now the project default. Both array-new
//   constructors here build elements whose constructor is out of line, and with
//   C++ exception handling on cl wraps the array-new loop in an unwind frame
//   (___CxxFrameHandler, a .text$x funclet and an .xdata$x entry) that retail
//   does not have. Retail's 0x628ED0 and 0x628B00 are a bare loop, so the
//   retail build compiled this translation unit without /GX.
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | private-ref-cross-check
//   Bytes matched against the user's retail gamemd.exe v1.001 at 0x6285A0,
//   0x628A70, 0x628B00, 0x628D10, 0x628D80, 0x628DF0 and 0x628ED0, plus
//   0x4F4D80 and 0x4F4D90.

#include "scratch_buffer_vector_methods.h"

// FUNCTION: GAMEMD 0x4F4D80
// Retail's body is a single `JMP` to itself: the comparison calls itself in
// tail position and never compares anything.
bool ScratchEntry::operator==(ScratchEntry const& other) const
{
    return *this == other;
}

// FUNCTION: GAMEMD 0x4F4D90
bool ScratchEntry::operator!=(ScratchEntry const& other) const
{
    return !(*this == other);
}

// FUNCTION: GAMEMD 0x6285A0
//
// Find an entry in the growable 3-byte-element vector and return its index, or
// -1 when it is not there. The bound is the active count at +0x10 rather than
// the capacity at +0x08, which is what distinguishes this search from the one
// at 0x628A70; the stride constant `ADD EBX,0x3` is the element size.
int TripleDynVector::ID(TripleEntry const& object) const
{
    for (int index = 0; index < Count; index++) {
        if (Vector[index] == object) return index;
    }
    return -1;
}

// FUNCTION: GAMEMD 0x628A70
//
// The same search over the fixed-capacity vector of 0x104-byte entries. An
// invalid vector answers zero rather than -1, which is the `XOR EAX,EAX` tail
// reached from the leading `MOV AL,[ESI+0xC]; TEST AL,AL` guard; a valid vector
// that runs off the end answers -1 through the shared `OR EAX,-1` tail.
int ScratchVector::ID(ScratchEntry const& object) const
{
    if (!IsValid) return 0;

    for (int index = 0; index < Capacity; index++) {
        ScratchEntry const* item = &Vector[index];
        if (*item == object) return index;
    }
    return -1;
}

// FUNCTION: GAMEMD 0x628B00
//
// Construct the growable vector of entries. The base constructor is inlined
// (retail issues no call between the base's member stores and the derived vptr
// store at 0x628B8F), and the derived body is just the two counters, with the
// growth step seeded to ten.
ScratchDynVector::ScratchDynVector(unsigned int size, ScratchEntry const* array)
    : ScratchVectorInline(size, array)
{
    CapacityIncrement = 10;
    Count = 0;
}

// FUNCTION: GAMEMD 0x628D10
//
// Append one entry, growing first if the vector is full. The three refusals --
// borrowed non-empty storage, a non-positive growth step, and a failed resize
// -- all reach the single `XOR AL,AL` tail at 0x628D3F, so they are one
// condition chain rather than three early returns. The count is re-read after
// the possible resize (`LEA ECX,[EAX+1]` with the old value kept in EAX is the
// post-increment), and the element assignment is inlined: the out-of-line call
// copies the name buffer and the caller copies the value word at +0x100.
bool ScratchDynVector::Add(ScratchEntry const& object)
{
    if (Count < Capacity
        || ((IsAllocated || Capacity == 0)
            && CapacityIncrement > 0
            && Resize(Capacity + CapacityIncrement, 0))) {

        int index = Count;

        Count = index + 1;
        Vector[index] = object;

        return true;
    }

    return false;
}

// FUNCTION: GAMEMD 0x628D80
//
// The growable entry vector's search: the same shape as 0x6285A0 with the
// 0x104-byte stride and the entry comparison.
int ScratchDynVector::ID(ScratchEntry const& object) const
{
    for (int index = 0; index < Count; index++) {
        ScratchEntry const* item = &Vector[index];
        if (*item == object) return index;
    }
    return -1;
}

// FUNCTION: GAMEMD 0x628DF0
//
// Construct the fixed-capacity vector of 3-byte entries over storage the caller
// supplies or over storage of its own. The element constructor is small enough
// for VC6 to inline into the array-new loop, which is retail's three byte
// stores from a zeroed register followed by `ADD EAX,0x3`. A failed allocation
// still marks the vector as owning its storage.
TripleVector::TripleVector(unsigned int size, TripleEntry const* array)
    : Vector(0), Capacity(size), IsValid(true), IsAllocated(false)
{
    if (size) {
        if (array) {
            Vector = new((void*)array) TripleEntry[size];
        } else {
            Vector = new TripleEntry[size];
            IsAllocated = true;
        }
    }
}

// FUNCTION: GAMEMD 0x628ED0
//
// The same constructor for the 0x104-byte entry, where the element constructor
// is out of line and the array-new loop keeps its call. The allocation size is
// `n * 65 * 4`, spelled by retail as `SHL 6; ADD; SHL 2`.
ScratchVector::ScratchVector(unsigned int size, ScratchEntry const* array)
    : Vector(0), Capacity(size), IsValid(true), IsAllocated(false)
{
    if (size) {
        if (array) {
            Vector = new((void*)array) ScratchEntry[size];
        } else {
            Vector = new ScratchEntry[size];
            IsAllocated = true;
        }
    }
}
