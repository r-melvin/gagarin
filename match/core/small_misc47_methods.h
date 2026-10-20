// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra
//   Offsets, slot displacements and CRT helper addresses read numerically off
//   the user's retail gamemd.exe v1.001 via the local Ghidra CLI at 0x412610,
//   0x455D50 and 0x455DA0.
#ifndef GG_MATCH_CORE_SMALL_MISC47_METHODS_H
#define GG_MATCH_CORE_SMALL_MISC47_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// ---------------------------------------------------------------------------
// 0x412610 — parse a hexadecimal string.
//
// The two CRT helpers are identified by their use: 0x7C99B4 gates the loop on
// each character and 0x7C97D3 folds a letter's case before the 0x37 subtraction,
// i.e. `isxdigit` and `toupper`. Both take an `int`, which is why retail
// sign-extends the character with `MOVSX` at each call.
//
// The loop condition is the pointer, not the digit test: retail re-tests EDI at
// the bottom (`TEST EDI,EDI; JNZ`) even though it was just incremented, and the
// non-digit exit is a `break` inside the body.
// ---------------------------------------------------------------------------
extern "C" int __cdecl FUN_007C99B4(int c);   // isxdigit
extern "C" int __cdecl FUN_007C97D3(int c);   // toupper

// FUNCTION: GAMEMD 0x412610
int __fastcall FUN_00412610(const char* text);

// ---------------------------------------------------------------------------
// 0x455D50 — run an optional step, then the mandatory one.
//
// Type 0x13 is excluded outright. Otherwise the optional step at 0x70C610 runs
// when either slot +0x284 says so or the settings flag at +0x16B9 is set, and
// 0x709A30 runs regardless. Both arguments are read from the stack only after
// the virtual call, which is why they are not held in locals up front.
// ---------------------------------------------------------------------------
struct Settings_00455D50
{
    char _pad000[0xEB8];
    int  Mode;       // +0x0EB8
    char _padEBC[0x16A9 - 0xEBC];
    char FlagA9;     // +0x16A9
    char _pad16AA[0x16AC - 0x16AA];
    char FlagAC;     // +0x16AC
    char _pad16AD[0x16B9 - 0x16AD];
    char FlagB9;     // +0x16B9
};
GG_STATIC_ASSERT(offsetof(Settings_00455D50, Mode) == 0xEB8);
GG_STATIC_ASSERT(offsetof(Settings_00455D50, FlagA9) == 0x16A9);
GG_STATIC_ASSERT(offsetof(Settings_00455D50, FlagAC) == 0x16AC);
GG_STATIC_ASSERT(offsetof(Settings_00455D50, FlagB9) == 0x16B9);

// CLASS IDENTITY (whole-image RTTI sweep, docs/rtti_sweep.md; renamed from
// the raw `Obj_`/`Sub_`/`Subject_` placeholder). BuildingClass's own vtable is 0x7E3EBC.
//   0x455D50 -> BuildingClass slot 288 (byte-off 0x480).
//   0x455DA0 -> BuildingClass slot 161 (byte-off 0x284).
// Each of those tables is the only table in the image that holds them, so the slot is
// declared on BuildingClass and not inherited from TechnoClass/ObjectClass above it.
// The METHOD name is still unknown; only the class is proven, so the
// `FUN_<addr>` member name stays as the transitional placeholder.
struct BuildingClass_00455D50
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
    virtual bool vt_284();   // +0x0284

    char               _pad004[0xAC - 0x04];
    int                Type;       // +0x00AC
    char               _pad0B0[0x520 - 0xB0];
    Settings_00455D50* Settings;   // +0x0520

    // FUNCTION: GAMEMD 0x70C610
    void FUN_0070C610(void* first);
    // FUNCTION: GAMEMD 0x709A30
    void FUN_00709A30(void* first, void* second);

    // FUNCTION: GAMEMD 0x455D50
    void FUN_00455D50(void* first, void* second);
    // FUNCTION: GAMEMD 0x455DA0
    //
    // Ghidra has no function record at this entry point, so its length is
    // pinned in the manifest by hand: 0x30 bytes, ending at the `MOV AL,0x1;
    // RET` at 0x455DCD.
    bool FUN_00455DA0();
};
GG_STATIC_ASSERT(offsetof(BuildingClass_00455D50, Type) == 0xAC);
GG_STATIC_ASSERT(offsetof(BuildingClass_00455D50, Settings) == 0x520);

// ---------------------------------------------------------------------------
// 0x41D7E0 — "has this entry come due, or has its target changed?"
//
// Which of the two delays applies is decided by 0x750010 against the object at
// +0x4C offset by 0x150; retail branches for it rather than using a
// conditional move. When the suppression flag at +0x3C is clear and the deadline
// has passed the answer is an outright yes, otherwise it falls through to
// comparing the argument against +0x50.
// ---------------------------------------------------------------------------
// GLOBAL: GAMEMD 0xA8ED84 — the engine frame counter.
#include "../core/frame_counter.h"

// FUNCTION: GAMEMD 0x750010 — the mode test, __fastcall, byte result.
bool __fastcall FUN_00750010(void* subject);

struct Obj_0041D7E0
{
    char  _pad000[0x3C];
    char  Suppressed;   // +0x003C
    char  _pad03D[0x40 - 0x3D];
    int   Start;        // +0x0040
    int   DelayA;       // +0x0044
    int   DelayB;       // +0x0048
    char* Subject;      // +0x004C
    int   Target;       // +0x0050

    // FUNCTION: GAMEMD 0x41D7E0
    bool FUN_0041D7E0(int candidate);
};
GG_STATIC_ASSERT(offsetof(Obj_0041D7E0, Suppressed) == 0x3C);
GG_STATIC_ASSERT(offsetof(Obj_0041D7E0, Start) == 0x40);
GG_STATIC_ASSERT(offsetof(Obj_0041D7E0, Subject) == 0x4C);
GG_STATIC_ASSERT(offsetof(Obj_0041D7E0, Target) == 0x50);

#endif  // GG_MATCH_CORE_SMALL_MISC47_METHODS_H
