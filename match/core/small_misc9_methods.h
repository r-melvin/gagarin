// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check
//   Each entry point disassembled individually from the user's retail
//   gamemd.exe v1.001 via the local Ghidra CLI. None is bound by YRpp.
#ifndef GG_MATCH_CORE_SMALL_MISC9_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC9_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

#include "../_layout/geometry2d.h"

// CLASS IDENTITY (whole-image RTTI sweep; renamed from
// the raw `Obj_` placeholder). AircraftClass's own vtable is 0x7E22A4.
//   0x41A590 -> AircraftClass slot 93 (byte-off 0x174).
// No other table in the image holds it, so the slot is declared on
// AircraftClass rather than inherited. The METHOD name is still unknown; only the
// class is proven, so the `FUN_<addr>` member name stays a placeholder.
struct AircraftClass_0041A590;
struct Probe_005B3A00 { char _pad[0x9]; unsigned char at9; };
Probe_005B3A00* FUN_005B3A00(AircraftClass_0041A590* self);   // GAMEMD 0x5B3A00

// The virtual at +0x484 takes both arguments on the stack, so the zero-argument
// function-pointer idiom cannot express it and __fastcall would put the first
// in EDX. Same situation as receiveDamage at +0x16C: declare the slots in order
// and let cl generate the call. The dummy slots are never defined or called.
// CLASS IDENTITY (whole-image RTTI sweep; renamed from
// the raw `Obj_`/`Sub_`/`Subject_` placeholder). AircraftClass's own vtable is 0x7E22A4.
//   0x41A590 -> AircraftClass slot 93 (byte-off 0x174).
// That table is the only table in the image that holds it, so the slot is
// declared on AircraftClass and not inherited from TechnoClass/ObjectClass above it.
// The METHOD name is still unknown; only the class is proven, so the
// `FUN_<addr>` member name stays as the transitional placeholder.
struct AircraftClass_0041A590
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
    virtual void vt_1D0();
    virtual void vt_1D4();
    virtual void vt_1D8();
    virtual void vt_1DC();
    virtual void vt_1E0();
    virtual void vt_1E4();
    virtual void vt_1E8();
    virtual void vt_1EC();
    virtual void vt_1F0();
    virtual void vt_1F4();
    virtual void vt_1F8();
    virtual void vt_1FC();
    virtual void vt_200();
    virtual void vt_204();
    virtual void vt_208();
    virtual void vt_20C();
    virtual void vt_210();
    virtual void vt_214();
    virtual void vt_218();
    virtual void vt_21C();
    virtual void vt_220();
    virtual void vt_224();
    virtual void vt_228();
    virtual void vt_22C();
    virtual void vt_230();
    virtual void vt_234();
    virtual void vt_238();
    virtual void vt_23C();
    virtual void vt_240();
    virtual void vt_244();
    virtual void vt_248();
    virtual void vt_24C();
    virtual void vt_250();
    virtual void vt_254();
    virtual void vt_258();
    virtual void vt_25C();
    virtual void vt_260();
    virtual void vt_264();
    virtual void vt_268();
    virtual void vt_26C();
    virtual void vt_270();
    virtual void vt_274();
    virtual void vt_278();
    virtual void vt_27C();
    virtual void vt_280();
    virtual void vt_284();
    virtual void vt_288();
    virtual void vt_28C();
    virtual void vt_290();
    virtual void vt_294();
    virtual void vt_298();
    virtual void vt_29C();
    virtual void vt_2A0();
    virtual void vt_2A4();
    virtual void vt_2A8();
    virtual void vt_2AC();
    virtual void vt_2B0();
    virtual void vt_2B4();
    virtual void vt_2B8();
    virtual void vt_2BC();
    virtual void vt_2C0();
    virtual void vt_2C4();
    virtual void vt_2C8();
    virtual void vt_2CC();
    virtual void vt_2D0();
    virtual void vt_2D4();
    virtual void vt_2D8();
    virtual void vt_2DC();
    virtual void vt_2E0();
    virtual void vt_2E4();
    virtual void vt_2E8();
    virtual void vt_2EC();
    virtual void vt_2F0();
    virtual void vt_2F4();
    virtual void vt_2F8();
    virtual void vt_2FC();
    virtual void vt_300();
    virtual void vt_304();
    virtual void vt_308();
    virtual void vt_30C();
    virtual void vt_310();
    virtual void vt_314();
    virtual void vt_318();
    virtual void vt_31C();
    virtual void vt_320();
    virtual void vt_324();
    virtual void vt_328();
    virtual void vt_32C();
    virtual void vt_330();
    virtual void vt_334();
    virtual void vt_338();
    virtual void vt_33C();
    virtual void vt_340();
    virtual void vt_344();
    virtual void vt_348();
    virtual void vt_34C();
    virtual void vt_350();
    virtual void vt_354();
    virtual void vt_358();
    virtual void vt_35C();
    virtual void vt_360();
    virtual void vt_364();
    virtual void vt_368();
    virtual void vt_36C();
    virtual void vt_370();
    virtual void vt_374();
    virtual void vt_378();
    virtual void vt_37C();
    virtual void vt_380();
    virtual void vt_384();
    virtual void vt_388();
    virtual void vt_38C();
    virtual void vt_390();
    virtual void vt_394();
    virtual void vt_398();
    virtual void vt_39C();
    virtual void vt_3A0();
    virtual void vt_3A4();
    virtual void vt_3A8();
    virtual void vt_3AC();
    virtual void vt_3B0();
    virtual void vt_3B4();
    virtual void vt_3B8();
    virtual void vt_3BC();
    virtual void vt_3C0();
    virtual void vt_3C4();
    virtual void vt_3C8();
    virtual void vt_3CC();
    virtual void vt_3D0();
    virtual void vt_3D4();
    virtual void vt_3D8();
    virtual void vt_3DC();
    virtual void vt_3E0();
    virtual void vt_3E4();
    virtual void vt_3E8();
    virtual void vt_3EC();
    virtual void vt_3F0();
    virtual void vt_3F4();
    virtual void vt_3F8();
    virtual void vt_3FC();
    virtual void vt_400();
    virtual void vt_404();
    virtual void vt_408();
    virtual void vt_40C();
    virtual void vt_410();
    virtual void vt_414();
    virtual void vt_418();
    virtual void vt_41C();
    virtual void vt_420();
    virtual void vt_424();
    virtual void vt_428();
    virtual void vt_42C();
    virtual void vt_430();
    virtual void vt_434();
    virtual void vt_438();
    virtual void vt_43C();
    virtual void vt_440();
    virtual void vt_444();
    virtual void vt_448();
    virtual void vt_44C();
    virtual void vt_450();
    virtual void vt_454();
    virtual void vt_458();
    virtual void vt_45C();
    virtual void vt_460();
    virtual void vt_464();
    virtual void vt_468();
    virtual void vt_46C();
    virtual void vt_470();
    virtual void vt_474();
    virtual void vt_478();
    virtual void vt_47C();
    virtual void vt_480();
    virtual void vt_484(int a, int b);                       // +0x0484

    // FUNCTION: GAMEMD 0x41A590 — three arguments are declared and none used.
    void FUN_0041A590(int a, int b, int c);
};

struct Obj_0042EB20
{
    char  _pad00[0x8];
    char* Items;   // +0x0008  sixteen-byte records

    // The lookup is __thiscall - retail pushes the key rather than passing it
    // in EDX - so it is declared as a member alongside its caller.
    int FUN_0042EB50(int key);   // GAMEMD 0x42EB50

    // FUNCTION: GAMEMD 0x42EB20
    char* FUN_0042EB20(int key);
};
GG_STATIC_ASSERT(offsetof(Obj_0042EB20, Items) == 0x8);

// GLOBAL: GAMEMD 0x819288 — six eight-byte entries, value first then key. The
// scan runs to 0x8192BC, which is what fixes the count at six.
struct Entry8 { void* Value; int Key; };
extern Entry8 DAT_00819288[6];

// FUNCTION: GAMEMD 0x45DD20 — look the key up; fall back to the first entry.
void* FUN_0045DD20(int key);

#endif  // GG_MATCH_CORE_SMALL_MISC9_METHODS_H
