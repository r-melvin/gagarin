// SPDX-License-Identifier: GPL-3.0-or-later
// Provenance: own-binary-via-Ghidra | YRpp-cross-check | behaviour-confirmed-name
//   Offsets read numerically off the user's retail gamemd.exe v1.001 through
//   the local Ghidra CLI at 0x629E90:
//     FootClass  the facing sub-object at +0x388 (`ADD ECX,0x388` before
//                CALL 0x4C93D0, which takes one pushed out-buffer address and
//                returns a pointer whose first word is read `MOVSX ECX,
//                word ptr [EAX]` and biased by 0x3FFF).
//     the three stack arguments are [EBP+0x8], [EBP+0xC] and [EBP+0x10] and
//     become the X/Y/Z of a 12-byte CoordStruct built at [ESP+0x38..0x40]
//     whose address is pushed (`LEA EDX,[ESP+0x44]`); RET 0xC.
//     ScenarioClass::Instance at 0xA8B230 with its randomizer at +0x218
//     (`LEA ECX,[EDX+0x218]` before CALL 0x65C7E0).
//     RulesClass::Instance at 0x8871E0 with the wake animation type at +0x94
//     (`MOV EDX,[ECX+0x94]`, pushed as the first constructor argument).
//     AnimClass is 0x1C8 bytes (`PUSH 0x1C8` into 0x7C8E17) and its
//     constructor is 0x421EA0.
//     The double constant at 0x7E2810 scales the facing into radians.
//   The scenario randomizer agrees with
//   match/ai/trigger_class_reset_timers_methods.h and the 0x1C8/0x421EA0 pair
//   with match/ai/house_class_psi_warn_methods.h (neither edited; both
//   re-derived here so the TU stands alone). Names cross-checked against YRpp
//   (offsets reconfirmed).
#ifndef GG_MATCH_MOVEMENT_FOOT_CLASS_WAKES_METHODS_H
#define GG_MATCH_MOVEMENT_FOOT_CLASS_WAKES_METHODS_H

#include <stddef.h>
#include "../_rt/gg_static_assert.h"

// FUNCTION: GAMEMD 0x7C8E17 (decl; reloc) — operator new, __cdecl.
extern "C" void* __cdecl FUN_007C8E17(unsigned int size);
// FUNCTION: GAMEMD 0x4CAD00 (decl; reloc) — the in-image CRT cos.
extern "C" double __cdecl FUN_004CAD00(double x);
// FUNCTION: GAMEMD 0x4CACB0 (decl; reloc) — the in-image CRT sin.
extern "C" double __cdecl FUN_004CACB0(double x);

// GLOBAL: GAMEMD 0x7E2810 — the facing-to-radians scale.
extern const double DAT_007E2810;

struct CoordStruct_00629E90
{
    int X;    // +0x0000
    int Y;    // +0x0004
    int Z;    // +0x0008
};
GG_STATIC_ASSERT(offsetof(CoordStruct_00629E90, Z) == 0x8);
GG_STATIC_ASSERT(sizeof(CoordStruct_00629E90) == 0xC);

// The word the facing helper writes out; only its first member is read.
struct DirStruct_00629E90
{
    short Value;   // +0x0000
    short _pad002;
};
GG_STATIC_ASSERT(sizeof(DirStruct_00629E90) == 4);

// The FootClass facing sub-object at +0x388.
struct Facing_00629E90
{
    // FUNCTION: GAMEMD 0x4C93D0 (decl; reloc) — current facing into `out`.
    short* GetCurrent(DirStruct_00629E90* out);
};

// The scenario randomizer; only the ranged draw is called.
struct Random_00629E90
{
    // FUNCTION: GAMEMD 0x65C7E0 (decl; reloc) — Randomizer::RandomRanged.
    int RandomRanged(int min, int max);
};

// ScenarioClass — only Random @0x218 is touched.
struct Scenario_00629E90
{
    char            _pad000[0x218];   // +0x0000
    Random_00629E90 Random;           // +0x0218
};
GG_STATIC_ASSERT(offsetof(Scenario_00629E90, Random) == 0x218);

// GLOBAL: GAMEMD 0xA8B230 — ScenarioClass::Instance.
extern Scenario_00629E90* DAT_00A8B230;

struct AnimTypeClass_00629E90;

// RulesClass — only the wake animation type @0x94 is touched.
struct Rules_00629E90
{
    char _pad000[0x94];                  // +0x0000
    AnimTypeClass_00629E90* At_94;       // +0x0094
};
GG_STATIC_ASSERT(offsetof(Rules_00629E90, At_94) == 0x94);

// GLOBAL: GAMEMD 0x8871E0 — RulesClass::Instance.
extern Rules_00629E90* DAT_008871E0;

// AnimClass — sizeof 0x1C8; only the constructor is used.
struct AnimClass_00629E90
{
    char _pad000[0x1C8];

    // FUNCTION: GAMEMD 0x421EA0 (decl; reloc) — the constructor, spelled as an
    // ordinary __thiscall member so the allocate/test/construct expansion can
    // be written out by hand (a real `new T(...)` drags in a /GX EH frame
    // retail does not have).
    AnimClass_00629E90* FUN_00421EA0(AnimTypeClass_00629E90* type,
                                     const CoordStruct_00629E90& coords,
                                     int loopDelay, int loopCount,
                                     unsigned int flags, int forceZAdjust,
                                     char reverse);
};
GG_STATIC_ASSERT(sizeof(AnimClass_00629E90) == 0x1C8);

struct Foot_00629E90
{
    char            _pad000[0x388];   // +0x0000
    Facing_00629E90 Facing;           // +0x0388

    // FUNCTION: GAMEMD 0x629E90
    void CreateWakes(int x, int y, int z);
};
GG_STATIC_ASSERT(offsetof(Foot_00629E90, Facing) == 0x388);

#endif  // GG_MATCH_MOVEMENT_FOOT_CLASS_WAKES_METHODS_H
