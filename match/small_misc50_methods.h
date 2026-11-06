// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Native field offsets and control flow for 0x4253B0 and 0x44FE60.
//   The former private 0x410960 constructor view has been replaced by
//   AbstractTypeClass in the implementation file.
#ifndef GG_MATCH_CORE_SMALL_MISC50_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC50_METHODS_H

#include <stddef.h>
#include "_rt/gg_static_assert.h"
#include "_layout/building_class.h"
#include "_layout/building_array.h"

// ---------------------------------------------------------------------------
// 0x4253B0 — record where this object's key appears in the registry, then
// forward.
//
// The search runs backwards from the last entry, so the recorded index is the
// *last* match rather than the first. Not-found leaves -1, and retail reaches
// that store by falling through while the found path jumps over it - two
// separate writes to +0xD8, not one.
//
// The bottom-of-loop `TEST EAX,EAX; JGE` is genuine here, not the redundant
// test-self of section 4.8: the `SUB ECX,4` between the `DEC` and the `TEST`
// clobbers the flags, so the compare has to be repeated.
// ---------------------------------------------------------------------------
struct Entry_004253B0
{
    char  _pad000[0x30C];
    void* Key;   // +0x030C
};
GG_STATIC_ASSERT(offsetof(Entry_004253B0, Key) == 0x30C);

// GLOBAL: GAMEMD 0xB054D4 — the registry; 0xB054E0 is its count.
extern Entry_004253B0** DAT_00B054D4;
extern int              DAT_00B054E0;

// CLASS IDENTITY (whole-image RTTI sweep; renamed from the
// invented `Subject_004253B0`). 0x4253B0 sits at slot 6 (byte-off 0x18) of
// AnimClass's own vtable 0x7E3354, and in no other table in the image. The
// virtual is `__stdcall`, so `this` arrives as the first STACK argument rather
// than in ECX -- that is why it is written as a free function taking the object
// pointer, and why naming the class means typing that parameter. 0x410320, the
// forward target below, takes the same object and is in no vtable at all.
struct AnimClass_004253B0
{
    char  _pad000[0xD4];
    void* Key;     // +0x00D4
    int   Index;   // +0x00D8
};
GG_STATIC_ASSERT(offsetof(AnimClass_004253B0, Key) == 0xD4);
GG_STATIC_ASSERT(offsetof(AnimClass_004253B0, Index) == 0xD8);

// FUNCTION: GAMEMD 0x410320 — the forward target, __stdcall.
long __stdcall FUN_00410320(AnimClass_004253B0* subject, void* second, void* third);

// FUNCTION: GAMEMD 0x4253B0
long __stdcall FUN_004253B0(AnimClass_004253B0* subject, void* second, void* third);

// ---------------------------------------------------------------------------
// 0x44FE60 — select the INI section, then run one step per eligible entry.
//
// The section name is not a literal but a pointer held at 0x7E3E88, so it is
// loaded before being pushed. An entry is skipped when either its own byte at
// +0x81 or the settings byte at +0x16BF is set; the step itself is a
// __thiscall on the entry with the INI as its argument.
// ---------------------------------------------------------------------------
// GLOBAL: GAMEMD 0x7E3E88 — holds the section name pointer.
extern const char* DAT_007E3E88;

struct Ini_0044FE60
{
    // FUNCTION: GAMEMD 0x5257C0
    void FUN_005257C0(const char* section, int flags);
};

// FUNCTION: GAMEMD 0x44FE60
void FUN_0044FE60(Ini_0044FE60* ini);

#endif  // GG_MATCH_CORE_SMALL_MISC50_METHODS_H
