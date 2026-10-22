// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Slot displacements, argument slots and offsets read numerically off the
//   user's retail gamemd.exe v1.001 via the local Ghidra CLI at 0x410320 and
//   0x410380.
//
// A save/load pair over an ISequentialStream. The slot numbers identify it:
// +0x00/+0x04/+0x08 are IUnknown, +0x0C is Read and +0x10 is Write, and both
// are called with the receiver pushed rather than in ECX - the __stdcall COM
// convention. Each writes or reads a four-byte identity word first, then the
// object's body sized by its own +0x30 slot.
//
// Reading the argument counts needs care. At 0x410354 a `PUSH 0` sits *between*
// the size query and the stream call; it belongs to the *stream* call, not the
// query. Arguments are pushed right to left, so the rightmost (the null
// out-count) goes first, then the inner call produces the middle one. Both
// stream calls therefore take three arguments plus the receiver, which is what
// makes them the same slot.
#ifndef GG_MATCH_CORE_STREAM_PERSIST_METHODS_H
#define GG_MATCH_CORE_STREAM_PERSIST_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

struct Stream_00410320;

typedef long (__stdcall* StreamIo)(Stream_00410320*, void*, unsigned long,
                                   unsigned long*);

#define STREAM_READ(s, p, n)  ((*(StreamIo*)(*(char**)(s) + 0x0C))(s, p, n, 0))
#define STREAM_WRITE(s, p, n) ((*(StreamIo*)(*(char**)(s) + 0x10))(s, p, n, 0))

struct Subject_00410320
{
    virtual void vt_000();
    virtual void vt_004();
    virtual void vt_008();
    virtual void vt_00C();
    virtual void vt_010();
    virtual void vt_014();
    virtual void vt_018();
    virtual void vt_01C();
    virtual void vt_020();
    virtual void vt_024();
    virtual void vt_028();
    virtual void vt_02C();
    virtual unsigned long vt_030();   // +0x0030  serialised size

    char  _pad004[0x1C - 0x04];
    void* Restored;    // +0x001C
    char  Dirty;       // +0x0020
};
GG_STATIC_ASSERT(offsetof(Subject_00410320, Restored) == 0x1C);
GG_STATIC_ASSERT(offsetof(Subject_00410320, Dirty) == 0x20);

// GLOBAL: GAMEMD 0xB0C110 — the registry the loader hands the identity word to.
extern char DAT_00B0C110;

// FUNCTION: GAMEMD 0x6CF2C0 — records the identity word against the object,
// __stdcall.
void __stdcall FUN_006CF2C0(void* registry, void* identity, Subject_00410320* subject);

// FUNCTION: GAMEMD 0x410320 — save.
long __stdcall FUN_00410320(Subject_00410320* subject, Stream_00410320* stream,
                            int clearDirty);

// FUNCTION: GAMEMD 0x410380 — load.
long __stdcall FUN_00410380(Subject_00410320* subject, Stream_00410320* stream);

#endif  // GG_MATCH_CORE_STREAM_PERSIST_METHODS_H
