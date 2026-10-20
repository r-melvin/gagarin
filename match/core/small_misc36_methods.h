// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, vtable slots and globals read numerically off the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI at the three addresses below.
//   None is bound by YRpp or the seed map, so placeholder names are kept.
//
// Three unrelated small __thiscall methods, grouped only by size. Each carries
// its own vtable-shaped class: the dummy `vt_XXX` slots exist to place the one
// or two slots actually called at the right displacement, and carry no claim
// about what those slots are.
#ifndef GG_MATCH_CORE_SMALL_MISC36_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC36_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// 0x4115F0 - a weighted two-term sum with a side effect.
//
// Bumps the counter at +0x0C, then returns the base at +0x14 plus each of two
// virtual results scaled by one of the two stack arguments. `RET 0x8` with the
// object in ECX pins it as __thiscall with two 4-byte arguments; [ESP+0x10] and
// [ESP+0x14] are those arguments seen past the three saved registers and the
// return address.
// ---------------------------------------------------------------------------
// CLASS IDENTITY (whole-image RTTI sweep, docs/rtti_sweep.md; renamed from
// the raw `Obj_` placeholder). BSurface's own vtable is 0x7E2070.
//   0x4115F0 -> BSurface slot 23 (byte-off 0x5C).
// No other table in the image holds it, so the slot is declared on
// BSurface rather than inherited. The METHOD name is still unknown; only the
// class is proven, so the `FUN_<addr>` member name stays a placeholder.
struct BSurface_004115F0
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
    virtual void vt_030();
    virtual void vt_034();
    virtual void vt_038();
    virtual void vt_03C();
    virtual void vt_040();
    virtual void vt_044();
    virtual void vt_048();
    virtual void vt_04C();
    virtual void vt_050();
    virtual void vt_054();
    virtual void vt_058();
    virtual void vt_05C();
    virtual void vt_060();
    virtual void vt_064();
    virtual void vt_068();
    virtual void vt_06C();
    virtual int vt_070();   // +0x0070
    virtual int vt_074();   // +0x0074

    char _pad04[0x0C - 0x04];
    int  Counter;      // +0x000C
    char _pad10[0x4];
    int  Base;         // +0x0014

    // FUNCTION: GAMEMD 0x4115F0
    int FUN_004115F0(int scaleA, int scaleB);
};
GG_STATIC_ASSERT(offsetof(BSurface_004115F0, Counter) == 0x0C);
GG_STATIC_ASSERT(offsetof(BSurface_004115F0, Base) == 0x14);

// ---------------------------------------------------------------------------
// 0x4587D0 - a two-hop predicate.
//
// Asks the argument object, through its slot +0x8C, for something derived from
// this object's field at +0x21C, then feeds that answer plus a global back into
// this object's own slot +0x100 and reports whether the result was non-zero.
// The `TEST EAX,EAX; SETNZ AL` tail is a bool return, not the raw value.
// ---------------------------------------------------------------------------
struct Arg_004587D0
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
    virtual void vt_030();
    virtual void vt_034();
    virtual void vt_038();
    virtual void vt_03C();
    virtual void vt_040();
    virtual void vt_044();
    virtual void vt_048();
    virtual void vt_04C();
    virtual void vt_050();
    virtual void vt_054();
    virtual void vt_058();
    virtual void vt_05C();
    virtual void vt_060();
    virtual void vt_064();
    virtual void vt_068();
    virtual void vt_06C();
    virtual void vt_070();
    virtual void vt_074();
    virtual void vt_078();
    virtual void vt_07C();
    virtual void vt_080();
    virtual void vt_084();
    virtual void vt_088();
    virtual int vt_08C(void* owner);   // +0x008C
};

// GLOBAL: GAMEMD 0x89C818 - loaded straight into the second argument slot.
extern void* volatile DAT_0089C818;

struct Obj_004587D0
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
    virtual void vt_030();
    virtual void vt_034();
    virtual void vt_038();
    virtual void vt_03C();
    virtual void vt_040();
    virtual void vt_044();
    virtual void vt_048();
    virtual void vt_04C();
    virtual void vt_050();
    virtual void vt_054();
    virtual void vt_058();
    virtual void vt_05C();
    virtual void vt_060();
    virtual void vt_064();
    virtual void vt_068();
    virtual void vt_06C();
    virtual void vt_070();
    virtual void vt_074();
    virtual void vt_078();
    virtual void vt_07C();
    virtual void vt_080();
    virtual void vt_084();
    virtual void vt_088();
    virtual void vt_08C();
    virtual void vt_090();
    virtual void vt_094();
    virtual void vt_098();
    virtual void vt_09C();
    virtual void vt_0A0();
    virtual void vt_0A4();
    virtual void vt_0A8();
    virtual void vt_0AC();
    virtual void vt_0B0();
    virtual void vt_0B4();
    virtual void vt_0B8();
    virtual void vt_0BC();
    virtual void vt_0C0();
    virtual void vt_0C4();
    virtual void vt_0C8();
    virtual void vt_0CC();
    virtual void vt_0D0();
    virtual void vt_0D4();
    virtual void vt_0D8();
    virtual void vt_0DC();
    virtual void vt_0E0();
    virtual void vt_0E4();
    virtual void vt_0E8();
    virtual void vt_0EC();
    virtual void vt_0F0();
    virtual void vt_0F4();
    virtual void vt_0F8();
    virtual void vt_0FC();
    virtual int vt_100(int derived, void* context);   // +0x0100

    char  _pad04[0x21C - 0x04];
    void* Owner;       // +0x021C

    // FUNCTION: GAMEMD 0x4587D0
    bool FUN_004587D0(Arg_004587D0* other);
};
GG_STATIC_ASSERT(offsetof(Obj_004587D0, Owner) == 0x21C);

// ---------------------------------------------------------------------------
// 0x43E900 - a negated lookup with a conditional offset.
//
// Slot +0x1D0 produces a key, the __fastcall helper at 0x6D20E0 turns it into a
// value, and the value is negated. The object at +0x520 then decides whether a
// second field is added on top: the flag at +0x16C5 gates it, and the JZ lands
// on the bare `MOV EAX,ECX` tail, so the unadjusted value is the trailing block
// and the addition is the fall-through.
// ---------------------------------------------------------------------------
// The object hanging off BuildingClass+0x520. Not named by RTTI directly -- it
// is reached only as a member load -- but +0x520 is `BuildingTypeClass* Type`
// on two independent counts: match/combat/building_class_voxel_barrel_methods.h
// already matches 0x458810 against `Type` at +0x520, and YRpp's BuildingClass
// lays Type out as the first member after the TechnoClass base with unknown_544
// at +0x544. Renamed from `Sub_0043E900`; still a per-address partial layout.
struct BuildingTypeClass_0043E900
{
    char _pad000[0x11E8];
    int  Adjustment;   // +0x11E8
    char _pad11EC[0x16C5 - 0x11EC];
    char Enabled;      // +0x16C5
};
GG_STATIC_ASSERT(offsetof(BuildingTypeClass_0043E900, Adjustment) == 0x11E8);
GG_STATIC_ASSERT(offsetof(BuildingTypeClass_0043E900, Enabled) == 0x16C5);

// FUNCTION: GAMEMD 0x6D20E0 - reached as `MOV ECX,EAX; CALL`, returns in EAX
// with no stack adjustment, so one register argument: __fastcall.
int __fastcall FUN_006D20E0(int key);

// CLASS IDENTITY (whole-image RTTI sweep, docs/rtti_sweep.md; renamed from
// the raw `Obj_`/`Sub_`/`Subject_` placeholder). BuildingClass's own vtable is 0x7E3EBC.
//   0x43E900 -> BuildingClass slot 187 (byte-off 0x2EC).
// That table is the only table in the image that holds it, so the slot is
// declared on BuildingClass and not inherited from TechnoClass/ObjectClass above it.
// The METHOD name is still unknown; only the class is proven, so the
// `FUN_<addr>` member name stays as the transitional placeholder.
struct BuildingClass_0043E900
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
    virtual void vt_030();
    virtual void vt_034();
    virtual void vt_038();
    virtual void vt_03C();
    virtual void vt_040();
    virtual void vt_044();
    virtual void vt_048();
    virtual void vt_04C();
    virtual void vt_050();
    virtual void vt_054();
    virtual void vt_058();
    virtual void vt_05C();
    virtual void vt_060();
    virtual void vt_064();
    virtual void vt_068();
    virtual void vt_06C();
    virtual void vt_070();
    virtual void vt_074();
    virtual void vt_078();
    virtual void vt_07C();
    virtual void vt_080();
    virtual void vt_084();
    virtual void vt_088();
    virtual void vt_08C();
    virtual void vt_090();
    virtual void vt_094();
    virtual void vt_098();
    virtual void vt_09C();
    virtual void vt_0A0();
    virtual void vt_0A4();
    virtual void vt_0A8();
    virtual void vt_0AC();
    virtual void vt_0B0();
    virtual void vt_0B4();
    virtual void vt_0B8();
    virtual void vt_0BC();
    virtual void vt_0C0();
    virtual void vt_0C4();
    virtual void vt_0C8();
    virtual void vt_0CC();
    virtual void vt_0D0();
    virtual void vt_0D4();
    virtual void vt_0D8();
    virtual void vt_0DC();
    virtual void vt_0E0();
    virtual void vt_0E4();
    virtual void vt_0E8();
    virtual void vt_0EC();
    virtual void vt_0F0();
    virtual void vt_0F4();
    virtual void vt_0F8();
    virtual void vt_0FC();
    virtual void vt_100();
    virtual void vt_104();
    virtual void vt_108();
    virtual void vt_10C();
    virtual void vt_110();
    virtual void vt_114();
    virtual void vt_118();
    virtual void vt_11C();
    virtual void vt_120();
    virtual void vt_124();
    virtual void vt_128();
    virtual void vt_12C();
    virtual void vt_130();
    virtual void vt_134();
    virtual void vt_138();
    virtual void vt_13C();
    virtual void vt_140();
    virtual void vt_144();
    virtual void vt_148();
    virtual void vt_14C();
    virtual void vt_150();
    virtual void vt_154();
    virtual void vt_158();
    virtual void vt_15C();
    virtual void vt_160();
    virtual void vt_164();
    virtual void vt_168();
    virtual void vt_16C();
    virtual void vt_170();
    virtual void vt_174();
    virtual void vt_178();
    virtual void vt_17C();
    virtual void vt_180();
    virtual void vt_184();
    virtual void vt_188();
    virtual void vt_18C();
    virtual void vt_190();
    virtual void vt_194();
    virtual void vt_198();
    virtual void vt_19C();
    virtual void vt_1A0();
    virtual void vt_1A4();
    virtual void vt_1A8();
    virtual void vt_1AC();
    virtual void vt_1B0();
    virtual void vt_1B4();
    virtual void vt_1B8();
    virtual void vt_1BC();
    virtual void vt_1C0();
    virtual void vt_1C4();
    virtual void vt_1C8();
    virtual void vt_1CC();
    virtual int vt_1D0();   // +0x01D0

    char          _pad04[0x520 - 0x04];
    BuildingTypeClass_0043E900* Settings;   // +0x0520

    // FUNCTION: GAMEMD 0x43E900
    int FUN_0043E900();
};
GG_STATIC_ASSERT(offsetof(BuildingClass_0043E900, Settings) == 0x520);

#endif  // GG_MATCH_CORE_SMALL_MISC36_METHODS_H
