// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra

#include "leaf_batch3_methods.h"

// FUNCTION: GAMEMD 0x004C6320
//
// Load the payload out of a COM stream: a one-argument `__thiscall` forwarder
// that reads sizeof(*this) bytes over itself through IStream::Read and lets
// the stream's HRESULT fall out in EAX.
//
// The whole body is the call's argument layout. `RET 4` fixes the forwarder at
// one argument; the callee cleans its own four dwords, which fixes it as
// `__stdcall`; and the receiver being pushed *last* (after the count and the
// null out-pointer, and after its own vtable load) is MSVC's `__stdcall`
// virtual convention, where the interface pointer is the leftmost stack
// argument rather than a register receiver. Writing the interface as a real
// C++ class with `__stdcall` virtuals and calling the slot normally produces
// that ordering for free.
GgHresult PersistPayload_004C6320::LoadFromStream(IStream_004C6320* stream)
{
    return stream->Read(this, sizeof(*this), 0);
}

// FUNCTION: GAMEMD 0x004C6340
//
// The mirror of the above: the same forwarder over IStream::Write, differing
// only in the vtable slot it dispatches through (+0x10 rather than +0x0C).
GgHresult PersistPayload_004C6320::SaveToStream(IStream_004C6320* stream)
{
    return stream->Write(this, sizeof(*this), 0);
}

// FUNCTION: GAMEMD 0x004C9470
//
// Copy the slot's four-byte value out through the caller's buffer and hand the
// buffer back. The buffer is an explicit out-parameter rather than a hidden
// return: the only call site that uses the result, 0x004CFA15, pushes EAX
// straight into the next call instead of re-taking the temporary's address.
//
// The lever here is that the pointer is *returned*. The identical body written
// as `void Read(Dir*)` scores 25%, because without the return cl has no reason
// to keep the buffer address in EAX and materialises it elsewhere; returning
// it makes the argument load into EAX the first instruction, exactly as retail
// has it. A by-value return of the four-byte class produces the same bytes, so
// this is a case where the disassembly alone does not separate the two forms
// and the call site does.
Dir_004C9470* FacingSlot_004C9470::Read(Dir_004C9470* out)
{
    *out = this->Value;
    return out;
}

// FUNCTION: GAMEMD 0x004C9C50
//
// Return the one-byte flag at +0x5C. Two instructions, and the only thing to
// get right is the return width: the exit is `MOV AL,byte ptr [ECX+0x5C]`, so
// the function returns a byte. Declared `int` it becomes a zero-extending
// load and scores 0%; written as `return Flag5C != 0;` over a wider member it
// also scores 0%, because the comparison adds a test-and-set. A `bool` (or
// `char`, or `unsigned char`) member returned bare is the single instruction.
bool FlagHolder_004C9C50::GetFlag5C() const
{
    return this->Flag5C;
}

// FUNCTION: GAMEMD 0x004D28C0
//
// Hand back the first item when the collection is non-empty, otherwise null.
//
// Retail's two return blocks — the hot one falling through the `JLE` and a
// cold `XOR EAX,EAX; RET` parked after it — are what the guard polarity
// decides. Written the other way round, as `if (Count <= 0) return 0;`
// followed by the item load, cl emits the zeroing first and the body scores
// 37.5%. With the positive test written first the zero block lands last with
// no extra work. A ternary and an explicit accumulator with an else arm both
// reach the same bytes, so this one is about which arm is inline, not about
// how many exits the source has.
void* ItemVectorOwner_004D28C0::GetFirstItem() const
{
    if (this->Count > 0) {
        return this->Items[0];
    }
    return 0;
}
