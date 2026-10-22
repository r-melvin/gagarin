// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | private-ref-cross-check
//   Every offset, element stride, virtual slot and growth constant below is
//   read numerically off the user's retail gamemd.exe v1.001 with the local
//   Ghidra CLI at 0x6285A0, 0x628A70, 0x628B00, 0x628D10, 0x628D80, 0x628DF0
//   and 0x628ED0. The container is a VectorClass/DynamicVectorClass pair (RTTI-named vector
//   classes; offsets as read here).
//
// One address run, two template instantiations of the same container pair.
//
//   ScratchEntry  -- 0x104 bytes: a 0x100-byte name buffer plus a 4-byte
//                    value. Its stride is pinned by the two independent
//                    encodings retail uses for it: `ADD EDI,0x104` in the
//                    search loops, and `EAX<<6 + EAX` then `<<2` (i.e.
//                    n * 65 * 4) for the allocation size and the element
//                    address.
//   TripleEntry   -- 3 bytes: `ADD EBX,0x3` in the search loop and
//                    `LEA EAX,[ESI + ESI*2]` for the allocation size.
//
// Container layout, confirmed member by member from the disassembly:
//   +0x00  vptr              `MOV [EDI],<vtable>`; `MOV EDX,[ESI]` +
//                            `CALL [EDX+8]` in Add
//   +0x04  Vector            `MOV ECX,[ESI+4]` then indexed by the stride
//   +0x08  Capacity         loop bound in the VectorClass search; compared
//                            against the count in Add; added to the step
//   +0x0C  IsValid   (byte)  `MOV AL,[ESI+0xC]` guard at 0x628A70
//   +0x0D  IsAllocated(byte) `MOV AL,[ESI+0xD]`; set to 1 on the owning arm
//   +0x10  Count       loop bound in the DynamicVectorClass search;
//                            post-incremented by `LEA ECX,[EAX+1]` in Add
//   +0x14  CapacityIncrement        `MOV [EDI+0x14],0xA` seeds it to ten; `JLE` on
//                            it, so it is signed
//
// Virtual slot order (the only slot these functions reach is +0x08):
//   0x00 ~VectorClass  0x04 operator==  0x08 Resize  0x0C Clear
//   0x10 ID            0x14 GetItemIndex 0x18 GetItem
// Add issues `CALL [EDX+0x8]` with two pushed arguments and tests the byte
// result, which is Resize(capacity, array).
#ifndef GG_MATCH_COMBAT_SCRATCH_BUFFER_VECTOR_METHODS_H
#define GG_MATCH_COMBAT_SCRATCH_BUFFER_VECTOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// The ordinary array form has to be declared alongside the placement forms or
// VC6 hides it and the allocating arm fails to compile.
void* __cdecl operator new(size_t);
void* __cdecl operator new[](size_t);
inline void* operator new(size_t, void* where) { return where; }
inline void* operator new[](size_t, void* where) { return where; }

// ---------------------------------------------------------------------------
// ScratchEntry: the 0x104-byte element.
//
// The name buffer's assignment is out of line (retail's `PUSH <src>;
// MOV ECX,<dst>; CALL 0x4F4CB0`, a `__thiscall` with the source pushed and
// popped by the callee), while the entry's own assignment is inlined at the
// call site -- which is why the 4-byte value is copied with a plain
// `MOV ECX,[EDI+0x100]; MOV [ESI+0x100],ECX` right after that call.
//
// The comparison arrives with `this` in ECX and the operand in EDX and pushes
// nothing, so it is `__fastcall`, not the ordinary `__thiscall`.
// ---------------------------------------------------------------------------
struct EntryNameBuf
{
    char Text[0x100];
    // FUNCTION: GAMEMD 0x4F4CB0 (decl; reloc) -- out-of-line buffer assignment.
    EntryNameBuf& operator=(EntryNameBuf const& other);
};
GG_STATIC_ASSERT(sizeof(EntryNameBuf) == 0x100);

struct ScratchEntry
{
    EntryNameBuf Name;   // +0x000
    int          Value;  // +0x100

    // FUNCTION: GAMEMD 0x4F4C20 (decl; reloc) -- out-of-line element ctor,
    // called once per slot by the inlined array-new loop.
    ScratchEntry();
    // FUNCTION: GAMEMD 0x4F4D80 (decl; reloc) -- __fastcall comparison.
    bool __fastcall operator==(ScratchEntry const& other) const;

    ScratchEntry& operator=(ScratchEntry const& other)
    {
        Name = other.Name;
        Value = other.Value;
        return *this;
    }
};
GG_STATIC_ASSERT(offsetof(ScratchEntry, Value) == 0x100);
GG_STATIC_ASSERT(sizeof(ScratchEntry) == 0x104);

// ---------------------------------------------------------------------------
// TripleEntry: the 3-byte element. Its constructor is inlined into the
// array-new loop (three byte stores from a zeroed register, in member order,
// then `ADD EAX,0x3`), so it is defined here rather than declared.
// ---------------------------------------------------------------------------
struct TripleEntry
{
    char A, B, C;

    TripleEntry() { A = 0; B = 0; C = 0; }
    // FUNCTION: GAMEMD 0x5175D0 (decl; reloc) -- __fastcall comparison.
    bool __fastcall operator==(TripleEntry const& other) const;
};
GG_STATIC_ASSERT(sizeof(TripleEntry) == 3);

// ---------------------------------------------------------------------------
// VectorClass<ScratchEntry>. Its constructor is emitted out of line at
// 0x628ED0; the copy of it that the growable vector inlines lives in
// ScratchVectorInline below, because VC6 will not inline a constructor it has
// only seen declared.
// ---------------------------------------------------------------------------
class ScratchVector
{
public:
    // VTABLE: GAMEMD 0x7EF7D0
    virtual ~ScratchVector();                                              // 0x00
    virtual bool operator==(ScratchVector const& other) const;             // 0x04
    virtual bool Resize(int capacity, ScratchEntry const* array);          // 0x08
    virtual void Clear();                                                  // 0x0C
    virtual int  ID(ScratchEntry const& object) const;                     // 0x10

    ScratchEntry* Vector;       // +0x04
    int           Capacity;    // +0x08
    bool          IsValid;      // +0x0C
    bool          IsAllocated;  // +0x0D

    // FUNCTION: GAMEMD 0x628ED0
    ScratchVector(unsigned int size, ScratchEntry const* array);
};
GG_STATIC_ASSERT(offsetof(ScratchVector, Vector) == 0x04);
GG_STATIC_ASSERT(offsetof(ScratchVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(ScratchVector, IsValid) == 0x0C);
GG_STATIC_ASSERT(offsetof(ScratchVector, IsAllocated) == 0x0D);
GG_STATIC_ASSERT(sizeof(ScratchVector) == 0x10);

// The same class with the constructor defined in the class body, so that the
// derived constructor at 0x628B00 inlines it exactly as retail does. Retail has
// no call between the base's member stores and the derived vptr store.
class ScratchVectorInline
{
public:
    // VTABLE: GAMEMD 0x7EF7D0
    virtual ~ScratchVectorInline();
    virtual bool operator==(ScratchVectorInline const& other) const;
    virtual bool Resize(int capacity, ScratchEntry const* array);
    virtual void Clear();
    virtual int  ID(ScratchEntry const& object) const;

    ScratchEntry* Vector;       // +0x04
    int           Capacity;    // +0x08
    bool          IsValid;      // +0x0C
    bool          IsAllocated;  // +0x0D

    ScratchVectorInline(unsigned int size, ScratchEntry const* array)
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
};
GG_STATIC_ASSERT(offsetof(ScratchVectorInline, IsAllocated) == 0x0D);

// ---------------------------------------------------------------------------
// DynamicVectorClass<ScratchEntry>.
// ---------------------------------------------------------------------------
class ScratchDynVector : public ScratchVectorInline
{
public:
    // VTABLE: GAMEMD 0x7EF770
    int Count;  // +0x10
    int CapacityIncrement;   // +0x14

    // FUNCTION: GAMEMD 0x628B00
    ScratchDynVector(unsigned int size, ScratchEntry const* array);
    // FUNCTION: GAMEMD 0x628D10
    bool Add(ScratchEntry const& object);
    // FUNCTION: GAMEMD 0x628D80
    int  ID(ScratchEntry const& object) const;
};
GG_STATIC_ASSERT(offsetof(ScratchDynVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(ScratchDynVector, CapacityIncrement) == 0x14);
GG_STATIC_ASSERT(sizeof(ScratchDynVector) == 0x18);

// ---------------------------------------------------------------------------
// VectorClass<TripleEntry> and its growable derivative. Only the base's
// constructor and the derivative's search are in this address run.
// ---------------------------------------------------------------------------
class TripleVector
{
public:
    // VTABLE: GAMEMD 0x7EF7F0
    virtual ~TripleVector();                                              // 0x00
    virtual bool operator==(TripleVector const& other) const;             // 0x04
    virtual bool Resize(int capacity, TripleEntry const* array);          // 0x08
    virtual void Clear();                                                 // 0x0C
    virtual int  ID(TripleEntry const& object) const;                     // 0x10

    TripleEntry* Vector;       // +0x04
    int          Capacity;    // +0x08
    bool         IsValid;      // +0x0C
    bool         IsAllocated;  // +0x0D

    // FUNCTION: GAMEMD 0x628DF0
    TripleVector(unsigned int size, TripleEntry const* array);
};
GG_STATIC_ASSERT(offsetof(TripleVector, Vector) == 0x04);
GG_STATIC_ASSERT(offsetof(TripleVector, Capacity) == 0x08);
GG_STATIC_ASSERT(offsetof(TripleVector, IsValid) == 0x0C);
GG_STATIC_ASSERT(offsetof(TripleVector, IsAllocated) == 0x0D);

class TripleDynVector : public TripleVector
{
public:
    int Count;  // +0x10
    int CapacityIncrement;   // +0x14

    // FUNCTION: GAMEMD 0x6285A0
    int ID(TripleEntry const& object) const;
};
GG_STATIC_ASSERT(offsetof(TripleDynVector, Count) == 0x10);
GG_STATIC_ASSERT(offsetof(TripleDynVector, CapacityIncrement) == 0x14);

#endif  // GG_MATCH_COMBAT_SCRATCH_BUFFER_VECTOR_METHODS_H
