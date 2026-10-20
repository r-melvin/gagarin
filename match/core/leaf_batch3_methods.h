// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Five small leaf bodies in the 0x004C6000-0x004D3000 range, each one
//   abandoned by an earlier pass after one or two spellings. Every member
//   offset below is read numerically off the member-access instructions in the
//   local Ghidra disassembly of the user's retail gamemd.exe v1.001; the
//   return widths are read off the exit instructions (MOV AL versus MOV EAX)
//   and confirmed at the call sites, which test AL for 0x004C9C50 and EAX for
//   0x004D28C0.
#ifndef GG_MATCH_CORE_LEAF_BATCH3_METHODS_H
#define GG_MATCH_CORE_LEAF_BATCH3_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

typedef unsigned long GgUlong;
typedef long GgHresult;

// The COM stream the persistence pair at 0x004C6320/0x004C6340 forwards to.
// The two bodies dispatch through slots +0x0C and +0x10 of the interface's
// vtable and push the interface itself as the leftmost stack argument, which
// is MSVC's `__stdcall` virtual convention: IUnknown occupies slots 0..2, so
// +0x0C is IStream::Read and +0x10 is IStream::Write. Declaring the five slots
// in that order and letting cl emit the call reproduces both bodies exactly;
// nothing here is ever instantiated, so the pure virtuals need no definitions.
struct IStream_004C6320 {
    virtual GgHresult __stdcall QueryInterface(const void* riid,
                                               void** ppvObject) = 0;  // +0x00
    virtual GgUlong __stdcall AddRef() = 0;                            // +0x04
    virtual GgUlong __stdcall Release() = 0;                           // +0x08
    virtual GgHresult __stdcall Read(void* pv, GgUlong cb,
                                     GgUlong* pcbRead) = 0;            // +0x0C
    virtual GgHresult __stdcall Write(const void* pv, GgUlong cb,
                                      GgUlong* pcbWritten) = 0;        // +0x10
};

// FUNCTION: GAMEMD 0x004C6320
// FUNCTION: GAMEMD 0x004C6340
// The payload the pair streams. Both bodies push the literal 0x44 as the byte
// count and never touch a member, so the only layout fact the binary gives up
// is the transfer size; it is modelled as the object's own size so the
// constant is derived rather than repeated.
struct PersistPayload_004C6320 {
    unsigned char unknown_00[0x44];

    // FUNCTION: GAMEMD 0x004C6320
    GgHresult LoadFromStream(IStream_004C6320* stream);
    // FUNCTION: GAMEMD 0x004C6340
    GgHresult SaveToStream(IStream_004C6320* stream);
};
GG_STATIC_ASSERT(sizeof(PersistPayload_004C6320) == 0x44);

// The four-byte value 0x004C9470 copies out. Only the low sixteen bits are
// ever written by the slot's writers, so the payload is a short beside an
// unwritten neighbour; the reader copies the whole dword regardless. The same
// shape is declared as a callee stand-in by the fly-locomotion headers
// (`Dir_004CE680`); this is the definition side of the same retail body.
struct Dir_004C9470 {
    short Raw;         // +0x00
    short Unknown02;   // +0x02
};
GG_STATIC_ASSERT(sizeof(Dir_004C9470) == 4);

// FUNCTION: GAMEMD 0x004C9470
// The facing slot the value lives in. The body reads the dword at [ECX] with
// no displacement, so the value sits at offset zero.
struct FacingSlot_004C9470 {
    Dir_004C9470 Value;  // +0x00

    // FUNCTION: GAMEMD 0x004C9470
    Dir_004C9470* Read(Dir_004C9470* out);
};
GG_STATIC_ASSERT(offsetof(FacingSlot_004C9470, Value) == 0x00);

// FUNCTION: GAMEMD 0x004C9C50
// The locomotion-ish object whose byte flag at +0x5C the getter returns. Its
// sole caller at 0x006A8F99 tests AL, and the neighbouring reader at
// 0x004C9C60 reads and clears a second byte at +0x5D, so +0x5C is a one-byte
// field and not the low byte of a wider one.
struct FlagHolder_004C9C50 {
    unsigned char unknown_00[0x5c];
    bool Flag5C;  // +0x5C

    // FUNCTION: GAMEMD 0x004C9C50
    bool GetFlag5C() const;
};
GG_STATIC_ASSERT(offsetof(FlagHolder_004C9C50, Flag5C) == 0x5c);

// FUNCTION: GAMEMD 0x004D28C0
// A vector-shaped owner: an items pointer at +0x60 and a signed count at
// +0x6C. The getter dereferences the items pointer with no index scaling, so
// it hands back element zero.
struct ItemVectorOwner_004D28C0 {
    unsigned char unknown_00[0x60];
    void** Items;                // +0x60
    unsigned char unknown_64[8];
    int Count;                   // +0x6C

    // FUNCTION: GAMEMD 0x004D28C0
    void* GetFirstItem() const;
};
GG_STATIC_ASSERT(offsetof(ItemVectorOwner_004D28C0, Items) == 0x60);
GG_STATIC_ASSERT(offsetof(ItemVectorOwner_004D28C0, Count) == 0x6c);

#endif  // GG_MATCH_CORE_LEAF_BATCH3_METHODS_H
