// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x67A3C0 and its nine duplicates. Offsets come straight off
//   the instructions: the vector's Count at `[EBX+0x10]` (`MOV EAX,[EBX+0x10]`
//   into the frame slot whose address is then handed to the stream) and its
//   Items at `[EBX+4]` (`LEA EDX,[ECX+ESI*4]`, so a four-byte element). The
//   called slot is `[ECX+0x10]` with four stack arguments and the receiver
//   pushed first — IStream::Write, three IUnknown slots plus ISequentialStream
//   ::Read at +0x0C ahead of it — so the convention is the __stdcall COM
//   virtual, not __thiscall. The count and every element are written with a
//   length of 4 and a null pcbWritten.
//
//   All ten instances are byte-for-byte identical, relocations included: the
//   element type never reaches the code because every write goes through the
//   same COM slot with the same literal length. These entry points carry no
//   name in the binary or in the YRpp map and keep their placeholder names.
#ifndef GG_MATCH_CORE_VECTOR_STREAM_SAVE_FAMILY_METHODS_H
#define GG_MATCH_CORE_VECTOR_STREAM_SAVE_FAMILY_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Stream_0067A3C0;

// IStream::Write is slot +0x10; __stdcall with the receiver pushed.
typedef long (__stdcall* StreamWrite_0067A3C0)(Stream_0067A3C0*, const void*,
                                               unsigned long, unsigned long*);
#define GG_SAVE_WRITE(s, p, n) \
    ((*(StreamWrite_0067A3C0*)(*(char**)(s) + 0x10))(s, p, n, 0))

// A growable vector of four-byte elements: vtable@0, Items@4, Capacity@8,
// the two flag bytes at +0xC/+0xD, Count@0x10, CapacityIncrement@0x14.
struct SaveVector_0067A3C0
{
    void* Vtbl;               // +0x0000
    int*  Items;              // +0x0004
    int   Capacity;           // +0x0008
    char  IsInitialized;      // +0x000C
    char  IsAllocated;        // +0x000D
    char  _pad00E[2];         // +0x000E
    int   Count;              // +0x0010
    int   CapacityIncrement;  // +0x0014

    int FUN_0067A3C0(Stream_0067A3C0* stream);
    int FUN_0067A4A0(Stream_0067A3C0* stream);
    int FUN_0067A520(Stream_0067A3C0* stream);
    int FUN_0067A630(Stream_0067A3C0* stream);
    int FUN_0067A6E0(Stream_0067A3C0* stream);
    int FUN_0067A770(Stream_0067A3C0* stream);
    int FUN_0067A7D0(Stream_0067A3C0* stream);
    int FUN_0067A850(Stream_0067A3C0* stream);
    int FUN_0067A8E0(Stream_0067A3C0* stream);
    int FUN_00717B20(Stream_0067A3C0* stream);
};
GG_STATIC_ASSERT(offsetof(SaveVector_0067A3C0, Items) == 0x04);
GG_STATIC_ASSERT(offsetof(SaveVector_0067A3C0, Count) == 0x10);
GG_STATIC_ASSERT(sizeof(SaveVector_0067A3C0) == 0x18);

// The one shared body: write the element count, then each element.
//
// The return type is `int` returning the count, not `void`. EAX holds the
// count at every exit of the retail function, and the extra `MOV EAX,[ESP+0xC]`
// that reloads it at the bottom of the loop only exists because the value has
// to survive the call for the return; written as `void` the reload disappears
// and one instruction is missing (66.7%, retail-only {mov}).
#define GG_VECTOR_STREAM_SAVE_BODY(ADDR)                                  \
int SaveVector_0067A3C0::FUN_##ADDR(Stream_0067A3C0* stream)              \
{                                                                         \
    int count = Count;                                                    \
    GG_SAVE_WRITE(stream, &count, 4);                                     \
    for (int i = 0; i < count; ++i) {                                     \
        GG_SAVE_WRITE(stream, &Items[i], 4);                              \
    }                                                                     \
    return count;                                                         \
}


#endif  // GG_MATCH_CORE_VECTOR_STREAM_SAVE_FAMILY_METHODS_H
