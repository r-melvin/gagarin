// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x408E00 / 0x40E4A0 / 0x41C210 / 0x426590. None is
//   bound by YRpp.
//
// Four scalar deleting destructors and one teardown.
//
// A scalar deleting destructor is what MSVC emits for a class with a virtual
// destructor: it runs the real destructor, then frees the object only if bit 0
// of its flag argument is set, and hands the pointer back. Retail's shape is
// `CALL <dtor>; TEST byte ptr [ESP+8],1; JZ; PUSH ESI; CALL <free>; MOV EAX,ESI`.
//
// These are written as ordinary functions rather than by declaring four classes
// with virtual destructors and letting cl emit `??_G`. Compiler-generated ones
// would inline a trivial destructor body into the thunk and lose the CALL,
// which is exactly the instruction that has to be there.
#ifndef GG_MATCH_CORE_DELETING_DTOR_METHODS_H
#define GG_MATCH_CORE_DELETING_DTOR_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

extern "C" void __cdecl FUN_007C8B3D(void* block);

// The four real destructors, declared only so cl emits reloc-normalised calls.
void FUN_00414080(void* self);   // GAMEMD 0x414080
void FUN_004228E0(void* self);   // GAMEMD 0x4228E0
void FUN_00466560(void* self);   // GAMEMD 0x466560
void FUN_005565A0(void* self);   // GAMEMD 0x5565A0

struct Obj_00408E00
{
    char  _pad00[0x10];
    void* unknown_10;   // +0x0010  owned buffer

    // FUNCTION: GAMEMD 0x408E00
    void FUN_00408E00();
};
GG_STATIC_ASSERT(offsetof(Obj_00408E00, unknown_10) == 0x10);

// The flag argument is declared unsigned int — four bytes of stack, matching
// `RET 4` — even though retail only ever tests its low byte.
struct Obj_0040E400 { void* FUN_0040E4A0(unsigned int flags); };  // FUNCTION: GAMEMD 0x40E4A0
// CLASS IDENTITY (whole-image RTTI sweep; renamed from
// the raw `Obj_` placeholder). AircraftClass's own vtable is 0x7E22A4.
//   0x41C210 -> AircraftClass slot 8 (byte-off 0x20).
// No other table in the image holds it, so the slot is declared on
// AircraftClass rather than inherited. The METHOD name is still unknown; only the
// class is proven, so the `FUN_<addr>` member name stays a placeholder.
struct AircraftClass_0041C200b { void* FUN_0041C210(unsigned int flags); }; // FUNCTION: GAMEMD 0x41C210
// CLASS IDENTITY (whole-image RTTI sweep; renamed from
// the raw `Obj_` placeholder). AnimClass's own vtable is 0x7E3354.
//   0x426590 -> AnimClass slot 8 (byte-off 0x20).
// No other table in the image holds it, so the slot is declared on
// AnimClass rather than inherited. The METHOD name is still unknown; only the
// class is proven, so the `FUN_<addr>` member name stays a placeholder.
struct AnimClass_00426500 { void* FUN_00426590(unsigned int flags); };  // FUNCTION: GAMEMD 0x426590
struct Obj_0046B500 { void* FUN_0046B5C0(unsigned int flags); };  // FUNCTION: GAMEMD 0x46B5C0
struct Obj_00473900 { void* FUN_00473920(unsigned int flags); };  // FUNCTION: GAMEMD 0x473920

#endif  // GG_MATCH_CORE_DELETING_DTOR_METHODS_H
