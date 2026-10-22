// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Read numerically off the user's retail gamemd.exe v1.001 via the local
//   Ghidra CLI at 0x407020 / 0x409310 / 0x411640 / 0x422BC0 / 0x437F30. None is
//   bound by YRpp.
//   Bytes and offsets read numerically off the user's retail gamemd.exe
//   v1.001 via the local Ghidra CLI at each address below. Nothing names any
//   of these three, so they keep Ghidra placeholder names.
//
// FUN_004DB250 — a two-DWORD-argument __stdcall no-op: `RET 8` alone, no
//   body. It is called directly (not just seated in a vtable), so it is
//   modelled as a plain free function rather than a method.
// FUN_004F42A0 / FUN_004F42E0 — two distinct retail addresses, byte-identical
//   bodies (`DAT_00a8ef54 = 0; RET`), each its own MapClass-vtable slot (see
//   match/map/map_class_more_methods.h for the sibling slot at 0x4F42D0).
//   Not folded by the linker because they are genuinely two different
//   overridden virtuals that both happen to reset the same static flag.
//
// NOTE: 0x4F4C20 and 0x4F4CA0, originally drafted alongside these, were
// dropped from this file — they collide with in-flight work already staked
// out (as "(decl; reloc)" forward declarations) in
// match/combat/scratch_buffer_vector_methods.h (ScratchEntry's out-of-line
// default ctor) and match/renderer/color_scheme_iterator_methods.h
// (Entry_00626690::IsBlank), both of which model a deeper surrounding class
// than the bare-pointer shape used here. Left for whoever owns that cluster.
#ifndef GG_MATCH_CORE_MISC_LEAF_METHODS_H
#define GG_MATCH_CORE_MISC_LEAF_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// GLOBAL: GAMEMD 0x87E730 — an init reference count.
extern int DAT_0087E730;

// The one-time initialiser the count guards. Declared only.
void __cdecl FUN_0040A940();

// FUNCTION: GAMEMD 0x407020 — first acquire runs the initialiser.
void __cdecl FUN_00407020();

// A helper taking (this, 0) in ECX/EDX, so __fastcall. Declared only.
void FUN_004091C0(void* self, int arg);

struct Obj_00409300b
{
    char _pad00[0x8];
    int  unknown_08;   // +0x0008

    // FUNCTION: GAMEMD 0x409310
    int FUN_00409310();
};
GG_STATIC_ASSERT(offsetof(Obj_00409300b, unknown_08) == 0x8);

// Declared only; __thiscall, returns an int.
// CLASS IDENTITY (whole-image RTTI sweep; renamed from
// the raw `Obj_` placeholder). AnimClass's own vtable is 0x7E3354.
//   0x422BC0 -> AnimClass slot 46 (byte-off 0xB8).
// No other table in the image holds it, so the slot is declared on
// AnimClass rather than inherited. The METHOD name is still unknown; only the
// class is proven, so the `FUN_<addr>` member name stays a placeholder.
struct AnimClass_00422B00;
int FUN_005F6BD0(AnimClass_00422B00* self);

// CLASS IDENTITY (whole-image RTTI sweep; renamed from
// the raw `Obj_`/`Sub_`/`Subject_` placeholder). AnimClass's own vtable is 0x7E3354.
//   0x422BC0 -> AnimClass slot 46 (byte-off 0xB8).
// That table is the only table in the image that holds it, so the slot is
// declared on AnimClass and not inherited from TechnoClass/ObjectClass above it.
// The METHOD name is still unknown; only the class is proven, so the
// `FUN_<addr>` member name stays as the transitional placeholder.
struct AnimClass_00422B00
{
    char _pad000[0x104];
    int  unknown_104;   // +0x0104

    // FUNCTION: GAMEMD 0x422BC0
    int FUN_00422BC0();
};
GG_STATIC_ASSERT(offsetof(AnimClass_00422B00, unknown_104) == 0x104);

// An eight-byte value type returned by value: the caller passes a hidden
// destination pointer as the only stack argument (`RET 4`) and gets it back in
// EAX, which is what MSVC does for any struct larger than four bytes.
struct Pair8
{
    int a;
    int b;
};

struct Obj_00437F00
{
    int unknown_00;   // +0x0000
    int unknown_04;   // +0x0004

    // FUNCTION: GAMEMD 0x437F30
    Pair8 FUN_00437F30() const;
};

// PLACEHOLDER DELIBERATELY KEPT (whole-image RTTI sweep).
// 0x4DB250 is slot 69 (byte-off 0x114) of FootClass's own vtable 0x7E8C94 and
// appears in no other table in the image, so FootClass declares it -- an empty
// `__stdcall` virtual. The modelled signature takes two raw `unsigned int`s and
// no object pointer at all, so there is no parameter to carry the class name;
// retyping the first argument as a pointer would be a modelling change, not a
// rename. Class and slot recorded here; the symbol stays `FUN_004DB250`.
// FUNCTION: GAMEMD 0x4DB250
void __stdcall FUN_004DB250(unsigned int unused1, unsigned int unused2);

// The static flag both 0x4F42A0 and 0x4F42E0 clear.
extern int DAT_00a8ef54;

// FUNCTION: GAMEMD 0x4F42A0
void __stdcall FUN_004F42A0(void);
// FUNCTION: GAMEMD 0x4F42E0
void __stdcall FUN_004F42E0(void);

#endif  // GG_MATCH_CORE_MISC_LEAF_METHODS_H
